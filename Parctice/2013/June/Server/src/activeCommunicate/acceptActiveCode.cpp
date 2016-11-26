/*
		文件类型：实现文件
		文件名称：acceptActiveCode.cpp
		文件作用：实现激活码的交互；
		修改人：chenzhen
		修改时间：2013.01.17
*/
#include"bag_operator.h"
#include"active_communicate.h"
#include"wholeDefine.h"
#include"hero.h"
#include"md5.h"  

extern set<AvtiveCode> outerActiveCodeMap;
extern set<AvtiveCode> innerActiveCodeMap;
extern Role *pg_role;
extern int sock_fd;
extern int cdKeySrvFd;
extern int g_msg_len;
extern char server_name[20];
extern Hero* pg_hero;
extern map<int, Role*> fd_to_pRole;
extern MyMemcache* cdkeyMemcached;
extern map<string,string> cdkey_to_goodsid;
/*激活码交互函数*/
void acceptActiveCode(char *buffer)
{	
	char *activeCodeId;	
	char failReason[100] = {'\0'};
	Role *role;
	char *userNme;
	map<int, Role*>::iterator role_it;
	
	MSG_BEGIN(buffer,g_msg_len);
	
	/*解析激活码*/
	MSG_CHAR_END(activeCodeId);
	
	cout<<"come hero and activeCodeId:"<<activeCodeId<<endl;
	
	role_it = fd_to_pRole.find(sock_fd);
	if(role_it == fd_to_pRole.end())
	{
		return;
	}
	role = role_it->second;
	userNme = role->getUserName();
	if(userNme == NULL)
	{
		cout<<"userNme is NULL:"<<endl;
		return;
	}
	
	if(activeCodeId == NULL || strlen(activeCodeId) == 0)
	{
		cout<<"activeCodeId is NULL:"<<endl;
		return;
	}
	
	char key[60]={0};
	strncpy(key,userNme,strlen(userNme));
	strncat(key,activeCodeId,1);
	int size=0;
	char *result;
	
	result=cdkeyMemcached->get_mem_data(activeCodeId,&size);
	if (!result)
	{	
		result=NULL;
		size=0;
		result=cdkeyMemcached->get_mem_data(key,&size);
		if (!result)
		{
			if (strlen(activeCodeId)==18)
			{
				cout<<"222222222222222222222222222222222"<<endl;
				memset(g_out_buf,0,sizeof(g_out_buf));
				char temp[60]={0};
				strncpy(temp,activeCodeId,12);
				cout<<"temp:"<<temp<<endl;
				strcat(temp,"1As8DSxfcfdas3d#@fdas-0jkduYHHfdXdfdaSDFDsseD");
				cout<<"temp:"<<temp<<endl;
				MD5 *md5=new MD5(temp,strlen(temp));
				string md5_string=md5->toString();
				cout<<"md5_string:"<<md5_string<<endl;
				delete md5;
				if (strncmp(md5_string.substr(0,6).c_str(),activeCodeId+12,6)==0)
				{				
					map<string,string>::iterator it;
					char cdkey[5]={0};
					strncpy(cdkey,activeCodeId,4);
					cout<<"cdkey:"<<cdkey<<endl;
					it=cdkey_to_goodsid.find(cdkey);
					if (it==cdkey_to_goodsid.end())
					{
						cout<<"cdkey config error in acceptActiveCode.cpp 95"<<endl;
						return;
					}
					else
					{
						char rewardGoodsId[20]={0};
						strncpy(rewardGoodsId,(it->second).c_str(),sizeof(rewardGoodsId)-1);
						if (saveGoodsInBag(pg_hero,rewardGoodsId,1))
						{
							// pg_hero->useActiveCode(activeCodeId,0);
						
							snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,3",28,3);
				
							send_msg(pg_hero->getFd(),g_out_buf);		
							
							char account_msg[1024]={'\0'};
							snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s",20,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),pg_role->getUserName(),activeCodeId);
							write_log(account_msg);	
							
							cdkeyMemcached->set_mem_data(activeCodeId,key,strlen(key));
							cdkeyMemcached->set_mem_data(key,activeCodeId,strlen(activeCodeId));
						}	
					}								
				}
				else
				{
					cout<<"官网验证码验证失败"<<endl;
					msg_error(g_out_buf,144);
					send_msg(pg_hero->getFd(),g_out_buf); 	
				}
			}
			else
			{
				cout<<"strlen(activeCodeId)::"<<strlen(activeCodeId)<<endl;
				msg_error(g_out_buf,144);
				send_msg(pg_hero->getFd(),g_out_buf); 	
			}
		}
		else
		{
			msg_error(g_out_buf,143);
			send_msg(pg_hero->getFd(),g_out_buf); 
		}
	}
	else
	{
		//cdkey已经使用
		msg_error(g_out_buf,142);
		send_msg(pg_hero->getFd(),g_out_buf); 	
	}
}

//解析从cdkey Server返回的消息
void acceptCdkeySrv(char *buffer)
{
	if (sock_fd != cdKeySrvFd)
	{
		return;
	}
	cout<<"the sizeof buff:"<<strlen(buffer)<<endl;
	
	char *userName;
	char *cdKeyId;
	char *heroId;
	char failReason[100] = {0};
	char *flag;
	MSG_BEGIN(buffer,g_msg_len);
	// MSG_CHAR(userName);
	MSG_CHAR(heroId);
	// MSG_CHAR(cdKeyId);
	// MSG_CHAR_END(flag);
	
	Hero *myHero = heroid_to_hero(heroId);
	
	if(myHero == NULL)
	{
		cout<<"the hero is NUll:"<<heroId<<endl;
		return;
	}
	
	
	cout<<"userName:"<<userName<<endl;
	cout<<"heroId:"<<heroId<<endl;
	cout<<"cdKeyId:"<<cdKeyId<<endl;
	cout<<"flag:"<<flag<<endl;
	
	
	if(strncmp(flag,"0",1) == 0)
	{
		/*激活码错误*/
		snprintf(failReason,sizeof(failReason),"%d,%d,0",28,3);
		send_msg(myHero->getFd(),failReason); 	
		cout<<"the activeCodeId is error:"<<cdKeyId<<endl;
	}	
	else if(strncmp(flag,"1",1) == 0)
	{
		/*激活码已被使用*/
		snprintf(failReason,sizeof(failReason),"%d,%d,1",28,3);
		send_msg(myHero->getFd(),failReason); 	
		cout<<"the activeCodeId is used by other:"<<cdKeyId<<endl;
	}	
	//已使用激活码
	else if(strncmp(flag,"2",1) == 0)
	{
		snprintf(failReason,sizeof(failReason),"%d,%d,2",28,3);
		send_msg(myHero->getFd(),failReason); 	
	}	
	
}




//解析从cdkey Server返回的消息
void acceptCdkeySrvSuccess(char *buffer)
{
	if (sock_fd != cdKeySrvFd)
	{
		return;
	}
	cout<<"the sizeof buff:"<<strlen(buffer)<<endl;
	char *userName;
	char *cdKeyId;
	char *heroId;
	char *goodsId;
	char *type;
	char failReason[100] = {0};
	int flag = 0;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(userName);
	MSG_CHAR(heroId);
	MSG_CHAR(cdKeyId);
	MSG_CHAR(goodsId);	
	MSG_CHAR_END(type);
	
	
	Hero *myHero = heroid_to_hero(heroId);
	
	if(myHero == NULL)
	{
		cout<<"the hero is NUll:"<<heroId<<endl;
		return;
	}
	if(type[0] == '0')
	{
		myHero->useActiveCode(cdKeyId,0);
	}
	else
	{
		myHero->useActiveCode(cdKeyId,1);
	}
	
	/*成功激活验证码*/
	snprintf(failReason,sizeof(failReason),"%d,%d,3",28,3);
	
	send_msg(myHero->getFd(),failReason);		
	
	saveGoodsInBag(myHero,goodsId,1);
	
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s",20,0,server_name,(int)myTime.tv_sec,myHero->getIdentity(),myHero->getNickName(),pg_role->getUserName(),cdKeyId);
	write_log(account_msg);	
	
}


