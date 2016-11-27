#ifndef RECORD_TASK_H
#define RECORD_TASK_H

#include "base/baseTcpTaskQueue.h"
#include "base/baseLock.h"
#include "base/baseTime.h"
#include "base/baseAnalysisCmd.h"

class RecordTask : public TcpTaskQueue
{
	public:
		enum Recycle_State
		{
			RS_First,
			RS_Second,
			RS_Third,
		};

		RecordTask(const SDWORD sock,const struct sockaddr_in *addr=NULL);
		~RecordTask() {};
		const char* getClassName() const
		{
			return "RecordTask";
		}
		
		/// @检查连接回收状态
		bool checkRecycle();

		/// @brief 连接验证
		SDWORD verifyConnect();
		
		/// @brief 等待同步
		SDWORD  waitSync();
		
		/// @设置连接回收状态
		SDWORD recycleConnect();
		
		/// @brief 加入容器且进行唯一性验证
		bool uniqueAdd();
		
		/// @brief 从容器中删除
		bool uniqueRemove();
		
		/// @brief 解析启动消息
		bool msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen);
		
		/// @brief 解析转发消息
		bool msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen);
		
		/// @brief 解析消息
		bool msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen);

		/// @brief 统计发送指令
		void analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen);
		
		/// @brief 统计接收指令
		void analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen);
		
		/// @brief 更改指令统计标志
		static void switchCmdAnalysis(const bool analysisCmdFlg);
	
	private:
		/// 回收状态
		Recycle_State m_recycleState;
		/// 验证标志
		bool m_verify;
		/// 回收周期
		DWORD m_recycleTime;
		/// 发送消息统计容器
		AnalysisCmd m_analysisSend;
		/// 接收消息统计容器
		AnalysisCmd m_analysisRecv;
		/// 消息统计标志
		static bool s_analysisCmdFlg;
};

#endif
