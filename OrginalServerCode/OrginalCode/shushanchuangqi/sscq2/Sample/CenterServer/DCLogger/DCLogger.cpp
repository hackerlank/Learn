// =====================================================================================
//
//       Filename:  DCLogger.cpp
//
//    Description:  腾讯日志上报
//
//        Version:  1.0
//        Created:  10/21/2014 09:31:12 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DCLogger.h"
#include "User.h"
#include "Config.h"
#include "DCWorker.h"


class SysMsgItem;

bool CDCLogger::Init()
{
    version = _VERSION;
    appid = _APPID;

    memset(_dwOnlineNumDomain, 0, sizeof(_dwOnlineNumDomain));
    for(int i = 0; i < MAX_DOMAIN; ++i)
        _dwDomain[i] = i + 1;

    return true;
}

void CDCLogger::IncDomainOnlineNum(UINT8 domain)
{
    for(int i = 0; i < MAX_DOMAIN; ++i)
    {
        if(domain == _dwDomain[i])
            ++_dwOnlineNumDomain[i];
    }
}

void CDCLogger::DecDomainOnlineNum(UINT8 domain)
{
    for(int i = 0; i < MAX_DOMAIN; ++i)
    {
        if(domain == _dwDomain[i] && _dwOnlineNumDomain[i] > 0)
            --_dwOnlineNumDomain[i];
    }
}

bool CDCLogger::Reg(CUserPtr pUser)
{
    std::ostringstream msg;

    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=3&actionid=2";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "source=";
    msg << pUser->GetVia();
    msg << "&" << "touid=&toopenid=&level=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";
    DC().Push(msg.str());
    return true;
}

bool CDCLogger::Login(CUserPtr pUser)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=4&actionid=1";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "source=";
    msg << pUser->GetVia();
    msg << "&" << "touid=&toopenid=&level=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}

bool CDCLogger::Logout(CUserPtr pUser)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=4&actionid=9";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "onlinetime=";
    msg << time(NULL) - pUser->GetCurLoginTime(); 
    msg << "&" << "source=";
    msg << pUser->GetVia();
    msg << "&" << "touid=&toopenid=&level=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}

void CDCLogger::Online()
{
    for(int i = 0; i < MAX_DOMAIN; ++ i)
    {
        if(_dwOnlineNumDomain[i])
            Online(_dwOnlineNumDomain[i], _dwDomain[i]);
    }
}

bool CDCLogger::Online(UINT32 num, UINT8 domain)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain="; 
    msg << (int)domain;
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=5&actionid=14";
    msg << "&" << "user_num=";
    msg << num;
    msg << "&" << "opuid=";
    msg << Config._wGroup;
    msg << "&" << "userip=&svrip=&opopenid=&touid=&toopenid=&level=&source=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&onlinetime=&key=&keycheckret=&safebuf=&remark=";

    DC().Push(msg.str());
    return true;
}

bool CDCLogger::Consume(CUserPtr pUser, UINT32 dwTotal, UINT32 c)
{
    stringstream msg;
    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=1&actionid=5";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "itemid=29999";
    msg << "&" << "itemtype=29";
    msg << "&" << "itemcnt=1";
    msg << "&" << "modifyfee=";
    msg << c*10;
    msg << "&" << "totalfee=";
    msg << dwTotal*10;
    msg << "&" << "touid=&toopenid=&level=&source=&modifyexp=&totalexp=&modifycoin=&totalcoin=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}

bool CDCLogger::Fee(CUserPtr pUser, UINT32 dwTotal, INT32 c)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=1&actionid=15";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "itemid=29999";
    msg << "&" << "itemtype=29";
    msg << "&" << "itemcnt=";
    msg << (c+9)/10;
    msg << "&" << "modifyfee=";
    msg << c*10;
    if (dwTotal)
    {
        msg << "&" << "totalfee=";
        msg << dwTotal*10;
    }
    else
        msg << "&" << "totalfee=";
    msg << "&" << "touid=&toopenid=&level=&source=&modifyexp=&totalexp=&modifycoin=&totalcoin=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}

bool CDCLogger::Blue(CUserPtr pUser)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=5&actionid=101";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "touid=&toopenid=&level=&source=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}

bool CDCLogger::D3d6(CUserPtr pUser)
{
    std::ostringstream msg;

    msg << "version=";
    msg << version;
    msg << "&" << "appid=";
    msg << appid;
    msg << "&" << "userip=";
    msg << pUser->GetClientIP();
    msg << "&" << "svrip=";
    msg << Config._wListenPort;
    msg << "&" << "time=";
    msg << time(NULL);
    msg << "&" << "domain=";
    msg << pUser->GetDomain();
    msg << "&" << "worldid=";
    msg << Config._wGroup;
    msg << "&" << "optype=5&actionid=102";
    msg << "&" << "opuid=";
    msg << pUser->GetRoleID();
    msg << "&" << "opopenid=";
    msg << pUser->GetOpenId();
    msg << "&" << "key=";
    msg << pUser->GetOpenKey();
    msg << "&" << "touid=&toopenid=&level=&source=&itemid=&itemtype=&itemcnt=&modifyexp=&totalexp=&modifycoin=&totalcoin=&modifyfee=&totalfee=&onlinetime=&keycheckret=&safebuf=&remark=&user_num=";

    DC().Push(msg.str());
    return true;
}


