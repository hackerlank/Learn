#include "guildBussiness.h"
using namespace std;
extern map<string,int> goodsId_to_price; 			//帮派商店
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
void buyGuildBussiness(char* buffer)
{	
	char *goodsid;	
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(goodsid);
	MSG_INT(num);
	
	cout<<"9,13,"<<goodsid<<","<<num<<endl;
	
	Guild *guild=pg_hero->getGuild();
	if (guild==NULL)
	{
		msg_error(g_out_buf,53);
		cout<<"jolly:pg_hero has no guild in guildBUssiness 49"<<endl;
	}
	else
	{		
		map<string,int>::iterator it;
		it=goodsId_to_price.find(goodsid);
		if (it==goodsId_to_price.end())
		{
			cout<<"jolly:This goods is not sell in guild bussiness man guildBussiness 50"<<endl;
		}
		else
		{
			int price=it->second;
			price=price*num;
			int guildReward=guild->getHeroGlory(pg_hero->getIdentity());
			cout<<"guildReward:"<<guildReward<<endl;
			cout<<"price:"<<price<<endl;
			if (guildReward>=price)
			{
				if (saveGoodsInBag(pg_hero,goodsid,num))
				{
					if (guild->decHeroGlory(pg_hero->getIdentity(),price))
					{
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,GUILDGLORY,SUCCESS,guild->getHeroGlory(pg_hero->getIdentity()));
					}
				}
			}				
			else
			{
				msg_error(g_out_buf,52);
				cout<<"jolly:guild reward is not enough guildBussiness 72"<<endl;
			}
		}	
	}
	send_msg(pg_hero->getFd(),g_out_buf);
}

void GuildBussinessRequest(char* buffer)
{
	cout<<"9,14,"<<endl;
	
	Guild *guild=pg_hero->getGuild();
	if (guild==NULL)
	{			
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,GUILDGLORY,FAILED);
		cout<<"jolly:pg_hero has no guild in guildBUssiness 49"<<endl;
	}
	else
	{		
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",9,GUILDGLORY,SUCCESS,guild->getHeroGlory(pg_hero->getIdentity()));
	}
	send_msg(pg_hero->getFd(),g_out_buf);	
}