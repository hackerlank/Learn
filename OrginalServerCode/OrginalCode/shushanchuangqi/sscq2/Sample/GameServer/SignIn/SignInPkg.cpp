#include "SignInPkg.h"
#include "Protocols.h"
#include "Player.h"
#include "User.h"
#include "SysMsgDefine.h"
#include "VIPMgr.h"
#include "Parameter.h"
#include "SignInManager.h"

using namespace NVarDefine; 
CSignInPkg::CSignInPkg(CPlayer &rPlayer):_rPlayer(rPlayer)
{

}
UINT64 CSignInPkg::GetBITValue(UINT64 setValue,UINT8 byStart,UINT8 byEnd)
{
    assert(byStart <= byEnd);
    assert(byStart <=63 &&  byEnd <= 63);

    setValue = (setValue << (63-byEnd));
    setValue = (setValue >> (byStart + 63 - byEnd));
    return setValue;

}

void CSignInPkg::BITGetSignDays(UINT64 qwVar,UINT32 &dwSignData)
{
    dwSignData = GetBITValue(qwVar,0,31);
}
void CSignInPkg::BITDoSetSignDay(UINT64& qwVar,UINT8 byDay)
{
    UINT64 qwValue = 1;
    qwVar |=(qwValue << (byDay-1));
}
bool CSignInPkg::BITCheckSignDay(UINT64 qwVar,UINT8 byDay)
{
    UINT64 qwValue = 1;
    qwValue = (qwValue << ( byDay - 1 ));
    return (qwVar & qwValue ) > 0;
}


void CSignInPkg::BITGetReSignTimes(UINT64 qwVar,UINT8 &byReSignTimes)
{
    byReSignTimes = GetBITValue(qwVar,32,39);
}
void CSignInPkg::BITDoAddSignTimes(UINT64& qwVar)
{
    UINT32 dwValue = GetBITValue(qwVar,0,31); 
    qwVar = (qwVar >> 32);
    qwVar++;
    qwVar = (qwVar << 32);
    qwVar += dwValue;

}
void CSignInPkg::BITGetGetAwards(UINT64 qwVar,UINT32 &dwAward)
{
    dwAward = GetBITValue(qwVar,40,63);
}
void CSignInPkg::BITAddAwards(UINT64 &qwVar,UINT8 byId)
{
    if(byId > 24 || byId == 0)
        return ;
    UINT64 qwValue =1;
    qwVar |= ( qwValue << (40+ byId-1));
}

bool CSignInPkg::BITCheckAward(UINT64 qwVar,UINT8 byId)
{
    if(byId > 24 || byId == 0)  
        return false;
    UINT64 qwValue =1;
    return  (qwVar & ( qwValue << (40+ byId-1)) ) > 0;
}

void CSignInPkg::GetSignInfo(UINT32 &dwSignData,UINT8 &byReSignTimes,UINT32 &dwAward)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwValue = rCGameVar.GetVar(NVarDefine::ePlayerSign);  
    BITGetSignDays(qwValue,dwSignData);
    BITGetReSignTimes(qwValue,byReSignTimes);
    BITGetGetAwards(qwValue,dwAward);

}

ESignResult CSignInPkg::DoSign(UINT32 &dwSignData)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwValue = rCGameVar.GetVar(NVarDefine::ePlayerSign);  
    //如果今日已签到
    if(BITCheckSignDay(qwValue,GetDay()))
    {
        return eSignHasDone;
    }
    BITDoSetSignDay(qwValue,GetDay());
    rCGameVar.SetVar(NVarDefine::ePlayerSign,qwValue);
    //发送活跃池奖励
    _rPlayer.GetActivityPkg().AddActivityPool(SParamConfig::wSignInAward);
    BITGetSignDays(qwValue,dwSignData);

    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        _rPlayer.OnEvent(eEventType_CheckIn,vecParam);

    }
    return eSignSucceed;
}

ESignResult CSignInPkg::DoReSign(UINT8 byDay,UINT32 &dwSignData,UINT8 &byReSignTimes)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwValue = rCGameVar.GetVar(NVarDefine::ePlayerSign);  
    //如果该日==0 
    //如果该日 〉=今日
    if(byDay == 0 || byDay >= GetDay())
    {
        return eSignResignErrDate;
    }

    //如果该日已签到
    if(BITCheckSignDay(qwValue,byDay))
    {
        return eSignResignDone;
    }
    //如果补签次数用完
    UINT8 byTimes = 0;
    BITGetReSignTimes(qwValue,byTimes);
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(pCfgVip == NULL)
    {
        return eSignVIP;
    }
    if(byTimes >= pCfgVip->_SignIn)
    {
        return eSignResignOverTimes;
    }
    BITDoAddSignTimes(qwValue);
    BITDoSetSignDay(qwValue,byDay);
    rCGameVar.SetVar(NVarDefine::ePlayerSign,qwValue);
    //发送活跃池奖励
    _rPlayer.GetActivityPkg().AddActivityPool(SParamConfig::wSignInAward);
    BITGetSignDays(qwValue,dwSignData);
    BITGetReSignTimes(qwValue,byReSignTimes);
    
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        _rPlayer.OnEvent(eEventType_CheckInAdd,vecParam);
    }

    return eSignSucceed;

}
ESignResult CSignInPkg::DoGetAward(UINT8 byId,UINT32 &dwAward)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwValue = rCGameVar.GetVar(NVarDefine::ePlayerSign);  

    //Manager判断byId是否合法
    if(byId ==0 || byId > 24)
    {
        return eSignAwardIdErr;
    }
    const SSignInCFGEx *pCfg = g_CSignInManager.GetCFGbyId(byId);
    if(pCfg ==NULL)
    {
        return eSignAwardIdErr;
    }
    //判定奖励是否领过
    if(BITCheckAward(qwValue,byId))
    {
        return eSignAwardHasGet;
    }
    //判断领奖资格
    UINT8 byDays = GetSignDays(qwValue);
    if(byDays < pCfg->_SignIn)
    {
        return eSignAwardLowDays;
    }
    //判断包裹空格
    CPack& oPack = rUser.GetPack();
    TVecItemGenInfo vecItems;
    for(auto it = pCfg->mapAward.begin();it !=  pCfg->mapAward.end();it++)
    {
        SItemGenInfo sInfo;
        sInfo.wItemID = it->first;
        sInfo.dwCount = it->second;
        vecItems.push_back(sInfo);
    }

    if(!oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_SignInAward))
    {
        return eSignAwardPacketFull;
    }
    BITAddAwards(qwValue,byId);
    rCGameVar.SetVar(NVarDefine::ePlayerSign,qwValue);
    BITGetGetAwards(qwValue,dwAward);

    {
        TVecINT32 vecParam;
        vecParam.push_back(byId);
        _rPlayer.OnEvent(eEventType_CheckInGetPrize,vecParam);
    }

    return eSignSucceed;
}

UINT8 CSignInPkg::GetSignDays(UINT64 qwVar)
{
    UINT32 dwSignData = 0;
    BITGetSignDays(qwVar,dwSignData);
    UINT8 byCount = 0;
    while(dwSignData > 0 )
    {
        dwSignData &= (dwSignData-1);
        byCount++;
    }
    return byCount;
}

UINT8 CSignInPkg::GetDay()
{     
    time_t cur = Time::Now();
    struct tm t_tm;
    __LOCALTIME_R(&cur, &t_tm);
    return   t_tm.tm_mday;
}
