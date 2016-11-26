/*
		文件类型：实现文件
		文件名称：whisper.cpp
		文件作用：实现私聊的消息发送；
		修改人：xhm
		修改时间：2012.8.30 13:56
*/

#include"chat.h"
//缓存服务器管理类
#include "my_mem_group.h"

#include"chatGroupManager.h"
#include"chatGroup.h"

extern ChatGroupManager *chatManager;
extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
extern set<string> ban_speak;
extern map<string, Hero*> heroId_to_pHero;

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;
extern MyMemGroup* mem_group;

static char whisperInfo[2048];



void whisper(char *buffers)
{	
    /*
	   解析客户端发送过来数据，并且将发送给客户端的数据保存到msg变量里面；
    */
	Hero* wisperHero=NULL;//私聊对象的hero实例；

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(char* my_hero_id);//获取发送者信息；
	MSG_CHAR(char* desHeroId);//获取私聊对象的ID；
	MSG_CHAR_END(char* msgInfo);//获取消息内容；
	
	/*add chenzhen 20130312,自己不能邀请自己聊天*/
	if(strncmp(my_hero_id,desHeroId,strlen(my_hero_id)) == 0)
	{
		snprintf(whisperInfo,2047,"4,23,7");//自己不能邀请自己聊天；
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	if(MAX_MESSAGE_DATA_LEN < strlen(msgInfo))
	{
		snprintf(whisperInfo,2047,"4,21,2");//数据错误
		send_msg(pg_hero->getFd(),whisperInfo);		
		cout<<"[XHM WARNING] The whisper msgInfo is more than MAX_MESSAGE_DATA_LEN<whisper.cpp>!"<<endl;
		return;
	}	
	
	//增加禁言判断；
	set<string>::iterator iterSet = ban_speak.find(my_hero_id);
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM WARNING] The whisper hero in the ban_speak<whisper.cpp>!"<<endl;
		snprintf(whisperInfo,2047,"4,23,1");//增加禁言；
		send_msg(pg_hero->getFd(),whisperInfo);		
		return;
	}
	
	map<string,Hero*>::iterator iter=heroId_to_pHero.find(desHeroId);
	if(iter==heroId_to_pHero.end())
	{
		snprintf(whisperInfo,2047,"4,23,2");//玩家不在线
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}	
	
	wisperHero=iter->second;
	if(!wisperHero->getFriendInfo())
	{
		cout<<"void whisper(char *buffers) getFriendInfo is NULL:"<<endl;
		return;
	}
	
	if(wisperHero->getFriendInfo()->isInBlack(pg_hero->getIdentity()))
	{
		cout<<"void whisper(char *buffers) the you is in his blackList:"<<endl;
		return;
	}
	
	
	snprintf(whisperInfo,2047,"4,11,%s,%s,%s",my_hero_id,pg_hero->getNickName(),msgInfo);	
	if(NULL != wisperHero)//发送消息；
		send_msg(wisperHero->getFd(),whisperInfo);	
	
}



//不管私聊，还是群聊，都是这个聊天函数，函数名原是很早以前请的，不好维护，纯聊天
void whisperAfter(char *buffers)
{
	char* my_hero_id,*msgInfo,*chatId;
	

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);//获取发送者信息；
	MSG_CHAR(chatId); //获取聊天id；
	MSG_CHAR_END(msgInfo);//获取消息内容；
	
	if(MAX_MESSAGE_DATA_LEN < strlen(msgInfo))
	{
		snprintf(whisperInfo,2047,"35,0,1");//数据错误
		send_msg(pg_hero->getFd(),whisperInfo);		
		cout<<"[XHM WARNING] The whisper msgInfo is more than MAX_MESSAGE_DATA_LEN<whisper.cpp>!"<<endl;
		return;
	}	
	
	//增加禁言判断；
	set<string>::iterator iterSet = ban_speak.find(my_hero_id);
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM WARNING] The whisper hero in the ban_speak<whisper.cpp>!"<<endl;
		snprintf(whisperInfo,2047,"35,0,2");//增加禁言；
		send_msg(pg_hero->getFd(),whisperInfo);		
		return;
	}	
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		cout<<"chat is NULL:"<<chatId<<endl;
		return;
	}
	
	//不在群内
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,3");
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	snprintf(whisperInfo,2047,"35,1,1,%s,%s,%s,%s",my_hero_id,pg_hero->getNickName(),chatId,msgInfo);	
	
	//发送消息
	chat->sendMsg(whisperInfo);
}


//客户端点击面板前的交互，为了设置面板的id
void offNewGroupId(char *buffers)
{
	char* my_hero_id,*pulledId;	

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);//获取发送者信息
	MSG_CHAR_END(pulledId); //私聊id；
	
	char *chatId = const_cast<char*>(chatManager->campGroupHandle(my_hero_id));
	if(!chatId)
	{
		cout<<"pullPerson the chatId is NULL:"<<endl;
		return;
	}	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);		
	pg_hero->insertGroupId(chatId);
	chat->insert(my_hero_id);
	chat->insert(pulledId);
	
	//设置客户端的聊天面板id
	snprintf(whisperInfo,2047,"35,2,0,%s",chatId);
	send_msg(pg_hero->getFd(),whisperInfo);			
	
	return;	

}

/* 
* describe:合服后，要查看昵称对应的角色信息，需指定昵称所在的区 db_zone
*/
void find_hero_by_nickName(char *buffers){

	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR_END(char* nick_name);//获取消息内容；
	cout<<"[XHM TEST] find_hero_by_nickName:"<<nick_name<<endl;	

	//TODO 缓存操作，不要删除。
 	int nickname_inspection_size = 0;
	char* result = mem_operate_nickname_inspection->get_mem_data(nick_name, &nickname_inspection_size); 
	if(result != NULL)
	{
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(result);
		if(iter==heroId_to_pHero.end())
		{	
			//缓存数据再拿一次
			int size = 0;
			int where = 0;
			// MemHero* myHeroData=(MemHero*)mem_operate->get_mem_data(result,&size); tory modify 2013.3.18
			MemHero* myHeroData = (MemHero*)mem_group->get_data(result, &size, &where);
			if(NULL != myHeroData)
			{	
				sprintf(whisperInfo, "4,24,1,%s,%s,%d,%d",result,myHeroData->basicHeroData.party,myHeroData->level,myHeroData->camp);//不在线；	门派，等级，阵营，状态； 
			}else{
				sprintf(whisperInfo, "4,24,3,%s,N,0,-1",result);//不在线；	门派，等级，阵营，状态； 			
			}
		}else{
			sprintf(whisperInfo, "4,24,0,%s,%s,%d,%d",result,(iter->second)->getParty(),(iter->second)->getGradeNow(),(iter->second)->getCamp());//在线；				
		}
		free(result);
	}else{
		sprintf(whisperInfo, "4,24,2",result);//不存在；
		
	}
	
	send_msg(sock_fd, whisperInfo); 
}

//邀请进群
void pullPerson(char *buffers)
{
	int num;
	char *my_hero_id,*pulledHeroId,*chatId;
	vector<string> pulledIdVec;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(num);         //解析类型拉人数
	for(size_t person = 0;person < num;++person)
	{
		MSG_CHAR(pulledHeroId);//解析被拉进来的人id
		pulledIdVec.push_back(pulledHeroId);
	}
	MSG_CHAR_END(chatId);//解析群id
	
	if(pulledIdVec.empty())
	{
		cout<<"pullPerson pulledIdVec is emmpty:"<<endl;
		return;
	}
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//此群不存在
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;
	}
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,6");//拉别人的玩家没有在此群中
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;				
	}
	
	asistPull(pg_hero,chat,1,pulledIdVec);
	
}

//邀请进群
void pullPersonByNickName(char *buffers)
{
	int num;
	char *my_hero_id,*chatId,*nickName;
	vector<string> pulledNickNameVec;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(num);         //解析类型拉人数
	for(size_t person = 0;person < num;++person)
	{
		MSG_CHAR(nickName);//解析被拉进来的人昵称
		pulledNickNameVec.push_back(nickName);
	}
	MSG_CHAR_END(chatId);//解析群id
	
	if(pulledNickNameVec.empty())
	{
		cout<<"pullPersonByNickName pulledNickNameVec is emmpty:"<<endl;
		return;
	}
	
	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");  //此群不存在
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;
	}	
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,6");  //拉别人的玩家没有在此群中
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;					
	}
	asistPull(pg_hero,chat,0,pulledNickNameVec);
}

//回应邀请进群
void responsePullPerson(char *buffers)
{
	char *my_hero_id,*chatId;
	int type;
	
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_INT(type);
	MSG_CHAR_END(chatId);//解析群id
	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//此群不存在
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	//参数不对
	if(type < 0 || type > 1)
	{
		cout<<"	responsePullPerson the type argument is error:"<<endl;
		return;	
	}
	
	snprintf(whisperInfo,2047,"35,1,3,%d,%s,%s",type,my_hero_id,pg_hero->getNickName());//群消息
	
	//同意进群
	if(type == 1)
	{
		pg_hero->insertGroupId(chatId);		
	}
	
	chat->sendMsg(whisperInfo);	
}

//退出群,不需要任何人同意
void outGroup(char *buffers)
{
	char *my_hero_id,*chatId;
	
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(my_hero_id);
	MSG_CHAR_END(chatId);//解析群id
	

	ChatGroup* chat = chatManager->getChatGroupHandle(chatId);
	if(!chat)
	{
		snprintf(whisperInfo,2047,"35,0,7");//此群不存在
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	if(!chat->isInGroup(my_hero_id))
	{
		snprintf(whisperInfo,2047,"35,0,3");//玩家没有在此群中
		send_msg(pg_hero->getFd(),whisperInfo);			
		return;	
	}
	
	pg_hero->eraseGroupId(chatId);
	
	snprintf(whisperInfo,2047,"35,1,4,%s,%s",my_hero_id,pg_hero->getNickName());
	
	chat->sendMsg(whisperInfo);	
	
	chat->erase(my_hero_id);
	
	//回收群
	if(chat->empty())
	{
		chatManager->recoverGroupHandle(chatId);
	}
	
}

//邀请进群辅助函数
void asistPull(const Hero* inviter,const ChatGroup* chat,const int type,const vector<string> &pulledIdVec)
{
	if(!inviter || !chat || pulledIdVec.empty() || type > 1 || type < 0 )
	{
		cout<<"asistPull the argument is error:"<<endl;
		return;
	}	
		
	for(vector<string>::const_iterator invited = pulledIdVec.begin();invited != pulledIdVec.begin();++invited)
	{
		char tempId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'},chatMsg[300] = {'\0'};
		
		//type 0 表示vector装的都是昵称，否则为id
		if(type == 0)
		{
			int nickname_inspection_size = 0;			
			char* result = mem_operate_nickname_inspection->get_mem_data((*invited).c_str(), &nickname_inspection_size); 
			if(result == NULL)
			{
				snprintf(chatMsg,2047,"35,0,5"); //被拉玩家不在线
				send_msg(inviter->getFd(),chatMsg);	
				continue;			
			}
			strncpy(tempId,result,strlen(result));
			free(result);
		}
		else
		{
			strncpy(tempId,(*invited).c_str(),strlen((*invited).c_str()));
		}
	
		Hero *invitedHero = heroid_to_hero(tempId);
		
		if(strncmp(inviter->getIdentity(),tempId,strlen(tempId)) == 0)
		{
			snprintf(chatMsg,2047,"35,0,4");//自己不能拉自己进群；
			send_msg(inviter->getFd(),chatMsg);			
			continue;	
		}
		
		if(!invitedHero)
		{
			if(chat->isInGroup(tempId))
			{
				snprintf(chatMsg,2047,"35,0,8");//玩家在此群中
				send_msg(inviter->getFd(),chatMsg);		
				continue;
			}
			else
			{
		
				snprintf(chatMsg,sizeof(chatMsg),"35,1,1,%s,%s,%s",inviter->getIdentity(),inviter->getNickName(),tempId,chat->getGroupId());
				//某人邀请某人进某个群		
				send_msg(invitedHero->getFd(),chatMsg);
			}
		}
		else
		{
			snprintf(chatMsg,2047,"35,0,5");//被拉玩家不在线
			send_msg(inviter->getFd(),chatMsg);	
		}
	}
}

//获取基本数据
void gainMsgById(char *buffers)
{
	char *msgHeroId;
	MSG_BEGIN(buffers,g_msg_len);
	MSG_CHAR_END(msgHeroId);
	int onLine = 0;
	
	//数据错误
	if(!msgHeroId)
	{
		sprintf(whisperInfo,"4,1,1");
		send_msg(pg_hero->getFd(),whisperInfo);
		return;
	}
	
	Hero *msgHero = heroid_to_hero(msgHeroId);	
	MemHero *memHero;
	
	if(!msgHero)
	{
		int size = 0;
		int where = 0;
		char *pmem = mem_group->get_data(msgHeroId, &size, &where);
		if(pmem == NULL)
		{
			sprintf(whisperInfo,"4,1,2");     //此人不存在
			send_msg(pg_hero->getFd(),whisperInfo);
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
		memHero = msgHero->memHero;
		onLine = 1;
	}
	sprintf(whisperInfo,"4,1,0,%s,%s,%d,%d,%d,%s,%d",msgHeroId,memHero->nickName,memHero->level,memHero->vipDailyData.stage,memHero->camp,\
	memHero->basicHeroData.party,onLine);
	send_msg(pg_hero->getFd(),whisperInfo);
}
	
	
