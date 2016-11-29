#include "stdafx.h"
#include "Protocols.h"
#include "GUIDMgr.h"
#include "ProtoVersion.h"
#include "SHA1Engine.h"
//#include "GlobalDefine.h"
//接收：登陆请求
void CLoginProtS::OnRecv_LoginReq(
        UINT64 qwUsrID, //帐号ID
        UINT16 usGroupID, //区号
        UINT32 dwVersion, //版本号
        const string& strPassword
        )
{
    string strGateIP;
    UINT16 wGatePort = 0;
    UINT32 dwCryptoCode = 0;
    //TODO :check version
    //TODO:check area
    //TODO:check pwd
    //TODO:Create GUID
    ISocket* pSocket = _pConnHandler->GetCurSock();
    if(pSocket == NULL)
    {
        Send_LoginAck(eLoginOtherErr,0, strGateIP, wGatePort, dwCryptoCode);
        return;
    }
    ULONG ulAddr = pSocket->GetHostAddrNum();
    if(ulAddr == 0)
    {
        Send_LoginAck(eLoginOtherErr,0, strGateIP, wGatePort, dwCryptoCode);
        return;
    }
    if(Config._wGroup != usGroupID)
    {
        Send_LoginAck(eNotActivated, 0,strGateIP, wGatePort, dwCryptoCode);
        return ;
    }
    if(dwVersion != NProtoVersion::EPROTOVERSION)
    {
        Send_LoginAck(eVersionLess, 0,strGateIP, wGatePort, dwCryptoCode);
        return ;
    }
    if(!checkKey(strPassword.c_str(), qwUsrID))
    {
        Send_LoginAck(ePasswordInvalid, 0,strGateIP, wGatePort, dwCryptoCode);
        return ;
    }

    UINT64 qwRoleId = CGUIDMgr::GetGUID(usGroupID,0,GUID_ROLE,qwUsrID);
    UINT8 byType = Config.GetAddrType(ulAddr);
    if(!g_Login2CenterCommC.Send_UserLoginReq(qwRoleId, pSocket->GetPeerID(), byType))
        Send_LoginAck(eLoginServerErr,0, strGateIP, wGatePort, dwCryptoCode);
    LOG_INF << qwRoleId << " request to  Login"; 
}

bool CLoginProtS::checkKey(const char* _hashval, UINT64 _userid )
{
  #ifdef _DEBUG
     return true;
  #endif
    
    std::string& key1 = Config._strLoginKey1;
    std::string& key2 = Config._strLoginKey2;
    if(key1 == string("0") && key2 == string("0"))
    {
        return true;
    }
    SHA1Engine sha1;
    sha1.update(_hashval + 8, 4);
    sha1.update(key1.c_str(), static_cast<unsigned int>(key1.length()));
    sha1.update(_hashval, 4);
    sha1.update(&_userid, sizeof(UINT64));
    sha1.update(_hashval + 12, 4);
    sha1.update(key2.c_str(), static_cast<unsigned int>(key2.length()));
    sha1.update(_hashval + 4, 4);
    std::vector<UINT8> buf = sha1.digest();

    if (memcmp(&buf.front(), _hashval + 16, 20) == 0)
        return true;
    return false;
}
