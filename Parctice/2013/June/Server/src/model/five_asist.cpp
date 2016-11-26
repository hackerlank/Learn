/****************************************************************
 * Filename: five_asist.h
 * 
 * Description: 五行操作处理
 *
 * Original Author : bison, 2012-7-19
 *
 ****************************************************************/
 
#include"five_asist.h"

#include "money_operator.h"

extern map<string, Hero*> heroId_to_pHero;
/***************************************************************************
 * openFiveElem - 开启角色五行属性
 * @hero: 所要操作的角色指针
 * @elem: 所要初始的五行属性
 * @index: 宠物栏下标。为-1时表示操作是针对玩家,
 *		   否则是对玩家宠物栏中第index个宠物操作
 * Return: true:初始成功；false:初始失败
 ***************************************************************************/
bool openFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index)
{
	FiveElem *fiveElement = NULL;
	if (index == 20)
	{
		//角色大于25级才能开启五行属性
		if (hero->getLevel() < heroFiveElemConf.startLevel)
		{
			return false;
		}
		fiveElement = hero->getFiveElem();
		
	}
	else {
		//index 不为-1，则开启五行是对宠物操作
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			return false;
		} else if(pet->getLevel() < heroFiveElemConf.startLevel) {
			return false;
		}
		
		fiveElement = pet->fiveElem;
	}
	
	if(fiveElement==NULL)
	{
		return false;
	}
	
	//已经有五行属性不能再初始
	if ((fiveElement->getElem() != NOELEM))
	{
		return false;
	}
	//五行属性由NOELEM-->elem
	fiveElement->changeElem(elem);
	
	//五行等级由0-->1
	fiveElement->upGrade();
	
	//修改人物存到memcache中的数据
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memHero->fiveElementData.level += 1;
		hero->memHero->fiveElementData.expForNext = 4;		//这是1级的时候升级需要的
		hero->memSet();
	}
	return true;
}

/***************************************************************************
 * changeFiveElem - 初始化角色五行属性
 * @elem: 所要更改成的五行属性
 * @hero: 所要操作的角色指针
 * @index: 宠物栏下标。为-1时表示操作是针对玩家,
 *		   否则是对玩家宠物栏中第index个宠物操作
 * @order: 五行更改丹在背包中的位置
 * Return: true:更改成功；false:更改失败
 ***************************************************************************/
bool changeFiveElem(Hero *hero, FIVE_ELEMENT_T elem, int index, int order)
{
	// Money *gold = hero->getMoney();
	FiveElem *fiveElement;
	Bag *bag = hero->getBag();
	
	if (elem < 1 || elem > 5)
	{
		cout<<"BisonTest: elem is out range "<<elem <<endl;
		return false;
	}
	char *goodsId = "f_cl_100_100";
	if (useBagGoods(hero,goodsId, order, 1))
	{
		cout<<"BisonTest: use goods Fail！！！"<<endl;
		return false;
	}
	
	if (index == 20)
	{
		fiveElement = hero->getFiveElem();
	} else {
		//index 不为-1，则开启五行是对宠物操作
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			cout<<"BisonTest: NO PET YOU specifed send!"<<endl;
			return false;
		}
		fiveElement = pet->fiveElem;
	}	
	
	fiveElement->changeElem(elem);
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memSet();
	}
	return true;
}

//更改五行属性
int changeFiveElemNew(Hero *hero, FIVE_ELEMENT_T elem, int index)
{
	FiveElem *fiveElement;
	if (elem < 1 || elem > 5)
	{
		cout<<"BisonTest: elem is out range "<<elem <<endl;
		return 1;
	}
	
	if (index == 20)
	{
		if (hero->getLevel() < heroFiveElemConf.startLevel)
		{
			return 3;
		}
		fiveElement = hero->getFiveElem();
	} else {
		//index 不为-1，则开启五行是对宠物操作
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getPet(index);
		if (pet == NULL)
		{
			cout<<"BisonTest: NO PET YOU specifed send!"<<endl;
			return 2;
		}
		if (pet->getLevel() < heroFiveElemConf.startLevel)
		{
			return 3;
		}
		fiveElement = pet->fiveElem;
	}	
	
	if (fiveElement == NULL)
	{
		return 3;
	}
	if (!useGold(hero, heroFiveElemConf.changeNeedGold))
	{
		return 4;
	}
	
	fiveElement->changeElem(elem);
	if (index == 20)
	{
		hero->memHero->fiveElementData.element = elem;
		hero->memSet();
	}
	return 0;
}

/*****************************************************************************
 * upGradeFiveElem - 玩家使用五行丹升级五行等级接口
 * @hero: 所要操作的角色指针
 * @index: 宠物栏下标。为-1时表示操作是针对玩家,
 *		   否则是对玩家宠物栏中第index个宠物操作
 * Return: true:升级成功；false:升级失败
 *****************************************************************************/
/*
bool upGradeFiveElem(Hero *hero, int index)
{
	int level = hero->getLevel();
	FiveElem *fiveElement = hero->getFiveElem();
	if (index == -1)
	{
		level = hero->getLevel();
		fiveElement = hero->getFiveElem();
	} else {
		//index 不为-1，则开启五行是对宠物操作
		Pet *pet = hero->getPet(index);
		if (pet == NULL)
		{
			return false;
		}
		level = pet->getLevel();
		FiveElem *fiveElement = pet->getFiveElem();
	}
	
	Bag *bag = hero->bag;
	if ((level - fiveElement->getLevel()) < 25)
	{
		//五行等级最高也要比英雄等级低20级
		return false;
	}
//现在五行丹物品还没有，等有了再打开
#if 0
	int thirdPillNum = bag->getGoodsNum(thirdPill);			//三级五行丹数量
	int secondPillNum = bag->getGoodsNum(secondPill);		//二级五行丹数量
	int firstPillNum = bag->getGoodsNum(firstPill);			//一级五行丹数量
	
	if (thirdPillNum >= 1)
	{
		//一个三级五行丹能升一级
		if (fiveElement->upGrade())
		{
			//升级成功扣除三级五行丹一颗
			bag->useGoods(thirdPill, 1);
			return true;
		}
	} else if (secondPillNum >= 4) {
		//四个二级五行丹能升一级
		if (fiveElement->upGrade())
		{
			bag->useGoods(secondPill, 4);
			return true;
		}
	} else if ((secondPillNum * 4 + firstPillNum) >= 16) {
		if (fiveElement->upGrade())
		{
			//混扣二级五行丹和一级五行丹
			bag->useGoods(secondPill, secondPillNum);
			bag->useGoods(firstPill, 16 - secondPillNum * 4);
			return true;
		}
	}
#endif

	return false;
}
*/

/*****************************************************************************
 * useFiveElemGoods - 玩家使用五行丹增加五行经验
 * @hero: 所要操作的角色指针
 * @goodsId: 使用的五行丹ID
 * @order: 五行丹在背包中的位置
 * @index: 宠物栏下标。为-1时表示操作是针对玩家,
 *		   否则是对玩家的出战宠物操作
 * Return: true:增加经验成功；false:增加经验失败
 *****************************************************************************/
bool useFiveElemGoods(Hero *hero, char* goodsId, int order, int index)
{
	char msg[64] = {0};
	int ret = 0;
	int level;
	FiveElem *fiveElement;
	int val;							//丹药增加五行的经验值
	
	Bag *bag = hero->getBag();
	
	if (index == 20)
	{
		//是对英雄使用
		level = hero->getLevel();
		fiveElement = hero->getFiveElem();
		
		//人物必须使用人物的五行丹药
		if (!strcmp(goodsId, "f_dj_100_102") || !strcmp(goodsId, "b_dj_100_102"))
		{
			val = 4;
		} else if (!strcmp(goodsId, "f_dj_100_101") || !strcmp(goodsId, "b_dj_100_101")) {
			val = 2;
		} else if (!strcmp(goodsId, "f_dj_100_100") || !strcmp(goodsId, "b_dj_100_100")) {
			val = 1;
		} else {
			//不是人物使用的五行丹
			cout<<"BisonTest: It is not the five pills for hero using"<<endl;
			//不是正确的太极般若丹Id
			ret = 1;
			return false;
		}
	} else {
		//index 不为-1，则使用五行道具是对宠物操作
		//Pet *pet = hero->getPet(index);
		//因为现在策划规定五行丹只在背包中吃，背包中默认给出战宠物吃
		Pet_Box *pet_box = hero->getPetBox();
		Pet *pet = pet_box->getActivePet();
		if (pet == NULL)
		{
			cout<<"BisonTest: No this Pet with this index when eat five pills"<<endl;
			//玩家无宠物
			ret = 2;
			return false;
		}
		level = pet->getLevel();
		FiveElem *fiveElement = pet->fiveElem;
		//宠物必须使用宠物的五行丹药
		if (!strcmp(goodsId, "f_dj_101_102") || !strcmp(goodsId, "b_dj_101_102"))
		{
			val = 4;
		} else if (!strcmp(goodsId, "f_dj_101_101") || !strcmp(goodsId, "b_dj_101_101")) {
			val = 2;
		} else if (!strcmp(goodsId, "f_dj_101_100") || !strcmp(goodsId, "b_dj_101_100")) {
			val = 1;
		} else {
			//不是宠物使用的五行丹
			cout<<"BisonTest: It is not the five pills for pet using"<<endl;
			ret = 3;
			return false;
		}
	}
	if (fiveElement->getLevel() == 0)
	{
		//五行还没开始激活
		ret = 4;
		return false;
	}
	//五行等级最高也要比英雄等级低25级时才可以升级
	if (level < heroFiveElemConf.needHeroLevel[fiveElement->getLevel()] || fiveElement->getLevel() >= 60)
	{
		cout<<"BisonTest: level limit to use fiveElement Exp Pills"<<endl;
		ret = 5;
		return false;
	}
	
	if (useBagGoods(hero,goodsId, order, 1))
	{
		cout<<"BisonTest: use goods fail when eat fiveElem pills"<<endl;
		ret = 6;
		return false;
	}
	
	fiveElement->addExp(val);
	
	if (index == 20)
	{
		hero->memHero->fiveElementData.expNow = fiveElement->getExpNow();
		hero->memHero->fiveElementData.level = fiveElement->getLevel();
		hero->memHero->fiveElementData.expForNext = fiveElement->getExpForNext();
		
		hero->memSet();
	}
	sprintf(msg, "8,9,0,%d", ret);
	send_msg(hero->getFd(), msg);
	return true;
}

/*****************************************************************************
 * getFiveElemHurt - 五行伤害计算
 * @fiveHit: 攻击者的五行
 * @fiveHited: 被攻击者的五行
 * Return: 攻击后的伤害
 *****************************************************************************/
int getFiveElemHurt(FiveElem *fiveHit, FiveElem *fiveHited)
{

	//cout<<"fiveHit "<<fiveHit->getLevel()<<" "<<fiveHit->getValue()<<" " <<fiveHit->getElem()<<endl;
	//cout<<"fiveHit "<<fiveHited->getLevel()<<" "<<fiveHited->getValue()<<" " <<fiveHited->getElem()<<endl;
	//被攻击者对攻击者的五行抗性
	double k = fiveHited->getFactor(fiveHit->getElem());
	//cout<<"BisonTest k is "<<k<<endl;
	//攻击者打被攻击者附加的五行伤害
	int hurt = fiveHit->getHurt(k);
	
	return hurt;
}