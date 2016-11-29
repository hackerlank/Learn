// =====================================================================================
//
//       Filename:  RankMgr.h
//
//    Description:  排行榜管理
//
//        Version:  1.0
//        Created:  09/04/2014 09:39:35 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "stdafx.h"

#include "Singleton.h"

#include "RankProt.h"
#include "WonderActivity.h"

using namespace NRankProt;

#ifdef _DEBUG
const UINT32 MAX_RANK_COUNT = 30;
#else
const UINT32 MAX_RANK_COUNT = 3000;
#endif

class CRankInfoGreater
{
    public:
        bool operator () (const SRankInfoPtr& pInfoA, const SRankInfoPtr& pInfoB);
};

typedef set<SRankInfoPtr, CRankInfoGreater> SetRankInfo;
typedef SetRankInfo::iterator ItSetRankInfo;
typedef vector<ItSetRankInfo> VecItSetRank;
//typedef set<ItSetRankInfo, CSetItLess> SetItSetRankInfo;
typedef map<UINT64, VecItSetRank> MapRankIndex;
typedef map<UINT64, TSetUINT64> MapAdoreIndex;
// =====================================================================================
//        Class:  CRankMgr
//  Description:  排行榜管理
// =====================================================================================
class CRankMgr : public Singleton<CRankMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CRankMgr(){}
        virtual ~CRankMgr() ;

        // ====================  ACCESSORS     ======================================= //
        void GetRankInfo (UINT64 qwRoleID, ERankType eType, UINT32 dwIndex, UINT32 dwCount,
                UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, 
                TVecRankInfo& rvecRankInfo, TVecRankInfo& rvecSelfRankInfo) const;
        void GetHeadInfo (TVecRankInfo& rvecRankInfo) const;
        UINT32 GetAdoreCount(UINT64 qwRoleID);
        bool CheckAdorePlayer(UINT64 qwOpID, UINT64 qwRoleID) const;

        void GetArenaInfo (UINT64 qwRoleID, UINT32 dwIndex, UINT32 dwCount,
                UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, 
                TVecRankInfo& rvecRankInfo, TVecRankInfo& rvecSelfRankInfo) const;

        void GetRankRoleID(ERankType eType, UINT32 dwIndex, UINT32 dwCount, TVecUINT64& rvecRoleID) const;

        // ====================  MUTATORS      ======================================= //
        void UpdateRankInfo (UINT64 qwInstID, ERankType eType, const TVecRankInfo& vecRankInfo);
        void DeleteRankInfo (UINT64 qwInstID, ERankType eType, const TVecRankInfo& vecRankInfo);
        bool AdorePlayer(UINT64 qwOpID, UINT64 qwRoleID, ERankResult& eResult, UINT32& dwCount);
        void InitRankFromDB(const TVecRankInfo& vecRankInfo);
        void InitAdoreFromDB(const TVecDBAdoreInfo& vecAdoreInfo);
        void UpdateRankGuildName(UINT64 qwRoleID, const string& strGuildName);
        void UpdatePlatform();

        void ClearSurplusRank();

        // ====================  OPERATORS     ======================================= //
        bool Init();
        void LoadFromDB();
        void TimeCheck(time_t tNow);

       //====================== ACTIVITY ==============================================//
        bool       SendMail(ERankType eType,UINT32&,UINT16&,const TVecItemConfigPtr&,UINT16&,UINT16&);
        bool       SendMailForGuild(UINT32&,UINT16&,const TVecItemConfigPtr&,UINT16&,UINT16&);
        bool       SendMailForArena(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID);
        bool       GetPlayerInfo(UINT16,bool,UINT64&,UINT16&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        UINT32     GetPoint(UINT64 qwRoleID);
        UINT32     GetCount(UINT32 dwPoint);

        bool       SaveRoleInfoForAct(UINT16 wActID);

        bool GetGuildRankByLevel(UINT32 dwIndex,UINT32 dwCount,TVecUINT64& vecGuildID);
        //全服等级榜活动
        bool       GetPlayerInfoForLevel(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForLevel(UINT16 wActID);
       
        //全服散仙榜活动
        bool       GetPlayerInfoForFighter(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForFighter(UINT16 wActID);

        //全服阵灵榜活动
        bool       GetPlayerInfoForPet(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForPet(UINT16 wActID);
        
        //全服帮派榜活动
        bool       GetPlayerInfoForGuild(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForGuild(UINT16 wActID);
        
        //全服斗剑榜活动
        bool       GetPlayerInfoForArena(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForArena(UINT16 wActID);

        //全服法宝榜活动
        bool       GetPlayerInfoForTrump(UINT16,bool,UINT64&,SWActPlayerInfo&,NWonderActivityProt::EWActState eType);
        bool       SaveRoleInfoForTrump(UINT16 wActID);

        UINT16 GetFirstLevel();

    private:
        // ====================  METHODS       ======================================= //
        bool IsSameRankInfo(SRankInfoPtr pBaseInfoA, SRankInfoPtr pBaseInfoB) const;

        void GetArenaHeadInfo(TVecRankInfo& rvecRankInfo) const;
        void GetGuildBattleHeadInfo(TVecRankInfo& rvecRankInfo) const;

        // ====================  DATA MEMBERS  ======================================= //
        map<ERankType, SetRankInfo>      _mapRankInfo;      // <排行榜类型，玩家排名Set>
        map<ERankType, MapRankIndex>     _mapRankIndex;     // <排行榜类型，玩家ID->排名SetIT索引>
        map<UINT64, UINT32>              _mapAdore;         // <玩家ID, 崇拜人数>
        UINT32                           _dwNextAdoreTime;  // 崇拜榜结算时间
        UINT32                           _dwNextVoterTime;  // 崇拜榜投票者投票时间
        MapAdoreIndex                    _mapAdoreIndex;
        bool                             _bPlatFromInited;  // 是否同步平台信息
        
        TSetUINT64                       _setRoleID; //帮派发邮件临时数据
}; // -----  end of class CRankMgr  ----- //

