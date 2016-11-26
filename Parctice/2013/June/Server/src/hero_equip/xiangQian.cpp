#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include"equipment.h"
using namespace std;
extern char g_out_buf[20480];
/*
* 返回值：0、失败；1、成功；2、不可锻造型装备 3、已镶嵌满
*/
int EquipOperateXQ(Hero *hero,Equipment *equip, char* goodsid, int index)
{
	if (hero==NULL||equip==NULL)
	{
		return 0;
	}

	if(strlen(goodsid) != 12)
	{
		return 0;
	}
	
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return 0;
	}
	
	if(equip->gettype() == 0||equip->gettype() == 13)	
	{
		return 2;
	}
		
	//第一，判断装备是否有足够的孔数
	int num_hole = equip->getHoleNumber();	
	vector<string> xq_bs = equip->getxq_bs();	 //装备上镶嵌的宝石的集合
	if(num_hole <= xq_bs.size())				//已镶嵌满
	{
		cout<<"equipmentHole:"<<num_hole<<endl;
		cout<<"xq_bs.size():"<<xq_bs.size()<<endl;
		return 3;
	}

	//第二，装备上同一类的宝石不能超过1颗
	int num = equip->getBsNumByTy(goodsid);
	cout<<"num:"<<num<<endl;
	if(num >= 1 || num < 0)	//num<0，表示数据异常
	{
		cout<<"@@Tory same jewel is over 3:"<<num<<endl;
		return 4; 
	}
	
	if (bag->test(index,goodsid))
	{
		if (useBagGoods(hero,goodsid,index,1)==0)
		{			
			goodsid[0]='b';
			//第三，将宝石镶嵌到装备上操作
			xq_bs.push_back(goodsid);
			equip->setxq_bs(xq_bs);
			
			equip->addBsNumByTy(goodsid);
			
			equip->diamonAttribute(hero,goodsid);
			//如果是穿在身上的装备进行了镶嵌，需同时修改人物属性,装备是否穿在身上 0:在背包内；1:在身上
			if(equip->getIsBag() == 1)
			{					
				hero->send_msg_att();	//更新客户端的人物属性面板
			}
			equip->wareEquipSetBound();	
			memset(g_out_buf,0,sizeof(g_out_buf));
			equip->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
			send_msg(hero->getFd(), g_out_buf);	

			if (goodsid[10] - '0' == 3)
			{
				cout<<"hero->getAllFourDiamonNumber():"<<hero->getAllFourDiamonNumber()<<endl;
				equip->xianQiangFourDiamon();
				
				if (hero->getAllFourDiamonNumber()==30)
				{
					hero->updataSingleTarget(7,3);
				}
			}
			
			return 1;
		}	
	}
	else
	{
		return 5;
	}
	
	return 10;
}