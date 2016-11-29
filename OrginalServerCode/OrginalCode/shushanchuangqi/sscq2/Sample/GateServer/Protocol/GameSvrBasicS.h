#pragma once
#include "GameSvrBasicSvr.h"

using namespace NGameSvrBasic;

class CGameSvrBasicS : public CGameSvrBasicSvr
{
public:
	//接收：心跳
	virtual bool OnRecv_KeepAlive(shared_func<SKeepAliveAck>& fnAck
		) override;
};
