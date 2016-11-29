#include "BattleSimulator.h"

#include "BattleFighter.h"
#include "MachineState.h"
#include "Archive.h"
#include "BattleReportMgr.h"
#include "BattleDebugger.h"

#ifdef BATTLE_DEBUG
#include "Directory.h"
#endif
#include "RTime.h"

namespace NBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CBattleSimulator
//  Description:  构造函数
// =====================================================================================
CBattleSimulator::CBattleSimulator(UINT64 qwGUID)
{
    _oReport.qwBattleID = qwGUID;
    _oReport.wSceneID = 103;
    _oReport.by1Vs1 = 1;

#ifdef BATTLE_DEBUG
    g_BattleLog.Stop();
    g_qwDebuggerID = qwGUID;
    ostringstream ostrName;
    ostrName << _oReport.qwBattleID << ".txt";

    CreateDirectory("BattleLog");
    g_strDeuggerFile = ostrName.str();

    g_BattleLog.OpenConsole();
    ostrName.str("");
    ostrName << "BattleLog/" << _oReport.qwBattleID << ".txt";
    if(!g_BattleLog.OpenLog(ostrName.str().c_str()))
        LOG_CRI << "OpenBattleLog fails!";
    g_BattleLog.Start();
#endif // #ifdef BATTLE_DEBUG
}		// -----  end of function CBattleSimulator  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleSimulator
//  Description:  析构函数
// =====================================================================================
CBattleSimulator::~CBattleSimulator()
{
#ifdef BATTLE_DEBUG
    g_BattleLog.Stop();
    g_qwDebuggerID = 0;
    CreateDirectory("BattleLog");
    ostringstream ostrName;
    ostrName << _oReport.qwBattleID << "Common.txt";
    g_strDeuggerFile = ostrName.str();
    g_BattleLog.OpenConsole();
    ostrName.str("");
    ostrName << "BattleLog/" << _oReport.qwBattleID << ".txt";
    if(!g_BattleLog.OpenLog(ostrName.str().c_str()))
        LOG_CRI << "OpenBattleLog fails!";
    g_BattleLog.Start();
#endif // #ifdef BATTLE_DEBUG
}		// -----  end of function ~CBattleSimulator  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFinalWinner
//  Description:  返回最后的获胜者
// =====================================================================================
EBattleResult CBattleSimulator::GetFinalWinner() const
{
    return _oReport.eResult;
}		// -----  end of function GetFinalWinner  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTurns
//  Description:  获得战斗总出手数
// =====================================================================================
UINT32 CBattleSimulator::GetTurns() const
{
    return _oField.GetTurns();;
}		// -----  end of function GetTurns  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRounds
//  Description:  获得战斗总回合数
// =====================================================================================
UINT32 CBattleSimulator::GetRounds() const
{
    return _oField.GetRounds();;
}		// -----  end of function GetRounds  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetReport
//  Description:  获取战报数据
// =====================================================================================
void CBattleSimulator::GetReport(std::string& strReport) const
{
    COutArchive oar(strReport);
    oar << _oReport;
}		// -----  end of function GetReport  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleID
//  Description:  获取战报ID
// =====================================================================================
UINT64 CBattleSimulator::GetBattleID() const
{
    return _oReport.qwBattleID;
}		// -----  end of function GetBattleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsAttackDead
//  Description: 是否攻击者真的没血死了 
// =====================================================================================
bool CBattleSimulator::IsAttackDead() const
{
    if (_vecTeams.size() < 1)
        return true;
    SBattleTeamPtr pTeam = _vecTeams[0];
    if (!pTeam)
        return true;
    const TVecBattleFighterSPtr& rvecFighter = pTeam->_vecFighter;
    for (auto & pFighter : rvecFighter)
    {
        if (pFighter && pFighter->GetHP() != 0)
            return false;
    }
    return true;
}		// -----  end of function IsAttackDead  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsDefenseDead
//  Description:  是否防守者真的没血死了
// =====================================================================================
bool CBattleSimulator::IsDefenseDead() const
{
    if (_vecTeams.size() < 2)
        return true;
    SBattleTeamPtr pTeam = _vecTeams[1];
    if (!pTeam)
        return true;
    const TVecBattleFighterSPtr& rvecFighter = pTeam->_vecFighter;
    for (auto & pFighter : rvecFighter)
    {
        if (pFighter && pFighter->GetHP() != 0)
            return false;
    }
    return true;
}		// -----  end of function IsDefenseDead  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFighterList
//  Description:  获取战斗后的战斗对象供外部使用
// =====================================================================================
bool CBattleSimulator::GetFighterList(UINT8 bySide, ::TVecBattleFighterPtr& rvecBattleFighter)
{
    if (_vecTeams.size() <= bySide)
        return false;
    SBattleTeamPtr pTeam = _vecTeams[bySide];
    if (!pTeam)
        return false;
    for (auto& pFighter : pTeam->_vecFighter)
    {
        if (pFighter)
            rvecBattleFighter.push_back(dynamic_pointer_cast<IBattleFighter>(pFighter));
    }
    return true;
}		// -----  end of function GetFighterList  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PutFighters
//  Description:  放入玩家散仙
// =====================================================================================
void CBattleSimulator::PutFighters(UINT8 bySide, UINT64 qwLeaderID, UINT16 wLevel, 
        ::TVecBattleFighterPtr& rvecBattleFighter, UINT64 qwInstID /* = 0 */, bool bFullHP /* = true */,
        SFeatureBasePtr pMainFeature /* = NULL */)
{
    if(bySide > eBSideMax)
        return;

    SBattleTeamPtr pTeam(new SBattleTeam);
    pTeam->_qwInstID     = qwInstID;
    pTeam->_qwLeaderID   = qwLeaderID;
    pTeam->_wLevel       = wLevel;
    pTeam->_byGroupID    = bySide;

    for (auto & pFighter : rvecBattleFighter)
    {
        if (!pFighter)
            continue;
        CBattleFighterPtr pBattleFighter = dynamic_pointer_cast<CBattleFighter>(pFighter);
        if (bFullHP) // 根据战斗需求回满血量
            pBattleFighter->RegenAllHP();
        pBattleFighter->SetSide(bySide);

        // 主将
        if (pBattleFighter->GetInstID() == qwLeaderID)
            pTeam->_pFeature = pBattleFighter->GetFeature();

        pTeam->_vecFighter.push_back(pBattleFighter);
    }
    if (pMainFeature)
        pTeam->_pFeature = pMainFeature;

    if (pTeam->_vecFighter.empty())
    {
        LOG_CRI << "pTeam->Fighter Empty.";
        return;
    }
    if (_vecTeams.size() <= bySide)
        _vecTeams.resize(bySide + 1);
    _vecTeams[bySide] = pTeam;
}		// -----  end of function PutFighters  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PutScene
//  Description:  放入场景对象
// =====================================================================================
void CBattleSimulator::PutScene(IBattleFighterPtr pFighter)
{
    if (!pFighter)
        return;
    CBattleFighterPtr pFighterReal = dynamic_pointer_cast<CBattleFighter>(pFighter);
    _pScene = pFighterReal;
    SFeatureBasePtr pFeature = pFighterReal->GetFeature();
    SFieldFeaturePtr pFieldFeature = dynamic_pointer_cast<SFieldFeature>(pFeature);
    _oReport.wSceneID = pFieldFeature->wSceneID;
}		// -----  end of function PutScene  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Start
//  Description:  开始战斗
// =====================================================================================
void CBattleSimulator::Start(EBattleType eType)
{
    if (_vecTeams.size() < 2)
        return;
    if (!_vecTeams[0] || !_vecTeams[1])
        return;

    _oReport.eType = eType;

    InitField();

#ifdef BATTLE_DEBUG
    timediff_t tBegin = RTime().usecs();
#endif

    StartOneBattle();
    
#ifdef BATTLE_DEBUG
    timediff_t tEnd = RTime().usecs();

    UINT64 dwTime = tEnd - tBegin;
    LOG_INF << "OneBattle(" << dwTime << ").";
#endif

    CalcWinner();

    SaveReport();

    ResetBattleFighterBuff();
    DumpBattleProtocol();
}		// -----  end of function Start  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SaveReport
//  Description:  保存战报
// =====================================================================================
void CBattleSimulator::SaveReport ()
{
    string strReport;
    COutArchive oar(strReport);
    oar << _oReport;
    CBattleReportMgr::Instance().AddReport(_oReport.qwBattleID, strReport, true); // XXX: 这里默认保存所有战报
    BATTLE_DBG << "BattleID: " << _oReport.qwBattleID << ".";
}		// -----  end of function SaveReport  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  DumpBattleProtocol
//  Description:  输出战斗协议数据(当且仅当Debug版本并且开启协议xml格式的时候有效)
// =====================================================================================
void CBattleSimulator::DumpBattleProtocol ()
{
#ifdef BATTLE_DEBUG
#ifdef PROT_USE_XML
    CreateDirectory("BattleProtocol");
    ostringstream ostrName;
    ostrName << _oReport.qwBattleID << ".xml";
    TiXmlElement* pElement = new TiXmlElement(ostrName.str().c_str());
    if(pElement)
    {
        if(ToXML(_oReport, *pElement))
        {
            TiXmlDocument doc;
            TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
            if(pDecl)
            {
                doc.LinkEndChild(pDecl);
                doc.LinkEndChild(pElement);
                ostrName.str("");
                ostrName << "BattleProtocol/" << _oReport.qwBattleID << ".xml";
                doc.SaveFile(ostrName.str().c_str());
            }
        }
    }
#endif // #ifdef PROT_USE_XML
#endif // #ifdef BATTLE_DEBUG
}		// -----  end of function DumpBattleProtocol  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitField
//  Description:  将队伍中的战斗对象初始化到场地
// =====================================================================================
void CBattleSimulator::InitField()
{
    _oField.SetObject(_pScene, eBFDScene);

    TSetUINT16 setSummonFighterID;    // 召唤物的ID

    InitFieldSideInfo(0, setSummonFighterID);
    InitFieldSideInfo(1, setSummonFighterID);

    InitSummonInfo(setSummonFighterID);
}		// -----  end of function InitField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFieldSideInfo
//  Description:  初始化一边的场地信息
// =====================================================================================
void CBattleSimulator::InitFieldSideInfo(UINT8 bySide, TSetUINT16& rsetSummonFighterID)
{
    if (_vecTeams.size() <= bySide)
        return;

    SBattleTeamPtr pTeam = _vecTeams[bySide];

    if (!pTeam)
        return;

    if(pTeam->_vecFighter.empty())
    {
        LOG_CRI << "Side(" << (UINT32) bySide << ") team fighter list is empty";
        return;
    }

    SBattleGroup sGroup;
    sGroup.byGroupID       = pTeam->_byGroupID;
    sGroup.qwCreatrueID    = pTeam->_qwInstID;
    sGroup.qwLeaderID      = pTeam->_qwLeaderID;
    sGroup.wLevel          = pTeam->_wLevel;

    // 更新战斗头像
    if (pTeam->_pFeature)
        sGroup.pMainFeature = pTeam->_pFeature;
    else
    {
        SMonsterFeaturePtr pMonsterFeature(new SMonsterFeature());
        pMonsterFeature->wMonsterID = 1;
        sGroup.pMainFeature = dynamic_pointer_cast<SFeatureBase>(pMonsterFeature);
    }

    UINT8 byIndex = 0;
    for (auto& pFighter : pTeam->_vecFighter)
    {

#ifdef _DEBUG
        // 调试模式主将不出战
        if (pFighter && pFighter->GetID() < 8 && IsNoMain())
            pFighter->SetHP(0);
#endif
        // 放入战斗场地
        _oField.SetObject(pFighter, eBFDNormal);

        // 可能的召唤物ID
        pFighter->GetSummonFighterID(rsetSummonFighterID);

        // 组合技能 
        const TVecTeamSkillInfo& rvecTeamSkillInfo = pFighter->GetCombineSkill(byIndex);
        sGroup.vecCombineSkillInfo.insert(sGroup.vecCombineSkillInfo.end(), rvecTeamSkillInfo.begin(), rvecTeamSkillInfo.end());
        for (auto& rInfo : rvecTeamSkillInfo)
        {
            _oField.PushCombineSkill(bySide, pFighter->GetTeamID(), rInfo.byIndex, rInfo.dwSkillID);
        }

        // 战斗对象序列化给协议用
        SBattleFighter sBf;
        pFighter->GetBattleFighterInfo(sBf);
        sGroup.vFighters.push_back(sBf);

        // 活人或者特殊战斗对象算战斗力
        if (pFighter->GetPos() >= MAX_POS || pFighter->GetHP())
            sGroup.dwBattlePoint += pFighter->GetBattlePoint();
    }

    // 死人不算连携技能
    TVecUINT8 vecCombineIndex;
    for (auto& pFighter : pTeam->_vecFighter)
    {
        if (pFighter->GetPos() < MAX_POS &&  !pFighter->GetHP())
            _oField.RemoveCombineFighter(&(*pFighter), vecCombineIndex);
    }

    if (bySide == 0)
        _oReport.vAGroups.push_back(sGroup);
    else
        _oReport.vBGroups.push_back(sGroup);
}		// -----  end of function InitFieldSideInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitSummonInfo
//  Description:  初始化所有需要召唤出来的战斗对象到战斗场地和协议中
// =====================================================================================
void CBattleSimulator::InitSummonInfo(TSetUINT16& rsetSummonFighterID)
{
    auto it = rsetSummonFighterID.begin();
    while (it != rsetSummonFighterID.end())
    {
        if (!_oField.GetSummonFighter(*it))
        {
            if (!CBattleFighter::_funCreateFromID)
            {
                LOG_CRI << "_funCreateFromID == NULL.";
                break;
            }
            CBattleFighterPtr pFighter = dynamic_pointer_cast<CBattleFighter>(CBattleFighter::_funCreateFromID(*it));
            if (pFighter)
            {
                TSetUINT16 setNewFighterID;
                pFighter->GetSummonFighterID(setNewFighterID);
                _oField.SetObject(pFighter, eBFDSummon);
                for (auto & rID : setNewFighterID)
                {
                    if (!_oField.GetSummonFighter(rID))
                        rsetSummonFighterID.insert(rID);
                }
                SBattleFighter sBf;
                pFighter->GetBattleFighterInfo(sBf);
                _oReport.vSummons.push_back(sBf);
            }
        }
        rsetSummonFighterID.erase(it);
        it = rsetSummonFighterID.begin();
    }
}		// -----  end of function InitSummonInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetBattleFighterBuff
//  Description:  重置玩家Buff
// =====================================================================================
void CBattleSimulator::ResetBattleFighterBuff()
{
    _oField.ResetBattleFighterBuff();
}

// ===  FUNCTION  ======================================================================
//         Name:  EnterRound
//  Description:  入场回合，触发入场技能
// =====================================================================================
void CBattleSimulator::EnterRound ()
{
    SBattleRound oRound;

    oRound.dwRounds = 0;    // 入场不算第一回合，是第0回合

    CEnterMachineState cEnterMS(_oField);
    cEnterMS.Process();

    SBattleProgress&  rProgress = cEnterMS.GetBattleProgress();
    oRound.vTargets.push_back(rProgress);

    TVecMachineStatePtr& rvecMS = cEnterMS.GetExtraMS();
    for(auto& pMS : rvecMS)
    {
        if (pMS)
        {
            pMS->Process();
            SBattleProgress& rProgress2 = pMS->GetBattleProgress();
            oRound.vTargets.push_back(rProgress2);
            delete pMS;
        }
    }

    _oReport.vRound.push_back(oRound);
}		// -----  end of function EnterRound  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartOneBattle
//  Description:  进行一场战斗
// =====================================================================================
UINT32 CBattleSimulator::StartOneBattle()
{
    _oReport.qwNextBattleID     = 0;
    _oReport.byAWaves           = 1;    // 战斗只会有一队
    _oReport.byBWaves           = 1;    // 战斗只会有一队

    EnterRound();   // 入场回合

    if(_oField.IsEmpty())
        return 0;

    UINT32 dwRounds = 0;
    do
    {
        SBattleRound oRound;
        dwRounds = _oField.GetRounds();
        oRound.dwRounds = dwRounds;

        BATTLE_DBG << "==================================================\n\n";
        BATTLE_DBG << "Round : " << dwRounds << ".";

        bool bRoundEnd = true;

        // 一个大回合
        while(_oField.GetRounds() <= dwRounds)
        {
            CMainMachineState cMainMS(_oField, bRoundEnd);
            cMainMS.Process();

            bRoundEnd = cMainMS.IsRoundEnd();

            auto rvecExtraProgressBefore = cMainMS.GetExtraProgressBefore();
            oRound.vTargets.insert(oRound.vTargets.end(), rvecExtraProgressBefore.begin(), rvecExtraProgressBefore.end());

            SBattleProgress&  rProgress = cMainMS.GetBattleProgress();

            SBattleProgress&  rProgress2 = cMainMS.GetBattleProgressFinal();

            TVecMachineStatePtr& rvecMS = cMainMS.GetExtraMS();
            const TVecEffects& vEf0 = rProgress2.vEffectsBefore;
            rProgress.vEffectsBefore.insert(rProgress.vEffectsBefore.end(), vEf0.begin(), vEf0.end());

            const TVecEffects& vEf02 = rProgress2.vSkillEffects;
            rProgress.vSkillEffects.insert(rProgress.vSkillEffects.end(), vEf02.begin(), vEf02.end());

            const TVecEffects& vEf03 = rProgress2.vEffectsAfter;
            rProgress.vEffectsAfter.insert(rProgress.vEffectsAfter.end(), vEf03.begin(), vEf03.end());

            oRound.vTargets.push_back(rProgress);

            for(auto& pMS : rvecMS)
            {
                if (pMS)
                {
                    pMS->Process();
                    SBattleProgress& rProgress2 = pMS->GetBattleProgress();
                    oRound.vTargets.push_back(rProgress2);
                    delete pMS;
                }
            }


            auto rvecExtraProgressAfter = cMainMS.GetExtraProgressAfter();
            oRound.vTargets.insert(oRound.vTargets.end(), rvecExtraProgressAfter.begin(), rvecExtraProgressAfter.end());

            if(_oField.GetResult() != EBResultNone)
                break;

            // 行动方的组合技能
            UINT8 bySide = cMainMS.GetActiveSide();
            CombineRound(bySide, oRound);
            if(_oField.GetResult() != EBResultNone)
                break;

            // 非行动组合组合技能
            bySide = bySide ? 0 : 1;
            CombineRound(bySide, oRound);
            if(_oField.GetResult() != EBResultNone)
                break;

            // 行动方的美女技能
            bySide = cMainMS.GetActiveSide();
            BeautyRound(bySide, oRound);

            if(_oField.GetResult() != EBResultNone)
                break;

            // 非行动方的美女技能
            bySide = bySide ? 0 : 1;
            BeautyRound(bySide, oRound);
            if(_oField.GetResult() != EBResultNone)
                break;

            if (bRoundEnd)
            {
                CBattleFighter* pFighter = _oField.GetPet(0);
                if (pFighter)
                {
                    CMachineState cTmpMS(_oField, eMSRelease, pFighter, NULL);
                    cTmpMS.Process();
                }

                pFighter = _oField.GetPet(1);
                if (pFighter)
                {
                    CMachineState cTmpMS(_oField, eMSRelease, pFighter, NULL);
                    cTmpMS.Process();
                }
                _oField.UnlockCombineSkill();

                // 行动方的组合技能
                UINT8 bySide = cMainMS.GetActiveSide();
                CombineRound(bySide, oRound);
                if(_oField.GetResult() != EBResultNone)
                    break;

                // 非行动组合组合技能
                bySide = bySide ? 0 : 1;
                CombineRound(bySide, oRound);
                if(_oField.GetResult() != EBResultNone)
                    break;

                // 行动方的美女技能
                bySide = cMainMS.GetActiveSide();
                BeautyRound(bySide, oRound);

                if(_oField.GetResult() != EBResultNone)
                    break;

                // 非行动方的美女技能
                bySide = bySide ? 0 : 1;
                BeautyRound(bySide, oRound);
                if(_oField.GetResult() != EBResultNone)
                    break;

            }
        }
        _oReport.vRound.push_back(oRound);

        // 已经分出胜负或者超过最大回合数，强制结束战斗
        if (_oField.GetResult() != EBResultNone || dwRounds > DEFAULT_MAX_ROUND)
            break;
    } while(true);

    return dwRounds;
}		// -----  end of function StartOneBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BeautyRound
//  Description:  美女技能的行动时间（灵气值改变/释放美女技能）
// =====================================================================================
void CBattleSimulator::BeautyRound (UINT8 bySide, SBattleRound& rRound)
{
    CReiatsuChangeMachineState cReiatsuChangeMS(_oField, eMSOnReiatsuAdd, bySide);
    cReiatsuChangeMS.Process();
    if (cReiatsuChangeMS.IsLaunched())
    {
        SBattleProgress& rProgress = cReiatsuChangeMS.GetBattleProgress();
        rRound.vTargets.push_back(rProgress);
    }
}		// -----  end of function BeautyRound  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CombineRound
//  Description:  组合技能的行动时间（连携点数/释放连携技能）
// =====================================================================================
void CBattleSimulator::CombineRound (UINT8 bySide, SBattleRound& rRound)
{
    bool bLaunched = false;
    do
    {
        CCombineChangeMachineState cCombineChangeMS(_oField, eMSOnCombineAdd, bySide);
        cCombineChangeMS.Process();
        bLaunched = cCombineChangeMS.IsLaunched();
        if (bLaunched)
        {
            SBattleProgress& rProgress = cCombineChangeMS.GetBattleProgress();
            rRound.vTargets.push_back(rProgress);
        }
    } while(bLaunched);
}		// -----  end of function CombineRound  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CalcWinner
//  Description:  计算最后的获胜者
// =====================================================================================
EBattleResult CBattleSimulator::CalcWinner()
{
    EBattleResult eResult = _oField.GetResult();
    if (eResult == EBResultNone)
    {
        UINT32 dwTotalHP1 = 0;
        UINT32 dwTotalHP2 = 0;
        if (_vecTeams.size() >= 1)
        {
            SBattleTeamPtr pTeam = _vecTeams[0];
            if (pTeam)
            {
                for (auto pFighter : pTeam->_vecFighter)
                {
                    if (pFighter && pFighter->GetPos() < MAX_POS)
                        dwTotalHP1 += pFighter->GetHP();
                }
            }
        }

        if (_vecTeams.size() >= 2)
        {
            SBattleTeamPtr pTeam = _vecTeams[1];
            if (pTeam)
            {
                for (auto pFighter : pTeam->_vecFighter)
                {
                    if (pFighter && pFighter->GetPos() < MAX_POS)
                        dwTotalHP2 += pFighter->GetHP();
                }
            }
        }
        if (dwTotalHP1 > dwTotalHP2)
            eResult = EBResultAttackWin;
        else if (dwTotalHP2 < dwTotalHP1)
            eResult = EBResultDefenseWin;
        else
            eResult = EBResultTie;
    }
    _oReport.eResult = eResult;
    return eResult;
}		// -----  end of function CalcWinner  ----- //

} // namespace NBattle

