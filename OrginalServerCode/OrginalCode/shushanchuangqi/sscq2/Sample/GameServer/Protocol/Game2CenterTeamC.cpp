#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Loot.h"
#include "Game2CenterTeamC.h"
#include "DungeonMgr.h"
#include "Monster.h"
#include "DgnCondManager.h"
#include "TeamGS.h"
#include "Player.h"
#include "Battle.h"
#include "FighterManager.h"
#include "HeroFighter.h"
#include "BeautyMgr.h"
#include "GUIDMgr.h"

using namespace NTeamGS;
//接收：玩家请求加入，创建队伍
bool CGame2CenterTeamC::OnRecv_CanEnterCreateTeam(
        UINT64 qwUsrID, //帐号ID
        UINT8  byHeroNum,
        UINT16 wDgnType, //副本模板 
        shared_func<SCanEnterCreateTeamAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
    {
        LOG_CRI << "Can't find Player! UsrID: " << qwUsrID;
        return false;
    }

    ETEAMResult eResult = pPlayer->GetDgnPkg().CanCreateEnterTeam(wDgnType);
    if(eResult != ETeam_Suc)
    {
        LOG_CRI << "Can't EnterTeam! UsrID: " << qwUsrID <<":"<<eResult;
        fnAck->eResult = eResult;
        return true;
    }

    if(byHeroNum == 0)
        return true;

    // 检查其他进入条件
    NTeamGS::TVecTeamFighter& vecFighter = fnAck->vecFighter;
    CFighterManagerPtr pManager = pPlayer->GetFighterManager();
    if(!pManager)
        return false;

    TVecFighterPtr rvecFighters;
    pManager->GetTeamFighters(rvecFighters);

    // 1主将
    bool bFindPlayerFigther = false;
    for(size_t szPos = 0; szPos != rvecFighters.size(); szPos++)
    {
        IBattleFighterPtr pBattle = rvecFighters[szPos]->ToBattleFighter(0, EBTMonster);
        SBattleFighter sBf;
        pBattle->GetBattleFighterInfo(sBf);

        NTeamGS::CommonFighterPtr pCommon(new NTeamGS::CommonFighter);
        pCommon->pFeature       = sBf.oFgtInfo.pFeature;
        pCommon->byPos          = szPos;
        pCommon->byLevel        = sBf.oFgtInfo.byLevel;
        pCommon->qwInstID       = sBf.oFgtInfo.qwInstID; 
        pCommon->wFighterID     = sBf.oFgtInfo.wFighterID;
        pCommon->dwFighterPower = rvecFighters[szPos]->GetBattlePoint();

        if(sBf.oFgtInfo.pFeature->GetClassType() == eType_SPlayerFeatureWithBuff) // 找到主将
        {
            pCommon->byMain = 1;
            bFindPlayerFigther = true;
        }
        else
            pCommon->byMain = 0;

        vecFighter.push_back(pCommon);
    }

    if(!bFindPlayerFigther) // 找不到主将
    {
        LOG_CRI << "Can't find main fighter! UsrID: " << qwUsrID;
        fnAck->eResult = ETeam_OtherErr;
        return true;
    }

    // 美女
    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if (pBeautyMgr)
    {
        TVecBattleFighterPtr vecBattleFighter;
        pBeautyMgr->GetBattleFighters(vecBattleFighter);
        for (auto& pFighter : vecBattleFighter)
        {
            if (!pFighter)
                continue;
            NTeamGS::BeautyFighterPtr pBeauty(new NTeamGS::BeautyFighter);
            SBeautyFeaturePtr pFeature(new SBeautyFeature);
            pFeature->wBeautyID     = pFighter->GetID();
            pBeauty->pFeature       = pFeature;
            pBeauty->byPos          = IBattleFighter::GetBeautyPos();
            pBeauty->wFighterID     = pFighter->GetID();
            pBeauty->dwFighterPower = pPlayer->GetFighterManager()->GetBeautyBattlePoint();
            vecFighter.push_back(pBeauty);
            LOG_DBG << "Find Beauty(" << pFighter->GetID() << ").";
        }
    }
    return true;
}

bool CGame2CenterTeamC::OnRecv_GetFighterFeatureByInsID(
        UINT64 qwUsrID, //帐号ID
        UINT64 qwFighterID, //将ID
        shared_func<SGetFighterFeatureByInsIDAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    NTeamGS::CommonFighterPtr pComm = GetTeamFighterByID(pPlayer,qwFighterID);
    if(NULL != pComm)
    {
        fnAck->stFighter = *pComm;
    }
    return true;
}

NTeamGS::CommonFighterPtr CGame2CenterTeamC::GetTeamFighterByID(CPlayerPtr pPlayer,UINT64 qwFighterID)
{
    if(pPlayer == NULL)
    {
        return  NULL;
    }
    CFighterPtr pFigter = pPlayer->GetFighterByInstID(qwFighterID); 
    if(pFigter == NULL)
    {
        return NULL;
    }
    IBattleFighterPtr pBattle = pFigter->ToBattleFighter(0, EBTMonster);
    if(pBattle == NULL)
    {
        return NULL;
    }
    SBattleFighter sBf;
    pBattle->GetBattleFighterInfo(sBf);
    SFeatureBasePtr pFeature = sBf.oFgtInfo.pFeature;
    if(pFeature == NULL)
    {
        return NULL; 
    }
    if((pFeature->GetClassType() != eType_SHeroFeature) && (pFeature->GetClassType() != eType_SPlayerFeatureWithBuff))
    {
        return NULL;
    }
    NTeamGS::CommonFighterPtr pCommon(new NTeamGS::CommonFighter);
    pCommon->pFeature = sBf.oFgtInfo.pFeature;
    pCommon->byMain = 0;
    pCommon->byLevel = sBf.oFgtInfo.byLevel;
    pCommon->qwInstID =sBf.oFgtInfo.qwInstID; 
    pCommon->wFighterID =sBf.oFgtInfo.wFighterID;
    pCommon->dwFighterPower=pFigter->GetBattlePoint();
    return pCommon;
}

//接收：玩家加入/离开队伍信息同步
void CGame2CenterTeamC::OnRecv_SynTeam(
        UINT64 qwUsrID, //帐号ID
        EPlayerTeam eStatus //玩家操作
        )
{ 
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->SetInTeam(eStatus == EPlayerEnterTeam);

    return ;
}

//接收：获取玩家战斗信息
bool CGame2CenterTeamC::OnRecv_GetPlayerBattleInfo(
        UINT64 qwUsrID, //帐号ID
		UINT8 byPlayerPos, //玩家所在的队伍位置
		const TVecUINT64& vecFigther, //散仙唯一ID
        const TVecUINT8& vecPos, //玩家序列位置
        UINT8 byNeedPet, //0,不需要阵灵，1需要阵灵
        UINT16 wDgnType, //副本类型
        shared_func<SGetPlayerBattleInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    ETEAMResult eResult = pPlayer->GetDgnPkg().CanCreateEnterTeam(wDgnType);
    if(eResult != ETeam_Suc)
    {
        LOG_CRI << "Can't EnterTeam! UsrID: " << qwUsrID;
        fnAck->eResult = eResult;
        return true;
    }

    TVecUINT16 vecFighterID;
    for (auto& rInstID : vecFigther)
    {
        CFighterPtr pFigter = pPlayer->GetFighterByInstID(rInstID); 
        if(pFigter)
            vecFighterID.push_back(pFigter->GetID());
    }
    pPlayer->GetFighterManager()->ResetCombinationSkill(vecFighterID, eCombEquipToTeam);

    for (auto& rInstID : vecFigther)
    {
        CFighterPtr pFigter = pPlayer->GetFighterByInstID(rInstID); 
        if(pFigter)
        {
            IBattleFighterPtr pBattle = pFigter->ToBattleFighter(byPlayerPos, EBTMonster);
            if(pBattle)
            {
                SBattleFighter sBf;
                pBattle->GetBattleFighterInfo(sBf);
                fnAck->vecFighter.push_back(sBf);
            }
        }
    }
    pPlayer->GetFighterManager()->SetTeamFighters(vecFighterID, vecPos);
    if(byNeedPet > 0)
    {
        CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
        if (pBeautyMgr)
        {
            TVecBattleFighterPtr vecBattleFighter;
            pBeautyMgr->GetBattleFighters(vecBattleFighter);
            for (auto& pFighter : vecBattleFighter)
            {
                if (!pFighter)
                    continue;
                SBattleFighter sBf;
                pFighter->GetBattleFighterInfo(sBf);
                sBf.byFighterID = IBattleFighter::GetBeautyPos();
                fnAck->vecFighter.push_back(sBf);
            }
        }

    }
    pPlayer->GetFighterManager()->ResetCombinationSkill();
    return true;
}

//接收：请求发起战斗
bool CGame2CenterTeamC::OnRecv_StartBattle(
        UINT64 qwUsrID, //队长ID
        UINT16 wDgnType, //副本类型
        const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
        shared_func<SStartBattleAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    const SDgnInfo* pCfg = CDungeonMgr::GetDgnInfo(wDgnType);
    if(NULL == pCfg)
    {
        LOG_CRI << "Can not Find Team DgnType:" <<wDgnType;
        return false;
    }
    const TVecUINT16& vecOrder =  pCfg->oDgnCfg.vecAttackOrder; 
    TeamReport& stTeamReport = fnAck->stTeamReport;
    stTeamReport.bySuc = 1;
    stTeamReport.qwLeaderID = pPlayer->GetRoleID();
    stTeamReport.qwLeaderFighter = pPlayer->GetMainFighter()->GetInstID();
    TVecBattleFighterPtr vecBattleFighter;
    for(auto rInfo : vecFighter)
    {
        IBattleFighterPtr pFighter = CreateBattleFighter();
        if (!pFighter || !pFighter->InitFromInfo(rInfo, vecBattleFighter))
        {
            LOG_CRI << "CREATE ERR";
            continue;
        }
        pFighter->SetPos(rInfo.byFighterID);
        pFighter->RegenAllHP();
        vecBattleFighter.push_back(pFighter);
    }
    for(auto & rID : vecOrder)
    {
        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
        vector<TVecBattleFighterPtr> vecvecBattleFighter2;
        UINT64 qwDefenseID = GET_GUID(GUID_MONSTER);
        if(!CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, rID, qwDefenseID, vecBattleFighter))
        {
            LOG_CRI << "Can't find MonsterGroup! GroupID: " << rID;
            continue;
        }
        pBS->PutFighters(0, stTeamReport.qwLeaderFighter, pPlayer->GetLevel(), vecBattleFighter, stTeamReport.qwLeaderID, false);
        pBS->PutFighters(1, qwDefenseID, CMonster::GetMonsterLevelByGroupID(rID), vecvecBattleFighter2[0], qwDefenseID);
        IBattleFighterPtr pFighter = CMonster::GetSceneFighter(rID);
        if (!pFighter)
            pFighter = pPlayer->GetSceneFighter();
        pBS->PutScene(pFighter);
        pBS->Start(EBTMonster);
        BattleReport stReport;
        pBS->GetReport(stReport.strBattle);
        if(pBS->GetFinalWinner() == EBResultAttackWin)
            stReport.bySuc = 1;     // 玩家胜利
        else
            stTeamReport.bySuc = 0;//战斗中止
        stReport.qwBattleID = pBS->GetBattleID(); 
        //设置前一场战斗的后续ID
        if(stTeamReport.vecReport.size() > 0)
        {
            string &strPreBattle = stTeamReport.vecReport.back().strBattle;
            CInArchive iar(strPreBattle);
            SBattleReport stPreBattle;
            iar >> stPreBattle;
            stPreBattle.qwNextBattleID = stReport.qwBattleID;
            strPreBattle.clear();
            COutArchive oar(strPreBattle);
            oar << stPreBattle;
        }
        vecBattleFighter.clear();
        pBS->GetFighterList(0, vecBattleFighter);
        stReport.wMonsterGroup = rID;
        stTeamReport.vecReport.push_back(stReport);
        stTeamReport.wTurns += pBS->GetRounds();
        if(stTeamReport.bySuc == 0) // 玩家失败，直接退出战斗
            break;
    }
    return true;
}

//接收：通告战斗结果
void CGame2CenterTeamC::OnRecv_NoticeTeamReport(
        UINT64 qwUsrID, //帐号ID
        UINT16 wDgnType, //副本类型
        const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    for(auto it = stTeamReport.vecReport.begin();it != stTeamReport.vecReport.end();it++)
    {
        const BattleReport& stReport = *(it);
        //先发战报
        pPlayer->SendPkg(g_BattleGSS.BuildPkg_BattleReportData(stReport.strBattle, stTeamReport.qwLeaderID,stTeamReport.qwLeaderFighter));
        //胜利，发奖励
        if(stReport.bySuc > 0)
        {
            /*组队副本怪物暂时不掉落
              TVecSItemGenInfo vecItem;
              TVecResource vecRes;
              CMonster::DropToPlayer(stReport.wMonsterGroup,*pPlayer,true,&vecItem,&vecRes);
              pPlayer->PendDrop(vecItems,vecRes);
              */

        }
    }
    UINT64 qwLastBattleID = 0;
    if(!stTeamReport.vecReport.empty())
    {
        qwLastBattleID = stTeamReport.vecReport.back().qwBattleID;
    }
    if(stTeamReport.bySuc > 0)//过关奖励
    {
        const SDgnInfo* pDgnInfo = CDungeonMgr::GetDgnInfo(wDgnType);
        if(pDgnInfo == NULL)
        {
            LOG_CRI <<" Can Not Find Dgn";
        }
        else
        {
            std::vector<SItemGenInfo>vecItems;
            TVecResource vecRes;
            TVecINT32 vecParam;
            vecParam.push_back(wDgnType);

            if(pPlayer->GetDgnPkg().PlayerCompleteDgn(wDgnType,0))
            {
                RoleDgnInfo* pInfo =  pPlayer->GetDgnPkg().GetPlayerDgnInfoByType(wDgnType);
                if(pInfo)
                    vecParam.push_back(pInfo->dwCompleteTimes);
                if (!dwRewardRate)
                    dwRewardRate = 10000;
                CDungeonMgr::AwardToPlayer(*pDgnInfo,0,*pPlayer,true,&vecItems,&vecRes, dwRewardRate);
                pPlayer->PendDrop(vecItems,vecRes,PendDgn);
            }
            else
            {
                vecParam.push_back(0);
            }
            pPlayer->SendPkg(g_DungeonProtS.BuildPkg_NotifyDgnAward(0, wDgnType,qwLastBattleID,0,vecItems,vecRes));
            pPlayer->OnEvent(eEventType_TeamBattleVictory,vecParam);
        }

    }
    pPlayer->SendPkg(g_DungeonProtS.BuildPkg_TeamBattleResult(wDgnType,stTeamReport.bySuc));

}

void CGame2CenterTeamC::SyncBeautyInfo(UINT64 qwUsrID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(NULL == pPlayer || !pPlayer->IsInTeam())
        return ;

    NTeamGS::TVecTeamFighter vecFighter;
    // 美女
    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if (pBeautyMgr)
    {
        TVecBattleFighterPtr vecBattleFighter;
        pBeautyMgr->GetBattleFighters(vecBattleFighter);
        for (auto& pFighter : vecBattleFighter)
        {
            if (!pFighter)
                continue;
            NTeamGS::BeautyFighterPtr pBeauty(new NTeamGS::BeautyFighter);
            SBeautyFeaturePtr pFeature(new SBeautyFeature);
            pFeature->wBeautyID     = pFighter->GetID();
            pBeauty->pFeature       = pFeature;
            pBeauty->byPos          = IBattleFighter::GetBeautyPos();
            pBeauty->wFighterID     = pFighter->GetID();
            pBeauty->dwFighterPower = pPlayer->GetFighterManager()->GetBeautyBattlePoint();
            vecFighter.push_back(pBeauty);
        }
    }
        Send_SynTeamAddBeauty(qwUsrID,vecFighter);
}

void CGame2CenterTeamC::UpFighter2Center(UINT64 qwUsrID,UINT64 qwFighterID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(NULL == pPlayer || !pPlayer->IsInTeam())
    {
        return ;
    }
    NTeamGS::CommonFighterPtr pComm = GetTeamFighterByID(pPlayer,qwFighterID);
    if(pComm != NULL)
    {
        NTeamGS::TVecTeamFighter vecFighter;
        vecFighter.push_back(pComm);
        Send_SynTeamFighter(qwUsrID,vecFighter);

    }
}

CGame2CenterTeamC g_Game2CenterTeamC;

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

