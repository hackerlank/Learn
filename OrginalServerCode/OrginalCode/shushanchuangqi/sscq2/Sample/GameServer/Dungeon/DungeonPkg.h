#ifndef  DUNGEONPKG_H__
#define  DUNGEONPKG_H__
#include "RoleInfoDefine.h"
#include "DungeonProtS.h"
#include "TeamGS.h" //for ETEAMResult
class CPlayer;
using namespace NRoleInfoDefine;
using namespace NTeamGS;
class CDungeonPkg
{
    public:
        CDungeonPkg(CPlayer& rPlayer);

        //查询一个单人副本的相关信息
        RoleDgnInfo* GetPlayerDgnInfoByType(UINT32 dwDgnType);

        //玩家进入副本
        void UpadePlayerDgnInfoForEnter(UINT32 dwDgnType);//记录次数，支付代价

        //玩家副本结束
        //主动退出，失败（包括未完成超时结束），过期（不调用，由GetPlayerDgnInfoByType检测），成功（不调用，由PlayerCompleteDgn调用）
        void UpadePlayerDgnInfoForOver(UINT32 dwDgnType);

        //玩家完成副本
        bool PlayerCompleteDgn(UINT32 dwDgnType,UINT16 wMinTurns,bool bIsClean = false);

        //删除一个单人副本的相关信息
        //
        void DelPlayerDgnInfo(UINT32 dwDgnType);

        EDungeonResult Sweeping(UINT16 wDgnID, UINT8 byOptions, UINT16 wCount, UINT32& dwSweepEndTime);
        EDungeonResult CancelSweeping();
        EDungeonResult SweepingSpeedUp(UINT8 byOptions);
        ETEAMResult CanCreateEnterTeam(UINT16 wDgnID);
        EDungeonResult CheckDgnTimes(UINT16 wDgnID);
        bool IsDgnPassed(UINT16 wDgnID);
        bool IsDgnListPassed(const TVecUINT16& vecDgnID);
        void Init(const TVecRoleDgnInfo& vecRoleDgnInfo);
        void ReturnCost();
        //更新组队副本领奖情况
        void UpdateTeamAward();
        //更新历险副本
        void SendLiXianDgn();
        //更新单个副本完成情况
        void SendDgnInfo(const RoleDgnInfo &rDgn);
        void GetDgnStarByInfo(const RoleDgnInfo &rDgn,DgnStar& sDgnStar);
        void GetLiXian(DgnLiXian &sLiXian);

        void GetDgnInfoForAll(DgnLiXian &sLiXian,TVecDgnStar &vecStar);
        void SendDgnInfoForAll();
        EDungeonResult BuyHeroDgnTimes(UINT16 wDgnID);
        EDungeonResult    DoStarAward(UINT16 wStarID);
        EDungeonResult    BuyLiXianDgnTimes();
        bool CompleteDgnIsCost(UINT16 wDgnID);
    private:
        CPlayer& _rPlayer;
        map<UINT32,RoleDgnInfo> _mapPlayerDgnInfo;  //玩家的单人副本信息列表

};

#endif // DUNGEONPKG_H__
