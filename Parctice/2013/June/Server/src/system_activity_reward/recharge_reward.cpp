/****************************************************************
 * Filename: recharge_reward.cpp
 * 
 * Description: 充值奖励实现文件
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/
#include "recharge_reward.h"

#include "hero.h"
#include "system_activity_reward_assist.h"
#include "mail_systerm_interface.h"

using namespace std;

extern map<string, Hero*> heroId_to_pHero;
extern Recharge_reward_obj_T recharge_reward;
extern Recharge_reward_time_T reward_time_conf;//时间配置文件；
extern Recharge_reward_detail_T reward_detail_conf;//奖励配置文件；
extern char sendName[30];
extern char sendTitle[30];
extern char recharge[1024];

Recharge_reward::Recharge_reward()
{
	isActivity=false;
}

Recharge_reward::~Recharge_reward()
{

}
	
bool
Recharge_reward::send_reward(void)
{
	if(recharge_reward_heroId.size() == 0){
		// cout<<"[XHM MSG] recharge_reward_heroId.size() == 0 ERROR<recharge_reward.cpp>"<<endl;	
		return false;	
	}

	int max_size=0;
	char max_size_heroId[HEROID_LENGTH]={0};
		
	Mail_Txt mail(sendName, sendTitle, recharge);//构建收件箱中的邮件数据
	mail.isRead = 1;//收件箱内未读
	
	char* uuid = cid();
	strcpy(mail.mail_id,uuid);//生成邮件的Id
	free(uuid);
	
	map<string, Hero*>::iterator recharge_iter;	
	Hero *hero_rec = NULL;
	int value_ret =-1;	
	
	reward_iter=recharge_reward_heroId.begin();
	for(;reward_iter!=recharge_reward_heroId.end();reward_iter++)
	{
		for(int row =reward_detail_conf.levelcounts-1;row >= 0; row--)
		{
			if(reward_detail_conf.levelSize[row] <= reward_iter->second)
			{
				memcpy(mail.good1_id,reward_detail_conf.reward_goods_id[row], 15);
				mail.good1_num = reward_detail_conf.reward_goods_num[row];			
				memcpy(mail.good2_id,reward_detail_conf.reward_goods_id2[row], 15);
				mail.good2_num = reward_detail_conf.reward_goods_num2[row];	
				mail.money = reward_detail_conf.bind_gold[row];					
				mail.gamegold = reward_detail_conf.bind_gold[row];	
				break;
			}
		}
		
		if(reward_iter->second > max_size)//计算出最大的值
		{
			max_size=reward_iter->second;
			memcpy(max_size_heroId,(reward_iter->first).c_str(),HEROID_LENGTH);
		}
		
		recharge_iter = heroId_to_pHero.find(reward_iter->first);		
		if(recharge_iter==heroId_to_pHero.end())
		{
			cout<<"[XHM MSG] hero_receive isn't online<recharge_reward.cpp>:"<<reward_iter->first<<endl;
			value_ret = MailSystermInterface::create_mail_data(reward_iter->first, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
			if(value_ret == -1)
			{
				cout<<"[XHM MSG] MailSystermInterface::create_mail_data ERROR<recharge_reward.cpp>:"<<reward_iter->first<<endl;
				continue;
			}
		}else{//收件玩家在线的邮件操作处理
			hero_rec = recharge_iter->second;
			hero_rec->memHero->cum_recharge_awards=0;//清除为零；
			cout<<"[XHM MSG] hero_receive is online<recharge_reward.cpp>:"<<reward_iter->first<<endl;
			value_ret = MailSystermInterface::add_mail_data(recharge_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
			if(value_ret == -1)	
			{	
				cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<recharge_reward.cpp>:"<<reward_iter->first<<endl;
				continue;
			}
	
		}

	}
	
	if(max_size)//给第一的玩家发送额外奖励；
	{
		if(strlen(max_size_heroId))
		{
			//如果此处段错误，配置错误，配置没有配置全服充值第一奖励物品奖励；
			memcpy(mail.good1_id,reward_detail_conf.reward_goods_id[reward_detail_conf.levelcounts], 15);
			mail.good1_num = reward_detail_conf.reward_goods_num[reward_detail_conf.levelcounts];			
			memset(mail.good2_id,0,sizeof(mail.good2_id));
			mail.good2_num = 0;	
			
			recharge_iter = heroId_to_pHero.find(max_size_heroId);		
			if(recharge_iter==heroId_to_pHero.end())//玩家不在线处理
			{	
				string heroId=max_size_heroId;
				value_ret = MailSystermInterface::create_mail_data(heroId, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
				if(value_ret == -1)
				{
					cout<<"[XHM MSG] create_mail_data == -1 ERROR<recharge_reward.cpp>:"<<reward_iter->first<<endl;
				}
			}else{//收件玩家在线的邮件操作处理
					hero_rec = recharge_iter->second;
					hero_rec->memHero->cum_recharge_awards=0;//清除为零；
					// cout<<"[XHM MSG] hero_receive is online<recharge_reward.cpp>:"<<reward_iter->first<<endl;
					value_ret = MailSystermInterface::add_mail_data(recharge_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
					if(value_ret == -1)	
					{	
						cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<recharge_reward.cpp>:"<<reward_iter->first<<endl;
					}
	
			}
		}	
	}
	
	
	isActivity=false;//TODO 测试完成后，发送完奖励后，清空数据
	recharge_reward_heroId.clear();
	map<string,int>().swap(recharge_reward_heroId);
	
	recharge_reward.init();
	save_rechargeInfo_to_mem();	
}


bool
Recharge_reward::init_recharge_reward(void)
{

}

bool
Recharge_reward::save_recharge_reward_info()
{
	if(recharge_reward_heroId.size() == 0)
		return false;
		
	int row=0;		
	recharge_reward.init();

	reward_iter=recharge_reward_heroId.begin();	//普通奖励生成；
	for(;reward_iter!=recharge_reward_heroId.end();row++,reward_iter++)//如果不存在；
	{	
		if(row < MAX_RECHARGE_HERO*8)
		{
			memcpy(recharge_reward.heroId[row],(reward_iter->first).c_str(),HEROID_LENGTH);
			recharge_reward.recharge_num[row]=reward_iter->second;
		}
	}
	
	save_rechargeInfo_to_mem();
	cout<<"[XHM TEST] save_recharge_reward_info size:"<<row<<endl;
	return true;
}

	
int
Recharge_reward::add_to_reward_team(char *myHeroId,int size)
{
	if(!isActivity)
	{
		cout<<"[XHM WARNING] isActivity=FALSE <recharge_reward.cpp>!"<<endl;		
		return 1;
	}
	
	if(myHeroId == NULL || size <= 0)
	{
		cout<<"[XHM WARNING] add_to_reward_team myHeroId == NULL || size <= 0 ERROR<recharge_reward.cpp>!"<<endl;
		return 2;
	}	
	reward_iter=recharge_reward_heroId.find(myHeroId);
	if(reward_iter == recharge_reward_heroId.end())//如果不存在；
	{
		cout<<"[XHM WARNING] min_recharge_size:"<<min_recharge_size<<endl;
		if(size >= min_recharge_size)
		{
			reward_insert_ret = recharge_reward_heroId.insert(map<string,int>::value_type(myHeroId,size));
			if(!reward_insert_ret.second)//插入失败
			{
				cout<<"[XHM WARNING] add_to_reward_team recharge_reward_heroId.insert ERROR<recharge_reward.cpp>!"<<endl;
				return 3;
			}
		}else{
			cout<<"[XHM WARNING] size < min_recharge_size ERROR<recharge_reward.cpp>!"<<endl;			
		}
	}else{//存在
		reward_iter->second=size;
	}
	
	cout<<"[XHM WARNING] add_to_reward_team to save_recharge_reward_info!"<<endl;
	//保存充值奖励数据；
	save_recharge_reward_info();
	return 0;
}

bool
Recharge_reward::del_from_reward_team(char *myHeroId)
{
	if(myHeroId == NULL)
	{
		cout<<"[XHM WARNING] del_from_reward_team myHeroId == NULL || size <= 0 ERROR<recharge_reward.cpp>!"<<endl;
		return false;
	}	
	
	reward_iter=recharge_reward_heroId.find(myHeroId);
	if(reward_iter == recharge_reward_heroId.end())//如果不存在；
	{
		cout<<"[XHM WARNING] del_from_reward_team reward_iter == recharge_reward_heroId.end() ERROR<recharge_reward.cpp>!"<<endl;
		return false;
	}else{
		recharge_reward_heroId.erase(reward_iter);
	}
}	
