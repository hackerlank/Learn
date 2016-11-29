
#pragma once

#include "stdafx.h"

#include "Friend.h"
#include "MailBox.h"
#include "CenterVar.h"
#include "FireSlots.h"
#include "EventCenter.h"
#include "ShipPkg.h"
namespace NProtoCommon { enum ESexType; }
using namespace NEventCenter;
#include "RoleEnterGameProt.h"
namespace NProtoCommon { enum ESexType; }
using namespace NRoleEnterGameProt;
enum EUserState
{
    eUserNone,
    eUserWantLogin,
    eUserInGame,
    eUserReplace,
    eUserLeaveAway
};

/*#define SET_BIT(X,Y)     (X | (static_cast<UINT64>(1)<<Y))
#define GET_BIT(X,Y)     ((X & (static_cast<UINT64>(1)<<Y)) >> Y)
#define CLR_BIT(X,Y)     (X & ~(static_cast<UINT64>(1)<<Y))

#define CLR_BIT_8(X,Y)   (X & ~(0xFF<<(Y*8)))
#define SET_BIT_8(X,Y,V) (CLR_BIT_8(X,Y) | V<<(Y*8))
#define GET_BIT_8(X,Y)   ((X >> (Y*8)) & 0xFF)

#define CLR_BIT_32(X,Y)   (X & ~(static_cast<UINT64>(0xFFFFFFFF)<<(Y*32)))
#define SET_BIT_32(X,Y,V) (CLR_BIT_32(X,Y) | static_cast<UINT64>(V)<<(Y*32))
#define GET_BIT_32(X,Y)   ((static_cast<UINT64>(X) >> (Y*32)) & 0xFFFFFFFF)*/

#define SET_BIT(X,Y)     (static_cast<UINT64>(X) | (static_cast<UINT64>(1)<<static_cast<UINT64>(Y)))
#define GET_BIT(X,Y)     ((static_cast<UINT64>(X) & (static_cast<UINT64>(1)<<static_cast<UINT64>(Y))) >> static_cast<UINT64>(Y))
#define CLR_BIT(X,Y)     (static_cast<UINT64>(X) & ~(static_cast<UINT64>(1)<<static_cast<UINT64>(Y)))

#define CLR_BIT_8(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(8))))
#define SET_BIT_8(X,Y,V) (CLR_BIT_8(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(8)))
#define GET_BIT_8(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(8))) & static_cast<UINT64>(0xFF))

#define CLR_BIT_16(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFFFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(16))))
#define SET_BIT_16(X,Y,V) (CLR_BIT_16(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(16)))
#define GET_BIT_16(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(16))) & static_cast<UINT64>(0xFFFF))

#define CLR_BIT_32(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFFFFFFFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(32))))
#define SET_BIT_32(X,Y,V) (CLR_BIT_32(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(32)))
#define GET_BIT_32(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(32))) & static_cast<UINT64>(0xFFFFFFFF))

using namespace NProtoCommon;

static SPlatformParam s_sPlatformParam;
enum eLockType
{
    eLock_Arena     = 1,
    eLock_Tripod    = 2,
    eLock_Ship      = 3,
    eLock_GuildExchangedItem = 4,
};

struct COpLock
{
   COpLock(CUser &rUser):_rUser(rUser){}
   bool AddLock(eLockType eLock, UINT8 byTime = 3);
   void UnLock(eLockType eLock);
   private:
   CUser &_rUser;
   map<eLockType,UINT32> _mapLock;

};

class CUser : public enable_shared_from_this<CUser>
{
    friend class CUserMgr;
 public:
    DEF_NEW_DELETE(CUser);
    CUser(UINT64 qwUsrID);

    virtual ~CUser();

    UINT64 GetUserID() const { return _qwUsrID; }
    UINT64 GetRoleID() const { return _qwUsrID; }
    UINT64 GetOwnerID() const { return _qwUsrID; }

    const char* GetCUserName() const { return _strName.c_str(); }
    const std::string& GetUserName() const { return _strName; }
    const std::string& GetRoleName() const { return _strName; }
    void SetUserName(const std::string& name) { _strName = name; }
    const std::string GetFixdUserName() const;
    const char* GetFixdCUserName() const { return GetFixdUserName().c_str(); }

    UINT32 GetSessionID() const { return _dwSessionID; }
    void SetSessionID(UINT32 dwSessionID) { _dwSessionID = dwSessionID; }

    UINT8 GetAddrType() const { return _byAddrType; }
    void SetAddrType(UINT8 byAddrType) { _byAddrType = byAddrType; }

    UINT32 GetGameSvrID() const { return _dwGameSvrID; }
    void SetGameSvrID(UINT32 dwSvrID) { _dwGameSvrID = dwSvrID; }

    UINT8 GetNation() const { return _byNation; }
    void SetNation(UINT8 byNation);

    UINT8 GetGMLvl() const { return _byGMLvl; }
    void SetGMLvl(UINT8 byLvl) { _byGMLvl = byLvl; }

    UINT16 GetFighterID() const { return _wFighterID; }
    void SetFighterID(UINT16 wFighterID) { _wFighterID = wFighterID; }

    UINT32 GetTotalRecharge() const { return _dwTotalRecharge; }
    void SetTotalRecharge(UINT32 dwTotalRecharge) { _dwTotalRecharge = dwTotalRecharge; }
    void AddTotalRecharge(UINT32 dwRecharge) { _dwTotalRecharge += dwRecharge; }

    UINT32 GetLoginTime() const { return _dwLoginTime; }
    void SetLoginTime(UINT32 dwLoginTime) { _dwLoginTime = dwLoginTime; }

    UINT32 GetOfflineTime() const { return _dwOfflineTime; }
    void SetOfflineTime(UINT32 dwOfflineTime) { _dwOfflineTime = dwOfflineTime; }

    UINT32 GetCurLoginTime() const { return _dwCurLoginTime; }
    void SetCurLoginTime(UINT32 dwCurLoginTime) { _dwCurLoginTime = dwCurLoginTime; }

    UINT32 GetLockExpireTime() const { return _dwLockExpireTime; }
    void SetLockExpireTime(UINT32 dwLockExpireTime) { _dwLockExpireTime = dwLockExpireTime; }

    UINT32 GetForbExpireTime() const { return _dwForbExpireTime; }
    void SetForbExpireTime(UINT32 dwForbExpireTime) { _dwForbExpireTime = dwForbExpireTime; }
    void SetVIPLevel(UINT8 byLevel);
    UINT8 GetVIPLevel() const { return _byVIPLevel; }

    UINT32 GetCreateTime() const { return _dwCreateTime; }
    void SetCreateTime(UINT32 dwCreateTime) { _dwCreateTime = dwCreateTime; }

    const TVecPlatformParam& GetPlatformParam() const;
    void SetPlatformParam(const TVecPlatformParam& vecPlatformParam, UINT32 dwIndex);
    const SPlatformParam& GetCurPlatform() const ;

    void SetEnterString(const TVecString& vecEnterString) { _vecEnterString = vecEnterString; _vecEnterString.resize(4);}

    const string& GetCustomPar1() const { return _vecEnterString[0]; }
    const string& GetCustomPar2() const { return _vecEnterString[1]; }
    const string& GetOpenID() const { return _vecEnterString[2]; }

    UINT32 GetGold() const { return _dwGold; }
    void SetGold(UINT32 gold) { _dwGold = gold; }
    void ChangeGold(INT32 gold);
    UINT32 GetSilver() const { return _dwSilver; }
    void SetSilver(UINT32 silver) { _dwSilver = silver; }
    void ChangeSilver(INT32 silver);
    UINT32 GetCoupon() const { return _dwCoupon; }
    void SetCoupon(UINT32 coupon) { _dwCoupon = coupon; }
    void ChangeCoupon(INT32 coupon);
    void SetSoul(UINT32 soul) { _dwSoul = soul; }
    void ChangeSoul(INT32 soul);
    void SetPrestige(UINT32 prestige) { _dwPrestige = prestige; }
    void ChangePrestige(INT32 prestige);
    void SetHonor(UINT32 honor) { _dwHonor = honor; }
    void ChangeHonor(INT32 honor);

    const TVecUINT16& GetOwnTitle() const { return _vecOwnTitle; }
    void SetOwnTitle(const TVecUINT16& vecTitle) { _vecOwnTitle = vecTitle; }
    const TVecUINT16& GetEquipTitle() const { return _vecEquipTitle; }
    void SetEquipTitle(const TVecUINT16& vecTitle) { _vecEquipTitle = vecTitle; }

    UINT32 GetBattlePoint() const { return 0; } // TODO:
    void SetIcon(const string &strIcon);
#ifdef QQ_VERSION
    UINT8 GetDomain() const { return _byDomain; }
    void SetDomain(UINT8 byDomain) { _byDomain = byDomain; }
    UINT8 GetDomainLvl() const { return _byDomainLvl; }
    void SetDomainLvl(UINT8 byDomainLvl) { _byDomainLvl = byDomainLvl; }
    UINT8 GetDisplayLvl() const { return _byDisplayLvl; }
    void SetDisplayLvl(UINT8 byDisplayLvl) { _byDisplayLvl = byDisplayLvl; }
    UINT8 GetDomainYear() const { return _byDomainYear; }
    void SetDomainYear(UINT8 byDomainYear) { _byDomainYear = byDomainYear; }
    void SetOpenId(char* szOpenId);
    const char* GetOpenId() const { return _szOpenId; }
    void SetOpenKey(char* szOpenKey);
    const char* GetOpenKey() const { return _szOpenKey; }
#endif
    void SetVia(const char* szVia) { szVia?_strVia = szVia:NULL; }
    void SetVia(std::string& strVia) { _strVia = strVia; }
    const std::string& GetVia() const { return _strVia; }
    void SetInvited(UINT64 qwInvitedID){ _qwInvitedID = qwInvitedID;}
    UINT64 GetInvitedID() { return _qwInvitedID; }
    void SetWallow(UINT8 byWallow){ _byWallow = byWallow; } 
    void SetSign(const std::string& strSign) { _strSign = strSign; }
    const std::string& GetSign() const { return _strSign; }
    void SetMood(UINT16 wMood) { _wMood = wMood; }
    UINT16 GetMood() const { return _wMood; }
    static UINT8 calcVIPLevel(UINT32 total);

    ESexType GetSex() const { return _eSex; }
    void SetSex(ESexType eSex) { _eSex = eSex; }
    ECareerType GetCareer() const {return _eCareer;}
    void SetCareer(ECareerType eCareer){_eCareer = eCareer;}
    UINT8 GetLevel() const { return _byLevel; }
    void SetLevel(UINT8 byLevel) { _byLevel = byLevel; }


    time_t GetLastWorldTime() const { return _tLastWorldTime; }
    void SetLastWorldTime(time_t tNow) { _tLastWorldTime = tNow; }

    time_t GetLastCountryTime() const { return _tLastCountryTime; }
    void SetLastCountryTime(time_t tNow) { _tLastCountryTime = tNow; }

    UINT32 GetLastOnlineTime() const { return _dwLastOnlineTime; }
    void    SetLastOnlineTime(UINT32 dwTime) { _dwLastOnlineTime = dwTime; }

    bool IsOnline() const;
    EUserState GetState() const { return _eUserState; }
    void SetState(EUserState eState);
    bool CheckStateTime(UINT32 dwInterval);

    void RequestDB();

    const std::string& GetClientIP() const { return _strIP; }
    void SetClientIP(const string& strIP);

    bool SendPkg(const std::string& strPkg);

    void SendSysMsg(UINT16 wID);

    time_t GetCheckTime() const { return _tLastCheckTime; }
    time_t GetLastWhisperTime() const { return _tLastWhisperTime; }
    void SetLastWhisperTime(time_t t) { _tLastWhisperTime = t; }

    bool ReplaceUser();

    bool IsOnLine();
    void OnReplaceGateUser();
    void OnReplaceGameUser();
    void OnReplaceDBUser();

    void OnRecvFail();

    bool IsAllSysOpen() const { return _bAllSysOpen; }
    void SetAllSysOpen(bool bAllSysOpen) { _bAllSysOpen = bAllSysOpen; }
    //UINT32 GetGateId(){ return m_dwGateId; }
    //void SetGateId(UINT32 dwGateId){ m_dwGateId = dwGateId; }
    bool IsInCrossServer();

    CFriend& GetFriend() { return _oFriend; }
    CMailBox& GetMailBox() { return _oMailBox; }
    CCenterVar& GetCenterVar(){return _sVar;} 

    CGuildUserPtr GetGuildUser() { return _pGuildUser; }
    void SetGuildUser(CGuildUserPtr pGuildUser) { _pGuildUser = pGuildUser; }
    UINT64 GetGuildID();
     NRoleInfoDefine::TVecRoleArenaInfo & GetArenaInfo(){return  _vecArenaInfo;} //玩家斗剑信息
    void SetArenaInfo(const NRoleInfoDefine::TVecRoleArenaInfo& rInfo){_vecArenaInfo = rInfo;}
    UINT16 GetQueryRoom(){return _wQueryRoom;}
    void SetQueryRoom(UINT16 wQueryRoom){ _wQueryRoom = wQueryRoom;}
    void TimerCheck(time_t tNow);
    UINT32 GetFighterPower(){ return _dwFighterPower ;}
    void  SetFighterPower(UINT32 dwFighterPower) { _dwFighterPower = dwFighterPower;}
    UINT16 GetPlayerFighterID() const { return _wPlayerFighterID;}
    void SetPlayerFighterID(UINT16 wPlayerFighterID) { _wPlayerFighterID = wPlayerFighterID; }
    UINT8 GetQuality() const { return _byQuality;}
    void SetQuality(UINT8 byQuality);
    UINT8 GetColor() const { return _byQuality;}
    bool HasIcon(UINT16 wIcon);
    void GetLadderReport(boost::function<void(INT8,NRoleInfoDefine::TVecBattleRePort&)> funAck);
    void AddLadderReport(const NRoleInfoDefine::SBattleRePort&sReport );

    CFireSlots& GetFireSlots() { return _oTripodFire; }
    bool ActiveFire(UINT16 wFireID) { return _oTripodFire.ActiveFire(wFireID); }
    void OnEvent(const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "",bool bLog = true);
    static void AddOffLineEvent(const TVecUINT64& vecRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "");//蒋离线时间放入数据库
    static void AddOffLineEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "");
    static void OnRoleEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "",bool bLog = true);
    COpLock& GetOpLock(){ return _opLock;}
    CShipPkg& GetShipPkg() { return _rShipPkg;}
    void DoZeroEvent();

    UINT32 GetDayInviteFriendCnt();
    void   AddDayInviteFriendCnt(UINT32 dwCnt);

    //是否cd
    bool IsAddItemCd()
    {
        return time(NULL) < _dwLastAddItemCD;
    }

    void SetAddItemCd()
    {
        _dwLastAddItemCD = time(NULL) + 30;
    }
    void ClearAddItemCD()
    {
        _dwLastAddItemCD = 0;
    }

    void AddGameBuff(UINT16 wBuffID, UINT32 dwEndTime);
    bool CheckGameBuffValid(UINT16 wBuffID);
public:
    static bool bUdpTest;
protected:
    void UserReLoginNotify();

protected:
    UINT64 _qwUsrID;
    std::string _strName;

    UINT32 _dwSessionID;
    UINT8 _byAddrType;
    UINT32 _dwGameSvrID;
    UINT32 _dwRecvFailCount;
    EUserState _eUserState;
    bool _bAlreadyReqDB;
    ECareerType _eCareer;
    ESexType _eSex;
    UINT8 _byLevel;
    UINT8 _byNation;
    UINT8 _byGMLvl; // GM权限,参见GMSystem.h
    UINT16 _wFighterID; // 主将ID
    UINT32 _dwTotalRecharge; // 总充值累积数
    UINT32 _dwLoginTime; // 上次登陆时间
    UINT32 _dwOfflineTime; // 上次下线时间
    UINT32 _dwCurLoginTime; // 本次登陆时间
    UINT32 _dwLockExpireTime; // 被封禁结束时间
    UINT32 _dwForbExpireTime; // 被禁言结束时间
    UINT32 _dwCreateTime; // 创角时间
    UINT8 _byVIPLevel;  //vip等级
    // 货币
    UINT32 _dwGold; // 仙石
    UINT32 _dwSilver; // 银币
    UINT32 _dwCoupon; // 礼券
    UINT32 _dwSoul; // 礼券
    UINT32 _dwPrestige; // 声望
    UINT32 _dwHonor; // 荣誉

    TVecUINT16 _vecOwnTitle;//拥有的称号
    TVecUINT16 _vecEquipTitle;//装备的称号

#ifdef QQ_VERSION
    UINT8 _byDomain; // 渠道
    UINT8 _byDomainLvl; // 渠道等级 - 奖励
    UINT8 _byDisplayLvl; // 显示等级 - 显示
    UINT8 _byDomainYear; // 年费

    char _szOpenId[256+1];
    char _szOpenKey[256+1];
#endif
    std::string _strVia;
    // std::string _strInvited;
    UINT64 _qwInvitedID;
    UINT8 _byWallow; // 防沉迷
    std::string _strSign; // 签名
    UINT16 _wMood; // 心情表情

    time_t _tLastCheckTime;
    time_t _tLastWhisperTime;
    time_t _tLastWorldTime;
    time_t _tLastCountryTime;

    UINT32 _dwLastOnlineTime;

    UINT32 _dwLastAddItemCD;


    //替换帐号相关标记
    bool _bGateUserReplaced;
    bool _bGameUserReplaced;
    bool _bDBUserReplaced;

    bool _bAllSysOpen;

    std::string _strIP;
    //add yhs
    //UINT32 m_dwGateId;
    NRoleInfoDefine::TVecRoleArenaInfo _vecArenaInfo; //玩家斗剑信息
    CFriend _oFriend; 
    CMailBox _oMailBox;
    CCenterVar  _sVar;
    UINT16 _wQueryRoom;
    CGuildUserPtr _pGuildUser;
    UINT32 _dwFighterPower;
    UINT16 _wPlayerFighterID;
    UINT8 _byQuality;
    string _strIcon;
    bool _bHasLoadLadderReport;
    CFireSlots _oTripodFire;
    NRoleInfoDefine::TVecBattleRePort _vecLadderReport; //(返回值)返回的数据
    TVecPlatformParam _vecPlatformParam;
    UINT32 _dwPlatformIndex;

    TVecString _vecEnterString;
    CShipPkg _rShipPkg;
    private:
    COpLock _opLock;
    UINT32 _dwLastSendZero;
    map<UINT16, UINT32> _mapGameBuffUseInCenter;    //ID:Time
};

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

