/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server好友逻辑操作；

**************************************************/

#ifndef _FRIEND_H
#define _FRIEND_H

#include<map>
#include<string>
#include<vector>
#include<memory.h>
#include<iostream>

#include "data_structure_struct.h"

#define ONLINE 1
#define NOT_ONLINE 0

#define TRADE_ADD_FRIEND_DGR 1
#define FLOWERS_ADD_FRIEND_DGR 2
#define DAY_FRIEND_DGR_ADD_COUNTS 5
const int PAGE_FRIEND_NUM = 7;
using namespace std;
class Hero;


//有关角色好友基本信息；
// typedef struct FriendInfo_S{
	// char heroName[32];	//好友名字；
	// char party[2];		//好友门派；
	// int grad;			//好友等级；	
	// int friendLevel;	//好友度
	
	// FriendInfo_S(string _heroName=NULL,string _party=NULL,int _grad=0,int _friendLevel=0)
	// {
		// memcpy(heroName,_heroName.c_str(),strlen(_heroName.c_str()));
		// heroName[strlen(_heroName.c_str())]='\0';
		// memcpy(party,_party.c_str(),strlen(_party.c_str()));
		// party[strlen(_party.c_str())]='\0';
		// grad=_grad;
		// friendLevel=_friendLevel;
	// }
// }FriendInfo_T;

// typedef struct MemFriendInfo_S{
	// char myFriendID[MAX_FRIEND_COUNTS][37];
	// FriendInfo_T myFriendInfo[MAX_FRIEND_COUNTS];
	// char myBlackListID[MAX_FRIEND_COUNTS][37];	
	// FriendInfo_T myBlackListInfo[MAX_FRIEND_COUNTS];		
// }MemFriend_T;

#define NICKNAME_Val(a,b) ( map<string,string>::value_type( (a),(b)) )
#define FRIEND_Val(a,b) ( map<string,FriendInfo_T>::value_type( (a),(b)) )

class Friend{

public:

/**
函数作用 构造函数；
*/
Friend();

	
/**
函数作用 好友信息用缓存构建；
函数参数 myFriendInfo 好友信息信息结构体；
*/
Friend(MemFriend_T _myFriendInfo,int where_am_I);
	
	
/**
函数作用 好友信息存缓存；
函数参数 myHero 好友实例指针；
  返回值 int true成功；
			 false失败；
*/	
bool saveFriendInfoToMem(Hero* myHero);


/**
函数作用 加好友申请；
函数参数 heroId 将要加好友的Id；
  返回值 int -1:heroId为空；
			 -2:heroId在好友列表里面；
			 -3:heroId在黑名单列表里面；
			  0:成功；
*/
int applyForFriend(string heroId);
	
	
	
/*好友操作*/
/**
函数作用 从好友列表里面删除好友；
函数参数 myFrined 将要加好友的实例指针；
  返回值 int -1:heroId为空；
			 -2:heroId不在好友列表里面；
			  0:成功；
*/
int delFromFriendlist(string heroId);


/**
函数作用 加好友到好友列表；
函数参数 myFrined 将要加好友的实例指针；
  返回值 int -1:myFriend为空；
			 -2:myFriend已经在好友列表里面；
			 -3:myFriend是黑名单，不能加为好友；
			  0:成功；
*/
int add2Friendlist(int where_am_I, Hero* otherHero);										//好友在线；


/**
函数作用  加好友到好友列表；
函数参数  myFrined 将要加好友的id;tempInfo 好友信息结构体；
  返回值  int -1:myFriend为空；
			  -2:myFriend已经在好友列表里面；
			  -3:myFriend是黑名单，不能加为好友；
			   0:成功；
*/
int add2Friendlist2(string myFriend,FriendInfo_T& tempInfo);			//好友离线；


/**
函数作用  加好友到黑名单列表；
函数参数  heroId 将要加黑名单的id;
  返回值 int -1:在好友列表里面找不到（只能加好友为黑名单）；
			 -2:heroId已经在黑名单列表里面；
			  0:成功；
*/
int add2Blacklist(string heroId);

	
/*黑名单操作*/
/**
函数作用  将黑名单列表里移到好友列表；
函数参数  将要移除黑名单的id;
  返回值  int -1:在黑名单里面找不到（只能把黑名单的信息移到好友列表）；
			  -2:heroId已经在好友列表里面；
			   0:成功；
*/
int removeBlacklistToFriend(string heroId);


/**
函数作用  将黑名单列表里删除；
函数参数  heroId 将要删除黑名单的id;
  返回值  int -1:在黑名单里面找不到；
			   0:成功；
*/
int delFromBlacklist(string heroId);

	
/*好友系统信息查看操作*/
/**
函数作用  查看好友信息列表；
  返回值  string 好友信息的字符串列表；
		  heroId+heroName+heroPary+heroGrad+ISONLINE+friendLevel;
*/	
char*  viewFriendlistInfo(void);


/**
函数作用  查看黑名单信息列表；
  返回值  string 黑名单信息的字符串列表；
		  heroId+heroName+heroPary+heroGrad+ISONLINE+friendLevel;
*/	
char*  viewBlacklistInfo(void);

	
/**
函数作用  通过好友名字查找好友ID
  返回值  string 好友ID；
*/	
string NickNameFindFriendId(string _nickName);

/**
函数作用  初始化好友度增加限制值
  返回值  bool true成功.false失败；
*/	
bool initFriendDegLimit();


/**
函数作用  增加好友度；type 为TRADE_ADD_FRIEND_DGR交易增加，有限制次数；
						     FLOWERS_ADD_FRIEND_DGR送鲜花增加，无限制增加；
  返回值  bool true成功.false失败；
*/	
bool addFriendDeg(char* friendId,int _type,int num=1);


/**
函数作用  获取好友个数；
返回值 size_t 好友个数；
*/	
size_t getFrientSize(void);


//打印测试
void printFrients() const;


char* NickNameFindFriend(const char*_nickName,size_t friendFlg);

bool insertOnLineList(const char *friendId);

bool insertOffLineList(const char *friendId);

bool eraseOffLineList(const char *friendId);

bool eraseOnLineList(const char *friendId);
 
char* viewFriendlistInfo(size_t pageNum);

char* viewBlacklistInfo(size_t pageNum);

bool isInBlack(const char* friendHeroId) const;

bool isInFriend(const char* friendHeroId) const;
	
private:
	map<string,string>waitingResponseFriendsInfo;						//已经加好友等待响应信息；
	map<string,string>nickNameToheroIdInfo;
	map<string,FriendInfo_T>friendsInfo;								//好友信息；
	map<string,FriendInfo_T>BlacklistInfo;								//黑名单信息；
	set<string>onLineList;                 //上线容器	
	set<string>offLineList;                //离线容器
	char * findFriendMsg(const char*_heroId,size_t friendFlg);
	
	void initOnAndOffLineList(void);
	
	bool dealFriendAsist(const char *friendId);
	
	size_t sprintOffLineMsg(size_t position,size_t showPersonNum);
	
	size_t sprintOnLineMsg(size_t position,size_t showPersonNum);
};

#endif