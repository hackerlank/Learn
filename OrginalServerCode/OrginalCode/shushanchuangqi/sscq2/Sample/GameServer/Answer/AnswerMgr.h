
#ifndef ANSWERMGR_H_
#define ANSWERMGR_H_

#include "Singleton.h"
#include "DayActivity.h"

class CAnswerMgr : public Singleton<CAnswerMgr>,public CDayActivity
{
public:
    CAnswerMgr();
    ~CAnswerMgr();

    virtual bool GMOpen();
    virtual bool OnAlarm();
    virtual void OnReady();
    virtual void OnBegin();
    virtual void OnReBegin();
    virtual void OnEnd();
    virtual void OnEvent(SActEventData&);

    virtual void UpdateState(time_t tNow);
    virtual void ResetState();
private:
};
#endif // WORLDBOSSMGR_H_


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

