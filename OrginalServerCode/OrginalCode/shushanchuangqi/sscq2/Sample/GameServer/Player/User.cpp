/********************************************************************
//	Game Server Source File.
//	File name:	User.cpp
//	Created:	2011/05/30	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "UserMgr.h"
#include "Map.h"
#include "DungeonMgr.h"
#include "FighterManager.h"
#include "VIPMgr.h"
#include "Parameter.h"
#include "Bubble.h"
#include "MiscProtS.h"
#include "SysMsgDefine.h"
#include "EnergyMgr.h"
#include "GameServerLog.h"
#include "Mall.h"
#include "RTime.h"
#include "BoostMgr.h"
#include "HeroFighter.h"
#include "GameServerSysMail.h"
#include "DayActProtS.h"
#include "IconAppearManager.h"
#include "ServerID.h"
#include "GameNetMgr.h"
#include "EverydayRecharge.h"

#ifdef PROT_USE_XML
    template<typename T>
bool SaveToXML(const T& rT, const char* pszName, const char* pszPath)
{
    TiXmlElement* pElement = new TiXmlElement(pszName);
    if(pElement == NULL)
        return false;
    if(!ToXML(rT, *pElement))
        return false;
    TiXmlDocument doc;
    TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
    if(pDecl == NULL)
        return false;
    doc.LinkEndChild(pDecl);
    doc.LinkEndChild(pElement);
    return doc.SaveFile(pszPath);
}

    template<typename T>
bool LoadFromXML(const char* pszPath, T& rT)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(pszPath, TIXML_ENCODING_UTF8))
        return false;
    TiXmlElement* pElement = doc.RootElement();
    if(pElement == NULL)
        return false;
    if(!FromXML(*pElement, rT))
        return false;
    return true;
}
#endif

//////////////////////////////////////////////////////////////////////////

bool COpLock::AddLock(eLockType eLock, UINT8 byTime)
{
    auto it = _mapLock.find(eLock);
    UINT32 dwNow = time(NULL);
    if (it != _mapLock.end())
    {
        if(dwNow < it->second + byTime)
        {
            LOG_CRI << _rUser.GetUserID() << "Lock by " << eLock;
            return false;
        }
    }
    _mapLock[eLock] = dwNow;
    return true;
}

void COpLock::UnLock(eLockType eLock)
{
    _mapLock.erase(eLock);
}

const UINT32 INDULGE_UPDATE_TIME = 1*60; //1分钟
const UINT32 ONLINE_UPDATE_TIME = 3*60;
CUser::CUser(UINT64 qwUsrID) : _qwUsrID(qwUsrID), _dwRecvFailCount(0), _byCampForDB(0), _eUserState(eUserNone),
    _tLastCheckTime(0), _tLastSaveTime(0),
    _wUsrDataVer(0), _wSvrGroup(0), _bAllSysOpen(false), _pPlayer(NULL), _byNation(0), _byGMLvl(0x0),
    _byVIPLevel(0), _dwLoginTime(0), _dwOfflineTime(0), _dwLockExpireTime(0), _dwForbExpireTime(0),
    _oPack(*this, SParamConfig::wPackInitCount), _oDepot(*this), _oTaskPkg(*this), _oVars(*this), _opLock(*this), _bHasChange(false), _bHasMiscChange(false)

{
    _bIndulge = false;           //是否防沉迷
    _tIndulgeTime = 0;           //计时起点     
    _tDiffTime = 0;
    _wIncome = GAME_COEF_PERCENT;//防沉迷收益
    _dwKickTime = 0;
    _tAddOnLineTime = Time::Now();
    _vecEnterString.resize(4);
}


CUser::~CUser()
{
    LOG_INF << "delete user : " << _qwUsrID;
}

void CUser::Init()
{
    if (!_pBubbleOwner)
        _pBubbleOwner = CBubbleOwnerPtr(new CBubbleOwner(ToThisPtr(this)));
}

const std::string& CUser::GetUserName() const
{
    static std::string strNull = "null";
    return _pPlayer?_pPlayer->GetName():strNull;
}

UINT8 CUser::GetLevel() const
{
    return _pPlayer?_pPlayer->GetLevel():1;
}

void CUser::SetUserName(const std::string& name)
{
    if (_pPlayer)
        _pPlayer->SetName(name);
}

void CUser::OnRecvFail()
{
    ++_dwRecvFailCount;
    if(_dwRecvFailCount > 10)
    {
        LOG_INF << "CUser::OnRecvFail()";
        CUserMgr::KickUserOffLine(_qwUsrID, true);
        CUserMgr::OnUserLeave(_qwUsrID, eLeaveKick);
    }
}

void CUser::SetUserState(EUserState eUserState)
{
    LOG_INF <<"CUser::SetUserState" <<eUserState;
    _eUserState = eUserState;
    _tLastCheckTime = Time::Now();
}

const std::string CUser::GetFixdUserName() const
{
    return GetUserName();
}

bool CUser::HasChange() const
{
    // TODO:
    return _bHasChange;
}

void CUser::ClearChange()
{
    _bHasChange = false;
}

bool CUser::CanRemove()
{
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer != NULL)
    {
        return  pPlayer->CanRemove();
    }
    LOG_CRI << "Player = NULL.";
    return true;
}

UINT32 CUser::GetDBSvrID() const 
{ 
    return GetServerID(_wSvrGroup, eHostDB, 1); 
}

UINT32 CUser::GetCenterSvrID() const 
{ 
    return GetServerID(_wSvrGroup, eHostCenter, 1); 
}

void CUser::SetSvrGroup(UINT16 wSvrGroup) 
{ 
    _wSvrGroup = wSvrGroup; 
}

bool CUser::SendPkg(const string& strPkg)
{
    if(strPkg.empty())
        return false;
    return NetMgr.GetGateHandler()->SendClt(&_qwUsrID, 1, &strPkg[0], (UINT32)strPkg.size());
}

void CUser::SetAllSysOpen(bool bAllSysOpen, bool bNotify /*= true*/)
{
    _bAllSysOpen = bAllSysOpen;
    if(bNotify)
        SendPkg(g_GameSvrBasicS.BuildPkg_OpenAllSystem(bAllSysOpen));
}

bool CUser::SendCenterSvrPkg(const string& strPkg)
{
    if(strPkg.empty())
        return false;
    UINT32 dwSvrID = GetCenterSvrID();
    if(dwSvrID == 0)
        return false;
    auto pHandler = NetMgr.GetSvrHandler(eHostCenter);
    if(pHandler == NULL)
        return false;
    return pHandler->SendSvr(&dwSvrID, 1, &strPkg[0], (UINT32)strPkg.size());
}

void CUser::NotifyUserProp()
{
    // TODO: 登陆后需要发送的信息
}

void CUser::OnEnter()
{
    SCRIPT.VCall("OnUserEnter", this);
}

void CUser::OnReplace()
{
    SetUserState(eUserReplace);
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer != NULL)
    {
        pPlayer->SetPlayerState(ePlayerSwitch);
        pPlayer->OnReplace();
    }
}

void CUser::OnLeaveAway()
{
    SetUserState(eUserLeaveAway);
    SetOfflineTime((UINT32)Time::Now());
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer != NULL)
    {
        pPlayer->OnLeaveAway();
        pPlayer->SetPlayerState(ePlayerLeave);

    }
    if (_pBubbleOwner)
        _pBubbleOwner->ClearOfflineBubble();
    SCRIPT.VCall("OnLogout", this);
}

void CUser::OnLeaveOff(ESaveType eSaveType)
{
    // TODO:
    if(!Config._bIsCrossServer && eSaveType == eSaveOff)
    {
        if(!g_Game2DBCommC.SaveDataReq(*this, eSaveType, _vecPlatformParam))
            LOG_CRI << "SaveDataReq fails! UserID: " << _qwUsrID;
    }
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer != NULL)
    {
        pPlayer->OnLeaveOff();
    }

}

void CUser::OnSwitchMap(CGameMapPtr& pMap)
{
    // TODO:
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer->GetMap() == pMap)
        pMap->PlayerReappear(*pPlayer);
}

static UINT32 dwAllGold = 0;
UINT32& CUser::GetMoneyVarible(EMoneyType eMoneyType)
{
    if(NULL == _pPlayer)
    {
        return _dwNoMoney;
    }

    RoleBaseInfo &rRoleBase = _pPlayer->GetModifyBaseInfo();

    switch(eMoneyType)                     
    {
        case EMONEY_NONE:
            return _dwNoMoney;
        case EMONEY_GOLD:
            {
                dwAllGold = rRoleBase.dwGold + rRoleBase.dwFreeGold;
                return dwAllGold;
            }
        case EMONEY_COUPON:
            return rRoleBase.dwCoupon;
        case EMONEY_SILVER:
            return rRoleBase.dwSilver;
        case EMONEY_SOUL:
            return rRoleBase.dwSoul;
        case EMONEY_PRESTIGE:
            return rRoleBase.dwPrestige;
        case EMONEY_HONOR:
            return rRoleBase.dwHonor;
        case EMONEY_PEXP:
            return rRoleBase.dwPExp;
        case EMONEY_ACTION:
            return rRoleBase.dwAction;
        case EMONEY_POTEN:
            return rRoleBase.dwPoten;
        case EMONEY_REIKI:
            return rRoleBase.dwReiki;
        case EMONEY_DEMONSOUL:
            return rRoleBase.dwDemonSoul;
        case EMONEY_SOULHP:
            return rRoleBase.dwSoulHp;
        case EMONEY_SOULATTACK:
            return rRoleBase.dwSoulAttack;
        case EMONEY_SOULCRITICAL:
            return rRoleBase.dwSoulCritical;
        case EMONEY_SOULCOUNTER:
            return rRoleBase.dwSoulCounter;
        case EMONEY_SOULSPEED:
            return rRoleBase.dwSoulSpeed;
        case EMONEY_SOULDEFENCE:
            return rRoleBase.dwSoulDefence;
        case EMONEY_SOULHIT:
            return rRoleBase.dwSoulHit;
        case EMONEY_SOULDODGE:
            return rRoleBase.dwSoulDodge;
        case EMONEY_ACHIEVEMENTAP:
            return rRoleBase.dwAchievementAP;
        case EMONEY_COLLECTAP:
            return rRoleBase.dwCollectAP;
        case EMONEY_STAMPHUANG:
            return rRoleBase.dwStampHuang;
        case EMONEY_STAMPXUAN:
            return rRoleBase.dwStampXuan;
        case EMONEY_STAMPDI:
            return rRoleBase.dwStampDi;
        case EMONEY_STAMPTIAN:
            return rRoleBase.dwStampTian;
        case EMONEY_STAMPXING:
            return rRoleBase.dwStampXing;
        case EMONEY_STAMPYUE:
            return rRoleBase.dwStampYue;
        case EMONEY_STAMPDI2:
            return rRoleBase.dwStampDi2;
        case EMONEY_STAMPXIAN:
            return rRoleBase.dwStampXian;
        case EMONEY_STAMPSHENG:
            return rRoleBase.dwStampSheng;
        case EMONEY_STAMPFO:
            return rRoleBase.dwStampFo;
        case EMONEY_LOVEHEART:
            return rRoleBase.dwLoveHeart;
        case EMONEY_BLUEFAIRYFATE:
            return rRoleBase.dwBlueFairyFate;
        case EMONEY_PURPLEFAIRYFATE:
            return rRoleBase.dwPurpleFairyFate;
        case EMONEY_ORANGEFAIRYFATE:
            return rRoleBase.dwOrangeFairyFate;
        case EMONEY_DUJIEFU:
            return rRoleBase.dwDuJieFu;
        case EMONEY_LUCKYCOUPON:
            return rRoleBase.dwLuckyCoupon;
        case EMONEY_END:
        default:
            return _dwNoMoney;
    }
}

//统一货币扣除接口
UINT32 CUser::GetMoney(EMoneyType eMoneyType)
{
    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    return dwMoney;
}

//是否可以增加货币
bool CUser::CanAddMoney(EMoneyType eMoneyType,UINT32 dwCount)
{
    if(eMoneyType >= EMONEY_END)
    {
        return false;
    }

    if(EMONEY_EXP == eMoneyType) 
    {
        return true;
    }

    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    if(&dwMoney == &_dwNoMoney)
    {
        return false;
    }

    UINT32 dwSum = dwCount + dwMoney;
    if(dwSum < dwMoney || dwSum > MAX_POSSIBLE_MONEY)
        return false;
    return true;
}


//是否可以扣货币
bool CUser::CanSubMoney(EMoneyType eMoneyType,UINT32 dwCount)
{
    if(eMoneyType >= EMONEY_END)
    {
        return false;
    }

    //不允许扣经验
    if(EMONEY_EXP == eMoneyType) 
    {
        LOG_CRI<<"error EMoneyType";
        return false;
    }


    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    if(&dwMoney == &_dwNoMoney)
    {
        return false;
    }

    if(dwCount> dwMoney)
        return false;
    return true;
}

void  CUser::SynToCeneterNotify(EMoneyType eMoneyType, UINT32 dwValue)
{
    if(eMoneyType == EMONEY_GOLD)
    {
        g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropGold,NumberToString(dwValue));
    }
    else if(eMoneyType == EMONEY_SILVER)
    {
        g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropSilver,NumberToString(dwValue));
    }
    else if(eMoneyType == EMONEY_COUPON)
    {
        g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropCoupon,NumberToString(dwValue));
    }
}

bool CUser::AddMoney(EMoneyType eMoneyType,UINT32 dwCount, UINT16 fromWhere/*=0*/,bool bNotify /* = true */)
{
    if(!GetPlayer() || eMoneyType >= EMONEY_END)
    {
        return false;
    }

    //经验值特殊处理
    if(EMONEY_EXP == eMoneyType)
    {
        return GetPlayer()->AddExp(dwCount);
    }

    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    if(&dwMoney == &_dwNoMoney)
    {
        return false;
    }

    double fRate = 1.0;
    if(EMONEY_EXP == eMoneyType)
    {
        fRate = GetIndulgeRate();
        if(fRate<0.5)
        {
            SendSysMsg(eMsgChildFull);
        }
        else if(fRate < 1.0)
        {
            SendSysMsg(eMsgChildHalf);
        }
    }

    UINT32 dwSum = dwCount*fRate + dwMoney;
    if(dwSum < dwCount || dwSum > MAX_POSSIBLE_MONEY)
        return false;
    if(EMONEY_GOLD == eMoneyType)
    {
        RoleBaseInfo &rRoleBase = GetPlayer()->GetModifyBaseInfo();
        if (ItemFrom_Recharge != NLogDataDefine::ItemFrom(fromWhere))
            rRoleBase.dwFreeGold += dwCount*fRate;
        else
        {
            rRoleBase.dwGold += dwCount*fRate;
            UINT32 dwPos1EndTime = 0;
            UINT32 dwPos2EndTime = 0;
            UINT32 dwPos3EndTime = 0;
            CMall::Instance().CheckMarkID(ToThisPtr(this));
            CMall::Instance().IsInRechargeDiscount(dwPos1EndTime, dwPos2EndTime, dwPos3EndTime);
            if (dwPos1EndTime > 0)
            {
                UINT32 dwRechargePos1 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Recharge) + dwCount*fRate;
                GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos1Recharge, dwRechargePos1, 0, dwPos1EndTime);
            }
            if (dwPos2EndTime > 0)
            {
                UINT32 dwRechargePos2 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos2Recharge) + dwCount*fRate;
                GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos2Recharge, dwRechargePos2, 0, dwPos2EndTime);
            }
            if (dwPos1EndTime > 0)
            {
                UINT32 dwRechargePos3 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos3Recharge) + dwCount*fRate;
                GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos3Recharge, dwRechargePos3, 0, dwPos3EndTime);
            }
            CMall::Instance().SendMallDiscountInfo(ToThisPtr(this));
        }
        dwMoney = rRoleBase.dwGold + rRoleBase.dwFreeGold;
    }
    else
    {
        dwMoney = dwSum;
    }
    if (bNotify)
    {
        g_PropInfoS.ChangeMoney(*GetPlayer(),eMoneyType,dwMoney);
        string str = NProtoCommon::GetDescription(eMoneyType);
        SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetCurrency, BuildStrVec(str,UINT32(dwCount*fRate))));
    }
    
    GetPlayer()->UpdateBaseInfo2DB();
    SynToCeneterNotify(eMoneyType,dwSum);

    WriteMoneyLog(eMoneyType, dwCount*fRate, fromWhere);

    //兽魂
    if(eMoneyType>=EMONEY_SOULATTACK  && eMoneyType<= EMONEY_SOULDODGE)
    {
        TVecINT32 vecParam;
        vecParam.push_back(eMoneyType);
        vecParam.push_back(dwCount);
        GetPlayer()->OnEvent(eEventType_BeastSoulGet,vecParam);
    }

    {
        TVecINT32 vecParam;
        vecParam.push_back(eMoneyType);
        vecParam.push_back(dwCount);
        vecParam.push_back(dwMoney);
        GetPlayer()->OnEvent(eEventType_GetResource,vecParam);
    }

    if (eMoneyType == EMONEY_DUJIEFU)
    {   //XXX udpLog 渡劫符
        TVecUserItemChange vecItemChange;
        float fPrice = 0.0f;
        if (fromWhere == ItemFrom_Mall)
            fPrice = CItemMgr::GetGoldPrice(eMoneyType);
        SUserItemChange oItemChange(eMoneyType, dwCount*fRate, fPrice, fromWhere);
        vecItemChange.push_back(oItemChange);
        SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogItemChange(GetUserID(), eOpTypeItemChange, vecItemChange));
    }

    return true;
}

bool CUser::SubMoney(EMoneyType eMoneyType, UINT32 dwCount,NLogDataDefine::ItemTo toWhere/*=0*/, bool bNotify)
{
    if(!GetPlayer() || eMoneyType >= EMONEY_END || !dwCount)
    {
        return false;
    }

    //不允许扣经验
    if(EMONEY_EXP == eMoneyType) 
    {
        LOG_CRI<<"error EMoneyType";
        return false;
    }


    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    if(&dwMoney == &_dwNoMoney)
    {
        return false;
    }
    if(dwCount > dwMoney)
        return false;
    if(eMoneyType == EMONEY_GOLD)
    {
        RoleBaseInfo &rRoleBase = GetPlayer()->GetModifyBaseInfo();
        if (rRoleBase.dwFreeGold >= dwCount)
        {
            rRoleBase.dwFreeGold -= dwCount;
            WriteMoneyLog(eMoneyType, dwCount, toWhere, true);
        }
        else
        {
            UINT32 dwGold = dwCount-rRoleBase.dwFreeGold;
            rRoleBase.dwGold -= dwGold;
            rRoleBase.dwFreeGold = 0;
            WriteMoneyLog(eMoneyType, dwCount - dwGold, toWhere, true);
            WriteMoneyLog(eMoneyType, dwGold, toWhere, false);
        }
        dwMoney = rRoleBase.dwGold + rRoleBase.dwFreeGold;

        //TODO 去除交易所和闭关消耗的仙石
        GoldConvertVIPGrowth(dwCount);
        UINT32 dwPos1EndTime = 0;
        UINT32 dwPos2EndTime = 0;
        UINT32 dwPos3EndTime = 0;
        CMall::Instance().CheckMarkID(ToThisPtr(this));
        CMall::Instance().IsInConsumeDiscount(dwPos1EndTime, dwPos2EndTime, dwPos3EndTime);
        if (dwPos1EndTime > 0)
        {
            UINT32 dwRechargePos1 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Consume) + dwCount;
            GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos1Consume, dwRechargePos1, 0, dwPos1EndTime);
        }
        if (dwPos2EndTime > 0)
        {
            UINT32 dwRechargePos2 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos2Consume) + dwCount;
            GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos2Consume, dwRechargePos2, 0, dwPos2EndTime);
        }
        if (dwPos3EndTime > 0)
        {
            UINT32 dwRechargePos3 = GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos3Consume) + dwCount;
            GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos3Consume, dwRechargePos3, 0, dwPos3EndTime);
        }
        CMall::Instance().SendMallDiscountInfo(ToThisPtr(this));

        GetVars().AddVar(NVarDefine::ePlayerVarConsume, dwCount);
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(dwCount);
        if (_pPlayer)
            _pPlayer->OnEvent(eEventType_VipConsumptionSuccess, vecParam);
        //XXX udpLog GOLD
        TVecUserMoneyChange vecMoney;
        SUserMoneyChange oMoneyChange(eMoneyType, -dwCount, toWhere);
        vecMoney.push_back(oMoneyChange);
        SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogMoneyChange(GetUserID(), eOpTypeMoneyChange, vecMoney));
    }
    else
    {
        dwMoney -= dwCount;
        WriteMoneyLog(eMoneyType, dwCount, toWhere);
    }

    if(bNotify)
    {
        g_PropInfoS.ChangeMoney(*GetPlayer(),eMoneyType,dwMoney);
        string str = NProtoCommon::GetDescription(eMoneyType);
        SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgUseCurrency, BuildStrVec(str, dwCount)));
    }
    GetPlayer()->UpdateBaseInfo2DB();
    SynToCeneterNotify(eMoneyType,dwMoney);

    {
        TVecINT32 vecParam;
        vecParam.push_back(eMoneyType);
        vecParam.push_back(dwCount);
        vecParam.push_back(dwMoney);
        GetPlayer()->OnEvent(eEventType_SpendResource,vecParam);
    }

    if (eMoneyType == EMONEY_DUJIEFU)
    {   //XXX udpLog 渡劫符
        TVecUserItemChange vecItemChange;
        SUserItemChange oItemChange(eMoneyType, -dwCount, CItemMgr::GetGoldPrice(eMoneyType), toWhere);
        vecItemChange.push_back(oItemChange);
        SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogItemChange(GetUserID(), eOpTypeItemChange, vecItemChange));
    }

    return true;
}

void CUser::WriteMoneyLog(EMoneyType eMoneyType, UINT32 dwCount, UINT16 fromTo, bool bIsFreeGold /* = false */)
{
    if(0 == dwCount)
        return;

    NLogDataDefine::SMoneyCoursesLogPtr ptrLog(new NLogDataDefine::SMoneyCoursesLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SMoneyCoursesLog& rLog = *ptrLog;
    rLog.serverId  = Config._wGroup;
    rLog.playerId  = GetUserID();
    rLog.strOpenId = GetPlayer()->GetOpenId();
    rLog.moneyType = eMoneyType;
    rLog.moneyNum  = dwCount;
    rLog.totalNum  = GetMoney(eMoneyType);
    rLog.bIsFreeGold = bIsFreeGold ? 1 : 0;
    rLog.fromto    = fromTo;
    if (fromTo >= 5000)
        rLog.fromtoStr = NLogDataDefine::GetDescription(NLogDataDefine::ItemTo(fromTo));
    else
        rLog.fromtoStr = NLogDataDefine::GetDescription(NLogDataDefine::ItemFrom(fromTo));
    rLog.happenedTime = Time::Now();
    CGameServerLog::LogToDB(ptrLog);
}

void CUser::SetMoney(EMoneyType eMoneyType,UINT32 dwCount) 
{
    if(!GetPlayer() || eMoneyType >= EMONEY_END)
    {
        return;
    }

    UINT32& dwMoney = GetMoneyVarible(eMoneyType);
    if(&dwMoney == &_dwNoMoney)
    {
        return;
    }
    if (EMONEY_GOLD == eMoneyType)
    {
        RoleBaseInfo &rRoleBase = GetPlayer()->GetModifyBaseInfo();
        rRoleBase.dwFreeGold = dwCount;
    }
    else
        dwMoney = dwCount;

    return;
}

void CUser::GetMoneyList(TVecMoneyCount& vecMoneyCount)
{

    for(UINT32 i = EMONEY_NONE+1; i < EMONEY_END; i++ )
    {
        UINT32 dwValue = GetMoney((EMoneyType)i);
        if(0 != dwValue)
        {
            vecMoneyCount.emplace_back((EMoneyType)i,dwValue);
        }

        if(EMONEY_LOVEHEART == i)
        {
            LOG_INF<<"Hearts:"<<dwValue;
        }
    }

}

// ===  FUNCTION  ======================================================================
//         Name:  ExchangeMoney
//  Description:  两种类型货币兑换
// =====================================================================================
EExchangeResult CUser::ExchangeMoney(EPropType eSrcProp, EPropType eDestProp, UINT32 dwCount)
{
    EExchangeResult eResult = eExchangeResultFailed;
    if (eSrcProp == eDestProp)
        return eResult;
    EMoneyType eSrcType = EMONEY_NONE;
    EMoneyType eDestType = EMONEY_NONE;
    switch(eSrcProp)
    {
        case ePropBlueFairyFate : //蓝色仙缘
            eSrcType = EMONEY_BLUEFAIRYFATE;
            break;
        case ePropPurpleFairyFate : //紫色仙缘
            eSrcType = EMONEY_PURPLEFAIRYFATE;
            break;
        case ePropOrangeFairyFate : //橙色仙缘
            eSrcType = EMONEY_ORANGEFAIRYFATE;
            break;
        default:
            break;
    }

    if (eSrcType == EMONEY_NONE)
        return eResult;
    switch(eDestProp)
    {
        case ePropBlueFairyFate : //蓝色仙缘
            eDestType = EMONEY_BLUEFAIRYFATE;
            break;
        case ePropPurpleFairyFate : //紫色仙缘
            eDestType = EMONEY_PURPLEFAIRYFATE;
            break;
        case ePropOrangeFairyFate : //橙色仙缘
            eDestType = EMONEY_ORANGEFAIRYFATE;
            break;
        default:
            break;

    }
    if (eDestType == EMONEY_NONE)
        return eResult;

    if (static_cast<UINT8>(eSrcType) < static_cast<UINT8>(eDestType)) // 低级货币兑换为高级货币
    {
        UINT16 wRate = SParamConfig::wTavernExchangeMag * (static_cast<UINT8>(eDestType) - static_cast<UINT8>(eSrcType));
        UINT32 dwCount2 = dwCount / wRate;
        dwCount = dwCount2 * wRate;
        if (dwCount && dwCount2)
        {
            if (CanSubMoney(eSrcType, dwCount))
            {
                SubMoney(eSrcType, dwCount, ItemTo_ExchangeMoney);
                AddMoney(eDestType, dwCount2, ItemFrom_ExchangeMoney);
                eResult = eExchangeResultSuccess;
            }
            else
                eResult = eExchangeResultLack;
        }
    }
    else // 高级货币兑换为低级货币
    {
        UINT16 wRate = SParamConfig::wTavernExchangeMag * (static_cast<UINT8>(eSrcType) - static_cast<UINT8>(eDestType));
        UINT32 dwCount2 = dwCount * wRate;
        if (dwCount && dwCount2)
        {
            if (CanSubMoney(eSrcType, dwCount))
            {
                SubMoney(eSrcType, dwCount, ItemTo_ExchangeMoney);
                AddMoney(eDestType, dwCount2, ItemFrom_ExchangeMoney);
                eResult = eExchangeResultSuccess;
            }
            else
                eResult = eExchangeResultLack;
        }
    }
    return eResult;
    /*
       eExchangeResultSuccess = 0, //兑换成功
       eExchangeResultFailed, //兑换失败
       eExchangeResultLack, //兑换数量不足
       eExchangeResultLimit, //兑换已达上限
       eExchangeResultMax //兑换结果最大值
       */
}		// -----  end of function ExchangeMoney  ----- //

bool CUser::CanSubGoldOrCoupon(UINT32 dwCount, ECoinType eCoinType)
{
    if (eCoinType == eCouponCoin)
    {
        if (GetMoney(EMONEY_COUPON) >= dwCount)
            return true;
        if (GetMoney(EMONEY_GOLD) >= dwCount - GetMoney(EMONEY_COUPON))
            return true;
    }
    if (eCoinType == eGoldCoin)
    {
        if (GetMoney(EMONEY_GOLD) >= dwCount)
            return true;
        if (GetMoney(EMONEY_COUPON) >= dwCount - GetMoney(EMONEY_GOLD))
            return true;
    }
    return false;
}

bool CUser::SubGoldOrCoupon(UINT32 dwCount, ECoinType eCoinType, UINT16 toWhere, bool bNotify)
{
    if (GetMoney(EMONEY_GOLD) + GetMoney(EMONEY_COUPON) < dwCount)
        return false;

    if (eCoinType == eCouponCoin)
    {
        if (GetMoney(EMONEY_COUPON) >= dwCount)
        {
            SubMoney(EMONEY_COUPON, dwCount,(NLogDataDefine::ItemTo) (toWhere),bNotify);
        }
        else
        {
            SubMoney(EMONEY_GOLD, dwCount-GetMoney(EMONEY_COUPON),(NLogDataDefine::ItemTo)toWhere,bNotify);
            SubMoney(EMONEY_COUPON, GetMoney(EMONEY_COUPON),(NLogDataDefine::ItemTo)toWhere,bNotify);
        }
    }
    else if (eCoinType == eGoldCoin)
    {
        if (GetMoney(EMONEY_GOLD) >= dwCount)
        {
            SubMoney(EMONEY_GOLD, dwCount,(NLogDataDefine::ItemTo)toWhere,bNotify);
        }
        else
        {
            SubMoney(EMONEY_COUPON, dwCount - GetMoney(EMONEY_GOLD),(NLogDataDefine::ItemTo)toWhere);
            SubMoney(EMONEY_GOLD, GetMoney(EMONEY_GOLD),(NLogDataDefine::ItemTo)toWhere,bNotify);
        }
    }
    /*
       if(bNotify)
       {
       g_PropInfoS.ChangeMoney(*GetPlayer(), EMONEY_COUPON, _dwCoupon);
       g_PropInfoS.ChangeMoney(*GetPlayer(), EMONEY_GOLD, _dwGold);
       }
       GetPlayer()->UpdateBaseInfo2DB();
       SynToCeneterNotify(EMONEY_COUPON, _dwCoupon);
       SynToCeneterNotify(EMONEY_GOLD, _dwGold);
       */
    return true;
}
//体力增加扣除
bool CUser::CanSubAction(UINT32 dwAction)
{
    CEnergyMgrPtr pEnergyMgr = GetPlayer()->GetEnergyMgr();
    if(pEnergyMgr)
    {
        return pEnergyMgr->CanSubAction(dwAction);
    }

    return false;
}

bool CUser::AddAction(UINT32 dwAction,UINT16 fromwhere)
{
    if(!GetPlayer())
    {
        return false;
    }

    CEnergyMgrPtr pEnergyMgr = GetPlayer()->GetEnergyMgr();
    if(pEnergyMgr)
    {
        pEnergyMgr->AddAction(dwAction);
        return true;
    }

    return false;
}

bool CUser::SubAction(UINT32 dwAction,UINT16 towhere, bool bNotify)
{
    if(!GetPlayer())
    {
        return false;
    }

    CEnergyMgrPtr pEnergyMgr = GetPlayer()->GetEnergyMgr();
    if(pEnergyMgr)
    {
        return pEnergyMgr->SubAction(dwAction,bNotify);
    }

    return false;
}

UINT8 CUser::CalcVIPLevel()
{
    return CVIPMgr::Instance().CalcVIPLevel(GetTotalRecharge());
#if 0
    if (static_cast<UINT64>(Time::Now()) > GetVars().GetVar(NVarDefine::ePlayerVIPEndTime))     //VIP特权过期或者未开通
        return 0;
    UINT32 dwGrowthValue = GetVars().GetVar(NVarDefine::ePlayerVIPGrowthValue);
    if (!dwGrowthValue)
        return 0;
    return VIPMgr.CalcVIPLevel(dwGrowthValue);
#endif
}

UINT32 CUser::GetTotalRecharge() const
{
    RoleBaseInfo &rRoleBase = _pPlayer->GetModifyBaseInfo();
    return rRoleBase.dwTotalRecharge;
}

void CUser::SetTotalRecharge(UINT32 dwTotalRecharge)
{
    RoleBaseInfo &rRoleBase = _pPlayer->GetModifyBaseInfo();
    rRoleBase.dwTotalRecharge = dwTotalRecharge;
    if (GetPlayer())
        GetPlayer()->UpdateBaseInfo2DB();
}
bool CUser::AddTotalRechargeByLua(UINT16 wGoldID, UINT32 dwRecharge)
{
    if (0 == dwRecharge)
        return false;
    CMall::Instance().OnChongZhiAward(wGoldID, dwRecharge, ToThisPtr(this));
    //return AddTotalRecharge(dwRecharge);
    return AddMoney(EMONEY_GOLD, dwRecharge, NLogDataDefine::ItemFrom_Recharge);
}

bool CUser::AddTotalRecharge(UINT32 dwRecharge, bool bAddGold/* = true */)
{
    if (0 == dwRecharge)
        return false;
    RoleBaseInfo &rRoleBase = _pPlayer->GetModifyBaseInfo();
    rRoleBase.dwTotalRecharge += dwRecharge;
    g_PropInfoS.ChangeTotalRecharge(*GetPlayer(), rRoleBase.dwTotalRecharge);
    if (bAddGold)
    {
        bool bRes = AddMoney(EMONEY_GOLD, dwRecharge, NLogDataDefine::ItemFrom_Recharge);
        if (!bRes)  //XXX 以防加仙石出错!!
            LOG_CRI << "AddTotalRecharge: Add Gold Error";
    }
    GetPlayer()->UpdateBaseInfo2DB1();

    /*if (bAddGold)
    {
        bool bRes = AddMoney(EMONEY_GOLD, dwRecharge, NLogDataDefine::ItemFrom_Recharge);
        if (!bRes)  //XXX 以防加仙石出错!!
            GetPlayer()->UpdateBaseInfo2DB();
    }*/
    
    //二次
    if (GetVars().GetVar(NVarDefine::ePlayerVarRecharge) > 0)
        GetVars().AddVar(NVarDefine::ePlayerVarSecondRechargeValue, dwRecharge);
    if (GetVars().GetVar(NVarDefine::ePlayerVarSecondRechargeValue) >= SParamConfig::wSecondBuyCost 
            && GetVars().GetVar(NVarDefine::ePlayerVarSecondRechrgeStatus) == 0)
                GetVars().SetVar(NVarDefine::ePlayerVarSecondRechrgeStatus, 1);

    //首次
    GetVars().AddVar(NVarDefine::ePlayerVarRecharge, dwRecharge);
    GetVars().AddVar(NVarDefine::ePlayerVarDayRechargeGame, dwRecharge);
    if (GetVars().GetVar(NVarDefine::ePlayerVarFirstRechrgeStatus) == 0)
        GetVars().SetVar(NVarDefine::ePlayerVarFirstRechrgeStatus, 1);
    //今日冲值
     GetVars().AddVar(NVarDefine::ePlayerVarRechargeToday, dwRecharge);
     SendPkg(g_MiscProtS.BuildPkg_SyncRechargeToday(GetVars().GetVar(NVarDefine::ePlayerVarRechargeToday)));
     NMiscProt::EEveryDayReChargeAward  eResult;
     g_EveryDayRechargeMgr.GetAward(*this,eResult);
     

    //Event事件
    TVecINT32 vecParam;
    vecParam.push_back(dwRecharge);
    if (_pPlayer)
        _pPlayer->OnEvent(eEventType_VipRechargeSuccess, vecParam);
    g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropTotalRecharge,NumberToString(dwRecharge));
    SetVIPLevel(CalcVIPLevel());
    CIconAppearMgr::Instance().FinishReCharge(*this);
    return true;
}

void CUser::CheckVIPGrowthValue()
{
    UINT32 dwEndTime     = GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
    UINT32 dwDayTime     = GetVars().GetVar(NVarDefine::ePlayerVIPDayTime);
    UINT32 dwCurTime     = Time::Now();
    UINT32 dwGrowthValue = 0;
    bool bIsAdd = false;
    if (dwEndTime && dwCurTime > dwEndTime)  //VIP特权过期
    {
        if (dwCurTime > dwDayTime)
        {
            int cnt = 1;
            if (dwDayTime)
            {
                if (dwEndTime > dwDayTime)  //过期之前未结算
                {
                    cnt = (Time::TheDay(1, dwEndTime) - Time::TheDay(0, dwDayTime)) / 86400;
                    dwGrowthValue += 10*cnt;
                    dwDayTime = Time::TheDay(1, dwEndTime);
                }
                cnt = (Time::TheDay(1, dwCurTime) - Time::TheDay(0, dwDayTime)) / 86400;
            }
            /*【减少功能取消】
              dwGrowthValue = dwGrowthValue > 5*cnt ? dwGrowthValue-5*cnt : 0;
              */
            dwDayTime = Time::TheDay(1, dwCurTime);
            bIsAdd = true;
        }
    }
    else if (dwCurTime <= dwEndTime)    //VIP特权未过期
    {
        if (dwCurTime > dwDayTime)
        {
            int cnt = 1;
            if (dwDayTime)
                cnt = (Time::TheDay(1, dwCurTime) - Time::TheDay(0, dwDayTime)) / 86400;
            dwGrowthValue += 10*cnt;
            dwDayTime = Time::TheDay(1, dwCurTime);
            bIsAdd = true;
        }
    }
    if (bIsAdd)
    {
        GetVars().SetVar(NVarDefine::ePlayerVIPDayTime, dwDayTime);
        AddVIPGrowthValue(dwGrowthValue);
    }
}

void CUser::GoldConvertVIPGrowth(UINT32 dwUsedGold)
{
    if (!dwUsedGold)
        return;
    CheckVIPGrowthValue();
    UINT32 dwCurTime     = Time::Now();
    UINT32 dwEndTime     = GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
    if (!dwEndTime || dwCurTime > dwEndTime)  //没开通VIP特权或VIP特权过期
    {
        GetVars().AddVar(NVarDefine::ePlayerVIPUsedGold, dwUsedGold);
    }
    else
    {
        dwUsedGold += GetVars().GetVar(NVarDefine::ePlayerVIPUsedGold);
        GetVars().SetVar(NVarDefine::ePlayerVIPUsedGold, dwUsedGold % SParamConfig::wVIPConsumption);
        AddVIPGrowthValue(dwUsedGold / SParamConfig::wVIPConsumption);
    }
}

void CUser::AddVIPGrowthValue(UINT32 dwValue)
{
    return;     //XXX
    GetVars().AddVar(NVarDefine::ePlayerVIPGrowthValue, dwValue);
    UINT8 byOldLvl = GetVIPLevel();
    UINT8 byNewLvl = CalcVIPLevel();
    if (byNewLvl > byOldLvl)     //vip升级
    {
        //GetVars().SetVar(NVarDefine::ePlayerVIPGetDayPack, 0);
        SetVIPLevel(byNewLvl);

    }
    SendVIPInfoToClt();
}

UINT8 CUser::GetVIPLevel()
{
    /*
    if (static_cast<UINT64>(Time::Now()) > GetVars().GetVar(NVarDefine::ePlayerVIPEndTime))     //VIP特权过期或者未开通
        return 0;
    */
    return _byVIPLevel;
}

void CUser::SetVIPLevel(UINT8 byLevel)
{
    UINT8 byOldLvl = _byVIPLevel;
    if (byOldLvl != byLevel)
    {
        _byVIPLevel = byLevel;
        g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropVIPLevel,NumberToString(byLevel));

        //vip等级影响仓库格子数量
        AutoOpenDepotByVIPUp();

        //vip升级添加一个称号
        AutoAddTitleByVIPUp();
        GetPlayer()->GetActivityPkg().OnVipUp();
        if(GetPlayer()->GetMap())
            GetPlayer()->GetMap()->AppearToSurround(*GetPlayer());

        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(byLevel);
        if (_pPlayer)
            _pPlayer->OnEvent(eEventType_VipLevelChanging, vecParam);
    }
}

void CUser::PHPSetVIPLevel(UINT8 byLevel)
{
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byLevel);
#if 0
    if (pVIPLvlCfg)
        GetVars().SetVar(NVarDefine::ePlayerVIPGrowthValue, pVIPLvlCfg->_Exp);
    SVIPBaseCFGEx* pVIPBaseCfg = VIPMgr.GetVIPBaseCfg(CRandom::RandInt(1, 3));
    if (pVIPBaseCfg)
    {
        GetVars().SetVar(NVarDefine::ePlayerVIPEndTime, Time::Now()+pVIPBaseCfg->_Days*86400);
        GetVars().SetVar(NVarDefine::ePlayerVIPType, pVIPBaseCfg->_ID);
        GetVars().SetVar(NVarDefine::ePlayerVIPDayTime, Time::TheDay(1));
    }
    SetVIPLevel(byLevel);
    SendVIPInfoToClt();
#endif
    if (pVIPLvlCfg)
    {
        SetTotalRecharge(pVIPLvlCfg->_Exp);
    }
    SetVIPLevel(byLevel);
    g_PropInfoS.ChangeTotalRecharge(*GetPlayer(), pVIPLvlCfg->_Exp);
}

void CUser::SetYelloDiamondLevel(UINT8 byLevel)
{
    UINT8 byOldLvl = _byYelloDiamondLevel;
    if(byOldLvl != byLevel)
    {
        _byYelloDiamondLevel = byLevel;
        //g_Game2CenterCommC.Send_UserSyncPropNtf(_qwUsrID,eSyncPropYDLevel,NumberToString(byLevel));
    }
    GetPlayer()->SetYDLevel(_byYelloDiamondLevel);
}

UINT8 CUser::GetYelloDiamondLevel()
{
    if(!_byYelloDiamondLevel)
        SetYelloDiamondLevel(_byYelloDiamondLevel);
    return _byYelloDiamondLevel;
}

const SPlatformParam& CUser::GetCurrentPlatformParam() const
{ 
    if (_dwPlatformIndex + 1 > _vecPlatformParam.size())
        return s_sPlatformParam; 
    return _vecPlatformParam[_dwPlatformIndex];
}

const TVecPlatformParam& CUser::GetPlatformParam() const
{ 
    return _vecPlatformParam;
}

bool CUser::PlatformParamFromDB(const TVecPlatformParam& vecPlatformParam)
{
    SetPlatformParam(vecPlatformParam);
    return true;
}

bool CUser::IsSuperPlatform() const
{
    if (_vecPlatformParam.empty())
        return false;
    if (_dwPlatformIndex + 1 > _vecPlatformParam.size())
        return false;
    const SPlatformParam& rPlatformParam = _vecPlatformParam[_dwPlatformIndex];
    return (rPlatformParam.bySPType & (1 << ePBBitSuper)) ? true:false;
}

bool CUser::IsYealyPlatform() const
{
    if (_vecPlatformParam.empty())
        return false;
    if (_dwPlatformIndex + 1 > _vecPlatformParam.size())
        return false;
    const SPlatformParam& rPlatformParam = _vecPlatformParam[_dwPlatformIndex];
    return (rPlatformParam.bySPType & (1 << ePBBitYearly)) ? true:false;
}

bool CUser::IsYellowDiamond() const
{
    if (_vecPlatformParam.empty())
        return false;
    if (_dwPlatformIndex + 1 > _vecPlatformParam.size())
        return false;
    const SPlatformParam& rPlatformParam = _vecPlatformParam[_dwPlatformIndex];
    return (rPlatformParam.byQQPtType == eQQPtTypeYellow  && (rPlatformParam.byQQPtLv >= 1)) ? true:false;
}

bool CUser::SetPlatformParam(const TVecPlatformParam& vecPlatformParam)
{
    for (auto& rInfo : vecPlatformParam)
    {
        EDataChange eDataChange = eOpAdd;
        bool bUpdate = false;
        bool bFound = false;
        UINT32 dwIndex = 0;

        for (auto& rPlatformParam : _vecPlatformParam)
        {
            if (rPlatformParam.byPtType == rInfo.byPtType
                    && rPlatformParam.byQQPtType == rInfo.byQQPtType)
            {
                bFound = true;
                if(rPlatformParam.byQQPtLv != rInfo.byQQPtLv
                        || rPlatformParam.bySPType != rInfo.bySPType)
                {

                    bUpdate = true;
                    eDataChange = eOpUpdate;
                    rPlatformParam = rInfo;
                }
                _dwPlatformIndex = dwIndex;
                break;
            }
            ++dwIndex;
        }
        if (!bFound)
        {
            bUpdate = true;
            _dwPlatformIndex = _vecPlatformParam.size();
            _vecPlatformParam.push_back(rInfo);
        }
        if(bUpdate)
        {
            UpdateYD2DB(rInfo, eDataChange);
            g_Game2CenterCommC.Send_UpdatePlatformParam(GetRoleID(), _vecPlatformParam, _dwPlatformIndex);
        }
    }
    return true;
}

void CUser::SetEnterString(const TVecString& vecEnterString)
{
    _vecEnterString = vecEnterString;
    _vecEnterString.resize(4);
    g_Game2CenterCommC.Send_UpdateEnterString(GetRoleID(), _vecEnterString);
}

void CUser::UpdateYD2DB(const SPlatformParam& rInfo,EDataChange eDataChange) const
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(),eTypeYelloDiamond, eDataChange, strData);
}

void CUser::SendVIPInfoToClt()
{
    SVIPData stVIPData;
    /*
    stVIPData.byType        = GetVars().GetVar(NVarDefine::ePlayerVIPType);
    stVIPData.dwGrowthValue = GetVars().GetVar(NVarDefine::ePlayerVIPGrowthValue);
    stVIPData.dwEndTime     = GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
    */
    stVIPData.dwMonthCardEndTime = GetVars().GetVar(NVarDefine::ePlayerVarMonthCardEndTime);
    stVIPData.dwDayPack     = GetVars().GetVar(NVarDefine::ePlayerVIPGetDayPack);
    stVIPData.dwLvlAward    = GetVars().GetVar(NVarDefine::ePlayerVIPGetLevelAward);
    SendPkg(g_VIPProtS.BuildPkg_SelfVIPInfo(stVIPData));
    if (stVIPData.dwMonthCardEndTime && time(NULL) >= stVIPData.dwMonthCardEndTime && 0 == GetVars().GetVar(NVarDefine::ePlayerVarMonthCardOverNotice))
    {
        SendPkg(g_VIPProtS.BuildPkg_UpdateMonthCardOverdue(1));
        GetVars().SetVar(NVarDefine::ePlayerVarMonthCardOverNotice, 1);
    }
}

bool CUser::HasTempVIPPrivilege()
{
    SBuffInfo stBuffInfo;
    if (GetPlayer() && GetPlayer()->GetBuffData(SParamConfig::wTempVIPPrivilege, stBuffInfo) == eBORSuccess)
        return true;
    return false;
}

//接收：请求开启个人月卡
bool CUser::OpenSelfMonthCard()
{
    bool bMark = false;
    UINT32 dwEndTime = GetVars().GetVar(ePlayerVarMonthCardEndTime);
    dwEndTime = dwEndTime <= time(NULL) ? time(NULL) : dwEndTime;
    UINT32 dwNow = time(NULL);
    dwEndTime = dwEndTime <= dwNow ? dwNow : dwEndTime;
    if (dwEndTime == dwNow)
    {
        bMark = true;
        GetVars().SetVar(ePlayerVarMonthCardGetTime, 0);
    }
    GetVars().SetVar(ePlayerVarMonthCardEndTime, dwEndTime+SParamConfig::dwMonthCardTime);
    GetVars().DelVar(ePlayerVarMonthCardOverNotice);
    SendVIPInfoToClt();
    SendMonthCardAward();

    if(GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        GetPlayer()->OnEvent(eEventType_MonthCard,vecParam);
    }

    string strPkg;
    if (!bMark)
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonthCardRenew);
    else
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonthCardBuy);
    SendPkg(strPkg);

    return true;
}

void CUser::SendMonthCardAward()
{
    UINT32 dwEndTime = GetVars().GetVar(NVarDefine::ePlayerVarMonthCardEndTime);
    UINT32 dwNow = time(NULL);
    if (!dwEndTime)
        return;
    if (dwEndTime < dwNow)
    {
        if (0 == GetVars().GetVar(NVarDefine::ePlayerVarMonthCardOverNotice))
        {
            SendPkg(g_VIPProtS.BuildPkg_UpdateMonthCardOverdue(1));
            GetVars().SetVar(NVarDefine::ePlayerVarMonthCardOverNotice, 1);
        }
        return;
    }
    UINT32 dwGetTime = GetVars().GetVar(NVarDefine::ePlayerVarMonthCardGetTime);
    dwGetTime = dwGetTime == 0 ? dwNow : dwGetTime;
    int iDays = (Time::TheDay(1, dwNow) - Time::TheDay(0, dwGetTime)) / 86400;
    //LOG_WRN << "iDays:" << iDays << " UserID:" << GetUserID() << " dwGetTime:" << dwGetTime << " dwNow:" << dwNow;
    if (iDays <= 0)
        return;
    GetVars().SetVar(NVarDefine::ePlayerVarMonthCardGetTime, Time::TheDay(1, dwNow));
    //发送邮件
    TVecUINT64 vecTargets;
    vecTargets.push_back(GetUserID());
    TVecItemGenInfo vecItems;
    SItemGenInfo stItemGen;
    stItemGen.wItemID = EMONEY_GOLD;
    stItemGen.dwCount = SParamConfig::wMonthCardRebate*iDays;
    stItemGen.eBindType = eBindGet;
    vecItems.push_back(stItemGen);
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_MONTHCARD;
    stBody.vecParam.push_back(NumberToString(iDays));
    stBody.vecParam.push_back(NumberToString(stItemGen.dwCount));
    GameServerSysMail::SendSysMail(SEND_MONTHCARD, TITLE_MONTHCARD, stBody, vecTargets, &vecItems);
    if (dwNow + 86400 >= dwEndTime)
    {
        //发送过期邮件
        TVecUINT64 vecTargets;
        vecTargets.push_back(GetUserID());
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_MONTHCARD_OVERDUE;
        GameServerSysMail::SendSysMail(SEND_MONTHCARD_OVERDUE, TITLE_MONTHCARD_OVERDUE, stBody, vecTargets);
    }
}

//XXX 蜀山基金活动
void CUser::SendShushanFoundInfo()
{
    UINT64 qwValue = GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundInfo);
    UINT32 dwLoginDays = GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundLoginDays);

    UINT32 wGrowFoundInfo   = GET_BIT_16(qwValue, 0);
    UINT32 wPExpFoundInfo   = GET_BIT_16(qwValue, 1);
    UINT32 wSilverFoundInfo = GET_BIT_16(qwValue, 2);
    UINT32 wItemFoundInfo   = GET_BIT_16(qwValue, 3);
    string strData = g_DayActProtS.BuildPkg_ShushanFoundChangeNotify(wGrowFoundInfo,wPExpFoundInfo,wSilverFoundInfo,wItemFoundInfo,dwLoginDays);
    SendPkg(strData);
}

bool CUser::CanDelShushanFoundIcon()
{
    bool bRes = true;
    UINT64 qwValue = GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundInfo);

    for (size_t i = 0; i < 4; ++ i)
    {
        UINT16 wValue = GET_BIT_16(qwValue, i);
        if (GET_BIT(wValue, 0) == 0)    //未购买
            continue;
        UINT8 byGetCount = 0;
        for (size_t j = 1; j < 8; ++ j)
        {
            if ((wValue & (1 << j)) > 0)
                ++ byGetCount;
        }
        if (byGetCount < 7)
        {
            bRes = false;
            break;
        }
    }
    if (bRes)
    {
        UINT32 dwCreatTime = GetPlayer()->GetCreateTime();
        if (dwCreatTime + 86400*7 > time(NULL))
            bRes = false;
    }
    return bRes;
}

bool CUser::AutoOpenDepotByVIPUp()
{
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(GetVIPLevel());
    if (!pVIPLvlCfg || !pVIPLvlCfg->_StoreNum)
        return false;
    CDepot& rStore = GetDepot();
    UINT16 wCap = rStore.GetCapacity();
    if (pVIPLvlCfg->_StoreNum <= wCap)
        return false;
    if (eItemSucceed != rStore.Expand(pVIPLvlCfg->_StoreNum - wCap))
    {
        LOG_CRI << "VIP Open Depot Error! VIP level: " << GetVIPLevel();
        return false;
    }
    return true;
}

void CUser::SetSign(const std::string& strSign)
{
    _pPlayer->SetSign(strSign);
}

void CUser::SetMood(UINT16 wMood)
{
    _pPlayer->SetMood(wMood);
}

void CUser::TimerCheck(time_t tNow)
{
    _pPlayer->GetActionManager().TimerCheck(tNow);
    _pPlayer->TimerCheck(tNow);

    if(tNow > _tAddOnLineTime + ONLINE_UPDATE_TIME)
    {
        CGameVar& rCGameVar = GetVars();
        UINT32 dwOnLineTime = rCGameVar.GetVar(NVarDefine::ePlayerOnLineTime) + ONLINE_UPDATE_TIME;
        rCGameVar.SetVar(NVarDefine::ePlayerOnLineTime,dwOnLineTime);

        _tAddOnLineTime = tNow;
        TVecINT32 vecParam;
        vecParam.push_back(dwOnLineTime/60); //分钟为单位
        _pPlayer->OnEvent(eEventType_OnlineTime,vecParam);
    }
    // TODO:
    if(_bIndulge)
    {
        if(_dwKickTime)
        {
            if(_dwKickTime>Time::Now())
            {
                CUserMgr::KickUserOffLineReason(_qwUsrID,NServerCommon::eIndulgeTimeKick);
            }
            return;
        }

        if(Time::Now() > _tDiffTime)
        {
            UpdateIndulgeStatus();
            _tDiffTime =  Time::Now() + INDULGE_UPDATE_TIME;
        }

        CGameVar& rCGameVar = GetVars();
        UINT32 dwRecordTime = rCGameVar.GetVar(NVarDefine::ePlayerVarIndulgeTime);
        if( dwRecordTime > 3 * PER_HOUR_TO_S)
        {
            UpdateIndulgeStatus();
            UINT32 dwIndulgeLoginTime = GetPlayer()->GetIndulgeLoginTime();
            if(0 == dwIndulgeLoginTime )
            {
                UINT32 dwNextLoginTime = Time::Now() + 5 * PER_HOUR_TO_S;
                GetPlayer()->SetIndulgeLoginTime(dwNextLoginTime);
                GetPlayer()->UpdateBaseInfo2DB();
                //save
                //SendSysMsg(83);
                //kick
                CUserMgr::KickUserOffLineReason(_qwUsrID,NServerCommon::eIndulgeKick);

            }
            else if(dwIndulgeLoginTime > Time::Now())
            {
                //SendSysMsg(84);
                //T 人
                //CUserMgr::KickUserOffLineReason(_qwUsrID,NServerCommon::eIndulgeTimeKick);
                UINT32 dwT = dwIndulgeLoginTime - Time::Now();
                SendPkg(g_MiscProtS.BuildPkg_IndulgeNextLoginTime(dwT));
                _dwKickTime = Time::Now() + 5;
                LOG_INF<<"KICK NEXT TIME:"<<dwT;
            }
            else
            {
                rCGameVar.SetVar(NVarDefine::ePlayerVarIndulgeTime,0);
                GetPlayer()->SetIndulgeLoginTime(0);
                GetPlayer()->UpdateBaseInfo2DB();

            }

        }



    }
}

//角色地图同步
void CUser::BroadcastUserSync(const string& strMsg, bool bNotifySelf /*= true*/)
{
    // TODO:
}

void CUser::OnEnterToCrossSvr(const TVecString& vecParam)
{
    // TODO:
}

void CUser::OnEnterFromCrossSvr(const TVecString& vecParam)
{
    // TODO:
}

void CUser::OnReEnterCrossSvr()
{
    // TODO:
}

CPack& CUser::GetPack() { return _oPack; }
CDepot& CUser::GetDepot() { return _oDepot; }
CGameVar& CUser::GetVars() { return _oVars; }

// 根据各种条件解锁新法宝
bool CUser::TryUnlockTrump(const TVecUINT16& rvecActiveID, const TVecUINT32& rvecActiveValue)
{
    bool bCanUnlock = true;

    auto it = rvecActiveID.begin();
    auto it2 = rvecActiveValue.begin();
    for (it = rvecActiveID.begin(), it2 = rvecActiveValue.begin(); it != rvecActiveID.end() && it2 != rvecActiveValue.end(); ++it, ++it2)
    {
        switch(*it)
        {
            case 1:     // 等级
                if (GetPlayer()->GetLevel() < *it2)
                    bCanUnlock = false;
                break;
            case 2:     // 道具
                if (!GetPack().HasItem(static_cast<UINT16>(*it2)))
                    bCanUnlock = false;
                break;
            case 3:     // 成就
                break;
            default:
                break;
        }
        if (!bCanUnlock)
            break;
    }
    if (bCanUnlock)
    {
        for (it = rvecActiveID.begin(), it2 = rvecActiveValue.begin(); it != rvecActiveID.end() && it2 != rvecActiveValue.end(); ++it, ++it2)
        {
            switch(*it)
            {
                case 1:     // 等级
                    break;
                case 2:     // 道具
                    GetPack().DelItemByItemID(static_cast<UINT16>(*it2), 1, true, NLogDataDefine::ItemTo_TrumpActive);
                    break;
                case 3:     // 成就
                    break;
                default:
                    break;
            }
        }
    }
    return bCanUnlock;
}

CStore* CUser::GetStoreByType(EStoreType eStoreType)
{
    switch(eStoreType)
    {
        case eStorePack:
            return &_oPack;
        case eStoreDepot:
            return &_oDepot;
        default:
            break;
    }
    return NULL;
}

bool CUser::StoreToStream(EStoreType eStoreType, SStoreStream& stStoreStream)
{
    CStore* pStore = NULL;
    switch (eStoreType)
    {
        case eStorePack:
            pStore = &_oPack;
            break;

        case eStoreDepot:
            pStore = &_oDepot;
            break;
        case eStorePlayerCitta:
            {
                CPlayerPtr pPlayer = GetPlayer();
                if(!pPlayer)
                {
                    LOG_DBG << "Slot Capacity error1.";
                    return false;
                }
                pStore = &pPlayer->GetFighterManager()->GetCittaSlots();
            }
            break;
        case eStorePlayerTrump:
            {
                CPlayerPtr pPlayer = GetPlayer();
                if(pPlayer)
                    pStore = &pPlayer->GetFighterManager()->GetTrumpSlots();
            }
            break;
        default:
            break;
    }

    if (!pStore)
        return false;

    pStore->ToStream(stStoreStream);
    return true;
}

bool CUser::RoleToStream(SRoleStream& stRoleStream)
{
    if (!_pPlayer)
        return false;

    CHeroFighterPtr pFighter = _pPlayer->GetMainFighter();
    if (pFighter)
    {

        bool bRet = pFighter->ToProt(stRoleStream.oMainFighter);
        if (bRet)
        {
            CPlayerPtr pPlayer = GetPlayer();
            if(pPlayer)
            {
                CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
                if (pFighterManager)
                    pFighterManager->GetFashionSlots().ToProt(stRoleStream.oMainFighter.oEquips);
            }
        }
        return bRet;
    }
    return false;
}

bool CUser::GetFighters(TVecFighterSpecInfo& vecFighters)
{
    if (!_pPlayer)
        return false;
    CFighterManagerPtr& pFighterManager = _pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;
    pFighterManager->ToStream(vecFighters);
    return true;
}

void CUser::SyncData(RoleBaseInfo& info)
{
    /*
       info.dwGold             = _dwGold;
       info.dwSilver           = _dwSilver;
       info.dwCoupon           = _dwCoupon;
       info.dwSoul             = _dwSoul;
       info.dwPrestige         = _dwPrestige;
       info.dwHonor            = _dwHonor;
       info.dwPExp             = _dwPExp;
       info.dwSigil            = _dwSigil;
       info.dwCentsY           = _dwCentsY;
       info.dwAction           = _dwAction;
       info.dwSop              = _dwSop;
       info.dwTaoism           = _dwTaoism;
       info.dwPoten            = _dwPoten;
       info.dwReiki            = _dwReiki;
       info.dwHFP              = _dwHFP;
       info.dwDemonSoul        = _dwDemonSoul;         //锁妖塔魂值
       info.dwSoulAttack       = _dwSoulAttack;        //攻击之魄
       info.dwSoulHp           = _dwSoulHp;            //生命之魄
       info.dwSoulCritical     = _dwSoulCritical;      //暴击之魄
       info.dwSoulCounter      = _dwSoulCounter;       //破击之魄
       info.dwSoulSpeed        = _dwSoulSpeed;         //身法之魄
       info.dwSoulDefence      = _dwSoulDefence;       //防御之魄
       info.dwSoulHit          = _dwSoulHit;           //命中之魄
       info.dwSoulDodge        = _dwSoulDodge;         //闪避之魄
       info.dwStampHuang       = _dwStampHuang;        //黄阶除魔印
       info.dwStampXuan        = _dwStampXuan;         //玄阶除魔印
       info.dwStampDi          = _dwStampDi;           //地阶除魔印
       info.dwStampTian        = _dwStampTian;         //天阶除魔印
       info.dwStampXing        = _dwStampXing;         //星阶除魔印
       info.dwStampYue         = _dwStampYue;          //月阶除魔印
       info.dwStampDi2         = _dwStampDi2;          //帝阶除魔印
       info.dwStampXian        = _dwStampXian;         //仙阶除魔印
       info.dwStampSheng       = _dwStampSheng;        //圣阶除魔印
       info.dwStampFo          = _dwStampFo;           //佛阶除魔印
       info.dwAchievementAP    = _dwAchievementAP;     //成就点
       info.dwCollectAP        = _dwCollectAP;         //收藏点
       */
}

UINT64 CUser::Test64(UINT64 p)
{
    fprintf(stderr, "%s: %" I64_FMT "u\n", __PRETTY_FUNCTION__, p);
    return 0xffffffffffffffffLL;
}
CTaskPkg& CUser::GetTaskPkg()
{
    return _oTaskPkg;
}

//19点重置事件仅在线玩家执行
void CUser::OnDayReset(ETimePointType eType)
{
    CPlayerPtr pPlayer =  GetPlayer();
    if(pPlayer)
    {
        pPlayer->OnMidNight(eType);
    }
}

/*
// 保存Buff相关数据
void CUser::UpdateBuff2DB(const SBuffInfo& rBuffInfo, EDataChange eDataChange)
{
CPlayerPtr pPlayer = GetPlayer();
if (pPlayer)
pPlayer->UpdateBuff2DB(rBuffInfo, eDataChange);
}

void CUser::OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo)
{
TVecBuffInfo vecInfo;
vecInfo.push_back(rInfo);
string strData = g_RoleEventProtS.BuildPkg_BuffNotify(eType, vecInfo);
SendPkg(strData);
}
*/
void CUser::AddFashionItemForRobot()
{
    if (_pPlayer)
        _pPlayer->AddFashionItemForRobot();
}
//机器人
void CUser::RobotBoost(UINT32 dwMode)
{
    if (_pPlayer)
        _pPlayer->RobotBoost(dwMode);
}

// 新手一键加速
void CUser::Boost(UINT32 dwMode)
{
    AddMoney(EMONEY_SILVER, 790000,NLogDataDefine::ItemFrom_GM);
    AddMoney(EMONEY_PEXP, 80000,NLogDataDefine::ItemFrom_GM);
    if (_pPlayer)
        _pPlayer->Boost(dwMode);
}

// 帐号变得超级牛逼
void CUser::Super()
{
    MoneySuper();
    VIPSuper();
}

void CUser::MoneySuper()
{
    for (UINT8 byIndex = EMONEY_NONE; byIndex < EMONEY_END; ++ byIndex)
    {
        EMoneyType eType = static_cast<EMoneyType>(byIndex);
        AddMoney(eType, CBoostMgr::Instance().GetMoney(eType), NLogDataDefine::ItemFrom_GM);

    }
}

void CUser::VIPSuper()
{
#if 0
    UINT8 byLevel = CBoostMgr::Instance().GetVIPLevel();
    if (byLevel == 0)
    {
        SetVIPLevel(byLevel);
        GetVars().DelVar(NVarDefine::ePlayerVIPGrowthValue);
        GetVars().DelVar(NVarDefine::ePlayerVIPEndTime);
        GetVars().DelVar(NVarDefine::ePlayerVIPType);
        GetVars().DelVar(NVarDefine::ePlayerVIPGetDayPack);
        GetVars().DelVar(NVarDefine::ePlayerVIPGetLevelAward);
    }
    else
    {
        SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byLevel);
        if (pVIPLvlCfg)
            GetVars().SetVar(NVarDefine::ePlayerVIPGrowthValue, pVIPLvlCfg->_Exp);

        SVIPBaseCFGEx* pVIPBaseCfg = VIPMgr.GetVIPBaseCfg(CRandom::RandInt(1, 3));

        if (pVIPBaseCfg)
        {
            GetVars().SetVar(NVarDefine::ePlayerVIPEndTime, Time::Now() + pVIPBaseCfg->_Days * 86400);
            GetVars().SetVar(NVarDefine::ePlayerVIPType, pVIPBaseCfg->_ID);
            GetVars().SetVar(NVarDefine::ePlayerVIPDayTime, Time::TheDay(1));
        }

        SetVIPLevel(byLevel);
        SendVIPInfoToClt();
    }
#endif
    UINT8 byLevel = CBoostMgr::Instance().GetVIPLevel();
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byLevel);
    if (pVIPLvlCfg)
    {
        SetTotalRecharge(pVIPLvlCfg->_Exp);
    }
    SetVIPLevel(byLevel);
    SendVIPInfoToClt();
}

void CUser::NoticeStory(UINT16 wStoryID,UINT8 byType,UINT32 dwParam)
{
    SendPkg(g_TaskProtS.BuildPkg_NotifyStory(wStoryID,byType,dwParam));
}

time_t CUser::GetOffLineTime() const
{
    if(_eUserState == eUserLeaveAway)
    {
        return Time::Now() - _tLastCheckTime;
    }
    return 0;
}

UINT64 CUser::GetRoleID() const
{
    if(_pPlayer)
    {
        return _pPlayer->GetRoleID();
    }
    return 0;
}

void CUser::SendSysMsg(UINT32 dwMsgID)
{
    SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(dwMsgID)); 
}

void CUser::SetIndulge(bool bIndulge)
{
    LOG_INF<<"SetIndulge: bIndulge "<<bIndulge;
    _bIndulge = bIndulge;
    if(_bIndulge)
    {
        CGameVar& rCGameVar = GetVars();
        UINT32 dwValue = rCGameVar.GetVar(NVarDefine::ePlayerVarIndulgeTime);
        if(0 == dwValue)
        {
            rCGameVar.SetVar(NVarDefine::ePlayerVarIndulgeTime,1);
        }

        SendPkg(g_MiscProtS.BuildPkg_IndulgeTimeNotify(dwValue));
        _tIndulgeTime = Time::Now();
    }
}

void CUser::UpdateIndulgeStatus()
{
    if(!_bIndulge)
    {
        return;
    }
    CGameVar& rCGameVar = GetVars();
    UINT32 dwRecordTime = rCGameVar.GetVar(NVarDefine::ePlayerVarIndulgeTime);

    if(Time::Now() > _tIndulgeTime)
    {
        UINT32 dwOldTime = dwRecordTime;

        dwRecordTime += (Time::Now() -_tIndulgeTime);

        rCGameVar.SetVar(NVarDefine::ePlayerVarIndulgeTime,dwRecordTime);
        _tIndulgeTime = Time::Now();

        if(dwOldTime< 1 * PER_HOUR_TO_S && dwRecordTime >=1 * PER_HOUR_TO_S)
        {
            LOG_INF<<"Indulge ONE HOUR";
            SendPkg(g_MiscProtS.BuildPkg_IndulgeTimeNotify(dwRecordTime));
        }
        if(dwOldTime< 2 * PER_HOUR_TO_S && dwRecordTime >=2 * PER_HOUR_TO_S)
        {
            LOG_INF<<"Indulge TWO HOUR";
            SendPkg(g_MiscProtS.BuildPkg_IndulgeTimeNotify(dwRecordTime));
        }
        //SendPkg(g_MiscProtS.BuildPkg_IndulgeTimeNotify(dwRecordTime)); 
        //LOG_INF<<"Indulge:"<<dwRecordTime;
    }

    while (_wIncome > 0)
    {
        if (_wIncome == GAME_COEF_PERCENT)
        {
            if (dwRecordTime >= 3 * PER_HOUR_TO_S)
                _wIncome = GAME_COEF_PERCENT / 2;
            else
                break;
        }
        else if (_wIncome == GAME_COEF_PERCENT / 2)
        {
            if (dwRecordTime >= 5 * PER_HOUR_TO_S)
                _wIncome = 0;
            else
                break;
        }
    }
    //LOG_INF<<"GetIndulgeRate"<<(1.0f * _wIncome / GAME_COEF_PERCENT);
}

void CUser::GMAddIndulgeTime(UINT32 dwTime)
{
    CGameVar& rCGameVar = GetVars();
    UINT32 dwRecordTime = rCGameVar.GetVar(NVarDefine::ePlayerVarIndulgeTime);
    {
        dwRecordTime += dwTime;
        rCGameVar.SetVar(NVarDefine::ePlayerVarIndulgeTime,dwRecordTime);
        _tIndulgeTime = Time::Now();

        LOG_INF<<"GMAddIndulgeTime: "<<dwRecordTime;
        SendPkg(g_MiscProtS.BuildPkg_IndulgeTimeNotify(dwRecordTime)); 
    }
}

void CUser::SetIndulgeRate(UINT32 dwIndulgeRate)
{
    LOG_INF<<"SetIndulgeRate:"<< dwIndulgeRate;
    _wIncome = dwIndulgeRate;
}

double CUser::GetIndulgeRate()
{
    return (1.0f * _wIncome / GAME_COEF_PERCENT);  
    /*if (_bIndulge)
    {
        return (1.0f * _wIncome / GAME_COEF_PERCENT);  
    }
    return 1.0f;*/
}

void CUser::ActiveTripodFire(UINT16 wFireID)
{
    g_Game2CenterCommC.Send_ActiveTripodFire(_qwUsrID, wFireID);
}

bool CUser::AutoAddTitleByVIPUp()
{
    const SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(GetVIPLevel());
    if(pCfgVip == NULL)
        return false;

    Tokenizer tk(pCfgVip->_Title, "|");
    for (size_t i=0; i<tk.size(); ++i)
    {
        UINT16 wTitleId = atoi(tk[i].c_str());
        if (wTitleId > 0)
        {
            STitle *pTitle = GetPlayer()->GetTitlePkg().GetTitle(wTitleId);
            if(pTitle == NULL)
            {
                /*
                UINT32 dwCurTime = Time::Now();
                UINT32 dwEndTime = GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
                if (dwEndTime > dwCurTime)
                    GetPlayer()->GetTitlePkg().AddTitle(wTitleId, (dwEndTime-dwCurTime), false);
                */
                GetPlayer()->GetTitlePkg().AddTitle(wTitleId, 0, false);
            }
        }
    }
    return true;
}

UINT32 CUser::ToSize()
{
    UINT32 dwSize = sizeof(*this);

    LOG_INF<<"CUser:"<<sizeof(*this);

    dwSize += _oPack.ToSize();
    if(_pPlayer)
    {
        dwSize += _pPlayer->ToSize();
    }

    return dwSize;
}

void CUser::FixQQAlarmSuc()
{
   UINT64 qwVar = GetVars().GetVar(ePlayerQQAlarm);
   qwVar = qwVar | 1;
   GetVars().SetVar(ePlayerQQAlarm,qwVar);
   {
    //Event事件
    TVecINT32 vecParam;
    UINT32 dwTmp = 1;
    vecParam.push_back(dwTmp);
    if (_pPlayer)
        _pPlayer->OnEvent(eEventType_QQAlarmClock, vecParam);
   }
}

void CUser::AddIconByLua(UINT16 wIcon)
{
    if(_pPlayer)
        _pPlayer->OpenIcon(wIcon);
    TVecUINT16 vecIconAppear;
    vecIconAppear.push_back(wIcon);
    CIconAppearMgr::Instance().SynToClientAddIconAppear(*this,vecIconAppear);
}

void CUser::DelIconByLua(UINT16 wIcon)
{
    if(_pPlayer)
        _pPlayer->DelIcon(wIcon);
    CIconAppearMgr::Instance().CloseActionToClient(*this,wIcon);
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

