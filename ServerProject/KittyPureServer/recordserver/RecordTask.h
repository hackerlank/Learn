/**
 * \file
 * \version  $Id: RecordTask.h 42 2013-04-10 07:33:59Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义读档连接任务
 *
 */

#ifndef _RecordTask_h_
#define _RecordTask_h_

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "RecordCommand.h"
#include "zDBConnPool.h"

class RecordUser;
/**
 * \brief 定义读档连接任务类
 *
 */
class RecordTask : public zTCPTask
{

	public:
		RecordTask(zTCPTaskPool *pool,const int sock,const struct sockaddr_in *addr = NULL) : zTCPTask(pool, sock, addr, false)
		{
			wdServerID = 0;
			wdServerType = UNKNOWNSERVER;
		}
		virtual ~RecordTask() {};
		int verifyConn();
		int recycleConn();
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLe);

        //获取服务器编号
		const WORD getID() const
		{
			return wdServerID;
		}

        //获取服务器类型
		const WORD getType() const
		{
			return wdServerType;
		}

		bool uniqueAdd();
		bool uniqueRemove();

        //获得charid
        QWORD getCharID(const char *phoneNum,const char *email);
    private:
        //处理record的消息
        bool msgParseRecordCmd(const CMD::RECORD::RecordNull *ptNullCmd, const DWORD nCmdLen);
		bool verifyLogin(const CMD::RECORD::t_LoginRecord *ptCmd);
		bool create_role(const CMD::RECORD::t_CreateChar_GateRecord* cmd);
		//0成功 1失败 2账号已有角色 3角色名称重复
		DWORD create_role_inner(const AccountInfo &accountInfo,QWORD &charID);
    private:
        //服务器编号，一个区唯
		WORD wdServerID;
        //服务器类型
		WORD wdServerType;
		static const dbCol charbase_define[];
};

#endif

