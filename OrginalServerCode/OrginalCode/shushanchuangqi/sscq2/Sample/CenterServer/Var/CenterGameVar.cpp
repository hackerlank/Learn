
#include "stdafx.h"
#include "CenterGameVar.h"
#include "Protocols.h"
#include "RoleInfoDefine.h"
#include "ArenaManager.h"
#include "CenterGameVar.h"
CCenterGameVar g_CenterGameVar;
using namespace NRoleInfoDefine;
void CCenterGameVar::Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange)
{
    if( eDataChange == eOpDel)
    {
        g_Center2DBCommC.Send_DelGameVar(wVar);
        LOG_INF<<"g_Center2DBCommC.Send_DelGameVar(" << wVar << ")";
    }
    else if(eDataChange == eOpUpdate|| eDataChange == eOpAdd)
    {
        SGameVarsDBInfo oVarsDBInfo;
        oVarsDBInfo.byServerType = eHostCenter;
        oVarsDBInfo.wVar = wVar;
        oVarsDBInfo.qwValue = qwValue;
        oVarsDBInfo.dwExpired = dwExpired;
        if(eDataChange == eOpUpdate)
        {
            g_Center2DBCommC.Send_UpdateGameVar(oVarsDBInfo);
            LOG_INF<<"g_Center2DBCommC.Send_UpdateGameVar(oVarsDBInfo);";
        }
        else
        {
            g_Center2DBCommC.Send_AddGameVar(oVarsDBInfo);
            LOG_INF<<"g_Center2DBCommC.Send_AddGameVar(oVarsDBInfo)";
        }
    }
}

void CCenterGameVar::LoadFromDB()
{
    if(_bIsLoad)
        return;
    g_Center2DBCommC.Send_GetGameVar(
            [this](UINT8 byRet_,const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar)
            {
                _bIsLoad = true;
                Config.SetInited(eDBInitGameVar);
                for(auto & rVarDBInfo : vecVar)
                {
                    SetVarFromDB(rVarDBInfo.wVar, rVarDBInfo.qwValue, rVarDBInfo.dwExpired);
                }
                CArenaManager::DoInitCase();
            });
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

