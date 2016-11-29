
#pragma once
#include "ArenaGSSvr.h"
using namespace NArenaGS;

class CArenaGSS : public CArenaGSSvr
{
    public:
        //接收：请求自己竞技场信息,同时开启竞技场
        virtual bool OnRecv_ArenaInfoReq(
                shared_func<SArenaInfoReqAck>& fnAck //返回回调函数
                );

        //接收：请求挑战
        virtual bool OnRecv_ArenaChallengeReq(
                UINT64 qwDefense, //被挑战者ID
                shared_func<SArenaChallengeReqAck>& fnAck //返回回调函数
                );

        //接收：请求翻页
        virtual bool OnRecv_ArenaPageUpReq(
                EArenaLevel eLevel, //段位
                UINT32 dwRank, //请求排名开始名次
                UINT8 byNum, //请求数量
                shared_func<SArenaPageUpReqAck>& fnAck //返回回调函数
                );

        //接收：请求清除冷却
        virtual bool OnRecv_ArenaClearCDReq(
                UINT8 byType, 
                shared_func<SArenaClearCDReqAck>& fnAck //返回回调函数
                );

        //接收：请求获取奖池奖励
        virtual bool OnRecv_ArenaGetRankingRewardReq(
                UINT32 dwLootId, //奖励包
                EArenaAwardType eType, //奖励包类型
                shared_func<SArenaGetRankingRewardReqAck>& fnAck //返回回调函数
                );

        //接收：膜拜请求
        virtual bool OnRecv_ArenaWorship(
                UINT64 qwRoleID, //膜拜对象
                shared_func<SArenaWorshipAck>& fnAck //返回回调函数
                );
        //接收：请求刷将
        virtual bool OnRecv_FlushNewEnemy(
                shared_func<SFlushNewEnemyAck>& fnAck //返回回调函数
                ) ;
        //接收：请求对手信息
        virtual bool OnRecv_GetAllEnemy(
                shared_func<SGetAllEnemyAck>& fnAck //返回回调函数
                ); 
        //接收：请求奖励信息
        virtual bool OnRecv_GetAllAward(
                shared_func<SGetAllAwardAck>& fnAck //返回回调函数
                );
        //接收：请求膜拜信息
        virtual bool OnRecv_GetAllWirship(
                shared_func<SGetAllWirshipAck>& fnAck //返回回调函数
                );
        //接收：请求计算:奖励信息 
        virtual bool OnRecv_GetAllAwardInfo(
                shared_func<SGetAllAwardInfoAck>& fnAck //返回回调函数
                );
        //接收：请求购买挑战次数
        virtual bool OnRecv_ArenaByChallengeTimes(
                shared_func<SArenaByChallengeTimesAck>& fnAck //返回回调函数
                ) ;
        //接收：请求对手信息
        virtual bool OnRecv_ReFluseLadderEnemy(
                UINT8 byType, //0,默认刷对手，1顺次刷对手
                shared_func<SReFluseLadderEnemyAck>& fnAck //返回回调函数
                ) ;

        //接收：清求领取今日天梯奖励
        virtual bool OnRecv_GetLadderAward(
                shared_func<SGetLadderAwardAck>& fnAck //返回回调函数
                ) ;
        //接收：清求领取今日历练奖励
        virtual bool OnRecv_GetArenaAward(
                shared_func<SGetArenaAwardAck>& fnAck //返回回调函数
                ) ;

        //接收：战报
        virtual bool OnRecv_GetLadderReport(
                shared_func<SGetLadderReportAck>& fnAck //返回回调函数
                ) ;

        //接收：请求天梯挑战
        virtual bool OnRecv_LadderBattle(
                UINT64 qwEnemyID, //对手ID
                UINT32 dwEnemyRank, //对手天梯排名
                shared_func<SLadderBattleAck>& fnAck //返回回调函数
                ) ;
        //接收：请求天梯排名
        virtual bool OnRecv_LadderPageUpReq(
                UINT32 dwRank, //请求排名开始名次
                UINT8 byNum, //请求数量
                shared_func<SLadderPageUpReqAck>& fnAck //返回回调函数
                ) ;
        //接收：请求购买天梯挑战次数
        virtual bool OnRecv_ArenaBuyLadderTimes(
                shared_func<SArenaBuyLadderTimesAck>& fnAck //返回回调函数
                ) ;




    public:
        void SendSysMsgIDNotify(EArenaResult eResult,UINT64 qwRoleId);
};
