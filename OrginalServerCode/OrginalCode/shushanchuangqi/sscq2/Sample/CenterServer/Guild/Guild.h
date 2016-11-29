#ifndef GUILD_H
#define GUILD_H

#include "stdafx.h"
#include "GuildProt.h"
#include "GuildProtSvr.h"

using namespace NGuildProt;
using namespace NProtoCommon;

const UINT32 MAX_INFO_LENGTH = 200;
const UINT32 MAX_DONATE_EVERYDAY = 200000;
const UINT32 CREATE_GUILD_SILVER = 10000;
const UINT32 DEFAULT_RANK_COUNT_TABLE [] = 
{
    999,
    /*成员*/    999,
    /*精英*/    999,
    /*长老*/    4,
    /*副帮主*/  2,
    /*帮主*/    1,
    0,
};

class CGuild : public enable_shared_from_this<CGuild>, public CPoolObj<CGuild>
{
    public:
        CGuild(CGuildUserPtr pUser, const string& strName);
        CGuild(const SGuildBaseInfo& rGuildBaseInfo);
        virtual ~CGuild();
        DEF_NEW_DELETE(CGuild);

        UINT64          GetID()             const;
        const string    GetIDHexString()    const;
        const string&   GetName()           const;
        const string&   GetInfo()           const;
        UINT8           GetLevel()          const;

        UINT16          GetBuildingMaxLevel() const;

        UINT64 GetOwnerID()             const;
        const string&   GetOwnerName()  const;
        UINT16 GetMemberCount()         const;
        UINT16 GetMaxMemberCount()      const;
        UINT16 GetEmptyMemberCount()    const;
        UINT64 GetQQGroupID()           const;
        UINT32 GetMoney()               const;
        UINT32 GetCount()               const;
        UINT8 GetExchangedMark()        const;

        UINT32 GetBattleScore()         const;
        //void   SetScore(UINT32 dwTmp) { _dwScore = dwTmp; }
        UINT16 GetPlayerFighterID() const;
        UINT8  GetQuality() const;

        CGuildBuildingOwnerPtr GetBuildingOwner() const;
        CGuildBuildingOwnerPtr GetBuildingOwner();

        CGuildStatueOwnerPtr GetStatueOwner() const;
        CGuildStatueOwnerPtr GetStatueOwner();

        bool   SubMoney(UINT32 dwMoney);
        void   AddMoney(UINT32 dwMoney);
        void   SetMoney(UINT32 dwMoney);

        void   AddCount(UINT32 dwCount);
        void   SetCount(UINT32 dwCount);
        
        bool CheckLingshanType(UINT8 byLingShanType);
        TVecUINT8 GetLingShanType();
        const string& GetLingShan() const;
        void SetLingShan();

        void   SetExchangedMark(UINT8 byExchangedMark);

        void SetQuality(UINT8 byQuality);
        void SetPlayerFighterID(UINT16 wPlayerFighterID);

        bool InitUser   (CGuildUserPtr pUser);
        bool InitAuthority (const TVecGuildAuthorityInfo& rvecAuthority);
        bool InitBuildings ();
        bool InitBuildings (const TVecGuildBuildingInfo& rvecBuildings);
        bool InitStatue();
        bool InitStatue(const SGuildStatueInfo& rStatue);
        bool InitLog(const TVecGuildLogInfo& rInfo);

        bool EditInfo (const string& strInfo, EEditInfoResult& eResult);

        bool SetMemberAuthority(EMemberRank eRank, UINT32 dwAuthority, CGuildUserPtr pUser, ESetAuthorityResult& eResult);
        bool SetMemberRank(UINT64 qwRoleID, EMemberRank eNewRank, CGuildUserPtr pUser, EMemberOperateResult& eResult);
        bool KickMember(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult);
        bool UpMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult);
        bool DownMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult);
        bool FireMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult);
        bool GiveOwner(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult);

        void AddApplyInfo(CGuildApplyInfoPtr pApplyInfo);
        bool AgreeApply(UINT64 qwRoleID, CGuildUserPtr pGuildUser, EApplyResult& eResult);
        bool AgreeApplyAll(CGuildUserPtr pGuildUser, EApplyResult& eResult);
        bool RejectApply(UINT64 qwRoleID, CGuildUserPtr pGuildUser, EApplyResult& eResult);
        bool RejectApplyAll(CGuildUserPtr pGuildUser, EApplyResult& eResult);
        bool CancelApply(UINT64 qwRoleID, EApplyResult& eResult);

        bool InviteOther(CGuildUserPtr pGuildUser, const string& strName, EApplyResult& eResult);
        bool InviteReply(bool bAgree, CGuildUserPtr pGuildUser, EApplyResult& eResult);

        bool QuitGuild(CGuildUserPtr pGuildUser, EQuitResult& eResult);
        bool DisbandGuild(CGuildUserPtr pGuildUser, EQuitResult& eResult);
        bool KickGuild(CGuildUserPtr pGuildUserKicker, CGuildUserPtr pGuildUserBeKeker, EMemberOperateResult& eResult);

        bool LaunchImpeach(CGuildUserPtr pGuildUser, EImpeachResult& eResult, function<void(UINT8 byRet)> func);
        bool CancelImpeach();
        bool ImpeachReply(bool bAgree, CGuildUserPtr pGuildUser, EImpeachResult& eResult);

        bool Donate(CGuildUserPtr pGuildUser, UINT32 dwMoney, EDonateResult& eResult, function<void(UINT8 byRet)> func);

        void AddLog(CGuildLogPtr pLog);

        void GetAllUserID(TVecUINT64& rvecUserID) const;

        bool HaveAuthority(CGuildUserPtr pGuildUser, UINT16 wAuthorityBit) const;

        void StatueReward();
        void BattleReward();

        void GetGuildExchangedItemInfo(
                CGuildUserPtr pGuildUser,
                TVecUINT8& vecLingShanType,
                TVecGuildExchangedItem& vecGuildExchangedItem,
                UINT32& dwGUildAllMemberExchangedItemNum,
                UINT32& dwPlayerExchangedItemNum,
                EMemberRank& eMemberLastRank
                );

        void ReqGuildExchangeItem(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount, shared_func<CGuildProtSvr::SReqGuildExchangeItemAck>& fnAck);
        
        EGuildExchangeRet GuildExchangedItemAccount(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount);

        EGuildExchangeRet GuildExchangedItemCheck(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount);

        void SetGuildExchangedItem(UINT32 dwExchangeID, UINT32 dwCount);
        
        UINT32 GetGuildExchangedItemCount(UINT32 dwExchangeID);

        void GuildExchangedItemNotify(UINT32 dwExchangeID);

        void GuildExchangedItemDB(UINT32 dwExchangeID, EDataChange eChangeType);
        
        void GuildExchangedItemBegin(TVecUINT8 vecLingShanType);
        
        //void GuildExchangedItemEnd();

        void GuildExchangedItemZeroClean();

        void GuildExchangedItemClean();

        bool InitGuildExchangedItemLog(const TVecGuildLogInfo& rInfo);

        bool GetGuildExchangedItemLog(TVecGuildLogInfo& rInfo);

        bool AddGuildExchangedItemLog(SGuildLogInfo& sGuildLogInfo);

        void FormatGuildExchangedItemLog(UINT8 byType, UINT8 byQuality, string strName, UINT32 dwItemID, UINT32 dwItemCount, SGuildLogInfo& sGuildLogInfo);

        void GuildExchangedItemLogNotify(const SGuildLogInfo& sGuildLogInfo);

        void UpdateGuildExchangedItemLogDB(const SGuildLogInfo& sGuildLogInfo, EDataChange eChangeType);

    public:     // 各种通知
        void NotifyBaseInfo(UINT64 qwExceptRoleID = 0) const;
        void NotifyBaseInfoSelf(CGuildUserPtr pGuildUser) const;
        void NotifyApplyInfo() const;
        void NotifyAuthorityInfo() const;
        void NotifyUserInfo(UINT64 qwExceptRoleID = 0) const;
        void NotifyImpeachInfo() const;
        void NotifyImpeachSucceed() const;
        void NotifyImpeachFailed() const;
        void NotifyImpeachCancel() const;
        void NotifyBuildingInfo() const;
        void NotifyStatueInfo() const;
        void NotifyLogInfo() const;

        void NotifyIDInfo(UINT16 wMsgID, const TVecString& vecStr) const;

        bool GetImpeachNotify(CGuildUserPtr pGuildUser) const;

        void Broadcast(const string& strData, const TVecUINT64& vecExcpRoleID) const;

        void SyncGuildLevel() const;

    public:     // 各种获取向协议里序列化
        bool GetAllInfo(SGuildAllInfo& rAllInfo, CGuildUserPtr pUser) const;

        bool GetBaseInfo(SGuildBaseInfo& rBaseInfo, CGuildUserPtr pUser) const;
        bool GetMemberInfo(TVecGuildUserInfo& rInfo) const;
        bool GetMemberInfo(TVecSGuildInfoBase& rInfo) const;
        bool GetApplyInfo(TVecGuildApplyInfo& rInfo) const;
        bool GetAuthorityInfo(TVecGuildAuthorityInfo& rvecInfo) const;
        bool GetAuthorityInfo(TVecSGuildInfoBase& rvecInfo) const;
        bool GetBuildingInfo(TVecGuildBuildingInfo& rvecInfo) const;
        bool GetBuildingInfo(TVecSGuildInfoBase& rvecInfo) const;
        bool GetStatueInfo(SGuildStatueInfo& rInfo) const;
        bool GetLogInfo(TVecSGuildInfoBase& rvecInfo) const;
        bool GetLogInfo(TVecGuildLogInfo& rvecInfo) const;
        bool GetLogInfoWithoutType(ELogType eType, TVecSGuildInfoBase& rvecInfo) const;
        bool GetLogInfoWithoutType(ELogType eType, TVecGuildLogInfo& rvecInfo) const;
        bool GetLogInfoWithType(ELogType eType, TVecGuildLogInfo& rvecInfo) const;

        void SetDirty(EGuildDataType eType);
        bool IsDirty(EGuildDataType eType) const;
        void ClearDirty();

        void SaveData();
        static void Update2DB(CGuildPtr pGuild, EDataChange eChangeType, UINT64 qwGuild = 0);

        void UpdateRankInfo(UINT32 dwBattleScore) const;

    private:
        void    PreGuildUserEnter(CGuildUserPtr pGuildUser);
        void    OnGuildUserEnter(CGuildUserPtr pGuildUser);
        void    OnGuildUserQuit(CGuildUserPtr pGuildUser, CGuildUserPtr pKicker = NULL);
        void    OnGuildUserRankChanged(CGuildUserPtr pGuildUser, CGuildUserPtr pChanger, EMemberRank eOldRank, EMemberRank eNewRank);
        void    CheckImpeach();

        UINT16  GetMemberRankCount(EMemberRank eRank) const;

    private:
        UINT64          _qwID;
        string          _strName;
        string          _strInfo;
        //UINT32          _dwScore; //天元神兽积分
        UINT64          _qwOwnerID;
        string          _strOwnerName;

        UINT32          _dwExp;         // 帮派经验值（就是建设度）

        CGuildUserPtr   _pOwner;        // 帮主对象

        UINT64          _qwQQGroupID;   // 帮派QQ群群号

        UINT32          _dwMoney;       // 帮派资金

        UINT16          _wPlayerFighterID; // 帮主主将职业
        
        UINT8           _byQuality;        // 帮主主将品质
        
        UINT32          _dwCount;          // 兑换所有类型物品的数量总和
        
        string          _strLingShan;      // 占领灵山

        TVecGuildUserPtr        _vecMemberPtr;
        TVecGuildApplyInfoPtr   _vecApplyInfoPtr;

        CGuildBuildingOwnerPtr  _pBuildingOwner;
        CGuildStatueOwnerPtr    _pStatueOwner;
        map<EMemberRank, UINT32> _mapAuthority;
        map<EMemberRank, UINT32> _mapRankCount;

        UINT64          _qwImpeachLauncherRoleID;
        UINT8           _byImpeachLauncherQuality;
        string          _strImpeachLauncherName;
        TSetUINT64      _setImpeachAgreeer;
        TSetUINT64      _setImpeachRejecter;

        map<EGuildDataType, bool> _mapDirty;

        TVecGuildLogPtr _vecLogPtr;
    
        map<UINT32, UINT32> _mapGuildExchangedItem;
        TVecUINT8           _vecLingShanType;
        //TVecGuildLogInfo    _vecExchangedItemLog;
        typedef std::deque<SGuildLogInfoPtr> DequeGuildLogInfo;
        DequeGuildLogInfo _dequeExchangedItemLog;
};

// 用于其他帮派列表显示用的信息(启动即预加载)
class CGuildListInfo :public enable_shared_from_this<CGuildListInfo>
{
    public:
        CGuildListInfo();
        CGuildListInfo(CGuildPtr pGuild);
        CGuildListInfo(const SGuildListInfo& rGuildListInfo);
        virtual ~CGuildListInfo();

        UINT64 GetID() const;
        const string& GetName() const;

        UINT64 GetOwnerID() const;
        const string& GetOwnerName() const;
        UINT8 GetLevel() const;

        UINT16 GetMemberCount() const;
        UINT16 GetMaxMemberCount() const;

        const string& GetInfo() const;

        void SetOwnerID(UINT64 qwOwnerID);
        void SetOwnerName(const string& strName);

        void SetLevel(UINT8 byLevel);

        void SetInfo(const string& strInfo);

        void SetMemberCount(UINT16 wCount);
        void SetMaxMemberCount(UINT16 wCount);

        bool GetAllInfo(SGuildListInfo& rAllInfo) const;

        void SaveData();
        static void Update2DB(CGuildListInfoPtr pGuildListInfo, EDataChange eChangeType, UINT64 qwGuild = 0);

    private:
        UINT64              _qwID;

        string              _strName;
        string              _strInfo;

        UINT8               _byLevel;

        UINT64              _qwOwnerID;
        string              _strOwnerName;
        UINT16              _wMemberCount;
        UINT16              _wMaxMemberCount;
};

#endif // #ifndef GUILD_H

