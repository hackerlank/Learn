// =====================================================================================
//
//       Filename:  DCLogger.h
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

#ifndef DC_LOGGER_H
#define DC_LOGGER_H

#include "stdafx.h"
#include "Config.h"
#include "dcapi_cpp.h"
#include "Singleton.h"

using namespace DataCollector;

#if 0
    1   qzone
    2   pengyou
    2   xiaoyou
    3   qqweibo
    4   qplus
    5   caifutong
    10  qqgame
    11  q3366
    12  kingxin(s3)
    16  gamelife
    17  qqunion
    23  gamebox
    40  facebook
    41  6waves
    42  113
    43  pps
    60  kingnet(xy)
    61  union_xy
    62  gamebase
    63  pubgame
#endif

#define MAX_DOMAIN 256

class CDCLogger : public Singleton<CDCLogger>
{
    public:

        bool Init();

        bool Reg(CUserPtr pUser);
        bool Login(CUserPtr pUser);
        bool Logout(CUserPtr pUser);
        bool Online(UINT32 num, UINT8 domain);
        bool Consume(CUserPtr pUser, UINT32 dwTotal, UINT32 c);
        bool Fee(CUserPtr pUser, UINT32 dwTotal, INT32 c);
        bool Blue(CUserPtr pUser);
        bool D3d6(CUserPtr pUser);
        bool CheckYB(CUserPtr pUser);

        void Online();

        void IncDomainOnlineNum(UINT8 domain);
        void DecDomainOnlineNum(UINT8 domain);
        void GetOnline(UINT32* buf)
        {
            if (!buf) return;
            memcpy(buf, _dwOnlineNumDomain, sizeof(_dwOnlineNumDomain));
        }
    private:
        UINT32 version;
        UINT64 appid;
        UINT32 _dwOnlineNumDomain[MAX_DOMAIN];
        UINT32 _dwDomain[MAX_DOMAIN];
};

#define CDCLOGGER()  CDCLogger::Instance()

#endif // #ifndef DC_LOGGER_H
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
