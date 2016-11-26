/****************************************************************
 * Filename: consume_reward.h
 * 
 * Description: 消费奖励
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/

#ifndef MY_CONSUME_REWARD_H_
#define MY_CONSUME_REWARD_H_

#include<map>
#include<string>

using namespace std;

class Consume_reward{
public:
	Consume_reward();
	~Consume_reward();
	
	bool send_reward(void);//奖励发送到邮件；
	bool init_consume_reward(void);//初始化消费数据；
	
	bool save_consume_reward_info(void);//保存消费数据；
	bool del_from_reward_team(char *myHeroId);//删除对象
	int add_to_reward_team(char *myHeroId,int size);//添加到奖励对象

public:
	bool isActivity;//是否在活动时间内；
	int min_consume_size;//最小值奖励的；
	map<string,int> consume_reward_heroId;//对象Id;
	
private:
	map<string,int>::iterator reward_iter;// 排序用的容器； 
	pair< map< string,int>::iterator,bool > reward_insert_ret;//用于insert的返回值，判断insert是否成功。
};
#endif