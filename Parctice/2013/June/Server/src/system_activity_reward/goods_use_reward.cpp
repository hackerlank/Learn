/****************************************************************
 * Filename: goods_use_reward.cpp
 * 
 * Description: 物品使用奖励实现文件
 *
 * Original Author : xhm, 2013-02-02
 *
 ****************************************************************/
#include "goods_use_reward.h"

#include "hero.h"
#include "system_activity_reward_assist.h"
#include "mail_systerm_interface.h"

using namespace std;

extern Goods_oper_reward_T flowers_send_reward_detail;//送鲜花奖励
extern Goods_oper_reward_T flowers_gain_reward_detail;//得到鲜花奖励

extern Goods_oper_reward_obj_T flowers_send_reward_obj;
extern Goods_oper_reward_obj_T flowers_gain_reward_obj;

extern map<string, Hero*> heroId_to_pHero;
extern char sendName[30];
extern char sendTitle[30];
extern char sendFlower[1024];
extern char receiveFlower[1024];

Goods_use_reward::Goods_use_reward()
{
	isUseActivity=false;
	isGainActivity=false;	
}

Goods_use_reward::~Goods_use_reward()
{

}
	
bool
Goods_use_reward::send_use_reward()
{
	cout<<"goods_use_reward_heroId.size:"<<goods_use_reward_heroId.size()<<endl;

	Hero *hero_rec = NULL;		
		
	if(goods_use_reward_heroId.size() != 0){
		Mail_Txt mail(sendName, sendTitle, sendFlower);//构建收件箱中的邮件数据
		mail.isRead = 1;//收件箱内未读
	
		char* uuid = cid();
		strcpy(mail.mail_id,uuid);//生成邮件的Id
		free(uuid);
	
		map<string, Hero*>::iterator use_goods_iter;	

		int value_ret =-1;	
	
		reward_iter=goods_use_reward_heroId.begin();
		for(;reward_iter!=goods_use_reward_heroId.end();reward_iter++)
		{
			for(int row =2;row >= 0; row--)
			{
				if(flowers_send_reward_detail.goods_reward_obj[row].size <= reward_iter->second)
				{
					memcpy(mail.good1_id,flowers_send_reward_detail.goods_reward_obj[row].reward_goods_id,sizeof(mail.good1_id)-1);
					mail.good1_num = 1;//需求更改接口，奖励游戏币！
					// cout<<"[XHM MSG] ************mail.good1_id:"<<mail.good1_id<<endl;
					break;
				}
			}
			
			// cout<<"[XHM MSG] ************mail.good1_id:"<<mail.good1_id<<"reward_iter->second:"<<reward_iter->second<<endl;	
			use_goods_iter = heroId_to_pHero.find(reward_iter->first);		
			if(use_goods_iter==heroId_to_pHero.end())//不在线处理
			{
				cout<<"[XHM MSG] hero_receive isn't online<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
				value_ret = MailSystermInterface::create_mail_data(reward_iter->first, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
				if(value_ret == -1)
				{
					cout<<"[XHM MSG] MailSystermInterface::create_mail_data ERROR<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
					continue;
				}
			}else{//在线的邮件操作处理
				hero_rec = use_goods_iter->second;
				hero_rec->memHero->goods_use_size=0;//清除为零；
				// cout<<"[XHM MSG] hero_receive is online<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
				value_ret = MailSystermInterface::add_mail_data(use_goods_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
				if(value_ret == -1)	
				{	
					cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
					continue;
				}
	
			}

		}

		goods_use_reward_heroId.clear();
		map<string,int>().swap(goods_use_reward_heroId);
	
		flowers_send_reward_obj.clean_reward();
		save_goods_use_info_2_mem();	
	}
	
	isUseActivity=false;//TODO 测试完成后，发送完奖励后，清空数据	
}


bool Goods_use_reward::send_gain_reward()
{
	cout<<"goods_gain_reward_heroId.size:"<<goods_gain_reward_heroId.size()<<endl;

	Hero *hero_rec = NULL;	
	if(goods_gain_reward_heroId.size() != 0){
		Mail_Txt mail(sendName, sendTitle, receiveFlower);//构建收件箱中的邮件数据
		mail.isRead = 1;//收件箱内未读
	
		char* uuid = cid();
		strcpy(mail.mail_id,uuid);//生成邮件的Id
		free(uuid);
	
		map<string, Hero*>::iterator gain_goods_iter;	

		int value_ret =-1;	
	
		reward_iter=goods_gain_reward_heroId.begin();
		for(;reward_iter!=goods_gain_reward_heroId.end();reward_iter++)
		{
			for(int row =2;row >= 0; row--)
			{
				if(flowers_gain_reward_detail.goods_reward_obj[row].size <= reward_iter->second)
				{
					memcpy(mail.good1_id,flowers_gain_reward_detail.goods_reward_obj[row].reward_goods_id,sizeof(mail.good1_id)-1);
					mail.good1_num = 1;//需求更改接口，奖励游戏币！
					break;
				}
			}
			// cout<<"[XHM MSG] &&&&&&&&&&mail.good1_id:"<<mail.good1_id<<"reward_iter->second:"<<reward_iter->second<<endl;		
			gain_goods_iter = heroId_to_pHero.find(reward_iter->first);		
			if(gain_goods_iter==heroId_to_pHero.end())//不在线处理
			{
				// cout<<"[XHM MSG] hero_receive isn't online<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
				value_ret = MailSystermInterface::create_mail_data(reward_iter->first, 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
				if(value_ret == -1)
				{
					cout<<"[XHM MSG] MailSystermInterface::create_mail_data ERROR<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
					continue;
				}
			}else{//在线的邮件操作处理
				hero_rec = gain_goods_iter->second;
				hero_rec->memHero->goods_gain_size=0;//清除为零；
				// cout<<"[XHM MSG] hero_receive is online<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
				value_ret = MailSystermInterface::add_mail_data(gain_goods_iter->second, 0, (int)sizeof(mail), &mail);//tory modify 2012.12.30
				if(value_ret == -1)	
				{	
					cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<goods_use_reward.cpp>:"<<reward_iter->first<<endl;
					continue;
				}
	
			}

		}
		goods_gain_reward_heroId.clear();
		map<string,int>().swap(goods_gain_reward_heroId);
	
		flowers_gain_reward_obj.clean_reward();
		save_goods_gain_info_2_mem();	
	}

	isGainActivity=false;//TODO 测试完成后，发送完奖励后，清空数据
}


bool
Goods_use_reward::init_reward(void)
{
;
}

	
int
Goods_use_reward::add_goods_use_id_reward_team(char *myHeroId,int size)
{
	if(!isUseActivity)
	{
		cout<<"[XHM WARNING] isActivity=FALSE <goods_use_reward.cpp>!"<<endl;		
		return 1;
	}
	
	if(myHeroId == NULL || size <= 0)
	{
		cout<<"[XHM WARNING] add_goods_use_id_reward_team myHeroId == NULL || size <= 0 ERROR<goods_use_reward.cpp>!"<<endl;
		return 2;
	}	
	reward_iter=goods_use_reward_heroId.find(myHeroId);
	if(reward_iter == goods_use_reward_heroId.end())//如果不存在；
	{
		cout<<"[XHM WARNING] min_use_size:"<<min_use_size<<endl;
		if(size >= min_use_size)
		{
			reward_insert_ret = goods_use_reward_heroId.insert(map<string,int>::value_type(myHeroId,size));
			if(!reward_insert_ret.second)//插入失败
			{
				cout<<"[XHM WARNING] add_goods_use_id_reward_team goods_use_reward_heroId.insert ERROR<goods_use_reward.cpp>!"<<endl;
				return 3;
			}
		}else{
			cout<<"[XHM WARNING] size < min_recharge_size ERROR<goods_use_reward.cpp>!"<<endl;			
		}
	}else{//存在
		reward_iter->second=size;
	}
	
	cout<<"[XHM WARNING] add_goods_use_id_reward_team to save_recharge_reward_info!"<<endl;
	
	//保存赠送鲜花奖励数据；
	save_goods_use_reward_info();
	return 0;
}

int 
Goods_use_reward::add_goods_gain_id_reward_team(char *myHeroId,int size)
{
	if(!isGainActivity)
	{
		cout<<"[XHM WARNING] isActivity=FALSE <goods_use_reward.cpp>!"<<endl;		
		return 1;
	}
	
	if(myHeroId == NULL || size <= 0)
	{
		cout<<"[XHM WARNING] add_goods_gain_id_reward_team myHeroId == NULL || size <= 0 ERROR<goods_use_reward.cpp>!"<<endl;
		return 2;
	}	
	reward_iter=goods_gain_reward_heroId.find(myHeroId);
	if(reward_iter == goods_gain_reward_heroId.end())//如果不存在；
	{
		cout<<"[XHM WARNING] min_gain_size:"<<min_gain_size<<endl;
		if(size >= min_gain_size)
		{
			reward_insert_ret = goods_gain_reward_heroId.insert(map<string,int>::value_type(myHeroId,size));
			if(!reward_insert_ret.second)//插入失败
			{
				cout<<"[XHM WARNING] add_goods_gain_id_reward_team goods_gain_reward_heroId.insert ERROR<goods_use_reward.cpp>!"<<endl;
				return 3;
			}
		}else{
			cout<<"[XHM WARNING] size < min_recharge_size ERROR<goods_use_reward.cpp>!"<<endl;			
		}
	}else{//存在
		reward_iter->second=size;
	}
	
	cout<<"[XHM WARNING] add_goods_gain_id_reward_team to save_recharge_reward_info!"<<endl;
	
	//保存获得鲜花奖励数据；
	save_goods_gain_reward_info();
	return 0;
}

	
bool 
Goods_use_reward::save_goods_use_reward_info(void)
{
	if(goods_use_reward_heroId.size() == 0)
		return false;
		
	int row=0;		
	flowers_send_reward_obj.init();

	reward_iter=goods_use_reward_heroId.begin();	//普通奖励生成；
	for(;reward_iter!=goods_use_reward_heroId.end();row++,reward_iter++)//如果不存在；
	{	
		if(row < MAX_RECHARGE_HERO)
		{
			memcpy(flowers_send_reward_obj.reward_obj[row],(reward_iter->first).c_str(),HEROID_LENGTH);
			flowers_send_reward_obj.reward_obj_value[row]=reward_iter->second;
		}
	}
	
	save_goods_use_info_2_mem();
	cout<<"[XHM TEST] save_goods_use_info_2_mem size:"<<row<<endl;
	return true;
}
	
	
bool 
Goods_use_reward::save_goods_gain_reward_info(void)
{
	if(goods_gain_reward_heroId.size() == 0)
		return false;
		
	int row=0;		
	flowers_gain_reward_obj.init();

	reward_iter=goods_gain_reward_heroId.begin();	//普通奖励生成；
	for(;reward_iter!=goods_gain_reward_heroId.end();row++,reward_iter++)//如果不存在；
	{	
		if(row < MAX_RECHARGE_HERO)
		{
			memcpy(flowers_gain_reward_obj.reward_obj[row],(reward_iter->first).c_str(),HEROID_LENGTH);
			flowers_gain_reward_obj.reward_obj_value[row]=reward_iter->second;
		}
	}
	
	save_goods_gain_info_2_mem();
	cout<<"[XHM TEST] save_goods_gain_info_2_mem size:"<<row<<endl;
	return true;
}
	
	