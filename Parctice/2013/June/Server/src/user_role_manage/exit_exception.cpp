/********************************************
* Filename：exit_exception.cpp
* Authof： ChenZhen
* Description:处理角色的非正常退出
* 更改人：Tory
* 更改时间：2012.9.23
**********************************************/
//交互处理返回消息的宏定义
#include"command_return_define_data.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"
//角色管理头文件
#include"command_user_role_manage.h"
//维护当前时间的头文件
#include "my_time.h"
#include "team_operation.h"
#include"role.h"
#include"anyBusiness.h"
#include"pet_box.h"

#include"pet.h"

#include"map_inform.h"

#include "team.h"

#include "guild_war_asist.h"

#include "wagon.h"

#include "revival_config.h"

#include "analyzeCampWar.h"

#include"meridian_asist.h"

#include "campWarManagement.h"

#include "rankInfoAsist.h"

#include"boxAsist.h"

#include"commodity.h"

#include "hero_drugs_manage.h"

#include "towerDefTeamAsist.h"

#include "rob_flag_war_logic.h"

#include"cpyAsist.h"

#include "mailSysterm.h"

//缓存服务器管理类
#include "my_mem_group.h"
//用于昵称检查缓存的操作类指针实例引用声明
// extern MyMemcache* mem_operate;

extern MyMemGroup* mem_group;

#include"statuaryAsist.h"

extern GuildWarAsist *guildWarManage;			//帮派战管理

extern map<string,Wagon*> wagonInstMap;			//所有马车实例

extern int from; 

extern int sock_fd;
//空闲用户列表
extern list<Role*> idle_role_list;
//空闲角色列表
extern list<Hero*> idle_hero_list;

extern map<int, Role*> fd_to_pRole;

extern map<string,Map_Src*>mapId_connect_map;

//extern map<string, Role*> userName_to_pRole;

extern map<string, Hero*> heroId_to_pHero;

extern map<string,Revival_Config*> mapId_to_revival;		//复活点坐标信息
		

extern map<string,set<string > > tid; //组队目的对应队伍id

// extern map<string,set<string > > pid;	//组队目的对应hero
	
extern map<string,Pet*> id_to_activePet;	

extern campWarManagement campWarController;

extern char server_name[10];

extern Role *pg_role;

extern map<string ,PrivateStall* > onLineStall; //在线摊位

extern map<string, MailSysterm*> mail_map;

void exit_accident(int sock_fd)                 
{
	
    map<int,Role*>::iterator role_it; 
    role_it = fd_to_pRole.find(sock_fd);
    if(role_it == fd_to_pRole.end())
    {
        cout<<"exit_accident.cpp:find Role error"<<endl;
        return;
    }
    Role *player;              //下线玩家role实例指针
    player = role_it->second;
	
	char oldUserName[51]  = {0};
	bool isTempGuestFlag = false;
	strncpy(oldUserName, player->getUserName(), sizeof oldUserName);
	if (strlen(oldUserName) == 21 && strncmp(oldUserName, "TempGuest", 9) == 0)
	{
		isTempGuestFlag = true;
	}
    //如果进入了游戏场景，则需要对活动hero实例做下线处理    
    Hero *myHero = player->getActive_hero();   
	Map_Inform *map_now;
	Nbox *box;	
	char* heroId;
	
    if(myHero != NULL)
    {
		
		myHero->offLineTeam();
		
		/*副本里面退出副本*/		
		if(strlen(myHero->getFbRom()) > 0)
		{
			outCpy(myHero);
		}   
		
        map_now = myHero->getMap();
		
        if(map_now == NULL)
        {
            cout<<"in exit_accident::map_now is NULL"<<endl;
            return ;
        }
		
        box=map_now->getBox();  	

		if(box == NULL)
		{

			cout<<"it is error:"<<endl;
			return;
		}		
		
		
		myHero->abandTaskBySubType(1, true);
		
		heroId = myHero->getIdentity();
		
		StyObj obj(heroId,HERO_STYLE_TYPE);
		
		box->getStaInSrcVec(obj);
		
		map_now->deleteID(obj);
		
		map_now->delFd(myHero->getFd());
	
		box->heroEnter(myHero,2);   
		
		cout<<"-------------------------124-------------------------"<<endl;
		/*人物若是死亡状态下线,则自动让其回城复活,再数据下线 jolly 10,12 start*/
		if (myHero->getLifeVal()<=0)
		{			
			Map_Src *scene_map=NULL;
			Point revival_pt;
			cout<<"jolly:hero is dead ,so before offline,we should move hero to city at first exit_exception 69"<<endl;
			map<string,Revival_Config*>::iterator it;
			it=mapId_to_revival.find(map_now->getIdentity());
			if (it==mapId_to_revival.end())
			{				
				cout<<"jolly:revival error hero_revival.cpp 154"<<endl;	
				map<string,Map_Src*>::iterator map_it;				
				map_it = mapId_connect_map.find("map_001");
				if (map_it==mapId_connect_map.end())
				{
					cout<<"jolly:map_001 error exit_exception 173"<<endl;
				}					
				else
				{
					scene_map = map_it->second;
					revival_pt=	scene_map->getEntPt();	
					myHero->setMapId("map_001");	
					myHero->setMap(scene_map);
					myHero->setLocation(revival_pt);  						
				}
			}
			else
			{						
				Revival_Config *revival=it->second;
				string revival_map=revival->getRevivalMap();				
				map<string,Map_Src*>::iterator map_it;
				map_it = mapId_connect_map.find(revival_map);
				if(map_it == mapId_connect_map.end())
				{					
					cout<<"Acording to mapid can't find the Mapinform (in hero_revival)"<<endl;
				}
				else
				{	
					scene_map = map_it->second;
					revival_pt._x=revival->getPtx();
					revival_pt._y=revival->getPty();
					myHero->setMapId(revival_map.c_str());
					myHero->setMap(scene_map);
					myHero->setLocation(revival_pt);
				}  
			}
			myHero->setLifeStation(1);
			int revival_life=myHero->getLifeUpperVal();
			int revival_magic=myHero->getMagicUpperVal();
			myHero->setLifeVal(revival_life);
			myHero->setMagicVal(revival_magic);
		}
		cout<<"-------------------------164-------------------------"<<endl;
						
		//停止经脉定时器
		stopMeridianTimer(heroId);

		//人物下线,记录在线奖励的情况
		if (myHero->getRewardOnline())
		{
			myHero->getRewardOnline()->judgeTotalTime();
		}
		/////////////////////////////////////////处理帮派系统中的数据
		
		// if ((long)MY_TV_SEC > 0)
		// {
			// myHero->memHero->offlineTime = MY_TV_SEC;			cout<<"-------------------------169-------------------------"<<endl;		//离线时间	
		// }		
		// myHero->memHero->rewarddata.offline_time=MY_TV_SEC;
		Guild* my_guild = myHero->getGuild();
		if(my_guild != NULL)
		{
			//unfinished
			//置玩家下线
			my_guild->setHeroOnline(myHero->getIdentity(), false);		cout<<"-------------------------175-------------------------"<<endl;
			//如果在帮派战房间中，把他踢出
			if (myHero->isInGuildWarRoom())
			{
				//退出帮派战房间
				// guildWarManage->exitGuildWar(myHero, true);			cout<<"-------------------------180-------------------------"<<endl;
				robFlagWarManage->exitRoom(myHero, true);
			}
		}
#if 1		

		//如果有马车任务，马车先不搞掉，只把主人指针清了,
		//策划定的玩家掉线一段时间之前马车任务可以继续做
		char* wagonId = myHero->memHero->wagonId;
		map<string,Wagon*>::iterator wagon_it;
		if (strlen(wagonId) != 0)
		{
			wagon_it = wagonInstMap.find(wagonId);
			if(wagon_it != wagonInstMap.end())
			{	
				Wagon *myWagon = wagon_it->second;
				//马车和主人离婚
				myWagon->divorceWithOwner(); 
			}
			
		}
#endif	

		/* 将下线角色的新邮件内容写入外部文件 tory */
   		map<string, MailSysterm*>::iterator iter = mail_map.find(myHero->getIdentity());
		if(iter != mail_map.end())	
		{
			MailSysterm* m_s = iter->second;
			if(m_s != NULL)
			{
				m_s->save_mail_data(myHero->getIdentity());
				delete m_s;
			}	
		}  
		mail_map.erase(myHero->getIdentity());
		
		//下线是否摆摊检测 ，若是则停止摆摊
		if(myHero->getHeroState()==5)
		{
			//找到该玩家摊位
			myHero->stall.initPrivateStall();
		}	
		
		//玩家下线前是否在交易,若在交易则关闭
		if (myHero->bussinessData.bussinessFlag!=0)
		{
			bussinessCancelDeal(myHero);
		}
		
		//玩家下线前若是在玩猜拳游戏,则帮其退出 jolly add 2013.1.9
		myHero->exitFingerGuessingGame();		//若没有参加 则有保护
		
		//更新角色排名
		updateRankTempData(myHero);					cout<<"-------------------------229-------------------------"<<endl;
		//如果是在阵营战中退出
		CampData_T campWardata= myHero->getCampWarData();	cout<<"-------------------------231-------------------------"<<endl;
		/*根据阵营战类型，选择加入不同的阵营战.*/
		int campWarType=campWardata.campWarType;	cout<<"-------------------------233-------------------------"<<endl;
		switch(campWarType)
		{
		case 1:																//添加到普通阵营战中；
			campWarController.exitFromOrdinayCampWar(heroId,campWardata.campWarRoomNum,1);
			break;
		case 2:																//添加到统领争夺阵营战中；
			campWarController.exitFromLeaderCampWar(heroId);
			break;
		case 3:																//添加到盟主争夺阵营战中；
			campWarController.exitFromChiefCampWar(heroId);	
			break;
		case 4:
			campWarController.exitCampResWar(myHero);
			break;
		default:
			break;
		}
		


		cout<<"second offLine mapId:"<<map_now->getMapId()<<endl;
		//处理在地图中的数据
        map_now->deleteID(obj); 
		cout<<"-------------------------249-------------------------"<<endl;

		// myHero->memHero->rewarddata.offline_time = MY_TV_SEC;		//记录下线时间（秒）
		//放在最后，以防有在这之前没存到memcached中的数据 by bison				
		myHero->memSet();
		
		/*记录角色下线的流水账 jolly 11.15 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%ld,%ld,%ld,%ld",1,3,server_name,(int)myTime.tv_sec,player->getUserName(),myHero->getIdentity(),myHero->getNickName(),\
		myHero->getLevel(),myHero->getMoney()->money_getBoundGold(),myHero->getMoney()->money_getGold(),myHero->getMoney()->money_getBoundGameMoney(),myHero->getMoney()->money_getGameMoney());	
		write_log(account_msg);
		/*记录角色下线的流水账 jolly 11.15 end*/		
		myHero->stopTongBuTimer();
		/*jolly修改,人物数据全部保存后,让宠物下线*/
        Pet_Box *pet_box=myHero->getPetBox();
        Pet *pet=pet_box->getActivePet();
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        if(pet!=NULL)
        {					
			cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
            map<string,Pet*>::iterator it;
			string pet_identity=pet->getIdentity();
			it=id_to_activePet.find(pet_identity);
			if (it==id_to_activePet.end())
			{
				cout<<"error-------------------------------------exit_exception.cpp 259"<<endl;
			}
			else
			{	
				cout<<"##################################################"<<endl;
				// id_to_activePet.erase(it);	
				// myHero->stopPetTimer();
				cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
			}
			pet->send_msg_downLine(myHero);
        }  		
		myHero->endHappyTimer(1);			//停止娱乐图时间计时
		if (isTempGuestFlag)
		{
			// mem_operate->delete_mem_data(myHero->getIdentity());
			mem_group->delete_data(myHero->getIdentity(), from);
		}
		delete myHero;
		//待通过数据重置来处理
		//heroId_to_pHero.erase(heroId);//move this to Hero 析构函数，确保任何情况都会删掉 benliao 2012.12.01
		cout<<"********************************"<<endl;
		
		//清除聊天id集合
		myHero->clearChatSet();
	}
    //用户下线处理
    player->setLoginState(false);                  //将下线的Role对象的在线状态isLogin改为false
    player->setActive_heroId("0");                 //将下线的Role对象的获得heroId设置为“0”
    player->setActive_hero(NULL);                  //将玩家的活动角色设置为空
	
	//如果是临时用户
	if (isTempGuestFlag)
	{
		// mem_operate->delete_mem_data(oldUserName);
		mem_group->delete_data(oldUserName, from);
	}
	idle_role_list.push_back(player);	//todo benliao 这里疑问	
}

//服务器关闭处理
void closeServerDeal(Hero *myHero)
{
	if (myHero == NULL)
	{
		return;
	}
	string returnMapId = "map_001";
	
	char* heroId = myHero->getIdentity();
	Map_Inform *map_now = myHero->getMap();
	/////////////////////////////////////////下线前部分状态数据更新至memHero中
	//	myHero->memHero->basicHeroData.pt = myHero->getLocation();
	myHero->memHero->basicHeroData.pt._x = myHero->getLocation()._x;
	myHero->memHero->basicHeroData.pt._y = myHero->getLocation()._y ; 
	cout<<"x:"<<myHero->memHero->basicHeroData.pt._x<<" y:"<<myHero->memHero->basicHeroData.pt._y<<endl;
	
	/*副本里面退出副本，则下次进去先去主城*/		
	if(strlen(myHero->getFbRom()) > 0)
	{
		myHero->setFbRom(NULL);
		// myHero->setMap(NULL);
		myHero->setMapId(myHero->getMainSrc());
		Point piex = myHero->getBeforePiexPt();
		myHero->setLocation(piex);
	}
	
	cout<<"-------------------------124-------------------------"<<endl;
	/*人物若是死亡状态下线,则自动让其回城复活,再数据下线 jolly 10,12 start*/
	if (myHero->getLifeVal()<=0)
	{
		cout<<"jolly:hero is dead ,so before offline,we should move hero to city at first exit_exception 69"<<endl;
		map<string,Revival_Config*>::iterator it;
		it=mapId_to_revival.find(map_now->getIdentity());
		if (it==mapId_to_revival.end())
		{
			cout<<"jolly:revival error hero_revival.cpp 154"<<endl;
		}
		else
		{						
			Revival_Config *revival=it->second;
			string revival_map=revival->getRevivalMap();				
			map<string,Map_Src*>::iterator map_it;
			map_it = mapId_connect_map.find(revival_map);
			if(map_it == mapId_connect_map.end())
			{
				cout<<"Acording to mapid can't find the Mapinform (in hero_revival)"<<endl;
			}
			else
			{					
				Map_Src *scene_map = map_it->second;
				myHero->setMap(scene_map);
				myHero->setMapId(revival_map.c_str());
				int ptx=revival->getPtx();
				int pty=revival->getPty();
				Point revival_pt;
				revival_pt._x=ptx;
				revival_pt._y=pty;
				myHero->setLocation(revival_pt);  
				myHero->setLifeStation(1);
				int revival_life=myHero->getLifeUpperVal();
				int revival_magic=myHero->getMagicUpperVal();
				myHero->setLifeVal(revival_life);
				myHero->setMagicVal(revival_magic);
			}
		}
	}
	cout<<"-------------------------164-------------------------"<<endl;
	/*人物若是死亡状态下线,则自动让其回城复活,再数据下线 jolly 10,12 end*/
	
	//停止经脉定时器
	stopMeridianTimer(heroId);
	
	if (myHero->isInCollecting())
	{
		myHero->stopCollectTimer(6);
	}
	
	myHero->abandTaskBySubType(1, true);
	
	/* 将下线角色的新邮件内容写入外部文件 tory 2013.1.9*/
   	map<string, MailSysterm*>::iterator iter = mail_map.find(myHero->getIdentity());
	if(iter != mail_map.end())	
	{
		MailSysterm* m_s = iter->second;
		if(m_s != NULL)
		{
			m_s->save_mail_data(myHero->getIdentity());
			delete m_s;
		}	
	}  
	mail_map.erase(myHero->getIdentity());
		
	/////////////////////////////////////////处理帮派系统中的数据
	// if ((long)MY_TV_SEC > 0)
	// {
		// myHero->memHero->offlineTime = MY_TV_SEC;			cout<<"-------------------------169-------------------------"<<endl;		//离线时间	
	// }
	// myHero->memHero->rewarddata.offline_time=MY_TV_SEC;	
	Guild* my_guild = myHero->getGuild();
	if(my_guild != NULL)
	{
		//unfinished
		//置玩家下线
		my_guild->setHeroOnline(myHero->getIdentity(), false);		cout<<"-------------------------175-------------------------"<<endl;
		//如果在帮派战房间中，把他踢出
		if (myHero->isInGuildWarRoom())
		{	
			//设置玩家状态不在帮派战房间中
			myHero->setInGuildWarRoom(false, NULL);
			myHero->setMapId(myHero->getMainSrc());
			Point piex = myHero->getBeforePiexPt();
			myHero->setLocation(piex);
			//myHero->setMapId(myHero->getMainSrc());	
		}
	}
		
	//玩家下线前若是在玩猜拳游戏,则帮其退出 jolly add 2013.1.9
	myHero->exitFingerGuessingGame();		//若没有参加 则有保护
	
	//人物下线,记录在线奖励的情况
	if (myHero->getRewardOnline())
	{
		myHero->getRewardOnline()->judgeTotalTime();
	}
	
	//下线是否摆摊检测 ，若是则停止摆摊
	if(myHero->getHeroState()==5)
	{
		//找到该玩家摊位
		myHero->stall.initPrivateStall();
	}			
	
	/*记录角色下线的流水账 jolly 11.15 start*/
	char account_msg[1024]={'\0'};
	map<int, Role*>::iterator role_it;
	role_it=fd_to_pRole.find(myHero->getFd());
	if (role_it==fd_to_pRole.end())
	{
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s",1,3,server_name,(int)myTime.tv_sec,myHero->getIdentity(),myHero->getNickName());
	}
	else
	{
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",1,3,server_name,(int)myTime.tv_sec,role_it->second->getUserName(),myHero->getIdentity(),myHero->getNickName());
	}	
	write_log(account_msg);
	/*记录角色下线的流水账 jolly 11.15 end*/		
	
	
	
	
	////////////////////////////////////////更新角色排名
	//updateRankTempData(myHero);					cout<<"-------------------------229-------------------------"<<endl;
	///////////////////////////////////////如果是在阵营战中退出
	CampData_T campWardata= myHero->getCampWarData();	cout<<"-------------------------231-------------------------"<<endl;
	/*根据阵营战类型，选择加入不同的阵营战.*/
	int campWarType=campWardata.campWarType;	cout<<"-------------------------233-------------------------"<<endl;
	switch(campWarType)
	{
	case 1:																//添加到普通阵营战中；
		campWarController.exitFromOrdinayCampWar(heroId,campWardata.campWarRoomNum,1);	
	break;
	case 2:																//添加到统领争夺阵营战中；
		campWarController.exitFromLeaderCampWar(heroId);	
	break;
	case 3:																//添加到盟主争夺阵营战中；
		campWarController.exitFromChiefCampWar(heroId);	
	break;
	case 4:
		campWarController.exitCampResWar(myHero);
		break;
	default:
	break;
	}
	cout<<"[BisonShow] the hero's all data has been dealed before close the server"<<endl;
	// myHero->memHero->rewarddata.offline_time = MY_TV_SEC;		//记录下线时间（秒）
	//放在最后，以防有在这之前没存到memcached中的数据 by bison
	myHero->memSet();
	/*jolly修改,人物数据全部保存后,让宠物下线*/
	Pet_Box *pet_box=myHero->getPetBox();
	Pet *pet=pet_box->getActivePet();
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	if(pet!=NULL)
	{					
		cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
		map<string,Pet*>::iterator it;
		string pet_identity=pet->getIdentity();
		it=id_to_activePet.find(pet_identity);
		if (it==id_to_activePet.end())
		{
			cout<<"error-------------------------------------exit_exception.cpp 259"<<endl;
		}
		else
		{	
			cout<<"##################################################"<<endl;
			// id_to_activePet.erase(it);	
			pet->send_msg_downLine(myHero);
			// myHero->stopPetTimer();
			cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		}
	}	
}
