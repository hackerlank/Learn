/****************************************************************
 * Filename: consume_reward.cpp
 * 
 * Description: 消费奖励实现文件
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/
 #include "consume_reward.h"
 
#include "hero.h"
#include "system_activity_reward_assist.h"
#include "mail_systerm_interface.h"

using namespace std;

extern map<string, Hero*> heroId_to_pHero;
extern Consume_reward_obj_T consume_reward;
extern Consume_reward_time_T consume_reward_time_conf;//时间配置文件；
extern Consume_reward_detail_T consume_reward_detail_conf;//奖励配置文件；
extern char sendName[30];
extern char sendTitle[30];
extern char consume[1024];

Consume_reward::Consume_reward()
{
	//初始化对象；
}

Consume_reward::~Consume_reward()
{
	//析构对象；
}
	
bool
Consume_reward::send_reward()
{
	if(consume_reward_heroId.size() == 0){
		// cout<<"[XHM MSG] consume_reward_heroId.size() == 0 ERROR<consume_reward.cpp>"<<endl;	
		return false;	
	}
	cout<<"the consume_reward_heroId.size:"<<consume_reward_heroId.size()<<endl;
	
	
	int max_size=0;
	char max_size_heroId[HEROID_LENGTH]={0};//最大值对象；

	Mail_Txt mail(sendName, sendTitle, consume);//构建收件箱中的邮件数据
	mail.isRead = 1;//收件箱内未读
	
	char* uuid = cid();
	strcpy(mail.mail_id,uuid);//生成邮件的Id
	free(uuid);
	
	map<string, Hero*>::iterator consume_iter;	
	Hero *hero_rec = NULL;
	int value_ret =-1;	
	
	reward_iter=consume_reward_heroId.begin();
	for(;reward_iter!=consume_reward_heroId.end();reward_iter++)
	{
		memset(mail.good1_id,0,sizeof(mail.good1_id));
		mail.good1_num=0;
		memset(mail.good2_id,0,sizeof(mail.good2_id));
		mail.good2_num=0;	
		mail.money = 0;					
		mail.gamegold = 0;			
		
		for(int row =consume_reward_detail_conf.levelcounts-1;row >= 0; row--)//生成奖励
		{
			if(consume_reward_detail_conf.levelSize[row] <= reward_iter->second)
			{
				memcpy(mail.good1_id,consume_reward_detail_conf.reward_goods_id[row], 15);
				mail.good1_num = consume_reward_detail_conf.reward_goods_num[row];			
				memcpy(mail.good2_id,consume_reward_detail_conf.reward_goods_id2[row], 15);
				mail.good2_num = consume_reward_detail_conf.reward_goods_num2[row];	
				mail.money = consume_reward_detail_conf.bind_gold[row];					
				mail.gamegold = consume_reward_detail_conf.bind_gold[row];	
				break;
			}
		}
		
		cout<<"[XHM MSG] mail.good1_id:"<<mail.good1_id<<endl;
		
		if(reward_iter->second > max_size)//计算出最大的值，额外奖励
		{
			max_size=reward_iter->second;
			memcpy(max_size_heroId,(reward_iter->first).c_str(),HEROID_LENGTH);
		}
		
		consume_iter = heroId_to_pHero.find(reward_iter->first);		
		if(consume_iter==heroId_to_pHero.end())//玩家不在线处理
		{
			// cout<<"[XHM MSG] hero_receive isn't online<consume_reward.cpp>:"<<reward_iter->first<<endl;
			value_ret = MailSystermInterface::create_mail_data(reward_iter->first, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
			if(value_ret == -1)
			{
				cout<<"[XHM MSG] MailSystermInterface::create_mail_data ERROR<consume_reward.cpp>:"<<reward_iter->first<<endl;
				continue;
			}
			
		}else{//收件玩家在线的邮件操作处理
			hero_rec = consume_iter->second;
			hero_rec->memHero->useGoldForActive=0;//清除为零；
			// cout<<"[XHM MSG] hero_receive is online<consume_reward.cpp>:"<<reward_iter->first<<endl;
			value_ret = MailSystermInterface::add_mail_data(consume_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
			if(value_ret == -1)	
			{	
				cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<consume_reward.cpp>:"<<reward_iter->first<<endl;
				continue;
			}
	
		}

	}
	
	if(max_size)//给第一的玩家发送额外奖励；
	{
		if(strlen(max_size_heroId))
		{
			memset(mail.good1_id,0,sizeof(mail.good1_id));
			mail.good1_num=0;
			memset(mail.good2_id,0,sizeof(mail.good2_id));
			mail.good2_num=0;	
			mail.money = 0;					
			mail.gamegold = 0;	
			
			//如果此处段错误，配置错误，配置没有配置全服消费第一奖励物品奖励；
			memcpy(mail.good1_id,consume_reward_detail_conf.reward_goods_id[consume_reward_detail_conf.levelcounts], 15);
			mail.good1_num = consume_reward_detail_conf.reward_goods_num[consume_reward_detail_conf.levelcounts];			
			memset(mail.good2_id,0,sizeof(mail.good2_id));
			mail.good2_num = 0;	
			
			consume_iter = heroId_to_pHero.find(max_size_heroId);		
			if(consume_iter==heroId_to_pHero.end())//玩家不在线处理
			{			
				string heroId=max_size_heroId;
				value_ret = MailSystermInterface::create_mail_data(heroId, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
				if(value_ret == -1)
				{
					cout<<"[XHM MSG] create_mail_data == -1 ERROR<consume_reward.cpp>"<<endl;
				}
			}else{//收件玩家在线的邮件操作处理
					hero_rec = consume_iter->second;
					// cout<<"[XHM MSG] hero_receive is online<consume_reward.cpp>:"<<reward_iter->first<<endl;
					value_ret = MailSystermInterface::add_mail_data(consume_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
					if(value_ret == -1)	
					{	
						cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<consume_reward.cpp>:"<<reward_iter->first<<endl;
					}
	
			}
			
			cout<<"[XHM MSG] max_size_heroId mail.good1_id:"<<mail.good1_id<<endl;
		}
		
	}
	
	isActivity=false;  //TODO发送完奖励后，清空数据
	consume_reward_heroId.clear();
	map<string,int>().swap(consume_reward_heroId);
	
	consume_reward.init();
	save_consumeInfo_to_mem();	
}


bool
Consume_reward::init_consume_reward(void)
{

}

bool
Consume_reward::save_consume_reward_info()
{
	if(consume_reward_heroId.size() == 0)
		return false;
		
	consume_reward.init();
	int row=0;

	reward_iter=consume_reward_heroId.begin();//普通奖励生成；
	for(;reward_iter!=consume_reward_heroId.end();row++,reward_iter++)//如果不存在；
	{	
		if(row < MAX_RECHARGE_HERO*8)
		{
			memcpy(consume_reward.heroId[row],(reward_iter->first).c_str(),HEROID_LENGTH);
			consume_reward.consume_num[row]=reward_iter->second;
		}
	}
	
	save_consumeInfo_to_mem();
	cout<<"[XHM TEST] save_consume_reward_info size:"<<row<<endl;
	return true;
}

	
int
Consume_reward::add_to_reward_team(char *myHeroId,int size)
{
	if(!isActivity)
	{
		cout<<"[XHM WARNING] isActivity=FALSE <consume_reward.cpp>!"<<endl;		
		return 1;
	}
	
	cout<<"add_to_reward_team the size:"<<size<<endl;
	
	if(myHeroId == NULL || size <= 0)
	{
		cout<<"[XHM WARNING] add_to_reward_team myHeroId == NULL || size <= 0 ERROR<consume_reward.cpp>!"<<endl;
		return 2;
	}	
	reward_iter=consume_reward_heroId.find(myHeroId);
	if(reward_iter == consume_reward_heroId.end())//如果不存在；
	{
		if(size >= min_consume_size)
		{
			reward_insert_ret = consume_reward_heroId.insert(map<string,int>::value_type(myHeroId,size));
			if(!reward_insert_ret.second)//插入失败
			{
				cout<<"[XHM WARNING] add_to_reward_team consume_reward_heroId.insert ERROR<consume_reward.cpp>!"<<endl;
				return 3;
			}
		}else{
			cout<<"[XHM WARNING] size < min_consume_size ERROR<consume_reward.cpp>!"<<endl;			
		}
	}else{//存在
		reward_iter->second=size;
	}
	
	save_consume_reward_info();//保存充值奖励数据；
	return 0;
}


bool
Consume_reward::del_from_reward_team(char *myHeroId)
{
	if(myHeroId == NULL)
	{
		cout<<"[XHM WARNING] del_from_reward_team myHeroId == NULL <consume_reward.cpp>!"<<endl;
		return false;
	}	
	
	reward_iter=consume_reward_heroId.find(myHeroId);
	if(reward_iter == consume_reward_heroId.end())//如果不存在；
	{
		cout<<"[XHM WARNING] del_from_reward_team reward_iter == consume_reward_heroId.end() ERROR<consume_reward.cpp>!"<<endl;
		return false;
	}else{
		consume_reward_heroId.erase(reward_iter);
	}
}	
