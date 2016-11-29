#include "stdafx.h"
#include "User.h"
#include "UserMgr.h"
#include "Archive.h"
#include "Protocols.h"
#include "Game2CenterTeamS.h"
#include "TeamMananger.h"
#include "SysMsgDefine.h"
#include "TeamGSS.h"

CTeamGSS g_CTeamGSS;

//接收：根据模板查询可加入房间
bool CTeamGSS::OnRecv_GetTeamList(
        UINT16 DgnType, //房间ID
        shared_func<SGetTeamListAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
        return false;

    g_TeamManager.OpenQueryRoom(qwRoleID,DgnType);
    const vector<UINT32>* pVec = g_TeamManager.GetTeamByType(DgnType);
    if(pVec == NULL || pVec->empty())
        return true;

    TVecTeamInfoForList& rList = fnAck->vecReturn;
    for(auto it = pVec->begin();it != pVec->end();it++)
    {
        CTeamInfo* pTeam = g_TeamManager.GetTeamInfoByID(*it);
        if(NULL == pTeam)
        {
            LOG_CRI << "Can not Find team :" << (*it);
            continue;
        }
        TeamInfoForList Info;
        if(!pTeam->GetTeamInfoForList(Info))
            continue;
        rList.push_back(Info);
    }
    return true;
}

void CTeamGSS::OnRecv_StopTeamList(
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return ;
    }
    g_TeamManager.CloseQueryRoom(qwRoleID);
}

//接收：请求创建房间
bool CTeamGSS::OnRecv_CreateTeam(
        UINT16 DgnType, //副本类型
        const TeamSetting& stSetting, //队伍设置
        shared_func<SCreateTeamAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
        return false;

    const SDungeonCFG * pCfg = g_TeamManager.GetDgnConfigByType(DgnType);
    if(pCfg == NULL)
    {
        fnAck->eResult = ETeam_NODgnType; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo != NULL)
    {
        fnAck->eResult = ETeam_OtherTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    // 从GameServer拉取玩家的战斗对象相关的数据
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterTeamS.SendSvr_CanEnterCreateTeam(&dwServerID, 1, qwRoleID, MAXHERO, DgnType,
            [stSetting,qwRoleID,fnAck,DgnType,this](UINT8 byRet_,NTeamGS::ETEAMResult eResult, NTeamGS::TVecTeamFighter vecFighter)
            {
                if(byRet_ != 0)
                {
                    fnAck(false);
                    return ;
                }

                if(eResult != ETeam_Suc)
                {
                    fnAck->eResult = eResult;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult, qwRoleID);
                    return ;
                }

                CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                if(NULL == pUser)
                {
                    fnAck(false);
                    return ;
                }

                CMemInfo* pMemInfo = g_TeamManager.GetRoleInfoByID(qwRoleID);
                // 已经在其他组队副本中
                if(pMemInfo != NULL)
                {
                    fnAck->eResult = ETeam_OtherTeam; 
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult, qwRoleID);
                    return ;
                }

                fnAck->dwTeamID = g_TeamManager.CreateTeam(qwRoleID, DgnType, stSetting, vecFighter);
                fnAck(true);
            });
    return true;
}

//接收：请求加入房间
bool CTeamGSS::OnRecv_EnterTeam(
        UINT32 dwTeamID, //房间ID  
        UINT32 dwPassWord,
        shared_func<SEnterTeamAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo != NULL)
    {
        fnAck->eResult = ETeam_OtherTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =g_TeamManager.GetTeamInfoByID(dwTeamID);
    if(pTeam == NULL)
    {
        fnAck->eResult = ETeam_ErrTeam;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }

    if(!pTeam->CanJoin())
    {
        fnAck->eResult = ETeam_Full;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }
    if(pTeam->GetSetting().dwPassWord != 0 && pTeam->GetSetting().dwPassWord != dwPassWord)
    {
        fnAck->eResult = ETeam_PassWord;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterTeamS.SendSvr_CanEnterCreateTeam(&dwServerID,1,qwRoleID,MAXHERO,pTeam->GetDgnType(),
            [dwPassWord,qwRoleID,fnAck,dwTeamID,this](UINT8 byRet_,NTeamGS::ETEAMResult eResult, NTeamGS::TVecTeamFighter vecFighter)
            {
                if(byRet_ != 0)
                {
                    fnAck(false);
                    return ;
                }
                if(eResult != ETeam_Suc)
                {
                    fnAck->eResult = eResult;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                if(NULL == pUser)
                {
                    fnAck(false);
                    return ;
                }
                CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
                if(pMemInfo != NULL)
                {
                    fnAck->eResult = ETeam_OtherTeam; 
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;
                }
                CTeamInfo* pTeam =g_TeamManager.GetTeamInfoByID(dwTeamID);
                if(pTeam == NULL)
                {
                    fnAck->eResult = ETeam_ErrTeam;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                    return ;
                }
                if(!pTeam->CanJoin())
                {
                    fnAck->eResult = ETeam_Full;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                    return ;
                }
                if(pTeam->GetSetting().dwPassWord != 0 && pTeam->GetSetting().dwPassWord != dwPassWord)
                {
                    fnAck->eResult = ETeam_PassWord;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                    return ;
                }
                if(pTeam->IsBattle())
                {
                    fnAck->eResult = ETeam_InBattle;
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                    return ;
                }
                g_TeamManager.JoinTeam(qwRoleID,pTeam,vecFighter);
                fnAck->dwTeamID = dwTeamID;
                fnAck(true);
            });
    return true;

}

//接收：请求更换将
bool CTeamGSS::OnRecv_ResetFigter(
        UINT64 qwNewFighter, //新将
        UINT8  byPos, //旧将
        shared_func<SResetFigterAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pMemInfo->GetStatus() == EMEMBER_READY)
    {
        fnAck->eResult = ETeam_PlayerINReady;      
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(byPos > MAXHERO )
    {
        fnAck->eResult = ETeam_NewHeroPosErr;      
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    TVecTeamFighter& rvecFighter = pMemInfo->GetFighters();
    for(auto iter = rvecFighter.begin();iter != rvecFighter.end();iter++)
    {
        TeamFighterPtr pFighter = *(iter);
        if(pFighter->GetClassType() != eType_CommonFighter)
        {
            continue;
        }
        CommonFighterPtr pCommon = dynamic_pointer_cast<CommonFighter>(pFighter);
        if(pCommon == NULL)
        {
            LOG_CRI << "Trans ERR:";
            continue;
        }
        if(pCommon->qwInstID == qwNewFighter)
        {
            fnAck->eResult = ETeam_NewHeroIn;      
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;
        }
        if(pCommon->byPos == byPos)
        {
            if(pCommon->byMain > 0)
            {
                fnAck->eResult = ETeam_MainHero;      
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                return true;
            }
        }
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterTeamS.SendSvr_GetFighterFeatureByInsID(&dwServerID, 1,qwRoleID,qwNewFighter,[this,qwRoleID,qwNewFighter,byPos,fnAck] (UINT8 byRet_,const NTeamGS::CommonFighter& stFighter){
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            fnAck(false);
            return ;
            }
            CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
            if(pMemInfo == NULL)
            {
            fnAck->eResult = ETeam_NOTInTeam; 
            fnAck(true);
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return ;
            }
            if(pMemInfo->GetStatus() == EMEMBER_READY)
            {
            fnAck->eResult = ETeam_PlayerINReady;      
            fnAck(true);  
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return ;
            }
            CTeamInfo* pTeam = g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
            if(pTeam == NULL)
            {
                fnAck->eResult = ETeam_ErrTeam;
                fnAck(true);
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                return ;
            }
            if(pTeam->IsBattle())
            {
                fnAck->eResult = ETeam_InBattle;
                fnAck(true);
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
                return ;
            }
            TVecTeamFighter& rvecFighter = pMemInfo->GetFighters();
            for(size_t sz = 0;sz != rvecFighter.size();sz++)
            {
                TeamFighterPtr pFighter = rvecFighter[sz];
                if(pFighter->GetClassType() != eType_CommonFighter)
                {
                    continue;
                }
                CommonFighterPtr pCommon = dynamic_pointer_cast<CommonFighter>(pFighter);
                if(pCommon == NULL)
                {
                    LOG_CRI << "Trans ERR:";
                    continue;
                }
                if(pCommon->qwInstID == qwNewFighter)
                {
                    fnAck->eResult = ETeam_NewHeroIn;      
                    fnAck(true);  
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;
                }
                if(pCommon->byPos == byPos)
                {
                    if(pCommon->byMain > 0)
                    {
                        fnAck->eResult = ETeam_MainHero;      
                        fnAck(true);  
                        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                        return ;
                    }
                }
            }
            if(byRet_ != 0 ||stFighter.qwInstID == 0)
            {
                fnAck->eResult = ETeam_NewHeroErr;      
                fnAck(true);  
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                return ;
            }
            NTeamGS::CommonFighterPtr pFighter(new NTeamGS::CommonFighter(stFighter));
            g_TeamManager.ResetFighter(pMemInfo,byPos,pFighter);        
            fnAck(true);
    });

    return true;
}

//接收：交换自己的将位置
bool CTeamGSS::OnRecv_ChangeSelfPos(
        UINT8 byPos1, //第1个位置
        UINT8 byPos2, //第2个位置
        shared_func<SChangeSelfPosAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(pMemInfo->GetStatus() == EMEMBER_READY)
    {
        fnAck->eResult = ETeam_PlayerINReady;      
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        fnAck->eResult = ETeam_ErrTeam;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }
    if(pTeam->IsBattle())
    {
        fnAck->eResult = ETeam_InBattle;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }

    TVecTeamFighter& rvecFighter = pMemInfo->GetFighters();
    if(byPos1 == byPos2 || byPos1  > MAXHERO || byPos2 > MAXHERO)
    {
        fnAck->eResult = ETeam_PosErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    for(auto it = rvecFighter.begin();it != rvecFighter.end();it++)
    {
        if(byPos1 == (*it)->byPos)
        {
            (*it)->byPos = byPos2;
            continue;
        }

        if(byPos2 == (*it)->byPos)
        {
            (*it)->byPos = byPos1;
            continue;
        }
    }
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());
    return true;
}

//接收：交换列的位置
bool CTeamGSS::OnRecv_ChangeArrayPos(
        UINT8 byPos1, //第1个位置
        UINT8 byPos2, //第2个位置
        shared_func<SChangeArrayPosAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
        return false;

    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    // 不是队长
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    // 已经在战斗中
    if(pTeam->IsBattle())
    {
        fnAck->eResult = ETeam_InBattle;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }

    // 位置重复
    if(byPos1 == byPos2)
    {
        fnAck->eResult = ETeam_PosErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    const SDungeonCFG * pCfg = g_TeamManager.GetDgnConfigByType(pTeam->GetDgnType());
    if(NULL == pCfg)
    {
        LOG_CRI << "CAN NOT FIND CFG";
        fnAck->eResult = ETeam_OtherErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(byPos1 >= pCfg->_Max || byPos2 >= pCfg->_Max)
    {
        fnAck->eResult = ETeam_PosErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    const TVecUINT64& rvecMembers = pTeam->GetMemBers();
    for(auto it = rvecMembers.begin();it != rvecMembers.end();it++)
    {
        CMemInfo * pMem = NULL;
        if(*it == qwRoleID)
            pMem = pMemInfo;
        else
            pMem = g_TeamManager.GetRoleInfoByID(*it);
        pMem =  g_TeamManager.GetRoleInfoByID(*it);
        if(NULL == pMem)
        {
            LOG_CRI << "GetPlayerINFO ERR";
            continue;
        }
        if(pMem->GetPos() == byPos1)
        {
            pMem->SetPos(byPos2);
            continue;
        }
        if(pMem->GetPos() == byPos2)
        {
            pMem->SetPos(byPos1);
            continue;
        }
    }
    //如果其中一个为空位
    pTeam->ChangeFreePos(byPos1,byPos2);
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());
    return true;
}

//接收：请求离开房间
bool CTeamGSS::OnRecv_LeaveTeam(
        shared_func<SLeaveTeamAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //无房间
    CMemInfo * pMemInfo = g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    g_TeamManager.PlayerLeave(pMemInfo); 
    return true;
}

//接收：玩家已经准备好
bool CTeamGSS::OnRecv_DoReady(
        shared_func<SDoReadyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //无房间
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pMemInfo->GetStatus() == EMEMBER_READY)
    {
        fnAck->eResult = ETeam_PlayerINReady; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    g_TeamManager.PlayerReady(pMemInfo);
    return true;
}

//接收：玩家取消准备好
bool CTeamGSS::OnRecv_CancelDoReady(
        shared_func<SCancelDoReadyAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //无房间
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pMemInfo->GetStatus() != EMEMBER_READY)
    {
        fnAck->eResult = ETeam_PlayerNOReady; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->IsBattle())
    {
        fnAck->eResult = ETeam_InBattle;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }
    g_TeamManager.PlayerCancelReady(pMemInfo);
    return true;
}

//接收：请求进入副本
bool CTeamGSS::OnRecv_EnterDgn(
        shared_func<SEnterDgnAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //队长
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(pTeam->IsBattle())   //  组队副本战斗中
    {
        fnAck->eResult = ETeam_InBattle;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }

    if(pTeam->GetLeaderID() != qwRoleID) // 不是队长不能开始战斗
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    const TVecUINT64& rvecMembers = pTeam->GetMemBers();
    const SDungeonCFG * pCfg = g_TeamManager.GetDgnConfigByType(pTeam->GetDgnType());
    if(NULL == pCfg)
    {
        LOG_CRI << "CAN NOT FIND CFG";
        fnAck->eResult = ETeam_OtherErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(rvecMembers.size() < pCfg->_Min) // 人数不足
    {
        fnAck->eResult = ETeam_MinPerSon; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }

    // 检查是否队员都准备好
    for(auto& rRoleID : rvecMembers)
    {
        CMemInfo * pMem = NULL;
        if(rRoleID == qwRoleID)
            continue;
        else
            pMem = g_TeamManager.GetRoleInfoByID(rRoleID);
        pMem =  g_TeamManager.GetRoleInfoByID(rRoleID);
        if(NULL == pMem)
        {
            LOG_CRI << "GetPlayerINFO ERR";
            continue;
        }
        if(pMem->GetStatus() != EMEMBER_READY)
        {
            fnAck->eResult = ETeam_MemBerNOReady; 
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;
        }
    }

    pTeam->SetBattle(true);
    UINT32 dwTeamID = pTeam->GetTeamID();
    UINT16 wDgnType = pTeam->GetDgnType();
    GetMultiPlayerBattleInfo(rvecMembers,dwTeamID,wDgnType,
            [fnAck,qwRoleID,dwTeamID,pCfg,this](ETEAMResult eResult,const NBattleGS::TVecBattleFighter& vecFighter,const TVecUINT64& vecErr)
            {
                CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(dwTeamID);
                if(pTeam == NULL)
                {
                    LOG_CRI << "Mem TeamID ERR";
                    fnAck->eResult = ETeam_NOTInTeam; 
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                if(NULL == pUser)
                {
                    pTeam->SetBattle(false);
                    fnAck(false);
                    return ;
                }
                if(pTeam->GetLeaderID() != qwRoleID)
                {
                    fnAck->eResult = ETeam_NOLeader; 
                    fnAck(true);
                    pTeam->SetBattle(false); 
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;
                }
                if(eResult != ETeam_Suc)
                {
                    if(!vecErr.empty())
                    {
                        for(auto pos = vecErr.begin();pos != vecErr.end();pos++)
                        {
                            CMemInfo * pMem =  g_TeamManager.GetRoleInfoByID(*pos);
                            if(pMem->GetTeamID() == dwTeamID)
                                pMem->SetStatus(EMEMBER_ERR);
                        }
                        g_TeamManager.NoticeTeamInfo(dwTeamID);
                    }

                    fnAck->eResult = ETeam_ErrPerSon; 
                    fnAck(true);
                    pTeam->SetBattle(false); 
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;
                }


                const TVecUINT64& rvecMembers = pTeam->GetMemBers();
                if(rvecMembers.size() < pCfg->_Min)
                {
                    fnAck->eResult = ETeam_MinPerSon; 
                    fnAck(true);
                    SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    return ;

                }
                for(auto it = rvecMembers.begin();it != rvecMembers.end();it++)
                {
                    CUserPtr pOtherUser = CUserMgr::GetUserByUserID(*it);
                    if(NULL == pOtherUser)
                    {
                        fnAck->eResult = ETeam_OtherErr; 
                        fnAck(true);
                        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                        pTeam->SetBattle(false);
                        return ;
                    }

                    CMemInfo * pMem =  g_TeamManager.GetRoleInfoByID(*it);
                    if(NULL == pMem)
                    {
                        fnAck->eResult = ETeam_PlayerNOReady; 
                        fnAck(true);
                        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                        pTeam->SetBattle(false);
                        return ;

                    }
                    if(*it != qwRoleID && pMem->GetStatus() != EMEMBER_READY)
                    {
                        fnAck->eResult = ETeam_PlayerNOReady; 
                        fnAck(true);
                        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                        pTeam->SetBattle(false);
                        return ;
                    } 

                }
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterTeamS.SendSvr_StartBattle(&dwServerID, 1,qwRoleID,pTeam->GetDgnType(),vecFighter,
                        [this,fnAck,dwTeamID,qwRoleID](UINT8 byRet_,const TeamReport& stTeamReport)
                        {
                            if(byRet_ != 0)
                            {
                                fnAck->eResult = ETeam_OtherErr; 
                                fnAck(true);
                                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                                return ;
                            }

                            CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(dwTeamID);
                            if(pTeam == NULL)
                            {
                                fnAck->eResult = ETeam_NOTInTeam; 
                                fnAck(true);
                                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                                return ;
                            }
                            pTeam->SetBattle(false); 
                            g_TeamManager.ResetTeam(pTeam);
                            const TVecUINT64& rvecMembers = pTeam->GetMemBers();
                            UINT32 dwPersonRate = g_TeamManager.GetRewardRateByPerson(rvecMembers.size());
                            UINT32 dwSysRate = g_TeamManager.GetRewardRate();
                            dwSysRate = dwSysRate*dwPersonRate / 10000;

                            for(auto it = rvecMembers.begin();it != rvecMembers.end();it++)
                            {
                                CUserPtr pOtherUser = CUserMgr::GetUserByUserID(*it);
                                if(NULL == pOtherUser)
                                    continue ;
                                UINT32 dwServerID =pOtherUser->GetGameSvrID();
                                g_Game2CenterTeamS.SendSvr_NoticeTeamReport(&dwServerID,1,*it,pTeam->GetDgnType(),stTeamReport, dwSysRate);

                            }

                            fnAck(true);
                            //应策划要求，战斗后解散队伍
                            if(stTeamReport.bySuc)
                                g_TeamManager.DisMiss(dwTeamID);
                            else
                            {
                                pTeam->SetBattle(false); 
                                g_TeamManager.ResetTeam(pTeam);
                            }
                        });
            });
    return true;
}

//接收：请求踢玩家出队伍
bool CTeamGSS::OnRecv_KickOffPlayer(
        UINT64 qwKickOffRoleID, //踢的人
        shared_func<SKickOffPlayerAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    if(qwKickOffRoleID == qwRoleID)
    {
        fnAck->eResult = ETeam_KickSelf; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    //队长
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(!pTeam->IsMember(qwKickOffRoleID))
    {
        fnAck->eResult = ETeam_KickErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    g_CTeamGSS.SendClt_NoticeKicked(&qwKickOffRoleID,1,pTeam->GetDgnType()); 
    g_TeamManager.PlayerLeave(qwKickOffRoleID); 
    return true;
}

//接收：请求获得队伍信息
bool CTeamGSS::OnRecv_GetTeamInfo(
        shared_func<SGetTeamInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID(),qwRoleID);
    fnAck(true);
    return true;
}

//接收：换副本请求
bool CTeamGSS::OnRecv_ChangDgnType(
        UINT16 NewDgnType, //新副本类型
        shared_func<SChangDgnTypeAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //队长
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->GetDgnType() == NewDgnType )
    {
        return true;
    }
    const SDungeonCFG * pNewConfig = g_TeamManager.GetDgnConfigByType(NewDgnType);
    if(pNewConfig == NULL)
    {
        fnAck->eResult = ETeam_NODgnType; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    const SDungeonCFG * pOldConfig = g_TeamManager.GetDgnConfigByType(pTeam->GetDgnType());
    if(pOldConfig == NULL)
    {
        fnAck->eResult = ETeam_OtherErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pOldConfig->_Max != pNewConfig->_Max || pOldConfig->_Min != pNewConfig->_Min)
    {
        fnAck->eResult = ETeam_DiffDgn; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->IsBattle())
    {
        fnAck->eResult = ETeam_InBattle;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);     
        return true;
    }
    g_TeamManager.ResetNewDgn(pTeam,NewDgnType);
    return true;
}

// 调用地点: OnRecv_EnterDgn
void CTeamGSS::GetMultiPlayerBattleInfo(const TVecUINT64& vecTeamUser,UINT32 dwTeamID,UINT16 wDgnType,ResultFun fun)
{
    SynRecordPtr pRecord(new SynRecord(fun)); 
    if(vecTeamUser.empty())
    {
        return ;
    }

    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(dwTeamID);
    if(pTeam == NULL)
    {
        pRecord->Finish(ETeam_ErrTeam,NBattleGS::TVecBattleFighter());
        return ;
    }
    for(auto & rRoleID :  vecTeamUser)
    {
        CUserPtr pOtherUser = CUserMgr::GetUserByUserID(rRoleID);
        if(NULL == pOtherUser)
        {
            LOG_CRI <<"ERR !User Not Game";
            pRecord->Finish(ETeam_OtherErr,NBattleGS::TVecBattleFighter());
            return ;
        }
        CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(rRoleID);
        if(pMemInfo == NULL)
        {
            LOG_CRI <<"ERR! USER NOT IN Team";
            pRecord->Finish(ETeam_OtherErr,NBattleGS::TVecBattleFighter());
            return ;
        }

        TVecUINT64 vecFighter;
        TVecUINT8  vecPos;
        for(auto & pTeamFighter : pMemInfo->GetFighters())
        {
            if(pTeamFighter->GetClassType() == eType_CommonFighter)
            {
                CommonFighterPtr ptrFighter = dynamic_pointer_cast<CommonFighter>(pTeamFighter);
                vecFighter.push_back(ptrFighter->qwInstID);
                vecPos.push_back(ptrFighter->byPos);
            }

        } 

        UINT32 dwServerID = pOtherUser->GetGameSvrID();
        g_Game2CenterTeamS.SendSvr_GetPlayerBattleInfo(&dwServerID, 1, rRoleID, pMemInfo->GetPos(), vecFighter, vecPos, pTeam->GetBeautyOwer() == rRoleID ? 1 : 0, wDgnType,
                [pRecord,rRoleID](UINT8 byRet_,NTeamGS::ETEAMResult eResult,const NBattleGS::TVecBattleFighter& vecFighter)
                {
                    if(byRet_ != 0 || eResult != ETeam_Suc)
                    {
                        pRecord->Finish(ETeam_OtherErr,NBattleGS::TVecBattleFighter(),rRoleID);
                        return;
                    }

                    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(rRoleID);
                    if(pMemInfo == NULL)
                    {
                        pRecord->Finish(ETeam_MemBerNOReady,NBattleGS::TVecBattleFighter());
                        return ;
                    }
                    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
                    if(pTeam == NULL)
                    {
                        pRecord->Finish(ETeam_MemBerNOReady,NBattleGS::TVecBattleFighter());
                        return ;
                    }
                    for(auto& rFighter : vecFighter)
                    {
                        NBattleGS::SBattleFighter& refFighter = const_cast<NBattleGS::SBattleFighter&>(rFighter);

                        if (refFighter.byFighterID != BEAUTYPOS)
                            refFighter.byFighterID =  g_TeamManager.CalFighterPos(refFighter.oFgtInfo.qwInstID, pMemInfo);

                    }
                    pRecord->Finish(ETeam_Suc,vecFighter);
                });
    }
}

//接收：换阵灵请求
bool CTeamGSS::OnRecv_ChangPet(
        UINT64 qwPetRoleID, //阵灵的主人
        shared_func<SChangPetAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
        return false;

    //队长
    CMemInfo* pMemInfo = g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    // 不是队长
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    // 更换的就是自己的阵灵
    if(qwPetRoleID == pTeam->GetBeautyOwer())
        return true;

    if(qwPetRoleID == 0)
    {
        pTeam->SetBeautyOwer(0);
        g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());
        return true;
    }

    if(!pTeam->IsMember(qwPetRoleID))
    {
        fnAck->eResult = ETeam_PetErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    CMemInfo * pBeautyMemInfo =  g_TeamManager.GetRoleInfoByID(qwPetRoleID);
    if(!pBeautyMemInfo)
    {
        fnAck->eResult = ETeam_PetErr; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(pBeautyMemInfo->IsHaveBeauty())
        pTeam->SetBeautyOwer(qwPetRoleID);
    else
        pTeam->SetBeautyOwer(0);
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());

    return true;
}

//接收：更改设置请求
bool CTeamGSS::OnRecv_ChangSetting(
        const TeamSetting& stSetting, //队伍设置
        shared_func<SChangSettingAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //队长
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    pTeam->SetSetting(stSetting);
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());
    return true;
}

//接收：换队长
bool CTeamGSS::OnRecv_ChangLeader(
        UINT64 qwNewLeader, //新队长ID
        shared_func<SChangLeaderAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    //队长
    CMemInfo * pMemInfo =  g_TeamManager.GetRoleInfoByID(qwRoleID);
    if(pMemInfo == NULL)
    {
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CTeamInfo* pTeam =  g_TeamManager.GetTeamInfoByID(pMemInfo->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Mem TeamID ERR";
        fnAck->eResult = ETeam_NOTInTeam; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(pTeam->GetLeaderID() != qwRoleID)
    {
        fnAck->eResult = ETeam_NOLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    if(qwNewLeader == qwRoleID)
    {
        fnAck->eResult = ETeam_IsLeader; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    if(!pTeam->IsMember(qwNewLeader))
    {
        fnAck->eResult = ETeam_ErrMem; 
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    pTeam->ChangLeader(qwNewLeader);
    fnAck(true);
    g_TeamManager.NoticeTeamInfo(pMemInfo->GetTeamID());
    return true;


}

void CTeamGSS::SendSysMsgIDNotify(ETEAMResult eResult,UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
        return ;
    UINT32 dwServerID = pUser->GetGameSvrID();

    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case ETeam_OtherTeam:
            eMsgID =  eMsgETeamOtherTeam;
            break;
        case ETeam_NOTInTeam:
            eMsgID =  eMsgETeamNOTInTeam;
            break;
        case ETeam_PreDgn:
            eMsgID =  eMsgETeamPreDgn;
            break;
        case ETeam_Full:
            eMsgID =  eMsgETeamFull;
            break;
        case ETeam_NOLeader:
            eMsgID =  eMsgETeamNOLeader;
            break;
        case ETeam_NODgnType:
            eMsgID =  eMsgETeamNODgnType;
            break;
        case ETeam_ErrTeam:
            eMsgID =  eMsgETeamErrTeam;
            break;
        case ETeam_NewHeroErr:
            eMsgID =  eMsgETeamNewHeroErr;
            break;
        case ETeam_MainHero:
            eMsgID =  eMsgETeamMainHero;
            break;
        case ETeam_NewHeroIn:
            eMsgID =  eMsgETeamNewHeroIn;
            break;
        case ETeam_NewHeroPosErr:
            eMsgID =  eMsgETeamNewHeroPosErr;
            break;
        case ETeam_PlayerINReady:
            eMsgID =  eMsgETeamPlayerINReady;
            break;
        case ETeam_PlayerNOReady:
            eMsgID =  eMsgETeamPlayerNOReady;
            break;
        case ETeam_MemBerNOReady:
            eMsgID =  eMsgETeamMemBerNOReady;
            break;
        case ETeam_LowLevel:
            eMsgID =  eMsgETeamLowLevel;
            break;
        case ETeam_KickSelf:
            eMsgID =  eMsgETeamKickSelf;
            break;
        case ETeam_KickErr:
            eMsgID =  eMsgETeamKickErr;
            break;
        case ETeam_PosErr:
            eMsgID =  eMsgETeamPosErr;
            break;
        case ETeam_InBattle:
            eMsgID =  eMsgETeamInBattle;
            break;
        case ETeam_MinPerSon:
            eMsgID =  eMsgETeamMinPerSon;
            break;
        case ETeam_ErrPerSon:
            eMsgID =  eMsgETeamErrPerSon;
            break;
        case ETeam_DiffDgn:
            eMsgID =  eMsgETeamDiffDgn;
            break;
        case ETeam_PassWord:
            eMsgID =  eMsgTeamBattlePasswordError;
            break;
        case ETeam_IsLeader:
        case ETeam_ErrMem:
        case ETeam_PetErr:
        case ETeam_OtherErr:
            eMsgID =  eMsgOtherErr;
            break;
        default :
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_Game2CenterCommS.SendSvr_SendSysMsg(&dwServerID,1,qwRoleID,eMsgID);
}
