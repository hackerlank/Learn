#include "mysteriousBussiness_communicate.h"
#include "money_operator.h"
#include "wholeDefine.h"
using namespace std;
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern Role *pg_role;
extern char server_name[10];
void mysteriousBussiness_return(char *buffer)
{
	MysteriousBussiness *mysteriousbussiness=pg_hero->getMysteriousBussiness();
	if (mysteriousbussiness==NULL)
	{
		return;
	}
	mysteriousbussiness->verifyFlag();
	if (mysteriousbussiness->isTimerForRefresh())
	{
		mysteriousbussiness->refreshGoods(pg_hero->getLevel());
		mysteriousbussiness->setFlag(1);
	}
	mysteriousbussiness->msg_mysteriousGoods(g_out_buf);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void mysteriousBussiness_refresh(char *buffer)
{
	cout<<"9,8,"<<endl;
		
	MysteriousBussiness *mysteriousbussiness=pg_hero->getMysteriousBussiness();
	if (mysteriousbussiness==NULL)
	{
		return;
	}
	if (useGold(pg_hero,mysteriousbussiness->getRefreshMoney()))
	{
		mysteriousbussiness->refreshGoods(pg_hero->getLevel());
		mysteriousbussiness->refreshIncreaseMoney();
		mysteriousbussiness->msg_mysteriousRefresh(g_out_buf);
		send_msg(pg_hero->getFd(),g_out_buf);
		
		//记录日志2013.4.28
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),pg_role->getUserName(),mysteriousbussiness->getRefreshMoney());
		write_log(account_msg);	
	}	
}

void mysteriousBussinessBuy(char *buffer)
{	
	int index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	
	//protected by benliao
	if((index < 0) || (index >9))
		return;
	
	if(pg_hero->getisRedName())
	{
		msg_error(g_out_buf,43);
		cout<<"jolly:name is red so you can't buy mysterious_communicate 109"<<endl;
	}
	else
	{
		if(!pg_hero->getBag()->bagIsFull(1))
		{
			MysteriousBussiness *mysteriousbussiness=pg_hero->getMysteriousBussiness();
			if (mysteriousbussiness==NULL)
			{
				return;
			}
			if (mysteriousbussiness->getBuyFlag(index)==0)
			{
				char* goodsId=mysteriousbussiness->getIdentiy(index);	
				int price=mysteriousbussiness->getPrice(index);
				if (useBoundGameMoney(pg_hero,price))
				{
					saveGoodsInBag(pg_hero,goodsId,1);
					sprintf(g_out_buf,"%d,%d,%d",9,MYSTERIOUS_BUY,index);
					mysteriousbussiness->setBuyFlag(1,index);
				}
			}
			else
			{
				msg_error(g_out_buf,45);
			}
		}
		else
		{
			msg_error(g_out_buf,44);
		}
	}			
	send_msg(pg_hero->getFd(),g_out_buf);	
}
