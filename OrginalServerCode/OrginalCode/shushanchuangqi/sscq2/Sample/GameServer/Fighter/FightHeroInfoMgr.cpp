#include "stdafx.h"
#include "FightHeroInfoMgr.h"
#include "Player.h"
#include "User.h"
//#include "SysMsgDefine.h"
#include "Game2DBCommC.h"
#include "Fighter.h"
#include "FighterManager.h"
extern CGame2DBCommC g_Game2DBCommC;
bool CFightHeroInfoMgr::FightHeroInfoInit()
{
    return true;
}

CFightHeroInfoMgr::CFightHeroInfoMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    
}

bool CFightHeroInfoMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    LOG_DBG<<"CFightHeroInfoMgr::LoadFromDB:"<<rRoleDataInfo.vecFightHeroDBInfo.size();
    for(size_t i=0; i < rRoleDataInfo.vecFightHeroDBInfo.size(); i++)
    {
        SFightHeroDBInfo oInfo = rRoleDataInfo.vecFightHeroDBInfo[i];
        UpdateFightHeroDBInfo(oInfo,false);
    }

    return true;
}

void CFightHeroInfoMgr::Update2DB(const SFightHeroDBInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeFightHero, eDataChange, strData);
}

//更新仙信息
void CFightHeroInfoMgr::UpdateFightHeroDBInfo(SFightHeroDBInfo& rFightHeroDBInfo,bool bSaveToDB/*=true*/)
{
    if( rFightHeroDBInfo.wBattleType < 1 || rFightHeroDBInfo.wBattleType >= EBattleEnd)
    {
        LOG_CRI<<"Error wBattleType:"<<rFightHeroDBInfo.wBattleType; 
        return;
    }

    if(0 == rFightHeroDBInfo.qwRoleID)
    {
        LOG_CRI<<"Error rFightHeroDBInfo.qwRoleID == 0";
        rFightHeroDBInfo.qwRoleID = _rPlayer.GetRoleID();
        //return;
    }
    TMapFightHeroDBInfo& rMapFightHeroDBInfo = GetMapFightHeroDBInfoByBattleType(rFightHeroDBInfo.wBattleType);
    rMapFightHeroDBInfo[rFightHeroDBInfo.qwInstID] = rFightHeroDBInfo;

    if(bSaveToDB)
    {
        Update2DB(rFightHeroDBInfo);
    }

}

//获取散仙信息false表示未存储
bool CFightHeroInfoMgr::GetFightHeroDBInfo(UINT16 wBattleType,UINT64 qwInstID,SFightHeroDBInfo& rFightHeroDBInfo)
{
    TMapFightHeroDBInfo& rMapFightHeroDBInfo = GetMapFightHeroDBInfoByBattleType(wBattleType);
    auto itr = rMapFightHeroDBInfo.find(qwInstID);
    if(itr == rMapFightHeroDBInfo.end())
    {
        return false;
    }

    rFightHeroDBInfo = itr->second;
    return true;
}

TMapFightHeroDBInfo& CFightHeroInfoMgr::GetMapFightHeroDBInfoByBattleType(UINT16 wBattleType)
{
    return _mapBattleType2MapFightHeroDBInfo[wBattleType];
}

//清理指定战斗类型的散仙数据
void CFightHeroInfoMgr::ClearByBattleType(UINT16 wBattleType)
{
    TMapFightHeroDBInfo& rMapFightHeroDBInfo = GetMapFightHeroDBInfoByBattleType(wBattleType);
    for(auto itr = rMapFightHeroDBInfo.begin(); itr != rMapFightHeroDBInfo.end(); ++itr)
    {
        Update2DB(itr->second,eOpDel);
    }

    rMapFightHeroDBInfo.clear();
}


//获取散仙信息
void CFightHeroInfoMgr::OnGetFightHeroInfo(UINT16 wBattleType,TVecFightHeroInfo& vecTVecFightHeroInfo)
{
    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
        return;

    TVecFighterPtr vecFighters;
    pFighterManager->GetAllFighters(vecFighters);

    for(size_t i=0; i < vecFighters.size(); i++)
    {
        CFighterPtr pFighter = vecFighters[i];
        if(pFighter)
        {
            FightHeroInfo oFightHeroInfo;
            oFightHeroInfo.qwInstID = pFighter->GetInstID();
            IBattleFighterPtr pBattleFighter = pFighter->ToBattleFighter(0, EBTINVALID);
            if(NULL == pBattleFighter)
            {
                continue;
            }
            oFightHeroInfo.dwMaxHP = pBattleFighter->GetMaxHP();
            oFightHeroInfo.dwMaxAura = pBattleFighter->GetMaxAura();
            SFightHeroDBInfo oFightHeroDBInfo;
            bool bRet = GetFightHeroDBInfo(wBattleType,pFighter->GetInstID(),oFightHeroDBInfo);
            if(bRet)
            {
                oFightHeroInfo.dwHP = oFightHeroDBInfo.dwHP;
                oFightHeroInfo.dwAura = oFightHeroDBInfo.dwAura;
            }
            else
            {
                oFightHeroInfo.dwHP = pBattleFighter->GetMaxHP();
                //默认初始灵气
                oFightHeroInfo.dwAura = pBattleFighter->GetAura();
            }
            vecTVecFightHeroInfo.push_back(oFightHeroInfo);
        }
    }
}



//获取当前战斗散仙数据
bool CFightHeroInfoMgr::GetBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter)
{
    for(size_t i=0; i < vecBattleFighter.size(); i++)
    {
        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
        SFightHeroDBInfo oFightHeroDBInfo;
        bool bRet = GetFightHeroDBInfo(eBattleType,pBattleFighter->GetInstID(),oFightHeroDBInfo);
        if(bRet)
        {
            pBattleFighter->SetHP(oFightHeroDBInfo.dwHP);
            pBattleFighter->SetAura(oFightHeroDBInfo.dwAura);
        }
        else
        {
            pBattleFighter->SetHP(pBattleFighter->GetMaxHP());
            //灵气值默认已设置
            //pBattleFighter->SetAura(pBattleFighter->GetAura());
        }
    }

    return true;
}

//保存当前战斗散仙数据
void CFightHeroInfoMgr::SaveBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter)
{
    for(size_t i=0; i < vecBattleFighter.size(); i++)
    {
        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
        SFightHeroDBInfo oFightHeroDBInfo;
        oFightHeroDBInfo.qwRoleID = _rPlayer.GetRoleID();
        oFightHeroDBInfo.qwInstID = pBattleFighter->GetInstID();
        oFightHeroDBInfo.wBattleType = eBattleType;
        oFightHeroDBInfo.dwHP = pBattleFighter->GetHP();
        oFightHeroDBInfo.dwMaxHP = pBattleFighter->GetMaxHP();
        oFightHeroDBInfo.dwAura =  pBattleFighter->GetAura();
        //oFightHeroDBInfo.dwMaxAura = pBattleFighter->GetMaxAura();
        UpdateFightHeroDBInfo(oFightHeroDBInfo);
    }
}

//检测所有散仙血量是否为0
bool CFightHeroInfoMgr::CheckAllFighterHPByBattleType(UINT16 wBattleType)
{
    //所有的散仙
    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
        return false;

    TVecFighterPtr vecFighters;
    pFighterManager->GetAllFighters(vecFighters);

    //参战的散仙
    UINT32 dwCount = 0;
    TMapFightHeroDBInfo& rMapFightHeroDBInfo = GetMapFightHeroDBInfoByBattleType(wBattleType);
    for(auto itr = rMapFightHeroDBInfo.begin(); itr != rMapFightHeroDBInfo.end(); ++itr)
    {
        if (0 == itr->second.qwInstID)
            continue;

        if (itr->second.dwHP > 0)
            return true;

        dwCount++;
    }

    if (vecFighters.size() > dwCount)
        return true;

    return false;
}


