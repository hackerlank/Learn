#pragma once
#include "LoginProtSvr.h"

using namespace NLoginProt;

class CLoginProtS : public CLoginProtSvr
{
public:
	//接收：登陆请求
	virtual void OnRecv_LoginReq(
		UINT64 qwUsrID, //帐号ID
		UINT16 usGroupID, //区号
		UINT32 dwVersion, //版本号
        const string& strPassword //密码
	);
    bool checkKey(const char* _hashval, UINT64 _userid = 20110503ll);

};
