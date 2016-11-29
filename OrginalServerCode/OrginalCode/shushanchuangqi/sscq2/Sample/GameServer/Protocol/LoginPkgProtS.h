
#pragma once
#include "LoginPkgProtSvr.h"

using namespace NLoginPkgProt;

class CLoginPkgProtS : public CLoginPkgProtSvr
{
public:	
     //接收：获取礼包
	virtual bool OnRecv_GetLoginPkg(
		UINT8 byIndex, //累计天数
		shared_func<SGetLoginPkgAck>& fnAck //返回回调函数
	);
      //接收：登入礼包信息
	virtual bool OnRecv_GetPkgInfo(
		shared_func<SGetPkgInfoAck>& fnAck //返回回调函数
	);

private:
};

extern CLoginPkgProtS g_LoginPkgProtS;
