#include"anyBusiness.h"
#include<map>
#include"hero.h"
#include <stdio.h>
#include <stdlib.h>
#include"commodity.h"
extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
#include "money_operator.h"
#include "wholeDefine.h"

//交易请求
void askForBusiness(char *buff)
{	
	//消息解析
	MSG_BEGIN(buff, g_msg_len)
	MSG_CHAR(char *inviteeIdChar)	
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	/*add chenzhen 20130312,自己不能邀请自己交易*/
	if(strncmp(pg_hero->getIdentity(),inviteeIdChar,strlen(inviteeIdChar)) == 0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,1,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
		
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(inviteeIdChar);
	if (it==heroId_to_pHero.end())
	{
		msg_error(g_out_buf,123);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	Hero *invitee=it->second;			
	
	if(invitee->bussinessData.bussinessFlag==0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s",14,1,1,pg_hero->getIdentity(),pg_hero->getNickName());
		send_msg(invitee->getFd(),g_out_buf);
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",14,0,2,invitee->getNickName());
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

 //交易请求反馈
void feedbackForAsk(char *buff)
{	
	//消息解析
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR(char *inviterIdChar)
	MSG_INT(int flag)			
	
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(inviterIdChar);
	if (it==heroId_to_pHero.end())
	{
		return;
	}
	Hero *inviter=it->second;		//找邀请者
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if(flag)
	{
		strncpy(pg_hero->bussinessData.businessPartnerId,inviter->getIdentity(),sizeof(pg_hero->bussinessData.businessPartnerId));
		strncpy(inviter->bussinessData.businessPartnerId,pg_hero->getIdentity(),sizeof(inviter->bussinessData.businessPartnerId));
		pg_hero->bussinessData.bussinessFlag=1;
		inviter->bussinessData.bussinessFlag=1;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%s",14,0,1,pg_hero->getIdentity(),pg_hero->getNickName());
		send_msg(inviter->getFd(),g_out_buf);
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",14,0,0,pg_hero->getNickName());
		send_msg(inviter->getFd(),g_out_buf);
		return;
	}
}

//交易界面添加物品
void addGoods(char *buff)
{
	//消息解析	
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR(char *goodsid)
	MSG_INT(int bagIndex)		//背包索引
	MSG_INT(int number)	
	
	cout<<"14,2,"<<goodsid<<","<<bagIndex<<","<<number<<endl;
	
	if(pg_hero->bussinessData.bussinessFlag!=1)
	{
		cout<<"it is be locked !!! So you can't do this in playerBusiness.cpp"<<endl;
		msg_error(g_out_buf,111);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	} 
	
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(pg_hero->bussinessData.businessPartnerId);
	if (it==heroId_to_pHero.end())
	{
		return;
	}
	Hero *businessPartner=it->second;		

	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (bagIndex<0||bagIndex>bagNum)
	{
		return;
	}

	if(!bag->putOnTradeTable(goodsid,bagIndex))
	{
		cout<<"put on trade table is failed  goodsId is :" <<goodsid<<endl;
		return;
	}
	
	vector<int> businessStore =pg_hero->getBag()->tradeSuccessReturnIndex();

	memset(g_out_buf,0,sizeof(g_out_buf));
	vector<int>::iterator v_it;
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",14,2,0,(int)businessStore.size());
	char msg[2048]={0};
	snprintf(msg,sizeof(msg),"%d,%d,%d,%d",14,2,1,(int)businessStore.size());
	char identity[50]={0};
	for(v_it=businessStore.begin();v_it!=businessStore.end();++v_it)
	{
		goodsid=bag->getIdentity(*v_it);
		int goodsNum=bag->getGridNum(*v_it);
		int goodsType=getGoodsType(goodsid);
		if (goodsType==1)
		{
			strncpy(identity,pg_hero->identity_to_goodsid(goodsid),sizeof(identity));
		}
		else 
		{
			strncpy(identity,goodsid,sizeof(identity));
		}
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%s,%s,%d,%d,%d",identity,goodsid,goodsType,goodsNum,*v_it);
		snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%s,%s,%d,%d,%d",identity,goodsid,goodsType,goodsNum,*v_it);
	}
	send_msg(businessPartner->getFd(),g_out_buf);
	send_msg(pg_hero->getFd(),msg);
}

//交易界面删除物品
void deleteGoods(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_CHAR(char *goodsid)
	MSG_INT(int index)
		
	cout<<"14,3,"<<goodsid<<","<<index<<endl;
	
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
	
	if(!bag->takeOffTradeTable(index))
	{
		cout<<"delete business goods failed "<<endl;
		return;
	}
	
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(pg_hero->bussinessData.businessPartnerId);
	if (it==heroId_to_pHero.end())
	{
		return;
	}
	Hero *businessPartner=it->second;	
	
	vector<int> businessStore =pg_hero->getBag()->tradeSuccessReturnIndex();

	memset(g_out_buf,0,sizeof(g_out_buf));
	char msg[2048]={0};
	if(businessStore.size()==0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",14,2,0,0);
		snprintf(msg,sizeof(msg),"%d,%d,%d,%d",14,2,1,0);
		send_msg(businessPartner->getFd(),g_out_buf);
		send_msg(pg_hero->getFd(),msg);
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	vector<int>::iterator v_it;
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",14,2,0,(int)businessStore.size());
	snprintf(msg,sizeof(msg),"%d,%d,%d,%d",14,2,1,(int)businessStore.size());
	char identity[50]={0};
	for(v_it=businessStore.begin();v_it!=businessStore.end();++v_it)
	{
		goodsid=bag->getIdentity(*v_it);
		int goodsNum=pg_hero->getBag()->getGridNum(*v_it);
		int goodsType=getGoodsType(goodsid);
		if (goodsType==1)
		{
			strncpy(identity,pg_hero->identity_to_goodsid(goodsid),sizeof(identity));
		}
		else 
		{
			strncpy(identity,goodsid,sizeof(identity));
		}			
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%s,%s,%d,%d,%d",identity,goodsid,goodsType,goodsNum,*v_it);
		snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%s,%s,%d,%d,%d",identity,goodsid,goodsType,goodsNum,*v_it);
	}
	send_msg(businessPartner->getFd(),g_out_buf);
	send_msg(pg_hero->getFd(),msg);
}

//关闭交易
void businessCancel(char *buff)
{	
	cout<<"14,6"<<endl;
	
	bussinessCancelDeal(pg_hero);
}

void bussinessCancelDeal(Hero *hero)
{
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(hero->bussinessData.businessPartnerId);
	if (it==heroId_to_pHero.end())
	{
		return;
	}
	Hero *businessPartner=it->second;	
	
	if (hero->getBag()==NULL)
	{
		return;
	}
	if (businessPartner->getBag()==NULL)
	{
		return;
	}	
	
	hero->getBag()->tradeFailed();
	businessPartner->getBag()->tradeFailed();
	
	hero->bussinessData.init();
	businessPartner->bussinessData.init();
		
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",14,6);
	send_msg(businessPartner->getFd(),g_out_buf);
	send_msg(hero->getFd(),g_out_buf);
}

//交易锁
void businessLock(char *buff)
{	
	MSG_BEGIN(buff,g_msg_len)
	MSG_INT(int lockFlag)
	MSG_INT(int money)
	
	cout<<"14,4,"<<lockFlag<<","<<money<<endl;
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if(!pg_hero->getMoney()->beforeUse(money))
	{	
		msg_error(g_out_buf,1);
		send_msg(pg_hero->getFd(),g_out_buf);
		
		memset(g_out_buf,0,sizeof(g_out_buf));
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,8);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(pg_hero->bussinessData.businessPartnerId);
	if (it==heroId_to_pHero.end())
	{
		return;
	}
	Hero *businessPartner=it->second;	

	pg_hero->bussinessData.businessMoney=money;

	char msg[1024]={0};
	snprintf(msg,sizeof(msg),"%d,%d,%d,%d",14,3,1,lockFlag);
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d",14,3,0,lockFlag,money);
	send_msg(pg_hero->getFd(),msg);
	send_msg(businessPartner->getFd(),g_out_buf);
	if(lockFlag)
	{
		pg_hero->bussinessData.bussinessFlag=2;
	}
	else
	{
		pg_hero->bussinessData.bussinessFlag=1;
		if (businessPartner->bussinessData.bussinessFlag==3)
		{
			snprintf(msg,sizeof(msg),"%d,%d,%d,%d,%d",14,3,0,0,-1);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",14,3,1,0);
			send_msg(pg_hero->getFd(),msg);
			send_msg(businessPartner->getFd(),g_out_buf);
			businessPartner->bussinessData.bussinessFlag=1;
		}
	}
}

//交易确认
void verifyThisBusiness(char *buff)
{
	// cout<<"******************************"<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	if(pg_hero->bussinessData.bussinessFlag!=2&&pg_hero->bussinessData.bussinessFlag!=3)
	{
		msg_error(g_out_buf,108);
		send_msg(pg_hero->getFd(),g_out_buf);
		cout<<"businessLock is false  you cant do this in playerBusiness.cpp"<<endl;
		return;
	}
	
	//找到与他交易的玩家实例指针	
	map<string, Hero*>::iterator it;
	it=heroId_to_pHero.find(pg_hero->bussinessData.businessPartnerId);
	if (it==heroId_to_pHero.end())
	{
		// cout<<"111111111111111111111111111111"<<endl;
		return;
	}
	Hero *businessPartner=it->second;	
	
	if (pg_hero->getBag()==NULL||businessPartner->getBag()==NULL)
	{
		// cout<<"222222222222222222222222222222"<<endl;
		return;
	}
		
	//获取两个玩家所需要交易的物品的总数
	int heroBagVolume=pg_hero->getBag()->getTradeIndexSize();
	int businessPartnerBagVolume=businessPartner->getBag()->getTradeIndexSize();
	
	//检查玩家背包容量是否足够
	if(heroBagVolume>businessPartnerBagVolume)
	{
		int i=heroBagVolume-businessPartnerBagVolume;
		if(businessPartner->getBag()->bagIsFull(i))
		{
			msg_error(g_out_buf,126);
			send_msg(businessPartner->getFd(),g_out_buf);
			memset(g_out_buf,0,sizeof(g_out_buf));
			msg_error(g_out_buf,125);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"in playerBusiness.cpp :359"<<endl;
			return;
		}
	}
	else
	{
		int i=businessPartnerBagVolume-heroBagVolume;
		if(pg_hero->getBag()->bagIsFull(i))
		{
			msg_error(g_out_buf,126);
			send_msg(pg_hero->getFd(),g_out_buf);
			memset(g_out_buf,0,sizeof(g_out_buf));
			msg_error(g_out_buf,125);
			send_msg(businessPartner->getFd(),g_out_buf);
			cout<<"in playerBusiness.cpp :367"<<endl;
			return;
		}
	}
		
	if(businessPartner->bussinessData.bussinessFlag==3)
	{
		if (pg_hero->getMoney()->money_getGameMoney()>=pg_hero->bussinessData.businessMoney&&businessPartner->getMoney()->money_getGameMoney()>=businessPartner->bussinessData.businessMoney)
		{	
			vector<int> trade_index=pg_hero->getBag()->tradeSuccessReturnIndex();
			if (!trade_index.empty())
			{
				vector<int>::iterator it;
				for (it=trade_index.begin();it!=trade_index.end();++it)
				{		
					int index=*it;
					int num=pg_hero->getBag()->getGridNum(index);
					char *goodsid=pg_hero->getBag()->getIdentity(index);
					int type=getGoodsType(goodsid);
					if (type==1)				//装备直接交易实例
					{
						Equipment *equipment=pg_hero->getEquip(goodsid);
						if (equipment==NULL)
						{
							cout<<"equipment is null in bussiness bag_operator 2522"<<endl;
						}
						else
						{
							saveEquipIntoBag(businessPartner,equipment);
							pg_hero->dropEquipInst(goodsid);	
						}			
					}
					else
					{
						saveGoodsInBag(businessPartner,goodsid,num);	
					}
					pg_hero->getBag()->initGrid(index);
					send_msg_useSuccess(pg_hero,index);	
				}
			}	
				
			trade_index.clear();
			trade_index=businessPartner->getBag()->tradeSuccessReturnIndex();
			if (!trade_index.empty())
			{
				vector<int>::iterator it;
				for (it=trade_index.begin();it!=trade_index.end();++it)
				{		
					int index=*it;
					int num=businessPartner->getBag()->getGridNum(index);
					char *goodsid=businessPartner->getBag()->getIdentity(index);
					int type=getGoodsType(goodsid);
					if (type==1)				//装备直接交易实例
					{
						Equipment *equipment=businessPartner->getEquip(goodsid);
						if (equipment==NULL)
						{
							cout<<"equipment is null in bussiness bag_operator 2522"<<endl;
						}
						else
						{
							saveEquipIntoBag(pg_hero,equipment);
							businessPartner->dropEquipInst(goodsid);	
						}			
					}
					else
					{
						saveGoodsInBag(pg_hero,goodsid,num);	
					}
					businessPartner->getBag()->initGrid(index);
					send_msg_useSuccess(businessPartner,index);	
				}
			}			
			
				int heroMoney=businessPartner->bussinessData.businessMoney-pg_hero->bussinessData.businessMoney;
				int partnerMoney=pg_hero->bussinessData.businessMoney-businessPartner->bussinessData.businessMoney;
				if (heroMoney<0)
				{
					heroMoney=0-heroMoney;
					useGameMoney(pg_hero,heroMoney);
				}
				else if(heroMoney>0)
				{
					increaseGameMoney(pg_hero,heroMoney);
				}
				if (partnerMoney<0)
				{
					partnerMoney=0-partnerMoney;
					useGameMoney(businessPartner,partnerMoney);
				}
				else if(partnerMoney>0)
				{
					increaseGameMoney(businessPartner,partnerMoney);
				}
				cout<<"-------------------    387   ----------------------"<<endl;
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",14,5);
				send_msg(pg_hero->getFd(),g_out_buf);
				send_msg(businessPartner->getFd(),g_out_buf);
				
				pg_hero->bussinessData.init();
				pg_hero->getBag()->tradeFailed();
				businessPartner->bussinessData.init();	
				businessPartner->getBag()->tradeFailed();	
				
			//TODO 有待修改
			//增加好友度，有疑问RTX xhm,策划需求
			// cout<<"[XHM TEST] add the friend(playBusiness.cpp)"<<endl;
			if(businessPartner->getFriendInfo())
				(businessPartner->getFriendInfo())->addFriendDeg(pg_hero->getIdentity(),TRADE_ADD_FRIEND_DGR);
				
			if(pg_hero->getFriendInfo())
				(pg_hero->getFriendInfo())->addFriendDeg(businessPartner->getIdentity(),TRADE_ADD_FRIEND_DGR);
		}	
	}
	else
	{	
		// cout<<"-------------------    407   ----------------------"<<endl;
		pg_hero->bussinessData.bussinessFlag=3;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",14,4);
		send_msg(businessPartner->getFd(),g_out_buf);
	}
}






















