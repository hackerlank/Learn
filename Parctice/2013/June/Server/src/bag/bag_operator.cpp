#include"bag_operator.h"
#include "wholeDefine.h"
#include"user_role_manage_equip.h"
#include"pet_operator.h"
#include"five_asist.h"
#include"five_elem_comm.h"
#include"vip.h"
#include"command_other_function_all_over.h"
#include"reward_recharge_config.h"
#include "hero_drugs_manage.h"
#include"boxAsist.h"
#include"GM_communicate.h"
#include"pick.h"
#include"data_structure_struct.h"
#include"campWarManagement.h"
#include"money_operator.h"
#include"ride.h"
#include"dropgoods.h"
#include "my_mem_group.h"
#include"monsterTool.h"
using namespace std;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Ride_Config*> id_to_ride;
extern map<string,Goods_Config*> id_to_dj;
extern map<int,int> campNumber;
extern map<string,Ointment *>id_to_ointment;
extern map<string,Goods_Config*> id_to_cl;
extern map<string ,VipDataInitial> vipDataStore;
extern map<string,Equip_config*>id_to_equip;
extern map<string,Reward_recharge_config*>sid_to_reward_recharge;
extern int sock_fd;
extern map<string,Pet_Config*> id_to_pet;
extern struct timeval myTime;
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern map<string,MonsterTool*> toolToMonster;
extern map<string,MonsterTool*> toolMonsterIdToInst;
extern char server_name[10];
extern campWarManagement campWarController; 
extern map<string,set<Equipment*> > bussinessEquip;
//缓存操作类实例指针，全局变量
extern MyMemGroup* mem_group;
extern Role *pg_role;
/**药品管理系统**/
/* extern Hero_Drugs_MNG* hero_drugs_MNG; */
//双击使用背包中的物品
void bag_useAllGoods(char *buffer)
{
	int type;
	int index;
	char *goodsid;
	char *identity;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(type);
	MSG_INT(index);
	MSG_CHAR(goodsid);
	MSG_CHAR_END(identity);
	
	cout<<"9,3,"<<type<<","<<index<<","<<goodsid<<","<<identity<<endl;
	
	/*解析数据处理*/
	if (type<0||type>4)		//判断type是否合法
	{
		return;
	}
	Bag *bag=pg_hero->getBag();					//取的hero下的背包指针
	if (bag==NULL)							//判断bag是否存在
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)				//判断index是否合法
	{
		return;
	}
	
	if (pg_hero->getLifeVal()>0)
	{
		if (bag->test(index,identity))		//验证背包中该索引下的物品是否与客户端发来的id一致
		{		
			char flag[10]={0};
			strncpy(flag,goodsid+2,6);		//取得物品的详细类型
			if (type==1)							//大类型为1,均为装备
			{
				putOnEquip(pg_hero,index,goodsid);			//玩家穿装备
			}
			else if (strcmp(flag,"dj_100")==0)
			{
				// if (useFiveElemGoods(pg_hero, goodsid, index, 20))
				// {
					// cout<<"BisonTest: use fiveElem pills !"<<endl;
					// 人物使用五行丹成功，可客户端刷新五行信息
					// char p[3] = "aa";
					// viewFiveElemComm(p);
				// }				
			}				
			else if (strcmp(flag,"dj_102")==0)
			{
				heroExpDrug(pg_hero,goodsid,index,1);				//玩家使用经验药品
			}	
			else if (strcmp(flag,"dj_103")==0)
			{
				petExpDrug(pg_hero,goodsid,index,1);				//玩家使用宠物经验药
			}
			else if (strcmp(flag,"dj_106")==0)
			{
				usePetAgg(pg_hero,goodsid,index);				//使用宠物蛋
			}
			else if (strcmp(flag,"dj_107")==0)
			{
				usePopularity(pg_hero,goodsid,index,1);			//使用声望书
			}
			else if (strcmp(flag,"dj_108")==0)		
			{
				
			}
			else if (strcmp(flag,"dj_109")==0)
			{
				drug_use_interface(pg_hero, goodsid, index);	//使用药膏
			}
			else if (strcmp(flag,"dj_112")==0)
			{
				useRewardBag(pg_hero,goodsid,index);			//使用礼包
			}
			else if (strcmp(flag,"dj_113")==0)
			{
				useGiftBag(pg_hero,goodsid,index);			//使用可以随机出物品的宝箱
			}
			else if (strcmp(flag,"dj_115")==0)
			{
				
			}
			else if (strcmp(flag,"dj_116")==0)
			{
				useMoneyBag(pg_hero,goodsid,index,1);				//使用宠物技能书
			}
			else if (strcmp(flag,"dj_118")==0)
			{
				useExpTimes(pg_hero,goodsid,index);				//使用多倍经验丹
			}
			else if (strcmp(flag,"dj_119")==0)					
			{
				useGiftBag(pg_hero,goodsid,index);			//使用圣诞礼包
			}
			else if (strcmp(flag,"dj_120")==0)
			{
				useGiftBag(pg_hero,goodsid,index);
			}
			else if (strcmp(flag,"dj_121")==0)					//使用春节红包
			{	
				useGiftBag(pg_hero,goodsid,index);
			}
			else if (strcmp(flag,"dj_122")==0)					//使用坐骑经验丹
			{	
				useRideExp(pg_hero,goodsid,index,1);
			}
			else if (strcmp(flag,"dj_123")==0)					//使用坐骑
			{	
				useRideAgg(pg_hero,goodsid,index);
			}
			else if (strcmp(flag,"dj_124")==0)
			{
				useEquipBag(pg_hero,goodsid,index);				//试用装备宝箱
			}
			else if (strcmp(flag,"dj_125")==0)
			{
				useRandomEquip(pg_hero,goodsid,index);			//试用随机装备包厢
			}
			else if (strcmp(flag,"dj_126")==0)
			{
				useDecreaseCrime(pg_hero,goodsid,index,1);			//洗红名道具
			}
			//可以使用的任务道具之“到指定地点使用的道具”
			else if (strcmp(flag,"rw_101")==0)
			{
				taskGoodsSpecialPosUse(pg_hero, goodsid, index);	//使用可以使用的任务道具
			}
			else if (strcmp(flag,"rw_102")==0)
			{
				taskGoodsSpecialPosUse(pg_hero, goodsid, index);	//使用可以使用的任务道具
				// useToolBruMon(pg_hero, goodsid, index);				//使用任务道具召唤怪物
			}
		}
	}
	else
	{
		cout<<"jolly:pg_hero is dead bag_operator 163"<<endl;
		msg_error(g_out_buf,50);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void mulityUse(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(int type);
	MSG_INT(int index);
	MSG_CHAR(char *goodsid);
	MSG_CHAR(char *identity);
	MSG_INT(int number)
	
	cout<<"9,7,"<<type<<","<<index<<","<<goodsid<<","<<identity<<","<<number<<endl;
	
	/*解析数据处理*/
	if (type!=2)		//判断type是否合法
	{
		return;
	}
	
	Bag *bag=pg_hero->getBag();					//取的hero下的背包指针
	if (bag==NULL)							//判断bag是否存在
	{
		return;
	}
	
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)				//判断index是否合法
	{
		return;
	}
	
	if (pg_hero->getLifeVal()>0)
	{
		if (bag->test(index,identity))		//验证背包中该索引下的物品是否与客户端发来的id一致
		{		
			if (bag->testNumber(index,number))
			{
				char flag[10]={0};
				strncpy(flag,goodsid+2,6);		//取得物品的详细类型
				if (strcmp(flag,"dj_100")==0)
				{
					// if (useFiveElemGoods(pg_hero, goodsid, index, 20))
					// {
						// cout<<"BisonTest: use fiveElem pills !"<<endl;
						// 人物使用五行丹成功，可客户端刷新五行信息
						// char p[3] = "aa";
						// viewFiveElemComm(p);
					// }				
				}				
				else if (strcmp(flag,"dj_102")==0)
				{
					heroExpDrug(pg_hero,goodsid,index,number);				//玩家使用经验药品
				}	
				else if (strcmp(flag,"dj_103")==0)
				{
					petExpDrug(pg_hero,goodsid,index,number);				//玩家使用宠物经验药
				}
				else if (strcmp(flag,"dj_107")==0)
				{
					usePopularity(pg_hero,goodsid,index,number);			//使用声望书
				}
				else if (strcmp(flag,"dj_116")==0)
				{
					useMoneyBag(pg_hero,goodsid,index,number);				//使用宠物技能书
				}
				else if (strcmp(flag,"dj_122")==0)							//使用坐骑经验丹
				{	
					useRideExp(pg_hero,goodsid,index,number);
				}
				else if (strcmp(flag,"dj_126")==0)
				{
					useDecreaseCrime(pg_hero,goodsid,index,number);			//洗红名道具
				}
			}			
		}
	}
	else
	{
		cout<<"jolly:pg_hero is dead bag_operator 163"<<endl;
		msg_error(g_out_buf,50);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void bagArrang(char *buffer)
{	
	int n;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(n);

	cout<<"9,12,"<<n;
	

	Bag *bag=pg_hero->getBag();
	if (bag==NULL)							//判断bag是否存在
	{
		return;
	}
	BagData newBagData;
	newBagData.bagnum=bag->getBagNum();
	newBagData.expandNeedGold=bag->getExpandNeedGold();
	int index;
	for (int i=0;i<n;i++)		//因为整理好的背包,索引肯定是从0开始整齐排列的,所以用循环操作,将从客户端得到的之前索引,放到循环下的索引中去
	{		
		MSG_INT(index);
		cout<<","<<index;
		newBagData.baggoodsdata[i]=bag->getBagGoodsData(index);
	}		
	cout<<endl;
	bag->setMemStruct(newBagData);			//保存背包数据
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,24,1);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void getEquipInform(char *buffer)
{
	char *identity;
	char *heroIdentity;
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(heroIdentity);
	MSG_CHAR_END(identity);
	
	Hero *hero=heroid_to_hero(heroIdentity);
	if (hero==NULL)
	{
		return;
	}
	
	Equipment *equip=hero->getEquip(identity);		//通过装备实例id找到装备的实例
	if (equip==NULL)
	{			
		cout<<"jolly:error bag_operator 266"<<endl;			
	}
	else
	{
		equip->msg_return_equipInform(g_out_buf,sizeof(g_out_buf));		//调用发送装备信息的函数
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void bag_operator(char *buff)
{
	int flag; //操作标志
	MSG_BEGIN(buff,g_msg_len);
    MSG_INT(flag);

		
	cout<<"9,0,"<<flag<<endl;
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)							//判断bag是否存在
	{
		return;
	}
	int bagNum=bag->getBagNum();
	
	if (flag==1)
	{
		
		int initindex;
		int finalindex;
		char *firstgoodsid;             //拖到的物品id
		char *secondgoodsid;            //拖动到的物品id,若没有则为空

		MSG_INT(initindex);
		MSG_INT(finalindex);		
		MSG_CHAR(firstgoodsid);		
		MSG_CHAR_END(secondgoodsid);
		
		cout<<flag<<","<<initindex<<","<<finalindex<<","<<firstgoodsid<<","<<secondgoodsid<<endl;

		if (initindex<0||initindex>bagNum)				//判断initindex是否合法
		{	
			return;
		}
		if (finalindex<0||finalindex>bagNum)			//判断finalindex是否合法
		{
			return;
		}
			
		if (!bag->isLocking(initindex)&&!bag->isLocking(finalindex))
		{
			if (bag->drag(initindex,finalindex,firstgoodsid,secondgoodsid))		//调用背包中的拖动函数
			{
				bag->msg_drag_success(g_out_buf,sizeof(g_out_buf),initindex,finalindex,firstgoodsid,secondgoodsid);
			}
			else
			{
				bag->msg_drag_failed(g_out_buf,sizeof(g_out_buf));
			}
		}
		else
		{
			bag->msg_drag_failed(g_out_buf,sizeof(g_out_buf));
			cout<<"jolly:goods has been locked bag_operator.cpp 324"<<endl;
		}
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==2)
	{
		int index; //拆分的物品索引
		int num;  //拆分的数量
		
		MSG_INT(index);
		MSG_INT(num);
		
		cout<<flag<<"   "<<index<<"   "<<num<<endl;
		
		if (index<0||index>bagNum)			//判断index是否合法
		{
			return;
		}

		splitGoods(pg_hero,index,num);	//调用背包中的拆分函数
		
	}
	else if (flag==3)
	{
		cout<<"jolly:erererererererererer  error error bag_operator 384"<<endl;
	}
	else if (flag==4)
	{	
		int num;
		MSG_INT(num);
		
		if (num<0)				//判断num是否合法
		{
			num=56;
			cout<<"jolly:expand number is minutes error bag_operator 439"<<endl;
		}
						
		if (expand(pg_hero,num))		//调用背包拓展函数
		{
			cout<<"Bag expand success bag_operator 367"<<endl;
		}
		else
		{
			cout<<"Bag expand failed bag_operator 371"<<endl;
		}
		
	}
	else if (flag==5)
	{
		char money_msg[1024]={'\0'};
		pg_hero->getMoney()->send_msg_money(money_msg,sizeof(money_msg));

		char bag_msg[20000]={'\0'};
		pg_hero->send_bag_msg(bag_msg,sizeof(bag_msg));
		cout<<"bag_msg:"<<bag_msg<<endl;

		memset(g_out_buf,0,sizeof(g_out_buf));
		snprintf(g_out_buf,sizeof(g_out_buf),"%s,%s",money_msg,bag_msg);
		send_msg(pg_hero->getFd(),g_out_buf);
	}	
}

void destoryGoods(char *buffer)
{
	int index;	//摧毁的物品索引
	
	int type;	//摧毁的物品类型
	
	char *goodsid;		//摧毁的物品id	
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	MSG_INT(type);
	MSG_CHAR_END(goodsid);		
	
	cout<<"9,1,"<<index<<","<<type<<","<<goodsid<<endl;
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)							//判断bag是否存在
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)					//判断index是否合法
	{
		return;		
	}	
	if (type<0||type>4||type==3)		//判断type是否合法
	{
		return;
	}	

	destoryBagGoods(pg_hero,index,goodsid);			//调用背包中的摧毁函数		

}

void bagFlagSet(char *buffer)
{	
	int flag_money;		//游戏币(元宝)标记
	
	int flag;				//开关标记
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag_money);
	MSG_INT(flag);
	
	cout<<"9,2,"<<flag_money<<","<<flag<<endl;
	
	Money *money=pg_hero->getMoney();
	if (money==NULL)
	{
		return;
	}
	
	if (flag_money==1)		//当游戏币标记为开启时
	{
		if (flag==1)			//开关标记为开
		{
			money->setMoneyFlag(g_out_buf,1);
		}
		else if (flag==0)
		{
			money->setMoneyFlag(g_out_buf,0);
		}
	}
	else if (flag_money==0)
	{
		if (flag==1)
		{
			money->setGoldFlag(g_out_buf,1);
		}
		else if (flag==0)
		{
			money->setGoldFlag(g_out_buf,0);
		}
	}
	send_msg(pg_hero->getFd(),g_out_buf);
}

void useDecreaseCrime(Hero *hero,char* goodsid,int index,int number)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);

	int levelLimit;

	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the dj bag_operator 1244"<<endl;
	}
	else
	{
		Goods_Config *goods=it->second;
		levelLimit=goods->getLevelLimit();
		if(hero->getLevel()<levelLimit)
		{
			return;
		}

		int crimeNow=hero->getCrimeValue();
		if (number%2==0)
		{
			number=number/2;
		}
		else
		{
			number=number/2+1;
		}
		
		if (useBagGoods(hero,goodsid,index,number)==0)
		{			
			int useResult=goodsReturnInt(goods,0)*number;
			crimeNow-=useResult;
			if (crimeNow<0)
			{
				crimeNow=0;
			}
			hero->setCrimeValue(crimeNow);
		}
	}	
}

void expandReturn(char *buffer)
{
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(num);
	
	if (num<0)
	{
		num=56;
	}

	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();			//取得目前背包有多大
	if (bagNum>=96)
	{
		msg_error(g_out_buf,26);
	}
	else
	{
		if ((num+bagNum)>96)
		{
			num=96-bagNum;
		}
		int useMoney=0;
		int needGold=bag->getExpandNeedGold();
		for (int i=0;i<num;i++)
		{
			useMoney=useMoney+needGold+i;
		}			
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,EXPAND_RETURN,useMoney,num);
	}
	send_msg(pg_hero->getFd(),g_out_buf);
}

bool expand(Hero *hero,int num)
{
	if (hero==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	int bagNum=bag->getBagNum();			//取得目前背包有多大
	int initMoney=bag->getExpandNeedGold();
	int useMoney=0;
	if ((num+bagNum)>96)
	{
		num=96-bagNum;
	}
	for (int i=0;i<num;i++)
	{
		useMoney=useMoney+initMoney+i;
	}
	if (useBoundGold(hero,useMoney))				//开背包使用元宝,判定是否成功
	{
		bag->bagExpand(num);						//直接拓展,不做任何判定
		bag->msg_expand_success(g_out_buf,sizeof(g_out_buf));
		send_msg(hero->getFd(),g_out_buf);
		initMoney+=num;
		bag->setExpandNeedGold(initMoney);
		return true;
	}	
	else
	{
		return false;
	}
}

void useAllGoods(Hero *hero,char* identity)
{
	if (hero==NULL||identity==NULL)
	{
		return;
	}
	destoryAllBagGoods(hero,identity);
	destoryAllWarehouseGoods(hero,identity);
}

int goodsReturnInt(char* goodsid,int index)
{
	if (goodsid==NULL)
	{
		return -1;
	}
	int type=getGoodsType(goodsid);				//判断该物品的大类型
	if (type==1)
	{
		return -1;			//为装备,不需要返回任何属性
	}
	else if (type==3)
	{
		return -1;			//为任务道具,不需要返回任何属性
	}
	else
	{
		Goods_Config *goods;		
		if (type==2)		//为普通道具
		{
			if (id_to_dj.find(goodsid)==id_to_dj.end())
			{
				cout<<"error bag_operator 428"<<endl;
				return -1;
			}
			else
			{
				goods=id_to_dj.find(goodsid)->second;
			}
		}
		else 				//为材料
		{
			if (id_to_cl.find(goodsid)==id_to_cl.end())
			{
				cout<<"error bag_operator 439"<<endl;
				return -1;
			}
			else
			{
				goods=id_to_cl.find(goodsid)->second;
			}
		}
		
		char* effect=goods->getEffect();
		// string effects[80];
		// int num=0;

		//解析物品的effect字符串,以;分隔,装在string 数组中
		
		char b[2];
		strncpy(b,";",sizeof(";"));
		char d[2]={'\0'};
		char effects[80][20]={'\0'};
		int num=0;
		int len=0;
		for(int i=0;i<strlen(effect);i++)
		{			
			strncpy(d,effect+i,1);
			if (strcmp(b,d)==0)
			{							
				strncpy(effects[num],effect+len,i-len);						
				len=i+1;
				num++;
			}
		}	
		
		//取出需要的属性 转化为int 返回
		int value=atoi(effects[index]);
		return value;
	}
}

int goodsReturnInt(Goods_Config *goods,int index)		//取得物品的效果,goods为物品实例,index为想取得的第几位数据,从0开始
{
	if (goods==NULL)
	{
		return -1;
	}
	char* effect=goods->getEffect();	
	// cout<<"effect is "<<effect<<endl;
	char b[2];
	strncpy(b,";",sizeof(";"));
	char d[2]={'\0'};
	char effects[80][20]={'\0'};
	int num=0;
	int len=0;
	for(int i=0;i<strlen(effect);i++)
	{			
		strncpy(d,effect+i,1);
		if (strcmp(b,d)==0)
		{							
			strncpy(effects[num],effect+len,i-len);		
			// cout<<effects[num]<<endl;
			len=i+1;
			num++;
		}
	}
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	for (int i=0;i<num;i++)
	{
		cout<<effects[i]<<endl;
	}
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	return atoi(effects[index]);
}

void goodsReturnVector(Goods_Config *goods,vector<string> &effects)	//取得物品的效果,返回所有的effect
{
	if (goods==NULL)
	{
		return;
	}
	char* effect=goods->getEffect();	
	// cout<<"effect is "<<effect<<endl;
	char b[2];
	strncpy(b,";",sizeof(";"));
	char d[2]={'\0'};
	char temp[20]={'\0'};
	int num=0;
	int len=0;
	for(int i=0;i<strlen(effect);i++)
	{			
		strncpy(d,effect+i,1);
		if (strcmp(b,d)==0)
		{							
			strncpy(temp,effect+len,i-len);	
			effects.push_back(temp);
			memset(temp,0,sizeof(temp));
			// cout<<temp<<endl;
			len=i+1;
			num++;
		}
	}
}

/* tory_01_19 请写注释 jolly */
int getGoodsType(char* goodsid)
{
	if (goodsid==NULL)
	{
		return 0;
	}
	
	int len=strlen(goodsid);			//取goodsid长度
	if (len<5)			//goodsid长度小于5,表示id错误,返回0
	{
		// cout<<"goodsid length is "<<len<<" goods id is:"<<goodsid<<endl;
		return 0;
	}
	else if (len>30)					//goodsid大于30  说明是装备的实例id,则返回1
	{
		return 1;
	}
	else
	{
		char flag[5]={'\0'};
		strncpy(flag,goodsid+2,2);
		if(strcmp(flag,"rw")==0)
		{
			return 3;
		}
		else if (strcmp(flag,"cl")==0)
		{
			return 4;
		}
		else if (strcmp(flag,"dj")==0)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
}
/* 改变阵营
*  jolly 12.11
*/
void modifyCamp(Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	if (hero->isInCampResWar())
	{
		return;
	}
	if (hero->isInGuildWarRoom())
	{
		return;
	}
	if (hero->isInCampWar())
	{
		return;
	}
	if (hero->getCamp()!=-1)
	{
		if (!campWarController.isCampLeader(hero,hero->getCamp()))
		{
			if (!campWarController.isCampChief(hero))
			{
				int usedGold=0;
				if (hero->getLevel()<30)
				{
					usedGold=20;
				}
				else
				{
					usedGold=500;
				}
				if (strlen(hero->getGuildName())!=0)
				{
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",7,3,0);
					send_msg(hero->getFd(),g_out_buf);
				}
				else
				{
					if (useGold(hero,usedGold))
					{
						map<int,int>::iterator it;
						it=campNumber.find(pg_hero->getCamp());
						if (it!=campNumber.end())
						{
							int number=it->second;
							number--;
							if (number<0)
							{
								number=0;
							}
							campNumber.erase(it);
							campNumber.insert(map<int,int>::value_type(pg_hero->getCamp(),number));
						}
						hero->setCamp(-1);
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",7,3,1);
						send_msg(hero->getFd(),g_out_buf);
						
						//记录日志2013.4.28
						char account_msg[1024]={'\0'};
						snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,6,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),pg_role->getUserName(),usedGold);
						write_log(account_msg);	
					}	
				}	
			}
			else
			{
				msg_error(g_out_buf,68);
				send_msg(hero->getFd(),g_out_buf);	
			}
		}
		else
		{
			msg_error(g_out_buf,67);
			send_msg(hero->getFd(),g_out_buf);
		}
	}
	else
	{
		cout<<"jolly:you enter no camp bag_operator 654"<<endl;
	}
}

//使用礼包
bool useGiftBag(Hero *hero,char *goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return false;
	}
	
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	int remainnumber=bag->remainGridNum();
	cout<<"remainnumber:"<<remainnumber<<endl;
	int gridNum=bag->getBagNum();
	if (index<0||index>gridNum)
	{
		return false;
	}
	
	
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	cout<<"1111111111111111111111111111"<<endl;
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the dj bag_operator 1244"<<endl;
		return false;
	}
	else
	{
		char effect[2048]={0};
		strncpy(effect,it->second->getEffect(),sizeof(effect));
		
		char effects[200][20]; //by benliao 20130519 fix array out of bound
		memset(effects,0,sizeof(effects));
		
		int j=0;
		int k=0;
		for (int i=0;i<strlen(effect);i++)
		{
			if (effect[i]==';')
			{
				j++;
				k=0;
			}
			else
			{
				effects[j][k]=effect[i];
				k++;
			}
		}
		cout<<"22222222222222222222222222222"<<endl;
		int number=atoi(effects[0]);
		int flag=atoi(effects[1]);
		int needNumber=atoi(effects[2]);
		cout<<"number:"<<number<<endl;
		cout<<"flag:"<<flag<<endl;
		cout<<"needNumber:"<<needNumber<<endl;
		int remainNumber=bag->remainGridNum();

		cout<<"33333333333333333333333333333333333"<<endl;
		int loop=(number-3)/2;
		if ((number-3)%2!=0)
		{
			return false;
		}
		
		if (flag==0)
		{		
			if (remainNumber>=needNumber)
			{
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					for (int i=0;i<loop;i++)
					{
						cout<<"goodsid:"<<effects[4+i*2]<<"     number:"<<effects[3+i*2]<<endl;
						saveGoodsInBag(hero,effects[4+i*2],atoi(effects[3+i*2]));
					}		
				}
			}
			else
			{
				msg_error(g_out_buf,44);
				send_msg(hero->getFd(),g_out_buf);
			}
		}
		else if (flag<0)
		{
			return false;
		}
		else
		{
			if (remainNumber>=flag)
			{
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					for (int i=0;i<flag;i++)
					{
						int randomNum;
						if (loop==1)
						{
							randomNum=0;
						}
						else
						{
							randomNum=random_number(0,loop-1);
						}

						cout<<"goodsid:"<<effects[4+i*2]<<"     number:"<<effects[3+i*2]<<endl;
						saveGoodsInBag(hero,effects[4+randomNum*2],atoi(effects[3+randomNum*2]));
					}
				}
			}
			else
			{
				msg_error(g_out_buf,44);
				send_msg(hero->getFd(),g_out_buf);
			}
		}
	}
}

bool usePetAgg(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();	
	if (bag==NULL)
	{	
		return false;
	}
	map<string,Goods_Config*>::iterator it;
	
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"error bag_operator 428"<<endl;
		return false;
	}	
	char* effects=it->second->getEffect();
	char identity[40]={'\0'};
	strncpy(identity,effects,12);
	map<string,Pet_Config*>::iterator pet_it;
	pet_it=id_to_pet.find(identity);
	Pet_Config *pet_config;
	Pet *_pet;
	
	Pet_Box *pet_box=hero->getPetBox();
	if (pet_box==NULL)
	{
		return false;
	}
	
	if (pet_it==id_to_pet.end())	
	{
		cout<<"According to petid can't find the pet 209 (in bag.cpp)"<<endl;
		return false;
	}
	else
	{
		pet_config=pet_it->second;
		if (it->second->getLevelLimit()<=hero->getLevel())
		{			
			Pet_Box *pet_box=hero->getPetBox();
			if (pet_box==NULL)
			{
				return false;
			}
			int pet_boxMaxNum=pet_box->getMaxNumber();
			int pet_boxNum=pet_box->getNumber();
			if (pet_boxMaxNum==pet_boxNum)
			{
				msg_error(g_out_buf,17);
				send_msg(hero->getFd(),g_out_buf);
				return false;
			}
			else
			{				
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					cout<<"hero->memHero->petboxdataNew.number:"<<hero->memHero->petboxdataNew.number<<endl;
					_pet=new Pet(pet_config,hero->memHero->petboxdataNew.petdata + hero->memHero->petboxdataNew.number);
					if (_pet==NULL)
					{
						return false;
					}
					pet_box->usePetAgg(_pet);
					_pet->setMasterId(hero->getIdentity());
					bag->initGrid(index);
					int _index=hero->memHero->petboxdataNew.number-1;
					_pet->msg_return_pet(g_out_buf,_index,sizeof(g_out_buf),hero->memHero->petSkillNumber,1);
					send_msg(hero->getFd(),g_out_buf);
					memset(g_out_buf,0,sizeof(g_out_buf));
					pet_box->send_msg_list(g_out_buf,sizeof(g_out_buf));
					send_msg(hero->getFd(),g_out_buf);
					hero->updataSingleTarget(1,4);
					if (_pet->getGeneration()>=2)
					{
						hero->updataSingleTarget(3,7);
					}
					if (_pet->getQuality()==4)
					{
						hero->updataSingleTarget(5,4);
					}
					
					/*拥有5个宠物给头衔，宠物收集者*/
					if (pet_box->getNumber()==5)
					{
						hero->addTitle("T019");
					}
					/*拥一个4代宠物给头衔，神兽掌控者*/
					if (_pet->getGeneration()>=4)
					{
						hero->addTitle("T020");
					}
					
					return true;						
				}
				else
				{
					msg_error(g_out_buf,14);					
					send_msg(hero->getFd(),g_out_buf);
					return false;
				}
			}			
		}			
		else
		{
			msg_error(g_out_buf,18);
			send_msg(hero->getFd(),g_out_buf);
			cout<<"jolly:you can't use a pet agg bag.cpp 269"<<endl;
			return false;
		}			
	}	
}

void useMoneyBag(Hero *hero,char* goodsid,int index,int number)											//使用钱袋
{
	if (hero==NULL)
	{
		return;
	}
	
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the dj bag_operator 840"<<endl;
	}
	else
	{			
		Goods_Config *goods=it->second;
		vector<string> effects;
		goodsReturnVector(goods,effects);
		int money=atoi(effects[1].c_str())*number;
		
		if (useBagGoods(hero,goodsid,index,number)==0)
		{				
			if (effects[0]=="1")
			{		
				increaseBoundGameMoney(hero,money);
			}
			else if (effects[0]=="2")
			{
				increaseBoundGold(hero,money);			
			}
			else if (effects[0]=="3")
			{
				increaseGameMoney(hero,money);	
			}
			else if (effects[0]=="4")
			{
				increaseGold(hero,money);
			}
		}
	}	
}

void useRewardBagWithMoney(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the dj id can't find the goods_config bag_operator 762"<<endl;
	}
	else
	{		
		Goods_Config *goods=it->second;		
		char* effects=goods->getEffect();
		char b[2];
		strncpy(b,";",sizeof(";"));
		char d[2]={'\0'};
		char effect[20][20]={'\0'};
		int num=0;
		int len=0;
		for(int i=0;i<strlen(effects);i++)
		{			
			strncpy(d,effects+i,1);
			if (strcmp(b,d)==0)
			{							
				strncpy(effect[num],effects+len,i-len);						
				len=i+1;
				num++;
			}		
		}
		if (!bag->bagIsFull(atoi(effect[1])))
		{		
			if (useBagGoods(hero,goodsid,index,1)==0)
			{				
				if (strcmp(effect[2],"1")==0)			//绑定元宝
				{
					increaseBoundGold(hero,atoi(effect[3]));
				}
				else if (strcmp(effect[2],"2")==0)
				{
					increaseBoundGameMoney(hero,atoi(effect[3]));
				}
				for (int j=4;j<atoi(effect[0]);)
				{
					saveGoodsInBag(hero,effect[j+1],atoi(effect[j]));
					j=j+2;
				}
			}
		}
	}
}

//试用坐骑
void useRideAgg(Hero *hero,char *goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Ride *ride=hero->getRide();
	if (ride==NULL)
	{
		return;
	}

	memset(g_out_buf,0,sizeof(g_out_buf));
	if (ride->ifFull())
	{
		msg_error(g_out_buf,114);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		map<string,Goods_Config*>::iterator it;	
		it=id_to_dj.find(goodsid);
		if (it==id_to_dj.end())
		{
			cout<<"error bag_operator 1028"<<endl;
			return;
		}	
		char rideIdentity[50]={0};
		snprintf(rideIdentity,sizeof(rideIdentity),"%s%d%d",goodsid,1,1);		
		map<string,Ride_Config*>::iterator ride_it;
		ride_it=id_to_ride.find(rideIdentity);
		if (ride_it==id_to_ride.end())	
		{
			cout<<"According to rideid can't find the rid 1039 (in bag_operator.cpp) rideIdentity:"<<rideIdentity<<endl;
			return;
		}
		else
		{
			if (it->second->getLevelLimit()<=hero->getLevel())
			{					
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					ride->createRide(ride_it->second,goodsid);
					ride->increaseAtt(hero);
					ride->ride_msg_return(g_out_buf,sizeof(g_out_buf),hero);
					send_msg(hero->getFd(),g_out_buf);	
					hero->send_msg_att();

					hero->updataSingleTarget(1,2);
				}
				else
				{
					msg_error(g_out_buf,14);					
					send_msg(hero->getFd(),g_out_buf);
				}
			}	
			else 
			{
				msg_error(g_out_buf,18);
				send_msg(hero->getFd(),g_out_buf);
			}
		}
	}	
}

void useMoneyBox(Hero *hero,char *goodsid,Point pt)
{
	if (hero==NULL||goodsid==NULL||hero->getMap()==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the dj id can't find the goods_config bag_operator 762"<<endl;
	}
	else
	{
		Goods_Config *goods=it->second;		
		char* effect=goods->getEffect();	
		char b[2];
		strncpy(b,";",sizeof(";"));
		char d[2]={'\0'};
		char effects[2][20]={'\0'};
		int num=0;
		int len=0;
		for(int i=0;i<strlen(effect);i++)
		{			
			strncpy(d,effect+i,1);
			if (strcmp(b,d)==0)
			{							
				strncpy(effects[num],effect+len,i-len);						
				len=i+1;
				num++;
			}
		}
		int loop=atoi(effects[0]);							//取掉的堆数
		int moneyNum=atoi(effects[1]);						//取没堆的数量
		cout<<"jollyTest: loop is :"<<loop<<"  moneyNum is :"<<moneyNum<<endl;
		int time=random_number(1,loop);
		
		Map_Inform *map=hero->getMap();
		if (map==NULL)
		{
			return;
		}
		
		char* uuid=cid();				//掉落实例id,一个怪一个
		char flag[40]={'\0'};
		strncpy(flag,uuid,sizeof(flag));
		free(uuid);
		Pick *pick=new Pick(flag,hero->getIdentity(),time,map,1,pt);
		
		int locationRandomx;
		int locationRandomy;
		snprintf(g_out_buf,sizeof(g_out_buf),"7,6,%s,%d,%s,%d,%d",hero->getIdentity(),1,flag,moneyNum,time);
		for (int i=0;i<time;i++)
		{		
			locationRandomx=random_number(0,128);			//随即出像素点x坐标	
			locationRandomy=random_number(0,64);			//随即出像素点y坐标	
			
			pt._x=pt._x+locationRandomx-64;
			pt._y=pt._y+locationRandomy-32;
			
			int digst=map->getBaseDigst();
			Point temp=MapExchangeLogical(pt);
			Point logPoint;
			logPoint._x=temp._x;
			logPoint._y=temp._y+digst;
			
			//判断是否是障碍点.若是则重新随即
			if (!map->judgeLogPtHind(logPoint))
			{
				cout<<"jolly:this point is hind point in dropgoods 382"<<endl;
				pt=hero->getLocation();
			}
			char pt_flag[15]={'\0'};
			snprintf(pt_flag,sizeof(pt_flag),",%d,%d",pt._x,pt._y);
			snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),"%s",pt_flag);
			pick->insertDropGoods(pt_flag,const_cast<char*>(itos(moneyNum).c_str()));				//每个掉落物品都插入到pick中			
		}					
		map->insertDropInst(pick);
		send_msg_dropGoods(g_out_buf,flag,map);
	}
}

bool useRandomGoods(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return false;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 968"<<endl;
	}
	else
	{
		Goods_Config* goods_config=it->second;
		char* effect=goods_config->getEffect();

		
		char b[2];
		strncpy(b,";",sizeof(";"));
		char d[2]={'\0'};
		char effects[70][20]={'\0'};
		int num=0;
		int len=0;
		for(int i=0;i<strlen(effect);i++)
		{			
			strncpy(d,effect+i,1);
			if (strcmp(b,d)==0)
			{							
				strncpy(effects[num],effect+len,i-len);						
				len=i+1;
				num++;
			}
		}		
		int repeat=atoi(effects[1]);
		Bag *bag=hero->getBag();
		if (bag==NULL)
		{
			return false;
		}
		if (bag->bagIsFull(1))
		{
			cout<<"jolly:remain grid is too small bag_operator 1087"<<endl;
			return false;
		}
		else
		{
			int number=atoi(effects[2]);
			
			for (int j=0;j<atoi(effects[0]);j++)
			{					
				int random=random_number(3,number+2);
				if (index==-1)
				{
					// cout<<"!!!!!!!!!!!!!!!!!"<<endl;
					char saveGoodsid[40];
					strncpy(saveGoodsid,effects[random],sizeof(saveGoodsid));
					if (saveGoodsInBag(hero,saveGoodsid,repeat))
					{
					// cout<<"@@@@@@@@@@@@@@@@@@@@@"<<endl;
						return true;
					}
					else
					{					
					// cout<<"#####################"<<endl;
						return false;
					}				
				}
				else
				{				
					if (useBagGoods(hero,goodsid,index,1)==0)
					{
						char saveGoodsid[40];
						strncpy(saveGoodsid,effects[random],sizeof(saveGoodsid));
						saveGoodsInBag(hero,saveGoodsid,repeat);
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
}

void heroExpDrug(Hero *hero,char* goodsid,int index,int number)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 968"<<endl;
	}
	else
	{
		Goods_Config* goods=it->second;
		int levelLimit=goods->getLevelLimit();
		if (hero->getLevel()<levelLimit)
		{
			msg_error(g_out_buf,18);
			send_msg(hero->getFd(),g_out_buf);
			cout<<"jolly:hero's level is not enough to eat this goods bag.operator 1409"<<endl;
		}
		else
		{
			char temp[20]={'\0'};
			strncpy(temp,goodsid+11,1);
			int num=atoi(temp);
			int usedNum=hero->expDrugUsedNum(num);
			int canUse=goodsReturnInt(goods,1);
			// cout<<"you use drug is "<<num<<endl;
			// cout<<"everyday you can use "<<canUse<<endl;
			// cout<<"now you used number is "<<usedNum<<endl;
			if (usedNum<canUse)
			{
				int use=canUse-usedNum;
				if (use<number)
				{
					number=use;
				}
				
				if (useBagGoods(hero,goodsid,index,number)==0)
				{
					int exp=goodsReturnInt(goods,0)*number;
					hero->setExpNow(exp);
					usedNum+=number;
					hero->setDrugUsedNum(num,usedNum);
				}
				else
				{
					cout<<"jolly:useGoods error 1143 bag_operator 1143"<<endl;
				}
			}
			else
			{
				msg_error(g_out_buf,19);
				send_msg(hero->getFd(),g_out_buf);
				cout<<"jolly:this goods used time is enough bag_operator 1114"<<endl;
			}
		}
	}
}

/*使用道具刷怪*/
void useToolBruMon(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	MonsterTool *monTool;
	map<string,MonsterTool*>::iterator toolMon_it;
	
	// for(toolMon_it = toolToMonster.begin();toolMon_it != toolToMonster.end();toolMon_it++)
	// {
		// cout<<"key:"<<toolMon_it->first<<endl;
		// cout<<"monId:"<<toolMon_it->second->getMapId()<<endl;
	// }
	toolMon_it = toolToMonster.find(goodsid);
	if(toolMon_it == toolToMonster.end())
	{
		cout<<"the tool id is error:"<<goodsid<<endl;
		return;
	}
	
	if (bag==NULL)
	{
		cout<<"the bag is NULL:"<<endl;
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 968"<<endl;
	}
	else
	{
		if (useBagGoods(hero,goodsid,index,1)==0)
		{
			monTool = (MonsterTool*)(toolMon_it->second->copyMon("map_001"));
			if(monTool != NULL)
			{
				cout<<"go use first toolBruMon:"<<endl;
				monTool->initOnwer(hero);
				toolMonsterIdToInst[monTool->getIdentity()] = monTool;
				monTool->brushMon();
				
				cout<<"go use second toolBruMon:"<<monTool->getIdentity()<<endl;	
			}	
		}
			
	}
}

void petExpDrug(Hero *hero,char* goodsid,int index,int number)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	Pet_Box *pet_box=hero->getPetBox();
	if (pet_box==NULL)
	{
		return;
	}
	Pet *pet=pet_box->getActivePet();
	if (pet==NULL)
	{
		msg_error(g_out_buf,8);
		send_msg(hero->getFd(),g_out_buf);
		cout<<"jolly:has no active pet. so can't use this goods bag.operator 1163"<<endl;
	}
	else
	{
		int activePetIndex=pet_box->getActivePetIndex();
		map<string,Goods_Config*>::iterator it;
		it=id_to_dj.find(goodsid);
		if (it==id_to_dj.end())
		{
			cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 1171"<<endl;
		}
		else
		{
			Goods_Config* goods=it->second;
			int levelLimit=goods->getLevelLimit();
			int petLevel=pet->getLevel();
			if (petLevel<levelLimit)
			{
				msg_error(g_out_buf,0);
				send_msg(hero->getFd(),g_out_buf);
				cout<<"jolly:pet level is not enough to eat this goods bag.operator 1179"<<endl;
			}
			else
			{
				int heroLevel=hero->getLevel();
				if (petLevel==heroLevel)
				{
					if (pet->topLevel())
					{
						msg_error(g_out_buf,57);
						send_msg(hero->getFd(),g_out_buf);
						return;
					}
				}
				int num=*(goodsid+11) - '0';
				if (useBagGoods(hero,goodsid,index,number)==0)
				{
					int exp=goodsReturnInt(goods,0)*number;
					pet->growExp(exp,hero->getLevel(),hero);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d",10,PET_EXP,pet->getIdentity(),activePetIndex,pet->getExpNow());
					send_msg(hero->getFd(),g_out_buf);
				}
				else
				{
					cout<<"jolly:useGoods error 1143 bag_operator 1193"<<endl;
				}
			}
		}
	}
}

void useEquipBag(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 1171"<<endl;
	}
	else
	{
		Goods_Config* goods=it->second;
		int levelLimit=goods->getLevelLimit();
		int level=hero->getLevel();
		if (level<levelLimit)
		{
			msg_error(g_out_buf,18);
			send_msg(hero->getFd(),g_out_buf);
			cout<<"jolly:hero's level is not enough to eat this goods bag.operator 1531"<<endl;
		}
		else
		{
			if (useBagGoods(hero,goodsid,index,1)==0)
			{
				vector<string> effects;
				goodsReturnVector(goods,effects);
				int number=atoi(effects[0].c_str());
				cout<<"number:"<<number<<endl;
				if (!bag->bagIsFull(number))
				{
					int randomNumber;
					effects.clear();
					int randomMax=atoi(effects[1].c_str());
					cout<<"randomMax:"<<randomMax<<endl;
					for (int i=0;i<number;i++)
					{
						randomNumber=random_number(1,randomMax);
						cout<<"randomNumber:"<<randomNumber<<endl;
						char id[20]={0};
						snprintf(id,sizeof(id),"b_%c_%s",hero->memHero->basicHeroData.party[0]+32,effects[randomNumber+1].c_str());
						cout<<"id:"<<id<<endl;
						saveGoodsInBag(hero,id,1);
					}			
				}
			}						
		}
	}
}

void useRandomEquip(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}	
	
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods bag_operator.cpp 1171"<<endl;
	}
	else
	{
		Goods_Config* goods=it->second;
		int levelLimit=goods->getLevelLimit();
		int level=hero->getLevel();
		if (level<levelLimit)
		{
			msg_error(g_out_buf,18);
			send_msg(hero->getFd(),g_out_buf);
			cout<<"jolly:hero's level is not enough to eat this goods bag.operator 1531"<<endl;
		}
		else
		{
			if (useBagGoods(hero,goodsid,index,1)==0)
			{					
				vector<string> effects;
				effects.clear();
				goodsReturnVector(goods,effects);
				int number=atoi(effects[0].c_str());
				cout<<"number:"<<number<<endl;
				if (!bag->bagIsFull(number))
				{
					int randomNumber;
					int randomMax=atoi(effects[1].c_str());
					cout<<"randomMax:"<<randomMax<<endl;
					int equipNumber=atoi(effects[2].c_str())/2;
					cout<<"equipNumber:"<<equipNumber<<endl;
					for (int i=0;i<number;i++)
					{
						randomNumber=random_number(1,randomMax);
						cout<<"randomNumber:"<<randomNumber<<endl;
						for (int j=0;j<equipNumber;j++)
						{
							if (randomNumber<atoi(effects[j*2+3].c_str()))
							{
								cout<<"j:"<<j<<endl;
								cout<<"effects[j*2+1]:"<<effects[j*2+3]<<endl;
								cout<<"effects[randomNumber*2+2]:"<<effects[j*2+4]<<endl;
								char id[20]={0};
								snprintf(id,sizeof(id),"b_%c_%s",hero->memHero->basicHeroData.party[0]+32,effects[j*2+4].c_str());
								cout<<"id:"<<id<<endl;
								saveGoodsInBag(hero,id,1);
								break;
							}
						}					
					}			
				}	
			}		
		}
	}
}

int resolveVipId(char* vipId)
{
	char flag[5]={'\0'};
	strncpy(flag,vipId+11,1);
	int flagInt=0;
	if(flag=="0")
	{
		flagInt=1;
	}
	else if(flag=="1")
	{
		flagInt=2;
	}
	else
	{
		flagInt=3;
	}
	return flagInt;
}

void useExpTimes(Hero *hero,char *goodsid,int index)										//人物使用双倍经验或者三倍经验的数据	
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	if (hero->memHero->expTimes==3)
	{
		msg_error(g_out_buf,70);
		send_msg(hero->getFd(),g_out_buf);
	}
	else 
	{
		map<string,Goods_Config*>::iterator it;
		it=id_to_dj.find(goodsid);
		if (it==id_to_dj.end())
		{
			cout<<"jolly:According to the goodsid can't find the dj bag_operator 1339"<<endl;
		}
		else
		{			
			Goods_Config *goods=it->second;
			vector<string> effects;
			effects.clear();
			goodsReturnVector(goods,effects);
			int expTimes=atoi(effects[0].c_str());
			memset(g_out_buf,0,sizeof(g_out_buf));
			if (hero->memHero->expTimes==2&&expTimes==3)
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,EXP_TIMES_USE,1);
				send_msg(hero->getFd(),g_out_buf);
			}
			else if (hero->memHero->expTimes==2&&expTimes==2)
			{
				msg_error(g_out_buf,69);
				send_msg(hero->getFd(),g_out_buf);
			}
			else
			{
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					hero->memHero->expTimes=expTimes;
					hero->memHero->expTimesCount=atoi(effects[1].c_str());
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d,%d",3,19,1,hero->getIdentity(),22,hero->memHero->expTimes,hero->memHero->expTimesCount,hero->memHero->expTimes);
					send_msg(hero->getFd(),g_out_buf);
				}
			}			
		}
	}
}

void setGoodsUnBound(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int index)						//要解绑的道具索引
	MSG_CHAR(char *goodsid)					//要解绑的道具id
	MSG_CHAR(char *identity)					//要解绑的道具id
	MSG_INT(int needIndex)					//解绑道具的索引
	MSG_CHAR_END(char *needGoodsid)		//解绑道具的id
	
	cout<<"9,24,"<<index<<","<<goodsid<<","<<identity<<","<<needIndex<<","<<needGoodsid<<endl;
	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	if (!bag->test(index,identity))
	{
		return;
	}
	if (!bag->test(needIndex,needGoodsid))
	{
		return;
	}
	
	map<string,Equip_config*>::iterator it;
	it=id_to_equip.find(goodsid);
	if (it==id_to_equip.end())
	{
		cout<<"jolly:According to the equipment id can't find the equip_config in bag_operator.cpp1591"<<endl;
		return;
	}
	else
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		if (goodsid[0]=='f')
		{
			msg_error(g_out_buf,130);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
		else
		{
			Equipment *equip=pg_hero->getEquip(identity);
			if (equip==NULL)
			{
				cout<<"jolly:Accoring to the equipment identity can't find the equipment entity in bag_operator.cpp 1607"<<endl;
				return;
			}
			else
			{
				int type=equip->gettype();
				if (type==13||type==0)
				{
					msg_error(g_out_buf,131);
					send_msg(pg_hero->getFd(),g_out_buf);
				}
				else
				{
					if (equip->getIsBag()==1)
					{
						msg_error(g_out_buf,132);
						send_msg(pg_hero->getFd(),g_out_buf);
					}
					else
					{
						if (useBagGoods(pg_hero,needGoodsid,needIndex,1)==0)
						{
							equip->unboundDecreaseAttr(pg_hero,it->second);
							saveBagGoods(pg_hero,equip->getid(),1,1,identity,index,0);
							equip->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
							send_msg(pg_hero->getFd(),g_out_buf);
						}
					}
				}
			}
		}
	}
}

void useExpTimesReturn(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int index)
	MSG_CHAR_END(char *goodsid)
	
	cout<<"9,22,"<<index<<","<<goodsid<<endl;
	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)
	{
		return;
	}
	
	if (bag->test(index,goodsid))
	{
		map<string,Goods_Config*>::iterator it;
		it=id_to_dj.find(goodsid);
		if (it==id_to_dj.end())
		{
			cout<<"jolly:According to the goodsid can't find the dj bag_operator 1339"<<endl;
		}
		else
		{			
			Goods_Config *goods=it->second;
			vector<string> effects;
			effects.clear();
			goodsReturnVector(goods,effects);
			int expTimes=atoi(effects[0].c_str());
			memset(g_out_buf,0,sizeof(g_out_buf));			
			if (useBagGoods(pg_hero,goodsid,index,1)==0)
			{
				pg_hero->memHero->expTimes=expTimes;
				pg_hero->memHero->expTimesCount=atoi(effects[1].c_str());
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d,%d",3,19,1,pg_hero->getIdentity(),22,pg_hero->memHero->expTimes,pg_hero->memHero->expTimesCount,pg_hero->memHero->expTimes);
				send_msg(pg_hero->getFd(),g_out_buf);
			}		
		}
	}
}

void useRewardBag(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the dj bag_operator 1244"<<endl;
	}
	else
	{
			
		Goods_Config *goods=it->second;
		char* effect=goods->getEffect();
		
		
		char b[2];
		strncpy(b,";",sizeof(";"));
		char d[2]={'\0'};
		char stage[20]={'\0'};
		int num=0;
		int len=0;
		for(int i=0;i<strlen(effect);i++)
		{			
			strncpy(d,effect+i,1);
			if (strcmp(b,d)==0)
			{							
				strncpy(stage,effect+len,i-len);						
				break;
			}
		}
		//benliao 2013.1.3.			
		map<string,Reward_recharge_config*>::iterator iter;
		iter=sid_to_reward_recharge.find(stage);
		if (iter==sid_to_reward_recharge.end())
		{
			cout<<"jolly:According to the reward id can't find the reward bag_operator 1290"<<endl;
		}
		else
		{
			Reward_recharge_config* reward=iter->second;
			int number=reward->getNum();
			cout<<"number is :"<<number<<endl;
			Bag *bag=hero->getBag();
			if (bag==NULL)
			{
				return;
			}
			if (!bag->bagIsFull(number/2))
			{
				if (useBagGoods(hero,goodsid,index,1)==0)
				{
					char* goodsid=reward->getGoodsid();
					cout<<"goodis is :"<<goodsid<<endl;
					char effects[80][20]={'\0'};
					num=0;
					len=0;
					for(int i=0;i<strlen(effect);i++)
					{			
						strncpy(d,effect+i,1);
						if (strcmp(b,d)==0)
						{							
							strncpy(effects[num],effect+len,i-len);						
							len=i+1;
							num++;
						}
					}
					
					for (int i=0;i<number;)
					{
						saveGoodsInBag(hero,effects[i+1],atoi(effects[i]));
						i=i+2;
					}
				}
			}
		}
	}
}

void useChunjieBag(Hero *hero,char* goodsid,int index)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)
	{
		return;
	}
	
	vector<string> effects;
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		return;
	}
	else
	{
		Goods_Config *goods=it->second;
		goodsReturnVector(goods,effects);
		if (effects.size()<20)
		{
			return;
		}
		
		int randomMoneyNum=random_number(0,9);
		int randomGoldNum=random_number(10,19);
		
		if (useBagGoods(hero,goodsid,index,1)==0)
		{
			increaseBoundGold(hero,atoi(effects[randomGoldNum].c_str()));
			increaseBoundGameMoney(hero,atoi(effects[randomMoneyNum].c_str()));
		}
	}
}

void usePopularity(Hero *hero,char* goodsid,int index,int number)
{	
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);

	int levelLimit;

	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the dj bag_operator 1244"<<endl;
	}
	else
	{
		Goods_Config *goods=it->second;
		levelLimit=goods->getLevelLimit();
		if(hero->getLevel()<levelLimit)
		{
			return;
		}

		if (useBagGoods(hero,goodsid,index,number)==0)
		{			
			int useResult=goodsReturnInt(goods,0)*number;
			hero->addPrestigeValue(useResult);
		}
	}
}

void useRideExp(Hero *hero,char* goodsid,int index,int number)
{
	if (hero==NULL||goodsid==NULL)
	{
		return;
	}
	Ride *ride=hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	if (!ride->ifFull())
	{
		return;
	}
	map<string,Goods_Config*>::iterator it;
	it=id_to_dj.find(goodsid);
	if (it==id_to_dj.end())
	{
		cout<<"jolly:According to the goodsid can't find the goods config in bag_operator 1922"<<endl;
		return;
	}
	else
	{
		if (useBagGoods(hero,goodsid,index,number)==0)
		{
			int exp=goodsReturnInt(it->second,0)*number;
			ride->gainExp(hero,exp,0);
		}
	}
}

/*********************************************************************
 * taskGoodsSpecialPosUse - 到指定地点才能使用的任务道具的使用
 * @pg_hero: 使用者
 * @goodsId: 任务道具ID --goodsId如"b_rw_100_00200_01"形式,
 *						 表示任务task00200的第2个可使用道具
 * @index: 道具在背包中的下标
 *********************************************************************/
void taskGoodsSpecialPosUse(Hero *hero, char* goodsId, int index)
{
	if (hero==NULL||goodsId==NULL)
	{
		return;
	}
	if (strlen(goodsId) != 16)
	{
		//不是可使用的任务道具类型
		return;
	}
	char taskId[10] = "task";
	sub_str(taskId+strlen(taskId), goodsId, 9, 5);
	// string taskId = "task" + goodsId.substr(9, 5); //任务道具中埋伏着任务id后缀
	Task* task = hero->findAcceptedTaskList(taskId);
	if (task == NULL)
	{
		return;
	}
	Point pt = hero->getLocation();
	// string pointStr = intTostring(pt._x).substr(1);
	// pointStr += intTostring(pt._y);
	char pointStr[20];
	snprintf(pointStr,sizeof(pointStr), "%d,%d", pt._x, pt._y);
	//表示更新的是任务的坐标点验证需求
	int ret = task->taskUpdate(pointStr, -1);
	if(ret == -1)
	{
		//任务位置需求更新失败
		return;
	}
	for(int i = 0; i < 10; i++)
	{
		if (!strcmp(taskId, hero->memHero->taskSaveData.acced[i].taskId))
		{
			cout<<"[] have see you here!"<<endl;
			hero->memHero->taskSaveData.acced[i].status[ret] = 1;
		}
	}
	//把任务道具的需求也更新
	hero->updateHeroTaskStatus(7,goodsId);
	// int updGoods = task->taskUpdate(goodsId, 1);
	// pg_hero->memset();
	cout<<"######################################################"<<endl;
	// cout<<"[BisonShow] updata goods result is "<<updGoods<<endl;
	cout<<"######################################################"<<endl;
	// string msg_task = "5" + intTostring(TASK_UPDATE_RETURN) + "," + taskId;
	// msg_task += intTostring(SUCCESS);
	// msg_task += intTostring(task->getNeedType(goodsId));
	// msg_task += "," + goodsId;
	// msg_task += intTostring(1);
	snprintf(g_out_buf,sizeof(g_out_buf), "5,%d,%s,1,%d,%s,1", TASK_UPDATE_RETURN, taskId, task->getNeedType(goodsId), goodsId);
	//任务位置需求更新成功,后面就把物品使用掉。这里使用一定成功，因为在这个函数调用之前已经有判断
	// char useGoodsId[40];
	// strncpy(useGoodsId,goodsId,sizeof(useGoodsId));
	// useBagGoods(pg_hero,useGoodsId, index, 1);
	useToolBruMon(hero, goodsId, index);
	//直接发送任务道具使用需求更新成功，
	send_msg(hero->getFd(),g_out_buf);
}
/*
*拆分函数
*index为拆分的物品所在的位置,num为拆分出的数量
*/
bool splitGoods(Hero *hero,int index,int num)
{	
	if (hero==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	char* goodsid=bag->getIdentity(index);						//根据索引找实例id	;
	int split_place=bag->getNextGoodsIndex();						//查找拆分出的物品该放的索引
	int type=getGoodsType(goodsid);									//查询物品的类型
	int existNum=bag->getGridNum(index);									//查询拆分的道具在背包中现有的数量
	int bagNum=bag->getBagNum();									//查看当前背包的大小
	if (type==1||existNum==1||num>=existNum)	//当物品是装备,或堆叠只为1,或拆分出的道具位置大于背包大小,或要拆分的物品数量大于本格的大小,拆分失败
	{
		msg_error(g_out_buf,20);											//发送拆分失败信息
		send_msg(hero->getFd(),g_out_buf);
		cout<<"error bag_operator.cpp 1571"<<endl;
		return false;
	}
	else if (split_place>=bagNum)
	{
		msg_error(g_out_buf,44);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		int lastNum=existNum-num;									//拆分成功,本格剩余物品数量
		bag->saveGoodsInGrid(goodsid,index,lastNum);				//保存本格物品
		bag->saveGoodsInGrid(goodsid,split_place,num);				//保存拆分 出的物品
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d",9,GOODS_SPLIT,index,goodsid,lastNum,split_place,num);							//发送拆分成功信息
		send_msg(hero->getFd(),g_out_buf);
		return true;
	}	
}

void destoryBagGoods(Hero *hero,int index,char* identity)
{	
	if (hero==NULL||identity==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		cout<<"hero bag is null in bag_operator 1956"<<endl;
		return;
	}
	if (bag->test(index,identity))
	{
		int type=getGoodsType(identity);
		int number=bag->getGridNum(index);
		if (type==1)
		{
			if (!hero->deleteEquip(identity))
			{
				cout<<"deleteEquip Error in bag_operator 1967"<<endl;
				return;
			}
		}
		else
		{				
			/*记录摧毁物品的流水账 jolly 12.10 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",8,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),identity,number);
			write_log(account_msg);	
			/*记录摧毁物品的流水账 jolly 12.10 end*/
		}
		bag->initGrid(index);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,DESTORY_GOODS,index,identity);
		send_msg(hero->getFd(),g_out_buf);
	}
	else 
	{
		cout<<"abg_operator.cpp 1985 bag goods test error and identity:"<<identity<<"   index:"<<index<<endl;
	}
}

bool sellGoodsFromBag(Hero *hero,int index,char* identity,int &money)
{
	if (hero==NULL||identity==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	// cout<<"bag has no such equipment bag_operator.cpp 981"<<endl;
	int number=bag->getGridNum(index);
	// cout<<index<<endl<<identity<<endl;
	if (bag->test(index,identity))
	{
		// cout<<"111111111111111111111111111111111111111"<<endl;
		int type=getGoodsType(identity);
		// cout<<"bag has no such equipment bag_operator.cpp 1430"<<endl;
		if (type==1)
		{
			// cout<<"123123123123123123"<<endl;
			Equipment* equipment=hero->getEquip(identity);	//取装备实例
			if (equipment==NULL)
			{
				cout<<"bag has no such equipment bag_operator.cpp 758"<<endl;
				return false;
			}
			else
			{				
				bag->initGrid(index);
				money=equipment->getsellprice();
				
				/*记录出售装备的流水账 jolly 12.10 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s,%d",7,5,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),equipment->getid(),equipment->getname(),identity,money);
				write_log(account_msg);	
				/*记录出售装备的流水账 jolly 12.10 end*/
				
				hero->deleteEquip(identity);
				equipment=NULL;
			}		
		}
		else if(type==2)
		{	
			// cout<<"2222222222222222222222222222222222"<<endl;
			map<string,Goods_Config*>::iterator iDj=id_to_dj.find(identity);
			if(iDj==id_to_dj.end())
			{
				cout<<"cant sell this equip in bag_operator.cpp"<<endl;
				return false;
			}
			else
			{	
				money=iDj->second->getPrice()*number;
				
				/*记录出售物品的流水账 jolly 12.10 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",8,3,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),identity,number,money);
				write_log(account_msg);	
				/*记录出售物品的流水账 jolly 12.10 end*/
				
				bag->initGrid(index);
				// cout<<"bag has no such equipment bag_operator.cpp 1025"<<endl;
			}	
		}
		else if(type==3)
		{
			// cout<<"333333333333333333333333333333333"<<endl;
			return false;
		}
		else 
		{
			// cout<<"44444444444444444444444444444444444"<<endl;
			map<string,Goods_Config*>::iterator iCl=id_to_cl.find(identity);
			// cout<<"bag has no such equipment bag_operator.cpp 1034"<<endl;
			if(iCl==id_to_cl.end())
			{
				cout<<"cant sell this equip in bag_operator.cpp"<<endl;
				return false;
			}
			else
			{
				money=iCl->second->getPrice()*number;
				/*记录出售物品的流水账 jolly 12.10 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",8,3,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),identity,number,money);
				write_log(account_msg);	
				/*记录出售物品的流水账 jolly 12.10 end*/
				bag->initGrid(index);
				// cout<<"bag has no such equipment bag_operator.cpp 1042"<<endl;
			}	
		} 		
		// cout<<"bag has no such equipment bag_operator.cpp 1046"<<endl;		
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,DESTORY_GOODS,index,identity);
		send_msg(hero->getFd(),g_out_buf);
		// cout<<"bag has no such equipment bag_operator.cpp 1047"<<endl;
		return true;
	}
	else
	{
		cout<<"bag has no such goods bag_operator.cpp 1052"<<endl;
		return false;
	}
} 

/*
*保存所有物品到背包中的借口,已做了入参检查
*accountFlag:2:从副本领取
*/
bool saveGoodsInBag(Hero *hero,char* goodsid,int num,int accountFlag)
{
	cout<<"saveGoodsInBag::goodsid:"<<goodsid<<endl;
	if (num<=0)
	{
		return false;
	}
	if (hero==NULL || goodsid == NULL)
	{
		return false;
	}
	// cout<<"!!!!!!!!!!!!!!!!!!!!!!num is "<<num<<endl;
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	int i;
	int saveNum;
	// cout<<"goodsid is "<<goodsid<<endl;
	int type=getGoodsType(goodsid);	//物品类型
	int index;
	
	if (type==1)			//如果要保存的物品是装备,则进入此
	{
		int bagRemainGridNum=bag->remainGridNum();
		if (bagRemainGridNum<num)	//由于装备的堆叠数量为1,所以直接判断保存的数量和剩余格子的关系
		{			
			msg_error(g_out_buf,44);
			send_msg(hero->getFd(),g_out_buf);
			return false;				//背包放不下这么多道具,则1个都不保存
		}
		else
		{				
			map<string,Equip_config*>::iterator it;
			// cout<<"id is "<<goodsid<<endl;
			it=id_to_equip.find(goodsid);			//通过物品id查找装备
			Equipment* equip_pt;
			if (it==id_to_equip.end())
			{
				// cout<<"id is "<<goodsid<<endl;
				cout<<"According to the equip id can't find the equip_config  in bag.cpp"<<endl;
				msg_error(g_out_buf,145);
				send_msg(hero->getFd(),g_out_buf); 
				return false;
			}
			else
			{
				Equip_config *equip_config=it->second;
				for (int k=0;k<num;k++)
				{
					equip_pt=new Equipment(equip_config);					//保存装备  直接实例化装备
					char* identity=equip_pt->getentityid();
					EquipmentData *memEquipData=equip_pt->getEquipmentData();
					if (!mem_group->set_data(identity, (char*)memEquipData, (int)sizeof(EquipmentData),hero->getArea()))		//增加新装备的时候,立马向memcached中插入数据
					{						
						cout<<"jolly:save Equip in memcached error in bag.cpp 359"<<endl;
						return false;								//保存进memcached错误,先return,以后有了异常处理机制再修改
					}
					takeOffEquipToBag(hero,equip_pt);							//将装备保存入背包中
					hero->insertEquip(equip_pt);
					if (equip_pt->getrank()==5)
					{
						//武林目标 jolly 12.4 start
						hero->updataSingleTarget(4,8);
						//武林目标 jolly 12.4 end
						//捡到神器,全服广播						
						char info[1024]={'\0'};
						snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s",7,SYSTEM_WARN,"xf003",2,1,hero->getNickName(),hero->getIdentity(),0,0,4,equip_pt->getname(),equip_pt->getid(),equip_pt->getentityid(),hero->getIdentity());
						map<string, Hero*>::iterator it_hero;

						for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
						{
							if (it_hero->second!=NULL)
							{						
								send_msg(it_hero->second->getFd(),info);
							}
						}
					}
					
					/*记录获得装备的流水账 jolly 12.10 start*/
					char account_msg[1024]={'\0'};
					snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%s,%d",7,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,equip_pt->getname(),equip_pt->getentityid(),accountFlag);
					write_log(account_msg);	
					/*记录获得装备的流水账 jolly 12.10 end*/	

					hero->memSet();
				}
				
				if (accountFlag==2)
				{
					memset(g_out_buf,0,sizeof(g_out_buf));
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s",7,SYSTEM_WARN,"xf030",2,1,hero->getNickName(),hero->getIdentity(),0,0,4,equip_pt->getname(),equip_pt->getid(),equip_pt->getentityid(),hero->getIdentity());
					map<string, Hero*>::iterator it_hero;

					for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
					{
						if (it_hero->second!=NULL)
						{						
							send_msg(it_hero->second->getFd(),g_out_buf);
						}
					}
				}
			}	
		}
	}
	else				//如果要保存的物品是非装备,则进入此
	{		
		/* 读取物品的堆叠数量 start*/
		map<string,Goods_Config*>::iterator it;	
		Goods_Config *goods=NULL;
		if (type==4)					//物品为cl
		{			
			it = id_to_cl.find(goodsid);
			if (it==id_to_cl.end())
			{
				cout<<"jolly:goodsid is error cl bag.cpp 374 and goodsid:"<<goodsid<<endl;
				msg_error(g_out_buf,145);
				send_msg(hero->getFd(),g_out_buf); 
				return false;
			}
			goods=it->second;
		}
		else									//物品为dj或者rw
		{
			it = id_to_dj.find(goodsid);
			if (it==id_to_dj.end())
			{
				cout<<"jolly:goodsid is error cl bag_operator.cpp 1903   goodsid:"<<goodsid<<endl;
				msg_error(g_out_buf,145);
				send_msg(hero->getFd(),g_out_buf); 
				return false;
			}
			goods=it->second;
		}
		if (goods==NULL)
		{
			return false;
		}
		int maxnum=it->second->getRepeat();		
		/* 读取物品的堆叠数量 end*/			
		if (maxnum<=0)				//除数检查,若为0,则配置文件出错
		{
			cout<<"jolly:error in bag 389"<<endl;
			return false;
		}
		else
		{		
			int direactSave=bag->isExist(goodsid,maxnum);		//计算,查看该放在什么位置上
			int direactNum=bag->getGridNum(direactSave);		//查看该位置上的物品数量
			int totalnum=direactNum+num;						//将没有堆叠蛮的物品也算成要保存的物品,然后计算总共需要保存的物品数量
			int repeat=totalnum/maxnum;							//计算这些物品需要放几个格子
			if (totalnum%maxnum!=0)
			{
				repeat++;
			}
			int bagRemainGridNum=bag->remainGridNum();
			if (bagRemainGridNum<repeat)	//查看背包的位置是不是足够放这些物品
			{			
				msg_error(g_out_buf,44);
				send_msg(hero->getFd(),g_out_buf);
				return false;				
			}
			else
			{					
				if (accountFlag==2)
				{
					memset(g_out_buf,0,sizeof(g_out_buf));
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s",7,SYSTEM_WARN,"xf030",2,1,hero->getNickName(),hero->getIdentity(),0,0,4,goods->getName(),goods->getId(),goods->getId(),hero->getIdentity());
					map<string, Hero*>::iterator it_hero;

					for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
					{
						if (it_hero->second!=NULL)
						{						
							send_msg(it_hero->second->getFd(),g_out_buf);
						}
					}
				}
			
				if (totalnum<=maxnum)
				{
					saveBagGoods(hero,goodsid,type,totalnum,goodsid,direactSave,accountFlag);
					return true;
				}
				else
				{		
					totalnum=totalnum-maxnum;
					saveBagGoods(hero,goodsid,type,maxnum,goodsid,direactSave,accountFlag);
					for (i=1;i<repeat;i++)
					{
						if (totalnum>maxnum)
						{
							saveNum=maxnum;
						}
						else
						{
							saveNum=totalnum;
						}
						saveBagGoods(hero,goodsid,type,saveNum,goodsid,accountFlag);
						totalnum-=saveNum;
					}	
				}
			}							
		}		
	}
	return true;	
}

bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int accountFlag)
{
	Bag *bag=hero->getBag();
	if (hero==NULL || goodsid ==NULL)
	{
		return false;
	}
	if (bag==NULL)
	{
		return false;
	}
	int index=bag->getNextGoodsIndex();
	int bagNum=bag->getBagNum();
	if (index>=bagNum)
	{		
		send_msg_saveError(hero);
		cout<<"bag numer is error 625 in bag.cpp"<<endl;
		return false; 
	}
 	bag->saveGoodsInGrid(identity,index,num);
	send_msg_addgoods(hero,num,type,index,goodsid,identity);
	/*记录保存物品的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",8,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,num,accountFlag);
	write_log(account_msg);	
	/*记录保存物品的流水账 jolly 12.11 end*/

	return true;
}

bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int index,int accountFlag)
{
	if (hero==NULL||goodsid==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	int bagNum=bag->getBagNum();
	if (index>=bagNum)
	{	
		send_msg_saveError(hero);
		cout<<"bag numer is error 625 in bag.cpp"<<endl;
		return false; 
	}
 	bag->saveGoodsInGrid(identity,index,num);
	send_msg_addgoods(hero,num,type,index,goodsid,identity);
	/*记录保存物品的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",8,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,num,accountFlag);
	write_log(account_msg);	
	/*记录保存物品的流水账 jolly 12.11 end*/
	return true;
}

void destoryAllBagGoods(Hero *hero,char* identity)
{
	if (hero==NULL)
	{
		return;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();
	for (int i=0;i<bagNum;i++)
	{
		char* goodsid=bag->getIdentity(i);
		if (strcmp(goodsid,identity)==0)
		{
			int num=bag->getGridNum(i);
			bag->initGrid(i);
			send_msg_useSuccess(hero,i);
			/*记录摧毁物品的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",8,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,num);
			write_log(account_msg);	
			/*记录摧毁物品的流水账 jolly 12.11 end*/
		}
	}
}

int useBagGoods(Hero *hero,char* goodsid,int number)
{
	if (hero==NULL||goodsid==NULL)
	{
		return number;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return number+1;
	}
	int bagNum=bag->getBagNum();
	for (int i=0;i<bagNum;i++)
	{
		if (number!=0)
		{
			char* identity=bag->getIdentity(i);
			if (strcmp(identity,goodsid)==0)
			{	
				int gridNum=bag->getGridNum(i);					//该格子中物品的数量
				if (gridNum>=number)
				{
					gridNum=gridNum-number;
					if (gridNum==0)
					{
						bag->initGrid(i);
					}
					else
					{
						bag->setGridNum(gridNum,i);
					}
					send_msg_useSuccess(hero,i);
					number=0;
				}
				else
				{
					number=number-gridNum;
					bag->initGrid(i);
					send_msg_useSuccess(hero,i);
				}
				/*记录使用物品的流水账 jolly 12.11 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",8,2,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,gridNum);
				write_log(account_msg);	
				/*记录使用物品的流水账 jolly 12.11 end*/
			}
		}
		else
		{
			return 0;
		}
	}
	return number;
}

int useBagGoods(Hero *hero,const char* goodsid,int index,int num,bool sendFlag)									//使用背包中的物品
{
	if (hero==NULL||goodsid==NULL)
	{
		return num;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return num+1;
	}
	int gridNum=bag->getGridNum(index);	
	if (gridNum==0)
	{
		cout<<"this grid number is 0 bag.cpp 839"<<endl;
		return num+1;
	}
	else
	{
		if (bag->test(index,goodsid))
		{
			gridNum=gridNum-num;
			if (gridNum==0)
			{
				cout<<"jolly:the goods is used up bag.cpp 852"<<endl;
				bag->initGrid(index);
			}
			else
			{
				bag->setGridNum(gridNum,index);
			}
			/*记录使用物品的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",8,2,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,num);
			write_log(account_msg);	
			/*记录使用物品的流水账 jolly 12.11 end*/
			send_msg_useSuccess(hero,index);
			return 0;		
		}
		else
		{		
			cout<<"jolly:thie id can't fit the goodsid bag_operator.cpp 844"<<endl;
			if (sendFlag)
			{
				memset(g_out_buf,0,sizeof(g_out_buf));
				msg_error(g_out_buf,14);
				send_msg(hero->getFd(),g_out_buf);
			}
			return num+1;
		}
	}	
} 

bool useGoodsBoth(Hero *hero,char *goodsid,int number)
{
	if (hero==NULL  || goodsid==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	Warehouse *warehouse=hero->getWarehouse();
	if  (warehouse==NULL)
	{
		return false;
	}
	
	
	int bagNum=bag->getBagNum();
	int goodsNumInBag=0;
	for (int i=0;i<bagNum;i++)
	{
		// char* identity=bag->getIdentity(i);
		if (strcmp(bag->getIdentity(i),goodsid)==0)
		{	
			int gridNum=bag->getGridNum(i);					//该格子中物品的数量
			goodsNumInBag+=gridNum;
			if (goodsNumInBag>=number)
			{
				useBagGoods(hero,goodsid,number);
				return true;
			}
		}
	}
	
	int flag;
	int useBagNum;
	if (goodsNumInBag==0)
	{
		flag=0;
	}
	else
	{
		flag=1;
		useBagNum=goodsNumInBag;
	}
	
	int warehouseNum=warehouse->getGridNum();
	for (int i=0;i<warehouseNum;i++)
	{
		// char* identity=warehouse->getGridGoodsid();
		if (strcmp(warehouse->getGridGoodsid(i),goodsid)==0)
		{	
			int gridNum=warehouse->getGridGoodsNum(i);					//该格子中物品的数量
			goodsNumInBag+=gridNum;
			if (goodsNumInBag>=number)
			{
				if (flag==1)
				{
					useBagGoods(hero,goodsid,useBagNum);
					warehouse_destory_goods_byNum(hero,goodsid,number-useBagNum);
				}
				else
				{
					warehouse_destory_goods_byNum(hero,goodsid,number);
				}
				return true;
			}
		}
	}
	
	return false;
}

bool takeOffEquipToBag(Hero *hero,int index,Equipment* equipment)
{			
	if (hero==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	int bagNum=bag->getBagNum();
	char* entityid=equipment->getentityid();
	if (index>=bagNum)
	{
		cout<<"can't take off the equip (in bag.cpp takeOffEquip)"<<endl;
		return false;
	}
	else if (bag->getGridNum(index)==0)
	{
		if (saveBagGoods(hero,equipment->getid(),1,1,entityid,index,2))
		{
			return true;
		}	
		else
		{
			return false;
		}
	}
	else
	{
		if (saveBagGoods(hero,equipment->getid(),1,1,entityid,2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool takeOffEquipToBag(Hero *hero,Equipment* equipment)
{
	if(hero==NULL){//benliao
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	char* entityid=equipment->getentityid();
	if (saveBagGoods(hero,equipment->getid(),1,1,entityid,2))
	{
		return true;		
	}
	else
	{
		return false;
	}
}

Equipment* getEquipFromBag(Hero *hero,int _index)	//取装备实例
{
	if (hero==NULL)
	{
		return NULL;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return NULL;
	}
	char* identity=bag->getIdentity(_index);
	if (strcmp(identity,"0")==0)
	{
		cout<<"jolly:This index equip identity is 0 bag_operator 1813"<<endl;
		return NULL;
	}
	else
	{
		return hero->getEquip(identity);
	}	
}	

vector<Trade_Goods> tradeSuccessDelete(Hero *hero)
{
	vector<Trade_Goods> trade_goods;
	if (hero==NULL)
	{
		return trade_goods;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return trade_goods;
	}
	vector<int> trade_index=bag->tradeSuccessReturnIndex();
	Trade_Goods goods;
	if (!trade_index.empty())
	{
		vector<int>::iterator it;
		for (it=trade_index.begin();it!=trade_index.end();it++)
		{		
			int index=*it;
			strncpy(goods.goodsid,bag->getIdentity(index),sizeof(goods.goodsid));
			goods.num=bag->getGridNum(index);
			goods.type=getGoodsType(goods.goodsid);
			if (goods.type==1)				//装备直接交易实例
			{
				char *id=hero->identity_to_goodsid(goods.goodsid);
				strncpy(goods.goodsid,id,sizeof(goods.goodsid));
				set<Equipment*> tempSet;
				map<string,set<Equipment*> >::iterator equip_it;
				equip_it=bussinessEquip.find(hero->bussinessData.identity);
				Equipment *equipment=hero->getEquip(bag->getIdentity(index));
				if (equipment==NULL)
				{
					cout<<"equipment is null in bussiness bag_operator 2522"<<endl;
					return trade_goods;
				}
				if (equip_it==bussinessEquip.end())
				{
					tempSet.insert(equipment);
				}
				else
				{
					tempSet=equip_it->second;
					bussinessEquip.erase(equip_it);
					tempSet.insert(equipment);
				}
				bussinessEquip.insert(map<string,set<Equipment*> >::value_type(hero->bussinessData.identity,tempSet));
				hero->dropEquipInst(bag->getIdentity(index));				
			}
			trade_goods.push_back(goods);
			bag->initGrid(index);
			send_msg_useSuccess(hero,index);	
		}
	}	
	return trade_goods;
}

bool tradeSuccessInsert(Hero *hero,vector<Trade_Goods> _trade_goods)
{
	if (hero==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		cout<<"jolly:bag is null bag_operator 1912"<<endl;
		return false;
	}
	if (_trade_goods.size()>bag->remainGridNum())
	{
		cout<<"jolly:_trade_goods is big than bag number bag_operator 1917"<<endl;
		return false;
	}
	else
	{
		if (!_trade_goods.empty())
		{
			/*记录交易日志 jolly 2013.2.25*/			
			Hero *coHero=heroid_to_hero(hero->bussinessData.businessPartnerId);
			if (coHero==NULL)
			{
				return false;
			}
			char account_msg[10240]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s,%d",14,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),coHero->getIdentity(),coHero->getNickName(),(int)_trade_goods.size());
			
			Trade_Goods goods;
			vector<Trade_Goods>::iterator it;
			
			map<string,set<Equipment*> >::iterator map_it;
			map_it=bussinessEquip.find(hero->bussinessData.identity);
			if (map_it!=bussinessEquip.end())
			{
				set<Equipment*> tempSet=map_it->second;
				set<Equipment*>::iterator set_it;
				for (set_it=tempSet.begin();set_it!=tempSet.end();++set_it)
				{
					saveEquipIntoBag(hero,*set_it);
					snprintf(account_msg+strlen(account_msg),sizeof(account_msg)-strlen(account_msg),",%s,%d",(*set_it)->getid(),1);
				}
			}
			for (it=_trade_goods.begin();it!=_trade_goods.end();it++)
			{	
				goods=*it;
				
				if (goods.type!=1)
				{					
					char goodsid[40]={0};
					strncpy(goodsid,goods.goodsid,sizeof(goodsid));
					saveGoodsInBag(hero,goodsid,goods.num);	
					snprintf(account_msg+strlen(account_msg),sizeof(account_msg)-strlen(account_msg),",%s,%d",goodsid,goods.num);
				}	
			}
			write_log(account_msg);	
		}		
		_trade_goods.clear();
		bag->tradeFailed();		
		return true;
	}
}

//将装备实例保存到背包中
bool saveEquipIntoBag(Hero *hero,Equipment *equip)
{
	if (hero==NULL||equip==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	int bagRemainNum=bag->remainGridNum();
	if (bagRemainNum>0)
	{		
		char* entityid=equip->getentityid();
		if (saveBagGoods(hero,equip->getid(),1,1,entityid,2))
		{
			hero->insertEquip(equip);
			return true;		
		}
		else
		{
			return false;
		}
	}
	else
	{
		msg_error(g_out_buf,44);
		send_msg(hero->getFd(),g_out_buf);
	}
}

void send_msg_addgoods(Hero *hero,int num,int type,int index,char* goodsid,char* identity)
{
	if (hero==NULL||goodsid==NULL||identity==NULL)
	{
		return;
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d,%s,%s",9,SAVE_GOODS,1,num,type,index,goodsid,identity);
//	cout<<"@@Tory add send_msg_addgoods:"<<g_out_buf<<endl;
	send_msg(hero->getFd(),g_out_buf);
}

void send_msg_saveError(Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,SAVE_GOODS,3);
	send_msg(hero->getFd(),g_out_buf);
}

void send_msg_useSuccess(Hero *hero,int index)
{
	if (hero==NULL)
	{
		return;
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,GOODS_USE_SUECCESS,index,hero->getBag()->getGridNum(index));
	send_msg(hero->getFd(),g_out_buf);
}

