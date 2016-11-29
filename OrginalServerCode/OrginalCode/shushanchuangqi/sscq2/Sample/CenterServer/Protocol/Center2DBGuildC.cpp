// =====================================================================================
//
//       Filename:  Center2DBGuildC.cpp
//
//    Description:  Center与DB帮派相关协议处理
//
//        Version:  1.0
//        Created:  03/21/2015 01:17:05 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "Center2DBGuildC.h"

#include "stdafx.h"
#include "GuildMgr.h"
#include "GuildUserMgr.h"
#include "GuildUser.h"
#include "GuildXiheManager.h"
/////////////////////////////////////////////////////////////////////////////

CCenter2DBGuildC g_Center2DBGuildC;

//接收：帮派公共信息加载返回
void CCenter2DBGuildC::OnRecv_GuildPubInfoNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
        )
{
    CGuildMgr::Instance().InitPubInfo(dwCurSize, dwTotalSize, vecPubGuildAllInfo);
}

//接收：帮派
void CCenter2DBGuildC::OnRecv_GuildLoginNotify(
        UINT64 qwGuildID, //帮派ID
        const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
        )
{
    CGuildMgr::Instance().InitGuildInfo(qwGuildID, sData);
}

//接收：帮派用户登录返回
void CCenter2DBGuildC::OnRecv_GuildUserLoginNotify(
        UINT64 qwRoleID, //玩家ID
        const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (pGuildUser)
    {
        LOG_DBG << "GuildUser(" << pGuildUser->GetID() << ") has Logined.";
        return;     // 已经登录过的
    }
    if (vecGuildUserInfo.empty())
    {
        LOG_DBG << "vecGuildUserInfo.empty().";
        return;
    }
    for (auto it = vecGuildUserInfo.begin(); it != vecGuildUserInfo.end(); ++it)
    {
        const SDBGuildUserInfo& rGuildUserInfo = *it;
        pGuildUser = CGuildUserMgr::Instance().CreateGuildUser(rGuildUserInfo);
        break;
    }
}

	//接收：帮派
void CCenter2DBGuildC::OnRecv_AllGuildLoginNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
        )
{
    for (auto it = vecData.begin(); it != vecData.end(); ++it)
    {
        CGuildMgr::Instance().InitGuildInfo(*it);
    }
    if (dwCurSize >= dwTotalSize)
    {
        Config.SetInited(eDBInitGuildAll);
        if (Config.IsSomeInited(eDBInitGuild))
            CGuildMgr::Instance().SyncBattleRank();
        CGuildMgr::Instance().InitGuildRankByLevel();
        CGuildMgr::Instance().LoadAllGuildExchangedItemFromDB();
    }
}

//接收：返回请求帮派供奉人数
void CCenter2DBGuildC::OnRecv_SendAllGuildStatueWorshipCount(
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
        )
{
    CGuildMgr::Instance().StatueReward(vecGSWorshiInfo);
}

//接收：返回所有羲和神车信息
void CCenter2DBGuildC::OnRecv_SendAllGuildXihe(
    UINT32 dwPageSize, //已发送条数
    UINT32 dwTotalSize, //总条数
    const NGuildProt::TVecGuildXihe& vecSendData //更新信息
)
{
    GuildXiheManager.RecieveDBData(dwPageSize, dwTotalSize, vecSendData);
}

//接收：所有帮派兑换物品加载返回
void CCenter2DBGuildC::OnRecv_SendAllGuildExchangedItem(
    const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
)
{
    CGuildMgr::Instance().InitGuildExchangedItem(vecGuildExchangedItem);
}

