#include"anyBusiness.h"
#include"wholeDefine.h"
#include<map>
#include"hero.h"
#include <stdio.h>
#include <stdlib.h>
#include"commodity.h"
#include"nbox.h"
#include "money_operator.h"
#include"bag_operator.h"


//added by benliao
#include "wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;
extern PitchTerm pitchTerm;

//创建摊位请求
void createStall(char *buff)
{
	cout << "createStall" << endl;
	Map_Inform *map_now;
	Nbox* box;
		
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);
	
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	if (pg_hero->getHeroState()==6)
	{
		msg_error(g_out_buf,128);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	Point pixelPt=pg_hero->getLocation();
	if (pixelPt._x>=pitchTerm.pt1._x&&pixelPt._x<=pitchTerm.pt2._x&&pixelPt._y<=pitchTerm.pt1._y&&pixelPt._y>=pitchTerm.pt2._y)			//判断是不是在摆摊区
	{			
		//为该角色创建摊位
		if(pg_hero->getHeroState()==0)
		{
			pg_hero->stopMove();
			strncpy(pg_hero->stall.privateStallName,pg_hero->getNickName(),sizeof(pg_hero->stall.privateStallName));
			pg_hero->stall.pt=pg_hero->getLogPt();
			pg_hero->stall.number=0;
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%s",14,11,pg_hero->getIdentity(),pg_hero->getNickName());
			box->sentBoxMsg(g_out_buf);
			pg_hero->setHeroState(5);
			
			//jolly add wulintarget 12.4 start
			pg_hero->updataSingleTarget(1,1);
			//jolly add wulintarget 12.4 end
		}
		else
		{
			cout<<" it is wrong in 110;"<<endl;
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,11,0);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}
	else
	{
		msg_error(g_out_buf,76);
		send_msg(pg_hero->getFd(),g_out_buf);
	}	
}


int returnFreeGrid(Hero *hero)
{
	if (hero==NULL)
	{
		return -1;
	}
	
	for (int i=0;i<24;i++)
	{
		if (pg_hero->stall.stallGoods[i].number==0)
		{
			return i;
		}
	}
	
	return -1;
}

//增加商品
void addCommodity(char *buff)
{
	MSG_BEGIN(buff,g_msg_len);
	MSG_CHAR(char* identity);//物品实例id
	MSG_CHAR(char *goodsid);//物品类型id	
	MSG_INT(int type); //物品类型	
	MSG_INT(int money); //物品单价
	MSG_INT(int num); //物品数量
	MSG_INT(int index);//物品在背包的下标
	MSG_INT(int flag);	//钱的标志
	
	cout<<"14,19,"<<identity<<","<<goodsid<<","<<type<<","<<money<<","<<num<<","<<index<<","<<flag<<endl;
	
	if (money<=0)
	{
		return;
	}
	if (num<=0)
	{
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if(pg_hero->getHeroState()!=5)
	{
		cout<<"there is no this onLineStall in  stallBusiness.cpp :34"<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,18,0);//返回0代表操作失败
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	//检查该物品是否确实存在
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	if(!bag->test(index,identity))
	{
		cout<<"identity  is :"<<identity<<"this id is wrong "<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,18,0);//返回0代表操作失败
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	//绑定物品不能出售
	if(strncmp(goodsid,"b",1)==0)
	{
		msg_error(g_out_buf,133);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if (bag->isLocking(index))
	{
		cout<<"物品正在操作中"<<endl;
		msg_error(g_out_buf,146);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	//摆摊数量和格子数量不相等的时候先进行拆分再操作
	int gridNumber=bag->getGridNum(index);
	if (gridNumber>num)
	{
		if (!splitGoods(pg_hero,index,gridNumber-num))
		{
			return;
		}
	}
	
	int stallindex=returnFreeGrid(pg_hero);
	if (stallindex==-1)
	{
		cout<<"stall is full in onlineStallBUssiness.cpp 155"<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,18,0);//返回0代表操作失败
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	pg_hero->stall.stallGoods[stallindex].price=money;
	strncpy(pg_hero->stall.stallGoods[stallindex].typeId,goodsid,sizeof(pg_hero->stall.stallGoods[stallindex].typeId));
	pg_hero->stall.stallGoods[stallindex].type=type;
	pg_hero->stall.stallGoods[stallindex].number=num;
	pg_hero->stall.stallGoods[stallindex].goodsIndexInBag=index;
	pg_hero->stall.stallGoods[stallindex].priceFlag=flag;
	pg_hero->stall.number++;
	bag->goodsLockIndex(index);
	strncpy(pg_hero->stall.stallGoods[stallindex].goodsId,identity,sizeof(pg_hero->stall.stallGoods[stallindex].goodsId));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d",14,18,1,identity,goodsid,type,stallindex,money,num,index,flag);//返回1代表操作成功 
	send_msg(pg_hero->getFd(),g_out_buf);
}


//他人买入
void stallBusiness(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_INT(int indexStall)
	MSG_CHAR(char *goodsid)
	MSG_INT(int number)
	MSG_INT(int buyPrice)
	MSG_INT(int flag)
	
	cout<<"14,14,"<<indexStall<<","<<goodsid<<","<<number<<","<<buyPrice<<","<<flag<<endl;
	
	if (indexStall<0||indexStall>23)
	{
		return;
	}
	if (number<0)
	{
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	//错误信息 0：找不到玩家， 2：该物品已经下架 ，3：该物品已经改价 ，4：买不起这件物品
	Hero *hero=heroid_to_hero(pg_hero->viewIdentity);
	if (hero==NULL)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,15,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if (number>hero->stall.stallGoods[indexStall].number)
	{
		return;
	}
	
	if (strcmp(goodsid,hero->stall.stallGoods[indexStall].typeId)!=0)
	{
		return;
	}
	
	if (buyPrice!=hero->stall.stallGoods[indexStall].price||flag!=hero->stall.stallGoods[indexStall].priceFlag)
	{
		cout<<"sorry this price is not same with me "<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",14,15,3,indexStall,hero->stall.stallGoods[indexStall].price,hero->stall.stallGoods[indexStall].priceFlag);
		send_msg(pg_hero->getFd(),g_out_buf);//3：该物品已经改价
		return;
	}
		
	if(hero->stall.stallGoods[indexStall].type!=0)
	{
		int price=hero->stall.stallGoods[indexStall].price*number;
		Money *myMoney=pg_hero->getMoney();
		Money *sellerMoney=hero->getMoney();
		if (myMoney==NULL||sellerMoney==NULL)
		{
			return;
		}
		
		int bagIndex=hero->stall.stallGoods[indexStall].goodsIndexInBag;
		if (hero->stall.stallGoods[indexStall].priceFlag==1)
		{
			if (useGameMoney(pg_hero,price))
			{
				if (saveGoodsInBag(pg_hero,hero->stall.stallGoods[indexStall].typeId,number))
				{
					hero->stall.stallGoods[indexStall].number-=number;
					increaseGameMoney(hero,price);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",14,15,1,indexStall,0,hero->stall.stallGoods[indexStall].number);
					char msg[1024]={'\0'};
					snprintf(msg,sizeof(msg),"%d,%d,%d,%d,%d,%d",14,15,1,indexStall,1,hero->stall.stallGoods[indexStall].number);						
					send_msg(pg_hero->getFd(),g_out_buf);//返回1代表成功
					send_msg(hero->getFd(),msg);
					if (hero->stall.stallGoods[indexStall].number==0)
					{
						destoryBagGoods(hero,hero->stall.stallGoods[indexStall].goodsIndexInBag,hero->stall.stallGoods[indexStall].goodsId);
						hero->stall.stallGoods[indexStall].initStallGoods();
						hero->stall.number--;
					}
					else 
					{
						hero->getBag()->setGridNum(hero->stall.stallGoods[indexStall].number,hero->stall.stallGoods[indexStall].goodsIndexInBag);
						send_msg_useSuccess(hero,hero->stall.stallGoods[indexStall].goodsIndexInBag);
					}
				}
				else 
				{
					increaseGameMoney(pg_hero,price);
				}
			}
		}
		else if (hero->stall.stallGoods[indexStall].priceFlag==2)
		{
			if (useGold(pg_hero,price))
			{
				if (saveGoodsInBag(pg_hero,hero->stall.stallGoods[indexStall].typeId,number))
				{
					hero->stall.stallGoods[indexStall].number-=number;
					increaseGold(hero,price);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",14,15,1,indexStall,0,hero->stall.stallGoods[indexStall].number);
					char msg[1024]={'\0'};
					snprintf(msg,sizeof(msg),"%d,%d,%d,%d,%d,%d",14,15,1,indexStall,1,hero->stall.stallGoods[indexStall].number);						
					send_msg(pg_hero->getFd(),g_out_buf);//返回1代表成功
					send_msg(hero->getFd(),msg);
					if (hero->stall.stallGoods[indexStall].number==0)
					{
						destoryBagGoods(hero,hero->stall.stallGoods[indexStall].goodsIndexInBag,hero->stall.stallGoods[indexStall].goodsId);
						hero->stall.stallGoods[indexStall].initStallGoods();
						hero->stall.number--;
					}					
					else 
					{
						hero->getBag()->setGridNum(hero->stall.stallGoods[indexStall].number,hero->stall.stallGoods[indexStall].goodsIndexInBag);
						send_msg_useSuccess(hero,hero->stall.stallGoods[indexStall].goodsIndexInBag);
					}
				}
				else 
				{
					increaseGold(pg_hero,price);
				}
			}
		}
		
		if (hero->getBag())
		{
			if (bagIndex>0&&bagIndex<hero->getBag()->getBagNum())
			{
				hero->getBag()->goodsUnlockIndex(bagIndex);
			}
		}
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,15,2);
		send_msg(pg_hero->getFd(),g_out_buf);//2：该物品已经下架  
		return;
	}
} 

//物品改价 
void changeStallCommodityPrice(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_INT(int money) //修改的物品价格
	MSG_INT_MAX(int indexBag,95) //物品在背包中的索引
	MSG_INT_MAX(int indexStall, 23)
	MSG_INT(int flag)
	
	cout<<"14,15,"<<money<<","<<indexBag<<","<<indexStall<<","<<flag<<endl;

	if ((money <0) || (indexBag < 0) || (indexStall < 0) ||(flag<0)) { //check if negative benliao
		return;
	}	

	//如果没有摆摊,报错返回
	if(pg_hero->getHeroState()!=5)
	{
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,20,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}

	//验证物品是否合法
	if (pg_hero->stall.stallGoods[indexStall].goodsIndexInBag!=indexBag)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,20,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if(money>=0)
	{
		pg_hero->stall.stallGoods[indexStall].price=money;
		pg_hero->stall.stallGoods[indexStall].priceFlag=flag;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",14,20,1,indexStall,money,flag);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

//物品下架
void deleteStallCommodity(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_INT_MAX(int indexBag, 95)
	MSG_INT_MAX(int indexStall,23) 


	//如果没有摆摊,报错返回
	if(pg_hero->getHeroState()!=5)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,19,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
		return;
	}
	
	//验证物品是否合法
	if (pg_hero->stall.stallGoods[indexStall].goodsIndexInBag!=indexBag)
	{	
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,19,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if (pg_hero->getBag())
	{
		pg_hero->getBag()->goodsUnlockIndex(pg_hero->stall.stallGoods[indexStall].goodsIndexInBag);		
	}
	
	pg_hero->stall.number--;
	pg_hero->stall.stallGoods[indexStall].initStallGoods();

	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",14,19,1,indexStall);

	send_msg(pg_hero->getFd(),g_out_buf);
	
	

}

//收摊
void deleteStall(char *buff)
{
	Map_Inform *map_now;
	Nbox* box;
	
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);
	
	box->getStaInSrcVec(obj);
	
	if(pg_hero->getHeroState()!=5)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,14,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
		return;
	}
	
	cout<<"12222223333333333333333333333333333333333"<<endl;
	pg_hero->setHeroState(0);
	pg_hero->stall.initPrivateStall();
	for (int i=0;i<24;i++)
	{		
		if (pg_hero->getBag())
		{
			pg_hero->getBag()->goodsUnlockIndex(pg_hero->stall.stallGoods[i].goodsIndexInBag);		
		}
		
		pg_hero->stall.stallGoods[i].initStallGoods();
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s",14,14,pg_hero->getIdentity());
	box->sentBoxMsg(g_out_buf); 
}


//改名
void changeName(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR_END(char *name)
	
	
	Map_Inform *map_now;
	Nbox* box;
		
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);
	box->getStaInSrcVec(obj);
	
	if(pg_hero->getHeroState()!=5)
	{		
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,16,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	else
	{		
		strncpy(pg_hero->stall.privateStallName,name,sizeof(pg_hero->stall.privateStallName));
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%s",14,16,pg_hero->getIdentity(),name);
		box->sentBoxMsg(g_out_buf); 
	}
}


//查看摊位
void checkStall(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR(char* stallMaster)

	Hero *hero=heroid_to_hero(stallMaster);
	if (hero==NULL)
	{
		return;
	}
	
	if(hero->getHeroState()!=5)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,12,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		cout<<"wrong"<<endl;
		return;
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d",14,12,stallMaster,hero->stall.number);
		for(int i=0;i<24;i++)
		{	
			if (hero->stall.stallGoods[i].type!=0)
			{
				snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%s,%d,%d,%d,%d,%d",hero->stall.stallGoods[i].typeId,\
				hero->stall.stallGoods[i].type,hero->stall.stallGoods[i].number,hero->stall.stallGoods[i].price,i,hero->stall.stallGoods[i].priceFlag);
			}			
		}
		strncpy(pg_hero->viewIdentity,stallMaster,sizeof(pg_hero->viewIdentity));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

