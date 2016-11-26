/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server好友逻辑操作客户端交互；

**************************************************/
#include "hero.h"
#include "friendAnalyze.h"
#include "offline_unhandle_event.h"
//缓存服务器管理类
#include "my_mem_group.h"
//用于昵称检查缓存的操作类指针实例引用声明
// extern MyMemcache* mem_operate;
extern MyMemGroup* mem_group;

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;

static char msg_friend[200];
static char extern_msg_friend[200];
extern map<string, Hero*> heroId_to_pHero;	
extern MyMemcache* mem_operate_nickname_inspection;

bool asistOneKeyAppFriend(Hero* ownerHero,const char *applyHeroId);

bool ResponseApplyOneKeyAsist(Hero *ownerHero,const char *responseHeroId,const char *agreeFlag);
/**
	函数作用 申请好友信息解析；
	消息类型 13,0,myHeroId,friendHeroId;
*/
void 
analyzeFriendApply(char *buffers)
{
	map<string,Hero*>::iterator iter;
	int fd = sock_fd;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* my_hero_id);
	MSG_CHAR_END(char* desHeroId);
	
	sprintf(msg_friend,"13,0,%s,%s",my_hero_id,pg_hero->getNickName());

	if(pg_hero->getFriendInfo() == NULL)
	{
		return;
	}
	
	int ret = pg_hero->getFriendInfo()->applyForFriend(desHeroId);
	//请求失败
	if(ret < 0)
	{
		cout<<"[XHM WARNING]:int the friendAnalyze.cpp,the friend is in you friend list or black list,we just return!"<<endl;
		//已经是好友
		if(ret == -2)
			sprintf(extern_msg_friend,"13,8,2");	
			
		//黑名单		
		else if(ret == -3)
			sprintf(extern_msg_friend,"13,8,3");	
		//数据错误
		else 
			sprintf(extern_msg_friend,"13,8,4");	
			
		send_msg(fd,extern_msg_friend);				
		return;
	}
	
	iter=heroId_to_pHero.find(desHeroId);
	
	//找不到，下线加
	if(iter==heroId_to_pHero.end())//如果找不到，对下线英雄加好友，将消息放到好友管理器，等到上线再发送；
	{
		sprintf(extern_msg_friend,"13,8,1");			
		send_msg(fd,extern_msg_friend);			
		UNHANDLE_FUNC(desHeroId,9,msg_friend);
        return;
	}
	
	//自己不能加自己
	if(iter->second == pg_hero)//加自己为好友；错误返回；
	{
		sprintf(extern_msg_friend,"13,8,5");			
		send_msg(fd,extern_msg_friend);		
		return;	
	}
	
	/*
	*这里最好把好友信息加到预加好友信息列表;
	*/
	
	//对方数据异常
	if( iter->second->getFriendInfo() == NULL)
	{
		sprintf(extern_msg_friend,"13,8,4");	
		send_msg(fd,extern_msg_friend);			
		return;
	}
		
	ret = iter->second->getFriendInfo()->applyForFriend(my_hero_id);
	if(ret < 0 )
	{
		//已经是好友
		if(ret == -2)
		{
			//反加
			ret = pg_hero->getFriendInfo()->add2Friendlist(pg_hero->getArea(), iter->second);		
			sprintf(extern_msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,desHeroId,iter->second->getNickName(),iter->second->getParty(),\
			iter->second->getGradeNow(),ONLINE,iter->second->getFriendLevel(),iter->second->getCamp());		
			
			send_msg(fd,extern_msg_friend);	
			
			sprintf(extern_msg_friend,"13,8,6");	
			send_msg(fd,extern_msg_friend);			
		}
		//黑名单
		else if(ret == -3)
		{
			//cout<<"[XHM TEST] The friend in you black list(friendAnalyze.cpp)!"<<endl;
			sprintf(extern_msg_friend,"13,8,7");	
			send_msg(fd,extern_msg_friend);				
		}
		//数据错误
		else
		{
			sprintf(extern_msg_friend,"13,8,4");	
			send_msg(fd,extern_msg_friend);				
		}
		
		return;
	}
	
	//发送请求成功
	sprintf(extern_msg_friend,"13,8,0");	
	send_msg(fd,extern_msg_friend);	
	
	//发送对方相应
	send_msg(iter->second->getFd(),msg_friend);
}


/**
	函数作用 响应好友申请信息解析；
	消息类型 13,1,myHeroId,applyFriendHeroId;
*/
void 
analyzeResponseFriendApply(char *buffers)
{
	/*
	*解析客户端发送过来数据，并且将发送给客户端的数据保存到msg变量里面；
	*/
	map<string,Hero*>::iterator iter;
	int ret;
	int fd=sock_fd;

	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* agreeFlag);
	MSG_CHAR(char* my_hero_id);
	MSG_CHAR_END(char* desHeroId);	
	
	iter=heroId_to_pHero.find(desHeroId);
	// cout<<"[XHM MSG] FLAG FLAG agreeFlag[0]:"<<agreeFlag[0]-'0'<<endl;
	if(agreeFlag[0]=='0')
	{
		// cout<<"[XHM TEST] Request refuse to be friends(friendAnalyze.cpp)!"<<endl;
		if(iter!=heroId_to_pHero.end())	
		{
			sprintf(extern_msg_friend,"13,9,1,%s",pg_hero->getNickName());
			send_msg(iter->second->getFd(),extern_msg_friend);	
		}			
		return;
	}
	else if(agreeFlag[0]=='1')
	{
		if(iter==heroId_to_pHero.end())//如果请求者找不到实例，通过memcached找到desHeroId基本信息，构建tempInfo信息；
		{
			int size;
			int where = 0;
			MemHero* desHeroData =  (MemHero*)mem_group->get_data(desHeroId, &size, &where);
			if(NULL != desHeroData)
			{	
				char nickName[IDL] = {0};
				snprintf(nickName, 50, "%s", desHeroData->nickName);				
			#if 1
				if(where != pg_hero->getArea())	//新加好友与自己不是一个服,在昵称后加上区号
				{
					snprintf(nickName+strlen(nickName), 50, "_%d", where);
				}
			#endif
			
				FriendInfo_T tempInfo(nickName, desHeroData->basicHeroData.party,desHeroData->level,\
				desHeroData->friendLevel,desHeroData->vipDailyData.stage,desHeroData->camp,DAY_FRIEND_DGR_ADD_COUNTS);
				
				ret = pg_hero->getFriendInfo()->add2Friendlist2(desHeroId,tempInfo);
				sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d,%d",ret,my_hero_id,desHeroData->nickName,desHeroData->basicHeroData.party,\
				desHeroData->level,ONLINE,desHeroData->friendLevel,desHeroData->vipDailyData.stage,desHeroData->camp);		
				
				memset(nickName, 0, 50);
				snprintf(nickName, 50, "%s", pg_hero->getNickName());
				
			#if 1
				if(pg_hero->getArea() != where)	//自己和新加好友不在同一个服,构建FriendInfo_T时，在自己昵称后加上区号
				{
					snprintf(nickName+strlen(nickName), 50, "_%d", pg_hero->getArea());
				}
			#endif
			
				FriendInfo_T friendInfo(nickName,pg_hero->getParty(),pg_hero->getGradeNow(),pg_hero->getFriendLevel(),pg_hero->getVipStage(),\
				pg_hero->getCamp());
				UnhandleAddFriend_T tempEmailData(my_hero_id,friendInfo);	//将自己的信息加到管理器，待对方角色上线时处理；
				UNHANDLE_FUNC(desHeroId,11,tempEmailData);
				
				if(pg_hero->getFriendInfo()->insertOffLineList(desHeroId))
				{
					cout<<"the friend name："<<nickName<<" just add is off Line:"<<pg_hero->getIdentity()<<endl;
				}
			}
			
			if (desHeroData->targetItem[1][0]==0)
			{
				desHeroData->targetItem[1][0]=1;
				if (desHeroData->targetFinishNumber[1]!=-1)
				{
					desHeroData->targetFinishNumber[1]++;
				}	
			}
		}
		else
		{					
			/*
			*如果请求者找到实例，双方加成好友；	
			*/	
			if(iter->second->getFriendInfo())	
			{
				ret=iter->second->getFriendInfo()->add2Friendlist(iter->second->getArea(), pg_hero);		
				sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,my_hero_id,pg_hero->getNickName(),pg_hero->getParty(),\
				pg_hero->getGradeNow(),ONLINE,pg_hero->getFriendLevel(),pg_hero->getVipStage());				
				send_msg(iter->second->getFd(),msg_friend);
			
				ret = pg_hero->getFriendInfo()->add2Friendlist(pg_hero->getArea(), iter->second);	
				sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,desHeroId,iter->second->getNickName(),iter->second->getParty(),\
				iter->second->getGradeNow(),ONLINE,iter->second->getFriendLevel(),iter->second->getVipStage());	
				//cout<<"[XHM TEST] Add friends2(request hero online friendAnalyze.cpp) msg:"<<msg<<endl;
				sprintf(extern_msg_friend,"13,9,0,%s",pg_hero->getNickName());
				send_msg(iter->second->getFd(),extern_msg_friend);	
	
				iter->second->getFriendInfo()->saveFriendInfoToMem(iter->second);//存储好友；
				
				if(pg_hero->getFriendInfo()->insertOnLineList(desHeroId))
				{
					cout<<"the friend name ："<<iter->second->getNickName()<<" just add is on Line:"<<pg_hero->getIdentity()<<endl;
				}
				
				if(iter->second->getFriendInfo()->insertOnLineList(pg_hero->getIdentity()))
				{
					cout<<"the friend name ："<<pg_hero->getNickName()<<" just add is on Line:"<<iter->second->getIdentity()<<endl;
				}
				iter->second->updataSingleTarget(1,0);
			}
		}
		
			
		//jolly add wulintarget 12.4 start
		pg_hero->updataSingleTarget(1,0);
		//jolly add wulintarget 12.4 end
	}
	else
	{
		
		cout<<"[XHM WARNING]:in the friendAnalyze.cpp--->agree to be friend ,But type Error!"<<agreeFlag<<endl;	
		ret=-4;
		sprintf(msg_friend,"13,1,%d",ret);
	}
	if(pg_hero->getFriendInfo())
		pg_hero->getFriendInfo()->saveFriendInfoToMem(pg_hero);//存储好友；
	
	
	/*好友个数超过20个，给头衔，手足之情*/
	if(pg_hero->getFriendInfo()->getFrientSize() == 20)
	{
		pg_hero->addTitle("T023");
	}
	
	//cout<<"[XHM TEST]  the send msg(friendAnalyze.cpp): "<<msg<<endl;
	send_msg(fd,msg_friend);
}


/**
	函数作用 好友列表操作信息解析；
	消息类型 13,2，type(1,删除 2，拉入黑名单),myHeroId,friendHeroId；
*/
void 
FriendlistOperate(char *buffers)
{
	int fd=sock_fd;
	map<string,Hero*>::iterator iter;
	int ret=-1;//返回状态；

	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* operateType);
	MSG_CHAR(char* my_hero_id);
	MSG_CHAR_END(char* desHeroId);	

	iter=heroId_to_pHero.find(desHeroId);
	
	switch(operateType[0])
	{
		case '0':	//1,删除；
			ret=pg_hero->getFriendInfo()->delFromFriendlist(desHeroId);
			//cout<<"[XHM TEST] Friendlist operation1 delFromFriendlist(friendAnalyze.cpp): "<<ret<<endl;
			break;
		case '1':	// 2，拉入黑名单；
			ret=pg_hero->getFriendInfo()->add2Blacklist(desHeroId);
			//cout<<"[XHM TEST] Friendlist operation2 add2Blacklist(friendAnayze.cpp): "<<ret<<endl;
			if(iter==heroId_to_pHero.end()) 
			{
				UNHANDLE_FUNC(desHeroId,10,my_hero_id);
			}
			else
			{	//如果被操作者在线处理；
				iter->second->getFriendInfo()->delFromFriendlist(my_hero_id);
				//cout<<"[XHM TEST] Friendlist operation2 delFromFriendlist(friendAnayze.cpp): "<<ret<<endl;
			}
			break;
		default:	// 其他，不做任何处理；	
			cout<<"[XHM WARNING]:The friendoperation Type ERROR(friendAnayze.cpp):"<<operateType<<endl;
			break;
	}
	send_msg(fd,pg_hero->getFriendInfo()->viewFriendlistInfo(1));
#if 0
	if(pg_hero->getFriendInfo())
		pg_hero->getFriendInfo()->saveFriendInfoToMem(pg_hero);//存储好友；
	sprintf(msg_friend,"13,2,%s,%d",operateType,ret);
	send_msg(fd,msg_friend);
#endif	
}


/**
	函数作用 黑名单列表操作信息解析；
	消息类型 13,3，type(1，删除，2，移出黑名单),myHeroId,friendHeroId；
*/
void 
BlacklistOperate(char *buffers)
{
	int fd=sock_fd;
	int ret=-1;	//返回状态；
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* operateType);
	MSG_CHAR(char* my_hero_id);
	MSG_CHAR_END(char* desHeroId);	
	
	switch(operateType[0])
	{
		case '0'://	1,删除；
			ret=pg_hero->getFriendInfo()->delFromBlacklist(desHeroId);			
			//cout<<"[XHM TEST] Blacklist operation1 delFromBlacklist(friendAnayze.cpp):"<<ret<<endl;
			break;
		case '1':// 2，拉出黑名单；
			ret=pg_hero->getFriendInfo()->removeBlacklistToFriend(desHeroId);
			//cout<<"[XHM TEST] Blacklist operation2 removeBlacklistToFriend(friendAnayze.cpp):"<<ret<<endl;
			break;
		default:// 其他，不做任何处理；
			cout<<"[XHM WARNING] Blacklist operation Type Error(friendAnayze.cpp):"<<operateType<<endl;
			break;
	}
	
	send_msg(fd,pg_hero->getFriendInfo()->viewBlacklistInfo(1));
	
#if 0
	if(pg_hero->getFriendInfo())
		pg_hero->getFriendInfo()->saveFriendInfoToMem(pg_hero);			//存储好友；
	sprintf(msg_friend,"13,3,%s,%d",operateType,ret);	
	send_msg(fd,msg_friend);
#endif
}


/**
	函数作用 黑名单列表操作信息解析；
	消息类型 13,4，type;(1，好友信息 2，黑名单信息),myHeroId,friendHeroId；
*/
void viewFriendInfo(char *buffers) 	
{	
	int fd=sock_fd;
	int page;
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_INT(page);
	MSG_CHAR(char* operateType);
	MSG_CHAR_END(char* my_hero_id);		
		
	switch(operateType[0])
	{
		case '0'://	1,好友列表；
			//cout<<"[XHM TEST] Look for the friend list(friendAnayze.cpp)"<<endl;
			send_msg(fd,pg_hero->getFriendInfo()->viewFriendlistInfo(page));
			break;
		case '1':// 2，黑名单列表信息；
			//cout<<"[XHM TEST] Look for the blacklist(friendAnayze.cpp)"<<endl;
			send_msg(fd,pg_hero->getFriendInfo()->viewBlacklistInfo(page));
			break;
		default:// 其他，不做任何处理；
			cout<<"[XHM WARNING]:Look for friend info type ERROR(friendAnayze.cpp)!"<<endl;
			break;
	}
	
	if(pg_hero->getFriendInfo())
		pg_hero->getFriendInfo()->saveFriendInfoToMem(pg_hero);			//存储好友；
	//cout<<"[XHM TEST] The viewFriendInfo(friendAnayze.cpp): "<<msg<<endl;
}


/**
	查找好友（在好友列表中）
*/
void findFriendInfo(char *buffers) 	
{	
	int friendFlg;
	int fd=sock_fd;
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_INT(friendFlg);		
	MSG_CHAR_END(char* friend_NickName);		
	if(!pg_hero->getFriendInfo())
	{
		return;
	}
	send_msg(fd,pg_hero->getFriendInfo()->NickNameFindFriend(friend_NickName,friendFlg));
}

/**
	世界查找
*/
void findFriend(char *buffers) 	
{	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(char* friend_NickName);		
	
 	int nickname_inspection_size = 0;
	char* findHeroId = mem_operate_nickname_inspection->get_mem_data(friend_NickName, &nickname_inspection_size);
	int onLine = 0;
	if(!findHeroId)
	{
		sprintf(msg_friend,"13,10,0,%s",friend_NickName);
		send_msg(pg_hero->getFd(),msg_friend);
		return;
	}
	
	Hero *findHero = heroid_to_hero(findHeroId);
	MemHero *memHero;
	if(!findHero)
	{
		int size = 0;
		int where = 0;
		char *pmem = mem_group->get_data(findHeroId, &size, &where);
		if(pmem == NULL)
		{
			sprintf(msg_friend,"13,10,0,%s",friend_NickName);
			send_msg(pg_hero->getFd(),msg_friend);
			return;
		}
	
		memHero = (MemHero *)malloc(sizeof(MemHero));
		memset(memHero, '\0', sizeof(MemHero));
    
		size = size < sizeof(MemHero) ? size : sizeof(MemHero);
		memcpy(memHero, pmem, size);
		free(pmem);
	}
	else
	{
		memHero = findHero->memHero;
		onLine = 1;
	}
	sprintf(msg_friend,"13,10,1,%s,%s,%s,%d,%d,%d,%d,%d",findHeroId,friend_NickName,memHero->basicHeroData.party,\
	memHero->level,onLine,memHero->friendLevel,memHero->vipDailyData.stage,memHero->camp);
	send_msg(pg_hero->getFd(),msg_friend);
}

//一键申请好友
void analyzeFriendApplyByOneKey(char *buffers)
{
	int fd = sock_fd;
	int num;
	vector<string>friendsHeroIdSet;
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* my_hero_id);
	MSG_INT(num);
	
	for(int i = 0;i < num;++i)
	{
		MSG_CHAR_END(char* desHeroId);
		friendsHeroIdSet.push_back(desHeroId);
	}
	
	sprintf(msg_friend,"13,0,%s,%s",my_hero_id,pg_hero->getNickName());

	if(pg_hero->getFriendInfo() == NULL || friendsHeroIdSet.empty())
	{
		return;
	}
	
	for(vector<string>::iterator appId_it = friendsHeroIdSet.begin();appId_it != friendsHeroIdSet.end();++appId_it)
	{
		asistOneKeyAppFriend(pg_hero,(*appId_it).c_str());
	}
}


bool asistOneKeyAppFriend(Hero* ownerHero,const char *applyHeroId)
{
	memset(extern_msg_friend,'\0',sizeof(extern_msg_friend));
	if(!ownerHero || !applyHeroId)
	{
		return false;
	}
	
	int ret = ownerHero->getFriendInfo()->applyForFriend(applyHeroId);
	//请求失败
	if(ret < 0)
	{
		cout<<"[XHM WARNING]:int the friendAnalyze.cpp,the friend is in you friend list or black list,we just return!"<<endl;
		//已经是好友
		if(ret == -2)
		{
			sprintf(extern_msg_friend,"13,8,2");
			return true;
		}
			
		//黑名单		
		else if(ret == -3)
		{
			sprintf(extern_msg_friend,"13,8,3");	
			return false;
		}
		
		//数据错误		
		else 
		{
			sprintf(extern_msg_friend,"13,8,4");				
			send_msg(ownerHero->getFd(),extern_msg_friend);	
			return false;
		}
	}
	
	Hero *appHero = heroid_to_hero(applyHeroId);
			
	if(!appHero)
	{
		sprintf(extern_msg_friend,"13,8,1");			
		send_msg(ownerHero->getFd(),extern_msg_friend);			
		UNHANDLE_FUNC(applyHeroId,9,msg_friend);
		return true;
	}
		
	//自己不能加自己
	if(appHero == pg_hero)//加自己为好友；错误返回；
	{
		sprintf(extern_msg_friend,"13,8,5");			
		send_msg(ownerHero->getFd(),extern_msg_friend);		
		return true;
	}
			
	//对方数据异常
	if(appHero->getFriendInfo() == NULL)
	{
		sprintf(extern_msg_friend,"13,8,4");	
		send_msg(ownerHero->getFd(),extern_msg_friend);			
		return false;
	}
		
	ret = appHero->getFriendInfo()->applyForFriend(ownerHero->getIdentity());
	if(ret < 0 )
	{
		//已经是好友
		if(ret == -2)
		{
			//反加
			ret = pg_hero->getFriendInfo()->add2Friendlist(pg_hero->getArea(), appHero);		
			sprintf(extern_msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,applyHeroId,appHero->getNickName(),\
			appHero->getParty(),appHero->getGradeNow(),ONLINE,appHero->getFriendLevel(),appHero->getCamp());			
			send_msg(ownerHero->getFd(),extern_msg_friend);				
			sprintf(extern_msg_friend,"13,8,6");	
			send_msg(ownerHero->getFd(),extern_msg_friend);		
			return true;
		}
		//黑名单
		else if(ret == -3)
		{
			sprintf(extern_msg_friend,"13,8,7");	
			send_msg(ownerHero->getFd(),extern_msg_friend);		
			return false;
		}
		//数据错误
		else
		{
			sprintf(extern_msg_friend,"13,8,4");	
			send_msg(ownerHero->getFd(),extern_msg_friend);	
			return false;
		}		
	}
			
	//发送请求成功
	sprintf(extern_msg_friend,"13,8,0");	
	send_msg(ownerHero->getFd(),extern_msg_friend);	
			
	//发送对方相应
	send_msg(ownerHero->getFd(),msg_friend);
	
	return true;
}


void analyzeResponseFriendApplyOneKey(char *buffers)
{
	map<string,Hero*>::iterator iter;
	int num;
	vector<string> applyIdVec;
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* agreeFlag);
	MSG_CHAR(char* my_hero_id);
	MSG_INT(num);
	
	for(int i = 0;i < num;++i)
	{
		MSG_CHAR(char* desHeroId);
		applyIdVec.push_back(desHeroId);
	}		
	
	for(vector<string>::const_iterator apply_it = applyIdVec.begin();apply_it != applyIdVec.begin();++apply_it)
	{
		ResponseApplyOneKeyAsist(pg_hero,(*apply_it).c_str(),agreeFlag);
	}
		
	
	/*好友个数超过20个，给头衔，手足之情*/
	if(pg_hero->getFriendInfo()->getFrientSize() == 20)
	{
		pg_hero->addTitle("T023");
	}
	
	//jolly add wulintarget 12.4 start
	pg_hero->updataSingleTarget(1,0);
	//jolly add wulintarget 12.4 end
}



bool ResponseApplyOneKeyAsist(Hero *ownerHero,const char *responseHeroId,const char *agreeFlag)
{
	int ret;
	
	if(!ownerHero || !responseHeroId)
	{
		return false;
	}
	
	Hero* applyHero = heroid_to_hero(responseHeroId);		
		
	if(agreeFlag[0]=='0')
	{
		if(!applyHero)
		{
			return false;			
		}
			
		sprintf(extern_msg_friend,"13,9,1,%s",ownerHero->getNickName());
		send_msg(applyHero->getFd(),extern_msg_friend);	
		return false;
	}
	
	else if(agreeFlag[0]=='1')
	{
		if(!applyHero)//如果请求者找不到实例，通过memcached找到desHeroId基本信息，构建tempInfo信息；
		{
			int size;
			int where = 0;
			MemHero* desHeroData =  (MemHero*)mem_group->get_data(responseHeroId, &size, &where);
			
			if(!desHeroData)
			{
				return false;
			}
			
			
			char nickName[IDL] = {0};
			snprintf(nickName, 50, "%s", desHeroData->nickName);				
		#if 1
			if(where != ownerHero->getArea())	//新加好友与自己不是一个服,在昵称后加上区号
			{
				snprintf(nickName+strlen(nickName), 50, "_%d", where);
			}
		#endif
		
			FriendInfo_T tempInfo(nickName, desHeroData->basicHeroData.party,desHeroData->level,\
			desHeroData->friendLevel,desHeroData->vipDailyData.stage,desHeroData->camp,DAY_FRIEND_DGR_ADD_COUNTS);
				
			ret = ownerHero->getFriendInfo()->add2Friendlist2(responseHeroId,tempInfo);
			sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d,%d",ret,ownerHero->getIdentity(),desHeroData->nickName,\
			desHeroData->basicHeroData.party,desHeroData->level,ONLINE,desHeroData->friendLevel,\
			desHeroData->vipDailyData.stage,desHeroData->camp);		
				
			memset(nickName, 0, 50);
			snprintf(nickName, 50, "%s", ownerHero->getNickName());
				
		#if 1
			if(ownerHero->getArea() != where)	//自己和新加好友不在同一个服,构建FriendInfo_T时，在自己昵称后加上区号
			{
				snprintf(nickName+strlen(nickName), 50, "_%d", ownerHero->getArea());
			}
		#endif
			
			FriendInfo_T friendInfo(nickName,ownerHero->getParty(),ownerHero->getGradeNow(),ownerHero->getFriendLevel(),\
			ownerHero->getVipStage(),ownerHero->getCamp());
			
			UnhandleAddFriend_T tempEmailData(ownerHero->getIdentity(),friendInfo);	//将自己的信息加到管理器，待对方角色上线时处理；
			UNHANDLE_FUNC(responseHeroId,11,tempEmailData);
				
			if(ownerHero->getFriendInfo()->insertOffLineList(responseHeroId))
			{
				cout<<"the friend name："<<nickName<<" just add is off Line:"<<ownerHero->getIdentity()<<endl;
			}
		}
			
		if(!applyHero->getFriendInfo())
		{
			return false;
		}
			
		ret=applyHero->getFriendInfo()->add2Friendlist(applyHero->getArea(), ownerHero);		
		sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,ownerHero->getIdentity(),ownerHero->getNickName(),ownerHero->getParty(),\
		ownerHero->getGradeNow(),ONLINE,ownerHero->getFriendLevel(),ownerHero->getVipStage());				
		send_msg(applyHero->getFd(),msg_friend);
			
		ret = ownerHero->getFriendInfo()->add2Friendlist(ownerHero->getArea(), applyHero);	
		sprintf(msg_friend,"13,1,%d,%s,%s,%s,%d,%d,%d,%d",ret,responseHeroId,applyHero->getNickName(),applyHero->getParty(),\
		applyHero->getGradeNow(),ONLINE,applyHero->getFriendLevel(),applyHero->getVipStage());	
		
		sprintf(extern_msg_friend,"13,9,0,%s",ownerHero->getNickName());
		send_msg(applyHero->getFd(),extern_msg_friend);	
	
		applyHero->getFriendInfo()->saveFriendInfoToMem(applyHero);//存储好友；
				
		if(ownerHero->getFriendInfo()->insertOnLineList(responseHeroId))
		{
			cout<<"the friend name ："<<applyHero->getNickName()<<" just add is on Line:"<<ownerHero->getIdentity()<<endl;
		}
				
		if(applyHero->getFriendInfo()->insertOnLineList(ownerHero->getIdentity()))
		{
			cout<<"the friend name ："<<ownerHero->getNickName()<<" just add is on Line:"<<applyHero->getIdentity()<<endl;
		}		
	}
	else
	{
		cout<<"[XHM WARNING]:in the friendAnalyze.cpp--->agree to be friend ,But type Error!"<<agreeFlag<<endl;	
		ret=-4;
		sprintf(msg_friend,"13,1,%d",ret);
		return false;
	}
	
	if(ownerHero->getFriendInfo())
	{
		ownerHero->getFriendInfo()->saveFriendInfoToMem(applyHero);//存储好友；
	}
	
	send_msg(ownerHero->getFd(),msg_friend);
	
	return true;
}

