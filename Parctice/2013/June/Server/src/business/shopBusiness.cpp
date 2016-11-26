#include"anyBusiness.h"
#include <set>
#include <map>
#include"hero.h"
#include"other_define_data.h"
#include "money_operator.h"
using namespace::std;
extern set<string>shop; 
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Equip_config*>id_to_equip; 
extern map<string,Ointment *>id_to_ointment;
extern map<string,Goods_Config*> id_to_dj;				
extern map<string,Goods_Config*> id_to_cl;
extern map<int, Role*> fd_to_pRole;
extern int sock_fd;
extern int g_msg_len;
extern Hero * pg_hero;
extern char g_out_buf[20480];
extern char server_name[10];

void shopBusiness(char *buff)
{
	MSG_BEGIN(buff,g_msg_len);
	MSG_CHAR(char *goodsIdChar);	//物品id
	MSG_INT(int goodsNum);

	//最多一次买100个
	if((goodsNum <= 0 ) || (goodsNum > 100)) 
	{ 
		return;
	}

	int goodsType = getGoodsType(goodsIdChar);//购买商品类型	
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,",14,21);
	
	//根据goodsid获取物品配置类
	int boundGold,gold;
	Equip_config *equip;
	Goods_Config *goods;
	switch(goodsType)
	{
		case 1:
			//根据物品类型去对应容器查找物品实例
			if(id_to_equip.find(goodsIdChar)==id_to_equip.end())
			{
				snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",2);
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			equip=id_to_equip.find(goodsIdChar)->second;     
			boundGold=equip->getgoldBound()*goodsNum ;
			gold=equip->getgold()*goodsNum;
			break;
		case 2:
			//根据物品类型去对应容器查找物品实例
			if(id_to_dj.find(goodsIdChar)==id_to_dj.end())
			{
				snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",2);
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			goods=id_to_dj.find(goodsIdChar)->second; 
			boundGold=goods->getGoldBound()*goodsNum ;
			gold=goods->getGold()*goodsNum;
			break;
		case 3:
			//根据物品类型去对应容器查找物品实例
			snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",2);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"this is error id , do nothing for this "<<endl;
			return;
		break;
		case 4:
			//根据物品类型去对应容器查找物品实例
			if(id_to_cl.find(goodsIdChar)==id_to_cl.end())
			{
				snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",2);
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			goods=id_to_cl.find(goodsIdChar)->second;   
			boundGold=goods->getGoldBound()*goodsNum ;						
			gold=goods->getGold()*goodsNum;
			break;
	}
		
	if (boundGold!=0)
	{
		if(campareBoundGold(pg_hero,boundGold))
		{
			if (saveGoodsInBag(pg_hero,goodsIdChar,goodsNum))
			{
				useBoundGold(pg_hero,boundGold);
				snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",1);
				send_msg(pg_hero->getFd(),g_out_buf);
				/*记录商城买物品的流水账 jolly 2,2 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",15,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),goodsIdChar,goodsNum,boundGold);
				write_log(account_msg);	
				/*记录商城买物品的流水账 jolly 2,2 end*/	
			}
		}
	}
	
	if (gold!=0)
	{
		if(campareGold(pg_hero,gold))
		{
			if (saveGoodsInBag(pg_hero,goodsIdChar,goodsNum))
			{
				useGold(pg_hero,gold);
				snprintf(g_out_buf,sizeof(g_out_buf)-strlen(g_out_buf),"%d",1);
				send_msg(pg_hero->getFd(),g_out_buf);
				/*记录商城买物品的流水账 jolly 2,2 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",15,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),goodsIdChar,goodsNum,gold);
				write_log(account_msg);	
				/*记录商城买物品的流水账 jolly 2,2 end*/	
				
				//判断所购买物品是否为三倍经验丹
				if(strcmp(goodsIdChar,"f_dj_118_101") == 0)
				{
					pg_hero->memHero->buyThreeTmeExpCtn += goodsNum;
					
					//给头衔，疯狂练级者
					if(pg_hero->memHero->buyThreeTmeExpCtn >= 100)
					{
						pg_hero->addTitle("T018");
					}
				}
						
				
			}		
		}
	}	
}
void draw(char *buff)
{
	snprintf(g_out_buf,sizeof(g_out_buf),"14,10,0,60");
	send_msg(sock_fd,g_out_buf);
	cout<<"in shopBusiness 180"<<endl;
}
