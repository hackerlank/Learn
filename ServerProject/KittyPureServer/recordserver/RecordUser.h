/**
 * \file	RecordUser.h
 * \version  	$Id: RecordUser.h 53 2013-04-17 05:03:41Z  $
 * \author  	, @ztgame.com 
 * \date 	2007年01月30日 06时36分10秒 CST
 * \brief 	档案对象定义，以支持存档Cache
 *
 * 
 */

#ifndef RECORDUSER_H
#define RECORDUSER_H

#include <map>
#include <vector>
#include "RecordCommand.h"
#include "zDBConnPool.h"
#include "zSocket.h"
#include "zMisc.h"


const dbCol record_charbase[] = { 
    { "f_charid",     zDBConnPool::DB_QWORD,  sizeof(QWORD) },  
    { "f_account",    zDBConnPool::DB_STR,    50 }, 
    { "f_email",    zDBConnPool::DB_STR,  50 }, 
    { "f_phonenum",    zDBConnPool::DB_STR,  50 },
    { "f_createtime", zDBConnPool::DB_DWORD,   sizeof(DWORD) },  
    { "f_onlinetime", zDBConnPool::DB_DWORD,   sizeof(DWORD) },  
    { "f_offlinetime",zDBConnPool::DB_DWORD,   sizeof(DWORD) },
    { "f_allbinary",  zDBConnPool::DB_BIN2,   0}, 
    { NULL, 0, 0}
};

class RecordTask;

class RecordUser
{
    public:
        RecordUser();
        ~RecordUser();
        //玩家主角ID，由ID生成服务器生成，全服唯一
        QWORD charid;
        AccountInfo m_accountInfo;
        //从数据库读取角色完整档案到内存
        bool readCharBase();
        //同步角色基础信息到MemDB
        bool syncBaseMemDB();
};

#endif

