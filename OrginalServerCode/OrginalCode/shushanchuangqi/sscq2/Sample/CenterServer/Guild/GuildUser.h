#ifndef GUILD_USER_H
#define GUILD_USER_H
#include "stdafx.h"

#include "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

/////////////////////////////////////////////////////////
// 帮派固定权限
#define G_NONE             0x0000  
#define G_INVITE_MEMBER    0x0001  // 邀请成员
#define G_FIRE_MEMBER      0x0002  // 开除帮众
#define G_IMPROVE_MEMBER   0x0004  // 提升职位
#define G_DEMOTE_MEMBER    0x0008  // 降级
#define G_EDIT_INFO        0x0010  // 编辑工会信息
#define G_DISBAND          0x0020  // 解散帮会
#define G_DONATE           0x0040  // 捐献
#define G_QQGOURP          0x0080  // 设置Q群
#define G_IMPROVE_TECH     0x0100  // 升级帮派技能
#define G_IMPEACH          0x0200  // 发起弹劾
#define G_ALL              0x03FF  // 所有权限
// 帮派固定权限
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// 帮派可选权限
#define G_A_NONE            0x00 
#define G_A_BATTLE          0x01 // 指挥帮战
#define G_A_BUILD           0x02 // 升级建筑
#define G_A_BLOOD           0x04 // 开启血池
#define G_A_DOOMSDAY        0x08 // 指挥末日之战
#define G_A_ATTACK_TEAM     0x10 // 创建遗迹攻击小队
#define G_A_ALL             0x1F // 所有权限
// 帮派可选权限
/////////////////////////////////////////////////////////
const UINT16 AUTHORITY_TABLE [] =
{
    G_NONE,
    /*成员*/    G_DONATE,
    /*精英*/    G_DONATE|G_IMPROVE_TECH|G_IMPEACH,
    /*长老*/    G_INVITE_MEMBER|G_FIRE_MEMBER|G_DONATE|G_IMPROVE_TECH|G_IMPEACH,
    /*副帮主*/  G_INVITE_MEMBER|G_FIRE_MEMBER|G_IMPROVE_MEMBER|G_DEMOTE_MEMBER|G_EDIT_INFO|G_DONATE|G_IMPROVE_TECH|G_IMPEACH,
    /*帮主*/    G_INVITE_MEMBER|G_FIRE_MEMBER|G_IMPROVE_MEMBER|G_DEMOTE_MEMBER|G_EDIT_INFO|G_DISBAND|G_DONATE|G_QQGOURP|G_IMPROVE_TECH|G_IMPEACH,
    G_NONE,
};

const UINT16 DEFALUT_A_AUTHORITY_TABLE [] =
{
    G_NONE,
    /*成员*/    G_A_NONE,
    /*精英*/    G_A_ATTACK_TEAM,
    /*长老*/    G_A_ATTACK_TEAM|G_A_DOOMSDAY,
    /*副帮主*/  G_A_ATTACK_TEAM|G_A_DOOMSDAY|G_A_BLOOD|G_A_BATTLE,
    /*帮主*/    G_A_ATTACK_TEAM|G_A_DOOMSDAY|G_A_BLOOD|G_A_BATTLE|G_A_BUILD,
    G_NONE,
};

const UINT32 MIN_GUILD_USER_LEVEL = 30;
class CGuildUser : public  enable_shared_from_this<CGuildUser>, public CPoolObj<CGuildUser>
{
    friend class CGuildUserMgr;
    public:
        virtual ~CGuildUser();
        DEF_NEW_DELETE(CGuildUser);

        bool        InitFromUser(CUserPtr pUser);

        void        InitTechInfo();
        void        InitTechInfo(const TVecGuildTechInfo& rInfo);

        UINT64      GetID() const;
        UINT64      GetRoleID() const;
        CUserPtr    GetUserPtr() { return _pUser.lock(); }

        const string& GetName() const;

        void        SetLevel(UINT16 wLevel);
        UINT16      GetLevel() const;

        void        SetOnlineUser(CUserPtr pUser);
        void        SetLastOnlineTime(UINT32 dwTime);

        bool        IsOnline() const;
        CUserPtr    GetOnlineUser() const;
        CUserPtr    GetOnlineUser();
        void        SetUser(CUserPtr pUser);
        UINT64      GetGuildID() const;
        CGuildPtr   GetGuild();
        void        SetGuild(CGuildPtr pGuild, bool bLoad = false);

        UINT32      GetJoinTime() const;
        UINT32      GetLastOnlineTime() const;

        EMemberRank GetRank() const;
        EMemberRank GetLastRank() const;
        string      GetRankName();
        void        SetRank(EMemberRank eRank);
        void        SetLastRank(EMemberRank eLastRank);

        void        ResetDefaultAuthority();
        void        SetAuthority(UINT32 dwAuthority);

        UINT32      GetBattlePoint() const;

        UINT32      GetContribution() const;
        void        SetContribution(UINT32 dwContribution);
        bool        SubContribution(UINT32 dwContribution);
        void        AddContribution(UINT32 dwContribution);
        UINT32      GetRemainDonate() const;

        void        SetVIPLevel(UINT8 byVIPLevel);
        UINT8       GetVIPLevel() const;

        void        SetPlayerFighterID(UINT16 wPlayerFighterID);
        UINT16      GetPlayerFighterID() const;

        void        SetQuality(UINT8 byQuality);
        UINT8       GetQuality() const;

        void        GetAllInfo(SGuildUserInfo& rInfo) const;
        void        GetTechInfo(TVecGuildTechInfo& rvecInfo) const;
        void        GetAllDBInfo(SDBGuildUserInfo& rInfo) const;
        
        bool        HasAuthority(UINT16 dwFlag) const;

        UINT32      GetApplyCount() const;
        CGuildApplyInfoPtr GetApplyInfo(UINT64 qwGuildID);

        EApplyResult CreateApplyInfo(UINT64 qwGuildID, function<void(CGuildApplyInfoPtr pApplyInfo, EApplyResult eResult)> func);

        void        EraseApplyInfo(UINT64 qwGuildID);
        void        ClearApplyInfo();
        bool        GetApplyGuildID(TVecUINT64& rvecGuildID) const;

        void        TryGetImpeach();

        CGuildTechOwnerPtr GetTechOwner();

        void        UpdateTechAttr() const;

        void        AddBattleScore(UINT32 dwScore);
        void        SetBattleScore(UINT32 dwScore, bool bInit = false);
        UINT32      GetBattleScore() const;

        UINT32      GetLastWorshipTime() const;
        void        SetLastWorshipTime(UINT32 dwLastWorshipTime);

    public: 
        static void Update2DB(CGuildUserPtr pUser, EDataChange eChangeType);

    private:
        CGuildUser(CUserPtr pUser);
        CGuildUser(const SDBGuildUserInfo& rUserInfo);
        CGuildUser();

    private:
        CGuildPtr   _pGuild;
        CUserWtr    _pUser;

        UINT64      _qwRoleID;
        string      _strName;

        UINT16      _wLevel;

        UINT32      _dwJoinTime;

        UINT32      _dwLastOnlineTime; // 最后在线时间
        EMemberRank _eRank;
        EMemberRank _eLastRank;
        UINT32      _dwAuthority;

        UINT32      _dwBattlePoint;
        UINT32      _dwBattleScore;     // 帮派战积分

        UINT32      _dwContribution;    //GuildContrib  帮派贡献 货币类型 28;

        UINT8       _byVIPLevel;        // VIP等级
        UINT16      _wPlayerFighterID;  // 主将ID
        UINT8       _byQuality;         // 主将品质

        TVecGuildApplyInfoPtr _vecApplyInfoPtr;    // 申请列表信息
        CGuildTechOwnerPtr    _pTechOwner;
        UINT32      _dwLastWorshipTime; // 最后一次供奉时间(用于阻止发包刷任务)
};

#endif // #ifndef GUILD_USER_H
