// =====================================================================================
//
//       Filename:  BattleReportOP.h
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

#ifndef BATTLE_REPORT_OP_H
#define BATTLE_REPORT_OP_H

#include <Thread.h>
#include <ObjPool.h>

//#include <string>
#include <list>
//#include <map>
//#include <memory>

//#include "Linux.h"
#include "Lock.h"

using namespace std;

namespace NBattle
{
struct SBattleReportOPInfo;

class CBattleReportOP
{
    public:
        CBattleReportOP();
        virtual ~CBattleReportOP();

        static void Process(CBattleReportOP * pThis);
        void Start();
        virtual void Shutdown();

        void PushSaveReportReq(UINT64 qwBattleID, const string& strReport);
        void PushLoadReportReq( UINT64 qwBattleID, function<void(bool, string&)> callback );
        SBattleReportOPInfo* PopLoadReportReq();

        void PushLoadReportResult(SBattleReportOPInfo* pInfo);
        SBattleReportOPInfo* PopLoadReportResult();

        void LoadReport(SBattleReportOPInfo* pInfo);
        void SaveReport(SBattleReportOPInfo* pInfo);

        bool ProcessResult();
    protected:
        CThread m_LoadThread;
        bool m_bActive;
        list<SBattleReportOPInfo*> m_listIn;
        list<SBattleReportOPInfo*> m_listResult;
        CSpinLock m_oLock;
};

struct SBattleReportOPInfo : CPoolObj<SBattleReportOPInfo>
{
        UINT64 qwBattleID;
        bool bSuc;
        string strReport;
        function<void(SBattleReportOPInfo*)> thread_op;
        function<void(bool, string&)> callback;
        SBattleReportOPInfo():qwBattleID(0),bSuc(false),callback(nullptr){}
};

} // NBattle

#endif // #ifndef BATTLE_REPORT_OP_H

