/*
    文件类型：实现文件
    文件名称：command_other_function_all_over.cpp
    文件作用：实现一些在游戏各个部分都需要要到的函数的实现
*/
#include<math.h>
#include <sstream>
#include"command_other_function_all_over.h"
#include"pick.h"
#include"hero.h"
#include"map_inform.h"      
#include"pet_box.h"  
#include"wagon.h"
#include"takeGoods.h"
#include"bottle.h"
#include"pet.h"
#include<map> 
#include<string>
#include"cpyLimit.h"
#include"boxAsist.h"
#include"my_time.h"
#include"cpyAsist.h"
#include"monsterTool.h"
#include"statuaryHero.h"
#include"teamAsist.h"
#include"camp_war_reward.h"
extern int TileWidth;
extern int serverOpenTime;
extern int TileHeight;
/**	与套接字描述符绑定的消息接收队列 **/
extern map<int, Message_Receive>   message_queue;
extern int cdKeySrvFd;				//cdkey端口
extern int sock_fd;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<int, Role*> fd_to_pRole;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Pick*> goods_to_hero;
extern map<string,Pet*>id_to_activePet;     //add by jolly 2012.8.30
extern map<string,Wagon*> wagonInstMap;
extern struct ev_loop *loops;
extern struct timeval myTime;
extern char g_out_buf[20480];
extern map<string,Equipment*>dropEquipMent;
extern char server_name[10];
extern map<string,MonsterTool*> toolMonsterIdToInst;     //道具刷出的怪管理容器
using namespace std;
/*
完成内容：发送玩家九宫格内的其他玩家消息
完成时间：2012.8.23
完成人：Evan
*/

/*像素坐标点转化为逻辑坐标点*/
Point MapExchangeLogical(Point pointOfmap)
{
    Point Logicalpoint;
    Logicalpoint._x=floor(0.5*((pointOfmap._y<<1)+pointOfmap._x)/(TileWidth>>1));
    Logicalpoint._y=floor(0.5*((pointOfmap._y <<1)-pointOfmap._x)/(TileWidth>>1));
    return Logicalpoint;

}

/*逻辑坐标点转化为像素坐标点*/
Point LogicalExchangeMap(Point pointOflogical)
{
    Point Mappoint;
    Mappoint._x =(TileWidth >> 1) * (pointOflogical._x-pointOflogical._y);
    Mappoint._y =(TileHeight>> 1) * (pointOflogical._x+pointOflogical._y) + TileHeight/2;
    return Mappoint;
}

/*
    int类型转换为string
    参数：value  （int类型）
    获取的值：string类型
*/
string intTostring(int value)
{
    string a = ",";
    stringstream ss ;
    string s ;
    ss << value;
    ss >> s;
    return a + s;
}

string itos(int i)
{
    stringstream ss ;
    string s ;
    ss << i;
    ss >> s;
    return s;
}                                        
/*
    int类型转换为string
    参数：value  （char*类型）
    获取的值：string类型
*/
string charTostring(char *value)
{
    string s ;
    string a = ",";
    s.insert(0,value);
    return a + s ;

}    

bool send_msg(int fd, string &msg_body)
{
    if(fd <= 0 || msg_body.empty())
	{
        cout<<"msg_body is empty"<<endl;
		return false;
    }

	map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
	if(iter == message_queue.end())
	{
		cout<<fd<<":this client have no Message object in message_queue"<<endl;
		return false;
	}
	Message_Receive *_message_receive = &(iter->second);
	if(_message_receive->io_watcher == NULL)
		return false;		
 	char msg_flag;
	msg_flag = 249;
	bufferevent_write(_message_receive->io_watcher, (void *)&msg_flag, 1); 
	int msg_len = htonl(msg_body.size());
	bufferevent_write(_message_receive->io_watcher, (void *)&msg_len, 4); 
	bufferevent_write(_message_receive->io_watcher, (void*)(msg_body.c_str()), msg_body.size());
	bufferevent_flush(_message_receive->io_watcher, EV_WRITE , BEV_FINISHED );
	// memset(g_out_buf, 0, 20480);
}


bool send_msg(int fd, char *msg_body)
{
    if(fd <= 0 || msg_body == NULL || strlen(msg_body) == 0)
	{
		cout<<"msg_body is NULL"<<endl;
        return false;
    }

	map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
	if(iter == message_queue.end())
	{
		cout<<fd<<":this client have no Message object in message_queue"<<endl;
		return false;
	}
	Message_Receive *_message_receive = &(iter->second);
	if(_message_receive->io_watcher == NULL)
		return false;
		
 	char msg_flag;
	msg_flag = 249;

	bufferevent_write(_message_receive->io_watcher, (void *)&msg_flag, 1); 
	int msg_len = htonl(strlen(msg_body));
	bufferevent_write(_message_receive->io_watcher, (void *)&msg_len, 4); 
	bufferevent_write(_message_receive->io_watcher, msg_body, strlen(msg_body));
	bufferevent_flush(_message_receive->io_watcher, EV_WRITE , BEV_FINISHED );
	// memset(g_out_buf, 0, 20480);
}


bool send_msg(int fd, const char *msg_body)
{
    if(fd <= 0 || msg_body == NULL || strlen(msg_body) == 0)
	{
		cout<<"msg_body is NULL"<<endl;
        return false;
    }

	map<int, Message_Receive>::iterator iter =  message_queue.find(fd);
	if(iter == message_queue.end())
	{
		cout<<fd<<":this client have no Message object in message_queue"<<endl;
		return false;
	}
	Message_Receive *_message_receive = &(iter->second);
	if(_message_receive->io_watcher == NULL)
		return false;
		
 	char msg_flag;
	msg_flag = 249;

	bufferevent_write(_message_receive->io_watcher, (void *)&msg_flag, 1); 
	int msg_len = htonl(strlen(msg_body));
	bufferevent_write(_message_receive->io_watcher, (void *)&msg_len, 4); 
	bufferevent_write(_message_receive->io_watcher, msg_body, strlen(msg_body));
	bufferevent_flush(_message_receive->io_watcher, EV_WRITE , BEV_FINISHED );
	// memset(g_out_buf, 0, 20480);
}


bool ComFun(const HatVal &hat1,const HatVal &hat2)
{
    return hat1.value > hat2.value;
}

int HatFun(list<HatVal> &hat1,list<HatVal> &hat2,char *perHerId,char *goodsOwner,\
		   char *monId,bool isCopy)
{
    int flag,flgGogs;   
    Hero* hero;
    flag = -1;         //返回值	
    flgGogs = -1;     //物品归属标记值
    bool delPet;
    list<HatVal>::iterator hat1_it;   //hat1迭代器，新
    list<HatVal>::iterator hat2_it;   //hat2迭代器，旧
    hero = NULL;
    delPet = false;

    /*如果目标为空*/
    if(perHerId == NULL)
    {
        flag = 0;
    }

    /*如果物品有归属*/
    if(strlen(goodsOwner) == 0)
    {
        flgGogs = 0;
    }	

    /*遍历取交集*/
    for(hat2_it = hat2.begin();hat2_it != hat2.end();hat2_it++)
    {
        for(hat1_it = hat1.begin();hat1_it != hat1.end();hat1_it++)
        {
            // cout<<"newEnmistyId:"<<(*hat1_it).id<<endl;
            /*如果目标不为空，且目标还在新的仇恨范围内*/
            if(flag != 0 && strcmp((*hat1_it).id,perHerId) == 0)
            {
                flag = 1;               
            }
            /*如果此玩家原来在仇恨列表里，且现在又产生新的仇恨值了*/
            if(strcmp((*hat1_it).id,(*hat2_it).id) == 0)
            {
                delPet = true;
                /*取大者（注意：是经过叠加后的）*/
                if((*hat2_it).value > (*hat1_it).value)
                {
                    (*hat1_it).value = (*hat2_it).value;                    
                }
            }
            /*如果物品有归属*/
            if(flgGogs == -1)
            {
                /*如果此物品原来的归属还在仇恨范围内*/
                if(strcmp(goodsOwner,(*hat1_it).id) == 0)
                {
                    flgGogs = 1;
                }
            }
        }
		if(!delPet && isCopy)
        {
			hat1.insert(hat1.begin(),*hat2_it);
        }
        else if(!delPet)
        {
            hero = heroid_to_hero((*hat2_it).id);
            if(hero != NULL)
            {
                hero->deleteAttList(monId);
            }
        }

        delPet = false;         
    }
    /*对仇恨列表对仇恨值进行从大到小的排序*/
    hat1.sort(ComFun);

    /*如果此物品原来的归属不在仇恨范围内*/
    if(flgGogs != 1)
    {
		memset(goodsOwner,'\0',IDL + 1);
    }

    return flag;
}

/*获得被攻击玩家实例指针*/
Hero* heroid_to_hero(string heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

//函数功能：获取uuid，实现: Cookie				
char *cid()
{
    uuid_rc_t e;                                    //调用函数返回信息
    uuid_t *uuid;                                   //uuid object
    uuid_create(&uuid);                             //创建 uuid object
    unsigned int mode=(1<<0);                       //mode 是选择uuid的make方法
    e=uuid_make(uuid,mode);                         //make uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }
    size_t data_len=37;                             //接收 uuid 数据的字串长度
    char *data=(char *)malloc(data_len);            //定义接收 uuid 数据的字串
    uuid_fmt_t fmt=UUID_FMT_STR;                    //选择 uuid 接受数据形式为字串
    e=uuid_export(uuid,fmt,&data,&data_len);        //uuid 导出数据函数
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }
    e=uuid_destroy(uuid);                           //销毁 uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }

    return data;
}       


//函数功能：获取uuid，实现: Cookie				
char *cidOtherWay()
{
    uuid_rc_t e;                                    //调用函数返回信息
    uuid_t *uuid;                                   //uuid object
    uuid_create(&uuid);                             //创建 uuid object
    unsigned int mode=(1<<0);                       //mode 是选择uuid的make方法
    e=uuid_make(uuid,mode);                         //make uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }
    size_t data_len=16;                             //接收 uuid 数据的字串长度
    char *data=(char *)malloc(data_len);            //定义接收 uuid 数据的字串
    uuid_fmt_t fmt=UUID_FMT_BIN;                    //选择 uuid 接受数据形式为字串
    e=uuid_export(uuid,fmt,&data,&data_len);        //uuid 导出数据函数
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }
    e=uuid_destroy(uuid);                           //销毁 uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }

    return data;
}    

/*函数功能：获取uuid*/				
bool cidOtherWay(char *data,int length)
{
    uuid_rc_t e;                                    //调用函数返回信息
    uuid_t *uuid;                                   //uuid object
    uuid_create(&uuid);                             //创建 uuid object
    unsigned int mode=(1<<0);                       //mode 是选择uuid的make方法
    e=uuid_make(uuid,mode);                         //make uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return NULL;
    }
    size_t data_len=16;        
	if(data_len > length)
	{
		cout<<"uuId the length is error:"<<endl;
		return false;
	}	
    
    uuid_fmt_t fmt=UUID_FMT_BIN;                    //选择 uuid 接受数据形式为字串
    e=uuid_export(uuid,fmt,&data,&data_len);        //uuid 导出数据函数
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return false;
    }
    e=uuid_destroy(uuid);                           //销毁 uuid
    if(e!=UUID_RC_OK)
    {
        cout<<uuid_error(e)<<endl;
        return false;
    }
	return true;
}    

  
/*在id后面追加一个num，如果位数不够byteSum,则补零*/
void appendNum(char *id,int num,int byteSum)
{
    int i;
    int _num;
	
	if(id == NULL)
	{
		return;
	}
	
    stringstream ss ;
    string s ;

    for(i = 0,_num = num;_num > 0;i++)
    {
        _num /= 10;
    }

    while(i < byteSum)
    {
		sprintf(id + strlen(id),"%d",0);
        i++;
    }
    if(num != 0)
    {
		sprintf(id + strlen(id),"%d",num);
    }
}


void enter_scenes(Hero *myHero, Map_Inform *map_now,int entOlder)
{	
	
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char mapRealId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char mapRealIdStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char *mapId,*wagonId; 
	Wagon *wagon;            
    Nbox *box;     
    Pet *myPet;
	Point entPt;  	
	
	if(myHero == NULL || map_now == NULL)
	{
		return;
	}
	
	mapId = map_now->getMapId();
	StyObj obj(myHero->getIdentity(),HERO_STYLE_TYPE);
	
    /*副本地图处理*/
    if(entOlder < 2)
    {
        /*下一层*/
        if(entOlder > 0)
        {
            entPt = map_now->getEntPt();
        }
        /*上一层*/
        else
        {
            entPt = map_now->getOutPt();
        }
		
		cout<<"mapId:"<<mapId<<endl;
		strncpy(mapRealId,mapId,strlen(mapId) - 13);
		cout<<"mapRealId:"<<mapRealId<<endl;
		mapId = mapRealId; 
    }

    /*非副本地图处理*/
    else
    {
		entPt = myHero->getBeforePiexPt();		
    }
    /*开始生成切换场景信息*/
	sprintf(chageSre,"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,CHANGE_SCENE,SUCCESS,mapId,\
			entPt._x,entPt._y,map_now->getWarType(),map_now->getChangePkType(),\
			map_now->getMapType());
    send_msg(myHero->getFd(), chageSre); 
	
    myHero->setMap(map_now);
	
    myHero->setLocation(entPt); 	
    

    /*将heroId插入地图信息容器中管理*/
    map_now->insertID(obj);  

    map_now->inPutFd(myHero->getFd());                
	
	
	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->heroEnter(myHero,1);	 
	
	wagonId = myHero->memHero->wagonId;
	
    wagon = getInstWgon(wagonId);  
	
    if(wagon != NULL)
    {
        wagon->enter_scene();
    }
	
	if ( myHero->getPetBox()==NULL)
	{
		return;
	}
    myPet = myHero->getPetBox()->getActivePet();    
    if(myPet != NULL)
    {
        myPet->enter_scene(myHero);
    }	
    return; 
}       




void quit_scene(Hero *myHero, Map_Inform *map_now)             //退出游戏场景
{  
	char *wagonId;
	Wagon *wagon;
	Pet *myPet;
    Nbox *box;    
    

    if(map_now == NULL || myHero == NULL)
    {
        return;
    }
	
	StyObj obj(myHero->getIdentity(),HERO_STYLE_TYPE);
	
	box = map_now->getBox();                     

	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->heroEnter(myHero,2);

    /*获得当前下线角色所在点周围的id集合后，将自己的Id从地图信息中删除*/
    map_now->deleteID(obj);         

    map_now->delFd(myHero->getFd());  

    /*马车退出*/
    wagonId = myHero->memHero->wagonId;
    wagon = getInstWgon(wagonId);
    if(wagon != NULL)
    {
        wagon->quit_scene();        
    }
    if(myHero->getPetBox())
	{
        myPet = myHero->getPetBox()->getActivePet();
        if(myPet != NULL)
        {
            myPet->quit_scene(myHero);
        }
    }
}

Hero* fd_to_hero()
{
    map<int, Role*>::iterator role_it;
    Hero *hero;
    Role *role;
    role_it = fd_to_pRole.find(sock_fd);  
    if(role_it == fd_to_pRole.end())
    {
        cout<<"According to sock_fd can't find the Role (in all_over)"<<endl;
        return NULL;
    } else
    {
        role = role_it->second;
        hero = role->getActive_hero();
        return hero;
    }

}

/*
  函数：bool hasBarrier(Point ptStart,Point ptEnd,Map_Inform* mapInfo)
  作用：判断一张地图里俩个点直线之间是否有障碍点
  参数：ptStart,直线起点(像素点)；
        ptEnd,直线终点（像素点）；
        mapInfo,地图信息；
返回值：false 没有障碍点；
        true 有障碍点；
出错处理：如果转换后的逻辑点不符合要求，默认为此点是障碍点。
*/ //added by xhm;
bool 
hasBarrier(Point _ptStart,Point _ptEnd,Map_Inform* mapInfo)
{
/*地图最大逻辑点的横坐标和纵坐标*/
    int row = mapInfo->getRow(); 
    int col = mapInfo->getCol();

/*地图的像素点转换成为逻辑点*/
    Point ptStart = MapExchangeLogical( _ptStart);
    ptStart._y += mapInfo->getBaseDigst();
    Point ptEnd = MapExchangeLogical(_ptEnd);
    ptEnd._y += mapInfo->getBaseDigst();

/*获取地图障碍点数组*/
    vector< vector<int> > *barrier = &mapInfo->getMapHinder(); 

    /*如果起点和目标点是同一点，返回无障碍点*/
    if(ptStart._x==ptEnd._x && ptStart._y == ptEnd._y)
    {
        return false;
    }

    bool negativeFlag=false;//值的变化方向，值得是递增还是递减，true 递减，false 递增；
    int x_offset = ((ptStart._x-ptEnd._x) >= 0 ? (ptStart._x-ptEnd._x):(ptEnd._x-ptStart._x));
    int y_offset = ((ptStart._y-ptEnd._y) >= 0 ? (ptStart._y-ptEnd._y):(ptEnd._y-ptStart._y));
    bool x_direction=(x_offset >= y_offset ?true:false);

    if(x_direction)            //x方向；
    {
		/*交换起始点，把x值小的一点作为起始点*/
        if(ptStart._x-ptEnd._x > 0)
        {
            Point ptTemp = ptStart;
            ptStart = ptEnd;
            ptEnd = ptTemp;
        }
        if(ptStart._y-ptEnd._y > 0)
        {
            negativeFlag=true; //Y数据加上负数标示；
        }

        if(!negativeFlag)
        {
            if(ptStart._x < 0 || ptStart._x >= row || ptStart._y+1 < 0 || ptStart._y+1 >=col || 1==(*barrier)[ptStart._x][ptStart._y+1] )
                return true;
        } else
        {
            if(ptStart._x < 0 || ptStart._x >= row || ptStart._y < 0 || ptStart._y >= col || 1==(*barrier)[ptStart._x][ptStart._y])
                return true;
        }
        for(int _row = 1;_row < x_offset;_row++)
        {
            int y;
            if(negativeFlag)
            {
                y = -_row*(y_offset/x_offset);
            } else
            {
                y = _row*(y_offset/x_offset)+1;
            }
            if(ptStart._x+_row-1 < 0 || ptStart._x+_row-1 >= row || ptStart._y+y < 0 || ptStart._y+y >= col || ptStart._x+_row < 0 || ptStart._x+_row >= row ||
               1==(*barrier)[ptStart._x+_row-1][ptStart._y+y] || 1==(*barrier)[ptStart._x+_row][ptStart._y+y])
                return true;
        }
    } else //Y方向
    {
		/*交换起始点，把y值小的一点作为起始点*/
        if(ptStart._y-ptEnd._y > 0)
        {
            Point ptTemp = ptStart;
            ptStart = ptEnd;
            ptEnd = ptTemp;
        }
        if(ptStart._x-ptEnd._x > 0)
        {
            negativeFlag=true; //x数据加上负数标示；
        }

        for(int _row = 1;_row < y_offset;_row++)
        {
            int x;
            if(negativeFlag)
                x = -_row*(x_offset/y_offset);
            else
                x = _row*(x_offset/y_offset);
            if(ptStart._x+x-1 < 0 || ptStart._x+x-1 >= row || ptStart._y+_row < 0 || ptStart._y+_row >= col || ptStart._x+x < 0 || ptStart._x+x >= row ||
               1==(*barrier)[ptStart._x+x-1][ptStart._y+_row] || 1==(*barrier)[ptStart._x+x][ptStart._y+_row])
                return true;
        }

    }

    return false;
}


/*
  函数：bool hasBarrier(Point ptStart,Point ptEnd,Map_Inform* mapInfo)
  作用：判断一张地图里俩个点直线之间是否有障碍点
  参数：ptStart,直线起点(像素点)；
        ptEnd,直线终点（像素点）；
        mapInfo,地图信息；
返回值：false 没有障碍点；
        true 有障碍点；
出错处理：如果转换后的逻辑点不符合要求，默认为此点是障碍点。
*/ //added by xhm;
bool 
has_barrier(Point _ptStart,Point _ptEnd,Map_Inform* mapInfo)
{
	/*地图最大逻辑点的横坐标和纵坐标*/
    int row = mapInfo->getRow(); 
    int col = mapInfo->getCol();

	/*地图的像素点转换成为逻辑点*/
    Point ptStart = MapExchangeLogical( _ptStart);
    ptStart._y += mapInfo->getBaseDigst();
    Point ptEnd = MapExchangeLogical(_ptEnd);
    ptEnd._y += mapInfo->getBaseDigst();


	
	/*获取地图障碍点数组*/
    vector< vector<int> > *barrier = &mapInfo->getMapHinder(); 

    /*如果起点和目标点是同一点，返回无障碍点*/
    if(ptStart._x==ptEnd._x && ptStart._y == ptEnd._y)
    {
		cout<<"[XHM MSG] ptStart._x==ptEnd._x && ptStart._y == ptEnd._y"<<endl;
        return false;
    }

	/*转换大小点，永远x 坐标从小变大*/
    if(ptEnd._x < ptStart._x)
	{
		Point temp_point;
		temp_point = ptEnd;
		ptEnd = ptStart;
		ptStart = temp_point;
	}

	cout<<"[XHM MSG] ptStart._x:"<<ptStart._x<<"ptStart._y:"<<ptStart._y<<"ptEnd._x:"<<ptEnd._x<<"ptEnd._y:"<<ptEnd._y<<endl;	
	
	bool negativeFlag=false;
    if(ptStart._y-ptEnd._y > 0)
    {
        negativeFlag=true; //Y数据加上负数标示；
    }
	
    int x_offset = ptEnd._x-ptStart._x;
    int y_offset = ((ptStart._y-ptEnd._y) >= 0 ? (ptStart._y-ptEnd._y):(ptEnd._y-ptStart._y));

	
	
	
	int y=0;
	int x=0;
	int test_x=0;
	int test_y=0;	
	
	if(x_offset == 0)//如果角度是90度
	{
		int add_size = 0;
		int row = 0;
		int offset = 0;
		if(negativeFlag)
		{
			add_size = -1;
			row = 1;
			offset = y_offset;
		}else{
			add_size = 1;
			row = 0;
			offset = y_offset - 1;			
		}
		
		test_x = ptStart._x;
		int temp = ptStart._x - 1;
		if(temp < 0)
			temp = 0;
		
		for(; row <= offset;row ++)
		{
			y = ptStart._y+row*add_size;
			if(y < 0)
				y = 0;
				
			//测试点一
			if(1==(*barrier)[test_x][y] || 1==(*barrier)[temp][y])
			{
				cout<<"x_offset == 0"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<y<<"] :"<<(*barrier)[test_x][y]<<endl;
				cout<<"[XHM MSG](*barrier)["<<temp<<"]["<<y<<"] :"<<(*barrier)[test_x][y]<<endl;
				return true;
			}
		}
		
		return false;
	}
	
	if(y_offset == 0)//如果角度是0度
	{
		y = ptStart._y - 1;	
		if(y < 0)
			y = 0;
		
		for(int row = 0; row < y_offset;row ++)
		{
			//测试点一
			test_x = ptStart._x + row;
			if(test_x < 0)
				test_x = 0;
			
			if(1==(*barrier)[test_x][y] || 1==(*barrier)[test_x][ptStart._y])
			{
				cout<<"x_offset == 0"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<y<<"] :"<<(*barrier)[test_x][y]<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<ptStart._y<<"] :"<<(*barrier)[test_x][ptStart._y]<<endl;
				return true;
			}
		}
		
		return false;
	}
	
	float slope = (y_offset/x_offset) + 0.27;	//增加斜率；
	
	//如果第一格是障碍点，直接返回；
	if(negativeFlag)
		y=ptStart._y - 1;
	else
		y=ptStart._y;
	
	if(y < 0)
		y = 0;
	
	if(1==(*barrier)[ptStart._x][y])
	{
		cout<<"x1==(*barrier)[ptStart._x][y]"<<endl;
		cout<<"[XHM MSG](*barrier)["<<ptStart._x<<"]["<<y<<"] :"<<(*barrier)[ptStart._x][y]<<endl;	
		return true;
	}

    if(negativeFlag)
	{
		for(int _row = 1;_row < x_offset;_row++)
		{
			y=_row*slope+ ptStart._y-1;
			x = ptStart._x+_row;
			
			//测试点一
			test_y = y;
			test_x = x;
			if(test_y < 0)
				test_y = 0;
			if(test_x < 0)
				test_x = 0;
			if(1==(*barrier)[test_x][test_y])
			{
				cout<<"########111111111"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
				return true;
			}
				
			//测试点二
			test_x =x-1;
			test_y = y;
			if(test_y < 0)
				test_y = 0;
			if(test_x< 0)
				test_x = 0;
			if(1==(*barrier)[test_x][test_y])
			{
				cout<<"########2222222"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
				return true;
			}
				
			//测试点三
			test_x =x;
			test_y = y-1;
			if(test_y < 0)
				test_y = 0;
			if(test_x< 0)
				test_x = 0;
			if(1==(*barrier)[test_x][test_y])
			{
				cout<<"########3333333333"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
				return true;
			}
		}
			return false;
    }else{
		for(int _row = 1;_row < x_offset;_row++)
		{	
			y=_row*slope +ptStart._y + 0.5;
			x = ptStart._x+_row;
			//测试点一
			test_y = y-1;
			test_x = x;
			if(test_y < 0)
				test_y = 0;
			if(test_x < 0)
				test_x = 0;
			if(1==(*barrier)[test_x][test_y])
			{
				cout<<"!!!!!!!!!!11111111"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
				return true;
			}
				
			//测试点二
			test_x =x - 1;
			test_y = y - 1;
			if(test_y < 0)
				test_y = 0;
			if(test_x< 0)
				test_x = 0;
			if(1==(*barrier)[test_x][test_y])
			{
				cout<<"!!!!!!!!!!222222"<<endl;
				cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
				return true;
			}
				
			//测试点三
			if(_row == x_offset)
			{
				test_x =x;
				test_y = y;
				if(test_y < 0)
					test_y = 0;
				if(test_x< 0)
					test_x = 0;
				if(1==(*barrier)[test_x][test_y])
				{
					cout<<"!!!!!!!!!!333333333"<<endl;
					cout<<"[XHM MSG](*barrier)["<<test_x<<"]["<<test_y<<"] :"<<(*barrier)[test_x][test_y]<<endl;	
					return true;
				}
			}				
		}
		return false;
	}
}


/*
* author:tory
* 参数：@ ptStart,直线起点(像素点)
        @ ptEnd,直线终点（像素点）
		@ v 移动速度
		@ t 时间
        @ mapInfo,地图信息；
* 返回值：调用对象经过时间t,以速度v移动到的像素点
* 出错处理：如果传入数据出错，则返回起始点；如果经过时间t后的移动距离大于起始点到终点的距离，则返回终点
*/ 
Point getCurrenPt(Point _ptStart, Point _ptEnd, int v, int t, Map_Inform* mapInfo)
{
	int mapWidth = mapInfo->getWidth();		//获得地图宽度（像素）
	int mapHeight = mapInfo->getHeight();	//获得地图高度（像素）
	if(_ptStart._x < 0 || _ptStart._x > mapWidth || _ptEnd._x < 0 || _ptEnd._x > mapWidth)
		return _ptStart;
	if(_ptStart._y < 0 || _ptStart._y > mapHeight || _ptEnd._y < 0 || _ptEnd._y > mapHeight)	
		return _ptStart;
		
	unsigned int absX = (_ptStart._x - _ptEnd._x)>0 ? (_ptStart._x - _ptEnd._x) : (_ptEnd._x - _ptStart._x);
	unsigned int absY = (_ptStart._y - _ptEnd._y)>0 ? (_ptStart._y - _ptEnd._y) : (_ptEnd._y - _ptStart._y);	
		
	float v_x = 0;
	float v_y = 0;
	if(absX == 0)	
		v_x = 0;
	else 
		v_x = v*(_ptEnd._x - _ptStart._x)/sqrt(absX*absX + absY*absY);	//x方向的速度	
	if(absY == 0)
		v_y = 0;
	else
		v_y = v*(_ptEnd._y - _ptStart._y)/sqrt(absX*absX + absY*absY);	//y方向的速度
 	
/* 	cout<<"@@Tory start_x:"<<_ptStart._x<<endl;
	cout<<"@@Tory start_y:"<<_ptStart._y<<endl;
	cout<<"@@Tory v_y:"<<v_x<<endl;
	cout<<"@@Tory v_y:"<<v_y<<endl;
 	cout<<"@@Tory x_value:"<<v_x*t<<endl;
	cout<<"@@Tory y_value:"<<v_y*t<<endl; */
	
	Point currentPt = _ptStart;
	currentPt._x += v_x*t;
	currentPt._y += v_y*t;
	
	//获取经过时间t后的x方向和y方向的坐标更改值
	unsigned int absX_c = (_ptStart._x - currentPt._x)>0 ? (_ptStart._x - currentPt._x) : (currentPt._x - _ptStart._x);
	unsigned int absY_c = (_ptStart._y - currentPt._y)>0 ? (_ptStart._y - currentPt._y) : (currentPt._x - _ptStart._y);
	if(absX_c < absX || absY_c < absY)
		return currentPt;
	else	
		return _ptEnd;
}
/*通过宠物的实例id,找到正在出战的宠物,九宫格用*/
Pet* id_to_getActivePet(char* petid)
{
    map<string,Pet*>::iterator it;
    it=id_to_activePet.find(petid);
    if(it==id_to_activePet.end())
    {
        return NULL;
    } 
	else
    {
        return it->second;
    }
}

Pick* id_to_getPick(string pickid)
{
    map<string,Pick*>::iterator it;
    it=goods_to_hero.find(pickid);
    if(it==goods_to_hero.end())
    {
        return NULL;
    } else
    {
        return it->second;
    }
}

/*
* author: 	Tory
* date	:	2012/9/3  
* 传入参数：Hero对象指针：*myHero
* 返回值：	string类型值，用于发送给登陆用户的客户端，使其进入出生场景
* Description: come_into_scene为CreateMessage下的static成员函数，可通过类名直接调用，无需实例化
*/
string CreateMessage::come_into_scene(Hero *myHero)
{
    string basic_infor;
    string msg_head = "1";
    basic_infor = msg_head + intTostring(SELECT_HERO_RETURN) + intTostring(SUCCESS);
	char mapId[15] = {0};		//主城：map_001，副本地图：ectype_map_025
	strncpy(mapId, myHero->getMapId(), 14);	//去掉副本地图id后的衍生号
    basic_infor += charTostring(mapId);                				//3
    basic_infor += charTostring(myHero->getIdentity());             //4
    basic_infor += charTostring(myHero->getNickName());             //5
	Equipment *equip=myHero->getWearEquip(0);
	if (equip==NULL)												//6时装的图片id
	{
		basic_infor += ",0"; 
	}
	else
	{
		basic_infor += charTostring(equip->getPhotoId());
	}                   
    basic_infor += intTostring(myHero->getCamp());                  //7获得角色当前所在阵营
    basic_infor += intTostring(myHero->getGuildTitle());            //8帮派职位	
    basic_infor += charTostring(myHero->getGuildName());                    //9帮派名
    basic_infor += intTostring((myHero->getGuild() == NULL)\
                               ? 0 : myHero->getGuild()->getLevel());  //10帮派等级
    basic_infor += intTostring(myHero->getExpNow());                //11获得角色当前经验值
    basic_infor += intTostring(myHero->getExpForGrow());            //12获得角色升级所需经验
    basic_infor +=intTostring(myHero->memHero->vipDailyData.stage);                //13vip 
    basic_infor +=intTostring(myHero->getCrimeValue());             //14罪恶值
    basic_infor += intTostring(myHero->getGradeNow());              //15获得角色当前等级
    basic_infor += intTostring(myHero->getPrestigeValue());         //16获得角色当前声望
    basic_infor += ","+myHero->getTitle();                 			//17获得角色当前头衔
    basic_infor += charTostring(myHero->getParty());                //18获得角色所属门派
    basic_infor += intTostring(myHero->getLifeUpperVal());          //19获得生命值上限
    basic_infor += intTostring(myHero->getLifeVal());               //20获得当前生命值
    basic_infor += intTostring(myHero->getMagicUpperVal());         //21获得魔法上限值
    basic_infor += intTostring(myHero->getMagicVal());              //22获得当前魔法值
    basic_infor += intTostring(myHero->getAtk_range());             //23获得当前攻击角色攻击范围
    basic_infor += intTostring((myHero->getLocation())._x);         //24
    basic_infor += intTostring((myHero->getLocation())._y);         //25
	equip=myHero->getWearEquip(2);
    if(equip==NULL)
    {
        basic_infor += intTostring(0);          //26		武器等级
    } 
	else
    {
        basic_infor += intTostring(equip->getgrade());           //26		武器等级
    }
    equip=myHero->getWearEquip(7);
    if(equip==NULL)
    {
        basic_infor += intTostring(0);          //27		肩膀等级
    }
	else
    {
        basic_infor += intTostring(equip->getgrade());           //27		肩膀等级
    }
	equip=myHero->getWearEquip(13);
	if (equip==NULL)												//28		翅膀
	{
		basic_infor+=intTostring(0);
	}
	else
	{
		basic_infor+=charTostring(equip->getPhotoId());
	}
	
	Ride *ride=myHero->getRide();
	if (ride==NULL)
	{
		basic_infor+=intTostring(0);					//29没有坐骑
		basic_infor+=intTostring(0);					//30没有骑坐骑
	}
	else
	{
		if (ride->ifFull())
		{
			basic_infor+=intTostring(1);					//29有坐骑
			if (myHero->memHero->rideState == RIDE_STATE_RIDING)
			{
				basic_infor+=charTostring(ride->getPhotoId());					//30有骑坐骑			
			} 
			else
			{
				basic_infor += intTostring(0);					//30没有骑坐骑
			}
		}
		else 
		{
			basic_infor+=intTostring(0);					//29没有坐骑
			basic_infor+=intTostring(0);					//30没有骑坐骑
		}
	}
	
	if (serverOpenTime>myHero->memHero->offlineTime)
	{
		basic_infor+=intTostring(1);				//31出先更新公告
	}
	else
	{
		basic_infor+=intTostring(0);				//31不出先更新公告
	}	
	
	basic_infor += intTostring(myHero->getArea());			
    return basic_infor;
}

/********************************************************************
* author: 	Tory
* date	:	2012/9/3  
* 传入参数：Hero对象指针：*myHero
* 返回值：	string类型值，用于发送给登陆用户的客户端，使其进入出生场景
* Description: come_into_scene为CreateMessage下的static成员函数，可通过类名直接调用，无需实例化
*********************************************************************/
string CreateMessage::inst_record_infor(Hero *myHero)
{
    string inst_record_infor;
    string msg_head = "1";

    inst_record_infor = msg_head + intTostring(INSTANCE_RECORD_RETURN);
    inst_record_infor += ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
    return inst_record_infor;
}
/********************************************************************
* author: 	Tory
* date	:	2012/9/3  
* 传入参数：Hero对象指针：*myHero
* 返回值：	string类型值，用于广播给在线玩家，有新角色进入
* Description: come_into_view为CreateMessage下的static成员函数，可通过类名直接调用，无需实例化
*********************************************************************/
string CreateMessage::come_into_view(Hero *myHero)
{
    string msg_broadcast;                                               
    string msg_broadcast_head = "2";
    msg_broadcast += msg_broadcast_head;
    msg_broadcast += intTostring(LOGIN_RETURN_OTHER);
    msg_broadcast += ",";
    msg_broadcast += HERO_TYPE;                                         //2
    msg_broadcast += charTostring(myHero->getIdentity());               //3
    msg_broadcast += charTostring(myHero->getNickName());               //4
	Equipment *equip=myHero->getWearEquip(0);
	if (equip==NULL)												//5时装的图片id
	{
		msg_broadcast += ",0"; 
	}
	else
	{
		msg_broadcast += charTostring(equip->getPhotoId());
	}                    //5
    msg_broadcast += intTostring(myHero->getCamp());                    //6获得角色当前所在阵营
    msg_broadcast += intTostring(myHero->getGuildTitle());              //7帮派职位	
    msg_broadcast += charTostring(myHero->getGuildName());                      //8帮派名
    msg_broadcast += intTostring((myHero->getGuild() == NULL)\
                                 ? 0 : myHero->getGuild()->getLevel());          //9帮派等级
    msg_broadcast +=intTostring(myHero->memHero->vipDailyData.stage);              // 10vip
    msg_broadcast +=intTostring(myHero->getCrimeValue());               //11罪恶值
    msg_broadcast += intTostring(myHero->getGradeNow());                //12获得角色当前等级
    msg_broadcast += ","+myHero->getTitle();  			                    //13获得角色当前头衔
    msg_broadcast += charTostring(myHero->getParty());                  //14门派ID
    msg_broadcast += intTostring(myHero->getLifeUpperVal());            //15获得生命上限值
    msg_broadcast += intTostring(myHero->getLifeVal());                 //16获得当前生命值
    msg_broadcast += intTostring(myHero->getMagicUpperVal());           //17获得魔法上限值
    msg_broadcast += intTostring(myHero->getMagicVal());                //18获得当前魔法值
	//玩家状态,摆摊5,打坐6
	msg_broadcast+=intTostring(myHero->getHeroState());    //19 
    // msg_broadcast += intTostring(myHero->getAtk_range());               //19获得当前攻击角色攻击范围
    msg_broadcast += intTostring((myHero->getLocation())._x);           //20
    msg_broadcast += intTostring((myHero->getLocation())._y);           //21	  
	equip=myHero->getWearEquip(2);
    if(equip==NULL)
    {
        msg_broadcast += intTostring(0);          //22		武器等级
    } 
	else
    {
        msg_broadcast += intTostring(equip->getgrade());           //22		武器等级
    }
    equip=myHero->getWearEquip(7);
    if(equip==NULL)
    {
        msg_broadcast += intTostring(0);          //23		肩膀等级
    }
	else
    {
        msg_broadcast += intTostring(equip->getgrade());           //23		肩膀等级
    }
	equip=myHero->getWearEquip(13);
	if (equip==NULL)												//24		翅膀
	{
		msg_broadcast+=intTostring(0);
	}
	else
	{
		msg_broadcast+=charTostring(equip->getPhotoId());
	}
	
	Ride *ride = myHero->getRide();
	if (ride != NULL)
	{
		if (ride->ifFull())
		{
			if (myHero->memHero->rideState == RIDE_STATE_RIDING)
			{
				msg_broadcast+=charTostring(ride->getPhotoId());					//25有骑坐骑
			} 
			else
			{
				msg_broadcast += intTostring(0);					//25没有骑坐骑
			}
		}
		else
		{
			msg_broadcast+=intTostring(0);					//25没有骑坐骑
		}
	}
	else
	{
		msg_broadcast+=intTostring(0);					//25没有骑坐骑
	}
	msg_broadcast += intTostring(myHero->getArea());
	
	size_t teamSize = 0;
	
	//返回-1，表示异常，0：无组队，1，队员，2，队长
	msg_broadcast += intTostring(judgeHeroTeam(myHero,teamSize));	
	
	//队伍人数
	msg_broadcast += intTostring(teamSize);	
	
    return msg_broadcast;
    //cout<<"in enter_scene,msg_broadcast: "<<msg_broadcast<<endl;
}

/*下线通知*/
string CreateMessage::out_of_view(Hero *myHero)
{
    string msg_broadcast = "2";
    msg_broadcast += intTostring(5);
    msg_broadcast += charTostring(myHero->getIdentity()); 
    msg_broadcast += intTostring(1);
    return 	msg_broadcast;
}

//随机给数组排序
void   mysort(int   a[],int   iLen) 
{
    for(int   i=0;i <iLen;i++)
    {
        int   iRand   =   rand()%iLen; 
        int   iTemp   =   a[iRand]; 
        a[iRand]   =   a[i]; 
        a[i]   =   iTemp; 
    } 
}



/*获取马车的实例*/
Wagon* getInstWgon(string wagonId)
{
    map<string,Wagon*>::iterator wagon_it; 
    wagon_it = wagonInstMap.find(wagonId);
    if(wagon_it == wagonInstMap.end())
    {
        return NULL;
    }
    return wagon_it->second;
}

int random_number(int begin,int end)
{
    int between=end-begin;
    int result=rand()%(between+1);
    result+=begin;
    return result;
}


bool viewStyleHero(Hero *self,Hero *other,int style)
{
    string viewStr;
    string sellStr;
    if(self == NULL || other == NULL || self->getFd() == other->getFd() ||\
       strcmp(self->getIdentity(),other->getIdentity()) == 0)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        viewStr = CreateMessage::come_into_view(other);
        send_msg(self->getFd(),const_cast<char *>(viewStr.c_str()));

        /*摊位信息*/
		if (self->getHeroState()==5)
		{				
			self->sendMsgByStall(g_out_buf,sizeof(g_out_buf));
			send_msg(other->getFd(),g_out_buf);
		}
		if (other->getHeroState()==5)
		{
			other->sendMsgByStall(g_out_buf,sizeof(g_out_buf));
			send_msg(self->getFd(),g_out_buf);
		}
        
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = CreateMessage::out_of_view(other);
        send_msg(self->getFd(),const_cast<char *>(viewStr.c_str()));
        return true;
    }
    return false;
}

/*怪物信息*/
bool viewStyleMon(Hero *self,MonsterBase *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
	
	/*怪物已死亡*/
	if(!other->getLifeStation())
	{
		return false;
	}
	
    /*走进视野*/
    if(style == 1)
    {
        other->formBshMsg();    
        viewStr = other->getBshMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        other->formOutMsg();
        viewStr = other->getOutMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}

/*马车信息*/
bool viewStyleWagon(Hero *self,Wagon *other,int style)
{
    char* viewStr;
    if(self == NULL || other == NULL)
    {
		cout<<"the self or the other is NULL:"<<endl;
        return false;
    }

    if(other->getOwner()==NULL)
    {
		cout<<"the wagon owner is NULL:"<<endl;
		return false; //benliao 20121123
    }

    /*走进视野*/
    if(style == 1)
    {
        other->formBornMsg();   
        viewStr = other->getOnlineMsg();
        send_msg(self->getFd(),viewStr);
		cout<<"the about the heroid:"<<self->getIdentity()<<" viewStr of wagon:"<<viewStr<<endl;
        return true;
    }

    if(other->getOwner() == NULL || strcmp(self->getIdentity(), other->getOwner()->getIdentity()) == 0)
    {
        return false;
    }

    /*走出视野*/
    else if(style == 2)
    {
        other->formOutMsg();
        viewStr = other->getOfflineMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}

/*可摘取物品信息*/
bool viewStyleTakeGoods(Hero *self,TakeGoods *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
		other->formBornMsg();
        viewStr = other->getBronMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = other->getOutMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}

/*掉落装备信息*/
bool viewStyleEquip(Hero *self,Equipment *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        viewStr = other->getDropMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = other->getDropDisMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}

/*雕像信息*/
bool viewStyleStatuary(Hero *self,StatuaryHero *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        viewStr = other->getInSeeMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = other->getOutSeeMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}


/*陷阱，暗器信息*/
bool viewStyleTrap(Hero *self,Trap *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        viewStr = other->getBronMsg();
		cout<<"tarpView:"<<viewStr<<endl;
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = other->getOutMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}

/*瓶罐信息*/
bool viewStyleBottle(Hero *self,Bottle *other,int style)
{
    char *viewStr;
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        viewStr = other->getBronMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        viewStr = other->getOutMsg();
        send_msg(self->getFd(),viewStr);
        return true;
    }
    return false;
}


/*宠物信息*/
bool viewStylePet(Hero *self,Pet *other,int style)
{
    if(self == NULL || other == NULL)
    {
        return false;
    }
	

    /*走进视野*/
    if(style == 1)
    {
        other->msg_active(g_out_buf,sizeof(g_out_buf));
        send_msg(self->getFd(),g_out_buf);
        return true;
    }

    /*走出视野*/
    else if(style == 2)
    {
		/*宠物不给主人发下线消息*/
		if (self->getPetBox()->getActivePet()!=NULL)
		{		
			if(other->getIdentity()==self->getPetBox()->getActivePet()->getIdentity())
			{
				return false;
			}
		}
		
        other->msg_downline(g_out_buf,sizeof(g_out_buf));
        send_msg(self->getFd(),g_out_buf);
        return true;
    }
    return false;
}

//获取系统时间
int getTime()
{
    time_t rawtime;
    time ( &rawtime );
    return rawtime;
}

/*掉落信息*/
bool viewStylePick(Hero *self,Pick *other,int style)
{
    if(self == NULL || other == NULL)
    {
        return false;
    }
    /*走进视野*/
    if(style == 1)
    {
        other->msg_online(g_out_buf,sizeof(g_out_buf));
        send_msg(self->getFd(),g_out_buf);
        return true;
    }
    /*走出视野*/
    else if(style == 2)
    {
        other->msg_offline(g_out_buf,sizeof(g_out_buf));
        send_msg(self->getFd(),g_out_buf);
        return true;
    }
    return false;
}


/*去掉房间号的副本id*/
string dealCpyId(string _cpyId)
{	
    int found;
    string newCpyId;

    found = _cpyId.find_last_of("_");

    newCpyId = _cpyId.substr(0,found);

    return newCpyId;
}

void dealCpyId(char *_cpyId)
{
	int found;
    // string newCpyId;
	int num;
	char a[2]={'\0'},b[2]={'\0'};
	strncpy(b,"_",sizeof("_"));
	for (int i=0;i<strlen(_cpyId);i++)
	{
		strncpy(a,_cpyId+i,1);
		if (strcmp(a,b)==0)
		{
			found=i;
		}
	}
    // found = _cpyId.find_last_of("_");
	
	memmove(_cpyId,_cpyId,found);
    // newCpyId = _cpyId.substr(0,found);

    // return newCpyId;
}

void msg_error(char* msg,int flag)                  //错误信息发送
{
	if (msg==NULL)
	{
		return;
	}
	sprintf(msg,"%d,%d,%d",10,ERROR,flag);
}


/*在读取地图配置文件里面用*/
void deleteBruRec(map<string,BruMonInfor*> &bruRecod)
{
    map<string,BruMonInfor*>::iterator bru_it;
    bru_it = bruRecod.begin();
    BruMonInfor *node;
    while(bru_it != bruRecod.end())
    {
        node = bru_it->second;
        delete node;
        node = NULL;
        bru_it++;
    }
    bruRecod.clear();
}

static void setPlayerNumber(struct ev_loop *loop,ev_timer *think,int revents)
{
	ev_timer_stop(loop,think);
	/*记录在线角色的流水账 jolly 11.14 start*/
	char account_msg[100]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%d",2,0,server_name,(int)myTime.tv_sec,(int)heroId_to_pHero.size());
	write_log(account_msg);	
	// cout<<"11112222222333333344444444455555555666666677777777"<<endl;
	/*记录在线角色的流水账 jolly 11.14 end*/
	ev_timer_start(loop,think);
}

void initPlayerNumber(void)
{
	ev_timer *countPlayerTimer=new ev_timer;
	ev_timer_init(countPlayerTimer,setPlayerNumber,60,0);
	ev_timer_start(loops,countPlayerTimer);
}


void sub_str(char *dest, char *src, int start, int cnt)
{
	if (cnt == 0)
	{
		strncpy(dest, src + start, strlen(src+start));
		dest[strlen(src+start)] = 0;
	}
	else 
	{
		strncpy(dest, src + start, cnt);
		dest[cnt] = 0;
	}
}

int findChar(const char *src, char key, int srcLen)
{
	int pos = 0;
	while (src[pos] != key && --srcLen && src[pos++] != 0)
	;
	if (srcLen == 0)
	{
		return -1;
	}
	return pos;
}



/*获取掉落装备*/
Equipment* getEquipInst(string equipId)
{
	map<string,Equipment*>::iterator equip_it;
	// for(equip_it = dropEquipMent.begin();equip_it != dropEquipMent.end();equip_it++)
	// {
		// cout<<"the key:"<<equip_it->first<<endl;
		
		// cout<<"the Value:"<<equip_it->second->getparty()<<endl;
	// }
	
	if(equipId.empty() || dropEquipMent.empty())
	{
		cout<<"the id is error or the drioEquipMent is empty:"<<equipId<<endl;
		return NULL;
	}
	equip_it = dropEquipMent.find(equipId);
	if(equip_it == dropEquipMent.end())
	{
		cout<<"can not find the equipInst the id is error :"<<equipId<<endl;
		return NULL;
	}
	return equip_it->second;
}


/*删除掉落装备从全局容器*/
bool reaseEquip(string equipId)
{
	map<string,Equipment*>::iterator equip_it;
	// for(equip_it = dropEquipMent.begin();equip_it != dropEquipMent.end();equip_it++)
	// {
		// cout<<"the key:"<<equip_it->first<<endl;
		
		// cout<<"the Value:"<<equip_it->second->getparty()<<endl;
	// }
	
	if(equipId.empty() || dropEquipMent.empty())
	{
		cout<<"the id is error or the drioEquipMent is empty:"<<equipId<<endl;
		return false;
	}
	equip_it = dropEquipMent.find(equipId);
	if(equip_it == dropEquipMent.end())
	{
		cout<<"can not find the equipInst the id is error :"<<equipId<<endl;
		return false;
	}
	dropEquipMent.erase(equip_it);
	return true;
}

/*获得道具刷出怪物实例指针*/
MonsterBase* getToolMonster(char *monId)
{
	map<string,MonsterTool*>::iterator toolMon_it;
	Map_Inform *map_now;
	// cout<<"monId:"<<monId<<endl;
	
	
	for(toolMon_it = toolMonsterIdToInst.begin();toolMon_it != toolMonsterIdToInst.end();toolMon_it++)
	{
		// cout<<"key:"<<toolMon_it->first<<endl;
		map_now = toolMon_it->second->getMap();
		if(map_now == NULL)
		{
			cout<<"the map is NULL:"<<endl;
			continue;
		}
		
		cout<<"mapId:"<<map_now->getMapId()<<endl;
		cout<<"pt._x:"<<toolMon_it->second->getLocation()._x<<endl;
		cout<<"pt._y:"<<toolMon_it->second->getLocation()._y<<endl;
	}
	
	if(monId == NULL || strlen(monId) == 0)
	{
		return NULL;
	}
	toolMon_it = toolMonsterIdToInst.find(monId);
	if(toolMon_it == toolMonsterIdToInst.end())
	{
		return NULL;
	}
	return toolMon_it->second;
}

/*击杀世界boss,全服广播
**hero为杀boss最后一刀的玩家实例,monsterName为世界boss的汉字名字
*/
void killGlobalBossAdvertise(Hero *hero,char *monsterName)
{
	char info[1024]={'\0'};				
	if (hero!=NULL)
	{					
		snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%d,%d,%d",7,SYSTEM_WARN,"xf008",2,1,hero->getNickName(),hero->getIdentity(),0,0,3,monsterName,0,0,0);
		map<string, Hero*>::iterator it_hero;

		for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
		{
			if (it_hero->second!=NULL)
			{						
				send_msg(it_hero->second->getFd(),info);
			}
		}
	}
}

//发送消息到cdkey Server
bool send_msg_to_cdkey(char *msgbody)
{
	char msg[2048] = {0};
	memset(msg, 0, sizeof(msg));
	msg[0]=255;//消息头的生成；
	msg[1]=216;	
	msg[2]=1;
	msg[3]=1;	
	int size = strlen(msgbody);
	size=htonl(size);			//转换网络字节序；
	memcpy(msg + 4, (char*)&size, 4);
	
	/** size=0;//测试写入的大小对不对；
	 memcpy((char*)&size,recharge_msg+4,4);
	 cout<<"size:"<<size<<endl;*/
	memcpy(msg + 8, msgbody, strlen(msgbody));
	
	
	if(cdKeySrvFd == -1)//充值服务器宕机，重连接；
	{
		if(!con_cdkey_server())
		{
			//充值服务器宕机，重新链接失败；
			cout<<"[XHM TEST] cdkey_server is not working,To con_cdkey_server ERROR!"<<endl;
			return false;
		}else{
			cout<<"[XHM TEST] To con_cdkey_server SUCCESS!"<<endl;
		}
	}
	
	int ret = write(cdKeySrvFd, msg, 8 + strlen((char*)msgbody));//将消息发送到充值服务器
	if(ret != strlen(msgbody) + 8)
	{
		cout<<"[XHM Warning] (top_up.cpp) write ERROR,we just return."<<endl;
		if(ret == -1)
		{
			if(cdKeySrvFd == -1)//充值服务器宕机，重连接；
			{
				if(!con_cdkey_server())
				{
					//充值服务器宕机，重新链接失败；
					cout<<"[XHM TEST] cdkey_server is not working,To con_cdkey_server ERROR!"<<endl;
				}else{
					ret = write(cdKeySrvFd, msg, 8 + strlen((char*)msgbody));//将消息发送到充值服务器
					if(ret == strlen((char*)msgbody)+8)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

//刷新组队状态
string CreateMessage::brushHeroTeamStation(Hero *myHero)
{
	string basic_infor = "37,3";
	basic_infor += charTostring(myHero->getIdentity());			
	size_t teamSize = 0;
	
	//返回-1，表示异常，0：无组队，1，队员，2，队长
	basic_infor += intTostring(judgeHeroTeam(myHero,teamSize));	
	
	//队伍人数
	basic_infor += intTostring(teamSize);	
    return basic_infor;
}

