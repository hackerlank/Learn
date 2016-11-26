#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <list>
#include <string>
#include <map>
#include <set>
#include<unistd.h>
#include <fstream>
#include<fcntl.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <sys/stat.h>
#include <execinfo.h>
#include <signal.h>
#include<math.h>

#include<iostream>
using namespace std;
#define RECV_END_FLAG 		0xffffFFFF
#define RECV_BEGIN_FLAG 	0x5E5E5E5E
#define ONE_RECV_MSG_LEN 	8192
#define RECV_MSG_QUE_LEN	1024
#define RECV_MSG_QUE_SIZE	1048576	//ONE_RECV_MSG_LEN * RECV_MSG_QUE_LEN

char logDir[64] = "//dayoxi//log_data";
// char logDir[64] = "log";
typedef struct recvLog_S
{
	int tail;
	int head;
	int size;
	char msgQue[RECV_MSG_QUE_LEN][ONE_RECV_MSG_LEN];
	recvLog_S()
	{
		head = 0;
		size = 0;
		tail = 0;
		memset(msgQue, 0, RECV_MSG_QUE_SIZE);
	}
	
	int push_back()
	{
		if ((tail + 1) % RECV_MSG_QUE_LEN == head)
		{
			return RECV_END_FLAG;
		}
		tail %= RECV_MSG_QUE_LEN;
		return tail++;
	}
	int pop_front()
	{
		if (head == tail)
		{
			return RECV_BEGIN_FLAG;
		}
		head %= RECV_MSG_QUE_LEN;
		return head++;
	}
} recvLog_T;

set<string> SrvDirs;
set<string> TimeDirs;
map<string, FILE*> path2files;
map<string, set<string> > SrvLogFiles; 

struct event_base *BasePrioEvent;
	struct event *write_log_file_event;
void event_cb(struct bufferevent *bev, short what, void *arg);
void accept_cb(evutil_socket_t listener, short ev, void *arg);
void read_cb(struct bufferevent *bev, void *arg);
void write_file_cb(evutil_socket_t listener, short ev, void *arg);

void help(char *srvName, int timeSec, int first, int second, char *src, FILE* &fp, char *saveItem);
void resolve(char *msg, char *srvName, int &timeSec, int &first, int &second, char *src);

recvLog_T recvMsg;
struct timeval writeTv;
//当前进程崩溃之前，存储数据函数

void dump(int value)
{
	map<string, FILE*>::iterator it = path2files.begin();
	for (it; it != path2files.end(); it++)
	{
		FILE *fp = it->second;
		fclose(fp);
	}
	path2files.clear();
	_exit(0); 
}

int main(int argc ,char** argv)
{
	if (argc < 3)
	{
		cout<<"args is too few!"<<endl;
		return -1;
	}
	
	memset(logDir, 0, sizeof logDir);
	strncpy(logDir, argv[2], strlen(argv[2]));
	cout<<"Bison show"<<logDir<<endl;
	int flag = mkdir(logDir, 0755);
	if (flag != 0)
	{
		printf("[Warnning]Create log DIR Failed!!\n");
		
		struct stat filestat;
		if(stat(logDir, &filestat) != 0 || !S_ISDIR(filestat.st_mode))
		{
			printf("Not Exist\n");
		return -1;
		}
		printf("The Dir is already exist!\n");
	}
	
    signal(SIGTERM, &dump); //kill 信号
	signal(SIGKILL, &dump);	//非友好kill发送
	signal(SIGINT, &dump);	//ctrl + c的处理
	signal(SIGPIPE, SIG_IGN);
	
	writeTv.tv_sec = 1;
	writeTv.tv_usec = 0;
    BasePrioEvent = event_base_new();
	int init_prio = event_base_priority_init(BasePrioEvent, 3);
	int port;
    port = atoi(argv[1]);                //初始化套接字
	
	evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event *listener_event;
    if (!BasePrioEvent)
	{
        return -1;
	}
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);
	//设置reuse
	int so_reuseaddr = 1;
    setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,sizeof(so_reuseaddr));
	
    if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
        perror("bind");
        return -1;
    } else
	{
        int size = sizeof(sin);
        getsockname(listener, (sockaddr*)&sin, (socklen_t *)&size);
	}

    if (listen(listener, 1024)<0) {
        perror("listen");
        return -1;
    }
	
	printf("SOCKET CREATE SUCCESS\n");
	
	if (argc > 3 && (!strcmp(argv[3], "-d") || !strcmp(argv[3], "-D")))
	{
		cout<<"You have given the argv with -d "<<endl;
		daemon(1, 0);
    }
	
	listener_event = event_new(BasePrioEvent, listener, EV_READ, accept_cb, (void *)listener_event);
	event_priority_set(listener_event, 0);
	event_assign(listener_event, BasePrioEvent, listener, EV_READ, accept_cb, (void*) listener_event);
	
	write_log_file_event =  event_new(BasePrioEvent, -1, EV_TIMEOUT, write_file_cb, NULL);
	event_priority_set(write_log_file_event, 2);
	event_assign(write_log_file_event, BasePrioEvent, -1, EV_TIMEOUT, write_file_cb, (void*)write_log_file_event);
	
	event_add(write_log_file_event, &writeTv);
	
    event_add(listener_event, NULL);
    event_base_dispatch(BasePrioEvent);
	
	return 0;
}

void write_file_cb(evutil_socket_t listener, short ev, void *arg)
{
	struct event *writeFileEvent = (struct event *)arg;
	// struct timeval tv;
	// gettimeofday(&tv, NULL);
	// struct tm *tmp = localtime(&tv.tv_sec);	
	// char nowTime[32];
	// sprintf(nowTime, "%d-%02d-%02d %02d:%02d:%02d:", tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	
	// ofstream o_file;
	// const char filename[]="log.txt";
	// o_file.open(filename, ios::app);
	
	// if (o_file.is_open())
	// {
		// int i = recvMsg.pop_front();
		// while (i != RECV_BEGIN_FLAG)
		// {
			// o_file<<nowTime<<recvMsg.msgQue[i]<<endl;
			// i = recvMsg.pop_front();
		// }
	// }
	// o_file.close();
	
	FILE *fp = NULL;
	char saveItem[1024] = {0};
	int first = 0, second = 0;
	int timeSec = 0;
	char srvName[256] = {0};
	char src[1024] = {0};
	int index = recvMsg.pop_front();
	while (index != RECV_BEGIN_FLAG)
	{
		memset(src, '\0', sizeof(src));
		memset(srvName, 0, sizeof (srvName));
		resolve(recvMsg.msgQue[index], srvName, timeSec, first, second, src);
		memset(saveItem, '\0', sizeof(saveItem));
		help(srvName, timeSec, first, second, src, fp, saveItem);
		if (fp == NULL)
		{
			break;
		}
		memset(recvMsg.msgQue[index], 0, sizeof (recvMsg.msgQue[index]));
		fwrite(saveItem, 1, strlen(saveItem), fp);
		// fwrite("\0\n", 1, 2, fp);
		fflush(fp);
		// fwrite("\n", 1, 1, fp);
		index = recvMsg.pop_front();
	}
	
	event_add(writeFileEvent, &writeTv);
}

void accept_cb(evutil_socket_t listener, short ev, void *arg)
{
    struct event *listener_event = (struct event *)arg;
    struct sockaddr_in ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr *)&ss, &slen);
	
//	event_assign(listener_event, BasePrioEvent, listener, EV_READ, accept_cb, (void *)listener_event);

    /*XXX check it */
    event_add(listener_event, NULL);

    if (!BasePrioEvent)
    {
        cout << "BisonWarn: no BasePrioEvent" << endl;
    }
    struct bufferevent *bufEvent = bufferevent_socket_new (BasePrioEvent, fd, 0);
	bufferevent_priority_set(bufEvent, 0);
    if (fd < 0)
    {
        perror("accept");
    } else if (fd > FD_SETSIZE)
    {
        close(fd);
    } else
    {
		cout<<"One Game Server Have Connected To This Log Server And ConFd Is "<<fd<<endl;
		int flags = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);

		bufferevent_setwatermark(bufEvent, EV_WRITE, 0, 0);
        bufferevent_setcb(bufEvent, read_cb, NULL, event_cb, (void*)fd);
		bufferevent_enable(bufEvent, EV_READ | EV_WRITE);
    }
}

void event_cb(struct bufferevent *bev, short what, void *arg)
{
	cout << "event_cd called" << endl;
	int fd = (long)arg;	
	bufferevent_disable(bev, EV_READ | EV_WRITE);
	bufferevent_free(bev);
	bev=NULL;
	close(fd); 	
}

void read_cb(struct bufferevent *bev, void *arg)
//void read_cb(int fd, short event, void *arg)
{
	// puts("begin read!!!!!!!!!!!!!!!!!!!!");
	// int index = recvMsg.push_back();
	// if (index == RECV_END_FLAG)
	// {
		// event_active(write_log_file_event, -1, EV_TIMEOUT);
		// index = recvMsg.push_back();
	// }
	// int len = bufferevent_read(bev, &recvMsg.msgQue[index], 1024);
	// if (len > 0)
	// {
		// recvMsg.msgQue[index][len] = '\0';
		// cout<<"[BisonShow] recv one Msg is [ "<<recvMsg.msgQue[index]<<" ]"<<endl;
	// }
	
	unsigned char *mem;
    struct evbuffer *in = bufferevent_get_input(bev);

    mem = evbuffer_pullup(in, 6);
    int cmdlen = 0;
    while (evbuffer_get_length(in) >= 6)
    {
        mem = evbuffer_pullup(in, 6);
        if (*mem != 0x5E)
        {
            evbuffer_drain(in, 1);
			cout<<"log Comm check not OK and first is "<<(int)(*mem)<<endl;
            continue;
        }
        if (*(mem + 1) != 0x5E)
        {
			cout<<"log Comm check not OK and second is "<<(int)*(mem + 1)<<endl;
            evbuffer_drain(in, 2);
            continue;
        }
       
        // memcpy(&cmdlen, mem + 2, 4);
		cmdlen = (unsigned char)*(mem + 5)<<24
				| (unsigned char)*(mem + 4)<<16
				| (unsigned char)*(mem + 3)<<8
				| (unsigned char)*(mem + 2);
        // cmdlen = ntohl(cmdlen);
		cout<<"cmdlen is :"<<cmdlen<<endl;
		// cout<<""<<endl;
        if ((cmdlen < 0) || (cmdlen > 1024))
        {
            evbuffer_drain(in, 6);
			cout<<"the log msg long is not valid!"<<endl;
            continue;
        }

        if (evbuffer_get_length(in) < cmdlen + 6)
        {
			cout<<"Not len enough for one log"<<endl;
            break;
        }
		
		int index = recvMsg.push_back();
		if (index == RECV_END_FLAG)
		{
			event_active(write_log_file_event, -1, EV_TIMEOUT);
			index = recvMsg.push_back();
		}
		
		memset(recvMsg.msgQue[index], 0, sizeof(recvMsg.msgQue[index]));
		evbuffer_drain(in, 6);
        evbuffer_remove(in, recvMsg.msgQue[index], cmdlen);
		recvMsg.msgQue[index][cmdlen] = '\0';
		cout<<"[BisonShow] recv one Msg is [ "<<recvMsg.msgQue[index]<<" ]"<<endl;
	}
	// char buff[4096];
    // int len;

	// int fd = (long)arg;
    // len = bufferevent_read(bev, &buff, 4096);

    // if (len > 0)
    // {
        // buff[len] = '\0';
			
		// 将时间（秒）转换成本地格式，如：2012-09-22 15:22:17
		// struct timeval tv;
		// gettimeofday(&tv, NULL);
		// struct tm *tmp = localtime(&tv.tv_sec);	
		// char nowTime[32];
		// sprintf(nowTime, "%d-%02d-%02d %02d:%02d:%02d:", tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
		// printf("%s\n", buff);
		
		// ofstream o_file;
		// const char filename[]="log.txt";
		// o_file.open(filename, ios::app);
		// if (o_file.is_open())
		// {
			// o_file<<nowTime<<buff<<endl;
		// }
		// o_file.close();
	// }
}

void help(char *srvName, int timeSec, int first, int second, char *src, FILE* &fp, char *saveItem)
{
	char temp[256] = {0}, timeStr[256] = {0},
		 timeDirStr[256] = {0}, fileName[256] = {0},
		 srvDirStr[256] = {0};
		 
	struct timeval tv;
	tv.tv_sec = timeSec;
	struct tm *tmp = localtime(&tv.tv_sec);
	
	sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d", tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	sprintf(saveItem, "%s,%s\n", timeStr, src);
	sprintf(srvDirStr, "%s//%s", logDir, srvName);
	sprintf(timeDirStr, "%s//%d%02d%02d", srvDirStr, tmp->tm_year + 1900, tmp->tm_mon + 1,tmp->tm_mday);
	sprintf(fileName, "%s//%02d_%02d.txt", timeDirStr, first, second);
	cout<<"saveItem is:"<<saveItem<<endl;
	cout<<"srvDirStr is "<<srvDirStr<<endl;
	cout<<"timeDirStr is:"<<timeDirStr<<endl;
	cout<<"fileName is:"<<fileName<<endl;
	
	struct stat filestat;
	if (SrvDirs.find(srvDirStr) == SrvDirs.end())
	{
		int flag = mkdir(srvDirStr, 0755);
		if (flag != 0)
		{
			printf("[Warnning] Create DIR Failed!!");
			if(stat(srvDirStr, &filestat) != 0 || !S_ISDIR(filestat.st_mode))
			{
				printf("[Error] Not Exist\n");
				return;
			} else {
				SrvDirs.insert(srvDirStr);
			}
			
		} else {
			SrvDirs.insert(srvDirStr);
		}
	}
	
	if (TimeDirs.find(timeDirStr) == TimeDirs.end())
	{
		int flag = mkdir(timeDirStr, 0755);
		if (flag != 0)
		{
			printf("[Warnning]Create DIR Failed!!");
			if(stat(timeDirStr, &filestat) != 0 || !S_ISDIR(filestat.st_mode))
			{
				printf("[Error] Not Exist\n");
				return;
			} else {
				TimeDirs.insert(timeDirStr);
			}
		} else {
			TimeDirs.insert(timeDirStr);
			map<string, set<string> >::iterator it_allFiles = SrvLogFiles.find(srvDirStr);
			if (it_allFiles != SrvLogFiles.end())
			{
				set<string> srvFiles = it_allFiles->second;
				if (srvFiles.size() != 0)
				{
					set<string>::iterator it_oneFile;
					for (it_oneFile = srvFiles.begin(); it_oneFile != srvFiles.end(); it_oneFile++)
					{
						map<string, FILE*>::iterator it_oldFile = path2files.find(*it_oneFile);
						if (it_oldFile != path2files.end())
						{
							FILE* pf = it_oldFile->second;
							if (pf != NULL)
							{
								fclose(pf);
							}
							path2files.erase(*it_oneFile);
						}
					}
				}
				
			}
		}
	}
	
	map<string, FILE*>::iterator it_file = path2files.find(fileName);
	if (it_file == path2files.end())
	{
		fp = fopen(fileName, "a+");
		if (fp == NULL)
		{
			printf("[Warnning]Create File Failed!!");
			return;
		}
		else {
			path2files.insert(pair<string, FILE*>(fileName, fp));
			map<string, set<string> >::iterator it_allFiles = SrvLogFiles.find(srvDirStr);
			if (it_allFiles != SrvLogFiles.end())
			{
				set<string> *srvFiles = &it_allFiles->second;
				srvFiles->insert(fileName);
			}
		}
	} else {
		fp = it_file->second;
	}
	if (fp == NULL)
	{
		puts("3333333333333333333333333333333333333");
		puts("3333333333333333333333333333333333333");
	}
}

void resolve(char *msg, char *srvName, int &timeSec, int &first, int &second, char *src)
{
	char *start = msg;
	char *search = msg;
	char timeStr[32] = {0}, firstStr[32] = {0}, secondStr[32] = {0};
	
	for (;*search != ','; search++);
	strncpy(firstStr, start, search - start);
	first = atoi(firstStr);
	
	start = ++search;
	for (;*search != ','; search++);
	strncpy(secondStr, start, search - start);
	second = atoi(secondStr);
	
	start = ++search;
	for (;*search != ','; search++);
	strncpy(srvName, start, search - start);
	
	start = ++search;
	for (;*search != ','; search++);
	strncpy(timeStr, start, search - start);
	timeSec = atoi(timeStr);
	
	cout<<"first:"<<first<<" second:"<<second<<" srvName:"<<srvName<<endl;
	
	start = ++search;
	strncpy(src, start, strlen(start) + 1);
	cout<<"msg is "<<src<<endl;
	
}