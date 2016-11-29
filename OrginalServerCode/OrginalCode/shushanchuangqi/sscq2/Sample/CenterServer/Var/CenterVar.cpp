
#include "stdafx.h"
#include "CenterVar.h"
#include "Protocols.h"
#include "User.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
void CCenterVar::Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange)
{
    SVarsDBInfo oVarsDBInfo;
    oVarsDBInfo.qwRoleID = GetUser().GetUserID();
    oVarsDBInfo.byServerType = eHostCenter;
    oVarsDBInfo.wVar = wVar;

    if (eDataChange == eOpDel)
    {
        oVarsDBInfo.qwValue = 0;
        oVarsDBInfo.dwExpired = 0;
    }
    else
    {
        oVarsDBInfo.qwValue = qwValue;
        oVarsDBInfo.dwExpired = dwExpired;
    }
    string strData;
    COutArchive iar(strData);
    iar << oVarsDBInfo;
    g_Center2DBCommC.Send_RoleDataUpdate(oVarsDBInfo.qwRoleID, eTypeVarInfo, eDataChange, strData);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

