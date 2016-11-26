#include "shengWang_bussiness.h"
using namespace std;
extern char g_out_buf[20480];
extern Hero *pg_hero;
extern int g_msg_len;
extern map<string,int> goodsId_to_price_shengWang; 	
void buyShengWangGoods(char* buffer)
{
	char *goodsid;	
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(goodsid);
	MSG_INT(num);
	
	cout<<"9,15,"<<goodsid<<","<<num<<endl;
	
	map<string,int>::iterator it;
	it=goodsId_to_price_shengWang.find(goodsid);
	if (it==goodsId_to_price_shengWang.end())
	{
		cout<<"jolly:This goods is not sell in shengwang bussiness man shengWang_bussiness 22"<<endl;
	}
	else
	{
		int price=it->second;
		price=price*num;
		int shengWang=pg_hero->getPrestigeValue();
		if (price>shengWang)
		{
			msg_error(g_out_buf,59);
		}
		else
		{
			if (saveGoodsInBag(pg_hero,goodsid,num))
			{
				pg_hero->reducePrestigeValue(price);
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,SHENGWANG_RETURN,pg_hero->getPrestigeValue());
			}
			else
			{
				return;
			}			
		}
	}	
	send_msg(pg_hero->getFd(),g_out_buf);
}

void shengWangBussinessRequest(char* buffer)
{
	cout<<"9,16"<<endl;
	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,SHENGWANG_RETURN,pg_hero->getPrestigeValue());
	send_msg(pg_hero->getFd(),g_out_buf);	
}