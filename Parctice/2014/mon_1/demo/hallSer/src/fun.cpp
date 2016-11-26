//全局函数定义
#include"fun.h"
extern set<IpInfo> ipInfoSet;
bool chkIpInfo(const IpInfo &ipInfo)
{
    set<IpInfo>::iterator ip_it = ipInfoSet.find(ipInfo);
    return ip_it != ipInfoSet.end();
}
    