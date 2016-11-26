#include"command_other_function_all_over.h"
#include"hero.h"
#include"team.h"
#include"guild.h"
#include"cpy_series_command_function.h"
#include"map_inform.h"
//邮件系统操作头文件
#include "mail_systerm_interface.h"
//buff药品使用管理
#include "hero_drugs_manage.h"
#include "map_src.h"
#include"statuaryAsist.h"

extern Hero* pg_hero;
extern int shengyanDouble;

void enterScenResponse(char *buffer)
{
	char chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Point enterPt;

	Map_Inform *nowMap;
	char *sumMonMsg;
	
	if(!pg_hero)
	{
		return;
	}
	
	nowMap = pg_hero->getMap();
	
	if(!nowMap)
	{
		return;
	}
	
	if(nowMap->getFlgCpy())
	{	
		sumMonMsg = nowMap->getSumMonMsg();
		send_msg(pg_hero->getFd(),sumMonMsg);
	}	
	
	enterPt = pg_hero->getLocation();
	
	/*切换地图再发一次数据*/
	sprintf(chageSre,"%d,%d,%d,%d,%d,%d,%d,%d",1,5,SUCCESS,\
	enterPt._x,enterPt._y,nowMap->getWarType(),\
	nowMap->getChangePkType(),nowMap->getMapType());	
	
	send_msg(pg_hero->getFd(),chageSre); 
	
	char *mapId=pg_hero->getMap()->getIdentity();
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<mapId<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	if (strcmp(mapId,"map_018")==0||strcmp(mapId,"map_019")==0||strcmp(mapId,"map_020")==0||strcmp(mapId,"map_021")==0)					//跳转的地图是pk地图,进行武林目标验证
	{
		pg_hero->updataSingleTarget(2,7);
	}
	else if (strcmp(mapId,"map_023")==0||strcmp(mapId,"map_024")==0)					//跳转的地图是娱乐地图,进行武林目标验证
	{
		pg_hero->updataSingleTarget(2,1);
	}
	// else if (strncmp(mapId,"map_029",7)==0)
	// {
		// if (pg_hero->getGuild()!=NULL)
		// {
			// pg_hero->getGuild()->send_msg_feast();
		// }
	// }

#if 0
	/*测试雕像用*/	
	setUpStatuary(pg_hero->getIdentity(),"SH_T009");
	
#endif
	
	pg_hero->enter_scene();
	pg_hero->setWalkingFlg(true);
	
	
	
	// cout<<"-------------------------72-------------------------"<<endl;
	//玩家进入帮派盛宴地图.发送消息是否双倍的消息
	if(!nowMap->getFlgCpy())
	{
		Map_Src *mapHeroNow=(Map_Src*)nowMap;
		memset(g_out_buf,0,sizeof(g_out_buf));
		if (mapHeroNow->getPartyRoomLimit()!=NULL)
		{	
			if (shengyanDouble!=1)
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"12,30,1");
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}
	}
	// cout<<"-------------------------83-------------------------"<<endl;
	//设置PK模式；xhm added
	pg_hero->sethero_PK_status(nowMap->getWarType());
	// cout<<"[XHM TEST] enterScenRensponse gethero_PK_status:"<<pg_hero->gethero_PK_status()<<endl;
	
	//loadState为false时，表示刚上线进场景：
	if(pg_hero->getLoadState() == false)
	{		
		/* 处理不在线状态下收到的邮件数据 */
		MailSystermInterface::handle_mail_data(pg_hero->getIdentity());

		/* 处理buff药数据 */
		continueUseBuffDrug(pg_hero);
		
		pg_hero->setLoadState(true);
		return;
	}
}

	
		
    
