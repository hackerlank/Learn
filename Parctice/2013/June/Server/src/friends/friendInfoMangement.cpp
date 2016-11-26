#include "friendInfoManagement.h"
#include "hero.h"


void 
FriendInfoManagement::heroOnlineProces(Hero* myHero)
{
	if(NULL == myHero)
		return;
		
	/*消息发送处理*/
	iterMsg=heroId2msg.find(myHero->getIdentity());
	if(iterMsg != heroId2msg.end())
	{
		for(int i=0;i<(iterMsg->second).size();i++)
		{
			send_msg(myHero->getFd(),const_cast<char*>((iterMsg->second)[i].c_str()));
		}
		heroId2msg.erase(iterMsg);
	}

	/*好友删除处理*/
	iterDelFriend=heroIdDelFriend.find(myHero->getIdentity());
	if(iterDelFriend != heroIdDelFriend.end())
	{
		for(int i=0;i<(iterDelFriend->second).size();i++)
		{
			myHero->getFriendInfo()->delFromFriendlist((iterDelFriend->second)[i]);	
		}
		heroIdDelFriend.erase(iterDelFriend);
	}

	/*好友添加处理*/
	iterAddFriend=heroIdAddFriend.find(myHero->getIdentity());
	if(iterAddFriend != heroIdAddFriend.end())
	{
		for(int i=0;i<(iterAddFriend->second).size();i++)
		{
			myHero->getFriendInfo()->add2Friendlist2(myHero->getIdentity(),(iterAddFriend->second)[i]);	
		}
		heroIdAddFriend.erase(iterAddFriend);
	}

}

bool  
FriendInfoManagement::addHeroMsgSend(string heroId,string msg)
{
	iterMsg=heroId2msg.find(heroId);
	if(iterMsg==heroId2msg.end())
	{
		vector<string> temp;
		vector<string>::iterator it;
		it = temp.begin();
		it = temp.insert ( it,msg);
		heroId2msg.insert(IDVAL_MSG(heroId,temp));	
	}else{
		vector<string> temp=iterMsg->second;
		vector<string>::iterator it;
		it = temp.end();
		temp.insert (it,msg);
		heroId2msg.insert(IDVAL_MSG(heroId,temp));	
	}
	
}


bool  
FriendInfoManagement::addHeroDelFriend(string srcheroId,string decheroId)
{
	iterDelFriend=heroIdDelFriend.find(srcheroId);
	if(iterDelFriend==heroIdDelFriend.end())
	{
		vector<string> temp;
		vector<string>::iterator it;
		it = temp.begin();
		temp.insert ( it,decheroId);
		heroIdDelFriend.insert(IDVAL_DELFRIEND(srcheroId,temp));	
	}else{
		vector<string> temp=iterDelFriend->second;
		vector<string>::iterator it;
		it = temp.end();
		temp.insert ( it,decheroId);
		heroIdDelFriend.insert(IDVAL_DELFRIEND(srcheroId,temp));	
	}
	
}


bool  
FriendInfoManagement::addHeroAddfriend(string heroId,FriendInfo_T friendInfo)
{
	iterAddFriend=heroIdAddFriend.find(heroId);
	if(iterAddFriend==heroIdAddFriend.end())
	{
		vector<FriendInfo_T> temp;
		vector<FriendInfo_T>::iterator it;
		it = temp.begin();
		temp.insert (it,friendInfo);
		heroIdAddFriend.insert(IDVAL_ADDFRIEND(heroId,temp));	
	}else{
		vector<FriendInfo_T> temp=iterAddFriend->second;
		vector<FriendInfo_T>::iterator it;
		it = temp.end();
		temp.insert (it,friendInfo);
		heroIdAddFriend.insert(IDVAL_ADDFRIEND(heroId,temp));	
	}
}