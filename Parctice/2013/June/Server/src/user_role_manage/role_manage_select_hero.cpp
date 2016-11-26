/*
文件类型：角色管理，选择角色
文件名称：role_manage_select_hero.cpp
创建时间：2012.3.16
author：	Tory
*/
#include"command_user_role_manage.h"

#include"command_return_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"

#include"map_inform.h"

#include"skill.h"

#include"task_configuration.h"

#include"npc_configuration.h"

#include"task.h"

#include"npc.h"

#include<map>

#include<set>

#include<stdlib.h>

#include <sstream>

#include <iostream>

#include <string>

#include"timerContainer.h"

#include "pet.h"

//缓存操作头文件
#include "my_memcached.h"
//邮件系统操作头文件
#include "mail_systerm_interface.h"
//重启经脉时使用
#include"meridian_asist.h"
//重复选择相同角色进入游戏，断开上一个fd对应的连接
#include "libev.h"

#include"heroCpyRecord.h"

#include"hero_skill_asist.h"

#include "mailSysterm.h"

#include"cpyAsist.h"

#include "wholeDefine.h"
//缓存服务器管理类
#include "my_mem_group.h"

extern MyMemGroup* mem_group;

#include"statuaryAsist.h"

#include "systemMessage.h"

extern int sock_fd;
//事件主循环
extern struct ev_loop *loops;
//	与套接字描述符绑定的消息接收队列
extern map<int, Message_Receive>   message_queue;
//缓存操作类实例指针，全局变量
extern MyMemcache *mem_operate;


extern int sock_fd;

//引用保存在线玩家所创建的角色拥有的邮件数据的全局变量
extern map<string, MailSysterm *> mail_map;  
//引用全局变量声明
extern map<int, Role *> fd_to_pRole;
//全局变量引用声明，Hero ID索引Hero对象指针的map容器，管理所有已初始化的Hero对象
extern map<string, Hero *> heroId_to_pHero;

extern char server_name[10];

using namespace std;

void selectHero(char *buffer)
{
    int fd = sock_fd;
    MSG_BEGIN(buffer, g_msg_len)

    MSG_CHAR(char* user_name)
    cout << "user_name:" << user_name << endl;

    MSG_CHAR_END(char* hero_id)
    cout << "hero id:" << hero_id << endl;

    string msg_body;
    string msg_head = "1";

    if (strlen(hero_id) > 38)
    {
        cout << "role_manage_select_hero.cpp, parse heroID isn't fit" << endl;
        msg_body = msg_head + intTostring(CREATE_HERO_RETURN) + intTostring(FAILED);
        send_msg(fd, const_cast<char *>(msg_body.c_str()));
        return;
    }
    string heroId = hero_id;

    map<int, Role *>::iterator iter_r;
    iter_r = fd_to_pRole.find(fd);
    if (iter_r == fd_to_pRole.end())
    {
        cout << "role_manage_select_hero.cpp:111" << endl;
        return;
    }
    Role *player = iter_r->second;

    //一个用户不准登陆其他用户的hero
    list<My_hero_infor> my_hero_list = player->getHero_infor_list();
    list<My_hero_infor>::iterator iter = my_hero_list.begin();
    for (iter; iter != my_hero_list.end(); iter++)
    {
        My_hero_infor my_hero_infor = *iter;
        if (strcmp(my_hero_infor.heroId, hero_id) == 0)
        {
            goto LE;
        }
    }
    cout << "The role try login other's hero!!!!!!!!!!!!!!!!!!" << endl;
    return;
LE:;;
    map<string, Hero *>::iterator iter_h;
    iter_h = heroId_to_pHero.find(heroId);
    Hero *myHero = NULL;
	//选择进的角色已经在线，则将在线的角色踢下线
    if (iter_h != heroId_to_pHero.end()) 
    {
        myHero = iter_h->second;
        if (myHero->getFd() == sock_fd)  //客户端同时发了两次角色选择的消息过来<Tory 有这可能吗？>
        {
            return;
        }
        //关闭套接字和释放事件驱动指针
        int pre_fd = myHero->getFd();
        closeConnect(pre_fd);
    }

    int size = 0;
	int where = 0;
    // char *pmem = mem_operate->get_mem_data(heroId, &size);
	char *pmem = mem_group->get_data(heroId, &size, &where);
	cout<<"@@Tory the pmem is come from:"<<where<<endl;
	if(pmem == NULL)
	{
		return;
	}
    MemHero *mem_data_hero = (MemHero *)malloc(sizeof(MemHero));
    memset(mem_data_hero, '\0', sizeof(MemHero));
    
	size = size < sizeof(MemHero) ? size : sizeof(MemHero);
    memcpy(mem_data_hero, pmem, size);
    free(pmem);
	
	
	
    if (mem_data_hero != NULL)
    {
        cout << "------new Hero from memcached server--------" << endl;
        //	show_memHero_data(mem_data_hero);
        try
        {
            myHero = new Hero(mem_data_hero, fd, player->getArea());
        }
        catch (exception e)
        {
            return;
        }

        if (myHero == NULL)
        {
            return;
        }

        pair<map<string, Hero*>::iterator, bool> ret;
        ret =  heroId_to_pHero.insert(map<string, Hero *>::value_type(myHero->getIdentity(), myHero)); //将选择进行游戏的角色放入在线容器中
        if (ret.second == true) 
		{
			cout << "insert Hero* to heroId_to_pHero success" << endl;
        }
		else
		{
			cout << "insert Hero* to heroId_to_pHero failure" << endl;
		}
		
		/*校正体力值*/
		myHero->adjustFatigue();
		myHero->adjustTeamerId();
        player->setActive_heroId(heroId);   //将玩家选择进行游戏的角色Id设置为活动角色ID
        player->setActive_hero(myHero);     //将玩家选择进行游戏的角色设置为活动角色
#if 0		
		myHero->setCamp(rand() % 3);
        myHero->setExpNow(210000);
        // myHero->setExpNow(2100000000);
        // increaseBoundGold(myHero, 200000000);
        // increaseGold(myHero, 2000000000);
        // increaseGameMoney(myHero, 300000000);
#endif		
        //重启经脉
        restartMeridStudy(myHero);

        //生成角色出现在场景中的消息
        myHero->initTitle();                    //初始化头衔,xhm added;
        string  come_into_scene_msg = CreateMessage::come_into_scene(myHero);
        send_msg(fd, const_cast<char *>(come_into_scene_msg.c_str()));
		
		myHero->checkTitle();
		
		// char fatigueMsg[200] = {'\0'};
		// sprintf(fatigueMsg,"8,12,%s,%d,%d",myHero->getIdentity(),myHero->memHero->lastStrength,myHero->memHero->fatigueUpperVal);
		// send_msg(fd, fatigueMsg);
		
        // view_hero_skills_info_comm(myHero);

        //加载角色的邮件数据至game server中
        MailSystermInterface::load_mail_data(heroId);
        cout << "after load_mail_data,mail_map.size()" << mail_map.size() << endl;

        /*副本进入状态*/
        HeroCpyRecord *myCpyRecord;
        myCpyRecord = myHero->getCpyRecord();
        if (myCpyRecord != NULL)
        {
            myCpyRecord->setOwner(myHero);
        }
        myHero->initTongBuTimer();	
		
        /*记录角色上线的流水账 jolly 12.10 start*/
        char account_msg[1024] = { '\0' };
        snprintf(account_msg, sizeof(account_msg), "%d,%d,%s,%d,%s,%s,%s", 1, 2, server_name, (int)myTime.tv_sec, pg_role->getUserName(), myHero->getIdentity(), myHero->getNickName());
        write_log(account_msg);
	

	 /*全服广播 玩家上线了*/
         char info[1024]={'\0'};
         snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,0,0",7,SYSTEM_WARN,"xf029",1,1,myHero->getNickName(),myHero->getIdentity());
         map<string, Hero*>::iterator it_hero;

         for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
         {
              if (it_hero->second!=NULL)
              {
                   send_msg(it_hero->second->getFd(),info);
              }
          }

        /*记录角色上线的流水账 jolly 12.10 end*/
    } else
    {
        cout << "this key:" << heroId << "have no data in memcached server" << endl;
        return;
    }
}

