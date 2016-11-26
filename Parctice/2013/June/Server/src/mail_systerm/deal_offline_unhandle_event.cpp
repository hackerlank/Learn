/****************************************************************
 * Filename: deal_offline_unhandle_event.cpp
 * 
 * Description: 处理玩家离线期间未处理事件
 *
 * Original Author : bison, 2012-9-25
 *
 ****************************************************************/
 
#include "offline_unhandle_event.h"
#include"command_other_function_all_over.h"
#include "guild_asist.h"
#include "money_operator.h"
#include "systemMessage.h"

extern map<string, Hero*> heroId_to_pHero;

//主类型为5时,玩家属性相关的未处理事件
void deal_unhandle_attr_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleAttr_T *event = (UnhandleAttr_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<<" num is "<<event->num<<endl;
	Guild *guild = hero->getGuild();
	switch(event->type)
	{
		case UNHANDLE_HERO_EXP:						//未处理的英雄经验
			hero->setExpNow(event->num);
			break;
			
		case UNHANDLE_BOUND_GAME_MONEY:				//未处理的绑定游戏币
			increaseBoundGameMoney(hero,event->num);
			break;
			
		case UNHANDLE_GAME_MONEY:					//未处理的非绑定游戏币
			increaseGameMoney(hero,event->num);
			break;
			
		case UNHANDLE_BOUND_GOLD:					//未处理的绑定元宝
			increaseBoundGold(hero,event->num);
			break;
			
		case UNHANDLE_GOLD:							//未处理的元宝
			increaseGold(hero,event->num);
			break;
		
		case UNHANDLE_GUILD_EXP:					//未处理的玩家给帮派加的帮贡
			if (guild != NULL)
			{
				char* guildName = hero->getGuildName();
				addGuildExp(guildName, heroId, event->num);
			}
			break;
			
		case UNHANDLE_HERO_GLORY:					//未处理的玩家帮贡
			if(guild != NULL)
			{
				char* guildName = hero->getGuildName();
				addMyGuildGlory(guildName, heroId, event->num);
			}
			break;
		
		default:
			cout<<"BisonWarning: unhandle event type is error"<<endl;
			break;
	}
}


//主类型为6时,玩家物品奖励的未处理事件
void deal_unhandle_goods_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleGoods_T *event = (UnhandleGoods_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<<" num is "<<event->num<<endl;
	cout<<"And the event goods id is "<<event->id<<endl;
	Bag *bag = hero->getBag();
	
	if(event->type != UNHANDLE_GOODS)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle goods event!"<<endl;
		return;
	}
	//管它成功不成功，只设这一次，玩家包裹满的话算他倒霉
	saveGoodsInBag(hero,event->id, event->num);
}


//主类型为7时,玩家一个完整未处理事件对应的消息
void deal_unhandle_msg_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleMsg_T *event = (UnhandleMsg_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->msg<<endl;
	
	//不是法消息的类型
	if(event->type != UNHANDLE_LONG_MSG)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle msg event!"<<endl;
		return;
	}
	//玩家离线时发生了某种与他相关的事件，给玩家发这个事件的结果
	systemSendMssage(hero, event->msg, 0);
}

//主类型为8时，玩家加入帮派的未处理事件处理
void deal_unhandle_join_guild_event(char* heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构
	UnhandleJoinGuild_T *event = (UnhandleJoinGuild_T*)data;
	cout<<"BisonShow you can see is event val OK: type is "<<event->type<< " "<<event->guildName<<endl;
	
	//不是法消息的类型
	if(event->type != UNHANDLE_JOIN_GUILD)
	{
		cout<<"BisonWarning: get unhandle event from mail doesn't match the unhandle msg event!"<<endl;
		return;
	}
	
	Guild *guild = getGuildWithName(event->guildName);
	if (guild == NULL)
	{
		return;
	}
	
	int guildTitle = guild->getHeroTitle(heroId);
	if (guildTitle == -1)
	{
		//帮派查无此人
		return;
	}
	//ok,万事大吉，更新玩家的帮派信息
	hero->setGuildInfo(guild, guildTitle);
	
}

//主类型为9时,玩家一个完整未处理事件好友申请
void deal_unhandle_friend_apply_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"BisonShow mail give a null message to UNHANDLE to deal!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleFriendApply_T* event = (UnhandleFriendApply_T*)data;
	// cout<<"BisonShow you can see is event val OK: type is "<<event->msg<<endl;
	string msg = event->msg;
	send_msg(hero->getFd(), msg);
}

//主类型为10时,玩家一个完整未处理事件好友删除
void deal_unhandle_del_friend_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"in the deal_offerline_unhandle_event.cpp-->BisonShow mail give a null message to UNHANDLE to deal friend_apply!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleDelFriend_T* event = (UnhandleDelFriend_T*)data;
	// cout<<"BisonShow you can see is event val OK: type is "<<event->heroId<<endl;
	hero->getFriendInfo()->delFromFriendlist(event->heroId);
}

//主类型为11时,玩家一个完整未处理事件好友添加
void deal_unhandle_add_friend_event(string heroId, char* data)
{
	if (data == NULL)
	{
		cout<<"in the deal_offerline_unhandle_event.cpp-->BisonShow mail give a null message to UNHANDLE to deal friend_apply!"<<endl;
		return;
	}
	map<string, Hero*>::iterator it_hero;
	it_hero	= heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		cout<<"in the deal_offerline_unhandle_event.cpp--> the hero to be deal is still offline!"<<endl;
		return;
	}
	
	Hero* hero = it_hero->second;
	//强转成可处理结构体
	UnhandleAddFriend_T* event = (UnhandleAddFriend_T*)data;
	if(hero->getFriendInfo() == NULL)
		return;
		
	hero->getFriendInfo()->add2Friendlist2(event->heroId,event->myFriend);
}

