#include "midasTouch.h"
using namespace std;
extern MidasTouchNumber midasTouchNumber;	
MidasTouch::MidasTouch(void)
{	
	
}
MidasTouch::MidasTouch(MidasTouchData _midastouchdata)
{
	midastouchdata=_midastouchdata;
}

void MidasTouch::normalRefresh(char *msg,int len,Hero *hero)
{	
	if (msg==NULL)
	{
		return ;
	}
	midastouchdata.refreshNum--;
	midastouchdata.luckyRefreshMoney=10;
	int randomNum;
	for (int i=0;i<6;i++)
	{		
		randomNum=random_number(1,100);
		decideValue(i,randomNum);
	}	
	judgeReward(hero);

	snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",23,MIDASTOUCH_RETURN,midastouchdata.refreshNum,midastouchdata.luckyRefreshNum,midastouchdata.luckyRefreshMoney,\
	midastouchdata.value[0],midastouchdata.value[1],midastouchdata.value[2],midastouchdata.value[3],midastouchdata.value[4],\
	midastouchdata.value[5],midastouchdata.money,midastouchdata.popularity);
}

void MidasTouch::decideValue(int index,int randomNum)
{
	for (int i=0;i<6;i++)
	{
		if (randomNum<=midasTouchNumber.midasTouch[i].percent)
		{
			midastouchdata.value[index]=i+1;
			return;
		}
	}		
}

void MidasTouch::luckyRefresh(char *msg,int flag,int len,Hero *hero)
{
	if (msg==NULL)
	{
		return;
	}
	if (flag==1)
	{
		midastouchdata.luckyRefreshNum--;
	}
	else
	{		
		midastouchdata.luckyRefreshMoney+=5;
	}
	int randomNum;
	for (int i=0;i<6;i++)
	{
		if (midastouchdata.value[i]!=6)
		{			
			randomNum=random_number(1,100);
			decideValue(i,randomNum);
		}		
	}
	
	judgeReward(hero);	

	snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",23,MIDASTOUCH_RETURN,midastouchdata.refreshNum,midastouchdata.luckyRefreshNum,midastouchdata.luckyRefreshMoney,\
	midastouchdata.value[0],midastouchdata.value[1],midastouchdata.value[2],midastouchdata.value[3],midastouchdata.value[4],\
	midastouchdata.value[5],midastouchdata.money,midastouchdata.popularity);
}

void MidasTouch::reLoadMidasTouch(int freshNumber,int reNumber)
{
	midastouchdata.refreshNum=freshNumber;
	midastouchdata.luckyRefreshNum=reNumber;
	midastouchdata.luckyRefreshMoney=10;
}

void MidasTouch::msg_midasTouchInform(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",23,MIDASTOUCH_RETURN,midastouchdata.refreshNum,midastouchdata.luckyRefreshNum,midastouchdata.luckyRefreshMoney,\
	midastouchdata.value[0],midastouchdata.value[1],midastouchdata.value[2],midastouchdata.value[3],midastouchdata.value[4],\
	midastouchdata.value[5],midastouchdata.money,midastouchdata.popularity);
}

void MidasTouch::judgeReward(Hero *hero)
{
	int judge[6];
	for (int i=0;i<6;i++)
	{
		judge[i]=0;
	}
	midastouchdata.flag=0;
	midastouchdata.money=0;
	midastouchdata.popularity=0;
	for (int i=0;i<6;i++)
	{
		int num=midastouchdata.value[i]-1;
		if (num<0||num>5)
		{
			return ;
		}
		judge[num]++;		
	}
	for (int i=0;i<6;i++)
	{

		if (judge[i]!=0)
		{
			midastouchdata.money=midastouchdata.money+midasTouchNumber.midasTouch[i].money[judge[i]-1];
			midastouchdata.popularity=midastouchdata.popularity+midasTouchNumber.midasTouch[i].popularity[judge[i]-1];
			if (i!=5&&judge[i]>3)
			{
				midastouchdata.flag=1;
			}
			if (judge[i]==6)
			{
				/*一次搞到6个元宝，给头衔，幸运星*/
				if(hero)
				{
					hero->addTitle("T052");
				}
				
				break;
			}
		}
	}
}

void MidasTouch::receiveReward(void)
{
	for (int i=0;i<6;i++)
	{
		midastouchdata.value[i]=0;
	}
	midastouchdata.money=0;
	midastouchdata.popularity=0;
	midastouchdata.flag=0;
}

int MidasTouch::getRefreshNum(void)
{
	return midastouchdata.refreshNum;
}

void MidasTouch::setRefreshNum(int _refreshNum)
{
	midastouchdata.refreshNum=_refreshNum;
}

int MidasTouch::getLuckyRefreshNum(void)
{
	return midastouchdata.luckyRefreshNum;
}

void MidasTouch::setLuckyRefreshNum(int _luckyRefreshNum)
{
	midastouchdata.luckyRefreshNum=_luckyRefreshNum;
}

int MidasTouch::getLuckyRefreshMoney(void)
{
	return midastouchdata.luckyRefreshMoney;
}

void MidasTouch::setLuckyRefreshMoney(int _luckyRefreshMoney)
{
	midastouchdata.luckyRefreshMoney=_luckyRefreshMoney;
}

MidasTouchData MidasTouch::getMemStruct(void)
{
	return midastouchdata;
}

int MidasTouch::getMoney(void)
{
	return midastouchdata.money;
}

void MidasTouch::setMoney(int _money)
{
	midastouchdata.money=_money;
}

int MidasTouch::getPopularity(void)
{
	return midastouchdata.popularity;
}

void MidasTouch::setPopularity(int _popularity)
{
	midastouchdata.popularity=_popularity;
}

int MidasTouch::getFlag(void)
{
	return midastouchdata.flag;
}

void MidasTouch::setFlag(int _flag)
{
	midastouchdata.flag=_flag;
}

bool MidasTouch::isMax(void)
{
	int flag=0;
	for (int i=0;i<6;i++)
	{	
		if (midastouchdata.value[i]==6)
		{
			flag++;
		}
	}
	if (flag==6)
	{
		return true;
	}
	else
	{
		return false;
	}
}