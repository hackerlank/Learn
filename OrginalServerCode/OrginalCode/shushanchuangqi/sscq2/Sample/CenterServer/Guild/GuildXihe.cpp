// =====================================================================================
//
//       Filename:  GuildXihe.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  01/29/2015 12:47:30 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================

#include "Center2DBGuildC.h"
#include "GuildMgr.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "GuildXihe.h"
#include "User.h"
#include "Protocols.h"
#include "UserMgr.h"

static STruckInfo stTruckInfo(0, 0, 0, "",0);

CGuildXihe::CGuildXihe(UINT64 qwRoleID) : _qwOwnerID(qwRoleID), _byStage(EXiheStage(0)), _dwEndTime(0), _byRequest(0)
{}

CGuildXihe::~CGuildXihe()
{}

void CGuildXihe::ToProt(SGuildXihe& oGuildXihe)
{
    oGuildXihe.qwRoleID     = GetOwnerID();
    oGuildXihe.vecTruckInfo = GetTruckInfo();
    oGuildXihe.byStage      = GetStage();
    oGuildXihe.dwEndTime    = GetEndTime();
    oGuildXihe.byRequest    = GetRequest();
}

void CGuildXihe::Update2DB(EDataChange eDataChange/* = eOpUpdate*/)
{
    SGuildXihe oGuildXihe;
    ToProt(oGuildXihe);
    g_Center2DBGuildC.Send_UpdateGuildXihe(oGuildXihe, eDataChange);
}

void CGuildXihe::UpdateGuildXiheInfo(CUserPtr pUser)
{
    if (!pUser)
        return;
    if(_vecTruckInfo.size() == 0)
    {
        AssignTask();
        Update2DB(eOpUpdate);
        LOG_WRN<<"ReAssgin Task.";
    }
    SGuildXihe oGuildXihe;
    if(_vecTruckInfo.size() == 0)
    {
        AssignTask();
        Update2DB(eOpUpdate);
        LOG_WRN<<"ReAssign Task.";
    }
    ToProt(oGuildXihe);
    pUser->SendPkg(g_GuildProtS.BuildPkg_UpdateGuildXiheInfo(oGuildXihe));
}

UINT8 CGuildXihe::GetFinishTaskCount()
{
    UINT8 byCount = 0;
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byStatus == eXiheTaskFinishURe || it->byStatus == eXiheTaskFinishRe)
            ++ byCount;
    }
    return byCount;
}

bool CGuildXihe::IsFinishAllTask()
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byStatus != eXiheTaskFinishURe && it->byStatus != eXiheTaskFinishRe)
            return false;
    }
    return true;
}

void CGuildXihe::AssignTask()
{
    _vecTruckInfo.clear();
    UINT8 byLevel = 0;
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(GetOwnerID());
    if (!pGuildUser)
    {
        LOG_WRN<<"pGuildUser("<<GetOwnerID()<<") null.";
        return;
    }
    byLevel = pGuildUser->GetLevel();
    TVecUINT8 vecTruckIDs;
    CGuildMgr::Instance().GetTruckIDRandom(byLevel, vecTruckIDs);
    for (size_t i = 0; i < vecTruckIDs.size(); ++ i)
    {
        STruckInfo oTruck(vecTruckIDs[i], UINT8(eXiheTaskUnfinish), i, "",pGuildUser->GetQuality());
        _vecTruckInfo.push_back(oTruck);
        //LOG_WRN << "byLevel:" << byLevel << " byTruckID:" << vecTruckIDs[i] << " Pos:" << i;
    }
}

void CGuildXihe::SetTruckHelpName(UINT8 byPos, const string& strName,UINT8 byColor)
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byPos == byPos)
        {
            it->strName = strName;
            it->byColor = byColor;
            return;
        }
    }
}

void CGuildXihe::SetTruckStatus(UINT8 byPos, UINT8 byStatus)
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byPos == byPos)
        {
            it->byStatus = byStatus;
            return;
        }
    }
}

UINT8 CGuildXihe::GetTruckStatus(UINT8 byPos) const
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byPos == byPos)
            return it->byStatus;
    }
    return 0xFF;
}

STruckInfo& CGuildXihe::GetTruckInfoByPos(UINT8 byPos)
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byPos == byPos)
            return *it;
    }
    return stTruckInfo;
}

STruckInfo& CGuildXihe::GetTruckInfoByID(UINT8 byTruckID)
{
    for (auto it = _vecTruckInfo.begin(); it != _vecTruckInfo.end(); ++ it)
    {
        if(it->byTruckID == byTruckID)
            return *it;
    }
    return stTruckInfo;
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

