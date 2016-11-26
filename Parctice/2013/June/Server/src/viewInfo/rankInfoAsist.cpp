/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server排名数据管理类实现文件；

**************************************************/

#include "rankInfo.h"
#include "rankInfoAsist.h"
#include "my_memcached.h"
#include "my_mem_group.h"

RankInfo rankInfo;							//排名信息管理类；
extern MyMemGroup* mem_group;				// 缓存组
string myRankInfoMemKey="PMa3e3e108-1c2f-11e2-a3ce-14dae2222211";	//缓存的Key；


/******************************************
函数作用 获取排名信息，信息用string类型表示；
函数参数 _index 将要获取的信息类型下标；
  返回值 string 获取信息的具体值; 
*******************************************/
char* getRankInfo(int index)
{
	if(index >= 32 || index < 0)
		return NULL;
	else
		return rankInfo.gainRankInfo(index);

}

void rankAnalysis(void)
{
	rankInfo.analysis();
}

void saveRankLog(void)
{
	rankInfo.saveRankLog();
}
	
/**************************
函数作用 更新临时数据保存map；
  返回值 bool 获取信息成功; 
	调用 角色下线时调用；
***************************/
bool updateRankTempData(Hero* hero)
{
	if(NULL == hero)
		return false;
		
	return rankInfo.updateTempData(hero);
}


/**************************
函数作用 触发刷新排名信息；
  返回值 bool 成功是true,失败false; 
	调用 每天排名刷新时调用；
***************************/
void setRankInfoToLocal()
{
	rankInfo.setInfoToLocal();
	saveRankInfo2Mem();//保存到缓存；
}


/**************************
函数作用 开机读取排名信息；
	调用 开机时调用；
***************************/
bool rankInfoBootInit()
{
	if(NULL == mem_group)
		return false;
		
	int size=0;	
	int where = 0;
	MemRankInfo_T* myRankInfoMem=(MemRankInfo_T*)mem_group->get_data(myRankInfoMemKey,&size, &where, PUBLIC_MEMCACHED_INDEX);
	
	// cout<<"[XHM MSG] Get MemRankInfo_T size(rankInfoAsist.cpp):"<<size<<endl;
	
	if(!myRankInfoMem)
	{
		cout<<"------------------------------------------------------"<<endl;
		cout<<"get MemRankInfo error"<<endl;
		cout<<"------------------------------------------------------"<<endl;
		return false;
	}
	else
	{
		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->powerRankKey[index]))
				break;
			if(myRankInfoMem->powerRankInfo[index].grade > 200|| myRankInfoMem->powerRankInfo[index].grade <= 0)
				continue;	

			if(myRankInfoMem->powerRankInfo[index].party[0] != 'M' && myRankInfoMem->powerRankInfo[index].party[0]  != 'G'&& myRankInfoMem->powerRankInfo[index].party[0]  != 'X'&& myRankInfoMem->powerRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->powerRankInfo[index].party) != 1)
				continue;
				
			rankInfo.powerRank.insert(AddRankInfo(myRankInfoMem->powerRankKey[index],myRankInfoMem->powerRankInfo[index]));				
		}		

		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->levelRankKey[index]))
				break;
				
			if(myRankInfoMem->levelRankInfo[index].grade > 200 || myRankInfoMem->levelRankInfo[index].grade <= 0)
				continue;

			if(myRankInfoMem->levelRankInfo[index].party[0] != 'M' && myRankInfoMem->levelRankInfo[index].party[0]  != 'G'&& myRankInfoMem->levelRankInfo[index].party[0]  != 'X'&& myRankInfoMem->levelRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->levelRankInfo[index].party) != 1)
				continue;
				
			rankInfo.levelRank.insert(AddRankInfo(myRankInfoMem->levelRankKey[index],myRankInfoMem->levelRankInfo[index]));				
		}
		
		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->wealthRankKey[index]))
				break;
				
			if(myRankInfoMem->wealthRankInfo[index].grade > 200|| myRankInfoMem->wealthRankInfo[index].grade <= 0)	//等级大于100，数据异常；异常数据处理；还需其他处理；
				continue;
				
			if(myRankInfoMem->wealthRankInfo[index].party[0] != 'M' && myRankInfoMem->wealthRankInfo[index].party[0]  != 'G'&& myRankInfoMem->wealthRankInfo[index].party[0]  != 'X' && myRankInfoMem->wealthRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->wealthRankInfo[index].party) != 1)
				continue;
			
			rankInfo.wealthRank.insert(AddRankInfo(myRankInfoMem->wealthRankKey[index],myRankInfoMem->wealthRankInfo[index]));				
		}
		
		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->activityRankKey[index]))
				break;
				
			if(myRankInfoMem->activityRankInfo[index].grade > 200|| myRankInfoMem->activityRankInfo[index].grade <= 0)
				continue;

			if(myRankInfoMem->activityRankInfo[index].party[0] != 'M' && myRankInfoMem->activityRankInfo[index].party[0]  != 'G'&& myRankInfoMem->activityRankInfo[index].party[0]  != 'X'&& myRankInfoMem->activityRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->activityRankInfo[index].party) != 1)
				continue;
				
			rankInfo.activityRankInfo.insert(AddRankInfo(myRankInfoMem->activityRankKey[index],myRankInfoMem->activityRankInfo[index]));				
		}
		
		
		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->shamblesRankKey[index]))
				break;
				
			if(myRankInfoMem->shamblesRankInfo[index].grade > 200|| myRankInfoMem->shamblesRankInfo[index].grade <= 0)
				continue;

			if(myRankInfoMem->shamblesRankInfo[index].party[0] != 'M' && myRankInfoMem->shamblesRankInfo[index].party[0]  != 'G'&& myRankInfoMem->shamblesRankInfo[index].party[0]  != 'X'&& myRankInfoMem->shamblesRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->shamblesRankInfo[index].party) != 1)
				continue;
				
			rankInfo.shamblesRank.insert(AddRankInfo(myRankInfoMem->shamblesRankKey[index],myRankInfoMem->shamblesRankInfo[index]));				
		}
		
		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->prestigeRankKey[index]))
				break;
				
			if(myRankInfoMem->prestigeRankInfo[index].grade > 200 || myRankInfoMem->prestigeRankInfo[index].grade <= 0)
				continue;

			if(myRankInfoMem->prestigeRankInfo[index].party[0] != 'M' && myRankInfoMem->prestigeRankInfo[index].party[0]  != 'G'&& myRankInfoMem->prestigeRankInfo[index].party[0]  != 'X'&& myRankInfoMem->prestigeRankInfo[index].party[0]  != 'H' && strlen(myRankInfoMem->prestigeRankInfo[index].party) != 1)
				continue;
				
			rankInfo.prestigeRank.insert(AddRankInfo(myRankInfoMem->prestigeRankKey[index],myRankInfoMem->prestigeRankInfo[index]));				
		}

		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->petRankKey[index]))
				break;
				
			if(myRankInfoMem->petRankInfo[index].grade > 200 || myRankInfoMem->petRankInfo[index].grade <= 0)
				continue;
				
			rankInfo.petRank.insert(AddRankInfo(myRankInfoMem->petRankKey[index],myRankInfoMem->petRankInfo[index]));				
		}

		for(int index = 0; index < 40; index++)
		{
			if(!strlen(myRankInfoMem->rideRankKey[index]))
				break;
				
			if(myRankInfoMem->rideRankInfo[index].grade > 200 || myRankInfoMem->rideRankInfo[index].grade <= 0)
				continue;
				
			rankInfo.rideRank.insert(AddRankInfo(myRankInfoMem->rideRankKey[index],myRankInfoMem->rideRankInfo[index]));				
		}	
	}
	
	rankInfo.setInfoToLocal();			//把历史记录写入到内存；
}


/**************************
函数作用 存储排名信息；
	调用 存储时调用；
***************************/
bool saveRankInfo2Mem()
{
	if(NULL == mem_group)
		return false;
	
	mem_group->set_data(myRankInfoMemKey,(char*)&(rankInfo.myMemRankInfo),(int)(sizeof(rankInfo.myMemRankInfo)), PUBLIC_MEMCACHED_INDEX);	
}


/**************************
函数作用 获取战力值；
	调用 查看人物信息调用；
***************************/
unsigned long GetPowerValue(MemHero*memHero)
{
	if(NULL==memHero)
		return 0;

	unsigned long power=0;
	int tempValue=0;
	
	tempValue = memHero->basicHeroData.lifeUpperVal;			//生命值上限
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.lifeUpperVal value less than 0(rankInfoAsist.cpp)!"<<endl;
		tempValue=0;
	}
	power += LIFE_VALUE_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.magicUpperVal;			//魔法值上限
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.magicUpperVal value less than 0(rankInfoAsist.cpp)!"<<endl;
		tempValue=0;
	}
	power += MAGIC_VALUE_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.outattack;				//外功攻击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.outattack value less than 0(rankInfoAsist.cpp)!"<<endl;
		tempValue=0;	
	}		
	power += OUTER_ATTACK_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.inattack;				//内功攻击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.inattack value less than 0(rankInfoAsist.cpp)!"<<endl;	
		tempValue=0;	
	}		
	power += INTER_ATTACK_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.outdefense;				//外功防御
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.outdefense value less than 0(rankInfoAsist.cpp)!"<<endl;	
		tempValue=0;	
	}	
	power += OUTER_DEF_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.indefense;				 //内功防御
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.indefense value less than 0(rankInfoAsist.cpp)!"<<endl;			
		tempValue=0;	
	}	
	power += INTER_DEF_MODULUS*(tempValue);
	
	tempValue=memHero->basicHeroData.hited;					//命中
	if(tempValue < 0)
	{	
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.hited value less than 0(rankInfoAsist.cpp)!"<<endl;				
		tempValue=0;	
	}	
	power += HIT_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.crit;					//暴击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.crit value less than 0(rankInfoAsist.cpp)!"<<endl;		
		tempValue=0;	
	}	
	power += CRIT_MODULUS*(tempValue);
	
	tempValue=memHero->basicHeroData.dodge;					//闪避
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.dodge value less than 0(rankInfoAsist.cpp)!"<<endl;		
		tempValue=0;
	}	
	power += DUCK_MODULUS*(tempValue);
	
	tempValue = memHero->basicHeroData.tenacity;				//韧性
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.tenacity value less than 0(rankInfoAsist.cpp)!"<<endl;			
		tempValue=0;
	}	
	power += TOUGH_MODULUS*(tempValue);		
	
	cout<<"[XHM MSG] POWER SIZE<rankInfoAsist.cpp>:"<<power<<endl;
	
	return power;
}