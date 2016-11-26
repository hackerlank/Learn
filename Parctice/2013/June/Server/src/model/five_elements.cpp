/****************************************************************
 * Filename: five_elements.h
 * 
 * Description: 五行类操作实现及五行伤害计算
 *
 * Original Author : bison, 2012-7-10
 *
 ****************************************************************/
 
#include"five_elements.h"
#include "hero.h"
extern Hero *pg_hero;

extern map<string, Hero*> heroId_to_pHero;
/****************************************************************
 * FiveElem - 五行构造函数
 * @elem: 五行的属性值，默认为NOELEM 无五行属性
 * @_level: 五行等级，默认为0
 ****************************************************************/
FiveElem::FiveElem(FIVE_ELEMENT_T elem, int _level)
{
	element = elem;
	level = _level;
	expNow = 0;												//当前经验
	expForNext = heroFiveElemConf.upgradeNeedExp[level];	//升到下一级需要经验值
}

//根据memcache读上来的数据进行构造
FiveElem::FiveElem(FiveElementData fiveData)
{
	level = fiveData.level;
	element = (FIVE_ELEMENT_T)fiveData.element;
	expNow = fiveData.expNow;
	expForNext = fiveData.expForNext;
}

/****************************************************************
 * changeElem - 改变五行属性
 * @elem: 所要更改成的五行属性值
 * Return: bool型，false:不是有效的五行属性值；true:改变成功
 ****************************************************************/
bool FiveElem::changeElem(FIVE_ELEMENT_T elem)
{
	//这里不能改成NOELEM
	if (elem < 1 || elem > 5)
	{
		return false;
	}
	element = elem;
	return true;
}

//得到五行等级
int FiveElem::getLevel(void)
{
	return level;
}

//得到五行的属性值
FIVE_ELEMENT_T FiveElem::getElem(void)
{
	return element;
}

/*****************************************************************
 * upGrade - 五行升级，每次调用等级升1
 *
 * Return: false:升级失败，已经升到顶级；true:升级成功
 *****************************************************************/
bool FiveElem::upGrade(void)
{
	if ((level + 1) > 60)
	{
		//五行最高能升到60级
		return false;
	}
	
	level++;
	
	//更新升级到下一等级需要的经验
	if (level < 60)
	{
		expForNext = heroFiveElemConf.upgradeNeedExp[level];	//升到下一级需要经验值
	}
	
	
	if (pg_hero->memHero->fiveElementData.level==40||pg_hero->memHero->fiveElementData.level==50||pg_hero->memHero->fiveElementData.level==60)
	{
		char info[1024]={'\0'};
		snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf012",3,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,6,pg_hero->memHero->fiveElementData.element,0,0,0,3,pg_hero->memHero->fiveElementData.level,0,0,0);
		map<string, Hero*>::iterator it_hero;

		for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
		{
			if (it_hero->second!=NULL)
			{						
				send_msg(it_hero->second->getFd(),info);
			}
		}
	}
		
	
	return true;
}

/*****************************************************************
 * getValue - 获取五行数值
 * Return: 返回当前五行数值
 *****************************************************************/
int FiveElem::getValue(void)
{
	int ret;
	if (level == 0 || element == NOELEM)
	{
		ret = 0;
	} else {
		ret = heroFiveElemConf.fiveValue[level];	//升到下一级需要经验值
	}
	
	return ret;
}

/*****************************************************************
 * getFactor - 被攻击的五行抗性
 * @hitElem: 攻击者的五行属性
 * Return: 返回被攻击者的五行抗性值
 *****************************************************************/
double FiveElem::getFactor(FIVE_ELEMENT_T hitElem)
{
	double k;				//被攻击之的五行抗性系数
	double ret;				//被攻击者的五行抗性
#if 0	
	//如果攻击者没有五行属性
	if (hitElem == NOELEM)
	{
		//cout<<"BisonTest hit also no elem k is 1.0"<<endl;
		k = 1.0;
	}
	
	//如果被攻击者没有五行属性
	 else if (element == NOELEM)
	{
		//cout<<"BisonTest NoElem k is 0.0"<<endl;
		k = 0.0;
	}
	
	
	else if ((hitElem % 5 + 1) == element)
	{
		//如果攻击者五行属性克制被攻击者五行属性
		k = 0.001;
	} else if ((element % 5 + 1) == hitElem)
	{
		//被攻击者五行属性克制攻击者五行属性
		k = 0.003;
	} else {
		//攻击者和被攻击者五行属性互不克制
		k = 0.002;
	}

#endif
	k = heroFiveElemConf.defFactor[element - 1][hitElem - 1];
	//cout<<k<<endl;
	if (k == 1.0)
	{
		//被攻击者对没有五行属性的攻击者抗性为1
		//cout<<"BisonTest factor ret is 1"<<endl;
		ret = 1;
	} else if (k == 0.0) {
		//策划7.17修改：被攻击者无五行属性，受到伤害为攻击方五行数值/10
		//cout<<"BisonTest factor ret is 0.9"<<endl;
		ret = 0.0;
	} else {
		//根据五行抗性系数计算五行抗性
		int value = getValue();
		ret = k *(value) / (1 + k * (value));
		// ret = k *(value - 500) / (1 + k * (value - 500));
	}
	return ret;
}

/*****************************************************************
 * getHurt - 五行伤害计算，当前五行归属者作为攻击者
 * @k: 被攻击值的五行抗性
 * Return: 返回五行伤害值
 *****************************************************************/
int FiveElem::getHurt(double k)
{
	//主攻者的五行数值
	int value = getValue();
	//五行伤害
	//cout<<"k is "<<k<<endl;
	int ret = value * (1 - k);
	//cout<<"ret is "<<ret<<endl;
	return ret;
}

/*****************************************************************
 * addExp - 增加五行经验，外面判断比对象等级低25级的限制
 * @value: 增加的经验值
 * Return: 增加经验是否成功
 *****************************************************************/
bool FiveElem::addExp(int value)
{
	if (level >= 60)
	{
		//最高级的就不在加升级进度
		return false;
	}
	
	if (value > 4)
	{
		//五行丹一颗一颗的吃，最大的丹是加4点,因此不可能超过4点
		return false;
	}
	
	expNow += value;
	if (expNow >= expForNext)
	{
		
		expNow -= expForNext;
		//升一级
		upGrade();
		//这里估计还要向客户端发消息，通知客户端
		if (level >= 60)
		{
			//满级了，不再升级
			expNow = expForNext;
		}
		
	}
	
	return true;
}

//当前经验
int FiveElem::getExpNow()
{
	/* cout<<"________________________"<<endl;
	cout<<expNow<<endl; */
	return expNow;
}

//升到下一级需要的经验
int FiveElem::getExpForNext()
{
	/* cout<<expForNext<<endl; */
	return expForNext;
}