
#include "AnswerProtS.h"
#include "AnswerProt.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "Answer.h"
#include "User.h"
#include "UserMgr.h"

CAnswerProtS g_AnswerProtS;
//接收：玩家答题
bool CAnswerProtS::OnRecv_Answer(
		UINT8 byAnswerID, //玩家选择答案
		shared_func<SAnswerAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    bool bRet = false;
    bRet = AnswerMgr.AnswerTopic(*pUser,byAnswerID);
    
    if(bRet)
        fnAck->eResult = EAnswerResult_Suc;
    else 
        fnAck->eResult = EAnswerResult_Err;
    fnAck->dwIndex = static_cast<UINT32>(byAnswerID);
    return true;
}

//接收：玩家使用技能
bool CAnswerProtS::OnRecv_UseSkill(
		EAnswerSkill eSkillType, //技能ID
		shared_func<SUseSkillAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    fnAck->eSkillTypeRet = eSkillType;
    fnAck->eResult = AnswerMgr.UseSkill(*pUser,eSkillType);
    return true;
}
//接收：玩家报名
void CAnswerProtS::OnRecv_Join(
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return ;
    }
    AnswerMgr.OnJoin(*pUser);

}

//接收：玩家离开
void CAnswerProtS::OnRecv_Leave(
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return ;
    }
    AnswerMgr.OnLeave(*pUser);
}
//接收：获取活动开始倒计时
bool CAnswerProtS::OnRecv_GetCoutdown(
		shared_func<SGetCoutdownAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    AnswerMgr.GetCountdown(qwRoleID,fnAck->dwTime,fnAck->sPlayerInfo,fnAck->bRet);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

