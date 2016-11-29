// =====================================================================================
//
//       Filename:  DCWorker.cpp
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


#include "GlobalDefine.h"
#include "DCWorker.h"

using namespace DataCollector;

string g_strAppName = "appoperlog";

CDCWorker::CDCWorker():
    _bActive(false), _pLogger(NULL)
{}

CDCWorker::~CDCWorker()
{
    UnInit();
    if (_pLogger)
        delete _pLogger;
}

bool CDCWorker::Init()
{
    _pLogger = new (nothrow) CLogger();
    if (!_pLogger)
        return false;

    int iRet = _pLogger->init(g_strAppName);
    
    if (iRet)
    {
        LOG_CRI << "Init DCLogger FAILED! Return: " << iRet << ".";
        return false;
    }
    else
    {
        LOG_INF << "Init DCLogger SUCCESS!";
        _bActive = true;
        _cThread.Start(Process,this);
        return true;
    }
}

void CDCWorker::UnInit()
{
    Shutdown();
    _cThread.Join();
    Process(this);
    _bActive = false;
}

void CDCWorker::Process(CDCWorker * pThis)
{
    while(pThis->_bActive)
    {
        {
            CAutoLock<CSpinLock> cAutoLock(pThis->_cLock);
            if (!pThis->_vecDCLog.empty())
                pThis->_vecDCLogHandle.swap(pThis->_vecDCLog);
        }
        if (!pThis->_vecDCLogHandle.empty())
        {
            //LOG_INF << "pThis->_vecDCLogHandle.size() = " << pThis->_vecDCLogHandle.size() << ".";
            size_t szCount = pThis->_vecDCLogHandle.size();
            size_t szIndex = 0;
            while (szIndex < szCount)
            {
                string& strMsg = pThis->_vecDCLogHandle[szIndex];
                if (pThis->_pLogger)
                    pThis->_pLogger->write_baselog(LT_NORMAL, strMsg);
                //bool bRet = false;
                //if (pThis->_pLogger && !pThis->_pLogger->write_baselog(LT_NORMAL, strMsg))
                    //bRet = true;
                //LOG_INF << "DCLogger:" << szIndex << ":" << szCount << "-[" << strMsg << "] -> " << (bRet ? "true" : "false");
                ++szIndex;
            }
            pThis->_vecDCLogHandle.clear();
        }
        else
        {
            usleep(50000);
            continue;
        }
    }
}

void CDCWorker::Push(const string& strMsg)
{
    //LOG_INF << "Push DCLogger: " << strMsg;
    CAutoLock<CSpinLock> cAutoLock(_cLock);
    _vecDCLog.push_back(strMsg);
}

