/*
		文件类型：头文件
		文件名称：command_other_function_all_over
		文件作用：对一些在整个游戏中都会调用的的函数的定义
*/
#ifndef COMMAND_OTHER_FUNCTION_ALL_OVER
#define COMMAND_OTHER_FUNCTION_ALL_OVER
#include"data_structure_struct.h"
#include"libev.h"
#include<time.h>
#include<list>
#include<string.h>
#include<stdio.h>
#include<uuid.h>
#include<stdlib.h>
#include<iostream>
#include"map_inform.h"
#include"hero.h"
#include"role.h"
#include"wagon.h"
#include"trap.h"
#include"bottle.h"
#include<map>

class Pet;
class Hero;
class Map_Inform;
class Pick;
class MonsterBase;
class Wagon;
class TakeGoods;
class Bottle;
class Pet;
class Pick;
class BruMonInfor;
class Equipment;
class StatuaryHero;
void init_command_map(void);      												//初始化命令处理函数数组

void sendMsg_Nine(Hero *hero,string msg);										//发送玩家九宫格内的其他玩家消息 evan add 2012.8.23
Point MapExchangeLogical(Point pointOfmap);

Point LogicalExchangeMap(Point pointOflogical);

string intTostring(int value);                                               //int类型转换为string

string charTostring(char *value);                                            //char*类型转换为string

string itos(int i);															//int to string by Cookie

bool send_msg(int fd, char *msg_body);	

bool send_msg(int fd, string &msg_body);

bool ComFun(const HatVal &hat1,const HatVal &hat2);

int HatFun(list<HatVal> &hat1,list<HatVal> &hat2,char *perHerId,char *goodsOwner,\
			char *monId,bool isCopy = false);								//用于服务器向客户端消息的发送时

char *cid();																//获取uuid by Cookie
char *cidOtherWay();

/*在id后面追加流水号，且补齐byteSum位* add chenzhen 2012.06.11*/
void appendNum(char *id,int num,int byteSum);    


/*进入场景函数*/
void enter_scenes(Hero *myHero, Map_Inform *map_now,int entOlder = 1);     

/*退出场景函数*/
void quit_scene(Hero *myHero, Map_Inform *map_now);  

Hero* fd_to_hero();

/*判断一张地图里俩个点直线之间是否有障碍点*/
bool hasBarrier(Point ptStart,Point ptEnd,Map_Inform* mapInfo);

/*获得被攻击玩家实例指针*/
Hero* heroid_to_hero(string heroId);

//获得宠物实例
Pet* id_to_getActivePet(char* petid);

//获得宝箱实例
Pick* id_to_getPick(string pickid);
 
/*获取马车的实例*/
Wagon* getInstWgon(string wagonId);

/*取随机数*/
int random_number(int begin,int end);
 
class CreateMessage
{
	public:
		static string come_into_scene(Hero *myHero);
		//英雄进出副本状态消息生成 added by tory
		static string inst_record_infor(Hero *myHero);
		//用于广播给在线玩家，有新角色进入视野范围
		static string come_into_view(Hero *myHero);
		
		static string out_of_view(Hero *myHero);
		
		//刷新组队状态
		static string brushHeroTeamStation(Hero *myHero);
		
};

void   mysort(int   a[],int   iLen) ;

bool viewStyleHero(Hero *self,Hero *other,int style);

/*怪物信息*/
bool viewStyleMon(Hero *self,MonsterBase *other,int style);

/*马车信息*/
bool viewStyleWagon(Hero *self,Wagon *other,int style);

/*可摘取物品信息*/
bool viewStyleTakeGoods(Hero *self,TakeGoods *other,int style);

/*陷阱，暗器信息*/
bool viewStyleTrap(Hero *self,Trap *other,int style);

/*瓶罐信息*/
bool viewStyleBottle(Hero *self,Bottle *other,int style);

/*宠物信息*/
bool viewStylePet(Hero *self,Pet *other,int style);

/*掉落信息*/
bool viewStylePick(Hero *self,Pick *other,int style);

/*掉落装备信息*/
bool viewStyleEquip(Hero *self,Equipment *other,int style);

/*去掉房间号的副本id*/
string dealCpyId(string _cpyId);
void dealCpyId(char* _cpyId);

void msg_error(char *msg,int flag);					//错误信息发送
/*在读取地图配置文件里面用*/
void deleteBruRec(map<string,BruMonInfor*> &bruRecod);


//字符验证函数聊天 返回ture 则合法  返回false不合法
bool charsCheckingChat(const char *c);
//字符验证函数命名
bool charsCheckingName(const char *c);

void initPlayerNumber(void);

//substr
void sub_str(char *dest, char *src, int start, int cnt = 0);
//string::find
int findChar(const char *src, char key, int srcLen);

static void heroVerify(struct ev_loop *loop,ev_timer *think,int revents);

 bool send_msg(int fd, char* msg_body);
 
 bool send_msg(int fd, const char *msg_body);
 
 /*函数功能：获取uuid*/				
bool cidOtherWay(char *data,int length);

Point getCurrenPt(Point _ptStart, Point _ptEnd, int v, int t, Map_Inform* mapInfo);


/*获取掉落装备*/
Equipment* getEquipInst(string equipId);

/*删除掉落装备从全局容器*/
bool reaseEquip(string equipId);

/*获得道具刷出怪物实例指针*/
MonsterBase* getToolMonster(char *monId);


/*击杀世界boss,全服广播
**hero为杀boss最后一刀的玩家实例,monsterName为世界boss的汉字名字
*/
void killGlobalBossAdvertise(Hero *hero,char *monsterName);

//发送消息到cdkey Server
bool send_msg_to_cdkey(char *msgbody);

//判断是否有障碍点；
bool has_barrier(Point _ptStart,Point _ptEnd,Map_Inform* mapInfo);

/*雕像信息*/
bool viewStyleStatuary(Hero *self,StatuaryHero *other,int style);

#endif
