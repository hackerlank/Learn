/*
		文件类型：实现文件
		文件名称：user_role_manage_assist.cpp
		文件作用：在用户角色管理部分起辅助作用的函数的实现
		修改内容：添加了一个string类型转换为int的方法，这个方法以后可能会去除3
		修改人：Evan
		修改时间：2012.3.22 10:56
*/
#include<stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<time.h>
#include"library_head.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"

#include"user_role_manage_assist.h"

extern map<string, Hero*> heroId_to_pHero;

extern int sock_fd;

/*********因为从配置文件读取的数据都是string类型的，放到全局变量的时候w为转换******/
int stringToint(string value)
{
	char *tmp;
	tmp = &value[0];
	int i = atoi(tmp);
	return i;

}

//add chenzhen 5.14 
void sendLogMsg(Hero *myHero)
{
	map<string, Hero*>::iterator hero_it; 
	string mapId ;
	string msg_broadcast; 
	string msg_broadcast_head = "2";
	int connect_fd ;
	Hero *other_hero;
	connect_fd = myHero->getFd();
	mapId = myHero->getMapId();
	string msg_other;
	for(hero_it = heroId_to_pHero.begin();hero_it != heroId_to_pHero.end();hero_it++)
	{
		other_hero = hero_it->second;
		
		if(strcmp(mapId.c_str(),other_hero->getMapId()) != 0)
		{
			continue;
		}				
		//通知在线角色，有新角色进入
		msg_broadcast += msg_broadcast_head;

		msg_broadcast += intTostring(LOGIN_RETURN_OTHER);

		msg_broadcast += ",";

		msg_broadcast += HERO_TYPE;
	
		msg_broadcast += "," ;
		msg_broadcast +=  myHero->getIdentity();

		msg_broadcast += charTostring(myHero->getNickName());

		msg_broadcast += "," ;
		msg_broadcast +=  myHero->getPhotoId();

		msg_broadcast += charTostring(myHero->getParty());

		msg_broadcast += intTostring(myHero->getLifeUpperVal());            //获得生命上限值

		msg_broadcast += intTostring(myHero->getLifeVal());                 //获得当前生命值

		msg_broadcast +=  intTostring(myHero->getMagicUpperVal());          //获得魔法上限值

		msg_broadcast +=  intTostring(myHero->getMagicVal());               //获得当前魔法值

		msg_broadcast +=  intTostring(myHero->getAtk_range());          //获得当前攻击角色攻击范围

		msg_broadcast += intTostring((myHero->getLocation())._x);

		msg_broadcast += intTostring((myHero->getLocation())._y);
	//	cout<<"in enter_scene,msg_broadcast: "<<msg_broadcast<<endl;
      
		map<string,Skill*> others_skill;
		map<string,Skill*>::iterator iter_others;

		
		
		msg_other.clear();
		msg_other += msg_broadcast_head;  
              
		if(connect_fd == other_hero->getFd())
		{
			continue;
		}
           //Evan add 发送给其他玩家 当前登录玩家的信息
        send_msg(other_hero->getFd(),const_cast<char*>(msg_broadcast.c_str()));        

            //生成其他角色的信息
        msg_other += intTostring(LOGIN_RETURN_OTHER);

        msg_other += "," ; 
        msg_other += HERO_TYPE;

        msg_other += charTostring(other_hero->getIdentity());
        msg_other += charTostring(other_hero->getNickName());

        msg_other = "," + other_hero->getPhotoId();

        msg_other += charTostring(other_hero->getParty());

        msg_other += intTostring(other_hero->getLifeUpperVal());

        msg_other += intTostring(other_hero->getLifeVal());    

        msg_other += intTostring(other_hero->getMagicUpperVal());  

        msg_other += intTostring(other_hero->getMagicVal());

        msg_other += intTostring(other_hero->getAtk_range());

		msg_other += intTostring(other_hero->getLocation()._x);    

		msg_other += intTostring(other_hero->getLocation()._y);     

		// others_skill = other_hero->getSkill_list();

		// int skillsize_others = others_skill.size() - 1;
		// string skillCount_others = intTostring(skillsize_others);               //玩家掌握的技能总数
         // msg_other = msg_other + skillCount_others;

         // iter_others = others_skill.begin();

         // string skill_msg_others;
         // string skillId_others;
         // string skillLevel_others;

        // if(skillsize_others > 0)
        // {
                // for(iter_others;iter_others != others_skill.end();++iter_others)
                // {
                    // Skill *skill_others = iter_others->second;

                    // if(((skill_others->getid()).substr(1,3)).compare("000") == 0)  //2012.5.28
                    // {
                        // continue;
                    // }
                    // skill_msg_others = skill_msg_others + "," + skill_others->getid(); //2012.5.28
                    // skill_msg_others += intTostring(skill_others-> getskill_grade()); //2012.5.28
                // }
         // }
          // msg_other += skill_msg_others;
          send_msg(connect_fd, const_cast<char*>(msg_other.c_str()));  
			
	}
	
	
	map<string,MonsterBase*>::iterator monmap_it;
	Map_Inform *map_now = myHero->getMap();
	MonsterBase *monster_now;
			
} 

void heroWearEquip(char *buffer)		//add jolly 10.14
{	
	cout<<"4,7"<<endl;
	pg_hero->msg_wearEquip(g_out_buf,sizeof(g_out_buf));
	send_msg(pg_hero->getFd(),g_out_buf);
}

void heroWearEquipDestory(char *buffer)		//add jolly 10.14
{
	MSG_BEGIN(buffer, g_msg_len)
	
	MSG_CHAR(char *id_c)				//人物实例id
	string id;
	
	MSG_CHAR(char *index_c)				//装备索引
	int index = atoi(index_c);
	
	MSG_CHAR(char *identity_c)			//装备实例id
	string identity=identity_c;
	
	Hero *hero=pg_hero;
	
	if (hero==NULL)
	{
		cout<<"jolly:error user_role_manage_assist 196"<<endl;
	}
	else
	{
		hero->destoryWearEquip(index,identity);
	}
}
