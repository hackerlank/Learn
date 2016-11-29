#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "UserMgr.h"
#include "Player.h"
#include "NPCMgr.h"
#include "TaskMgr.h"
#include "MapMgr.h"
#include "Parameter.h"
#include "GameNetMgr.h"

//接收：打开NPC对话界面请求
void CNpcProtS::OnRecv_NpcTalkReq(
        UINT64 qwCreatureID //当前NPC的生物ID
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;
    CNpcPtr pNpc = CNpcMgr::GetNpc(qwCreatureID);
    if(pNpc == NULL)
        return;
    float fDist = GetDistance(*pPlayer, *pNpc);
    if(fDist > (float)SParamConfig::wParamNpcTalkDist)
    {
        Send_NpcTalkNtf(qwCreatureID, eTalkTooFar, "");
        return;
    }
    string strText;
    if (!Config.GetScript().NpcTalk(strText,"Main",pNpc->GetNpcID(),*pUser)||strText.empty())
    {
        return ;
    }
    CTaskMgr::GetNpcAcceptTaskMsg(*pNpc, *pUser, strText);
    if(!CTaskMgr::GetNpcTalkTaskMsg(*pNpc, *pUser, strText))
        return;
    LOG_INF<<"NPC num Is:" <<strText;
    Send_NpcTalkNtf(qwCreatureID, eTalkSucceed, strText);
    pPlayer->SetCurNpcID(qwCreatureID);
}

//接收：执行NPC对话脚本函数
void CNpcProtS::OnRecv_ExecScriptFunc(
        UINT64 qwCreatureID, //当前NPC的生物ID
        const std::string& strFuncName //脚本函数名称
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;
    CNpcPtr pNpc = CNpcMgr::GetNpc(qwCreatureID);
    if(pNpc == NULL)
        return;
    float fDist = GetDistance(*pPlayer, *pNpc);
    if(fDist > (float)SParamConfig::wParamNpcTalkDist)
    {
        Send_NpcTalkNtf(qwCreatureID, eTalkTooFar, "");
        return;
    }
    //执行函数
    string strText;
    if (!Config.GetScript().NpcTalk(strText,strFuncName,pNpc->GetNpcID(),*pUser)||strText.empty())
    {
        return ;
    }

    CTaskMgr::GetNpcAcceptTaskMsg(*pNpc, *pUser, strText);
    if(!CTaskMgr::GetNpcTalkTaskMsg(*pNpc, *pUser, strText))
        return;
    Send_NpcTalkNtf(qwCreatureID, eTalkSucceed, strText);
    pPlayer->SetCurNpcID(qwCreatureID);
}
//接收：完成一任务对话
 bool CNpcProtS::OnRecv_FinishTaskTalk(
		UINT64 qwCreatureID, //当前NPC的生物ID
		UINT16 wTaskID, //对话的任务
		shared_func<SFinishTaskTalkAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return  false;
    CNpcPtr pNpc = CNpcMgr::GetNpc(qwCreatureID);
    if(pNpc == NULL)
        return false;
    float fDist = GetDistance(*pPlayer, *pNpc);
    if(fDist > (float)SParamConfig::wParamNpcTalkDist)
    {
        //Send_NpcTalkNtf(qwCreatureID, eTalkTooFar, "");
        return false;
    }
    string &strText = fnAck->strContent;
    if (!Config.GetScript().NpcTalk(strText,"Main",pNpc->GetNpcID(),*pUser)||strText.empty())
    {
        return false;
    }
    //执行函数
    CTaskMgr::FinishTaskTalk(*pNpc, *pUser,wTaskID);
    CTaskMgr::GetNpcAcceptTaskMsg(*pNpc, *pUser, strText);
    if(!CTaskMgr::GetNpcTalkTaskMsg(*pNpc, *pUser, strText))
        return false;
    pPlayer->SetCurNpcID(qwCreatureID);
    return true;
}



void CNpcProtS::OnRecv_NpcTaskStateReq(
        UINT16 wMapID //地图ID
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    string strText;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        return;
    }

    CGameMapPtr pMap = NULL;
    if(wMapID == 0)
        pMap = pPlayer->GetMap();
    else
        pMap = CMapMgr::GetMap(wMapID);

    if(pMap == NULL)
        return;
    TVecNpcTask vecNpcTask;
    const TMapID2Npc& rMapID2Npc = pMap->GetNpcMap();
    for(auto it = rMapID2Npc.begin(); it != rMapID2Npc.end(); ++it)
    {
        CNpcPtr pNpc = it->second.lock();
        if(pNpc == NULL)
            continue;
        ENpcTaskState eNpcTaskState = pUser->GetTaskPkg().GetNpcTaskState(pNpc->GetNpcID());
        if(eNpcTaskState == eNpcTaskNone)
            continue;
        SNpcTaskState oNpcTask(pNpc->GetNpcID(), eNpcTaskState);
        vecNpcTask.push_back(oNpcTask);
    }
    if(!vecNpcTask.empty())
        pUser->SendPkg(BuildPkg_NpcTaskStateNtf(vecNpcTask));

}



