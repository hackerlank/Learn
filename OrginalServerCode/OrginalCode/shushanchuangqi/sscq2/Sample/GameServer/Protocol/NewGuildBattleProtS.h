// =====================================================================================
//
//       Filename:  NewGuildBattleProtS.h
//
//    Description:  新帮派战协议处理函数
//
//        Version:  1.0
//        Created:  03/18/2015 04:23:03 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_PROT_S_H
#define NEW_GUILD_BATTLE_PROT_S_H

#pragma once

#include "NewGuildBattleProtSvr.h"

using namespace NNewGuildBattleProt;

// =====================================================================================
//        Class:  CNewGuildBattleProtS
//  Description:  新帮派战协议处理类
// =====================================================================================
class CNewGuildBattleProtS : public CNewGuildBattleProtSvr
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        virtual ~CNewGuildBattleProtS();

        // ====================  METHODS       ======================================= //

        //接收：获取帮派战状态
        virtual bool OnRecv_GetState(
                shared_func<SGetStateAck>& fnAck //返回回调函数
                );

        //接收：获取历届占领帮会
        virtual bool OnRecv_GetOwnerHistory(
                ENGBMountain eMountainType, //灵山类型
                shared_func<SGetOwnerHistoryAck>& fnAck //返回回调函数
                );

        //接收：进入帮派战(进入准备场地)
        virtual bool OnRecv_Enter(
                ENGBMountain eMountainType, //灵山类型
                shared_func<SEnterAck>& fnAck //返回回调函数
                );

        //接收：城门战攻击玩家/城门
        virtual bool OnRecv_GateAttackPlayer(
                UINT64 qwTargetRoleID, //目标唯一ID(0为城墙)
                shared_func<SGateAttackPlayerAck>& fnAck //返回回调函数
                );

        //接收：购买傀儡
        virtual bool OnRecv_BuyPuppet(
                shared_func<SBuyPuppetAck>& fnAck //返回回调函数
                );

        //接收：获取城门战信息
        virtual bool OnRecv_GetGateInfo(
                shared_func<SGetGateInfoAck>& fnAck //返回回调函数
                );

        //接收：洞府战占领阵眼
        virtual bool OnRecv_CaveCapture(
                ENGBCaveCore eCaveType, //阵眼类型
                shared_func<SCaveCaptureAck>& fnAck //返回回调函数
                );

        //接收：洞府战攻击他人
        virtual bool OnRecv_CaveAttack(
                UINT64 qwTargetRoleID, //目标唯一ID
                shared_func<SCaveAttackAck>& fnAck //返回回调函数
                );

        //接收：洞府战从阵眼下阵
        virtual bool OnRecv_CaveRest(
                shared_func<SCaveRestAck>& fnAck //返回回调函数
                );

        //接收：获取洞府战信息
        virtual bool OnRecv_GetCaveInfo(
                shared_func<SGetCaveInfoAck>& fnAck //返回回调函数
                );

        //接收：立即买活
        virtual bool OnRecv_ClearDeadCD(
                shared_func<SClearDeadCDAck>& fnAck //返回回调函数
                );

        //接收：帮派战退出
        virtual bool OnRecv_Quit(
                shared_func<SQuitAck>& fnAck //返回回调函数
                );

        //接收：获取战功榜帮派排名信息
        virtual bool OnRecv_GetGuildRankInfo(
                UINT32 dwIndex, //排名索引
                UINT32 dwCount, //排名个数
                shared_func<SGetGuildRankInfoAck>& fnAck //返回回调函数
                );

        //接收：获取战功榜帮派成员排名信息
        virtual bool OnRecv_GetGuildMemberRankInfo(
                UINT32 dwIndex, //排名索引
                UINT32 dwCount, //排名个数
                shared_func<SGetGuildMemberRankInfoAck>& fnAck //返回回调函数
                );

        //接收：获取战功榜个人排名信息
        virtual bool OnRecv_GetPlayerRankInfo(
                UINT32 dwIndex, //排名索引
                UINT32 dwCount, //排名个数
                shared_func<SGetPlayerRankInfoAck>& fnAck //返回回调函数
                );

        //接收：召集帮众广播
        virtual bool OnRecv_CallMember(
                shared_func<SCallMemberAck>& fnAck //返回回调函数
                );
    private:
        // ====================  METHODS       ======================================= //

        void SystemMsg(ENGBResult& eResult);
        void SystemMsg(ENGBEnterResult& eResult);
        void SystemMsg(ENGBGateAttackResult& eResult);
        void SystemMsg(ENGBBuyPuppetResult& eResult);
        void SystemMsg(ENGBClearDeadCDResult& eResult);
        void SystemMsg(ENGBCaveAttackResult& eResult);
        void SystemMsg(ENGBQuitResult& eResult);
        void SystemMsg(ENGBBattleResult& eResult);

}; // -----  end of class CNewGuildBattleProtS  ----- //

extern CNewGuildBattleProtS g_NewGuildBattleProtS;

#endif // #ifndef NEW_GUILD_BATTLE_PROT_S_H
