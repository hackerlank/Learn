#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"hero.h"
#include"bag.h"
#include"map_inform.h"
#include"equipment.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"boxAsist.h"
using namespace std;
extern map<string, Hero*> heroId_to_pHero;
extern char server_name[10];
extern char g_out_buf[20480];

void putOnEquip(Hero *hero,int index,char *goodsid)
{

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
	
	string equip_msg_others = "3";//发送给周围玩家
	equip_msg_others = equip_msg_others + intTostring(HERO_CHANGE_EQUIP_OTHERS);
	/*第二，从背包内获取该装备的实例信息*/
	Bag *bag_hero=hero->getBag();
	Equipment *equip = getEquipFromBag(hero,index); 
	if(equip == NULL)
	{
		cout<<"equip_hero_manage_wear:the bag not has this equip!"<<endl;
		return;
	}
	char *party_hero = hero->getParty();
	char* party_equip = equip->getparty();
	if (strcmp(party_equip,"R")==0)
	{
		//是坐骑装备给坐骑穿上
		rideWearEquip(hero,equip,index);
		return;
	}
	//门派不匹配
	cout<<"party_equip"<<party_equip<<endl;
	if(strcmp( party_hero, party_equip) != 0&&strcmp(party_equip,"W")!=0)
	{
		cout<<"equip_hero_manage_wear:the party not same!"<<endl;
		msg_error(g_out_buf,84);
		send_msg(hero->getFd(),g_out_buf);
		return;
	}
	int grade_equip = equip->getgrade();
	int grade_hero = hero->getLevel();
	//玩家等级不够
	if(grade_equip>grade_hero)
	{
		cout<<"equip_hero_manage_wear:the equip grade is high!"<<endl;
		msg_error(g_out_buf,85);
		send_msg(hero->getFd(),g_out_buf);
		return;
	}
	
	/*jolly 修改,若玩家身上该部位有装备 则先脱下,再穿上9.26*/
	int	equiptype = equip->gettype();		
	
	/*第三，玩家穿上该装备改变自身属性的改变*/
	char* identity = equip->getentityid();
	bag_hero->initGrid(index,0);
	
	Equipment *equip_before=hero->getWearEquip(equiptype);
	int before_flag=0;
	if (equip_before!=NULL)
	{
		before_flag=1;
		int iswear = 0;
		equip_before->setisbag(iswear);//装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31
		//玩家首先要脱掉身上该部位穿有的装备并改变当前玩家属性
		int type_num = -1;
		ChangeEquipToHero(hero,equip_before,type_num);	//改变角色属性
		int fd = hero->getFd();
		
		/*玩家脱去的装备是否属于玩家身上套装的一部分 evan add 2012.8.31*/
		int type_n = 2;//玩家脱装备
		SuitManage(hero,equip_before,type_n);
		// delete [] equip_before;		//释放内存		
	}		
	
	wearEquip(hero,equip);
	//若穿的是时装,则进行一下操作,start jolly 2012.12.19
	if (equiptype==0||equiptype==13)
	{
		equip->beginTime();
	}
	//若穿的是时装,则进行一下操作,end jolly 2012.12.19
	
	equip->wareEquipSetBound();
	hero->saveHeroEquip(equiptype,identity,equip->getid(),1);
	/*第四，消息的回发*/
	//第一，发送给当前玩家	
	goodsid=equip->getid();
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",3,HERO_CHANGE_EQUIP,1,identity,goodsid,equiptype,hero->getLifeUpperVal(),hero->getLifeVal(),hero->getMagicUpperVal(),hero->getMagicVal(),index,hero->getOutAttack(),hero->getInAttack(),hero->getOutDefense(),hero->getInDefense(),hero->getHited(),hero->getDodge(),hero->getCrit(),hero->getTenacity());
	send_msg(hero->getFd(),g_out_buf);  //发送给当前玩家
	cout<<"ME wear msg:"<<g_out_buf<<endl;
	//第二，发送给周围玩家
	if(equiptype==2 || equiptype==7 ||equiptype==0 ||equiptype==13)
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%s,%s",3,HERO_CHANGE_EQUIP_OTHERS,hero->getIdentity(),equiptype,grade_equip,goodsid,equip->getPhotoId());
		myBox->sentBoxMsg(g_out_buf);
		cout<<"OTHER wear msg:"<<g_out_buf<<endl;
		send_msg_useSuccess(hero,index);
	}
	cout<<"id is :"<<equip->getid()<<endl;
	if (before_flag==1)
	{
		takeOffEquipToBag(hero,equip_before);		//将已有的装备从身上放到背包里	
	}
	
	/*记录使用装备的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s",7,2,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,equip->getname(),equip->getentityid());
	write_log(account_msg);	
	/*记录使用装备的流水账 jolly 12.11 end*/
	
	hero->send_msg_att();
	
	/*给头衔*/
	hero->titleOfPurpleEquip();
	
	if (hero->getAllFourDiamonNumber()==30)
	{
		hero->updataSingleTarget(7,3);
	}
}

//坐骑穿装备的方法
void rideWearEquip(Hero *hero,Equipment *equipment,int bagIndex)
{
	if (hero==NULL||equipment==NULL)
	{
		return;
	}
	Ride *ride=hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	
	cout<<"jolly:ride wear equip now"<<endl;
	
	int index=equipment->gettype();
	index=index-111;
	if (index<0||index>3)
	{
		return;
	}
	
	ride->decreaseAtt(hero);
	if (ride->judgeEquipWear(index))
	{
		//穿了装备 那么就先脱下来 
		Equipment *wearingEquipment=hero->getEquip(ride->getEquipmentIdentity(index));
		if (wearingEquipment!=NULL)
		{
			ride->takeOffEquip(wearingEquipment,index);
			saveEquipIntoBag(hero,wearingEquipment);
		}
	}

	//穿装备 
	ride->wearEquip(equipment,index);
	ride->increaseAtt(hero);
	equipment->wareEquipSetBound();
	bag->initGrid(bagIndex);
	send_msg_useSuccess(hero,bagIndex);
		
	memset(g_out_buf,0,sizeof(g_out_buf));
	ride->ride_wear_equip(g_out_buf,sizeof(g_out_buf),index,equipment->getentityid(),equipment->getid());
	send_msg(hero->getFd(),g_out_buf);
	hero->send_msg_att();
}