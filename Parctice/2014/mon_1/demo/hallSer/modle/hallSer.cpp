#include"hallSer.h"
#include"gameSer.h"
extern set<IpInfo> ipInfoSet;
HallSer::HallSer(void)
{
    init();
    strncpy(ip,HALL_IP,sizeof(ip));
    strncpy(name,HALL_NAME,sizeof(name));
    port = HALL_PORT;
    upperNum = HALL_UPPER;
    initGameSer();
    runLoop();
}

HallSer::~HallSer(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    close(listenerFd);
    delAllGameSer();
}
//关闭某个游戏服务器的所有连接
void HallSer::closeGameSerFd(size_t index)
{
    map<INDEX_TYPE,set<UID_TYPE> >::iterator index_it = indexUidMap.find(index);
    if(index_it == indexUidMap.end())
    {
        return;
    }
    set<UID_TYPE> &uidSet = indexUidMap[index];
    for(set<UID_TYPE>::iterator uid_it = uidSet.begin();uid_it != uidSet.end();++uid_it)
    {
        map<UID_TYPE,CONNECT_TYPE>::iterator fd_it = uidFdMap.find(*uid_it);
        if(fd_it == uidFdMap.end())
        {
             perror("fd_it is error");
             exit(0);
        }
        CONNECT_TYPE fd = uidFdMap[*uid_it];
        close(uidFdMap[*uid_it]);
        map<CONNECT_TYPE,UID_TYPE>::iterator _uid_it = fdUidMap.find(fd);
        if(_uid_it == fdUidMap.end())
        {
            perror("_uid_it is error");
            exit(0);
        }
        fdUidMap.erase(_uid_it);
        map<UID_TYPE,INDEX_TYPE>::iterator _index_it = uidIndexMap.find(*uid_it);
        if(_index_it == uidIndexMap.end())
        {
            perror("_index_it is error");
            exit(0);
        }
        uidIndexMap.erase(_index_it);
        uidFdMap.erase(fd_it);
    }
    indexUidMap.erase(index_it);
}
void HallSer::delAllGameSer(void)
{
    size_t size = gameSerVec.size();
    for(size_t index = 0;index < size;++index)
    {
        closeGameSerFd(index);
        delete gameSerVec[index];
        gameSerVec[index] = NULL;
    }
    gameSerVec.clear();
}
void HallSer::initGameSer(void)
{
    size_t index = 0;
    GameSer *gameSer = NULL;
    for(set<IpInfo>::iterator ip_it = ipInfoSet.begin();ip_it != ipInfoSet.end();++ip_it)
    {
        try
        {
            gameSer = new GameSer(&(*ip_it),index,this);
        }
        catch(...)
        {
            delete gameSer;
            gameSer = NULL;
            continue;
        }
        gameSerVec.push_back(gameSer);
        ++index;
    }
    if(gameSerVec.empty())
    {
        perror("HallSer::initGameSer error gameSerVec is empty");
        throw 1;
    }
}

void HallSer::init(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    listenerFd = 0;
    uid = 1;
    upperNum = 0;
    base = NULL;
}

void HallSer::runLoop(void)
{
    if(base)
    {
        perror("HallSer::runLoop error base is exist again");
        throw 1;
    }
    base = event_base_new();
    if(!base)
    {
        perror("HallSer::runLoop error base is NULL");
        throw 1;
    }
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip);
    
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("HallSer::runLoop error socket");
        throw 1;
    }
    listenerFd = fd;
    evutil_make_socket_nonblocking(listenerFd);
    if(bind(listenerFd,(sockaddr *)&sin,sizeof(sockaddr)) < 0)
    {
        perror("HallSer::runLoop error bind");
        throw 1;
    }
    if(listen(listenerFd,1024) < 0)
    {
        perror("HallSer::runLoop error listen");
        throw 1;
    }
    
    event *listen_event = event_new(base,listenerFd,EV_READ|EV_PERSIST,do_accept,this);
    event_add(listen_event, NULL);
    event_base_dispatch(base);
}

bool HallSer::check_connect(CONNECT_TYPE connectFd)
{
    map<CONNECT_TYPE,UID_TYPE>::iterator fd_it = fdUidMap.find(connectFd);
    return fd_it == fdUidMap.end();
}

int HallSer::find_empty_gameSer(void)
{
    size_t size = gameSerVec.size();
    for(size_t index = 0;index < size;++index)
    {
        GameSer *gameSer = gameSerVec[index];
        if(!gameSer || gameSer->isFull())
        {
            continue;
        }
        return index;
    }
    return -1;
}
bool HallSer::insert_connect(CONNECT_TYPE connectFd,INDEX_TYPE index)
{
    uidFdMap[uid] = connectFd;
    fdUidMap[connectFd] = uid;
    map<INDEX_TYPE,set<UID_TYPE> >::iterator index_it = indexUidMap.find(index);
    if(index_it == indexUidMap.end())
    {
        set<UID_TYPE> uidSet;
        uidSet.insert(uid);
        indexUidMap[index] = uidSet;
    }
    else
    {
        indexUidMap[index].insert(uid);
    }
    GameSer *gameSer = gameSerVec[index];
    gameSer->add_person();
    return true;
}

bool HallSer::accept_connect(CONNECT_TYPE connectFd)
{
    if(!check_connect(connectFd))
    {
        return false;
    }
    int index = find_empty_gameSer();
    if(index < 0)
    {
        return false;
    }
    return insert_connect(connectFd,index);
}
void do_accept(evutil_socket_t listenerFd,short event,void *arg)
{
    HallSer *hallSer = (HallSer *)arg;
    sockaddr sin;
    socklen_t len = sizeof(sin);
    int newfd = accept(listenerFd,(sockaddr *)&sin,&len);
    if(newfd < 0)
    {
        cout<<"warning newfd less 0"<<newfd<<endl;
        return;
    }
    else if(newfd > FD_SETSIZE)
    {
        cout<<"warning newfd more than FDSIZE"<<newfd<<endl;
        close(newfd);
    }
}
    

