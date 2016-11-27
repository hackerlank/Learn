/**
 * \file
 * \version  $Id: CharBase.h 53 2013-04-17 05:03:41Z  $
 * \author  ,@163.com
 * \date 2005年01月07日 21时09分24秒 CST
 * \brief 定义人物角色相关信息
 *
 * 
 */

 
#ifndef _CharBase_h_
#define _CharBase_h_

#include "zType.h"
#include <string.h>
#pragma pack(1)

//这里需要在数据库里面加字段
struct CharBase
{
    // 角色编号,charid,全区唯一编号
	QWORD 	charid;				
    //绑定的数字帐号
    char    account[MAX_NAMESIZE];
    char    email[MAX_NAMESIZE];
    char    phoneNum[MAX_NAMESIZE];
    //角色创建时间
	DWORD   createtime;
    //在线时间
	DWORD 	onlinetime;						
    //离线时间
	DWORD 	offlinetime;		
#if 0
    CharBase()
    {
        bzero(this,sizeof(*this));
    }
#endif
};

struct AccountInfo
{
    char phoneNum[MAX_NAMESIZE];
    char email[MAX_NAMESIZE];
    char account[MAX_NAMESIZE];
    char passwd[MAX_NAMESIZE];
    AccountInfo()
    {
        bzero(this,sizeof(*this));
    }
    bool operator < (const AccountInfo& accountInfo) const
    {
        if(strlen(phoneNum) && strlen(accountInfo.phoneNum))
        {
            return strncmp(phoneNum,accountInfo.phoneNum,strlen(phoneNum)) == -1 ? true : false;
        }
        if(strlen(email) && strlen(accountInfo.email))
        {
            return strncmp(email,accountInfo.email,strlen(email)) == -1 ? true : false;
        }
        return false;
    }
};

enum ChangeType
{
	CHANGE_NONE             = 0,
	CHANGE_DAY              = 1,                // 按天
	CHANGE_WEEK             = 2,                // 按周
	CHANGE_MONTH            = 3,                // 按月
	CHANGE_PHASE            = 4,                // 按时间段
	CHANGE_DIY              = 5,                // 自定义时间
	CHANGE_SIXHOUR          = 6,                // 每天六点
};

enum CounterType
{
	IS_FIRST_LOGIN 					= 0,    //是否是新玩家
};

#pragma pack()

#endif

