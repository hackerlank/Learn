
#pragma once
#include "ViewInfoProtSvr.h"

using namespace NViewInfoProt;

class CViewInfoProtS : public CViewInfoProtSvr
{
public:
    //接收：获取对方主角信息
	virtual bool OnRecv_GetRoleInfo(
		const std::string& strReceiveName, //对方玩家名字
		shared_func<SGetRoleInfoAck>& fnAck //返回回调函数
	);

	//接收：获取散仙信息
	virtual bool OnRecv_GetFighterInfo(
		const std::string& strReceiveName, //对方玩家名字
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SGetFighterInfoAck>& fnAck //返回回调函数
	);

    bool GetRoleInfo(
    UINT64 qwReceiveID, //对方玩家ID
    NViewInfoProt::SRoleData& roleData //玩家信息 
    );
private:
    bool SetGuildInfo(
    UINT64 qwReceiveID, 
    UINT64 qwGuildID, 
    const string& strGuildName, 
    UINT8 byGuildLvl, 
    NViewInfoProt::SRoleData& roleData
    );

    bool GetFighterInfo(
    UINT64 qwReceiveID, //对方玩家ID
    UINT64 qwInstID, //散仙唯一ID
    NViewInfoProt::SFighterData& fighterData //散仙信息 
    );
};

extern CViewInfoProtS g_ViewInfoProtS;
