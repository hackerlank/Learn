#pragma once
#include "NpcProtSvr.h"

using namespace NNpcProt;
class CNpcProtS : public CNpcProtSvr
{
public:
    //接收：打开NPC对话界面请求
    virtual void OnRecv_NpcTalkReq(
        UINT64 qwCreatureID //当前NPC的生物ID
    );

    //接收：执行NPC对话脚本函数
    virtual void OnRecv_ExecScriptFunc(
        UINT64 qwCreatureID, //当前NPC的生物ID
        const std::string& strFuncName //脚本函数名称
    );
    
   //接收：完成一任务对话
	virtual bool OnRecv_FinishTaskTalk(
		UINT64 qwCreatureID, //当前NPC的生物ID
		UINT16 wTaskID, //对话的任务
		shared_func<SFinishTaskTalkAck>& fnAck //返回回调函数
	);

	//接收：地图的NPC任务状态请求
	virtual void OnRecv_NpcTaskStateReq(
		UINT16 wMapID //地图ID
	);
};
