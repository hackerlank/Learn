// =====================================================================================
//
//       Filename:  DCWorker.h
//
//    Description:  DCLogger工作线程
//
//        Version:  1.0
//        Created:  10/21/2014 10:07:24 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef DC_WORKER_H
#define DC_WORKER_H

#include <string>
#include <vector>
#include <Thread.h>

#include "dcapi_cpp.h"
#include "Singleton.h"

using namespace DataCollector;


using namespace std;

#include "Lock.h"

class CDCWorker: public Singleton<CDCWorker>
{
    public:
        CDCWorker();
        virtual ~CDCWorker();
        bool Init();
        void UnInit();

    public:
        static void Process(CDCWorker * pThis);
        void Start();
        virtual void Shutdown(){ _bActive = false; }

        void Push(const string& strMsg);

    private:
        bool                _bActive;
        vector<string>      _vecDCLog;
        vector<string>      _vecDCLogHandle;
        CLogger*            _pLogger;
        CThread             _cThread;
        CSpinLock           _cLock;
};

#define DC() CDCWorker::Instance()


#endif // #ifndef DC_WORKER_H

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
