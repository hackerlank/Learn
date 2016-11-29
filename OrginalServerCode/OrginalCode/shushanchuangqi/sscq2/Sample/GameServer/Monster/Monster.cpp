#include "stdafx.h"

#include "Protocols.h"
#include "MonsterMgr.h"
#include "Map.h"
#include "User.h"
#include "ItemMgr.h"
#include "GameServerSysMail.h"
#include "Loot.h"
#include "TaskPkg.h"
#include "Task.h"
#include "SysMsgDefine.h"
#include "FighterMgr.h"
#include "Battle.h"
#include "ManagerMonsterAI.h"
#include "PlayerDgn.h"
#include "MapMgr.h"
#include "FighterManager.h"
#include "WorldBoss.h"
#include "HeroFighter.h"
#include "Random.h"
#include "GUIDMgr.h"

CMonster::~CMonster()
{
    LOG_INF << "Monster destroy"; 
    CMonsterAIPtr  pAI = GetAI();
    if(pAI != NULL)
    {
        g_MonsterAIManager.DestroyMonsterAI(pAI);
        pAI = NULL;
    }  
}

CDungeonPtr CMonster::GetDgnPtr()
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL)
    {
        return NULL;
    }
    CDungeonPtr pDgn = pMap->GetDungeon();
    return pDgn;
}

void CMonster::SetDir(float fDir)
{
    if(_fDir != fDir)
    {
        CMonsterAIPtr  pAI = GetAI(); 
        if(pAI)
        {
            pAI->SetPreDir(_fDir);
        }

    }
    return CBaseObj::SetDir(fDir);
}

bool CMonster::SetMonsterID(UINT16 wMonsterID)
{
    SFighterPropCFG* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(wMonsterID);
    if(pFighterPropCFG == NULL)
        return false;
    _wMonsterID = wMonsterID;
#ifdef _DEBUG
    if(_pFighterPropCFG != NULL)
        assert(_pFighterPropCFG->_Job == pFighterPropCFG->_Job);
#endif
    _pFighterPropCFG = pFighterPropCFG;
    SetJob(pFighterPropCFG->_Job);
    SetName(pFighterPropCFG->_Name);
    SetLevel(pFighterPropCFG->_Level);

    return true;
}

SFighterPropCFG& CMonster::GetFighterPropCfg()
{
    if(_pFighterPropCFG != NULL && _pFighterPropCFG->_ID == _wMonsterID)
        return *_pFighterPropCFG;
    _pFighterPropCFG = CFighterMgr::GetFighterPropCfg(_wMonsterID);
    if(_pFighterPropCFG == NULL)
    {
        LOG_CRI << "_pFighterPropCFG is NULL! MonsterID: " << _wMonsterID;
        DebugBreak();
        static SFighterPropCFG oFighterPropCFG;
        return oFighterPropCFG;
    }
    return *_pFighterPropCFG;
}

void CMonster::SetMonsterVal(UINT32 dwKey, const string& strVal)
{
    _mapKey2Val[dwKey] = strVal;
}

bool CMonster::GetMonsterVal(UINT32 dwKey, string& strVal)
{
    auto it = _mapKey2Val.find(dwKey);
    if(it == _mapKey2Val.end())
        return false;
    strVal = it->second;
    return true;
}

void CMonster::ClearMonsterVal()
{
    _mapKey2Val.clear();
}

void CMonster::GetMonsterAppear(SMonsterAppear& rMonsterAppear)
{
    rMonsterAppear.wMonsterID = GetFighterPropCfg()._ID;
    rMonsterAppear.strName = _strName;
    rMonsterAppear.byLevel = GetLevel();
    rMonsterAppear.wGroup = _wGroupID; 
    rMonsterAppear.dwSpeed = Speed();
    SMonsterFeaturePtr pMonsterFeature(new SMonsterFeature);
    if (pMonsterFeature)
        pMonsterFeature->wMonsterID = rMonsterAppear.wMonsterID;
    rMonsterAppear.pFeature = dynamic_pointer_cast<SFeatureBase>(pMonsterFeature);
    CMonsterAIPtr pAI = GetAI();
    if(pAI != NULL)
    {
        rMonsterAppear.bySight =  pAI->GetSightRadius();
        rMonsterAppear.bySightAngle = pAI->GetAICfg().SightAngle;
        rMonsterAppear.byFindEnemy = pAI->GetFightTarget() == NULL ? 0 :1;
    }

    TVecBuffInfo rvecBuffInfo; 
    GetAllBuffData(pMonsterFeature->vecBuffID,rvecBuffInfo); 

}

void CMonster::Disappear()
{
    CGameMapPtr pMap = GetMap();

    if(pMap != NULL)
    {
        pMap->MonsterDisappear(*this, true);
    }
    else
    {
        CMonsterMgr::DestroyMonster(ToThisPtr(this));
    }

}

void CMonster::DropToPlayer(UINT16 wGroupId,CPlayer& rPlayer,bool bIsAppend,std::vector<SItemGenInfo>* pvecItems ,TVecResource * pvecRes)
{
    CPack& oPack = rPlayer.GetUser().GetPack();
    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(wGroupId);
    std::vector<SItemGenInfo> vecMailInfo;
    TVecResource vecRes;
    std::vector<SItemGenInfo> vecItems;
    if(pMstGroup != NULL && !pMstGroup->vecDropID.empty())
    {
        for (auto & rDropID : pMstGroup->vecDropID)
        {
            LOOT.Roll(rDropID, vecItems,vecRes);
            if(!vecItems.empty())
            {
                if(!oPack.CanAddItem(vecItems))
                {
                    for(size_t i = 0; i !=  vecItems.size();i++)
                    {
                        vecMailInfo.push_back(vecItems[i]);
                    }
                }
                else
                {
                    if(!bIsAppend)
                        oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_MonsterDrop);
                    else
                        oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_MonsterDrop,true,false);
                }
            }
        }
    }

    if( NULL != pvecItems)
    {
        for(auto & rInfo : vecItems)
        {
            pvecItems->push_back(rInfo);
        }
    }

    if(pMstGroup->_uExp != 0)
    {
        SResource stRes;
        stRes._eRes = EMONEY_EXP;
        stRes._dwValue = pMstGroup->_uExp;
        vecRes.push_back(stRes);
    }

    if(!vecRes.empty()&&!bIsAppend)
        CStore::AddResource(rPlayer.GetUser(),vecRes,NLogDataDefine::ItemFrom_MonsterDrop);

    if(NULL != pvecRes)
    {
        for(auto iter =vecRes.begin();iter != vecRes.end();iter++)
        {
            pvecRes->push_back(*iter);
        }
    }

    if(!vecMailInfo.empty())
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
        //发送邮件
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_MONSTERDROP;
        stBody.vecParam.push_back(pMstGroup->_Name);
        TVecUINT64 vecTargets;
        vecTargets.push_back(rPlayer.GetUser().GetUserID());
        GameServerSysMail::SendSysMail(SEND_MONSTERDROP,TITLE_MONSTERDROP,stBody,vecTargets,&vecMailInfo);
    }

    if(!bIsAppend)
    {
        //add event
        rPlayer.GetUser().GetTaskPkg().OnKillMonster(wGroupId);
        CDungeonPtr pDgn = rPlayer.GetDgn();
        if(pDgn)
        {

            TVecINT32 vecData;
            vecData.push_back(1);
            rPlayer.GetEventMgr()->OnEvent(eEventType_DungeonBattleWin,vecData);
        }
    }


    //task 
    //任务掉落
    TVecItemGenInfo vecTaskItem;
    TMapTask2Drop* pMapTask2Drop = CMonsterMgr::GetTaskDropMap(wGroupId);
    if( NULL != pMapTask2Drop)
    {
        for(auto it = pMapTask2Drop->begin(); it != pMapTask2Drop->end(); ++it)
        {
            UINT16 wTaskID = it->first;
            TVecTaskDropInfo& rVecDropInfo = it->second;
            CTaskPtr pTask = rPlayer.GetUser().GetTaskPkg().FindTask(wTaskID);
            if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
            {
                for(size_t i = 0; i < rVecDropInfo.size(); ++i)
                {
                    STaskDropCFG& rDropCfg = rVecDropInfo[i];
                    if(rDropCfg._DropRate >= (UINT32)CRandom::RandInt(1, GAME_RANDOM_PERCENT))
                    {
                        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(rDropCfg._ItemID);
                        if(NULL != pItemInfo)
                        {
                            SItemGenInfo oGenItem;
                            oGenItem.wItemID = rDropCfg._ItemID;
                            oGenItem.dwCount = 1;
                            oGenItem.eBindType = eBindGet;
                            vecTaskItem.push_back(oGenItem);
                        }
                        else
                            LOG_CRI << "Create Item " << rDropCfg._ItemID << " fails!";
                    }
                }
            }
        }
    }

    if(!oPack.CanAddItem(vecTaskItem))//任务物品不发邮件
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgPackFullErr));
    else
    {
        oPack.AddItem(vecTaskItem,NLogDataDefine::ItemFrom_MonsterDrop,true,false);
        for(auto it = vecTaskItem.begin(); it != vecTaskItem.end();it++)
        {
            vecItems.push_back(*it);
        }
    }

    //将结果存到数据库
    if(bIsAppend)
    {
        rPlayer.PendDrop(vecItems,vecRes,PendBattle);
        rPlayer.PendParam(PendBattle,wGroupId,0);
    }
}

void CMonster::DropToPlayer(UINT16 wGroupId, std::vector<SItemGenInfo>& pvecItems, TVecResource& pvecRes)
{
    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(wGroupId);
    
    if(pMstGroup != NULL && !pMstGroup->vecDropID.empty())
    {
        for (auto iter=pMstGroup->vecDropID.begin(); iter!=pMstGroup->vecDropID.end(); iter++)
        {
            UINT32 dwDropId = (*iter); 
            LOOT.Roll(dwDropId, pvecItems, pvecRes);
        }
    }
}

void CMonster::OnDrop(CCreature& rKiller,UINT16 wGroup,string &strReport)
{
    if(CGUIDMgr::GetType(rKiller.GetCreatureID()) != GUID_ROLE)
        return;

    string &strPreBattle = strReport;
    CInArchive iar(strPreBattle);
    SBattleReport stPreBattle;
    iar >> stPreBattle;
    TVecItemGenInfo &vecItems = stPreBattle.vecItem;
    TVecResource &vecRes = stPreBattle.vecResSource;
    //掉落
    CPlayer& rPlayer = dynamic_cast<CPlayer&>(rKiller);
    DropToPlayer(wGroup,rPlayer,true,&vecItems,&vecRes);

    strPreBattle.clear();
    COutArchive oar(strPreBattle);
    oar << stPreBattle;


}

void CMonster::OnDie(CCreature& rKiller)
{
    CCreature::OnDie(rKiller);
    Disappear();
}

void CMonster::OnKill(CCreature& rTarget)
{
    CCreature::OnKill(rTarget);
}

UINT8 CMonster::GetMonsterLevelByGroupID(UINT16 wGroupID)
{
    const SMonsterGroupCFGEx* pGroup = CMonsterMgr::GetMonsterGroup(wGroupID);
    if( NULL == pGroup )
    {
        return 0;
    }
    SFighterPropCFGEx* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(pGroup->_MainMonster);
    if(NULL == pFighterPropCFG)
    {
        return 0;
    }
    return pFighterPropCFG->_Level;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleFighterListByGroupID
//  Description:  根据组名获得战斗对象列表
// =====================================================================================
UINT64 CMonster::GetBattleFighterListByGroupID(vector<TVecBattleFighterPtr>& vecvecBattleFighter, UINT16 wGroupID, UINT64 qwDefenseID, 
        TVecBattleFighterPtr& vecBattleFighterOther, CCreature* pCreature/*=NULL*/)
{
    UINT64 qwInstID = qwDefenseID;
    const SMonsterGroupCFGEx* pGroup = CMonsterMgr::GetMonsterGroup(wGroupID);
    if( NULL == pGroup )
        return 0;

    TVecUINT16 vecGroupID;
    vecGroupID.push_back(wGroupID);

    vecGroupID.insert(vecGroupID.end(), pGroup->vecMonsterID.begin(), pGroup->vecMonsterID.end());

    for(auto& rID : vecGroupID)
    {
        const SMonsterGroupCFGEx* pGroup = CMonsterMgr::GetMonsterGroup(rID);
        if( NULL == pGroup )
            continue;

        qwDefenseID = qwInstID + 1;
        TVecBattleFighterPtr vecBattleFighter;

        // 生成对应的战斗对象放入自己一方
        for (auto & rPos : pGroup->vecFighters)
        {
            UINT64 qwTmpID = 0;
            if (rPos.wMonsterID == pGroup->_MainMonster)
                qwTmpID = qwInstID;
            else
                qwTmpID = qwDefenseID ++;
            IBattleFighterPtr pBattleFighter = ToBattleFighter(rPos.wMonsterID, rPos.byPos, qwTmpID, pCreature);
            if (pBattleFighter)
                vecBattleFighter.push_back(pBattleFighter);
        }

        // 给对面的队伍增加额外成员
        for (auto & rPos : pGroup->vecAddFighters)
        {
            IBattleFighterPtr pBattleFighter = ToBattleFighter(rPos.wMonsterID, rPos.byPos, qwDefenseID ++, pCreature);
            if (pBattleFighter)
            {
                bool bSame = false;
                for (auto& pFighter : vecBattleFighterOther)
                {
                    if (pFighter && pFighter->GetPos() == pBattleFighter->GetPos())
                    {
                        bSame = true;
                        break;
                    }
                }
                if (!bSame)
                    vecBattleFighterOther.push_back(pBattleFighter);
            }
        }

        //  强插技能给对面
        for (auto & rPos : pGroup->vecAddSkills)
        {
            for (auto & pFighter : vecBattleFighterOther)
            {
                if (pFighter && 
                        ((rPos.wFighterID && pFighter->GetID() == rPos.wFighterID)
                         || (!rPos.wFighterID && pFighter->GetID() <= 8)))
                {
                    TVecUINT32 vecSkills;
                    vecSkills.push_back(CSkillMgr::Instance().GetSkillIDQualityLevel(rPos.dwSkillID, rPos.dwSkillLevel));
                    pFighter->PushMoreSkills(vecSkills);
                    break;
                }
            }
        }

        // 怪物阵灵
        IBattleFighterPtr pBattleFighter = ToBattleFighter(pGroup->wPetID, IBattleFighter::GetPetPos(), qwDefenseID ++, pCreature);
        if (pBattleFighter)
        {
            pBattleFighter->SetMaxHP(100);
            pBattleFighter->SetHP(100);
            vecBattleFighter.push_back(pBattleFighter);
        }
        vecvecBattleFighter.push_back(vecBattleFighter);
    }
    return qwInstID;
}		// -----  end of function GetBattleFighterListByGroupID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSceneFighter
//  Description:  获取该怪物对应的特定战斗场景
// =====================================================================================
IBattleFighterPtr CMonster::GetSceneFighter(UINT16 wMonsterID)
{
    const SMonsterGroupCFGEx* pGroup = CMonsterMgr::GetMonsterGroup(wMonsterID);
    UINT16 wMapID = pGroup->_FightMap;
    if (wMapID)
        return CMapMgr::ToBattleFighterWithFighterMapID(wMapID);
    return NULL;
}		// -----  end of function GetSceneFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ToBattleFighter
//  Description:  根据ID生成对应的战斗对象
// =====================================================================================
IBattleFighterPtr CMonster::ToBattleFighter(UINT16 wMonsterID, UINT8 byPos, UINT64 qwDefenseID, CCreature *pCreature /* = NULL */)
{
    SFighterPropCFGEx* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(wMonsterID);
    if(NULL == pFighterPropCFG)
        return NULL;

    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    CFighterPtr pFighter(new CFighter(wMonsterID,eFighterMonster, pCreature, qwDefenseID)); 
    if (!pFighter)
        return NULL;
    pFighter->SetPos(byPos);
    pBattleFighter = pFighter->ToBattleFighter(0, EBTMonster);

    return pBattleFighter;
}		// -----  end of function ToBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSceneFighter
//  Description:  根据怪物ID获取地图?(能获取么？)
// =====================================================================================
IBattleFighterPtr CMonster::GetSceneFighter()
{
    const SMonsterGroupCFGEx* pGroup = CMonsterMgr::GetMonsterGroup(_wGroupID);
    UINT16 wMapID = pGroup->_FightMap;
    if (wMapID)
        return CMapMgr::ToBattleFighterWithFighterMapID(wMapID);
    CGameMapPtr pMap = GetBornMap();
    if (pMap)
        return pMap->ToBattleFighter();
    return NULL;
}		// -----  end of function GetSceneFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleFighterList
//  Description:  获取该怪物的战斗对象列表
// =====================================================================================
UINT64 CMonster::GetBattleFighterList(vector<TVecBattleFighterPtr>& vecvecBattleFighter, UINT64 qwDefenseID, TVecBattleFighterPtr& vecBattleFighterOther)
{
    if(IsBufferDirty())
    {
        BufferRebuildAttr();
        SetBufferDirty(false);
    }

    UINT64 qwMainFighterID = GetBattleFighterListByGroupID(vecvecBattleFighter, _wGroupID, qwDefenseID, vecBattleFighterOther, this);
    ReadjustBattleFighterList(vecvecBattleFighter);
    return qwMainFighterID;
}		// -----  end of function GetBattleFighterList  ----- //

float CMonster::GetSpeedForWalker() const
{
    return (float)_dwSpeed/60;
}

CMonsterPtr CMonster::GetThisPtr()
{
    return dynamic_pointer_cast<CMonster>(shared_from_this());
}

void CMonster::OnAttacked(CCreature& rAttacker)
{
    CMonsterAIPtr pAI = GetAI();
    if(pAI != NULL)
    {
        pAI->OnAttacked(rAttacker);
    }
}

void CMonster::SetInPathFind(bool bFind)
{
    CMonsterAIPtr pAI = GetAI();
    if(pAI != NULL)
    {
        pAI->SetInPathFind(bFind);
    }
}

void CMonster::OnPathFound(TVecPoint& rVecPath)
{
    CMonsterAIPtr pAI = GetAI();
    if(pAI != NULL)
    {
        pAI->OnPathFound(rVecPath);
    }
}

void CMonster::CreateAI()
{
    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(_wGroupID);
    if(pMstGroup == NULL)
    {
        return ;
    }
    UINT16 wAIID = pMstGroup->_AI; 
    if(wAIID == 0)
    {
        return ;
    }
    _pAI = g_MonsterAIManager.CreateMonsterAI(*this,wAIID,GetPoint());

}

bool CMonster::CanFight(CCreature& rCreature)
{
    EGUIDType eType =  CGUIDMgr::GetType(rCreature.GetCreatureID());
    if(eType != GUID_ROLE)
        return false;
    CGameMapPtr pMap = GetMap();
    if(pMap != NULL && pMap->IsInSafeArea(rCreature.GetPoint()))
    {
        return false;
    }
    return CCreature::CanFight(rCreature);
}

bool CMonster::IsAttackable()
{
    return true;
}

// ===  FUNCTION  ======================================================================
//         Name:  FighterToOther
//  Description:  与另一个人开打
// =====================================================================================
bool CMonster::FighterToOther(CCreature& rTarget)
{
    // XXX: 目前只能怪和人打
    if (CGUIDMgr::GetType(rTarget.GetCreatureID() != GUID_ROLE))
        return false;

    CPlayer &rPlayer = static_cast<CPlayer&>(rTarget);
    bool bFullHP = true;
    if(GetBattleType())
    {
        rPlayer.SetBattleType((NBattleGS::EBattleType)(GetBattleType()));
        if(rPlayer.GetFighterManager())
            rPlayer.GetFighterManager()->SetDirty(eAttrGpBuffer);
    }
 
    if (IsWorldBoss())
    {
        static UINT32 eWorldBossDeadBufferID = 15; //死亡buffer
        if (!IsAttackable() 
                || rPlayer.HasBuff(eWorldBossDeadBufferID)) // 战斗CD
            return false;
        //bFullHP = false; 放到下面去了
        //设置boss战斗类型
        rPlayer.SetBattleType(EBWorldBoss);
        if(rPlayer.GetFighterManager())
            rPlayer.GetFighterManager()->SetDirty(eAttrGpBuffer);
    }

    CDungeonPtr pDgn = GetDgnPtr();

    // 副本怪
    if(pDgn)
    {
        if (!pDgn->CanAttackMonster(GetGroupID()) || rPlayer.IsDead())
            return false;

        if(rPlayer.IsBattleCD())
        {
            rPlayer.SendSysMsg(eMsgBattleCd);
            return false;
        }
    }

    rPlayer.SetBattleType(GetBattleType());

    rPlayer.GetWalker().Abort();
    rPlayer.RegenAllHP();

    TVecBattleFighterPtr vecBattleAttacker;
    UINT64 qwMainTargetID = rPlayer.GetBattleFighterList(vecBattleAttacker);
    if (!qwMainTargetID)
        return false;

    IBattleFighterPtr pScene = GetSceneFighter();
    if (!pScene)
        pScene = rPlayer.GetSceneFighter();

    vector<TVecBattleFighterPtr> vecvecBattleMonsters;
    LOG_WRN << "GetCreatureID() = " << GetCreatureID() << ".";
    UINT64 qwMainFighterID = GetBattleFighterList(vecvecBattleMonsters, GetCreatureID(), vecBattleAttacker);
    if (!qwMainFighterID || vecvecBattleMonsters.empty())
        return false;

    bool bPlayerWinned = true;
    UINT64* pNextBattleID = NULL;
    vector<SBattleReport> vecReport;
    vecReport.reserve(vecvecBattleMonsters.size());


    ResetNextBattleTime();

    UINT32 dwRounds = 0;
    UINT64 qwBattleID = 0;

    //世界boss特殊处理
    if(IsWorldBoss())
    {
        CWorldBoss *pBoss =(CWorldBoss *)this;
        //初始化boss血量攻击等
        pBoss->ReadjustBattleFighterList(vecvecBattleMonsters);
        bFullHP = false;
    }


    // 开始一场场战斗
    for (auto& vecMonster : vecvecBattleMonsters)
    {

        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
        pBS->PutFighters(0, qwMainTargetID,     rPlayer.GetLevel(), vecBattleAttacker,  rPlayer.GetCreatureID(), false);
        pBS->PutFighters(1, qwMainFighterID,    GetLevel(),            vecMonster,         GetCreatureID(),         bFullHP);

        bFullHP = true;

        pBS->PutScene(pScene);

        pBS->Start(EBTMonster);

        std::string strReport;
        pBS->GetReport(strReport);

        CInArchive iar(strReport);
        SBattleReport stReport;
        iar >> stReport;

        if (pNextBattleID)
            *pNextBattleID = pBS->GetBattleID();
        vecReport.push_back(stReport);

        if (!vecReport.empty())
            pNextBattleID = &vecReport.back().qwNextBattleID;


        vecBattleAttacker.clear();
        pBS->GetFighterList(0, vecBattleAttacker);
        dwRounds += pBS->GetRounds();
        qwBattleID = pBS->GetBattleID();

        if (IsWorldBoss()) // 世界boss
        {
            TVecBattleFighterPtr vecFighters; // XXX: 需要得到世界BOSS的血量
            pBS->GetFighterList(1, vecFighters);
            ((CWorldBoss *)this)->OnAttacked(rPlayer, vecFighters);
        }


        // 被怪物打死，直接结束战斗
        if(pBS->GetFinalWinner() != EBResultAttackWin)
        {
            bPlayerWinned = false;
            break;
        }
    }

    // 如果是战斗胜利，往最后一个战报塞入掉落物品
    if(!vecReport.empty() && bPlayerWinned)
    {
        SBattleReport& stPreBattle = vecReport.back();
        TVecItemGenInfo &vecItems = stPreBattle.vecItem;
        TVecResource &vecRes = stPreBattle.vecResSource;

        //掉落
        DropToPlayer(_wGroupID, rPlayer, true, &vecItems, &vecRes);
    }

    // 依次发送战报
    for (auto & rInfo : vecReport)
    {
        std::string strData;
        COutArchive oar(strData);
        oar << rInfo;

        rPlayer.SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strData, rPlayer.GetRoleID(), rPlayer.GetMainFighter()->GetID()));
    }

    // 玩家攻击副本怪物死亡
    if(!bPlayerWinned && pDgn)
        pDgn->OnPlayerDie(*this,rPlayer);

    if(pDgn)
    {
        switch (pDgn->GetDgnType())
        {
            case ePlayerDgn:
            case eGatherDgn:
                {
                    CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDgn);
                    pPlayerDgn->FightWithMonster(GetGroupID());
                    pPlayerDgn->AddAttackTurns(dwRounds);
                }
                break;
            default:
                break;
        }
        pDgn->SetBattleRouds(dwRounds);
        pDgn->SetReportID(qwBattleID);
        
    }

    // 玩家胜利
    if(bPlayerWinned)
    {  
        if(pDgn)
        {
            pDgn->SetBattleRouds(dwRounds);
            pDgn->OnMonsterDie(*this,rPlayer.GetRoleID(), qwBattleID);
        }
        OnDie(rPlayer);
        /*
        if (IsWorldBoss()) // 世界boss
        {
           this->OnKill(rPlayer);
        }
        */
    }



    // 重置玩家Buff属性
    rPlayer.SetBattleType(EBTINVALID);

    // 战斗CD
    rPlayer.SetBattleCD();

    //event

    if(pDgn&& rPlayer.GetFighterManager())
    {
        TVecINT32 vecParam;
        vecParam.push_back(GetGroupID());
        vecParam.push_back(bPlayerWinned);
        string strLog = rPlayer.GetFighterManager()->GetInfoLog();
        rPlayer.OnEvent(eEventType_DungeonVsMonster,vecParam,strLog);
        //LOG_INF<<"player info:"<<strLog;
        {
            TVecINT32 vecParam2;
            vecParam2.push_back(pDgn->GetDgnID());
            vecParam2.push_back(GetGroupID());
            vecParam2.push_back(rPlayer.GetBattlePoint());
            vecParam2.push_back(bPlayerWinned);
            ostringstream os;
            for(size_t i = 0; i < vecParam.size(); i++)
            {
                os<<vecParam[i];
                os<<",";
            }
            rPlayer.OnEvent(eEventType_DungeonVsMonster,vecParam,os.str());
        }

    }
    
    return true;
}		// -----  end of function FighterToOther  ----- //

bool CMonster::FighterToOther(CCreature& rTarget,bool &bPlayerWiner)
{
    // XXX: 目前只能怪和人打
    if (CGUIDMgr::GetType(rTarget.GetCreatureID() != GUID_ROLE))
        return false;
    CPlayer &rPlayer = static_cast<CPlayer&>(rTarget);
    bool bFullHP = true;
    if(GetBattleType())
    {
        rPlayer.SetBattleType((NBattleGS::EBattleType)(GetBattleType()));
        if(rPlayer.GetFighterManager())
            rPlayer.GetFighterManager()->SetDirty(eAttrGpBuffer);
    }
 
    if (IsWorldBoss())
    {
        static UINT32 eWorldBossDeadBufferID = 15; //死亡buffer
        if (!IsAttackable() 
                || rPlayer.HasBuff(eWorldBossDeadBufferID)) // 战斗CD
            return false;
        rPlayer.SetBattleType(EBWorldBoss);
        if(rPlayer.GetFighterManager())
            rPlayer.GetFighterManager()->SetDirty(eAttrGpBuffer);
    }
    CDungeonPtr pDgn = GetDgnPtr();
    // 副本怪
    if(pDgn)
    {
        if (!pDgn->CanAttackMonster(GetGroupID()) || rPlayer.IsDead())
            return false;
        if(rPlayer.IsBattleCD())
        {
            rPlayer.SendSysMsg(eMsgBattleCd);
            return false;
        }
    }
    rPlayer.SetBattleType(GetBattleType());
    rPlayer.GetWalker().Abort();
    rPlayer.RegenAllHP();

    TVecBattleFighterPtr vecBattleAttacker;
    UINT64 qwMainTargetID = rPlayer.GetBattleFighterList(vecBattleAttacker);
    if (!qwMainTargetID)
        return false;

    IBattleFighterPtr pScene = GetSceneFighter();
    if (!pScene)
        pScene = rPlayer.GetSceneFighter();

    vector<TVecBattleFighterPtr> vecvecBattleMonsters;
    LOG_WRN << "GetCreatureID() = " << GetCreatureID() << ".";
    UINT64 qwMainFighterID = GetBattleFighterList(vecvecBattleMonsters, GetCreatureID(), vecBattleAttacker);
    if (!qwMainFighterID || vecvecBattleMonsters.empty())
        return false;

    bool bPlayerWinned = true;
    UINT64* pNextBattleID = NULL;
    vector<SBattleReport> vecReport;
    vecReport.reserve(vecvecBattleMonsters.size());

    ResetNextBattleTime();

    UINT32 dwRounds = 0;
    UINT64 qwBattleID = 0;

    //世界boss特殊处理
    if(IsWorldBoss())
    {
        CWorldBoss *pBoss =(CWorldBoss *)this;
        //初始化boss血量攻击等
        pBoss->ReadjustBattleFighterList(vecvecBattleMonsters);
        bFullHP = false;
    }


    // 开始一场场战斗
    for (auto& vecMonster : vecvecBattleMonsters)
    {

        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
        pBS->PutFighters(0, qwMainTargetID,     rPlayer.GetLevel(), vecBattleAttacker,  rPlayer.GetCreatureID(), false);
        pBS->PutFighters(1, qwMainFighterID,    GetLevel(),            vecMonster,         GetCreatureID(),         bFullHP);

        bFullHP = true;

        pBS->PutScene(pScene);

        pBS->Start(EBTMonster);

        std::string strReport;
        pBS->GetReport(strReport);

        CInArchive iar(strReport);
        SBattleReport stReport;
        iar >> stReport;

        if (pNextBattleID)
            *pNextBattleID = pBS->GetBattleID();
        vecReport.push_back(stReport);

        if (!vecReport.empty())
            pNextBattleID = &vecReport.back().qwNextBattleID;


        vecBattleAttacker.clear();
        pBS->GetFighterList(0, vecBattleAttacker);
        dwRounds += pBS->GetRounds();
        qwBattleID = pBS->GetBattleID();

        if (IsWorldBoss()) // 世界boss
        {
            TVecBattleFighterPtr vecFighters; // XXX: 需要得到世界BOSS的血量
            pBS->GetFighterList(1, vecFighters);
            ((CWorldBoss *)this)->OnAttacked(rPlayer, vecFighters);
        }


        // 被怪物打死，直接结束战斗
        if(pBS->GetFinalWinner() != EBResultAttackWin)
        {
            bPlayerWinned = false;
            break;
        }
    }

    // 如果是战斗胜利，往最后一个战报塞入掉落物品
    if(!vecReport.empty() && bPlayerWinned)
    {
        SBattleReport& stPreBattle = vecReport.back();
        TVecItemGenInfo &vecItems = stPreBattle.vecItem;
        TVecResource &vecRes = stPreBattle.vecResSource;

        //掉落
        DropToPlayer(_wGroupID, rPlayer, true, &vecItems, &vecRes);
    }

    // 依次发送战报
    for (auto & rInfo : vecReport)
    {
        std::string strData;
        COutArchive oar(strData);
        oar << rInfo;

        rPlayer.SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strData, rPlayer.GetRoleID(), rPlayer.GetMainFighter()->GetID()));
    }

    // 玩家攻击副本怪物死亡
    if(!bPlayerWinned && pDgn)
        pDgn->OnPlayerDie(*this,rPlayer);

    if(pDgn)
    {
        switch (pDgn->GetDgnType())
        {
            case ePlayerDgn:
            case eGatherDgn:
                {
                    CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDgn);
                    pPlayerDgn->FightWithMonster(GetGroupID());
                    pPlayerDgn->AddAttackTurns(dwRounds);
                }
                break;
            default:
                break;
        }
        pDgn->SetBattleRouds(dwRounds);
        pDgn->SetReportID(qwBattleID);
        
    }

    // 玩家胜利
    if(bPlayerWinned)
    {  
        if(pDgn)
        {
            pDgn->SetBattleRouds(dwRounds);
            pDgn->OnMonsterDie(*this,rPlayer.GetRoleID(), qwBattleID);
        }
        OnDie(rPlayer);
        /*
        if (IsWorldBoss()) // 世界boss
        {
           this->OnKill(rPlayer);
        }
        */
    }



    // 重置玩家Buff属性
    rPlayer.SetBattleType(EBTINVALID);

    // 战斗CD
    rPlayer.SetBattleCD();

    //event

    if(pDgn&& rPlayer.GetFighterManager())
    {
        TVecINT32 vecParam;
        vecParam.push_back(GetGroupID());
        vecParam.push_back(bPlayerWinned);
        string strLog = rPlayer.GetFighterManager()->GetInfoLog();
        rPlayer.OnEvent(eEventType_DungeonVsMonster,vecParam,strLog);
        //LOG_INF<<"player info:"<<strLog;
        {
            TVecINT32 vecParam2;
            vecParam2.push_back(pDgn->GetDgnID());
            vecParam2.push_back(GetGroupID());
            vecParam2.push_back(rPlayer.GetBattlePoint());
            vecParam2.push_back(bPlayerWinned);
            ostringstream os;
            for(size_t i = 0; i < vecParam.size(); i++)
            {
                os<<vecParam[i];
                os<<",";
            }
            rPlayer.OnEvent(eEventType_DungeonVsMonster,vecParam,os.str());
        }

    }
    
    bPlayerWiner = bPlayerWinned;
   
    return true;
}
bool CMonster::IsDead() const
{
    CMonsterAIPtr pAI = _pAI.lock();
    if(pAI)
        return  pAI->IsDead();
    return false;
}

void CMonster::OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo)
{
}

void CMonster::SetGroupID(UINT16 wGroupID) 
{ 
    _wGroupID = wGroupID; 
    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(_wGroupID); 
    if(pMstGroup && pMstGroup->_FightType)
    {
        _eBattleType = static_cast<EBattleType>(pMstGroup->_FightType);
    }
} 

CMonsterAIPtr CMonster::GetAI()
{
    return _pAI.lock();
}

