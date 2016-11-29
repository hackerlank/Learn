#ifndef GUILD_BATTLE_PROT_S_H
#define GUILD_BATTLE_PROT_S_H
#pragma once

#include "GuildBattleProtSvr.h"

using namespace NGuildBattleProt;

class CGuildBattleProtS : public CGuildBattleProtSvr
{
    public:
        virtual ~CGuildBattleProtS();

        //接收：帮派战报名
        virtual bool OnRecv_SignUp(
                EGBSpot eSpotType, //据点类型
                shared_func<SSignUpAck>& fnAck //返回回调函数
                );
        //接收：进入帮派战
        virtual bool OnRecv_Enter(
                shared_func<SEnterAck>& fnAck //返回回调函数
                );
        //接收：帮派战退出
        virtual bool OnRecv_Quit(
                shared_func<SQuitAck>& fnAck //返回回调函数
                );
        //接收：帮派成员调整
        virtual bool OnRecv_AdjustMember(
                UINT64 qwRoleID, //成员角色ID
                EGBSpot eSpotType, //目标据点类型
                UINT8 byIndex, //新目标对应位置(从1开始)
                shared_func<SAdjustMemberAck>& fnAck //返回回调函数
                );
        //接收：帮派战场信息
        virtual bool OnRecv_GetFieldInfo(
                shared_func<SGetFieldInfoAck>& fnAck //返回回调函数
                );
        //接收：帮派据点信息
        virtual bool OnRecv_GetSpotInfo(
                EGBSpot eType, //据点类型
                shared_func<SGetSpotInfoAck>& fnAck //返回回调函数
                );
        //接收：获取帮派战状态
        virtual bool OnRecv_GetState(
                shared_func<SGetStateAck>& fnAck //返回回调函数
                );
        //接收：据点战报获取
        virtual bool OnRecv_GetSpotBattle(
                EGBSpot eType, //据点类型
                shared_func<SGetSpotBattleAck>& fnAck //返回回调函数
                );
        //接收：帮派战技能信息获取
        virtual bool OnRecv_GetSkillInfo(
                shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
                );
        //接收：帮派购买技能结果
        virtual bool OnRecv_BuySkill(
                EGBSkill eType, //购买的技能类型
                shared_func<SBuySkillAck>& fnAck //返回回调函数
                );
        //接收：获取帮派战小面板信息
        virtual bool OnRecv_GetPanelInfo(
                shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
                );
        //接收：召集帮众广播
        virtual bool OnRecv_CallMember(
                shared_func<SCallMemberAck>& fnAck //返回回调函数
                );
};

#endif // #ifndef GUILD_BATTLE_PROT_S_H

