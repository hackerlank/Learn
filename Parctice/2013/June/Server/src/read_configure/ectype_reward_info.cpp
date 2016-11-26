/****************************************************************
 * Filename: ectype_reward_info.cpp
 * 
 * Description: 副本奖励的信息的构造函数和奖励信息获取方法的定义
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include "ectype_reward_info.h"
#include<cstdlib>
#include<ctime>
using namespace std;

extern map<string,vector<string> > type_2_goodsList;

Ectype_Reward_Info::Ectype_Reward_Info(char *_ectypeId, int _heroSkill, int _petSkill, int _exp, int _money, int _silver, int useGold)
{
	strncpy(ectypeId, _ectypeId, sizeof ectypeId);
	exp = _exp;
	money = _money;
	silver = _silver;
	petSkillExp = _petSkill;
	heroSkillExp = _heroSkill;
	useGoldRateIndex = useGold;
}

void Ectype_Reward_Info::addOneRewardItem(char *typeId, int num, ...)
{
	EctypeRewardItem_T item;
	strncpy(item.typeId, typeId, sizeof item.typeId);
	
	int i = 0;
	double tempRate = 0.0;
	
	va_list ap;
	va_start (ap, num);
	for (; i < num; i++)
	{
		tempRate = va_arg (ap, double);
		item.vipRate[i] = tempRate;
	}
	va_end (ap);
	
	for (; i < (sizeof (item.vipRate) / sizeof (double)); i++)
	{
		item.vipRate[i] = tempRate;
	}
	
	rewardGoods.push_back(item);
}


void Ectype_Reward_Info::addOneReward(char *typeId, int num, double* rateList)
{
	EctypeRewardItem_T item;
	strncpy(item.typeId, typeId, sizeof item.typeId);
	
	int i = 0;
	double tempRate = 0.0;
	
	for (; i < num; i++)
	{
		tempRate = *rateList++;
		item.vipRate[i] = tempRate;
	}
	
	for (; i < (sizeof (item.vipRate) / sizeof (double)); i++)
	{
		item.vipRate[i] = tempRate;
	}
	
	rewardGoods.push_back(item);
}

void Ectype_Reward_Info::testData()
{
	cout<<"<EctypeReward id="<<ectypeId<<" goldRate="<<useGoldRateIndex<<" pelSkill="<<heroSkillExp<<" skill="<<petSkillExp<<" exp="<<exp<<" money="<<money<<" silver="<<silver<<"/>"<<endl;
	
	if (rewardGoods.size() == 0)
	{
		cout<<"[Warning]This EctypeReward have no goods reward item"<<endl;
	}
	vector<EctypeRewardItem_T>::iterator it_reward = rewardGoods.begin();
	for (;it_reward != rewardGoods.end(); it_reward++)
	{
		cout<<"<Item vip0Rate="<<(*it_reward).vipRate[0]<<" vip1Rate="<<(*it_reward).vipRate[1]<<" vip2Rate="<<(*it_reward).vipRate[2]<<" vip3Rate="<<(*it_reward).vipRate[3]<<" vip4Rate="<<(*it_reward).vipRate[4]<<" vip5Rate="<<(*it_reward).vipRate[5]<<" vip6Rate="<<(*it_reward).vipRate[6]<<" vip7Rate="<<(*it_reward).vipRate[7]<<" vip8Rate="<<(*it_reward).vipRate[8]<<" vip9Rate="<<(*it_reward).vipRate[9]<<" vip10Rate="<<(*it_reward).vipRate[10]<<" typeId="<<(*it_reward).typeId<<"/>"<<endl;
		cout<<"</EctypeReward>"<<endl;
	}
}

int Ectype_Reward_Info::getExp()
{
	return exp;
}

int Ectype_Reward_Info::getMoney()
{
	return money;
}

int Ectype_Reward_Info::getSilver()
{
	return silver;
}

int Ectype_Reward_Info::getPetSkillExp()
{
	return petSkillExp;
}

int Ectype_Reward_Info::getHeroSkillExp()
{
	return heroSkillExp;
}

int Ectype_Reward_Info::getDefendSilver(int missed)
{
	int realSilver = 0;
	if (strncmp(ectypeId, "008", 3))
	{
		cout<<"Only defend ectype can call this function"<<endl;
		return realSilver;
	}
	
	if(missed < 0)
	{
		cout<<"missing monsters num is not valid!"<<endl;
		return realSilver;
	}
	
	if (missed >= 5)
	{
		//大于5只不奖励银两
		realSilver = 0;
		
	} else {
		realSilver = silver - (missed - 1) * SILVER_DEC_STEP;
	}
	
	return realSilver;
}

int Ectype_Reward_Info::getUseGoldRateIndex()
{
	return useGoldRateIndex;
}


/************************************************************************
 * getOneGoods -- 从指定类型的物品id序列中随机得到一个
 * @type: 奖励物品的指定类型
 * @return: 随机奖励物品的id
 ************************************************************************/
char* Ectype_Reward_Info::getOneGoods(char* typeId)
{
	// string goodsId;					//返回的物品id
	vector<string> *idsTemp;		//奖励物品的某一序列,此处使用指针
	int size = 0;					//对应的某一奖励物品序列的总数
	
	map<string,vector<string> >::iterator iter;
	iter = type_2_goodsList.find(typeId);
	if (iter == type_2_goodsList.end())
	{
		//奖励库中没有此类型物品
		cout<<"No This kind of goods("<<typeId<<") in wellion's ectype_reward_goods.xml"<<endl;
		cout<<"No This kind of goods("<<typeId<<") in wellion's ectype_reward_goods.xml"<<endl;
		return NULL;
	}
	
	idsTemp = &(iter->second);
	size = idsTemp->size();
	////srand((unsigned)time(NULL));
	//随机产生一个不大于物品容器容量的正整数
	unsigned rand_value = rand() % size;

	return const_cast<char*>((*idsTemp)[rand_value].c_str());
	// return goodsId;
}

/************************************************************************
 * getGoods -- 根据副本难度获得副本奖励物品id
 * @vipClass: 玩家vip等级，如果花元宝刷新请传-1
 * @return: 返回副本奖励物品id
 ************************************************************************/
char* Ectype_Reward_Info::getGoods(int vipClass)
{
	if (rewardGoods.size() == 0)
	{
		cout<<"Read the config of ectypeReward goods error for no items and the ectypeId is "<<ectypeId<<endl;
		cout<<"[BisonShow] Please call me to testData"<<endl;
		return NULL;
	}
	
	unsigned rand_value = rand() % 10000;
	int size = rewardGoods.size();
	unsigned temp = 0;								//概率累加值
	for(int i = 0; i < size; i++)
	{
		EctypeRewardItem_T item;
		item = rewardGoods[i];
		double rate = 0.0;
		
		if (vipClass == -1)
		{
			rate = item.vipRate[useGoldRateIndex];
		} else
		{
			rate = item.vipRate[vipClass];
		}
		
		if (rand_value < (temp += (unsigned)((rate) * 100)))
		{
			return getOneGoods(item.typeId);
			//刷出三个骰子点数
			// vector<int> series = item.series;
			// int sum = series[rand() % series.size()];
			// cout<<"BisonTest : series size is "<<series.size()<<endl;
			// cout<<"BisonTest: now sum is "<<sum<<endl;
			// goodsId += rand3Num(sum);
			// break;
		}
	}
	cout<<"You will never see this when you get rewardGoods only if wellion's error conf(not 100%)"<<endl;
	// return goodsId;
	return NULL;
	
}

#if 0
/************************************************************************
 * getExp -- 根据副本难度获得副本奖励经验
 * @step: 副本难度等级
 * @return: 返回副本奖励经验值
 ************************************************************************/
int Ectype_Reward_Info::getExp(ECTYPE_CLASS_T step)
{
	int exp;
	switch (step)
	{
	case NORMAL_LEVEL:
		exp = Normal.exp;
		break;
	case MIDDLE_LEVEL:
		exp = Middle.exp;
		break;
	case HARD_LEVEL:
		exp = Hard.exp;
		break;
	default:
		cout<<"Ectype class value error!"<<endl;
		return -1;
	}
	
	return exp;
}

/************************************************************************
 * getMoney -- 根据副本难度获得副本奖励金钱
 * @step: 副本难度等级
 * @return: 返回副本奖励金钱值
 ************************************************************************/
int Ectype_Reward_Info::getMoney(ECTYPE_CLASS_T step)
{
	int money;
	switch (step)
	{
	case NORMAL_LEVEL:
		money = Normal.money;
		break;
	case MIDDLE_LEVEL:
		money = Middle.money;
		break;
	case HARD_LEVEL:
		money = Hard.money;
		break;
	default:
		cout<<"Ectype class value error!"<<endl;
		return -1;
	}
	
	return money;
}

/************************************************************************
 * getSilver -- 根据副本难度获得副本奖励银两
 * @step: 副本难度等级
 * @return: 返回副本奖励银两值
 ************************************************************************/
int Ectype_Reward_Info::getSilver(ECTYPE_CLASS_T step)
{
	int silver;
	switch (step)
	{
	case NORMAL_LEVEL:
		silver = Normal.silver;
		break;
	case MIDDLE_LEVEL:
		silver = Middle.silver;
		break;
	case HARD_LEVEL:
		silver = Hard.silver;
		break;
	default:
		cout<<"Ectype class value error!"<<endl;
		return -1;
	}
	
	return silver;
}

/************************************************************************
 * getDefendExp -- 获取塔防副本刷times波怪获得的经验奖励
 * @step: 副本难度等级
 * @times: 刷怪的波数
 * @return: 返回副本奖励经验值
 ************************************************************************/
int Ectype_Reward_Info::getDefendExp(ECTYPE_CLASS_T step, int times)
{
	int exp;
	
	if (strcmp(idNum, "008"))
	{
		cout<<"Only defend ectype can call this function"<<endl;
		return -1;
	}
	
	if (times < 0 || times > 10)
	{
		cout<<"brush monsters times value is error!"<<endl;
		return -1;
	}
	
//	if ((exp = getExp(step)) == -1)
//	{
		//副本难度参数传入有误
//		return -1;
//	}
	exp = TD_BASE_EXP + 50000 * step;
//modified on 6.29	
	
	exp += (times - 1) * EXP_INC_STEP;
	
	return exp;
}

/************************************************************************
 * getDefendMoney -- 获取塔防副本刷times波怪获得的金钱奖励
 * @step: 副本难度等级
 * @times: 刷怪的波数
 * @return: 返回副本奖励金钱值
 ************************************************************************/
int Ectype_Reward_Info::getDefendMoney(ECTYPE_CLASS_T step, int times)
{
	int money;
	
	if (strcmp(idNum, "008"))
	{
		cout<<"Only defend ectype can call this function"<<endl;
		return -1;
	}
	
	if(times < 0 || times > 10)
	{
		cout<<"brush monsters times value is error!"<<endl;
		return -1;
	}

//	if ((money = getMoney(step)) == -1)
//	{
		//副本难度参数传入值有误
//		return -1;
//	}
	money = TD_BASE_MONEY + 3000 * step;
//modified on 6.29	

	money += (times - 1) * MONEY_INC_STEP;
	
	return money;
}

/************************************************************************
 * getDefendSilver -- 获取塔防副本漏missed只怪获得的银两奖励
 * @step: 副本难度等级
 * @times: 刷怪的波数
 * @return: 返回副本奖励银两值
 ************************************************************************/
int Ectype_Reward_Info::getDefendSilver(ECTYPE_CLASS_T step, int missed)
{
	int silver;
	
	if (strcmp(idNum, "008"))
	{
		cout<<"Only defend ectype can call this function"<<endl;
		return -1;
	}
	
	if(missed < 0)
	{
		cout<<"missing monsters num is not valid!"<<endl;
		return -1;
	}
	
	if ((silver = getSilver(step)) == -1)
	{
		//副本难度参数传入值有误
		return -1;
	}
	
	if (missed >= 5)
	{
		//大于5只不奖励银两
		silver = 0;
		
	} else {
		silver -= (missed - 1) * SILVER_DEC_STEP;
	}
	
	return silver;
}

/************************************************************************
 * getOneGoods -- 从指定类型的物品id序列中随机得到一个
 * @type: 奖励物品的指定类型
 * @return: 随机奖励物品的id
 ************************************************************************/
char* Ectype_Reward_Info::getOneGoods(char* typeId)
{
	// string goodsId;					//返回的物品id
	vector<string> *idsTemp;		//奖励物品的某一序列,此处使用指针
	int size = 0;					//对应的某一奖励物品序列的总数
	
	map<string,vector<string> >::iterator iter;
	iter = type_2_goodsList.find(typeId);
	if (iter == type_2_goodsList.end())
	{
		//奖励库中没有此类型物品
		cout<<"没有此类型物品"<<endl;
		return NULL;
	}
	
	idsTemp = &(iter->second);
	size = idsTemp->size();
	////srand((unsigned)time(NULL));
	//随机产生一个不大于物品容器容量的正整数
	unsigned rand_value = rand() % size;

	return const_cast<char*>((*idsTemp)[rand_value].c_str());
	// return goodsId;
}

/************************************************************************
 * getGoods -- 根据副本难度获得副本奖励物品id
 * @step: 副本难度等级
 * @return: 返回副本奖励物品id
 ************************************************************************/
char* Ectype_Reward_Info::getGoods(ECTYPE_CLASS_T step, int flag)
{
	vector<EctypeRewardItem_T> *Reward;			//奖励物品的序列
	// string goodsId;								//奖励物品id返回
	
	switch (step)
	{
	case NORMAL_LEVEL:
		Reward = &(Normal.rewardGoods);
		break;
	case MIDDLE_LEVEL:
		Reward = &(Middle.rewardGoods);
		break;
	case HARD_LEVEL:
		Reward = &(Hard.rewardGoods);
		break;
	default:
		cout<<"Ectype class value error!"<<endl;
		return NULL;
	}
	
	unsigned rand_value = rand() % 10000;
	int size = Reward->size();
	unsigned temp = 0;								//概率累加值
	for(int i = 0; i < size; i++)
	{
		EctypeRewardItem_T item;
		item = (*Reward)[i];
		double rate = 0.0;
		
		if (flag == 1)
		{
			rate = item.vipRate;
		} else if (flag == 2)
		{
			rate = item.useGoldRate;
		} else {
			rate = item.freeRate;
		}
		
		if (rand_value < (temp += (unsigned)((rate) * 100)))
		{
			return getOneGoods(item.typeId);
			//刷出三个骰子点数
			// vector<int> series = item.series;
			// int sum = series[rand() % series.size()];
			// cout<<"BisonTest : series size is "<<series.size()<<endl;
			// cout<<"BisonTest: now sum is "<<sum<<endl;
			// goodsId += rand3Num(sum);
			// break;
		}
	}
	cout<<"You will never see this when you get rewardGoods only if wellion's error conf(not 100%)"<<endl;
	// return goodsId;
	
}
#endif