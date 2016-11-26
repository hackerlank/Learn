/*
* 文件类型：角色管理，创建角色
* 文件名称：role_manage_create_hero.cpp
* 创建时间：2012.3.14
* authou：	Tory
*/
#include<string>
#include<map>
#include <sstream>
#include"command_user_role_manage.h"
#include"command_return_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"
#include"task_configuration.h"
//邮件系统操作头文件
/* #include "mail_systerm_interface.h" */

#include "bootAssignment.h"

#include"dictionary_asist.h"

#include"statuaryAsist.h"

#define INSERT_G_NICK_NAME_MAP(a,b) ( map<string,string>::value_type( (a),(b)) )

extern int sock_fd;
extern map<string,string>nickName2heroId;

//全局hanshmap 昵称对应heroId；TODO 不要删除 add xhm；
extern  NickNameCheck_T mynickName;
extern  int nickNameCounts;
extern int 	preNickNameCounts;
extern  vector<string> heroNameCheckName;
extern  vector<string> heroNameCheckHeroId;
extern NickName2heroIdHash heroNameCheckHash;

extern struct timeval myTime;
extern char server_name[10];
extern map<int, Role*> fd_to_pRole;

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;

extern int g_msg_len;
extern char g_out_buf[20480];

using namespace std;

//创建游戏角色消息解析
void createHero(char *buffer)
{
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(char* party);					//解析要创建角色的门派
	cout<<"@@Tory party:"<<party<<endl;
	
    MSG_CHAR(char* user_name);				//解析要创建角色的用户名	
	cout<<"@@Tory user_name:"<<user_name<<endl;

	MSG_CHAR(char* nickName);				//解析要创建角色的昵称
	cout<<"@@Tory nickName:"<<nickName<<endl;

	//输入的昵称不超过18字节（6个汉字），错误代码：3（NAME_ILLEGAL_FAILED）
	if (strlen(nickName) < 1 || strlen(nickName) > 18)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, 0, 3);	
		send_msg(sock_fd, g_out_buf);
		return;
	}
	//名字里含有敏感字，错误代码：3（NAME_ILLEGAL_FAILED）
	if (isHaveDirtyWords(nickName) == 1)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, 0, 3);	
		send_msg(sock_fd, g_out_buf);
		return;
	}
	//名字里有禁闭的标点符号，错误代码：3（NAME_ILLEGAL_FAILED）
	if  (isHaveIllSymbol(nickName) == 1)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, 0, 3);	
		send_msg(sock_fd, g_out_buf);
		return;
	}
	
	//TODO 缓存操作，不要删除。
 	int nickname_inspection_size = 0;
	char* result = mem_operate_nickname_inspection->get_mem_data(nickName, &nickname_inspection_size); 
	if(result != NULL)
	{
		free(result);
		puts("[XHM MSG] get mem_data from nickname_inspection memcached server success ,The same as the user name.\n");
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, CREATE_HERO_RETURN, NAME_SAME_FALLED);	
		send_msg(sock_fd, g_out_buf); 
		return;
	}
	else
		puts("[XHM MSG] get mem_operate_nickname_inspection mem_data from nickname_inspection memcached server  failure!\n");	

	//用户hashmap同名检测机制，请不要删除，有疑问RTX xhm;
	
	NickName2heroIdHash::iterator sameNameiter = heroNameCheckHash.find(nickName);
	//昵称重名，错误代码：2（NAME_SAME_FALLED）
	if(sameNameiter != heroNameCheckHash.end())
	{
		puts("[XHM MSG]  heroNameCheckHash.find name ,The same as the user name.\n");
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, 0, 3);	
		send_msg(sock_fd, g_out_buf);
		return;
	}
	
	map<int, Role*>::iterator iter = fd_to_pRole.find(sock_fd);
	if(iter == fd_to_pRole.end())
		return ;
	Role *player = iter->second;
	
	//创建角色，tory
	Hero *my_hero = player->create_hero(party, nickName, const_cast<char *>("femal"));
	if(my_hero == NULL)
	{
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d", 1, 0, 0);	
		send_msg(sock_fd, g_out_buf);
		return;
    }	
	
	
	//设置在黑木崖开启层数
	my_hero->initNowTowerId();
	
	//耐力值
	my_hero->memHero->fatigueUpperVal = my_hero->memHero->vipDailyData.muscleTimes;
	my_hero->memHero->lastStrength = my_hero->memHero->fatigueUpperVal;
	
	//三倍经验丹购买数量
	my_hero->memHero->buyThreeTmeExpCtn = 0;
	
	//青衣楼可进入层记录
	my_hero->initZoreLayerFlg();
	
	memset(my_hero->memHero->activeCodeId,'\0',sizeof(my_hero->memHero->activeCodeId));
	memset(my_hero->memHero->partyCodeId,'\0',sizeof(my_hero->memHero->partyCodeId));
	
	//TODO 这里可以创建账户；
		
    my_hero->memSet();		//创建角色成功，将当前角色下的所有数据set进memcached (add by tory 2012.9.14)
    player->memSet();       //玩家创建角色成功，需更新当前玩家memcached server中的角色列表数据 (add by tory 2012.9.14)
	
	/*测试雕像用*/
//	testInStatuary();
	
//	player->show_memRole_data();

	/*记录创建角色的流水账 jolly 11.14 start*/
	char account_msg[1024]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%s,%s",1,0,server_name,(int)myTime.tv_sec,player->getUserName(),my_hero->getIdentity(),nickName,party);
	write_log(account_msg);
	/*记录创建角色的流水账 jolly 11.14 end*/
	
	//TODO 缓存操作，不要删除。
 	bool isSuccess = mem_operate_nickname_inspection->set_mem_data(nickName, my_hero->getIdentity(), strlen(my_hero->getIdentity())); 
	if(isSuccess != true)
		puts("[XHM WARNING] set memData to nickname_inspection memcached server failure!");	 
		
    //添加到昵称同名检查容器；请不要删除。
    // memcpy(mynickName.nickName[nickNameCounts],nickName,strlen(nickName));
    // memcpy(mynickName.HeroId[nickNameCounts],my_hero->getIdentity(),strlen(my_hero->getIdentity()));
    // heroNameCheckHash[mynickName.nickName[nickNameCounts]]=mynickName.HeroId[nickNameCounts];
    // nickNameCounts++; 	

	memset(g_out_buf, 0, 20480);
	char photoId[IDL] = {"HM00101"};
	photoId[1] = *party;
	sprintf(g_out_buf, "%d,%d,%d,%s,%s,%c,%d,%s", 1,0,1,my_hero->getIdentity(), nickName, *party, 1, photoId);
	send_msg(sock_fd, g_out_buf);
	
	delete my_hero; 
}
