#include  "Activity.h"
#include "RTime.h"
#include "Protocols.h"
#include "ActivityMgr.h"

using namespace NActivity;

CActivity::CActivity(UINT32 dwActID,UINT8 byIndex)
    : _dwActID(dwActID)
    , _byIndex(byIndex)
{
    _dwAlarm = 0;
    _dwReady = _dwAlarm + 1 * 60;
    _dwBegin = _dwReady + 1 * 60;
    _dwEnd = _dwBegin + 5 * 60;
    _eState = eNone;
    _strName = "";
    _bSync = false;
    _dwSync = 2 * 60; //活动开启前 2分钟
   
}
bool CActivity::IsRun()
{
    return _eState == eBegin;
}

void CActivity::OnBegin()
{
   LOG_INF<<"Now:" << time(NULL)<<",Activity(ID="<<_dwActID<<") begin!"; 
   _eState = eBegin;
}

void CActivity::OnAlarm()
{
   LOG_INF<<"Now:" << time(NULL)<<",Activity(ID="<<_dwActID<<") alarm!"; 
   _eState = eAlarm;
}

void CActivity::OnEnd()
{
   LOG_INF<<"Now:" << time(NULL)<<",Activity(ID="<<_dwActID<<") end!"; 
   
   //清掉对象
   _eState = eEnd;
   g_ActivityMgr.DelAct(_dwActID,_byIndex); 
}

void CActivity::OnReBegin() 
{

   UINT32 dwNow = (UINT32)(time(NULL));
   if(_dwBegin < dwNow && dwNow < _dwEnd)
   {
       LOG_INF<<"Now:" << time(NULL)<<",Activity(ID="<<_dwActID<<") begin!"; 
       if(_bSync)
           OnSync();
       _eState = eBegin;
   }
}

void CActivity::Update2DB(EDataChange eUpdateType)
{
    SActivityOpt oInfo;
    oInfo.dwActID = _dwActID;
    oInfo.byIndex = _byIndex;
    oInfo.strName = _strName;
    oInfo.dwBegin = _dwBegin;
    oInfo.dwEnd = _dwEnd;
    oInfo.dwOptTime = time(NULL);
    g_Center2DBCommC.Send_SyncActivityCenterInfo(eUpdateType,oInfo);
}

void CActivity::OnSync()
{
    if(_bSync)
    {
        //TODO
        SActivityTime oTime;
        oTime.dwActID = _dwActID;
        oTime.dwAlarm = _dwAlarm;
        oTime.dwReady = _dwReady;
        oTime.dwBegin = _dwBegin;
        oTime.dwEnd = _dwEnd;
        UINT32 dwGameSvrID = CCenterConfig::Instance().GetSvrID();
        g_Game2CenterCommS.SendSvr_SyncActivityTime(&dwGameSvrID,1,oTime);
    }
    _eState = eSync;
}
void CActivity::OnReady()
{
    LOG_INF<<"Act OnReady";
    _eState = eReady;
}

void CActivity::UpdateState()
{
    switch(_eState)
    {
        case eNone:
            if(time(NULL) > _dwSync)
                OnSync();
            break;
        case eSync:
            if(time(NULL) > _dwAlarm)
                OnAlarm();
            break;
        case eAlarm:
            if(time(NULL) > _dwReady)
                OnReady();
            break;
        case eReady:
            if(time(NULL) > _dwBegin)
                OnBegin();
            break;
        case eBegin:
            if(time(NULL) > _dwEnd)
                OnEnd();
            break;
        case eEnd:
            _eState = eNone;
            break;
        default:
            break;
    }
}
