// =====================================================================================
//
//       Filename:  RankProtS.cpp
//
//    Description:  排名协议处理类
//
//        Version:  1.0
//        Created:  09/04/2014 10:47:05 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "RankProtS.h"

#include "RankMgr.h"

#include "User.h"
#include "UserMgr.h"
#include "Protocols.h"

#include "Parameter.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "SysMsgDefine.h"


CRankProtS::~CRankProtS()
{
}

// 接收：获取排行榜数据
bool CRankProtS::OnRecv_GetRankInfo(
        ERankType eType, //排行榜类型
        UINT32 dwIndex, //排名索引
        UINT32 dwCount, //排名个数
        shared_func<SGetRankInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    fnAck->eType = eType;
    CRankMgr::Instance().GetRankInfo(qwRoleID, eType, dwIndex, dwCount, 
            fnAck->dwMaxCount, fnAck->dwCurIndex, fnAck->dwSelfRank, fnAck->vecRankInfo, fnAck->vecSelfRankInfo);

    return true;
}

//接收：获得崇拜数量
bool CRankProtS::OnRecv_GetAdoreCount(
        UINT64 qwRoleID, //玩家ID
        shared_func<SGetAdoreCountAck>& fnAck //返回回调函数
        )
{
    fnAck->dwCount = CRankMgr::Instance().GetAdoreCount(qwRoleID);
    UINT64 qwOPID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwOPID);
    if(pUser)
    {
        CCenterVar& rVar = pUser->GetCenterVar();
        if (SParamConfig::byDailyMaxAdoreCount < rVar.GetVar(NVarDefine::ePlayerVarAdoreCount))
            fnAck->dwSelfCount = 0;
        else
            fnAck->dwSelfCount = SParamConfig::byDailyMaxAdoreCount - rVar.GetVar(NVarDefine::ePlayerVarAdoreCount);
    }
    return true;
}

//接收：崇拜玩家
bool CRankProtS::OnRecv_AdorePlayer(
        UINT64 qwRoleID, //玩家ID
        shared_func<SAdorePlayerAck>& fnAck //返回回调函数
        )
{
    bool bRet = false;
    UINT64 qwOPID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwOPID);
    fnAck->dwCount = CRankMgr::Instance().GetAdoreCount(qwRoleID);
    if(pUser)
    {
        CCenterVar& rVar = pUser->GetCenterVar();
        if (SParamConfig::byDailyMaxAdoreCount <= rVar.GetVar(NVarDefine::ePlayerVarAdoreCount))
        {
            fnAck->dwSelfCount = 0;
            TVecUINT64 vecUserID;
            vecUserID.push_back(qwOPID);
            g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgAdoreFailure, BuildStrVec(0));
            fnAck->eResult = eRRFailed;
        }
        else
        {
            bRet = CRankMgr::Instance().CheckAdorePlayer(qwOPID, qwRoleID);
            if (!bRet)
            {
                TVecUINT64 vecUserID;
                vecUserID.push_back(qwOPID);
                g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgAdoreRepeat);
                fnAck->eResult = eRRFailed;
            }
            else
            {
                UINT32 dwSeverID = pUser->GetGameSvrID();
                if (dwSeverID)
                {
                    g_Game2CenterCommS.SendSvr_CanPushLoot(&dwSeverID, 1, qwOPID, SParamConfig::wDailyAdoreReward,
                            [fnAck, qwOPID, qwRoleID, dwSeverID, pUser](UINT8 byRet, UINT8 byRet2) mutable
                            {
                            CCenterVar& rVar = pUser->GetCenterVar();
                            if (byRet == 0 && byRet2 == 0)
                            {
                            bool bRet = CRankMgr::Instance().AdorePlayer(qwOPID, qwRoleID, fnAck->eResult, fnAck->dwCount);
                            if (bRet)
                            {
                            rVar.AddVar(NVarDefine::ePlayerVarAdoreCount, 1);
                            fnAck->eResult = eRRSuccess;
                            g_Game2CenterCommS.SendSvr_PushLoot(&dwSeverID, 1, qwOPID, eOpAdoreAward, NLogDataDefine::ItemFrom_RankAdoreAward, SParamConfig::wDailyAdoreReward);
                            }
                            fnAck->dwSelfCount = SParamConfig::byDailyMaxAdoreCount - rVar.GetVar(NVarDefine::ePlayerVarAdoreCount);
                            if (bRet)
                            {
                            TVecUINT64 vecUserID;
                            vecUserID.push_back(qwOPID);
                            g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgAdoreSuccess, BuildStrVec(fnAck->dwSelfCount));
                            }
                            fnAck(true);
                            if (bRet) 
                            {
                                CUserPtr pUser = CUserMgr::GetUserByUserID(qwOPID);
                                TVecINT32 vecParam2;
                                vecParam2.push_back(rVar.GetVar(NVarDefine::ePlayerVarAdoreCount));

                                if (pUser && pUser->IsOnLine())
                                {
                                    pUser->OnEvent(eEventType_PlayerProstrate, vecParam2);
                                }
                                else
                                {
                                    CUser::AddOffLineEvent(qwOPID, eEventType_PlayerProstrate,vecParam2);
                                }

                            }
                            }
                            else
                            {
                                fnAck->eResult = eRRFailed;
                                fnAck(false);
                            }
                            fnAck->dwSelfCount = SParamConfig::byDailyMaxAdoreCount - rVar.GetVar(NVarDefine::ePlayerVarAdoreCount);
                            });
                }
            }
            fnAck->dwSelfCount = SParamConfig::byDailyMaxAdoreCount - rVar.GetVar(NVarDefine::ePlayerVarAdoreCount);
        }
    }
    return bRet;
}

//接收：获得玩家外观信息
bool CRankProtS::OnRecv_GetPlayerFeature(
        UINT64 qwRoleID, //玩家ID
        shared_func<SGetPlayerFeatureAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOPID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwOPID);
    if(!pUser)
    {
        fnAck->eResult = eRRFailed;
        return false;
    }
    UINT32 dwSeverID = pUser->GetGameSvrID();
    if (dwSeverID)
    {
        g_Game2CenterRankS.SendSvr_GetFeature(&dwSeverID, 1, qwRoleID, 
                [fnAck](UINT8 byRet, UINT8 byError, const std::string& strName, UINT16 wLevel, const NBattleGS::SFeatureBasePtr& pFeature)
                {
                if (!byRet && !byError)
                {
                fnAck->eResult = eRRSuccess;
                fnAck->pFeature = pFeature;
                fnAck(true);
                }
                else
                {
                LOG_CRI << "byRet = " << static_cast<INT32>(byRet) << ", byError = " << static_cast<INT32>(byError);
                fnAck->eResult = eRRFailed;
                fnAck(false);
                }
                });
    }
    return true;
}

