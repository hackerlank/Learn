
#include "stdafx.h"
#include "FightFormationMgr.h"
#include "Fighter.h"
#include "FighterMgr.h"
#include "UtilFunc.h" // XXX: for ValueInVec
#include "Battle.h"
#include "Player.h"
#include "User.h"
#include "FighterManager.h"
#include "Tokenizer.h"
#include "FightHeroInfoMgr.h"

string GetStringBattlePos(TVecBattlePosInfo& rTVecBattlePosInfo)
{
    ostringstream os;
    for(size_t i=0; i < rTVecBattlePosInfo.size(); i++)
    {
        os<<rTVecBattlePosInfo[i].qwInstID;
        os<<",";
        os<<(UINT32)rTVecBattlePosInfo[i].byPos;
        if( (i + 1) != rTVecBattlePosInfo.size())
        {
            os<<"|";
        }
    }
    return os.str();
}

void GetBattlePosFromString(TVecBattlePosInfo& rTVecBattlePosInfo,string strBattlePosInfo)
{
     
    Tokenizer tk(strBattlePosInfo, "|"); // XXX:qwInstID,byPos|qwInstID,byPos
    for (size_t i = 0; i < tk.size(); ++i)
    {
         Tokenizer yatk(tk[i], ",");
         if(yatk.size()<2)
             continue;
         UINT64 qwInstID = strtoll(yatk[0].c_str(),NULL,10);
         UINT8  byPos    = atoi(yatk[1].c_str());
         rTVecBattlePosInfo.emplace_back(qwInstID,byPos);
    }
    return;
}


//    SFormationCFGEx* pFormationCfg = CFighterMgr::GetFormationCfg(wFormationID);
EFightFormationResult CFightFormationMgr::OnGetFormation(UINT16 wBattleType,FightFormationInfo& rFightFormation)
{
    EBattleType eBattleType = (EBattleType)wBattleType;
    if(eBattleType >= EBattleEnd)
    {
        return eFightFormationResult_Fail;
    }
    rFightFormation = GetFormationByType(eBattleType);
    return eFightFormationResult_Succes;
}

EFightFormationResult CFightFormationMgr::OnSetFormation(UINT16 wBattleType,const FightFormationInfo& rFightFormation)
{
    if(!IsCanSet(rFightFormation))
    {
        return eFightFormationResult_Fail;
    }
    _mapFightFormationInfo[wBattleType] = rFightFormation;
    Update2DB(wBattleType,_mapFightFormationInfo[wBattleType]);

    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(pFighterManager)
    {
        TVecUINT16 vecFighterID;
        for(auto & rPosInfo : rFightFormation.vecBattlePosInfo)
        {
            CFighterPtr pFighter = pFighterManager->GetFighterByInstID(rPosInfo.qwInstID);
            if(NULL == pFighter)
                continue;
            vecFighterID.push_back(pFighter->GetID());
        }
        pFighterManager->ResetCombinationSkill(vecFighterID, eCombEquipToEMei, false);
    }
    return eFightFormationResult_Succes;
}

bool IsSinglePos(const TVecBattlePosInfo& vecBattlePosInfo,const UINT8 byPos)
{
    UINT32 dwCount = 0;
    for(size_t i=0; i < vecBattlePosInfo.size(); i++)
    {
        if(vecBattlePosInfo[i].byPos == byPos)
        {
            dwCount++;
        }
    }

    return dwCount == 1;
}

bool IsSingleInstID(const TVecBattlePosInfo& vecBattlePosInfo,const UINT64 qwInstID)
{
    UINT32 dwCount = 0;
    for(size_t i=0; i < vecBattlePosInfo.size(); i++)
    {
        if(vecBattlePosInfo[i].qwInstID == qwInstID)
        {
            dwCount++;
        }

    }
    return dwCount == 1;
}

bool CFightFormationMgr::IsCanSet(const FightFormationInfo& rFightFormation)
{
    
    //最高上阵人数限制
    if(rFightFormation.vecBattlePosInfo.size() > 5)
    {
        return false;
    }
    
    for(auto & rInfo : rFightFormation.vecBattlePosInfo)
    {
        UINT8 byPos = rInfo.byPos;
        UINT64 qwInstID = rInfo.qwInstID;

        /*
        if( !pFormationCfg->IsValidPos(rInfo.byPos))
        {
            LOG_CRI<<"InvalidPos:"<<rInfo.byPos;
            return false;
        }
        */

        if(rInfo.byPos>9)
            return false;

        if(!IsSinglePos(rFightFormation.vecBattlePosInfo,byPos))
        {
            LOG_CRI<<"double pos:"<<byPos;
            return false;
        }

        if(!IsSingleInstID(rFightFormation.vecBattlePosInfo,qwInstID))
        {
            LOG_CRI<<"double qwInstID:"<<qwInstID;
            return false;
        }
    }

    //if(find(pFormationCfg->vecPos.begin(),pFormationCfg)

    return true;
}

bool CFightFormationMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    LOG_DBG<<"CBattleArrayMgr::LoadFromDB:"<<rRoleDataInfo.vecFightFormationDBInfo.size();
    for(size_t i=0; i < rRoleDataInfo.vecFightFormationDBInfo.size(); i++)
    {
        FightFormationInfo oFightFormationInfo;
        oFightFormationInfo.wFormationID = rRoleDataInfo.vecFightFormationDBInfo[i].wFormationID;
        GetBattlePosFromString(oFightFormationInfo.vecBattlePosInfo,rRoleDataInfo.vecFightFormationDBInfo[i].strBattlePosInfo);
        if(oFightFormationInfo.vecBattlePosInfo.empty())
        {
            LOG_CRI<<"Error BattlePosInfo:"<<rRoleDataInfo.vecFightFormationDBInfo[i].wBattleType;
            continue;
        }

        //此处未检查阵型数据
        _mapFightFormationInfo[rRoleDataInfo.vecFightFormationDBInfo[i].wBattleType] = oFightFormationInfo;

    }
    return true;
}

void CFightFormationMgr::Update2DB(UINT16 wBattleType,FightFormationInfo& rFightFormationInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    SFightFormationDBInfo oInfo;
    oInfo.qwRoleID = _rPlayer.GetRoleID();
    oInfo.wBattleType = wBattleType;
    oInfo.strBattlePosInfo = GetStringBattlePos(rFightFormationInfo.vecBattlePosInfo);
    string strData;
    COutArchive iar(strData);
    iar << oInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeFightFormation, eDataChange, strData);
}

UINT64 CFightFormationMgr::GetBattleFighters(EBattleType eBattleType, TVecBattleFighterPtr& vecBattleFighter)
{

    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(!pFighterManager)
        return 0;
    CFightHeroInfoMgrPtr pFightHeroInfoMgr = _rPlayer.GetFightHeroInfoMgr();
    if(!pFightHeroInfoMgr)
        return 0;

    bool bDead = true;

    UINT64 qwMainInstID = 1;
    FightFormationInfo oFightFormationInfo = GetFormationByType(eBattleType);
    for(auto & rPosInfo : oFightFormationInfo.vecBattlePosInfo)
    {
        CFighterPtr pFighter = pFighterManager->GetFighterByInstID(rPosInfo.qwInstID);
        if(!pFighter)
        {
            LOG_CRI<<"Unkon FighterInstID:"<< rPosInfo.qwInstID;
            return 0;
        }

        if (pFighter->IsMainFighter())
            qwMainInstID = pFighter->GetInstID();

        IBattleFighterPtr pBattleFighter = pFighter->ToBattleFighter(0, eBattleType);
        if(pBattleFighter)
        {
            vecBattleFighter.push_back(pBattleFighter);

            //阵位
            pBattleFighter->SetPos(rPosInfo.byPos);
            
            //血量
            //灵气
            SFightHeroDBInfo oFightHeroDBInfo;
            bool bRet = pFightHeroInfoMgr->GetFightHeroDBInfo(eBattleType,pFighter->GetInstID(),oFightHeroDBInfo);
            if(bRet)
            {
                pBattleFighter->SetHP(oFightHeroDBInfo.dwHP);
                pBattleFighter->SetAura(oFightHeroDBInfo.dwAura);
            }
            else
            {
                pBattleFighter->SetHP(pBattleFighter->GetMaxHP());
                pBattleFighter->SetAura(pBattleFighter->GetAura());
            }

            //阵灵美女排出在外
            if(pBattleFighter->GetPos() < 10 && pBattleFighter->GetHP())
                bDead = false;
        }
    }

    //全部死亡
    if(bDead)
        return 0;
    else
        return qwMainInstID;    // FIXME: 主将ID，主将的BattleFighter对象塞到rvecBattleFighterPtr里面去
}

//获取战斗力
UINT32 CFightFormationMgr::GetBattlePoint(EBattleType eBattleType)
{
    UINT32 dwPower = 0;
    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        return 0;
    }
    CFightHeroInfoMgrPtr pFightHeroInfoMgr = _rPlayer.GetFightHeroInfoMgr();
    if(NULL == pFightHeroInfoMgr)
    {
        return 0;
    }


    FightFormationInfo oFightFormationInfo = GetFormationByType(eBattleType);
    for(auto & rPosInfo : oFightFormationInfo.vecBattlePosInfo)
    {
        CFighterPtr pFighter = pFighterManager->GetFighterByInstID(rPosInfo.qwInstID);
        if(NULL == pFighter)
        {
            LOG_CRI<<"Unkon FighterInstID:"<< rPosInfo.qwInstID;
            return 0;
        }
        
        SFightHeroDBInfo oFightHeroDBInfo;
        bool bRet = pFightHeroInfoMgr->GetFightHeroDBInfo(eBattleType,pFighter->GetInstID(),oFightHeroDBInfo);
        if(bRet)
        {
            //has dead
            if(0 == oFightHeroDBInfo.dwHP)
                  continue;
         }
    
        dwPower += pFighter->GetBattlePoint();
    }

    return dwPower + pFighterManager->GetTrumpSkillBattlePoint();
}


FightFormationInfo CFightFormationMgr::GetFormationByType(EBattleType eBattleType)
{
    auto itr = _mapFightFormationInfo.find(eBattleType);
    if(itr != _mapFightFormationInfo.end())
        return itr->second;

    FightFormationInfo oFightFormationInfo;
    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(pFighterManager)
    {
        pFighterManager->GetDefaultFightFormation(oFightFormationInfo);
        //XXX 策划的BT要求,无语。。。
        TVecUINT16 vecFighterID;
        for(auto & rPosInfo : oFightFormationInfo.vecBattlePosInfo)
        {
            CFighterPtr pFighter = pFighterManager->GetFighterByInstID(rPosInfo.qwInstID);
            if(NULL == pFighter)
                continue;
            vecFighterID.push_back(pFighter->GetID());
        }
        UINT32 dwSkillID = pFighterManager->GetCombinationSkill(eCombEquipToLineUp);
        pFighterManager->SetCombinationSkill(eCombEquipToEMei, dwSkillID);
        pFighterManager->ResetCombinationSkill(vecFighterID, eCombEquipToEMei, false);
    }
    else
        LOG_CRI << "Unkown Error!!!";

    //
    return oFightFormationInfo;
}

//清除阵型数据
void CFightFormationMgr::ClearFormation(EBattleType eBattleType)
{
    auto itr = _mapFightFormationInfo.find(eBattleType);
    if(itr == _mapFightFormationInfo.end())
        return;

    Update2DB(eBattleType,itr->second,eOpDel);
    _mapFightFormationInfo.erase(itr);
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

