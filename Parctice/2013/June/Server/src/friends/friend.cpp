/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server好友逻辑操作实现文件；

**************************************************/

#include "hero.h"
#include "friend.h"
#include "my_memcached.h"
extern map<string, Hero*> heroId_to_pHero;	

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;
static char friend_info[MAX_FRIEND_COUNTS*100];
static char off_friend_info[MAX_FRIEND_COUNTS*100];

/**********************************************
函数作用 构造函数；
***********************************************/
Friend::Friend()
{
}

/**********************************************
函数作用 好友信息用缓存构建；
函数参数 myFriendInfo 好友信息信息结构体；
***********************************************/
Friend::Friend(MemFriend_T myFriendInfo, int where_am_I)
{
	for(int i = 0; i < MAX_FRIEND_COUNTS; i++)
	{
		if(!strlen(myFriendInfo.myFriendID[i]))
			break;	
		char* t = strrchr(myFriendInfo.myFriendInfo[i].heroName, '[');
#if 0
		if(t == NULL)	//将没有加区号的昵称加上区号 tory 2013.3.21
		{
			snprintf(myFriendInfo.myFriendInfo[i].heroName+strlen(myFriendInfo.myFriendInfo[i].heroName), sizeof(myFriendInfo.myFriendInfo[i].heroName), "[%d]", where_am_I);
			cout<<"@@Tory,nickName:"<<myFriendInfo.myFriendInfo[i].heroName<<endl;

		}
#endif		
		friendsInfo.insert(FRIEND_Val(myFriendInfo.myFriendID[i],myFriendInfo.myFriendInfo[i]));//添加到好友容器列表；
		nickNameToheroIdInfo.insert(NICKNAME_Val(myFriendInfo.myFriendInfo[i].heroName,myFriendInfo.myFriendID[i]));//添加到昵称找好友容器
	}
	for(int i = 0; i < MAX_FRIEND_COUNTS; i++)
	{
		if(!strlen(myFriendInfo.myBlackListID[i]))
			break;
		BlacklistInfo.insert(FRIEND_Val(myFriendInfo.myBlackListID[i],myFriendInfo.myBlackListInfo[i]));//添加到黑名单列表；
	}
	
	initOnAndOffLineList();

}



/**********************************************
函数作用 好友信息存储到缓存；
函数参数 myHero 好友实例指针；
  返回值 int true成功；
			 false失败；
***********************************************/
bool 
Friend::saveFriendInfoToMem(Hero* myHero)
{
	if(myHero==NULL)
		return false;
	int i=0;
	memset(myHero->memHero->myFriendInfo.myFriendID,'\0',sizeof(myHero->memHero->myFriendInfo.myFriendID));
	memset(myHero->memHero->myFriendInfo.myFriendInfo,'\0',sizeof(myHero->memHero->myFriendInfo.myFriendInfo));
	for(map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.begin();heroInfoIter!=friendsInfo.end();heroInfoIter++)
	{	
		memcpy(myHero->memHero->myFriendInfo.myFriendID[i],(heroInfoIter->first).c_str(),strlen((heroInfoIter->first).c_str()));
		myHero->memHero->myFriendInfo.myFriendID[i][strlen((heroInfoIter->first).c_str())]='\0';
		memcpy(myHero->memHero->myFriendInfo.myFriendInfo[i].heroName,(heroInfoIter->second).heroName,strlen((heroInfoIter->second).heroName));
		myHero->memHero->myFriendInfo.myFriendInfo[i].heroName[strlen((heroInfoIter->second).heroName)]='\0';
		memcpy(myHero->memHero->myFriendInfo.myFriendInfo[i].party,(heroInfoIter->second).party,strlen((heroInfoIter->second).party));
		myHero->memHero->myFriendInfo.myFriendInfo[i].party[strlen((heroInfoIter->second).party)]='\0';
		myHero->memHero->myFriendInfo.myFriendInfo[i].grad=(heroInfoIter->second).grad;		
		myHero->memHero->myFriendInfo.myFriendInfo[i].friendLevel=(heroInfoIter->second).friendLevel;
		myHero->memHero->myFriendInfo.myFriendInfo[i].vipLevel=(heroInfoIter->second).vipLevel;
		myHero->memHero->myFriendInfo.myFriendInfo[i].campFlg=(heroInfoIter->second).campFlg;
		myHero->memHero->myFriendInfo.myFriendInfo[i].friend_grd_limit=(heroInfoIter->second).friend_grd_limit;
		i++;
	}
	memset(myHero->memHero->myFriendInfo.myBlackListID,'\0',sizeof(myHero->memHero->myFriendInfo.myBlackListID));
	memset(myHero->memHero->myFriendInfo.myBlackListInfo,'\0',sizeof(myHero->memHero->myFriendInfo.myBlackListInfo));
	i=0;
	for(map<string,FriendInfo_T>::iterator heroInfoIter=BlacklistInfo.begin();heroInfoIter!=BlacklistInfo.end();heroInfoIter++)
	{	
		memcpy(myHero->memHero->myFriendInfo.myBlackListID[i],(heroInfoIter->first).c_str(),strlen((heroInfoIter->first).c_str()));
		myHero->memHero->myFriendInfo.myBlackListID[i][strlen((heroInfoIter->first).c_str())]='\0';
		memcpy(myHero->memHero->myFriendInfo.myBlackListInfo[i].heroName,(heroInfoIter->second).heroName,strlen((heroInfoIter->second).heroName));
		myHero->memHero->myFriendInfo.myBlackListInfo[i].heroName[strlen((heroInfoIter->second).heroName)]='\0';
		memcpy(myHero->memHero->myFriendInfo.myBlackListInfo[i].party,(heroInfoIter->second).party,strlen((heroInfoIter->second).party));
		myHero->memHero->myFriendInfo.myBlackListInfo[i].party[strlen((heroInfoIter->second).party)]='\0';
		myHero->memHero->myFriendInfo.myBlackListInfo[i].grad=(heroInfoIter->second).grad;
		myHero->memHero->myFriendInfo.myBlackListInfo[i].friendLevel=(heroInfoIter->second).friendLevel;
		myHero->memHero->myFriendInfo.myBlackListInfo[i].vipLevel=(heroInfoIter->second).vipLevel;
		myHero->memHero->myFriendInfo.myBlackListInfo[i].campFlg=(heroInfoIter->second).campFlg;
		myHero->memHero->myFriendInfo.myBlackListInfo[i].friend_grd_limit=(heroInfoIter->second).friend_grd_limit;
		i++;
	}
	
	// myHero->memSet();//保存角色下的好友数据；
	return true;	
}


/**********************************************
函数作用 加好友判断；
函数参数 heroId 将要加好友的Id；
  返回值 int -1:heroId为空；
			 -2:heroId在好友列表里面；
			 -3:heroId在黑名单列表里面；
			  0:成功；
***********************************************/
int 
Friend::applyForFriend(string heroId)
{
	//最好加上预加好友验证
	if(heroId.empty())
		return -1;
		
	map<string,FriendInfo_T>::iterator iter = friendsInfo.find(heroId);//已经是好友，重复加好友返回；
	if(iter!=friendsInfo.end())
		return -2;
	
	iter = BlacklistInfo.find(heroId);//已经是黑名单，不能加为好友；
	if(iter!=BlacklistInfo.end())
		return -3;
	
	return 0;
}
	
/*好友操作*/
/**********************************************
函数作用 从好友列表里面删除好友；
函数参数 myFrined 将要加好友的实例指针；
  返回值 int -1:heroId为空；
			 -2:heroId不在好友列表里面；
			  0:成功；
***********************************************/
int 
Friend::delFromFriendlist(string heroId)
{
	if(!dealFriendAsist(heroId.c_str()))
	{
		cout<<"Friend::delFromFriendlist warning the friend list is error:"<<heroId<<endl;
	}
	
	if(heroId.empty())
		return -1;
		
	map<string,FriendInfo_T>::iterator iter = friendsInfo.find(heroId);
	if(iter==friendsInfo.end())
		return -2;
	
	map<string,string>::iterator nickNameIter = nickNameToheroIdInfo.find(iter->second.heroName);
	if(nickNameIter!=nickNameToheroIdInfo.end())
		nickNameToheroIdInfo.erase(nickNameIter);
		
	
	friendsInfo.erase(iter);
	return 0;
}



/****************************************
函数作用 加好友到好友列表；
函数参数 where_am_I:当前角色所在的服务器区 otherHero 将要加好友的实例指针；
  返回值 int -1:myFriend为空；
			 -2:myFriend已经在好友列表里面；
			 -3:myFriend是黑名单，不能加为好友；
			  0:成功；
******************************************/
int 
Friend::add2Friendlist(int where_am_I, Hero* otherHero)
{
	if(NULL == otherHero)
		return -1;
		
	map<string,FriendInfo_T>::iterator iter = friendsInfo.find(otherHero->getIdentity());//已经是好友，重复加好友返回；
	if(iter!=friendsInfo.end())
		return -2;
	
	iter = BlacklistInfo.find(otherHero->getIdentity());//已经是黑名单，不能加为好友；
	if(iter!=BlacklistInfo.end())
		return -3;
	
	char nickName[50] = {0};
	snprintf(nickName, 50, "%s", otherHero->getNickName());
	if(where_am_I != otherHero->getArea())
	{
		snprintf(nickName+strlen(nickName), 50, "[%d]", otherHero->getArea());
	}
	
	FriendInfo_T tempInfo(nickName,otherHero->getParty(),otherHero->getGradeNow(),1,otherHero->getVipStage(),\
	otherHero->getCamp(),DAY_FRIEND_DGR_ADD_COUNTS);

	nickNameToheroIdInfo.insert(NICKNAME_Val(nickName,otherHero->getIdentity()));
	friendsInfo.insert(FRIEND_Val(otherHero->getIdentity(),tempInfo));
	if(!insertOnLineList(otherHero->getIdentity()))
	{
		cout<<"Friend::add2Friendlist(int where_am_I, Hero* otherHero) insert failed:"<<otherHero->getIdentity()<<endl;
	}
	return 0;
}



/********************************************************
函数作用  加好友到好友列表；
函数参数  myFrined 将要加好友的id;tempInfo 好友信息结构体；
  返回值  int -1:myFriend为空；
			  -2:myFriend已经在好友列表里面；
			  -3:myFriend是黑名单，不能加为好友；
			   0:成功；
********************************************************/
int 
Friend::add2Friendlist2(string myFriend,FriendInfo_T& tempInfo)
{
	if(myFriend.empty())
		return -1;
		
	map<string,FriendInfo_T>::iterator iter = friendsInfo.find(myFriend);//已经是好友，重复加好友返回；
	if(iter!=friendsInfo.end())
		return -2;
		
	iter = BlacklistInfo.find(myFriend);//已经是黑名单，不能加为好友；
	if(iter!=BlacklistInfo.end())
		return -3;
	
	nickNameToheroIdInfo.insert(NICKNAME_Val(tempInfo.heroName,myFriend));
	friendsInfo.insert(FRIEND_Val(myFriend,tempInfo));
	
	return 0;
}



/********************************************************
函数作用  加好友到黑名单列表；
函数参数  heroId 将要加黑名单的id;
  返回值 int -1:在好友列表里面找不到（只能将已是好友的角色列入黑名单）；
			 -2:heroId已经在黑名单列表里面；
			  0:成功；
**********************************************************/
int 
Friend::add2Blacklist(string heroId)
{
	map<string,FriendInfo_T>::iterator iter = friendsInfo.find(heroId);
	if(iter==friendsInfo.end())
		return -1;
			
	FriendInfo_T tempInfo(iter->second.heroName,iter->second.party,iter->second.grad,iter->second.friendLevel,iter->second.vipLevel,\
	iter->second.campFlg);
	
	friendsInfo.erase(iter);
	
	iter = BlacklistInfo.find(heroId);//已经是黑名单，重复返回；
	if(iter!=BlacklistInfo.end())
		return -2;
		
	BlacklistInfo.insert(FRIEND_Val(heroId,tempInfo));
	return 0;
}
	
	
	
/*黑名单操作*/
/*************************************************************************
函数作用  将黑名单列表里移到好友列表；
函数参数  将要移除黑名单的id;
  返回值  int -1:在黑名单里面找不到（只能把黑名单的信息移到好友列表）；
			  -2:heroId已经在好友列表里面；
			   0:成功；
**************************************************************************/
int 
Friend::removeBlacklistToFriend(string heroId)
{
	map<string,FriendInfo_T>::iterator iter = BlacklistInfo.find(heroId);
	if(iter==BlacklistInfo.end())
		return -1;
		
	FriendInfo_T tempInfo(iter->second.heroName,iter->second.party,iter->second.grad,0,iter->second.vipLevel);
	
	BlacklistInfo.erase(iter);
	
	iter = friendsInfo.find(heroId);//已经是好友，重复返回；
	if(iter!=friendsInfo.end())
		return -2;
	
	nickNameToheroIdInfo.insert(NICKNAME_Val(iter->second.heroName,heroId));
	friendsInfo.insert(FRIEND_Val(heroId,tempInfo));
	
	//跟新当前上下线容器
	Hero *newFriendHero = heroid_to_hero(heroId);
	if(newFriendHero)
	{
		if(!insertOnLineList(heroId.c_str()))
		{
			cout<<"Friend::removeBlacklistToFriend the heroId is failed to insert insertOnLineList:"<<heroId<<endl;
		}
	}
	else
	{
		if(!insertOffLineList(heroId.c_str()))
		{
			cout<<"Friend::removeBlacklistToFriend the heroId is failed to insert insertOffLineList:"<<heroId<<endl;
		}
	}
		
		
	return 0;
}


/****************************************
函数作用  将黑名单列表里删除；
函数参数  heroId 将要删除黑名单的id;
  返回值  int -1:在黑名单里面找不到；
			   0:成功；
******************************************/
int 
Friend::delFromBlacklist(string heroId)
{
	
	map<string,FriendInfo_T>::iterator iter = BlacklistInfo.find(heroId);
	if(iter==BlacklistInfo.end())
		return -1;
		
	BlacklistInfo.erase(iter);
	return 0;
}


/*********************************************************
函数作用  查看好友信息列表；
  返回值  string 好友信息的字符串列表；
		  heroId+heroName+heroPary+heroGrad+ISONLINE+friendLevel;
**********************************************************/	
char* 
Friend::viewFriendlistInfo()
{
	map<string, Hero*>::iterator iter; 	
	friend_info[0]='\0';	
	sprintf(friend_info,"13,4,0,%d",(int)friendsInfo.size());			
	off_friend_info[0]='\0';	

	int len = 0;
	for(map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.begin();heroInfoIter!=friendsInfo.end();++heroInfoIter)
	{		
		iter=heroId_to_pHero.find(heroInfoIter->first);
		if(iter!=heroId_to_pHero.end())	//当前玩家在线；
		{
			len=strlen(friend_info);
			heroInfoIter->second.grad=iter->second->getGradeNow();//更新等级；
			memcpy(heroInfoIter->second.heroName,iter->second->getNickName(),strlen(iter->second->getNickName()));
			memcpy(heroInfoIter->second.party,iter->second->getParty(),strlen(iter->second->getParty()));
			
			if((len+100) > MAX_FRIEND_COUNTS*100)
				break;
			sprintf(friend_info+len,",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		
		}else{//当前玩家不在线；
			len=strlen(off_friend_info);
			if((len+100) > MAX_FRIEND_COUNTS*100)
				break;			
			sprintf(off_friend_info+len,",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,NOT_ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		}
	}
	
	len=strlen(friend_info);
	int off_len=strlen(off_friend_info);
	if((len+off_len) < MAX_FRIEND_COUNTS*100)
	{		
		sprintf(friend_info+len,"%s",off_friend_info);	
	}	
	return friend_info;
}


/***********************************************************
函数作用  查看黑名单信息列表；
  返回值  string 黑名单信息的字符串列表；
		  heroId+heroName+heroPary+heroGrad+ISONLINE+friendLevel;
*******************************************************/	
char* 
Friend::viewBlacklistInfo()
{
	map<string, Hero*>::iterator iter; 
	friend_info[0]='\0';			
	sprintf(friend_info,"13,4,1,%d",(int)BlacklistInfo.size());			
	off_friend_info[0]='\0';
	int len;
	
	for(map<string,FriendInfo_T>::iterator heroInfoIter=BlacklistInfo.begin();heroInfoIter!=BlacklistInfo.end();++heroInfoIter)
	{	
		iter=heroId_to_pHero.find(heroInfoIter->first);
		if(iter==heroId_to_pHero.end())	//当前玩家不在线；
		{
			len=strlen(off_friend_info);
			if((len+100) > MAX_FRIEND_COUNTS*100)
				break;			
		
			sprintf(off_friend_info+len,",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,NOT_ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		}else{//当前玩家在线；
			len=strlen(friend_info);	
			heroInfoIter->second.grad=iter->second->getGradeNow();//更新等级；
			// heroInfoIter->second.friendLevel=iter->second->getFriendLevel();
			memcpy(heroInfoIter->second.heroName,iter->second->getNickName(),strlen(iter->second->getNickName()));
			memcpy(heroInfoIter->second.party,iter->second->getParty(),strlen(iter->second->getParty()));
			heroInfoIter->second.campFlg=iter->second->getCamp();
			if((len+100) > MAX_FRIEND_COUNTS*100)
				break;
			sprintf(friend_info+len,",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		}
	}
	
	len=strlen(friend_info);
	int off_len=strlen(off_friend_info);
	if((len+off_len) < MAX_FRIEND_COUNTS*100)
	{		
		sprintf(friend_info+len,"%s",off_friend_info);	
	}	
	
	return friend_info;
}


/***********************************************************
函数作用  通过好友名字查找好友ID
  返回值  string 好友ID；
*******************************************************/	
string 
Friend::NickNameFindFriendId(string _nickName)
{
	string ret;
	if(_nickName.empty())
		return ret;
		
	map<string,string>::iterator iter = nickNameToheroIdInfo.find(_nickName);
	if(iter != nickNameToheroIdInfo.end())
		return iter->second;
	return ret;
}

/***********************************************************
函数作用  初始化好友度增加限制值
  返回值  bool true成功.false失败；
*******************************************************/	
bool 
Friend::initFriendDegLimit()
{
	if(friendsInfo.empty())
		return false;
		
	for(map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.begin();heroInfoIter!=friendsInfo.end();++heroInfoIter)
	{	
		heroInfoIter->second.friend_grd_limit=DAY_FRIEND_DGR_ADD_COUNTS;
	}
	
	return true;
}

/**
函数作用  增加好友度；type 为TRADE_ADD_FRIEND_DGR交易增加，有限制次数；
						     FLOWERS_ADD_FRIEND_DGR送鲜花增加，无限制增加；
  返回值  bool true成功.false失败；
*/	
bool 
Friend::addFriendDeg(char* friendId,int _type,int _num)
{
	if(friendId==NULL || strlen(friendId)==0 || _num<=0)
		return false;
	
	map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.find(friendId);
	if(heroInfoIter == friendsInfo.end())
		return false;
	
	// cout<<"[XHM TEST] heroInfoIter->second.friend_grd_limit:"<<heroInfoIter->second.friend_grd_limit<<endl;
	// cout<<"[XHM TEST] heroInfoIter->second.friendLevel:"<<heroInfoIter->second.friendLevel<<endl;
	
	if(_type == TRADE_ADD_FRIEND_DGR)
	{
		if(heroInfoIter->second.friend_grd_limit <= 0)
			return false;
		if(heroInfoIter->second.friendLevel+_num>0)
			heroInfoIter->second.friendLevel+=_num;
		heroInfoIter->second.friend_grd_limit--;
		
	}else if(_type == FLOWERS_ADD_FRIEND_DGR)
	{
		if(heroInfoIter->second.friendLevel+_num>0)
			heroInfoIter->second.friendLevel+=_num;
	}else{
		return false;
	}
	
	//TODO可能增加保存到缓存的操作 XHM；
	return true;
}

/**
函数作用  获取好友个数；
返回值 size_t 好友个数；
*/	
size_t Friend::getFrientSize(void)
{
	return nickNameToheroIdInfo.size();
}

//打印测试
void Friend::printFrients() const
{
	for(map<string,string>::const_iterator nick_it = nickNameToheroIdInfo.begin();nick_it != nickNameToheroIdInfo.end();++nick_it)
	{
		cout<<"nickName:"<<nick_it->first<<"  friendId:"<<nick_it->second<<endl;
	}
}


char*
Friend::NickNameFindFriend(const char*_nickName,size_t friendFlg)
{
	friend_info[0]='\0';	
	
	sprintf(friend_info,"13,4,1,%d,%d,%d",1,(int)BlacklistInfo.size() / PAGE_FRIEND_NUM + 1,0);
	
	if(friendFlg == 0)
	{
		friend_info[5] = '0';
	}
	
	if(!_nickName)
	{
		cout<<"Friend::NickNameFindFriend the _nickName is NULL:"<<endl;
		return friend_info;
	}
		
	map<string,string>::iterator iter = nickNameToheroIdInfo.find(_nickName);

	if(iter == nickNameToheroIdInfo.end())
	{
		cout<<"Friend::NickNameFindFriend the _nickName is not find in friend list:"<<endl;
		return friend_info;
	}	
	return findFriendMsg((iter->second).c_str(),friendFlg);
}

char * Friend::findFriendMsg(const char*_heroId,size_t friendFlg)
{
	
	map<string,FriendInfo_T>::iterator friend_it = friendsInfo.find(_heroId);
	
	if(friendFlg == 0)
	{
		if(friend_it == friendsInfo.end())
		{
			cout<<"Friend::NickNameFindFriend the friend_it == friendsInfo.end():"<<_heroId<<endl;
			return friend_info;
		}
	}
	else
	{
		friend_it = BlacklistInfo.find(_heroId);
		if(friend_it == BlacklistInfo.end())
		{
			cout<<"Friend::NickNameFindFriend the friend_it == BlacklistInfo.end():"<<_heroId<<endl;
			return friend_info;
		}
	}
	
	Hero *friendHero = heroid_to_hero(_heroId);	
	
	if(!friendHero)
	{		
		sprintf(friend_info + strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(friend_it->first).c_str(),friend_it->second.heroName,\
		friend_it->second.party,friend_it->second.grad,NOT_ONLINE,friend_it->second.friendLevel,\
		(int)friend_it->second.vipLevel,friend_it->second.campFlg);
		
		friend_info[11] = '1';
		return friend_info;
	}
	
	friend_it->second.grad = friendHero->getGradeNow();//更新等级；
	// friend_it->second.friendLevel=friendHero->getFriendLevel();
	memcpy(friend_it->second.heroName,friendHero->getNickName(),strlen(friendHero->getNickName()));
	memcpy(friend_it->second.party,friendHero->getParty(),strlen(friendHero->getParty()));	
			
	sprintf(friend_info + strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(friend_it->first).c_str(),friend_it->second.heroName,\
	friend_it->second.party,friend_it->second.grad,ONLINE,friend_it->second.friendLevel,\
	(int)friend_it->second.vipLevel,friend_it->second.campFlg);
	
	friend_info[11] = '1';
	return friend_info;
}



void Friend::initOnAndOffLineList(void)
{
	for(map<string,FriendInfo_T>::const_iterator friend_it = friendsInfo.begin();friend_it != friendsInfo.end();++friend_it)
	{
		Hero *friendHero = heroid_to_hero(friend_it->first);
		if(friendHero)
		{
			onLineList.insert(friend_it->first);
		}
		else
		{
			offLineList.insert(friend_it->first);
		}
	}
}

bool Friend::insertOnLineList(const char *friendId)
{
	if(!friendId)
	{
		return false;
	}
	pair<set<string>::iterator,bool> result_it = onLineList.insert(friendId);
	return result_it.second;
}

bool Friend::insertOffLineList(const char *friendId)
{
	if(!friendId)
	{
		return false;
	}
	pair<set<string>::iterator,bool> result_it = offLineList.insert(friendId);
	return result_it.second;
}

bool Friend::eraseOffLineList(const char *friendId)
{
	if(!friendId)
	{
		return false;
	}
	size_t result = offLineList.erase(friendId);
	
	return result == 1;
}

bool Friend::eraseOnLineList(const char *friendId)
{
	if(!friendId)
	{
		return false;
	}
	size_t result = onLineList.erase(friendId);
	
	return result == 1;
}

bool Friend::dealFriendAsist(const char *friendId)
{
	if(!friendId)
	{
		return false;
	}
	Hero *dealHero = heroid_to_hero(friendId);
	
	if(dealHero)
	{
		return eraseOnLineList(friendId);
	}
	
	return eraseOffLineList(friendId);
}


char* 
Friend::viewFriendlistInfo(size_t pageNum)
{
	friend_info[0]='\0';	
	sprintf(friend_info,"13,4,0,%d,%d,%d",(int)pageNum,(int)friendsInfo.size() / PAGE_FRIEND_NUM + 1,PAGE_FRIEND_NUM);	
	
	size_t onLineNum = 0,offLineNum = 0;		
	
	//页数越界
	if(onLineList.size() + offLineList.size() <= PAGE_FRIEND_NUM * (pageNum - 1))
	{
		cout<<"Friend::viewFriendlistInfo(size_t pageNum) all friends num:"<<onLineList.size() + offLineList.size()<<"error pageNum:"<<pageNum<<endl;
		friend_info[11] = '0' + offLineNum + onLineNum;
		return friend_info;
	}
	
	//这页全是下线的人
	if(onLineList.size() <= PAGE_FRIEND_NUM * (pageNum - 1))
	{
		offLineNum = sprintOffLineMsg(PAGE_FRIEND_NUM * (pageNum - 1) - onLineList.size(),PAGE_FRIEND_NUM);	
	}
	
	//这页全是上线的人
	else if(onLineList.size() >= PAGE_FRIEND_NUM * pageNum)
	{
		onLineNum = sprintOnLineMsg((pageNum - 1) * PAGE_FRIEND_NUM,PAGE_FRIEND_NUM);
		
		//如果这页实际上线人数不够，就用下线人数补齐
		if(onLineNum != PAGE_FRIEND_NUM)
		{
			offLineNum = sprintOffLineMsg(0,PAGE_FRIEND_NUM - onLineNum);
		}
	}
	
	else
	{
		//这页既有上线者，也有下线者
		onLineNum = sprintOnLineMsg((pageNum - 1) * PAGE_FRIEND_NUM,PAGE_FRIEND_NUM);
		offLineNum = sprintOffLineMsg(0,PAGE_FRIEND_NUM - onLineNum);
	}
	
	//矫正这页实际人数	
	if(offLineNum + onLineNum < PAGE_FRIEND_NUM)
	{	
		friend_info[11] = '0' + offLineNum + onLineNum;
	}
	
	return friend_info;
}	

size_t Friend::sprintOffLineMsg(size_t position,size_t showPersonNum)
{
	if(position >= offLineList.size())
	{
		cout<<"Friend::sprintOnLineMsg the position :"<<position<<" is more than the onLineList.size():"<<onLineList.size()<<endl;		
		return 0;
	}
	
	size_t offLineNum = 0;
	set<string>::iterator friend_it = offLineList.begin();
	advance(friend_it,position);
	while(friend_it != offLineList.end() && offLineNum < showPersonNum)
	{
		map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.find(*friend_it);
		if(heroInfoIter == friendsInfo.end())
		{
			offLineList.erase(friend_it++);
			continue;
		}
		Hero *offLineHero = heroid_to_hero(*friend_it);	
		if(offLineHero)
		{
			if(insertOnLineList((*friend_it).c_str()))
			{
				cout<<"Friend::viewFriendlistInfo(size_t pageNum) the friend_it is exist:"<<*friend_it<<endl;
			}					
			heroInfoIter->second.grad=offLineHero->getGradeNow();//更新等级；
			heroInfoIter->second.vipLevel=offLineHero->getVipStage();
			heroInfoIter->second.campFlg=offLineHero->getCamp();
			memcpy(heroInfoIter->second.heroName,offLineHero->getNickName(),strlen(offLineHero->getNickName()));
			memcpy(heroInfoIter->second.party,offLineHero->getParty(),strlen(offLineHero->getParty()));
			sprintf(friend_info+strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,NOT_ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
			offLineList.erase(friend_it++);
			++offLineNum;
			continue;
		}
			
		sprintf(friend_info+strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
		heroInfoIter->second.party,heroInfoIter->second.grad,NOT_ONLINE,heroInfoIter->second.friendLevel,\
		(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		++friend_it;
		++offLineNum;
	}
	return offLineNum;
}

size_t Friend::sprintOnLineMsg(size_t position,size_t showPersonNum)
{

	if(position >= onLineList.size())
	{
		cout<<"Friend::sprintOnLineMsg the position :"<<position<<" is more than the onLineList.size():"<<onLineList.size()<<endl;
		return 0;
	}
	
	set<string>::iterator friend_it = onLineList.begin();
	advance(friend_it,position);		
	size_t onLineNum = 0;
	
	while(friend_it != onLineList.end() && onLineNum < showPersonNum)
	{
		Hero *onLineHero = heroid_to_hero(*friend_it);
			
		if(!onLineHero)
		{
			if(insertOffLineList((*friend_it).c_str()))
			{
				cout<<"Friend::sprintOnLineMsg warningthe friend_it is exist:"<<*friend_it<<endl;
			}
				
			onLineList.erase(friend_it++);
			continue;
		}
						
		map<string,FriendInfo_T>::iterator heroInfoIter=friendsInfo.find(*friend_it);
		if(heroInfoIter == friendsInfo.end())
		{
			onLineList.erase(friend_it++);
			continue;
		}
		heroInfoIter->second.grad=onLineHero->getGradeNow();//更新等级；
		heroInfoIter->second.vipLevel=onLineHero->getVipStage();
		heroInfoIter->second.campFlg=onLineHero->getCamp();
		memcpy(heroInfoIter->second.heroName,onLineHero->getNickName(),strlen(onLineHero->getNickName()));
		memcpy(heroInfoIter->second.party,onLineHero->getParty(),strlen(onLineHero->getParty()));
			
		sprintf(friend_info+strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
		heroInfoIter->second.party,heroInfoIter->second.grad,ONLINE,heroInfoIter->second.friendLevel,\
		(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		++friend_it;
		++onLineNum;
	}
	return onLineNum;
}

char* 
Friend::viewBlacklistInfo(size_t pageNum)
{
	map<string, Hero*>::iterator iter; 
	friend_info[0]='\0';
	
	sprintf(friend_info,"13,4,1,%d,%d,%d",(int)pageNum,(int)BlacklistInfo.size() / PAGE_FRIEND_NUM + 1,PAGE_FRIEND_NUM);
	
	size_t balckNum = 0;
	
	//页数越界
	if(BlacklistInfo.size() <= PAGE_FRIEND_NUM * (pageNum - 1))
	{
		cout<<"Friend::viewBlacklistInfo(size_t pageNum) all friends num:"<<BlacklistInfo.size() <<"error pageNum:"<<pageNum<<endl;
		friend_info[11] = '0';
		return friend_info;
	}
	map<string,FriendInfo_T>::iterator heroInfoIter = BlacklistInfo.begin();
	
	advance(heroInfoIter,PAGE_FRIEND_NUM * (pageNum - 1));
	
	while(heroInfoIter != BlacklistInfo.end() && balckNum < PAGE_FRIEND_NUM)
	{	
		Hero *blackHero = heroid_to_hero(heroInfoIter->first);
		if(!blackHero)
		{
			sprintf(friend_info + strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,NOT_ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		}
		else
		{
			heroInfoIter->second.grad=blackHero->getGradeNow();//更新等级；
			// heroInfoIter->second.friendLevel=blackHero->getFriendLevel();
			heroInfoIter->second.vipLevel=blackHero->getVipStage();
			heroInfoIter->second.campFlg=blackHero->getCamp();
			memcpy(heroInfoIter->second.heroName,blackHero->getNickName(),strlen(blackHero->getNickName()));
			memcpy(heroInfoIter->second.party,blackHero->getParty(),strlen(blackHero->getParty()));
			
			sprintf(friend_info + strlen(friend_info),",%s,%s,%s,%d,%d,%d,%d,%d",(heroInfoIter->first).c_str(),heroInfoIter->second.heroName,\
			heroInfoIter->second.party,heroInfoIter->second.grad,ONLINE,heroInfoIter->second.friendLevel,\
			(int)heroInfoIter->second.vipLevel,heroInfoIter->second.campFlg);
		}
		++heroInfoIter;
		++balckNum;
	}
	
	//矫正实际人数
	if(heroInfoIter == BlacklistInfo.end() && balckNum != PAGE_FRIEND_NUM)
	{
		friend_info[11] = '0' + balckNum;
	}
	
	return friend_info;
}


bool Friend::isInBlack(const char* friendHeroId) const
{
	return BlacklistInfo.find(friendHeroId) != BlacklistInfo.end();
}

bool Friend::isInFriend(const char* friendHeroId) const
{
	return friendsInfo.find(friendHeroId) != friendsInfo.end();
}