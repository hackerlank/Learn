#include "stdafx.h"
#include "Protocols.h"

//接收：玩家请求进入服务器应答
void CLogin2CenterCommC::OnRecv_UserLoginAck(
	EReqResult eResult, //登陆请求的结果
	UINT64 qwUsrID, //帐号ID
	UINT32 dwSessionID, //会话ID
	const std::string& strGateAddr, //GateServer的地址
	UINT16 wGatePort, //GateServer的端口
	UINT32 dwCryptoCode //登录验证码
	)
{
	static IConnectionHandler* pHandler = g_LoginProtS.GetConnectionHandler();
	if(pHandler == NULL)
	{
		LOG_CRI << "pHandler is NULL!";
		return;
	}
	static CLoginAuthHandler* pAuthHandler = dynamic_cast<CLoginAuthHandler*>(pHandler);
	if(pAuthHandler == NULL)
	{
		LOG_CRI << "pAuthHandler is NULL!";
		return;
	}
	ISocket* pSocket = pHandler->GetSocket(dwSessionID);
	if(pSocket == NULL)
	{
		LOG_CRI << "pSocket is NULL, UsrID: " << qwUsrID;
		return;
	}
	NLoginProt::ELoginResult eEnterResult = NLoginProt::eLoginOtherErr;
	switch(eResult)
	{
        case eReqSucceed:
            eEnterResult = NLoginProt::eLoginSucceed;
            break;
        case eReqFull:
            eEnterResult = NLoginProt::eServerFull;
            break;
        case eReqOnline:
            eEnterResult = NLoginProt::eRoleOnline;
            break;
        case eReqKickWait:
            eEnterResult = NLoginProt::eKickWait;
            break;
        case eReqLeaveWait:
            eEnterResult = NLoginProt::eLeaveWait;
            break;
        case NLogin2CenterComm::eReqTooFreqent:
            eEnterResult = NLoginProt::eEnterTooFreqent;
            break;
        case eReqNotInited:
            eEnterResult = NLoginProt::eServerInitErr;
            break;
        default:
            break;
	}
	ULONG uAddr = pSocket->GetPeerAddrNum();
	if(Config._setInAddr.find(uAddr) != Config._setInAddr.end())
	{
		auto it = Config._mapOutAddr.find(strGateAddr);
		if(it != Config._mapOutAddr.end())
			(string&)strGateAddr = it->second;
	}
	string& strPkg = g_LoginProtS.BuildPkg_LoginAck(eEnterResult,qwUsrID, strGateAddr, wGatePort, dwCryptoCode);
	pAuthHandler->Send(*pSocket, strPkg.c_str(), (UINT32)strPkg.size());
	pSocket->Close();
}
