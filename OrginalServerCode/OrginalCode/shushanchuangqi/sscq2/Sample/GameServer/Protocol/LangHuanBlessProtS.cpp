
#include "LangHuanBlessProtS.h"
#include "LangHuanBlessMgr.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "LangHuanBlessProt.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

CLangHuanBlessProtS g_LangHuanBlessProtS;

//接收：进入LangHuanBless地图
bool CLangHuanBlessProtS::OnRecv_EnterMap(
    shared_func<SEnterMapAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        return false;
    }
    fnAck->eLHBResult = CLangHuanBlessMgr::Instance().CanEnterMap(*pPlayer);
    if(eLHBResult_success != fnAck->eLHBResult)
    {
        return true;
    }
    fnAck->eLHBResult = CLangHuanBlessMgr::Instance().OnEnterMap(*pPlayer);
   return true;
}
//接收：选择问道
bool CLangHuanBlessProtS::OnRecv_SelectSkill(
		UINT64 qwPlayerID, //被选择的玩家
		ELHBSkillType eLHBSkillType, //技能类型
		shared_func<SSelectSkillAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eLHBResult = eLHBResult_otherError;
        return false;
    }
    if(qwPlayerID == pPlayer->GetOwnerID())
    {
        LOG_CRI << "玩家不可以对自己释放技能";
        fnAck->eLHBResult = eLHBResult_otherError;
        return false;
    }
    fnAck->eRetLHBSkillType = eLHBSkillType;
    fnAck->eLHBResult = CLangHuanBlessMgr::Instance().OnUseSkill(*pPlayer,qwPlayerID,eLHBSkillType);

    if(fnAck->eLHBResult != eLHBResult_success)
    {
        SendSysMsg(fnAck->eLHBResult);
    }

   return true;
}

//接收：活动修为值
bool CLangHuanBlessProtS::OnRecv_GetScore(
    shared_func<SGetScoreAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        return false;
    }
    fnAck->wScore = CLangHuanBlessMgr::Instance().GetScore(*pPlayer);
    return true;
}

//接收：离开boss地图
bool CLangHuanBlessProtS::OnRecv_LeaveMap(
    shared_func<SLeaveMapAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

     fnAck->eLHBResult = CLangHuanBlessMgr::Instance().OnLeaveMap(*pPlayer);
    return true;

}
//接收：获得技能使用信息
bool CLangHuanBlessProtS::OnRecv_GetSkillInfo(
		shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    fnAck->eLHBResult = CLangHuanBlessMgr::Instance().GetSkillInfo(*pPlayer,fnAck->vecLHBSkillInfo);
    
   return true;

}
void CLangHuanBlessProtS::SendSysMsg(ELHBResult eLHBResult)
{
    ESystemMsgID eSysMsgID = eMsgSuccess;
    switch(eLHBResult)
    {
        case eLHBResult_inCD:
            eSysMsgID = eMsgLHBSkillInCD;
            break;
        case eLHBResult_hasBuff:
            eSysMsgID = eMsgLHBHasBuff;
            break;
        case eLHBResult_empty:
            eSysMsgID = eMsgLHBSkillInEnd;
            break;
        default:
            break;
    }
    if(eSysMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eSysMsgID);

}
bool CLangHuanBlessProtS::OnRecv_GetSustainTime(
		shared_func<SGetSustainTimeAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    fnAck->dwTime = CLangHuanBlessMgr::Instance().GetSustainTime(*pPlayer);
    
   return true;

}
//接收：获得玩家所有信息
bool CLangHuanBlessProtS::OnRecv_GetTotalInfo(
		shared_func<SGetTotalInfoAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    fnAck->bRet = CLangHuanBlessMgr::Instance().GetTotalInfo(*pPlayer,fnAck->sTotalInfo);
    
   return fnAck->bRet;

}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

