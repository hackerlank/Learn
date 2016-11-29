#include "RetainMgr.h"
#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
CRetainMgr g_RetainMgr;

void  CRetainMgr::LoadFromDB()
{
   g_Center2DBCommC.Send_GetRetain([](UINT8 byRet_, const NWonderActivityProt::TVecRetain& vecRet)
            {
                if(0 == byRet_)
                {
                       g_RetainMgr.OnLoad(vecRet);
                }
            });
}

void CRetainMgr::OnLoad(const TVecRetain& vecData)
{
      for(auto &oIt : vecData)
      {
          SWonderRetainKey oKey(oIt.qwRoleID,oIt.wActID,oIt.wType);
          //LOG_CRI << " Retain: qwRoleID("<<oIt.qwRoleID <<")|wActID("<<oIt.wActID<<")|Index("<<oIt.wType<<").";
          _mapID2Retain.insert(make_pair(oKey,oIt));
      }
}

bool CRetainMgr::GetRetainByType(UINT16 &wActID,UINT16 &wType, SRetain &rRetain)
{
    UINT64 qwRoleID = 0;
    for(auto &oIt : _mapID2Retain)
    {
        if(oIt.first.wActID == wActID && oIt.first.wType == wType)
        {
            qwRoleID = oIt.first.qwRoleID;
            if(!GetRetainValue(qwRoleID,wActID,wType,rRetain))
            {
                LOG_INF << "GetRetainValue Error!" ;
                return false;
            }
        }
    }
    return true;
}

bool CRetainMgr::GetRetainByRoleID(UINT64 qwRoleID,UINT16 &wActID, SRetain &rRetain)
{
    UINT16 wType = 0;
    for(auto &oIt : _mapID2Retain)
    {
        if(oIt.first.wActID == wActID && oIt.first.qwRoleID == qwRoleID)
        {
            wType = oIt.first.wType;
            if(!GetRetainValue(qwRoleID,wActID,wType,rRetain))
            {
                LOG_INF << "GetRetainValue Error!" ;
                return false;
            }
        }
    }
    return true;

}


bool CRetainMgr::GetRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType,SRetain &rRetain)
{
    if(qwRoleID == 0 || wActID == 0)
        return false;
    SWonderRetainKey oKey(qwRoleID,wActID,wType);
    auto oIt = _mapID2Retain.find(oKey);
    if(oIt == _mapID2Retain.end())
        return false;
    rRetain = oIt->second;
    return true;
}

bool CRetainMgr::SetRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType,SRetain &sSave)
{
    if(qwRoleID == 0 || wActID == 0)
        return false;
    time_t tNow = time(NULL);
    SRetain sTmp;
    sTmp.qwRoleID = qwRoleID;
    sTmp.strName  = sSave.strName;
    sTmp.strGuildName  = sSave.strGuildName;
    sTmp.wID = sSave.wID;
    sTmp.byCareer = sSave.byCareer;
    sTmp.bySex    = sSave.bySex;
    sTmp.wActID   = wActID;
    sTmp.wType    = wType;
    sTmp.dwValue  = sSave.dwValue;
    sTmp.dwTime   = tNow;
    SWonderRetainKey oKey(qwRoleID,wActID,wType);
    auto oIt = _mapID2Retain.find(oKey);
    if(oIt == _mapID2Retain.end())
    {
        _mapID2Retain[oKey] = sTmp;
        g_Center2DBCommC.Send_UpdateRetain(sTmp,eOpAdd);
    }else
    {
        oIt->second.dwValue = sSave.dwValue;
        oIt->second.dwTime = tNow;
        g_Center2DBCommC.Send_UpdateRetain(sTmp,eOpUpdate);
    }
    return true;
}

bool CRetainMgr::SetRetain(SRetain &sRetain)
{
    if(!SetRetainValue(sRetain.qwRoleID,sRetain.wActID,sRetain.wType,sRetain))
    {
        return false;
    }
    return true;
}

bool CRetainMgr::DelRetain(SRetain &sRetain)
{
    if(!DelRetainValue(sRetain.qwRoleID,sRetain.wActID,sRetain.wType,sRetain))
    {
        return false;
    }
    return true;
}

bool CRetainMgr::DelRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType,SRetain &sRetain)
{
    if(qwRoleID == 0 || wActID == 0)
        return false;
    SWonderRetainKey oKey(qwRoleID,wActID,wType);
    auto oIt = _mapID2Retain.find(oKey);
    if(oIt != _mapID2Retain.end())
    {
        _mapID2Retain.erase(oKey);
    }
    g_Center2DBCommC.Send_UpdateRetain(sRetain,eOpDel);
    return true;
}

bool  CRetainMgr::DelRetainByActID(UINT16 &wActID)
{
    for(auto oIt=_mapID2Retain.begin(); oIt!=_mapID2Retain.end();)
    {
        auto itInfo = oIt;
        ++oIt;
        if(itInfo->first.wActID == wActID)
        {
            if(!DelRetain(itInfo->second))
            {
                return false;
            }       
        }
    }
    return true;
}
