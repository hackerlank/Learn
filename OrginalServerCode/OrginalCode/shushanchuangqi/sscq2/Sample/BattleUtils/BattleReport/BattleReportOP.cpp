// =====================================================================================
//
//       Filename:  BattleReportOP.cpp
//
//    Description:  战报操作相关类
//
//        Version:  1.0
//        Created:  06/16/2015 01:48:18 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "BattleReportMgr.h"
#include "BattleReportOP.h"
#include <stdarg.h>
#include <sys/stat.h>

#include "Directory.h"

namespace NBattle
{

CBattleReportOP::CBattleReportOP() : 
    m_bActive(false) 
{
}

CBattleReportOP::~CBattleReportOP()
{
    Shutdown();
    m_LoadThread.Join();

    for (auto it = m_listIn.begin(); it != m_listIn.end(); ++it)
    {
        delete *it;
    }
    m_listIn.clear();
    for (auto it = m_listResult.begin(); it != m_listResult.end(); ++it)
    {
        delete *it;
    }
    m_listResult.clear();
}

void  CBattleReportOP::Process(CBattleReportOP * pThis)
{
    while(pThis->m_bActive)
    {
        SBattleReportOPInfo* pInfo = pThis->PopLoadReportReq();
        if (pInfo)
        {
            pInfo->thread_op(pInfo);
            //LoadReport(pInfo);
           pThis->PushLoadReportResult(pInfo);
        }
        else
           sleep(1);
    }
}

void CBattleReportOP::Start()
{   
    m_bActive = true;
    m_LoadThread.Start(Process,this);
}

void CBattleReportOP::Shutdown()
{ 
    m_bActive = false; 
}

void CBattleReportOP::PushSaveReportReq( UINT64 qwBattleID, const string& strReport )
{
    SBattleReportOPInfo* pInfo = new SBattleReportOPInfo;
    if (!pInfo)
        return;
    pInfo->qwBattleID = qwBattleID;
    pInfo->strReport = strReport;
    pInfo->thread_op = bind(&CBattleReportOP::SaveReport, this, std::placeholders::_1);
    CAutoLock<CSpinLock> oAutoLock(m_oLock);
    m_listIn.push_back(pInfo);
}

void CBattleReportOP::PushLoadReportReq( UINT64 qwBattleID, function<void(bool, string&)> callback )
{
    if (!callback)
        return;

    SBattleReportOPInfo* pInfo = new SBattleReportOPInfo;
    if (!pInfo)
    {
        static string s;
        callback(false, s);
        return;
    }
    pInfo->qwBattleID = qwBattleID;
    pInfo->callback = callback;
    pInfo->thread_op = bind(&CBattleReportOP::LoadReport, this, std::placeholders::_1);
    CAutoLock<CSpinLock> oAutoLock(m_oLock);
    m_listIn.push_back(pInfo);
}

SBattleReportOPInfo* CBattleReportOP::PopLoadReportReq()
{
    CAutoLock<CSpinLock> oAutoLock(m_oLock);
    if(m_listIn.empty())
        return NULL;
    SBattleReportOPInfo* pInfo = m_listIn.front();
    m_listIn.pop_front();
    return pInfo;
}

void CBattleReportOP::PushLoadReportResult( SBattleReportOPInfo* pInfo )
{
    if (!pInfo)
        return;
    CAutoLock<CSpinLock> oAutoLock(m_oLock);
    m_listResult.push_back(pInfo);
}

SBattleReportOPInfo* CBattleReportOP::PopLoadReportResult()
{
    CAutoLock<CSpinLock> oAutoLock(m_oLock);
    if(m_listResult.empty())
        return NULL;
    SBattleReportOPInfo* pInfo = m_listResult.front();
    m_listResult.pop_front();
    return pInfo;
}

void CBattleReportOP::LoadReport( SBattleReportOPInfo* pInfo )
{
    if (!pInfo)
        return;
    UINT64 qwCounter = pInfo->qwBattleID;
    char path[1024];
    sprintf(path, "%s/%s%" I64_FMT "u/%" I64_FMT "u/%" I64_FMT "u.dat", "Report", CBattleReportMgr::Instance().GetReportDir().c_str(), qwCounter / 100000, (qwCounter / 1000) % 100, qwCounter);
    FILE * f = fopen(path, "rb");
    if(f == NULL)
    {
        pInfo->bSuc = false;
        return;
    }
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    string strReport;
    strReport.resize(size);
    fread(&strReport[0], 1, size, f);
    fclose(f);
    pInfo->strReport.swap(strReport);
    pInfo->bSuc = true;
    return;
}

void CBattleReportOP::SaveReport(SBattleReportOPInfo* pInfo)
{
    if (!pInfo)
        return;
    UINT64 qwCounter = pInfo->qwBattleID;
    char path[1024]={0}, path2[1024]={0};
    sprintf(path, "%s/%s%" I64_FMT "u/%" I64_FMT "u", "Report", CBattleReportMgr::Instance().GetReportDir().c_str(), qwCounter / 100000, (qwCounter / 1000) % 100);
    sprintf(path2, "%s/%" I64_FMT "u.dat", path, qwCounter);
    string strDir = path;
    CreateDirectory(strDir);
    FILE * f = fopen(path2, "wb");
    if(f == NULL)
        return;
    fwrite(pInfo->strReport.c_str(), 1, pInfo->strReport.size(), f);
    fclose(f);
}

bool CBattleReportOP::ProcessResult()
{
    SBattleReportOPInfo* pResult = NULL;
    bool bBusy = false;
    pResult = PopLoadReportResult();
    while(pResult)
    {
        bBusy = true;
        if(pResult->callback)
            pResult->callback(pResult->bSuc, pResult->strReport);
        delete pResult;
        pResult = PopLoadReportResult();
    }
    return bBusy;
}
} // namespace NBattle


#include "BattleReportOP.h"
