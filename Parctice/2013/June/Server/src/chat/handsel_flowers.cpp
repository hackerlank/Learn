/*
		文件类型：实现文件
		文件名称：handsel_flowers.cpp
		文件作用：赠送鲜花；
		修改人：xhm
		修改时间：2012.11.30 13:56
*/

#include"chat.h"

#include <string.h>

#include"friend.h"
#include"hero.h"
#include "goods_use_reward.h"
#include "system_activity_reward_assist.h"

#define ROSES_F1	"f_cl_102_100"
#define ROSES_B1	"b_cl_102_100"
#define ROSES_F99	"f_cl_102_101"
#define ROSES_B99	"b_cl_102_101"
#define ROSES_F999	"f_cl_102_102"
#define ROSES_B999	"b_cl_102_102"

char handsel_flowers_ret[2048];

extern int sock_fd;
extern int g_msg_len;
extern Hero * pg_hero;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Goods_Config*> id_to_cl;

extern Goods_use_reward* goods_use_reward_asist;

void handsel_flowers(char *buffers)
{	
	MSG_BEGIN(buffers,g_msg_len);
	MSG_CHAR(char *recipientId);
	MSG_CHAR(char *goodsId);
	MSG_INT(int index);
	MSG_CHAR_END(char *bless_info);

	// cout<<"[XHM MSG] Hander the function handsel_flowers!"<<endl;
	// cout<<"[XHM MSG] The recipientId:"<<recipientId<<endl;
	// cout<<"[XHM MSG] The goodsId:"<<goodsId<<endl;
	// cout<<"[XHM MSG] The index:"<<index<<endl;
	// cout<<"[XHM MSG] bless_info:"<<bless_info<<endl;
	
	if(recipientId == NULL || strlen(recipientId) == 0 ||goodsId == NULL || strlen(goodsId) == 0 )
	{
		sprintf(handsel_flowers_ret,"13,5,1,0");
		send_msg(sock_fd,handsel_flowers_ret);
		return;
	}
	
	map<string,Hero*>::iterator iter=heroId_to_pHero.find(recipientId);
	if(iter == heroId_to_pHero.end())
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		msg_error(g_out_buf,127);
		send_msg(sock_fd,g_out_buf);
		return;
	}
	
	int add_friend_value=0;
	int add_prestige=0;
	int add_goods_size=0;
	
	if(useBagGoods(pg_hero,goodsId,index,1)==0)
	{	
		bool flag_goods=false;
		Goods_Config *GoodsInist=NULL;
		
		map<string,Goods_Config*>::iterator it_goods;
		it_goods=id_to_cl.find(goodsId);
		char goodsName[40]={'\0'};

		if (it_goods==id_to_cl.end())
		{
			cout<<"jolly:不好意思,悲剧了..."<<endl;
			strncpy(goodsName,"某些东西",sizeof(goodsName));
		}
		else
		{
			GoodsInist=it_goods->second;
			strncpy(goodsName,GoodsInist->getName(),sizeof(goodsName));
			flag_goods=true;
		}
	
		if(!strcmp(goodsId,ROSES_F999)||!strcmp(goodsId,ROSES_B999))
		{
			sprintf(handsel_flowers_ret,"13,7,%s,%s,%s,%s,%s,%s",pg_hero->getIdentity(),pg_hero->getNickName(),goodsId,bless_info,iter->second->getNickName(),iter->second->getIdentity());
			//全服发送消息；
			cout<<"-----------------------------88------------------------------"<<endl;
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%d",\
			7,SYSTEM_WARN,"xf016",3,\
			1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,\
			1,iter->second->getNickName(),iter->second->getIdentity(),0,0,\
			4,goodsName,goodsId,goodsId,0);
			char msg[1024]={0};
			snprintf(msg,sizeof(msg),"%d,%d,%d,%d,%s,%s",4,25,0,1,bless_info,pg_hero->getNickName());
			for(map<string, Hero*>::iterator iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();iter++)
			{
				send_msg(iter->second->getFd(),handsel_flowers_ret);	
				send_msg(iter->second->getFd(),g_out_buf);
				send_msg(iter->second->getFd(),msg);	
			}	
			add_goods_size=999;
		}	
		
		if (flag_goods)
		{
			// cout<<"goodsId:"<<goodsId<<endl;
			add_friend_value=goodsReturnInt(GoodsInist,0);//魅力值
			add_prestige=goodsReturnInt(GoodsInist,1);//声望
		}		
		
		//TODO 赠送成功,接受者增加魅力值；增加的大小和物品有关系；
		iter->second->addFriendLevel(add_friend_value);	
		
		/*接受的花不小于100，给头衔，颇受欢迎，有可能同时给几个头衔呀*/
		if(iter->second->getFriendLevel() >= 100)
		{
			iter->second->addTitle("T012");
		}
		
		/*接受的花不小于1000，给头衔，千人迷*/
		if(iter->second->getFriendLevel() >= 1000)
		{
			iter->second->addTitle("T013");
		}
		
		/*接受的花不小于10000，给头衔，万人迷*/
		if(iter->second->getFriendLevel() >= 10000)
		{
			iter->second->addTitle("T014");
		}
		

		//TODO 有待修改
		//如果是好友彼此增加好友度，有疑问RTX xhm,策划需求
		if(pg_hero->getFriendInfo())
			(pg_hero->getFriendInfo())->addFriendDeg(iter->second->getIdentity(),FLOWERS_ADD_FRIEND_DGR,1);
			
		if(iter->second->getFriendInfo())
			(iter->second->getFriendInfo())->addFriendDeg(pg_hero->getIdentity(),FLOWERS_ADD_FRIEND_DGR,1);	
			
		//TODO 赠送者自身增加声望。
		pg_hero->addPrestigeValue(add_prestige);
		
		sprintf(handsel_flowers_ret,"13,6,%s,%s,%s,%d,%s",pg_hero->getIdentity(),pg_hero->getNickName(),goodsId,add_friend_value,bless_info);
		send_msg(iter->second->getFd(),handsel_flowers_ret);		
		sprintf(handsel_flowers_ret,"13,5,0,%d",add_prestige);
		send_msg(sock_fd,handsel_flowers_ret);
		iter->second->send_msg_att();
		
		//更新送花奖励；
		time_t time_now = time(NULL);
		if(isNowGoodsUseReward(time_now))
		{
			if(!strcmp(goodsId,ROSES_F99)||!strcmp(goodsId,ROSES_B99))
			{	
				add_goods_size=99;
			}else if(!strcmp(goodsId,ROSES_F1)||!strcmp(goodsId,ROSES_B1))	
			{
				add_goods_size=1;
			}			
			
			cout<<"TIME isNowGoodsGainReward"<<endl;			
			pg_hero->memHero->goods_use_size += add_goods_size;
			
			goods_use_reward_asist->add_goods_use_id_reward_team(pg_hero->getIdentity(),pg_hero->memHero->goods_use_size);	
		}else{
			cout<<"NOT TIME isNowGoodsUseReward"<<endl;
			pg_hero->memHero->goods_use_size=0;
		}
		
		if(isNowGoodsGainReward(time_now))
		{
			if(!strcmp(goodsId,ROSES_F99)||!strcmp(goodsId,ROSES_B99))
			{	
				add_goods_size=99;
			}else if(!strcmp(goodsId,ROSES_F1)||!strcmp(goodsId,ROSES_B1))	
			{
				add_goods_size=1;
			}		
			
			cout<<"TIME isNowGoodsGainReward"<<endl;
			
			iter->second->memHero->goods_gain_size +=add_goods_size;
			goods_use_reward_asist->add_goods_gain_id_reward_team(iter->second->getIdentity(),iter->second->memHero->goods_gain_size);	
		}else{
			cout<<"NOT TIME isNowGoodsGainReward"<<endl;
			iter->second->memHero->goods_gain_size=0;		
		}
		
		
		
	}else{
		sprintf(handsel_flowers_ret,"13,5,2,%d",add_prestige);
		send_msg(sock_fd,handsel_flowers_ret);	
	}
	
}