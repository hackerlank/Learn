#include "wulinTarget.h"
#include "hero.h"
#include "wholeDefine.h"
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern vector<string> wuLinTarget;
extern WuLinTargetConfig wuLinTargetConfig[10];
//获取玩家所有武林目标数据
void wulinTargetReturn(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
	MSG_INT(int page)
	cout<<"22,6,"<<page<<endl;
	if (page<0||page>9)
	{
		return;
	}
	memset(g_out_buf,0,sizeof(g_out_buf));
	int chapter=0;
	if (pg_hero->memHero->targetFinishNumber[page]==-1)
	{
		chapter=2;
	}
	else if (wuLinTargetConfig[page].totalNumber==pg_hero->memHero->targetFinishNumber[page])
	{
		chapter=1;
	}
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,TARGET_RETURN,chapter);
	for  (int i=0;i<wuLinTargetConfig[page].totalNumber;i++)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d",i,pg_hero->memHero->targetItem[page][i]);
	}
	send_msg(pg_hero->getFd(),g_out_buf);
}

void wulinTargetReceive(char *buff)
{
	MSG_BEGIN(buff,g_msg_len);
	MSG_INT(int flag)
	MSG_INT(int page)
	MSG_INT(int id);
	
	cout<<"22,7,"<<flag<<","<<page<<","<<id<<endl;
	
	if (page<0||page>9)
	{
		return;
	}
	if (id<0||id>=50) //changed by benliao 2012.12.04
	{
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	if (flag==0)
	{
		if (wuLinTargetConfig[page].totalNumber==pg_hero->memHero->targetFinishNumber[page])
		{
			if (saveGoodsInBag(pg_hero,wuLinTargetConfig[page].goodsid,wuLinTargetConfig[page].number))
			{
				pg_hero->receiveTargetSuccess(page,id);
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",23,TARGET_RECEIVE,2,page);
				send_msg(pg_hero->getFd(),g_out_buf);
				pg_hero->memHero->targetFinishNumber[page]=-1;
			}
		}
		else
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,TARGET_RECEIVE,3);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}
	else if (flag==1)
	{
		if (pg_hero->isTargetFinish(page,id))
		{
			if (saveGoodsInBag(pg_hero,wuLinTargetConfig[page].wuLinTargeItemtConfig[id].goodsid,wuLinTargetConfig[page].wuLinTargeItemtConfig[id].number))
			{
				pg_hero->receiveTargetSuccess(page,id);
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d",23,TARGET_RECEIVE,SUCCESS,page,id);
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}
		else
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,TARGET_RECEIVE,FAILED);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}
}
