/*
	  author:	xhm
		time:	2012-9-3
	function:	管理好友信息操作，好友不在线处理；  

	好友信息信息管理类，离线信息基本操作；
	如果有疑问，请RTX xhm;
*/


#ifndef _FRIEND_INFO_MANAGEMENT_H
#define _FRIEND_INFO_MANAGEMENT_H


#include <map>
#include <vector>
#include "friend.h"

#define IDVAL_MSG(a,b) ( map<string,vector<string> >::value_type( (a),(b)) )
#define IDVAL_ADDFRIEND(a,b) ( map<string,vector<FriendInfo_T> >::value_type( (a),(b)) )
#define IDVAL_DELFRIEND(a,b) ( map<string,vector<string> >::value_type( (a),(b)) )

using namespace std;


class FriendInfoManagement{

public:
/*
argument: myHero 当前上线用户信息检查；
*/
void heroOnlineProces(Hero* myHero);

/*
argument: heroId 当前不在线用户 等待上线的消息发送；
		  msg 等待发送的消息内容；
*/
bool addHeroMsgSend(string heroId,string msg);

/*
argument：srcheroId 等待要删除好友信息的用户；
		  decheroId 删除好友的id;
*/
bool addHeroDelFriend(string srcheroId,string decheroId);

/*
argument：heroId 等待要添加好友信息的用户；
		  friendInfo 好友的基本信息;
*/
bool addHeroAddfriend(string heroId,FriendInfo_T friendInfo);

private:

map<string,vector<string> >heroId2msg;
map<string,vector<string> >::iterator iterMsg;

map<string,vector<FriendInfo_T> >heroIdAddFriend;
map<string,vector<FriendInfo_T> >::iterator iterAddFriend;

map<string,vector<string> >heroIdDelFriend;
map<string,vector<string> >::iterator iterDelFriend;
};
#endif
