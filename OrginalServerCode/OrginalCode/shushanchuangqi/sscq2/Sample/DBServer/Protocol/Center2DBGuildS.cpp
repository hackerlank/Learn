// =====================================================================================
//
//       Filename:  Center2DBGuildS.cpp
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

#include "Center2DBGuildS.h"

#include "stdafx.h"
#include "Protocols.h"

#include "DBGuildMgr.h"
#include "DBPubGuildMgr.h"
#include "DBGuildXiheTable.h"
#include "DBGuildExchangedItemTable.h"

CCenter2DBGuildS g_Center2DBGuildS;

//接收：帮派数据更新
void CCenter2DBGuildS::OnRecv_GuildDataUpdate(
        UINT64 qwGuildID, //帮派ID
        NGuildProt::EGuildDataType eDataType, //更新数据类型
        NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
        const std::string& strData //更新数据
        )
{
    CDBGuildMgr::Instance().GuildDataOperate(qwGuildID, eDataType, eUpdateType, strData);
}

//接收：帮派公共信息更新
void CCenter2DBGuildS::OnRecv_GuildPubDataUpdate(
        UINT64 qwGuildID, //帮派ID
        NGuildProt::EGuildPubDataType eDataType, //更新数据类型
        NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
        const std::string& strData //更新数据
        )
{
    CDBPubGuildMgr::Instance().DataOperate(qwGuildID, eDataType, eUpdateType, strData);
}
//接收：获取帮派公共信息（启动预加载调用）
void CCenter2DBGuildS::OnRecv_GetGuildPubInfo(
        )
{
    CDBPubGuildMgr::Instance().GetAllData(20);
}

//接收：获取所有帮派信息
void CCenter2DBGuildS::OnRecv_GetAllGuildInfo(
        )
{
    CDBGuildMgr::Instance().LoadAllGuildData();
}

//接收：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
void CCenter2DBGuildS::OnRecv_GuildLogin(
        UINT64 qwGuildID //帮派ID
        )
{
    CDBGuildMgr::Instance().LoginGuild(qwGuildID, 0);
}

//接收：玩家登录，拉取可能存在的帮派信息
void CCenter2DBGuildS::OnRecv_GuildUserLogin(
        UINT64 qwRoleID //玩家ID
        )
{
    CDBGuildMgr::Instance().UserLoginGuild(qwRoleID);
}

//接收：帮派神像奖励结算
void CCenter2DBGuildS::OnRecv_GuildStatueReward(
        )
{
    CDBGuildMgr::Instance().SendAllGuildWorshipInfo();
}

//接收：请求所有羲和神车信息
void CCenter2DBGuildS::OnRecv_GetAllGuildXihe(
        UINT32 dwPageSize //发送条数
        )
{
    g_CDBGuildXiheManager.GetAllGuildXihe(dwPageSize);
}

//接收：更新玩家羲和神车信息
void CCenter2DBGuildS::OnRecv_UpdateGuildXihe(
        const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
        NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
        )
{
    if (eUpdateType == eOpUpdate || eUpdateType == eOpAdd)
        g_CDBGuildXiheManager.Update(oGuildXihe);
    else if (eUpdateType == eOpDel)
        g_CDBGuildXiheManager.DelData(oGuildXihe.qwRoleID);
}


//接收：获取帮派战兑换物品
void CCenter2DBGuildS::OnRecv_GetAllGuildExchangedItem(
)
{
   g_CDBGuildExchangedItemTable.LoadGuildExchangedItem(); 
}

//接收：更新帮派战兑换物品信息
void CCenter2DBGuildS::OnRecv_UpdateGuildExchangedItem(
		const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	)
{
    if (eOpAdd == eUpdateType)
        g_CDBGuildExchangedItemTable.AddGuildExchangedItem(sGuildExchangedItem); 
    if (eOpUpdate == eUpdateType)
        g_CDBGuildExchangedItemTable.UpdateGuildExchangedItem(sGuildExchangedItem); 
    if (eOpDel == eUpdateType)
        g_CDBGuildExchangedItemTable.DelGuildExchangedItem(); 
}

