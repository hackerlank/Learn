#include <iostream>
#include <stdlib.h>
#include "mailSysterm.h"
//离线未处理事件
#include "offline_unhandle_event.h"
#include "money_operator.h"
using namespace std;
/** 邮件数据存放路径 added by Tory**/
extern string mail_data_url_T;

extern int g_msg_len;
extern Hero* pg_hero;
extern char g_out_buf[20480];

MailSysterm::MailSysterm()
{
	new_mail = 0;		//tory add 2013.1.7
}

bool MailSysterm::load_mail_infor(Mail_Infor& mail_i)	//将单个邮件加载到MailSysterm对象中管理
{
 	Mail_Infor* m_i = (Mail_Infor*)malloc(sizeof(Mail_Infor));	//在MailSysterm析构函数中free掉
	if(m_i == NULL)	return false;
	memmove(m_i, &mail_i, sizeof(Mail_Infor));
	
	string key = m_i->identity;
	//根据Mail_Infor中的data_type决定邮件的存储类型（0：收到的邮件 1：发送的邮件 2：下线消息处理）
 	if(m_i->data_type == 0)
	{
		mail_Inbox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Inbox.size():"<<mail_Inbox.size()<<endl;
	}else if(m_i->data_type == 1)
	{
		mail_Outbox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Outbox.size():"<<mail_Outbox.size()<<endl;
	}else
	{
		mail_Unhandlebox.insert(map<string, Mail_Infor*>::value_type(key, m_i));
		cout<<"@@Tory MailSysterm::mail_Unhandlebox.size():"<<mail_Unhandlebox.size()<<endl;
	}
	
	Mail_Txt* m_t = (Mail_Txt*)m_i->data;		//tory modify 2013.1.7
	if(m_t->isRead == 1)		//isRead 0:收件箱邮件已读，1：收件箱邮件未读
	{
		new_mail += 1;
	}
	return true;
}

MailSysterm::~MailSysterm()		//角色下线时，将角色对应的邮件数据释放掉
{
	cout<<"~MailSysterm start"<<endl;
	map<string, Mail_Infor*>::iterator iter_i = mail_Inbox.begin();	//收件箱
	for(iter_i; iter_i != mail_Inbox.end(); iter_i++)
	{
		Mail_Infor* m_i = iter_i->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Inbox "<<endl;
	
	map<string, Mail_Infor*>::iterator iter_o = mail_Outbox.begin();	//发件箱
	for(iter_o; iter_o != mail_Outbox.end(); iter_o++)
	{
		Mail_Infor* m_i = iter_o->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Outbox "<<endl;
	
	map<string, Mail_Infor*>::iterator iter_u = mail_Unhandlebox.begin();	//下线时受到的消息
	for(iter_u; iter_u != mail_Unhandlebox.end(); iter_u++)
	{
		Mail_Infor* m_i = iter_u->second;
		if(m_i != NULL)	;
		{
			free(m_i);
		}
	}
	cout<<"free mail_Unhandlebox "<<endl;
	cout<<"~MailSysterm end"<<endl;
}

void MailSysterm::mail_handle(string heroId)		//处理邮件数据
{
 	map<string, Mail_Infor*>::iterator iter = mail_Unhandlebox.begin();	//下线未处理消息
	for(iter; iter != mail_Unhandlebox.end(); iter++)
	{
		Mail_Infor* mail_infor = iter->second;
		//由data_type决定邮件数据的处理方式,处理函数写在mail_systerm_handle.h中
		cout<<"mail_infor->data_type:"<<mail_infor->data_type<<endl;
		switch(mail_infor->data_type)			
		{
			case 2:
					printf("in parse_mail_data, case 0:%s\n", mail_infor->data);
					break;
			case 3:
					break;
		
			case 5:	
					deal_unhandle_attr_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 6: 
					deal_unhandle_goods_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 7: 
					deal_unhandle_msg_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
					
			case 8: 
					deal_unhandle_join_guild_event(const_cast<char*>(heroId.c_str()), mail_infor->data);
					break;
			case 9:	
					// printf("in parse_mail_data, case 9\n");			//好友申请 主类型9
					deal_unhandle_friend_apply_event(heroId, mail_infor->data);
					break;
			case 10:	
					// printf("in parse_mail_data, case 10\n");		//好友删除 主类型10
					deal_unhandle_del_friend_event(heroId,mail_infor->data);			
					break;
			case 11:	
					// printf("in parse_mail_data, case 11\n");		//好友添加 主类型11
					deal_unhandle_add_friend_event(heroId,mail_infor->data);	
					break;			
			default:
					break;

		}
	} 

}

bool time_compare(const Mail_Infor *first, const Mail_Infor *second)
{
	if(first->mail_time > second->mail_time)
		 return true; 
	else 
		return false;
}

bool MailSysterm::get_mail_list(Hero* myHero, int type)	
{
	if(myHero == NULL)	return false;
	//获取收件箱列表信息 //17,0
	if(type == 0)	
	{
		list<Mail_Infor*> inbox_list;
	 	map<string, Mail_Infor*>::iterator iter = mail_Inbox.begin();	//收件箱
		for(iter; iter != mail_Inbox.end(); iter++)
		{
			inbox_list.push_back(iter->second);
		}
		//对邮件列表按时间先后顺序排序(时间值由大到小)，自定义排序函数compare
		inbox_list.sort(time_compare);
		
		int mail_number = inbox_list.size();
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 0, type, mail_number);
		
		int index = 0;
		list<Mail_Infor*>::iterator iter_l = inbox_list.begin();
		for(iter_l; iter_l != inbox_list.end(), index < mail_number; iter_l++, index++)
		{
			Mail_Infor* m_i = *iter_l;
			if(m_i == NULL)	return false;
			
			Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
		//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));		//邮件文本数据
		//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
			
			time_t seconds =  m_i->mail_time;//邮件的生成时间
			struct tm *tmp = localtime(&seconds);	
			char time_temp[50] = {0}; 
			sprintf(time_temp, "%02d-%02d",tmp->tm_mon + 1,tmp->tm_mday);			//将邮件时间转换为字符串型
			
			sprintf(g_out_buf+strlen(g_out_buf), ",%d,%s,%s,%s,%d,%s", index, m_i->identity, mail_text->nickName, time_temp, mail_text->isRead, mail_text->theme);
		//	free(mail_text);
		}
		cout<<"@@Tory get_mail_list:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}else if(type == 1)
	{
		list<Mail_Infor*> outbox_list;
	 	map<string, Mail_Infor*>::iterator iter = mail_Outbox.begin();	//发件箱
		for(iter; iter != mail_Outbox.end(); iter++)
		{
			outbox_list.push_back(iter->second);
		}
		//对邮件列表按时间先后顺序排序(时间值由大到小)，自定义排序函数compare
		outbox_list.sort(time_compare);
		
		int mail_number = outbox_list.size();
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 0, type, mail_number);
		
		int index = 0;
		list<Mail_Infor*>::iterator iter_l = outbox_list.begin();
		for(iter_l; iter_l != outbox_list.end(), index < mail_number; iter_l++, index++)
		{
			Mail_Infor* m_i = *iter_l;
			if(m_i == NULL)	return false;
			
			Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
		//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));		//邮件文本数据
		//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
			
			time_t seconds =  m_i->mail_time;//邮件的生成时间
			struct tm *tmp = localtime(&seconds);	
			char time_temp[50] = {0}; 
			sprintf(time_temp, "%02d-%02d",tmp->tm_mon + 1,tmp->tm_mday);			//将邮件时间转换为字符串型
			
			sprintf(g_out_buf+strlen(g_out_buf), ",%d,%s,%s,%s,%d,%s", index, m_i->identity, mail_text->nickName, time_temp, mail_text->isRead, mail_text->theme);
		//	free(mail_text);
		}
		cout<<"@@Tory get_mail_list:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}
}

bool MailSysterm::get_mail_content(Hero* myHero, int type, string mail_id)	
{
	if(myHero == NULL)	return false;
	//获取收件箱列表信息 //17,1
	if(type == 0)	
	{//收件箱邮件
		map<string, Mail_Infor*>::iterator iter = mail_Inbox.find(mail_id);
		if(iter == mail_Inbox.end())	return false;	
		
		Mail_Infor* m_i = iter->second;
		if(m_i == NULL)	return false;
			
		Mail_Txt* mail_text = (Mail_Txt*)m_i->data;	//tory modify 2012.12.29
	//	Mail_Txt* mail_text = (Mail_Txt*)malloc(sizeof(Mail_Txt));
	//	memmove(mail_text, m_i->data, sizeof(Mail_Txt));
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 1, type, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%s,%d,%d,%s,%d,%s,%d,%s,%d,%s,%d", m_i->identity,mail_text->nickName,mail_text->theme,\
												mail_text->content,\
												mail_text->money,mail_text->gamegold,\
												mail_text->good1_id, mail_text->good1_num,\
												mail_text->good2_id, mail_text->good2_num,\
												mail_text->good3_id, mail_text->good3_num,\
												mail_text->good4_id, mail_text->good4_num);
		
		mail_text->isRead = 0;		//改为已阅读
	//	free(mail_text);
		cout<<"@@Tory get_mail_content:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}else if(type == 1)
	{
		map<string, Mail_Infor*>::iterator iter = mail_Outbox.find(mail_id);
		if(iter == mail_Outbox.end())	return false;	
		
		Mail_Infor* m_i = iter->second;
		if(m_i == NULL)	return false;
			
		Mail_Txt* mail_text = (Mail_Txt*)m_i->data;		//tory modify 2012.12.29
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 1, type, 1);
		sprintf(g_out_buf+strlen(g_out_buf),",%s,%s,%s,%s,%d,%d,%s,%d,%s,%d,%s,%d,%s,%d", m_i->identity,mail_text->nickName,mail_text->theme,\
												mail_text->content,\
												mail_text->money,mail_text->gamegold,\
												mail_text->good1_id, mail_text->good1_num,\
												mail_text->good2_id, mail_text->good2_num,\
												mail_text->good3_id, mail_text->good3_num,\
												mail_text->good4_id, mail_text->good4_num);
		
		mail_text->isRead = 0;		//改为已阅读
		cout<<"@@Tory get_mail_content:"<<g_out_buf<<endl;
		send_msg(myHero->getFd(), g_out_buf);
		return true;
	}
}
	
bool MailSysterm::delet_mail_infor(int type, string mail_id)//删除邮件内容
{

}


bool MailSysterm::save_mail_data(string heroId)	//角色下线时，保存邮件数据
{
	string mail_data_url = mail_data_url_T;
	mail_data_url += "//"+heroId;
	mail_data_url += ".bin";
	cout<<"mail_data_url:"<<mail_data_url<<endl;

	FILE *out;
	// if((out = fopen(mail_data_url.c_str(), "wb")) == NULL){
	if((out = fopen(mail_data_url.c_str(), "ab+")) == NULL){	//以追加模式打开邮件文件，防止中途系统给用户发的邮件被覆盖
		fprintf(stderr, "fopen file %s to append write error!\n", mail_data_url.c_str());
		return -1;
	}

	map<string, Mail_Infor*>::iterator iter_i = mail_Inbox.begin();	//收件箱
	for(iter_i; iter_i != mail_Inbox.end(); iter_i++)
	{
		Mail_Infor* m_i = iter_i->second;
		if(m_i == NULL)	continue;
		
		//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
		if(fwrite((void*)m_i, sizeof(Mail_Infor), 1, out) != 1)
		{
			fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
			return false;	
		}
	}
	
	map<string, Mail_Infor*>::iterator iter_o = mail_Outbox.begin();	//发件箱
	for(iter_o; iter_o != mail_Outbox.end(); iter_o++)
	{
		Mail_Infor* m_i = iter_o->second;
		if(m_i == NULL)	continue;
		
		//size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
		if(fwrite((void*)m_i, sizeof(Mail_Infor), 1, out) != 1)
		{
			fprintf(stderr, "fwrite data to mail_data error!\n", mail_data_url.c_str());
			return false;	
		}
	}	
	
	if(fclose(out) != 0)
	{
		fprintf(stderr, "fclose file %s error!\n", mail_data_url.c_str());
		return false;
	} 
	return true;

}

/* 
* author: tory
* date: 2012.12.29
* describe:返回邮件系统中，收/发件箱的邮件数目
*/
bool MailSysterm::getMailListNum(Hero* myHero)
{
	if(myHero == NULL)	return false;
	
	int in_num = mail_Inbox.size();
	int out_num = mail_Outbox.size();
	
	memset(g_out_buf, 0, 20480);	
	sprintf(g_out_buf, "%d,%d,%d,%d,%d", 17, 4, in_num, out_num, new_mail);
	cout<<"@@Tory: getMailListNum:"<<g_out_buf<<endl;
	send_msg(myHero->getFd(), g_out_buf);

	return true;	
}

/* 
* author: tory
* date: 2012.12.29
* describe:领取邮件中的物品
*/
bool MailSysterm::mail_goods_receive(Hero* myHero, string mail_id)
{
	if(myHero == NULL)	return false;
	map<string, Mail_Infor*>::iterator iter = mail_Inbox.find(mail_id);
	if(iter == mail_Inbox.end())	return false;	
		
	Mail_Infor* m_i = iter->second;
	if(m_i == NULL)	return false;
			
	Mail_Txt* m_t = (Mail_Txt*)m_i->data;		//tory modify 2012.12.29
	
	if(mail_id.compare(m_i->identity) != 0)
	{
		cout<<"mail_goods_receivep：the mail id is not same"<<endl;
		return false;
	}

	int all_number = m_t->good1_num + m_t->good2_num + m_t->good3_num + m_t->good4_num;
	
	//jolly add 1.25  for bagfull
	int count=0;
	if (m_t->good1_num!=0)
	{
		count++;
	}
	if (m_t->good2_num!=0)
	{
		count++;
	}
	if (m_t->good3_num!=0)
	{
		count++;
	}
	if (m_t->good4_num!=0)
	{
		count++;
	}
	
	if(myHero->getBag()->bagIsFull(count))
	{//背包内格子数不够
		cout<<"mail_goods_receivep：the bag is not null"<<endl;
		return false;
	} 
	
	//将物品将在到背包内
	if(m_t->good1_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good1_id, m_t->good1_num);	
		strncpy(m_t->good1_id, "0", 15);
		m_t->good1_num = 0;
	}
	if(m_t->good2_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good2_id, m_t->good2_num);	
		strncpy(m_t->good2_id, "0", 15);
		m_t->good2_num = 0;
	}
	if(m_t->good3_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good3_id, m_t->good3_num);	
		strncpy(m_t->good3_id, "0", 15);
		m_t->good3_num = 0;
	}
	if(m_t->good4_num > 0)
	{
		saveGoodsInBag(myHero, m_t->good4_id, m_t->good4_num);	
		strncpy(m_t->good4_id, "0", 15);
		m_t->good4_num = 0;
	}	
	
	//将游戏币与非绑定元宝加载到背包内
	increaseGameMoney(myHero, m_t->money);
	m_t->money = 0;
	
	increaseGold(myHero, m_t->gamegold);	
	m_t->gamegold = 0;
	
	int index = 0;
	memset(g_out_buf, 0, 20480);	
	sprintf(g_out_buf, "17,6,1,%d,%s", index, mail_id.c_str());
	cout<<"@@Tory, mail_goods_receive:"<<g_out_buf<<endl;
	send_msg(myHero->getFd(), g_out_buf);
}