#ifndef PLATE_TASK_H
#define PLATE_TASK_H

#include "base/baseTcpTaskQueue.h"
#include "base/baseLock.h"
#include "base/baseTime.h"
#include "base/baseAnalysisCmd.h"

class PlateTask : public TcpTaskQueue
{
	public:
		enum Recycle_State
		{
			RS_First,
			RS_Second,
			RS_Third,
		};

		PlateTask(const SDWORD sock,const struct sockaddr_in *addr=NULL);
		~PlateTask() {};

		const char* getClassName() const
		{
			return "PlateTask";
		}
		
		/// @brief 是否通知全部返回
		bool notifyReturnOK()
		{
			return m_serverSize == m_serverReturnSize;
		}
		
		bool notifyMeReturnOK()
		{
			return m_hasNotifyMeReturn;
		}
		
		void notifyReturn()
		{
			++m_serverReturnSize;
		}
		
		bool checkRecycle();
		
		/// @brief 验证连接
		SDWORD verifyConnect();
		
		/// @brief 等待同步
		SDWORD  waitSync();
		
		/// @brief 设置回收状态
		SDWORD recycleConnect();
		
		/// @brief 放入容器进行唯一性验证
		bool uniqueAdd();
		
		/// @brief 从容器中唯一性删除
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
		/// @brief 连接认证
		bool verify(const DWORD serverType,const char *ip);
		/// @brief 同步通知其他服务器
		bool notifyOther();
		
		/// @brief 同步通知自己
		bool notifyMe();

	private:
		/// 协议号
		DWORD m_protocol;
		/// 编译时间
		DWORD m_buildTime;
		/// 版本号
		DWORD m_svnVersion;
		/// 回收状态
		Recycle_State m_recycleState;
		/// 验证标志
		bool m_verify;
		/// 回收周期
		DWORD m_recycleTime;
		/// 同步定时器
		Timer m_syncTimer;
		/// 启动时通知其他服务器标志
		bool m_hasNotifyOther;
		/// 启动时通知自己
		bool m_hasNotifyMe;
		/// 启动时通知自己已返回标志
		bool m_hasNotifyMeReturn;
		/// 启动时通知其他服务器数量
		DWORD m_serverSize;
		/// 启动时通知其他服务器已返回数量
		DWORD m_serverReturnSize;
		/// 对应服务器的ip
		char m_ip[MAX_IP_LENGTH];
		/// 对应服务器的端口
		WORD m_port;
		/// 对应服务器的对外ip
		char m_outIP[MAX_IP_LENGTH];
		/// 对应服务器的对外端口
		WORD m_outPort;
		/// 发送消息统计容器
		AnalysisCmd m_analysisSend;
		/// 接收消息统计容器
		AnalysisCmd m_analysisRecv;
		/// 消息统计标志
		static bool s_analysisCmdFlg;
};
#endif
