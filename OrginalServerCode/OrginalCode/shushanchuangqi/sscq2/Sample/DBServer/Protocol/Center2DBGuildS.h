// =====================================================================================
//
//       Filename:  Center2DBGuildS.h
//
//    Description:  Center与DB通讯的帮派相关协议
//
//        Version:  1.0
//        Created:  03/21/2015 11:50:22 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef CENTER_2_DB_GUILD_S_H
#define CENTER_2_DB_GUILD_S_H

#pragma once
#include "Center2DBGuildSvr.h"

using namespace NCenter2DBGuild;

class CCenter2DBGuildS : public CCenter2DBGuildSvr
{
    public:
        //接收：帮派数据更新
        virtual void OnRecv_GuildDataUpdate(
                UINT64 qwGuildID, //帮派ID
                NGuildProt::EGuildDataType eDataType, //更新数据类型
                NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
                const std::string& strData //更新数据
                );

        //接收：帮派公共信息更新
        virtual void OnRecv_GuildPubDataUpdate(
                UINT64 qwGuildID, //帮派ID
                NGuildProt::EGuildPubDataType eDataType, //更新数据类型
                NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
                const std::string& strData //更新数据
                );

        //接收：获取帮派公共信息（启动预加载调用）
        virtual void OnRecv_GetGuildPubInfo(
                );

        //接收：获取所有帮派信息
        virtual void OnRecv_GetAllGuildInfo(
                );

        //接收：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
        virtual void OnRecv_GuildLogin(
                UINT64 qwGuildID //帮派ID
                );

        //接收：玩家登录，拉取可能存在的帮派信息
        virtual void OnRecv_GuildUserLogin(
                UINT64 qwRoleID //玩家ID
                );

        //接收：帮派神像奖励结算
        virtual void OnRecv_GuildStatueReward(
                );

        //接收：请求所有羲和神车信息
        virtual void OnRecv_GetAllGuildXihe(
                UINT32 dwPageSize //发送条数
                );

        //接收：更新玩家羲和神车信息
        virtual void OnRecv_UpdateGuildXihe(
                const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
                NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
                );
        
        //接收：获取帮派战兑换物品
        virtual void OnRecv_GetAllGuildExchangedItem(
                );
        
        //接收：更新帮派战兑换物品信息
        virtual void OnRecv_UpdateGuildExchangedItem(
                const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
                NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
                );
};

extern CCenter2DBGuildS g_Center2DBGuildS;

#endif // #ifndef CENTER_2_DB_GUILD_S_H

