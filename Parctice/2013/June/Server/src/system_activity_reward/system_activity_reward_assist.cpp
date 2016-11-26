#include "system_activity_reward_assist.h"

#include<sys/time.h>
#include "my_timer.h"
#include "my_memcached.h"
#include "recharge_reward.h"
#include "consume_reward.h"
#include "goods_use_reward.h"

//缓存服务器管理类
#include "my_mem_group.h"
extern MyMemGroup* mem_group;
// extern MyMemcache* mem_operate;//缓存操作类实例指针，全局变量

Recharge_reward *recharge_reward_asist;
Consume_reward *consume_reward_asist;
Goods_use_reward* goods_use_reward_asist;

/**充值奖励*/
Recharge_reward_time_T reward_time_conf;//时间配置文件；
Recharge_reward_detail_T reward_detail_conf;//奖励配置文件；
Recharge_reward_obj_T recharge_reward;//充值奖励详细信息

/**消费奖励*/
Consume_reward_time_T consume_reward_time_conf;//时间配置文件；
Consume_reward_detail_T consume_reward_detail_conf;//奖励配置文件；
Consume_reward_obj_T consume_reward;

/**送鲜花奖励*/
Goods_oper_reward_T flowers_send_reward_detail;//送鲜花奖励
Goods_oper_reward_obj_T flowers_send_reward_obj;

/**获得鲜花奖励*/
Goods_oper_reward_T flowers_gain_reward_detail;//得到鲜花奖励
Goods_oper_reward_obj_T flowers_gain_reward_obj;

static const char *rechargeInfo_key="rechargeInfo_key";
static const char *consumeInfo_key="consumeInfo_key";
static const char *goods_use_reward_key="goods_use_reward_key";
static const char *goods_gain_reward_key="goods_gain_reward_key";
static struct timeval my_time;

/**
*判断是否是累积充值奖励时间；
*/
bool isNowRechargeReward(long sec)
{
	if(!recharge_reward_asist->isActivity)
		return false;

	struct tm* lastTm = localtime(&sec);

	//这里只判断当前月的奖励，如果奖励的时间跨月份，需要修改代码；
	if(reward_time_conf.year == lastTm->tm_year+1900 && reward_time_conf.month == lastTm->tm_mon+1 &&\
				(reward_time_conf.end_day >= lastTm->tm_mday && reward_time_conf.start_day <= lastTm->tm_mday ))
	{
		return true;
	} else {
		return false;
	}
}

bool init_rechargeInfo_reward(void)
{
	if(recharge_reward_asist==NULL)
	{
		recharge_reward_asist = new Recharge_reward();
		if(recharge_reward_asist == NULL)
			return false;
	}

	if(!read_rechargeInfo_from_mem())
	{
		cout<<"[XHM WARNING] init_rechargeInfo_reward read_rechargeInfo_from_mem ERROR<recharge_reward_assist.cpp>!"<<endl;
		return false;
	}
	
	gettimeofday(&my_time, NULL);
	struct tm* timeNow = localtime(&my_time.tv_sec);	
	/*
	cout<<endl<<endl<<"[XHM MSG] reward_time_conf.year:"<<reward_time_conf.year<<endl;	
	cout<<"[XHM MSG] reward_time_conf.month:"<<reward_time_conf.month<<endl;	
	cout<<"[XHM MSG] reward_time_conf.start_day:"<<reward_time_conf.start_day<<endl;	
	cout<<"[XHM MSG] reward_time_conf.end_day:"<<reward_time_conf.end_day<<endl<<endl;
	
	cout<<"[XHM TEST] curr year:"<<timeNow->tm_year+1900<<endl;	
	cout<<"[XHM TEST] curr month:"<<timeNow->tm_mon+1<<endl;	
	cout<<"[XHM TEST] curr day:"<<timeNow->tm_mday<<endl<<endl;
	*/
	if(reward_time_conf.year == timeNow->tm_year+1900 && reward_time_conf.month == timeNow->tm_mon+1 &&\
					reward_time_conf.end_day >= timeNow->tm_mday && reward_time_conf.start_day <= timeNow->tm_mday )
	{
		recharge_reward_asist->isActivity=true;

	}else{
		cout<<"[XHM WARNING] NOT ACIVITY TIME<recharge_reward_assist.cpp>!"<<endl;		
		recharge_reward_asist->send_reward();//发送一次奖励；
		recharge_reward_asist->isActivity=false;
		return false;
	}
	
	
	//初始化时间
	if(recharge_reward.recharge_reward_time.year==0 && recharge_reward.recharge_reward_time.month==0 &&\
		recharge_reward.recharge_reward_time.start_day==0 && recharge_reward.recharge_reward_time.end_day==0)
	{
		recharge_reward.recharge_reward_time.year=reward_time_conf.year;
		recharge_reward.recharge_reward_time.month=reward_time_conf.month;
		recharge_reward.recharge_reward_time.start_day=reward_time_conf.start_day;
		recharge_reward.recharge_reward_time.end_day=reward_time_conf.end_day;	
	}else if(reward_time_conf.year >= recharge_reward.recharge_reward_time.year ||
		reward_time_conf.month  >= recharge_reward.recharge_reward_time.month||
		reward_time_conf.start_day >= recharge_reward.recharge_reward_time.start_day ||
		reward_time_conf.end_day >= recharge_reward.recharge_reward_time.end_day)
	{
		recharge_reward.recharge_reward_time.year=reward_time_conf.year;
		recharge_reward.recharge_reward_time.month=reward_time_conf.month;
		recharge_reward.recharge_reward_time.start_day=reward_time_conf.start_day;
		recharge_reward.recharge_reward_time.end_day=reward_time_conf.end_day;	
		recharge_reward_asist->send_reward();//发送一次奖励；
	}else{
		cout<<"[XHM WARNING] NOT ACIVITY TIME<recharge_reward_assist.cpp>!"<<endl;	
		recharge_reward_asist->isActivity=false;
		recharge_reward_asist->send_reward();//发送一次奖励；
		return false;	
	}
	
	
	if(!isNowRechargeReward(time(NULL)))
	{
		cout<<"[XHM WARNING] !isNowRechargeReward<recharge_reward_assist.cpp>!"<<endl;	
		recharge_reward_asist->isActivity=false;
		recharge_reward_asist->send_reward();//发送一次奖励；		
		return false;
	}
	
	//给最小值赋初值；
	recharge_reward_asist->isActivity=true;	
	recharge_reward_asist->min_recharge_size=reward_detail_conf.levelSize[0];
	
	if(recharge_reward_asist->isActivity)
	{	
 	cout<<endl<<endl<<"[XHM MSG] reward_time_conf.year:"<<reward_time_conf.year<<endl;	
	cout<<"[XHM MSG] reward_time_conf.month:"<<reward_time_conf.month<<endl;	
	cout<<"[XHM MSG] reward_time_conf.start_day:"<<reward_time_conf.start_day<<endl;	
	cout<<"[XHM MSG] reward_time_conf.end_day:"<<reward_time_conf.end_day<<endl<<endl<<endl;
	}
/*
	for(int row=0;row < reward_detail_conf.levelcounts;row++)
	{
		cout<<"[XHM MSG] reward_detail_conf.reward_goods_id:"<<reward_detail_conf.reward_goods_id[row]<<" reward_detail_conf.reward_goods_num:"<<reward_detail_conf.reward_goods_num[row]<<endl;		
		cout<<"[XHM MSG] reward_detail_conf.reward_goods_id:"<<reward_detail_conf.reward_goods_id2[row]<<" reward_detail_conf.reward_goods_num:"<<reward_detail_conf.reward_goods_num2[row]<<endl;		
		cout<<"[XHM MSG] reward_detail_conf.levelSize:"<<reward_detail_conf.levelSize[row]<<" reward_detail_conf.bind_gold:"<<reward_detail_conf.bind_gold[row]<<endl;
	}
	cout<<endl<<endl;
	*/
}
	
bool save_rechargeInfo_to_mem()
{
	// if(NULL == mem_operate)
		// return false;
		
	// bool isSuccess = mem_operate->set_mem_data(rechargeInfo_key,(char*)&(recharge_reward),(int)(sizeof(recharge_reward)));
	bool isSuccess = mem_group->set_data(rechargeInfo_key,(char*)&(recharge_reward),(int)(sizeof(recharge_reward)),PUBLIC_MEMCACHED_INDEX);
	if(!isSuccess)
	{
		cout<<"[XHM WARNING] save_rechargeInfo_to_mem mem_group->set_data ERROR<recharge_reward_assist.cpp>!"<<endl;
		return false;
	}	
}

bool read_rechargeInfo_from_mem()
{
	// if(NULL == mem_operate)
		// return false;
					
	int size=0;	
	int where=0;	
	// Recharge_reward_obj_T* recharge_reward_obj=(Recharge_reward_obj_T*)mem_operate->get_mem_data(rechargeInfo_key,&size);
	Recharge_reward_obj_T* recharge_reward_obj=(Recharge_reward_obj_T*)mem_group->get_data(rechargeInfo_key,&size,&where,PUBLIC_MEMCACHED_INDEX);
	
	// cout<<"[XHM MSG] Get Recharge_reward_objId_T size(recharge_reward_assist.cpp):"<<size<<endl;
	
	if(!recharge_reward_obj)
	{
		recharge_reward.init();
		save_rechargeInfo_to_mem();
		cout<<"[XHM WARNING] Gain the Recharge_reward_obj_T at function read_rechargeInfo_from_mem(recharge_reward_assist.cpp),The pointer is NULL!"<<endl;
		return false;
	}else{
		recharge_reward.recharge_reward_time.year=recharge_reward_obj->recharge_reward_time.year;
		recharge_reward.recharge_reward_time.month=recharge_reward_obj->recharge_reward_time.month;
		recharge_reward.recharge_reward_time.start_day=recharge_reward_obj->recharge_reward_time.start_day;
		recharge_reward.recharge_reward_time.end_day=recharge_reward_obj->recharge_reward_time.end_day;
	
		for(int index = 0; index < MAX_RECHARGE_HERO*8; index++)
		{
			if(!strlen(recharge_reward_obj->heroId[index]))
				break;
				
			if(recharge_reward_obj->recharge_num < 0)
				break;
			
			if(recharge_reward_asist == NULL)
				break;
			//添加到管理器对应的容器里面；	
			(recharge_reward_asist->recharge_reward_heroId).insert(map<string,int>::value_type(recharge_reward_obj->heroId[index],recharge_reward_obj->recharge_num[index]));
		}
	
	}
	free((char *)recharge_reward_obj);
	
	return true;
}


//消费累积奖励
/**
*判断是否是累积充值奖励时间；
*/
bool isNowConsumeReward(long sec)
{
	if(!consume_reward_asist->isActivity)
		return false;

	struct tm* lastTm = localtime(&sec);

	if(consume_reward_time_conf.year == lastTm->tm_year+1900 && consume_reward_time_conf.month == lastTm->tm_mon+1 &&\
				consume_reward_time_conf.end_day >= lastTm->tm_mday && consume_reward_time_conf.start_day <= lastTm->tm_mday )
	{
		return true;
	} else {
		return false;
	}
}


bool init_consumeInfo_reward()
{
	if(consume_reward_asist==NULL)
	{
		consume_reward_asist = new Consume_reward();
		if(consume_reward_asist == NULL)
			return false;
	}

	if(!read_consumeInfo_from_mem())
	{
		cout<<"[XHM WARNING] init_consumeInfo_reward read_consumeInfo_from_mem ERROR<recharge_reward_assist.cpp>!"<<endl;
		return false;
	}
	
	gettimeofday(&my_time, NULL);
	struct tm* timeNow = localtime(&my_time.tv_sec);	
	/*
	cout<<"[XHM TEST] curr year:"<<timeNow->tm_year+1900<<endl;	
	cout<<"[XHM TEST] curr month:"<<timeNow->tm_mon+1<<endl;	
	cout<<"[XHM TEST] curr day:"<<timeNow->tm_mday<<endl<<endl;
	
	cout<<endl<<endl<<"[XHM MSG] consume_reward_time_conf.year:"<<consume_reward_time_conf.year<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.month:"<<consume_reward_time_conf.month<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.start_day:"<<consume_reward_time_conf.start_day<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.end_day:"<<consume_reward_time_conf.end_day<<endl<<endl<<endl;	
	*/
	
	if(consume_reward_time_conf.year == timeNow->tm_year+1900 && consume_reward_time_conf.month == timeNow->tm_mon+1 &&\
				consume_reward_time_conf.end_day >= timeNow->tm_mday && consume_reward_time_conf.start_day <= timeNow->tm_mday )
	{
		consume_reward_asist->isActivity=true;
	}else{
		cout<<"[XHM WARNING] NOT ACIVITY TIME<recharge_reward_assist.cpp>!"<<endl;	
		consume_reward_asist->send_reward();//发送一次奖励；
		consume_reward_asist->isActivity=false;
		return false;	
	}
	
	//初始化时间
	if(consume_reward.consume_reward_time.year==0 && consume_reward.consume_reward_time.month==0 &&\
		consume_reward.consume_reward_time.start_day==0 && consume_reward.consume_reward_time.end_day==0)
	{
		consume_reward.consume_reward_time.year=consume_reward_time_conf.year;
		consume_reward.consume_reward_time.month=consume_reward_time_conf.month;
		consume_reward.consume_reward_time.start_day=consume_reward_time_conf.start_day;
		consume_reward.consume_reward_time.end_day=consume_reward_time_conf.end_day;	
	}else if(consume_reward_time_conf.year >= consume_reward.consume_reward_time.year ||
		consume_reward_time_conf.month  >= consume_reward.consume_reward_time.month||
		consume_reward_time_conf.start_day >= consume_reward.consume_reward_time.start_day ||
		consume_reward_time_conf.end_day >= consume_reward.consume_reward_time.end_day)
	{
		consume_reward.consume_reward_time.year=consume_reward_time_conf.year;
		consume_reward.consume_reward_time.month=consume_reward_time_conf.month;
		consume_reward.consume_reward_time.start_day=consume_reward_time_conf.start_day;
		consume_reward.consume_reward_time.end_day=consume_reward_time_conf.end_day;
		consume_reward_asist->send_reward();//发送一次奖励；		
	}else{
		cout<<"[XHM WARNING] NOT ACIVITY TIME<recharge_reward_assist.cpp>!"<<endl;	
		consume_reward_asist->isActivity=false;
		consume_reward_asist->send_reward();//发送一次奖励；
		return false;	
	}
	
	if(!isNowConsumeReward(time(NULL)))
	{
		cout<<"[XHM WARNING] !isNowConsumeReward<recharge_reward_assist.cpp>!"<<endl;	
		consume_reward_asist->isActivity=false;
		consume_reward_asist->send_reward();//发送一次奖励；
		return false;
	}
	
	//给最小值赋初值；
	consume_reward_asist->isActivity=true;

	consume_reward_asist->min_consume_size=consume_reward_detail_conf.levelSize[0];
	
	if(consume_reward_asist->isActivity)
	{
	cout<<endl<<endl<<"[XHM MSG] consume_reward_time_conf.year:"<<consume_reward_time_conf.year<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.month:"<<consume_reward_time_conf.month<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.start_day:"<<consume_reward_time_conf.start_day<<endl;	
	cout<<"[XHM MSG] consume_reward_time_conf.end_day:"<<consume_reward_time_conf.end_day<<endl<<endl<<endl;	
	}
	
	// for(int row=0;row <= consume_reward_detail_conf.levelcounts;row++)
	// {
		// cout<<"[XHM MSG] consume_reward_detail_conf.reward_goods_id:"<<consume_reward_detail_conf.reward_goods_id[row]<<" consume_reward_detail_conf.reward_goods_num:"<<consume_reward_detail_conf.reward_goods_num[row]<<endl;		
		// cout<<"[XHM MSG] consume_reward_detail_conf.reward_goods_id:"<<consume_reward_detail_conf.reward_goods_id2[row]<<" consume_reward_detail_conf.reward_goods_num:"<<consume_reward_detail_conf.reward_goods_num2[row]<<endl;		
		// cout<<"[XHM MSG] consume_reward_detail_conf.levelSize:"<<consume_reward_detail_conf.levelSize[row]<<" consume_reward_detail_conf.bind_gold:"<<consume_reward_detail_conf.bind_gold[row]<<endl;
	// }
	// cout<<endl<<endl;
}

	
bool save_consumeInfo_to_mem()
{
	// if(NULL == mem_operate)
		// return false;
		
	// bool isSuccess = mem_operate->set_mem_data(consumeInfo_key,(char*)&(consume_reward),(int)(sizeof(consume_reward)));
	bool isSuccess = mem_group->set_data(consumeInfo_key,(char*)&(consume_reward),(int)(sizeof(consume_reward)),PUBLIC_MEMCACHED_INDEX);
	if(!isSuccess)
	{
		// cout<<"[XHM WARNING] save_consumeInfo_to_mem mem_group->set_data ERROR<recharge_reward_assist.cpp>!"<<endl;
		return false;
	}	
}

bool read_consumeInfo_from_mem()
{
	// if(NULL == mem_operate)
		// return false;
					
	int size=0;	
	int where=0;	
	// Consume_reward_obj_T* consume_reward_obj=(Consume_reward_obj_T*)mem_operate->get_mem_data(consumeInfo_key,&size);
	Consume_reward_obj_T* consume_reward_obj=(Consume_reward_obj_T*)mem_group->get_data(consumeInfo_key,&size,&where,PUBLIC_MEMCACHED_INDEX);
	
	if(!consume_reward_obj)
	{
		consume_reward.init();
		save_consumeInfo_to_mem();
		cout<<"[XHM WARNING] Gain the Consume_reward_obj_T at function read_rechargeInfo_from_mem(recharge_reward_assist.cpp),The pointer is NULL!"<<endl;
		return false;
	}else{
		consume_reward.consume_reward_time.year=consume_reward_obj->consume_reward_time.year;
		consume_reward.consume_reward_time.month=consume_reward_obj->consume_reward_time.month;
		consume_reward.consume_reward_time.start_day=consume_reward_obj->consume_reward_time.start_day;
		consume_reward.consume_reward_time.end_day=consume_reward_obj->consume_reward_time.end_day;
	
		for(int index = 0; index < MAX_RECHARGE_HERO*8; index++)
		{
			if(!strlen(consume_reward_obj->heroId[index]))
				break;
				
			if(consume_reward_obj->consume_num < 0)
				break;
			
			if(recharge_reward_asist == NULL)
				break;
			//添加到管理器对应的容器里面；	
			(consume_reward_asist->consume_reward_heroId).insert(map<string,int>::value_type(consume_reward_obj->heroId[index],consume_reward_obj->consume_num[index]));
		}
	
	}
	free((char *)consume_reward_obj);
	
	return true;
}

//送鲜花，获得鲜花奖励
bool isNowGoodsUseReward(long second)
{
	if(!goods_use_reward_asist->isUseActivity)
		return false;

	struct tm* lastTm = localtime(&second);

	if(flowers_send_reward_detail.year == lastTm->tm_year+1900 && flowers_send_reward_detail.month == lastTm->tm_mon+1 &&\
				flowers_send_reward_detail.end_day >= lastTm->tm_mday && flowers_send_reward_detail.start_day <= lastTm->tm_mday )
	{
		return true;
	} else {
		return false;
	}
}


//送鲜花，获得鲜花奖励
bool isNowGoodsGainReward(long second)
{
	if(!goods_use_reward_asist->isGainActivity)
		return false;

	struct tm* lastTm = localtime(&second);

	if(flowers_gain_reward_detail.year == lastTm->tm_year+1900 && flowers_gain_reward_detail.month == lastTm->tm_mon+1 &&\
				flowers_gain_reward_detail.end_day >= lastTm->tm_mday && flowers_gain_reward_detail.start_day <= lastTm->tm_mday )
	{
		return true;
	} else {
		return false;
	}
}
bool init_goods_opr_reward(void)
{
	if(goods_use_reward_asist==NULL)
	{
		goods_use_reward_asist = new Goods_use_reward();
		if(goods_use_reward_asist == NULL)
			return false;
	}
	
	gettimeofday(&my_time, NULL);
	struct tm* timeNow = localtime(&my_time.tv_sec);
			
	if(read_goods_use_info_from_mem())
	{
		goods_use_reward_asist->isUseActivity=true;
		
		if(!isNowGoodsUseReward(time(NULL)))
		{
			cout<<"[XHM WARNING] ######!isNowGoodsUseReward<system_activity_reward_assist.cpp>!"<<endl;	
			goods_use_reward_asist->isUseActivity=false;
			goods_use_reward_asist->send_use_reward();//发送一次奖励；
			return false;
		}
		
		if(flowers_send_reward_detail.year != flowers_send_reward_obj.year ||
			flowers_send_reward_detail.month  != flowers_send_reward_obj.month||
			flowers_send_reward_detail.start_day != flowers_send_reward_obj.start_day ||
			flowers_send_reward_detail.end_day != flowers_send_reward_obj.end_day)
		{
			flowers_send_reward_obj.year=consume_reward_time_conf.year;
			flowers_send_reward_obj.month=consume_reward_time_conf.month;
			flowers_send_reward_obj.start_day=consume_reward_time_conf.start_day;
			flowers_send_reward_obj.end_day=consume_reward_time_conf.end_day;
			goods_use_reward_asist->send_use_reward();//发送一次奖励；		
		}
	
		//给最小值赋初值；
		goods_use_reward_asist->isUseActivity=true;

		goods_use_reward_asist->min_use_size=flowers_send_reward_detail.goods_reward_obj[0].size;
		
	}
	
	if(read_goods_gain_info_from_mem())
	{

		goods_use_reward_asist->isGainActivity=true;
		
		if(!isNowGoodsGainReward(time(NULL)))
		{
			cout<<"[XHM WARNING] !isNowGoodsGainReward<system_activity_reward_assist.cpp>!"<<endl;	
			goods_use_reward_asist->isGainActivity=false;
			goods_use_reward_asist->send_gain_reward();//发送一次奖励；
			return false;
		}
		
		if(flowers_gain_reward_detail.year != flowers_gain_reward_obj.year ||
			flowers_gain_reward_detail.month  != flowers_gain_reward_obj.month||
			flowers_gain_reward_detail.start_day != flowers_gain_reward_obj.start_day ||
			flowers_gain_reward_detail.end_day != flowers_gain_reward_obj.end_day)
		{
			flowers_gain_reward_obj.year=consume_reward_time_conf.year;
			flowers_gain_reward_obj.month=consume_reward_time_conf.month;
			flowers_gain_reward_obj.start_day=consume_reward_time_conf.start_day;
			flowers_gain_reward_obj.end_day=consume_reward_time_conf.end_day;
			goods_use_reward_asist->send_use_reward();//发送一次奖励；		
		}
		
		//给最小值赋初值；
		goods_use_reward_asist->isGainActivity=true;

		goods_use_reward_asist->min_gain_size=flowers_gain_reward_detail.goods_reward_obj[0].size;	
	}

}
	
bool save_goods_use_info_2_mem()
{
	// if(NULL == mem_operate)
		// return false;
		
	// bool isSuccess = mem_operate->set_mem_data(goods_use_reward_key,(char*)&(flowers_send_reward_obj),(int)(sizeof(flowers_send_reward_obj)));
	bool isSuccess = mem_group->set_data(goods_use_reward_key,(char*)&(flowers_send_reward_obj),(int)(sizeof(flowers_send_reward_obj)),PUBLIC_MEMCACHED_INDEX);
	if(!isSuccess)
	{
		cout<<"[XHM WARNING] save_goods_use_info_2_mem mem_operate->set_mem_data ERROR<system_activity_reward_assist.cpp>!"<<endl;
		return false;
	}	
}

bool save_goods_gain_info_2_mem()
{
	// if(NULL == mem_operate)
		// return false;
		
	// bool isSuccess = mem_operate->set_mem_data(goods_gain_reward_key,(char*)&(flowers_gain_reward_obj),(int)(sizeof(flowers_gain_reward_obj)));
	bool isSuccess = mem_group->set_data(goods_gain_reward_key,(char*)&(flowers_gain_reward_obj),(int)(sizeof(flowers_gain_reward_obj)),PUBLIC_MEMCACHED_INDEX);
	
	if(!isSuccess)
	{
		cout<<"[XHM WARNING] save_goods_gain_info_2_mem mem_group->set_data ERROR<system_activity_reward_assist.cpp>!"<<endl;
		return false;
	}	

}

bool read_goods_use_info_from_mem(void)
{
	// if(NULL == mem_operate)
		// return false;
					
	int size=0;	
	int where=0;	
	// Goods_oper_reward_obj_T* goods_use_reward_obj=(Goods_oper_reward_obj_T*)mem_operate->get_mem_data(goods_use_reward_key,&size);
	Goods_oper_reward_obj_T* goods_use_reward_obj=(Goods_oper_reward_obj_T*)mem_group->get_data(goods_use_reward_key,&size,&where,PUBLIC_MEMCACHED_INDEX);
	
	if(!goods_use_reward_obj)
	{
		flowers_send_reward_obj.init();
		save_goods_use_info_2_mem();
		cout<<"[XHM WARNING] Gain the Consume_reward_obj_T at function read_goods_use_info_from_mem(system_activity_reward_assist.cpp),The pointer is NULL!"<<endl;
		return false;
	}else{
		for(int index = 0; index < MAX_RECHARGE_HERO; index++)
		{
			if(!strlen(goods_use_reward_obj->reward_obj[index]))
				break;
				
			if(goods_use_reward_obj->reward_obj_value < 0)
				continue;
			
			if(goods_use_reward_asist == NULL)
				break;
			//添加到管理器对应的容器里面；	
			(goods_use_reward_asist->goods_use_reward_heroId).insert(map<string,int>::value_type(goods_use_reward_obj->reward_obj[index],goods_use_reward_obj->reward_obj_value[index]));
		}
	
	}
	free((char *)goods_use_reward_obj);
	
	return true;
}

bool read_goods_gain_info_from_mem(void)
{
	// if(NULL == mem_operate)
		// return false;
					
	int size=0;	
	int where=0;	
	// Goods_oper_reward_obj_T* goods_gain_reward_obj=(Goods_oper_reward_obj_T*)mem_operate->get_mem_data(goods_gain_reward_key,&size);
	Goods_oper_reward_obj_T* goods_gain_reward_obj=(Goods_oper_reward_obj_T*)mem_group->get_data(goods_gain_reward_key,&size,&where,PUBLIC_MEMCACHED_INDEX);

	if(!goods_gain_reward_obj)
	{
		flowers_send_reward_obj.init();
		save_goods_gain_info_2_mem();
		cout<<"[XHM WARNING] Gain the Consume_reward_obj_T at function read_goods_use_info_from_mem(system_activity_reward_assist.cpp),The pointer is NULL!"<<endl;
		return false;
	}else{
		for(int index = 0; index < MAX_RECHARGE_HERO; index++)
		{
			if(!strlen(goods_gain_reward_obj->reward_obj[index]))
				break;
				
			if(goods_gain_reward_obj->reward_obj_value < 0)
				continue;
			
			if(goods_use_reward_asist == NULL)
				break;
				
			//添加到管理器对应的容器里面；	
			(goods_use_reward_asist->goods_gain_reward_heroId).insert(map<string,int>::value_type(goods_gain_reward_obj->reward_obj[index],goods_gain_reward_obj->reward_obj_value[index]));
		}
	
	}
	free((char *)goods_gain_reward_obj);
	
	return true;
}