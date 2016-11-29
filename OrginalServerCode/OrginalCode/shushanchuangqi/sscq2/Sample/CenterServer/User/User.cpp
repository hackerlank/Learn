/********************************************************************
//	Center Server Source File.
//	File name:	User.cpp
//	Created:	2011/06/06	10:00
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
#include "Utils.h"
#include "User.h"
#include "UserMgr.h"
#include "SvrInfo.h"
#include "Protocols.h"
#include "UserInfoMgr.h"
#include "ProtoCommon.h"
#include "GuildUser.h"
#include "TeamMananger.h"
#include "GuildUserMgr.h"
#include "Title.h"
#include "ArenaManager.h"
#include "VarDefine.h"

using namespace NProtoCommon;

bool CUser::bUdpTest = false;

bool COpLock::AddLock(eLockType eLock, UINT8 byTime)
{
    auto it = _mapLock.find(eLock);
    UINT32 dwNow = time(NULL);
    if(it != _mapLock.end())
    {
        if(  dwNow < it->second + byTime)
        {
            LOG_CRI << _rUser.GetUserID() << "Lock by " << eLock;
            return false;
        }

    }
    _mapLock[eLock] =  dwNow;
    return true;
}

void COpLock::UnLock(eLockType eLock)
{
    _mapLock.erase(eLock);
}


CUser::CUser(UINT64 qwUsrID) :
    _qwUsrID(qwUsrID),
    _dwSessionID(0), _byAddrType(0), _dwGameSvrID(0), _dwRecvFailCount(0), _eUserState(eUserNone), _bAlreadyReqDB(false),
    _eCareer(ECAREER_ALL),_eSex(ESEX_ALL), _byLevel(0), _byNation(0), _byGMLvl(0), _wFighterID(0), _dwTotalRecharge(0), _dwLoginTime(0),
    _dwOfflineTime(0), _dwLockExpireTime(0), _dwForbExpireTime(0), _dwCreateTime(0), _byVIPLevel(0), _dwGold(0), _dwSilver(0), _dwCoupon(0),/* _byTitle(0),*/
#ifdef QQ_VERSION
    _byDomain(0), _byDomainLvl(0), _byDisplayLvl(0), _byDomainYear(0),
#endif
    _byWallow(0), _wMood(0),
    _tLastCheckTime(0), _tLastWhisperTime(0), _tLastWorldTime(0), _tLastCountryTime(0),
    _dwLastOnlineTime(0),
    _bGateUserReplaced(false), _bGameUserReplaced(false), _bDBUserReplaced(false),
    _bAllSysOpen(false),/*m_dwGateId(0),*/ _oFriend(*this),_oMailBox(*this),_sVar(*this),
    _wQueryRoom(0),_dwFighterPower(0), _wPlayerFighterID(0), _byQuality(0), _bHasLoadLadderReport(false), _oTripodFire(*this), _dwPlatformIndex(0),_rShipPkg(*this),_opLock(*this),_dwLastSendZero(0)
{
#ifdef QQ_VERSION
    MEMZRO(_szOpenId, sizeof(_szOpenId));
    MEMZRO(_szOpenKey, sizeof(_szOpenKey));
#endif
    _dwLastAddItemCD = 0;
    _vecEnterString.resize(4);
}

CUser::~CUser()
{
    if (_pGuildUser)
        _pGuildUser->SetUser(NULL);
    _pGuildUser = NULL;
}

bool CUser::IsOnLine()
{
    return  _eUserState == eUserInGame || _eUserState == eUserReplace;
}

void CUser::OnRecvFail()
{
    ++_dwRecvFailCount;
    if(_dwRecvFailCount > 10)
    {
        CUserMgr::KickUserOffLine(_qwUsrID, true);
        LOG_INF << "CUser::OnRecvFail() RemoveUser" << _qwUsrID;
        CUserMgr::RemoveUser(_qwUsrID);
    }
}

bool CUser::IsInCrossServer()
{
    UINT32 dwGameSvrID = GetGameSvrID();
    return Config._wCrossGroup == GetServerGroup(dwGameSvrID);
}

void CUser::SetState(EUserState eState)
{
    LOG_INF << "set state Is "<< eState;
    _eUserState = eState;
    _tLastCheckTime = time(NULL);
    if (eState == eUserLeaveAway)
    {
        _dwLastOnlineTime = time(NULL);
        if (_pGuildUser)
        {
            _pGuildUser->SetLastOnlineTime(_dwLastOnlineTime);
            //_pGuildUser->SetUser(NULL);
        }
    }
    if (eState == eUserInGame)
    {
        _dwLastSendZero = _tLastCheckTime;
        if (!_pGuildUser)
            _pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(GetUserID());
        if (_pGuildUser)
            _pGuildUser->SetLastOnlineTime(_dwLastOnlineTime);
    }
    g_TeamManager.PlayerOffLine(_qwUsrID);

}

bool CUser::CheckStateTime(UINT32 dwInterval)
{
    time_t tNow = time(NULL);
    if(tNow > _tLastCheckTime && tNow - _tLastCheckTime >= dwInterval)
        return true;
    return false;
}

void CUser::RequestDB()
{
    // TODO: Game告诉Center需要加载的相关数据
    if(!_bAlreadyReqDB)
    {
        // TODO:
        _bAlreadyReqDB = true;
    }
    else
    {
        // TODO:
    }
}

const std::string CUser::GetFixdUserName() const
{
    // TODO:
    return GetUserName();
}

void CUser::SetVIPLevel(UINT8 byLevel) 
{ 
    _byVIPLevel = byLevel; 
    CGuildUserPtr pGuildUser = GetGuildUser();
    if (pGuildUser)
        pGuildUser->SetVIPLevel(byLevel);
    _oFriend.ChangeVIPLevel(byLevel);
}

void CUser::SetNation(UINT8 byNation)
{
    _byNation = byNation;
}

void CUser::SetOpenId(char* szOpenId)
{
    buf::cpystr(szOpenId, _szOpenId, sizeof(_szOpenId));
}

void CUser::SetOpenKey(char* szOpenKey)
{
    buf::cpystr(szOpenKey, _szOpenKey, sizeof(_szOpenKey));
}

UINT8 CUser::calcVIPLevel(UINT32 total)
{
    // TODO:
    static UINT32 KVIPS[] = {88,888,1888,5888,18888,58888,88888,188888,288888,588888,988888,1888888,2888888,5888888,8888888};
    for (UINT8 i = 0; i < sizeof(KVIPS)/sizeof(UINT32); ++i)
    {
        if (total < KVIPS[i])
            return i;
    }
    return 0;
}

void CUser::ChangeGold(INT32 gold)
{
    if (gold > 0)
        _dwGold += gold;
    else if (_dwGold >= static_cast<UINT32>(gold))
        _dwGold += gold;
}

void CUser::ChangeSilver(INT32 silver)
{
    if (silver > 0)
        _dwSilver += silver;
    else if (_dwSilver >= static_cast<UINT32>(silver))
        _dwSilver += silver;
}

void CUser::ChangeCoupon(INT32 coupon)
{
    if (coupon > 0)
        _dwCoupon += coupon;
    else if (_dwCoupon >= static_cast<UINT32>(coupon))
        _dwCoupon += coupon;
}

void CUser::ChangeSoul(INT32 soul)
{
    if (soul > 0)
        _dwSoul += soul;
    else if (_dwSoul >= static_cast<UINT32>(soul))
        _dwSoul += soul;
}

void CUser::ChangePrestige(INT32 prestige)
{
    if (prestige > 0)
        _dwPrestige += prestige;
    else if (_dwPrestige >= static_cast<UINT32>(prestige))
        _dwPrestige += prestige;
}

void CUser::ChangeHonor(INT32 honor)
{
    if (honor > 0)
        _dwHonor += honor;
    else if (_dwHonor >= static_cast<UINT32>(honor))
        _dwHonor += honor;
}

bool CUser::SendPkg(const std::string& strPkg)
{
    if(strPkg.empty())
        return false;
    return NetMgr.GetGateHandler()->SendClt(&_qwUsrID, 1, &strPkg[0], (UINT32)strPkg.size());
}

void CUser::SendSysMsg(UINT16 wID)
{
    UINT32 dwServerID = GetGameSvrID();
    g_Game2CenterCommS.SendSvr_SendSysMsg(&dwServerID,1,GetUserID(),wID);
}


bool CUser::IsOnline() const
{
    bool bIsOnline = false;
    switch(GetState())
    {
        case eUserInGame:
        case eUserReplace:
            bIsOnline = true;
            break;
        case eUserNone:
        case eUserWantLogin:
        case eUserLeaveAway:
        default:
            bIsOnline = false;
            break;
    }
    return bIsOnline;
}

bool CUser::ReplaceUser()
{
    SetState(eUserReplace);
    UINT32 dwSvrID = NetMgr.GetGateHandler()->GetGateID(_qwUsrID);
    if(!g_Gate2CenterCommS.SendSvr_ReplaceUser(&dwSvrID, 1, _qwUsrID, [](UINT8 byRet_, //0为成功，1为失败，2为超时
                    UINT64 qwUsrID //(本地保存的函数参数)帐号ID
                    ){
                if(byRet_ != 0)
                {
                LOG_CRI << "byRet != 0";
                return;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
                if(pUser == NULL)
                {
                LOG_CRI << "Can't find User: " << qwUsrID;
                return;
                }
                pUser->OnReplaceGateUser();
                }))
    return false;

    if(!g_Game2CenterCommS.SendSvr_ReplaceUser(&_dwGameSvrID, 1, _qwUsrID, [](UINT8 byRet_, //0为成功，1为失败，2为超时
                    UINT64 qwUsrID //(本地保存的函数参数)帐号ID
                    ){
                if(byRet_ != 0)
                {
                LOG_CRI << "byRet != 0";
                return;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
                if(pUser == NULL)
                {
                LOG_CRI << "Can't find User: " << qwUsrID;
                return;
                }
                pUser->OnReplaceGameUser();
                }))
    return false;


    if(!g_Center2DBCommC.Send_ReplaceUser(_qwUsrID, [](UINT8 byRet_, //0为成功，1为失败，2为超时
                    UINT64 qwUsrID //(本地保存的函数参数)帐号ID
                    ){
                if(byRet_ != 0)
                {
                LOG_CRI << "byRet != 0";
                return;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
                if(pUser == NULL)
                {
                LOG_CRI << "Can't find User: " << qwUsrID;
                return;
                }
                pUser->OnReplaceDBUser();
                }))
    return false;

    _bGateUserReplaced = _bGameUserReplaced = _bDBUserReplaced = false;
    return true;
}

void CUser::OnReplaceGateUser()
{
    _bGateUserReplaced = true;
    UserReLoginNotify();
}

void CUser::OnReplaceGameUser()
{
    _bGameUserReplaced = true;
    UserReLoginNotify();
}

void CUser::OnReplaceDBUser()
{
    _bDBUserReplaced = true;
    UserReLoginNotify();
}

void CUser::UserReLoginNotify()
{
    if(!_bGateUserReplaced || !_bGameUserReplaced || !_bDBUserReplaced)
        return;
    LOG_DBG << "Replace User, UsrID: " << _qwUsrID;
    UINT32 dwSvrID = NetMgr.GetGateHandler()->GetGateID(_qwUsrID);
    SSvrInfo* pSvrInfo = CSvrInfoMgr::GetSvrInfo(dwSvrID);
    if(pSvrInfo == NULL)
    {
        LOG_CRI << "Can't find SvrInfo! SvrID: " << dwSvrID;
        return;
    }
    g_Login2CenterCommS.NotifyUserLogin(*this, *pSvrInfo);
}

void CUser::SetClientIP(const string& strIP)
{
    _strIP = strIP;
    _dwLoginTime = (UINT32)time(NULL);
}

void CUser::TimerCheck(time_t tNow)
{
    _oMailBox.TimerCheck();
    DoZeroEvent();
}

void CUser::SetQuality(UINT8 byQuality)
{
    _byQuality = byQuality;
    CGuildUserPtr pGuildUser;
    if (!_pGuildUser)
        pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(GetUserID());
    else
        pGuildUser = _pGuildUser;
    if (pGuildUser)
        pGuildUser->SetQuality(byQuality);

    _oFriend.ChangeColor(byQuality);

}

void CUser::SetIcon(const string &strIcon)
{
    _strIcon = strIcon;
}
bool CUser::HasIcon(UINT16 wIcon)
{
    return TITLE_DATA::TestNum(wIcon,_strIcon);
}

const TVecPlatformParam& CUser::GetPlatformParam() const 
{ 
    return _vecPlatformParam; 
}

void CUser::SetPlatformParam(const TVecPlatformParam& vecPlatformParam, UINT32 dwIndex)
{
    for (auto& rInfo : vecPlatformParam)
    {
        bool bFound = false;

        for (auto& rPlatformParam : _vecPlatformParam)
        {
            if (rPlatformParam.byPtType == rInfo.byPtType
                    && rPlatformParam.byQQPtType == rInfo.byQQPtType)
            {
                bFound = true;
                if(rPlatformParam.byQQPtLv != rInfo.byQQPtLv
                        || rPlatformParam.bySPType != rInfo.bySPType)
                    rPlatformParam = rInfo;
                break;
            }
        }
        if (!bFound)
            _vecPlatformParam.push_back(rInfo);
    }
    _dwPlatformIndex = dwIndex;
    CUserMgr::UpdatePlatformParam(GetRoleID(), vecPlatformParam);
}

const SPlatformParam& CUser::GetCurPlatform() const 
{
    if (_dwPlatformIndex >= _vecPlatformParam.size())
        return s_sPlatformParam;
    else
    {
        //LOG_DBG << "_dwPlatformIndex = " << _dwPlatformIndex << ", vecPlatformParam.size() = " << _vecPlatformParam.size() << ".";
        return _vecPlatformParam[_dwPlatformIndex];
    }
}

void CUser::GetLadderReport(boost::function<void(INT8,NRoleInfoDefine::TVecBattleRePort&)> funAck)
{
    if(_bHasLoadLadderReport)
    {
        funAck(0,_vecLadderReport);
        return ;
    }
    g_Center2DBCommC.Send_GetBattleReport(_qwUsrID,NRoleInfoDefine::eTypeLadder,NRoleInfoDefine::eTypeALL,[this,funAck](UINT8 byRet_, //0为成功，1为失败，2为超时
                const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值
        )
                {
                if(byRet_ != 0)
                {
                funAck(byRet_,_vecLadderReport); 
                return;
                }
                _bHasLoadLadderReport = true;
                _vecLadderReport = vecReport;
                funAck(byRet_,_vecLadderReport);

                });
            }

            void  CUser::AddLadderReport(const NRoleInfoDefine::SBattleRePort& sReport )
            {
            if(_bHasLoadLadderReport)
            {
            g_Center2DBCommC.Send_AddBattleReport( _qwUsrID,sReport,10,[this,sReport](UINT8 byRet_,const TVecUINT64& vecBattleID){
                if(!vecBattleID.empty())
                {
                for(auto pos = vecBattleID.begin();pos != vecBattleID.end();pos++)
                {
                for(auto it = _vecLadderReport.begin();it != _vecLadderReport.end();)
                {
                if(*pos == (*it).qwBattleID)
                {
                it = _vecLadderReport.erase(it);
                continue;
                }
                else
                {
                it++;
                }
                }
                }
                }
                _vecLadderReport.push_back(sReport);
                });
            }
            else
            {
                g_Center2DBCommC.Send_AddBattleReport(	_qwUsrID,sReport,10,NULL);
            }
            }

void CUser::OnEvent(const EventType eEvent, const TVecINT32& vecParam,const string& strParam ,bool bLog )
{
    UINT32 dwServerID = GetGameSvrID();
    g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID,1,_qwUsrID,eEvent,vecParam,strParam,bLog);

}

void CUser::AddOffLineEvent(const TVecUINT64& vecRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam )//蒋离线时间放入数
{
    NRoleInfoDefine::SEventOffLine sEvent; 
    sEvent.dwEventType = eEvent; 
    sEvent.dwTime = time(NULL);   
    ostringstream strInfo;
    for(size_t sz = 0; sz != vecParam.size();sz++)
    {
        if(sz != 0)
            strInfo  << ",";
        strInfo  << vecParam[sz];
    }
    sEvent.strParam1 = strInfo.str();


    sEvent.strParam2 = strParam;

    UINT32 dwSize = TAKE_ARRAY_LENGTH(UINT64);
    if(vecRoleID.size() <= dwSize)
    {
        g_Center2DBCommC.Send_AddOffLineEvent(vecRoleID,sEvent);
    }
    else
    {
        TVecUINT64 vecSend;
        for(size_t sz =0; sz != vecRoleID.size();sz++)
        {
            vecSend.push_back(vecRoleID[sz]);
            if(vecSend.size() == dwSize)
            {
                g_Center2DBCommC.Send_AddOffLineEvent(vecSend,sEvent);
                vecSend.clear();
            }
        }
        if(!vecSend.empty())
        {
            g_Center2DBCommC.Send_AddOffLineEvent(vecSend,sEvent);
            vecSend.clear();
        }
    }
}

void CUser::AddOffLineEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam )
{
    TVecUINT64 vecRoleID;   
    vecRoleID.push_back(qwRoleID);
    AddOffLineEvent(vecRoleID, eEvent, vecParam,strParam);
}

void CUser::OnRoleEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam,bool bLog)
{

    CUserPtr pUser =  CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser && pUser->IsOnLine())
    {
        pUser->OnEvent(eEvent,vecParam,strParam,bLog);
    }
    else
    {
        AddOffLineEvent(qwRoleID,eEvent,vecParam,strParam);
    }
}
UINT64 CUser::GetGuildID()
{
    if(_pGuildUser) return _pGuildUser->GetGuildID();
    return 0;
}

void CUser::DoZeroEvent()
{
    if(Time::sameDay(time(NULL),_dwLastSendZero))
    {
      return ;
    }
    _dwLastSendZero = time(NULL);
    if(HasIcon(73))
    {
        _rShipPkg.Send2ClientSelfData();
    }
}

UINT32 CUser::GetDayInviteFriendCnt()
{
    
    CCenterVar& rVar = GetCenterVar();
    return rVar.GetVar(NVarDefine::ePlayerInvites);

}

void   CUser::AddDayInviteFriendCnt(UINT32 dwCnt)
{
    CCenterVar& rVar = GetCenterVar();
    UINT32 dwTotal = rVar.GetVar(NVarDefine::ePlayerInvites) + dwCnt;
    rVar.SetVar(NVarDefine::ePlayerInvites,dwTotal);
}

void CUser::AddGameBuff(UINT16 wBuffID, UINT32 dwEndTime)
{
    if (!wBuffID || !dwEndTime)
        return;
    UINT32 dwNow = time(NULL);
    auto iter = _mapGameBuffUseInCenter.find(wBuffID);
    if (iter == _mapGameBuffUseInCenter.end())
    {
        if (dwNow < dwEndTime)
            _mapGameBuffUseInCenter.insert(make_pair(wBuffID, dwEndTime));
        return;
    }
    if (dwNow < dwEndTime)
        iter->second = dwEndTime;
    else
        _mapGameBuffUseInCenter.erase(iter);
}

bool CUser::CheckGameBuffValid(UINT16 wBuffID)
{
    auto iter = _mapGameBuffUseInCenter.find(wBuffID);
    if (iter == _mapGameBuffUseInCenter.end())
        return false;
    return iter->second > time(NULL);
}
