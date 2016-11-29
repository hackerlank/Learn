// =====================================================================================
//
//       Filename:  BattleReportMgr.cpp
//
//    Description:  战报管理器
//
//        Version:  1.0
//        Created:  06/16/2015 01:46:53 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "BattleReportMgr.h"

namespace NBattle
{

bool CBattleReportMgr::Init(const string& strReportDir)
{
    _strReportDir = strReportDir;
    m_cBattleReportOP.Start();
    return true;
}

void CBattleReportMgr::AddReport( UINT64 qwBattleID, string& strReport, bool bSave )
{
    if (!qwBattleID)
        return;
    //m_mapBattleReport[qwBattleID] = strReport;
    if (bSave)
        m_cBattleReportOP.PushSaveReportReq(qwBattleID, strReport);
}

void CBattleReportMgr::GetReport( UINT64 qwBattleID , function<void(string*)> funcGetted)
{
    map<UINT64, string>::iterator it = m_mapBattleReport.find(qwBattleID);
    if (it != m_mapBattleReport.end())
        return funcGetted(&it->second);

    m_cBattleReportOP.PushLoadReportReq(qwBattleID, 
            [this, qwBattleID, funcGetted](bool bSuc, string& strReport)
            {
                if (!bSuc)
                {
                    funcGetted(NULL);
                    return;
                }
                string& str = m_mapBattleReport[qwBattleID];
                str.swap(strReport);
                funcGetted(&str);
            });
}

void CBattleReportMgr::SaveReport(UINT64 qwBattleID)
{
    GetReport(qwBattleID, 
            [qwBattleID, this](string* pReport)mutable
            {
                if (pReport)
                    this->m_cBattleReportOP.PushSaveReportReq(qwBattleID, *pReport);
            });
}

void CBattleReportMgr::DeleteReport(UINT64 qwBattleID)
{
    map<UINT64, string>::iterator it = m_mapBattleReport.find(qwBattleID);
    if (it != m_mapBattleReport.end())
        m_mapBattleReport.erase(it);
}

bool CBattleReportMgr::ProcessResult()
{
    return m_cBattleReportOP.ProcessResult();
}

const string& CBattleReportMgr::GetReportDir() const
{
    return _strReportDir;
}

} // namespace NBattle

