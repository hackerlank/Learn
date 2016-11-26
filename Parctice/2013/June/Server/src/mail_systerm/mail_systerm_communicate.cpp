/*
* Filename: mail_systerm_communicate.cpp
* Authof:	Tory
* Date:		2012.9.17 
* Description: 用于客户端发邮件、收邮件、删邮件的功能
*/
#include <stdio.h>
#include <map>
#include <arpa/inet.h>

//所有工具函数的头文件
#include"command_other_function_all_over.h"
//交互处理返回的宏定义头文件
#include "command_return_define_data.h"
//邮件系统接口头文件
#include "mail_systerm_interface.h"
//邮件系统交互处理头文件
#include "mail_systerm_communicate.h"
//角色类的头文件
#include "hero.h"

#include "mailSysterm.h"

#include"command_game_fight_manage.h"

#include "money_operator.h"
//引用全局变量声明，Hero ID索引Hero对象指针的map容器，管理所有已初始化的Hero对象
extern map<string, Hero*> heroId_to_pHero;

extern map<string, MailSysterm*> mail_map;	//tory add 

extern Hero* pg_hero;

#include "wholeDefine.h"

/*
* author: evan
* date: 2012.9.25
* amend: tory 2012.12.29
* describe:发送邮件（处理客户端的18,2命令）,如果收件人不在在线，则调用MailSystermInterface::create_mail_data直接
           向收件人的外部文件写入数据；如果收件人在线，则调用MailSystermInterface::add_mail_data,将新邮件加载至game_server
		   进程的内存中，同时将新邮件数据写入.bak的外部文件，防止服务器意外断开
*/
void MailSystermCommunicate::send_mail(char* buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *heroId_send)			 //邮件的发件人Id
	MSG_CHAR(char *nickname_send)		 //邮件的发件人昵称
	MSG_CHAR(char *nickname_receive)	 //收件人的昵称
	cout<<"@@Tory nickname_receive:"<<nickname_receive<<endl;
	
	MSG_CHAR(char *title_email)			 //邮件的标题
	cout<<"@@Tory title_email:"<<title_email<<endl;
	
	MSG_CHAR(char *money_email)			 //附件内的金钱数
	cout<<"@@Tory money_email:"<<money_email<<endl;
	
	MSG_CHAR(char *gamegold_email)		 //附件内的非绑定元宝数
	cout<<"@@Tory gamegold_email:"<<gamegold_email<<endl;
	
	MSG_CHAR(char *goods_num)			 //附件内的物品类型数目
	cout<<"@@Tory goods_num:"<<goods_num<<endl;
	
	MSG_CHAR(char *good1_bag_num)		 //第一件物品在背包内的索引值
	MSG_CHAR(char *good1_id_email)		 //附件内的第一件物品Id
	MSG_CHAR(char *good1_num_email)		 //附件内的第一件物品数量
	MSG_CHAR(char *good2_bag_num)		 //第二件物品在背包内的索引值
	MSG_CHAR(char *good2_id_email)		 //附件内的第二件物品Id
	MSG_CHAR(char *good2_num_email)		 //附件内的第二件物品数量
	MSG_CHAR(char *good3_bag_num)		 //第三件物品在背包内的索引值
	MSG_CHAR(char *good3_id_email)		 //附件内的第三件物品Id
	MSG_CHAR(char *good3_num_email)		 //附件内的第三件物品数量
	MSG_CHAR(char *good4_bag_num)		 //第四件物品在背包内的索引值
	MSG_CHAR(char *good4_id_email)		 //附件内的第四件物品Id
	MSG_CHAR(char *good4_num_email)		 //附件内的第四件物品数量

	// MSG_CHAR(char *content_email)		 //邮件的内容
	MSG_CHAR_U(char *content_email);
	cout<<"@@Tory content_email:"<<content_email<<endl; 
	
	
	/*add chenzhen 20130312,自己不能给自己发送邮件*/
	if(strncmp(nickname_send,nickname_receive,strlen(nickname_send)) == 0)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 4);
		send_msg(pg_hero->getFd(), g_out_buf);
		return;
	}
	
	Hero* hero_send = pg_hero;		//发件人的实例指针
	
	//通过好友系统，以昵称为搜索条件获取收件人的heroId
	string heroId_receive = hero_send->getFriendInfo()->NickNameFindFriendId(nickname_receive);
	
	hero_send->getFriendInfo()->printFrients();
	
	//不在好有列表，收件人ID获取错误，邮件发送失败，错误编号：2
	if(heroId_receive.size() == 0)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 2);
		send_msg(pg_hero->getFd(), g_out_buf);
		return;
	}
	
#if 0	
	string acceptNickName = nickname_receive;
	//add chenzhen 20130312,请加区号
	if(acceptNickName.find("[") == string::npos)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 5);
		send_msg(pg_hero->getFd(), g_out_buf);
		return;
	}
#endif	
	
	

	/* 检查发送的游戏币和元宝数目是否正常 */
	if(hero_send->getMoney() == NULL)
	{
		return ;	//数据错误，不做响应
	}
	long gameMoney = hero_send->getMoney()->money_getGameMoney();
	long gold = hero_send->getMoney()->money_getGold();
	if(atoi(money_email) > gameMoney || atoi(gamegold_email) > gold)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 0);	//金钱不够
		send_msg(pg_hero->getFd(), g_out_buf);
		return;
	}
	/*判断发件人附件中的物品，在背包内是否存在且数量充足,条件满足的话，以下变量的值都变为1，否则为0*/
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int num4 = 0;
	if(hero_send->getBag()->test(atoi(good1_bag_num),good1_id_email) && hero_send->getBag()->getGridNum(atoi(good1_bag_num))>=atoi(good1_num_email))
	{
		num1 = 1;
		cout<<"index1:"<<good1_bag_num<<" num1:"<<hero_send->getBag()->getGridNum(atoi(good4_bag_num))<<endl;	
	}
	if(hero_send->getBag()->test(atoi(good2_bag_num),good2_id_email) && hero_send->getBag()->getGridNum(atoi(good2_bag_num))>=atoi(good2_num_email))
	{
		num2 = 1;
		cout<<"index2:"<<good2_bag_num<<" num2:"<<hero_send->getBag()->getGridNum(atoi(good4_bag_num))<<endl;
	}
	if(hero_send->getBag()->test(atoi(good3_bag_num),good3_id_email) && hero_send->getBag()->getGridNum(atoi(good3_bag_num))>=atoi(good3_num_email))
	{
		num3 = 1;
		cout<<"index3:"<<good3_bag_num<<" num3:"<<hero_send->getBag()->getGridNum(atoi(good4_bag_num))<<endl;
	}
	if(hero_send->getBag()->test(atoi(good4_bag_num),good4_id_email) && hero_send->getBag()->getGridNum(atoi(good4_bag_num))>=atoi(good4_num_email))
	{
		num4 = 1;
		cout<<"index4:"<<good4_bag_num<<" num4:"<<hero_send->getBag()->getGridNum(atoi(good4_bag_num))<<endl;
	}
	
	//发件人背包的物品数量不足，邮件发送失败,错误编号：1
	if((num1+num2+num3+num4)!=atoi(goods_num))
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 1);
		send_msg(pg_hero->getFd(), g_out_buf);
		return;
	}	
	
	//如果要通过昵称找到id,不管是不是好友，都能发邮件，用缓存指针mem_operate_nickname_inspection，有疑问RTX xhm
	if( hero_send->getFriendInfo() == NULL)
	{
		cout<<"[XHM WARNING]  hero_send->getFriendInfo() == NULL(mail_systerm_send.cpp)"<<endl;
		return;
	}
	
	
	/*add chenzhen 20130326 在发送人昵称（如果有，则不加，没有后面加上区号）*/
	int areaIndex = pg_hero->getArea();
	char nickName_areaIndex[200] = {'\0'};
	strncpy(nickName_areaIndex,nickname_send,strlen(nickname_send));	
#if 0
	if(nickName_areaIndex[strlen(nickname_send)] != ']')
	{		
		sprintf(nickName_areaIndex + strlen(nickName_areaIndex),"[%d]",areaIndex);		
	}
#endif
	Mail_Txt m_t(nickName_areaIndex, title_email, content_email);
	
	//构建收件箱中的邮件数据 Tory 
//	Mail_Txt m_t(nickname_send, title_email, content_email);	
	m_t.isRead = 1;			//收件箱内未读
	
	char* uuid = cid();
	strcpy(m_t.mail_id,uuid);//生成邮件的Id evan add 2012.9.27
	free(uuid);
	
	m_t.money = atoi(money_email);
	m_t.gamegold = atoi(gamegold_email);
	strncpy(m_t.good1_id, good1_id_email, 15);
	m_t.good1_num = atoi(good1_num_email);
	
	strncpy(m_t.good2_id, good2_id_email, 15);
	m_t.good2_num = atoi(good2_num_email);
	
	strncpy(m_t.good3_id, good3_id_email, 15);
	m_t.good3_num = atoi(good3_num_email);
	
	strncpy(m_t.good4_id, good4_id_email, 15);
	m_t.good4_num = atoi(good4_num_email);

	
	Hero *hero_rec = heroid_to_hero(heroId_receive);;
	if(hero_rec == NULL)	/*收件玩家不在线的邮件操作处理*/
	{	
		cout<<"@@Tory hero_receive isn't online:"<<heroId_receive<<endl;
		//将邮件数据写入收件人的收件箱中
		int value_ret = MailSystermInterface::create_mail_data(heroId_receive, 0, (int)sizeof(m_t), (char*)&m_t);
		//写邮件至收件人的外部文件不成功，邮件发送失败,错误编号：3
		if(value_ret == -1)
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d，%d", 17, 3, 0, 3);
			send_msg(pg_hero->getFd(), g_out_buf);
			return;
		}
		
	}else{	/*收件玩家在线的邮件操作处理*/		
		cout<<"@@Tory hero_receive is online"<<endl;
		int value_ret = MailSystermInterface::add_mail_data(hero_rec, 0, (int)sizeof(m_t), &m_t);
		//写邮件至收件人的mailSysterm不成功，邮件发送失败,错误编号：3
		if(value_ret == -1)	
		{	
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d,%d", 17, 3, 0, 3);
			send_msg(pg_hero->getFd(), g_out_buf);
			return;
		}
		
	}
	
	//将邮件内容改为发件人发件箱中的邮件
	m_t.isRead = 2;									//将可读标识取消，改为发件标识
	strncpy(m_t.nickName, nickname_receive, 16);	//昵称改为发件人的昵称	

	
	//将邮件数据载入发件人的发件箱 
	int value_ret = MailSystermInterface::add_mail_data(pg_hero, 1, (int)sizeof(m_t), &m_t);
	//写邮件至发件人的mailSysterm不成功，邮件此时已成功发送，但发件人收件箱中无法保存此邮件
	if(value_ret == -1)	
	{	
		cout<<"@@Tory, add_mail_data to mail_sender's OubBox failur"<<endl;
		return;;
	}
	
	//将发送出去的物品从背包中删除掉
	if(num1==1)
	{
		useBagGoods(hero_send,good1_id_email,atoi(good1_bag_num),atoi(good1_num_email));		 	//从背包内删除必须使用的道具		
	}
	if(num2==1)
	{		
		useBagGoods(hero_send,good2_id_email,atoi(good2_bag_num),atoi(good2_num_email));		 	//从背包内删除必须使用的道具	
	}
	if(num3==1)
	{
		useBagGoods(hero_send,good3_id_email,atoi(good3_bag_num),atoi(good3_num_email));		 	//从背包内删除必须使用的道具
	}
	if(num4==1)
	{
		useBagGoods(hero_send,good4_id_email,atoi(good4_bag_num),atoi(good4_num_email));		 	//从背包内删除必须使用的道具
	}
	useGameMoney(hero_send,atoi(money_email));
	useGold(hero_send,atoi(gamegold_email));
	
}

/*
* author: evan
* date: 2012.9.25
* amend: tory 2012.12.29
* describe:客户端请求邮件列表数据（处理客户端的18,1命令）
*/
void MailSystermCommunicate::get_mail_txt_list(char* buffer)
{
	char *heroId;				 //邮件查看人的HeroId
	char *type;					 //查看的是收件还是发件；0收件；1，发件
	int  index_type;				
	char *num_start;			 //查看邮件列表的第一份邮件索引值
	int  index_start;
	char *num_end;				 //查看邮件列表的最后一份邮件索引值
	int  index_end;
	
	MSG_BEGIN(buffer,g_msg_len);
	/*邮件查看人的HeroId*/
	MSG_CHAR(heroId)
	/*查看的是收件还是发件；0收件；1，发件*/
	MSG_CHAR(type)
	index_type = atoi(type);
	cout<<"get_mail_txt_list::index_type:"<<index_type<<endl;
	
	/*查看邮件列表的第一份邮件索引值*/
	MSG_CHAR(num_start)
	index_start = atoi(num_start);
	cout<<"get_mail_txt_list::num_start:"<<num_start<<endl;
	
	/*查看邮件列表的最后一份邮件索引值*/
	MSG_CHAR(num_end)
	index_end = atoi(num_end);
	cout<<"get_mail_txt_list::num_end:"<<num_end<<endl;
	
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		cout<<"get_mail_txt_list,data error"<<endl;
		return ;
	}
	MailSysterm* m_s = iter->second;
	m_s->get_mail_list(pg_hero, index_type);

}


/*
* author: evan
* date: 2012.9.25
* amend: tory 2012.12.29
* describe:客户端请求获取单封邮件内容（处理客户端的18,0命令）
*/
void MailSystermCommunicate::get_mail_content(char* buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	char *heroId;				 //邮件查看人的HeroId
	char *type;					 //查看的是收件还是发件；0收件；1，发件
	int  index_type;				
	char *num;					 //查看的邮件的索引值
	int  index;
	char *mailid;				 //邮件Id
	
	/*邮件查看人的HeroId*/
	MSG_CHAR(heroId)
	cout<<"heroId:"<<heroId<<endl;
	
	/*查看的是收件还是发件；0收件；1，发件*/
	MSG_CHAR(type)
	index_type = atoi(type);
	cout<<"type:"<<index_type<<endl;
	
	/*查看的邮件的索引值*/
	MSG_CHAR(num)
	index = atoi(num);
	cout<<"num:"<<index<<endl;
	
	/*邮件的Id*/
	MSG_CHAR(mailid)
	cout<<"mailid:"<<mailid<<endl;
	
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		cout<<"get_mail_txt_list,data error"<<endl;
		return ;
	}
	MailSysterm* m_s = iter->second;
	m_s->get_mail_content(pg_hero, index_type, mailid);
	
	
}

/*
* author: evan
* date: 2012.9.25
* amend: tory 2012.12.29
* describe:角色上线时，请求当前玩家所有邮件的数量（处理客户端的18,3命令）
*/	
void MailSystermCommunicate::info_mail_all(char* buffer)
{
	char* heroId = pg_hero->getIdentity();
	
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		cout<<"get_mail_txt_list,data error"<<endl;
		return ;
	}
	MailSysterm* m_s = iter->second;
	m_s->getMailListNum(pg_hero);
	
}		


/*
* author: evan
* date: 2012.9.25
* amend: tory 2012.12.29
* describe:获取邮件中的物品（处理客户端的18,4命令）
*/
void MailSystermCommunicate::mail_goods_receive(char* buffer)
{
	MSG_BEGIN(buffer,g_msg_len);
	
	MSG_CHAR(char *heroId)
	cout<<"@@Tory , heroId:"<<heroId<<endl;
	MSG_CHAR(char *index_mail)
		
	MSG_CHAR_END(char *mailid)
	cout<<"@@Tory ,mailId:"<<mailid<<endl;
	
	map<string, MailSysterm*>::iterator iter = mail_map.find(heroId);
	if(iter == mail_map.end())	
	{
		cout<<"get_mail_txt_list,data error"<<endl;
		return ;
	}
	MailSysterm* m_s = iter->second;
	m_s->mail_goods_receive(pg_hero, mailid);
}