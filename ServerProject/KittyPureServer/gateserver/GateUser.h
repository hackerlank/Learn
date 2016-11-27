/**
 * \file
 * \version  $Id: GateUser.h 65 2013-04-23 09:34:49Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时54分48秒 CST
 * \brief 定义网关用户类
 */

#ifndef _GATEUSER_H_
#define _GATEUSER_H_

#include <set>
#include "Command.h"
#include "RecordCommand.h"
#include "LoginUserCommand.h"
#include "Fir.h"
#include "zRWLock.h"
#include "CmdAnalysis.h"
#include "nullcmd.h"
#include "login.pb.h"
#include "extractProtoMsg.h"

class GateUserManager;
class GatewayTask;
class SceneClient;
/**
 * \brief 网关用户
 *
 */
class GateUser
{
	friend class GatewayTask;
	friend class GateUserAccountID;
	friend class RecordClient;

	public:
		QWORD charid;
		std::string strMacAddr; //MAC地址

		void lock()
		{   
			mlock.lock();
		}   

		void unlock()
		{   
			mlock.unlock();
		}   
	private:
		zMutex mlock;

	public:

	// 游戏状态
	enum Systemstate
	{
		SYSTEM_STATE_INITING,		/// 初始状态
		SYSTEM_STATE_CREATING,		/// 创建角色状态
		SYSTEM_STATE_PLAY,			/// 游戏状态
		SYSTEM_WAIT_STATE_PLAY,		/// 等待游戏状态
		SYSTEM_WAIT_STATE_UNREG		/// 等待退出角色流程
	};
	volatile Systemstate systemstate;
	void initState(){systemstate = SYSTEM_STATE_INITING;}
	bool isInitState() const {return SYSTEM_STATE_INITING == systemstate;}
	void createState(){systemstate = SYSTEM_STATE_CREATING;}
	bool isCreateState() const{return SYSTEM_STATE_CREATING == systemstate;}
	void playState(SceneClient *s=NULL , DWORD scene_tempid=0);
	bool isPlayState() const{return SYSTEM_STATE_PLAY == systemstate;}
	void waitPlayState(){systemstate = SYSTEM_WAIT_STATE_PLAY;}
	bool isWaitPlayState() const{return SYSTEM_WAIT_STATE_PLAY == systemstate;}
	void waitUnregState(){systemstate = SYSTEM_WAIT_STATE_UNREG;}
	bool isWaitUnregState() const{return (SYSTEM_WAIT_STATE_UNREG == systemstate);}
	int getState(){return systemstate;}


	SceneClient *scene;
	GatewayTask *gatewaytask;
	DWORD scene_id;
	BYTE m_byCreate; 

	GateUser(const QWORD charID,GatewayTask *histask);
	~GateUser();

	void TerminateWait();
	bool isTerminateWait();
	void Terminate();
	bool isTerminate();
	

	bool beginSelect();
	bool reg();
	void unreg();
	bool sendCmd(const void *pstrCmd, const unsigned int nCmdLen,const bool hasPacked=false);
	void final();
	public:
        GatewayTask* getGatewayTask() { return gatewaytask; }
        bool syncMemDBBase();
        bool ackLoginGateway(const ProtoMsgData::LoginError &error = ProtoMsgData::LE_Default,const bool flag = false);
};
#endif
