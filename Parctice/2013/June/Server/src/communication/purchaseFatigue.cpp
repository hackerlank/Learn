/*
		文件类型：实现文件
		文件名称：purchaseFatigue.cpp
		文件作用：购买体力值
		修改人：chenzhen
		修改时间：2013.10.24
*/
#include"cpyAsist.h"
#include"hero.h"
#include"wholeDefine.h"

extern int g_msg_len;
extern Hero* pg_hero;

/*购买体力值*/
void purchaseFatigue(char *buffer)
{
	char *heroId,purchaseMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Hero* myHero;
	 
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	myHero = pg_hero;
	
	if(myHero->memHero->lastStrength == myHero->memHero->fatigueUpperVal)
	{
		cout<<"the fatigue is full:"<<endl;
		
		/*体力是满的*/
		sprintf(purchaseMsg,"3,27,%d",1);

		send_msg(myHero->getFd(), purchaseMsg);
		
		return;
	}
	
	if(!myHero->isCanBuyFatigue())
	{
		cout<<"purchaseFatigue you have not times to buy the fatigue:"<<myHero->getIdentity()<<endl;
		
		/*购买次数已满*/
		sprintf(purchaseMsg,"3,27,%d",0);

		send_msg(myHero->getFd(), purchaseMsg);
		return;
	}
	
	/*购买一次20绑定元宝*/
	if(myHero->useMoney(1,20))
	{
		myHero->setFatigueVal(myHero->memHero->lastStrength + 20);		

		sprintf(purchaseMsg,"8,12,%s,%d,%d",myHero->getIdentity(),myHero->memHero->lastStrength,myHero->memHero->fatigueUpperVal);

		send_msg(myHero->getFd(), purchaseMsg);
		
		++myHero->memHero->buyFatigueTmes;
		
		
		memset(purchaseMsg,'\0',sizeof(purchaseMsg));
		
		/*购买成功*/
		sprintf(purchaseMsg,"3,27,%d",2);

		send_msg(myHero->getFd(), purchaseMsg);
	}
	
	
}




