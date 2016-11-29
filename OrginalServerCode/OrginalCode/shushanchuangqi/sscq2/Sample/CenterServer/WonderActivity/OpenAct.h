#ifndef OPENACT_H__ 
#define OPENACT_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class COpenAct : public CWonderActivity
{
    public:
        COpenAct(UINT16 wType) : CWonderActivity(wType) {}
        virtual ~COpenAct(){};
        void     OnEnd();
        void     OnBegin();
        void     OpenIcon(bool bNotify);
};
#endif
