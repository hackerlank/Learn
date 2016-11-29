// =====================================================================================
//
//       Filename:  Center2DBGuildC.h
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

#ifndef CENTER_2_DB_GUILD_C_H
#define CENTER_2_DB_GUILD_C_H

#pragma once
#include "Center2DBGuildClt.h"

using namespace NCenter2DBGuild;

class CCenter2DBGuildC : public CCenter2DBGuildClt
{
public:
	///////////////////////////////////////////////////////////////////////////////
	//接收：帮派公共信息加载返回
	virtual void OnRecv_GuildPubInfoNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
	);

	//接收：帮派
	virtual void OnRecv_AllGuildLoginNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
	);

	//接收：帮派
	virtual void OnRecv_GuildLoginNotify(
		UINT64 qwGuildID, //帮派ID
		const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
	);

	//接收：帮派用户登录返回
	virtual void OnRecv_GuildUserLoginNotify(
		UINT64 qwRoleID, //玩家ID
		const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
	);

	//接收：返回请求帮派供奉人数
	virtual void OnRecv_SendAllGuildStatueWorshipCount(
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
	);

	//接收：返回所有羲和神车信息
	virtual void OnRecv_SendAllGuildXihe(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecGuildXihe& vecSendData //更新信息
	);

    //接收：所有帮派兑换物品加载返回
	virtual void OnRecv_SendAllGuildExchangedItem(
		const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
	);

};

extern CCenter2DBGuildC g_Center2DBGuildC;

#endif // #ifndef CENTER_2_DB_GUILD_C_H

