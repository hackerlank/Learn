// =====================================================================================
//
//       Filename:  BattleReportMgr.h
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

#ifndef BATTLE_REPORT_MGR_H
#define BATTLE_REPORT_MGR_H

#include <Singleton.h>

#include "BattleReportOP.h"
namespace NBattle
{
class CBattleReportMgr : public Singleton<CBattleReportMgr>
{
    public:
        CBattleReportMgr(){}

        bool Init(const string& strReportDir);
        void AddReport(UINT64 qwBattleID, string& strReport, bool bSave);
        void GetReport( UINT64 qwBattleID , function<void(string*)> funcGetted);
        void SaveReport(UINT64 qwBattleID);
        void DeleteReport(UINT64 qwBattleID);
        bool ProcessResult();
        const string& GetReportDir() const;
    private:
        map<UINT64, string> m_mapBattleReport;

        CBattleReportOP m_cBattleReportOP;
        UINT8 _byIndex;
        string _strReportDir;
};

} // NBattle

#endif // #ifndef BATTLE_REPORT_MGR_H
