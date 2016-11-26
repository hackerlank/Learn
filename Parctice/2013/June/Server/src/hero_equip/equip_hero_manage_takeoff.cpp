#include<string>
#include<iostream>
#include<map>
#include"user_role_manage_equip.h"
#include"hero.h"
#include"bag.h"
#include"map_inform.h"
#include"equipment.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"nbox.h"
using namespace std;
extern map<string, Hero*> heroId_to_pHero;

#include "wholeDefine.h"
extern char g_out_buf[20480];
extern char server_name[10];

/*
完成内容：完成穿装备的方法实现
完成时间：2012.8.23
完成人：Evan
*/
void equipchange(char *buffer)			//jolly 修改 9.26
{
	MSG_BEGIN(buffer, g_msg_len)
	MSG_CHAR(char *type_char)	//玩家操作装备类型
	int  type=atoi(type_char);
	MSG_CHAR(char *heroId)		//玩家ID
	MSG_CHAR(char *equip_num)	//装备在背包中的索引
	int  equip_number = atoi(equip_num);
	MSG_CHAR(char *equipId)	//装备ID
	MSG_CHAR(char *equip_type)	//装备类型
	int	 equiptype = atoi(equip_type);		//装备类型
	
	takeOffEquip(heroId,equip_number,equipId,equiptype);
}


bool takeOffEquip(string heroId,int equip_number,string equipId,int equiptype)				//jolly根据上面的修改,提取方法 9.26
{
	string equip_msg = "3";		//发送给当前玩家
	equip_msg = equip_msg + intTostring(HERO_CHANGE_EQUIP);
	string equip_msg_others = "3";//发送给周围玩家
	equip_msg_others = equip_msg_others + intTostring(HERO_CHANGE_EQUIP_OTHERS);
	/*第二，获取玩家实例以及将要脱掉装备的实例*/	
	map<string, Hero*>::iterator roleId_it;
	roleId_it = heroId_to_pHero.find(heroId);    
	if(roleId_it==heroId_to_pHero.end())       
	{	
		cout<<"jolly:hero error equip_hero_manage_takeoff 168"<<endl;
		return false;	
	}
	else
	{			
		Hero *hero;
		hero = roleId_it -> second;  				//玩家角色实例
		Map_Inform *map_now;
		Nbox *myBox;
		map_now = hero->getMap();
		if(map_now == NULL)
		{
			return false;
		}
		myBox = map_now->getBox();
		if(myBox == NULL)
		{
			return false;
		}
		
		StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);
		myBox->getStaInSrcVec(obj);	
		// cout<<"4,7,"<<<<heroId<<","<<equip_number<<","<<equipId<<","<<equiptype<<endl;
		// cout<<"####################################################################"<<endl;
		// cout<<"equip_type:"<<equip_type<<endl;
		// cout<<"equiptype:"<<equiptype<<endl;
		// cout<<"size:"<<hero_equipment_map.size()<<endl;
		// cout<<"####################################################################"<<endl;
		
		Equipment *equip=hero->getWearEquip(equiptype);
		if(equip == NULL)
		{
			// cout<<"1111111111111111111111111111111111111111"<<endl;
			equip_msg = equip_msg + intTostring(FAILED); 
			send_msg(hero->getFd(),const_cast<char*>(equip_msg.c_str()));
			return false;
		}
		else
		{			
			/*第三，将装备从玩家身上脱掉*/							
			hero->setWearEquip(equiptype,NULL);	//从当前部位删除掉
			/*第三：第一，玩家脱去的装备是否属于玩家身上套装的一部分  evan add 2012.8.31*/
			int type_n = 2;//玩家脱装备
			SuitManage(hero,equip,type_n);
			/*第三：第二，装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31*/
			int iswear = 0;
			equip->setisbag(iswear);
			
			int type_num = -1;
			ChangeEquipToHero(hero,equip,type_num);	//改变角色属性
			/*jolly 修改 8.28*/
			if (equip_number==-1)
			{
				takeOffEquipToBag(hero,equip);		//将已有的装备从身上放到背包里	
			}
			else if (equip_number!=-2)
			{
				takeOffEquipToBag(hero,equip_number,equip);		//将已有的装备从身上放到背包里	
			}
			/*????????????????判断背包是否已满????????????????????*/
			
			/*第四，消息的回发*/
			char* identity = equip->getentityid();
			// hero->saveHeroEquip(equiptype,identity,equip->getid(),0);
			int    grade= equip->getgrade();
			int    index=hero->getBag()->getNextGoodsIndex();
			//第一，发送给当前玩家	
			equip_msg = equip_msg + intTostring(2);
			equip_msg += charTostring(identity);
			equip_msg = equip_msg + "," + equipId;
			equip_msg = equip_msg +intTostring(equiptype);
			equip_msg = equip_msg + intTostring(hero->getLifeUpperVal());
			equip_msg = equip_msg + intTostring(hero->getLifeVal());
			equip_msg = equip_msg + intTostring(hero->getMagicUpperVal());
			equip_msg = equip_msg + intTostring(hero->getMagicVal());
			equip_msg = equip_msg +intTostring(index);
			equip_msg+=intTostring(hero->getOutAttack());
			equip_msg+=intTostring(hero->getInAttack());
			equip_msg+=intTostring(hero->getOutDefense());
			equip_msg+=intTostring(hero->getInDefense());
			equip_msg+=intTostring(hero->getHited());
			equip_msg+=intTostring(hero->getDodge());
			equip_msg+=intTostring(hero->getCrit());
			equip_msg+=intTostring(hero->getTenacity());
			send_msg(hero->getFd(),const_cast<char*>(equip_msg.c_str()));  //发送给当前玩家
			cout<<"ME take off msg:"<<equip_msg<<endl;
			//第二，发送给周围玩家
			if(equiptype==2 || equiptype==7 || equiptype==0	||equiptype==13)
			{
				equip_msg_others = equip_msg_others + "," + hero->getIdentity();
				equip_msg_others = equip_msg_others + intTostring(equiptype);
				equip_msg_others = equip_msg_others + intTostring(0);		//jolly 修改9.23
				equip_msg_others = equip_msg_others +"," + equipId;
				equip_msg_others += ",0";
				// sendMsg_Nine(hero,equip_msg_others);
				// send_msg(hero->getFd(),equip_msg_others);
				myBox->sentBoxMsg(const_cast<char*>(equip_msg_others.c_str()));
				// sentBoxMsg(nbox_id_set,equip_msg_others);
				cout<<"OTHER take off msg:"<<equip_msg_others<<endl;
			}			
			/*记录使用装备的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s",7,3,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),equip->getid(),equip->getname(),identity);
			write_log(account_msg);	
			/*记录使用装备的流水账 jolly 12.11 end*/
			
			hero->send_msg_att();
		}
	}
}

void heroDropEquipment(Hero *hero,Equipment *equip)
{
	if (hero==NULL)
	{
		return;
	}
	if (equip==NULL)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",3,HERO_CHANGE_EQUIP,FAILED);
		send_msg(hero->getFd(),g_out_buf);
		return;
	}
	
	/*第二，获取玩家实例以及将要脱掉装备的实例*/			
	Map_Inform *map_now;
	Nbox *myBox;
	map_now = hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	myBox = map_now->getBox();
	if(myBox == NULL)
	{
		return;
	}
	
	StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);
	myBox->getStaInSrcVec(obj);	
	// cout<<"4,7,"<<<<heroId<<","<<equip_number<<","<<equipId<<","<<equiptype<<endl;
	// cout<<"####################################################################"<<endl;
	// cout<<"equip_type:"<<equip_type<<endl;
	// cout<<"equiptype:"<<equiptype<<endl;
	// cout<<"size:"<<hero_equipment_map.size()<<endl;
	// cout<<"####################################################################"<<endl;
	
	int equiptype=equip->gettype();
	/*第三，将装备从玩家身上脱掉*/							
	hero->setWearEquip(equiptype,NULL);	//从当前部位删除掉
	/*第三：第一，玩家脱去的装备是否属于玩家身上套装的一部分  evan add 2012.8.31*/
	int type_n = 2;//玩家脱装备
	SuitManage(hero,equip,type_n);
	/*第三：第二，装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31*/
	int iswear = 0;
	equip->setisbag(iswear);
	
	int type_num = -1;
	ChangeEquipToHero(hero,equip,type_num);	//改变角色属性
	
	/*第四，消息的回发*/
	char* identity = equip->getentityid();
	// hero->saveHeroEquip(equiptype,identity,equip->getid(),0);
	int    index=hero->getBag()->getNextGoodsIndex();
	//第一，发送给当前玩家	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",3,HERO_CHANGE_EQUIP,2,equip->getentityid(),\
	equip->getid(),equiptype,hero->getLifeUpperVal(),hero->getLifeVal(),hero->getMagicUpperVal(),hero->getMagicVal(),index,hero->getOutAttack(),hero->getInAttack(),\
	hero->getOutDefense(),hero->getInDefense(),hero->getHited(),hero->getDodge(),hero->getCrit(),hero->getTenacity());
	// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s,%d",3,HERO_CHANGE_EQUIP,2,equip->getentityid(),equip->getid(),equiptype);
	send_msg(hero->getFd(),g_out_buf);  //发送给当前玩家
	cout<<"ME take off msg:"<<g_out_buf<<endl;
	//第二，发送给周围玩家
	if(equiptype==2 || equiptype==7 || equiptype==0	||equiptype==13)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%s,%s",3,HERO_CHANGE_EQUIP_OTHERS,hero->getIdentity(),equiptype,0,equip->getentityid(),"0");
		// sendMsg_Nine(hero,equip_msg_others);
		// send_msg(hero->getFd(),equip_msg_others);
		myBox->sentBoxMsg(g_out_buf);
		// sentBoxMsg(nbox_id_set,equip_msg_others);
		cout<<"OTHER take off msg:"<<g_out_buf<<endl;
	}	
	
	/*记录使用装备的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s",7,3,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),equip->getid(),equip->getname(),identity);
	write_log(account_msg);	
	/*记录使用装备的流水账 jolly 12.11 end*/
	
	hero->send_msg_att();
}

//时装到期,脱时装并摧毁的方法
void fasionDestory(Hero *hero,int _index,char *identity)
{
	/*第二，获取玩家实例以及将要脱掉装备的实例*/	
	if (hero==NULL||identity==NULL)
	{
		return;
	}	
	Map_Inform *map_now = hero->getMap();
	if(map_now == NULL)
	{
		return;
	}	
	Nbox *myBox = map_now->getBox();
	if(myBox == NULL)
	{
		return;
	}
	
	StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);
	myBox->getStaInSrcVec(obj);	
	
	Equipment *equip=hero->getEquip(identity);			//时装类型为0
	memset(g_out_buf,0,sizeof(g_out_buf));
	if(equip == NULL)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",3,HERO_CHANGE_EQUIP,FAILED);
		send_msg(hero->getFd(),g_out_buf);
		return;
	}
	else
	{		
		if (equip->getIsBag()==1)
		{			
			/*第三，将装备从玩家身上脱掉*/							
			hero->setWearEquip(_index,NULL);	//从当前部位删除掉
			/*第三：第一，玩家脱去的装备是否属于玩家身上套装的一部分  evan add 2012.8.31*/
			int type_n = 2;//玩家脱装备
			SuitManage(hero,equip,type_n);
			/*第三：第二，装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31*/
			int iswear = 0;
			equip->setisbag(iswear);
			
			int type_num = -1;
			ChangeEquipToHero(hero,equip,type_num);	//改变角色属性
			
			/*第四，消息的回发*/
			int    grade= equip->getgrade();
			int    index=hero->getBag()->getNextGoodsIndex();
			//第一，发送给当前玩家			
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",3,HERO_CHANGE_EQUIP,2,equip->getentityid(),equip->getid(),_index,\
			hero->getLifeUpperVal(),hero->getLifeVal(),hero->getMagicUpperVal(),hero->getMagicVal(),-1,hero->getOutAttack(),hero->getInAttack(),\
			hero->getOutDefense(),hero->getInDefense(),hero->getHited(),hero->getDodge(),hero->getCrit(),hero->getTenacity());
			send_msg(hero->getFd(),g_out_buf);
			cout<<"ME take off msg:"<<g_out_buf<<endl;
			//第二，发送给周围玩家
			char equip_msg_others[1024]={0};
			snprintf(equip_msg_others,sizeof(equip_msg_others),"%d,%d,%s,%d,%d,%s,%d",3,HERO_CHANGE_EQUIP_OTHERS,hero->getIdentity(),_index,0,equip->getid(),0);
			myBox->sentBoxMsg(equip_msg_others);		
			
			hero->send_msg_att();	
		}
		
		/*记录使用装备的流水账 jolly 12.11 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s",7,3,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),equip->getid(),equip->getname(),equip->getentityid());
		write_log(account_msg);	
		/*记录使用装备的流水账 jolly 12.11 end*/		
		
		hero->deleteEquip(identity);
		
		memset(g_out_buf,0,sizeof(g_out_buf));
		if (_index==0)
		{
			msg_error(g_out_buf,106);
		}
		else if  (_index==13)
		{
			msg_error(g_out_buf,120);
		}
		send_msg(hero->getFd(),g_out_buf);
	}
}

void rideTakeOffEquip(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag);
	MSG_CHAR(char *id)		
	MSG_CHAR(char *identity)	
	MSG_INT(int type)			//装备类型
	MSG_INT(int index)			//背包中索引
	
	cout<<"30,1,"<<flag<<","<<identity<<","<<id<<","<<type<<","<<index<<endl;
	
	Ride *ride=pg_hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	if (type<0||type>3)
	{
		return;
	}
	if ((index<0||index>95)&&index!=100000)
	{
		return;
	}
	if (flag!=1&&flag!=0)
	{
		return;
	}
	
	if (strcmp(identity,ride->getEquipmentIdentity(type))==0)
	{
		Equipment *equip=pg_hero->getEquip(identity);
		if (equip==NULL)
		{
			return;
		}
		ride->decreaseAtt(pg_hero);
		ride->takeOffEquip(equip,type);
		ride->increaseAtt(pg_hero);
		memset(g_out_buf,0,sizeof(g_out_buf));
		ride->ride_takeoff_equip(g_out_buf,sizeof(g_out_buf),type,identity,id);
		send_msg(pg_hero->getFd(),g_out_buf);
		
		pg_hero->send_msg_att();
		
		if (flag==1)
		{
			if (index==100000)
			{		
				takeOffEquipToBag(pg_hero,equip);
			}
			else
			{
				takeOffEquipToBag(pg_hero,index,equip);
			}
		}
		else
		{
			pg_hero->deleteEquip(identity);
		}
	}
	else
	{
		//装备数据对不上
		cout<<"equipment is not suit in ride equipment takeoff"<<endl;
		cout<<"identity:"<<identity<<endl;
		cout<<"ride->getEquipmentIdentity(type):"<<ride->getEquipmentIdentity(type)<<endl;
	}
}