/*
* Filename: user_attr_apply.h  
* Description: 人物属性面板打开时的时候请求显示人物属性
* Original Author : bison, 2012-7-24
*/
 
#include "command_return_define_data.h"
#include "role.h"
#include "user_attr_apply.h"
#include "bag_operator.h"
#include "rankInfoAsist.h"
#include <arpa/inet.h>
#include"dictionary_asist.h"
#include"guild_asist.h"
#include "campWarManagement.h"
#include"rankInfoAsist.h"
//缓存服务器管理类
#include "my_mem_group.h"
//用于昵称检查缓存的操作类指针实例引用声明
// extern MyMemcache* mem_operate;
extern MyMemGroup* mem_group;

extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern Role *pg_role;
extern char server_name[10];
extern map<int,int> campNumber;
extern campWarManagement campWarController;//阵营战管理实例；

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;

//玩家请求人物属性 jolly modify 9.25
void userAttrApplyComm(char *buffer)
{	
	pg_hero->send_msg_att();	
}

void userExercise(char *buffer)
{	
	pg_hero->Exercise();
}

void userExerciseMoneySave(char *buffer)
{		
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)
	if (flag==1)
	{
		pg_hero->moneySaveExercise();
	}
	else if (flag==2)
	{
		pg_hero->onKeySaveExercise();
	}
}

void userExerciseGoldSave(char *buffer)
{
	int index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	
	pg_hero->goldSaveExercise(index);
}

/*
* date: 2012.12.4
* author: tory
* describe:获取指定角色ID的人物面板信息：人物基本属性+身上装备+战力值+声望 
*/
void getHeroAttribute(char* buff)
{
	MSG_BEGIN(buff, g_msg_len);	
	MSG_CHAR_END(char* heroId);
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf), "%d,%d", 25, 0);
	Hero *heroOther = heroid_to_hero(heroId);	
	if(heroOther == NULL) //该角色已不在线,从缓存中获取角色面板数据
	{		
		int size = 0;
		int where = 0;
		MemHero *memHero = (MemHero*)mem_group->get_data(heroId, &size, &where);	//由于heroId是唯一的，所以无需指定区
		cout<<"@@Tory,get memHero data from:"<<where<<endl;
		if(memHero != NULL)
		{	
			Guild *guild = getGuildWithId(memHero->heroGuildData.guildId);
			char guildName[51] = {0};
			if (guild != NULL)
			{
				strncpy(guildName, guild->getName(), sizeof(guildName));
			}
			//角色基本属性数据
			snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf), ",%s,%s,%s,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",heroId,\
					memHero->nickName,	guildName, memHero->camp, memHero->level,memHero->basicHeroData.party,\
					GetPowerValue(memHero), memHero->prestige,memHero->friendLevel,memHero->crimeValue,\
					memHero->exercisedata.physique,	memHero->exercisedata.wushu,memHero->exercisedata.will,	memHero->exercisedata.shenfa,\
					memHero->basicHeroData.lifeVal,	memHero->basicHeroData.lifeUpperVal,memHero->basicHeroData.magicVal,memHero->basicHeroData.magicUpperVal, memHero->basicHeroData.outattack,	memHero->basicHeroData.inattack,memHero->basicHeroData.outdefense,memHero->basicHeroData.indefense,	memHero->basicHeroData.hited,memHero->basicHeroData.dodge,memHero->basicHeroData.crit,memHero->basicHeroData.tenacity
					);	
			//角色身上装备数据						
			for (int i=0; i<14; i++)
			{
				if (memHero->wearequipdata[i].flag==1)
				{
					snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf), ",%d,%s,%s", i, memHero->wearequipdata[i].typeId, memHero->wearequipdata[i].goodsid);	
				}
			}	
			free(memHero);		//add 2012.12.19				
		}	
	}
	else
	{
		MemHero *memHero = heroOther->memHero;	//获取角色缓存数据的指针
		if(memHero != NULL)
		{		
			//角色基本属性数据
			snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf), ",%s,%s,%s,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",heroId,\
					memHero->nickName,	heroOther->getGuildName(), memHero->camp, memHero->level,memHero->basicHeroData.party,\
					GetPowerValue(memHero), memHero->prestige,memHero->friendLevel,memHero->crimeValue,\
					memHero->exercisedata.physique,	memHero->exercisedata.wushu,memHero->exercisedata.will,	memHero->exercisedata.shenfa,\
					memHero->basicHeroData.lifeVal,	memHero->basicHeroData.lifeUpperVal,memHero->basicHeroData.magicVal,memHero->basicHeroData.magicUpperVal, memHero->basicHeroData.outattack,	memHero->basicHeroData.inattack,memHero->basicHeroData.outdefense,memHero->basicHeroData.indefense,	memHero->basicHeroData.hited,memHero->basicHeroData.dodge,memHero->basicHeroData.crit,memHero->basicHeroData.tenacity
					);	
			//角色身上装备数据						
			for (int i=0; i<14; i++)
			{
				if (memHero->wearequipdata[i].flag==1)
				{
					snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf), ",%d,%s,%s", i, memHero->wearequipdata[i].typeId, memHero->wearequipdata[i].goodsid);	
				}
			}				
		}
	}
	send_msg(pg_hero->getFd(), g_out_buf);
}

void changeCamp(char *buffer)
{
	modifyCamp(pg_hero);
}
//人物改名
void changeNickName(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR(char* name)
	MSG_INT_MAX(int indexBag, 95)
	
	cout<<"4,15,"<<name<<","<<indexBag<<endl;
	
	if (strlen(name) < 1 || strlen(name) > 18)
	{
		return;
	}
	//名字里含有敏感字，错误代码：3（NAME_ILLEGAL_FAILED）
	if (isHaveDirtyWords(name) == 1)
	{
		return;
	}
	//名字里有禁闭的标点符号，错误代码：3（NAME_ILLEGAL_FAILED）
	if  (isHaveIllSymbol(name) == 1)
	{
		return;
	}
	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	
	//TODO 同名检查。
 	int nickname_inspection_size = 0;
	char* result = mem_operate_nickname_inspection->get_mem_data(name, &nickname_inspection_size); 
	if(result != NULL)
	{
		free(result);
		puts("[XHM MSG] get mem_data from nickname_inspection memcached server success ,The same as the user name.\n");
		memset(g_out_buf, 0, 20480);
		msg_error(g_out_buf,119);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if(useBagGoods(pg_hero,"b_cl_126_100",indexBag,1,false)==0||useBagGoods(pg_hero,"f_cl_126_100",indexBag,1)==0)
	{
		pg_role->setNickName(name,pg_hero->getIdentity());
		pg_hero->setNickName(name);
		Guild* guild = pg_hero->getGuild();
		if (guild != NULL)
		{
			guild->changeHeroNickName(pg_hero->getIdentity(), name);
		}
		
		if(pg_hero->getCamp() > 0)
			campWarController.updateLeaderInfo(pg_hero);//改名，更改阵营职务对应名字；added xhm;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",3,CHANGE_NICKNAME,SUCCESS,pg_hero->getIdentity());
		
			//TODO 改名成功,存储。
		bool isSuccess = mem_operate_nickname_inspection->set_mem_data(name, pg_hero->getIdentity(), strlen(pg_hero->getIdentity())); 
		if(isSuccess != true)
			puts("[XHM WARNING] set memData to nickname_inspection memcached server failure!");	 
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",3,CHANGE_NICKNAME,FAILED,pg_hero->getIdentity());
	}
	send_msg(pg_hero->getFd(),g_out_buf);
	pg_hero->memSet();
}

/*
* date: 2012.12.4
* author: tory
* describe:获取指定角色的个人资料，响应23,1命令
*/
void getHeroInfor(char* buff)
{

	MSG_BEGIN(buff, g_msg_len);
	
	MSG_CHAR_END(char* heroId);
	cout<<"@@Tory in getHeroInfor,heroId:"<<heroId<<endl;
	
	Hero *heroOther = heroid_to_hero(heroId);	
	if(heroOther == NULL) //角色不在线，从缓存服务器中获取角色个人资料
	{		
		int size = 0;
		int where = 0;
		//the object returned by memcached_get() must be released by the caller 
        // MemHero *memHero = (MemHero*)mem_operate->get_mem_data(heroId, &size);
		MemHero *memHero = (MemHero*)mem_group->get_data(heroId, &size, &where);	//由于heroId是唯一的，所以无需指定区
		if(memHero != NULL)
		{				
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s,%s", 25, 1, memHero->identity, memHero->heroInfor);
		}
		free(memHero);		//add 2012.12.19
	}else{
		MemHero *memHero = heroOther->memHero;	//获取角色缓存数据的指针
		if(memHero != NULL)
		{					
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s,%s", 25, 1, memHero->identity, memHero->heroInfor);
		}
	}
	
	send_msg(pg_hero->getFd(), g_out_buf);

}

/*
* date: 2012.12.4
* author: tory
* describe:保存自己角色的个人资料，响应23,2命令
*/
void saveHeroInfor(char* buff)
{

	cout<<"@@Tory buff+7:"<<buff+7<<endl;
	char* p = buff+6;
/* 	char len = *p;
	char* heroId = p+1;
	p += len+1;
	len = *p;
	*p = '\0';
	cout<<"@@Tory in saveHeroInfor,heroId:"<<heroId<<endl; */
	
	char* data = p+1;	//data为不定长，len = 0； 
//	p += len+1;
//	*p = '\0';
	cout<<"@@Tory in saveHeroInfor,data:"<<data<<endl;
	
	MemHero *memHero = pg_hero->memHero;	//获取角色缓存数据的指针
	if(memHero != NULL)
	{					
		memset(memHero->heroInfor, 0, 1024);	//清空原有数据
	//	sprintf(g_out_buf, "%d,%d,%s", 25, 1, memHero->heroInfor);
		memcpy(memHero->heroInfor, data, 1024);
		cout<<"@@Tory memHero->heroInfor:"<<memHero->heroInfor<<endl;
	}

	return;

}

void showCampSelect(char *buffer)		//add jolly 
{
	map<int,int>::iterator it;
	int suggestCamp=0;
	int campHero=0;
	if (!campNumber.empty())
	{
		campHero=campNumber.begin()->second;
	}
	for (it=campNumber.begin();it!=campNumber.end();++it)
	{
		if (it->second<campHero)
		{
			campHero=it->second;
			suggestCamp=it->first;
		}
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"8,11,%d",suggestCamp);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void judgeWarehouseAndShop(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (flag==1)		//商店
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,33,flag,pg_hero->memHero->vipDailyData.store);
	}
	else if (flag==2)			//仓库
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,33,flag,pg_hero->memHero->vipDailyData.warehouse);
	}
	send_msg(pg_hero->getFd(),g_out_buf);
}

void vipInformComm(char *buffer)
{
	cout<<"9,25"<<endl;
	
	Money *money=pg_hero->getMoney();
	
	int chongzhi=money->getAccMoney();
	
	int flag=0;
	
	if (pg_hero->memHero->testVipTime==-1)
	{
		flag=1;
	}
	else
	{
		flag=0;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",9,36,pg_hero->memHero->vipDailyData.stage,pg_hero->memHero->vipDailyData.recharge,chongzhi,flag);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void testVip(char *buffer)
{
	// cout<<"28,5"<<endl;
	// pg_hero->startTestVip();
}

void heroResponse(char *buffer)
{
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",1,7,GetPowerValue(pg_hero->memHero));
	send_msg(pg_hero->getFd(),g_out_buf);
}

void returnVipFreeNumber(char *buffer)
{
	cout<<"28,7"<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,37,pg_hero->memHero->vipDailyData.callTimes,pg_hero->memHero->vipDailyData.flyTimes);
	send_msg(pg_hero->getFd(),g_out_buf);
}