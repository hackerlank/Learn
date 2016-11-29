#ifndef CENTERDATA_H__
#define CENTERDATA_H__
#include<deque>
#include "BeautyLogGS.h"
#include "Center2DBCommC.h"
using namespace NBeautyLogGS;
using namespace NCenter2DBComm;
typedef std::deque<SCenterData> TDequeCenterData;
union URoleInfo
{
    struct
    {
        UINT8  byColor;
        UINT8  bySex;
        UINT8  byCareer;
        UINT8  byLevel;
    } sRole;
    UINT32 dwRole;
};


class CCenterDataMgr
{
public:
    enum
    {
        MAX_BEAUTY_LOG_COUNT = 20,
    };
    CCenterDataMgr();
    void InitDB();
    void OnLoad(const TVecCenterData& vecCenterData);

    void OnBeautyLogLoad(const SCenterData& oCenterData);

    void OnGetBeautyLog(UINT64 dwUserID,TVecBeautyLog& vecBeautyLog);
    void OnAddBeautyLog(const SBeautyLog& oBeautyLog);
public:
    void Update2DB(const SCenterData& oCenterData,bool bDelete);
    UINT64 GenBeautyInstID();
private:
    TDequeCenterData _dequeBeautyLog;
    UINT64 _qwMaxBeautyInstID;
    bool _bLoading;
};

extern CCenterDataMgr g_CenterDataMgr;

#endif //CENTERDATA_H__




