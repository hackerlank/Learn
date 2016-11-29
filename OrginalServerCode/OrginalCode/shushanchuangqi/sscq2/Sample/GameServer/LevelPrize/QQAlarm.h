#ifndef QQALARM_H__ 
#define QQALARM_H__
#include "stdafx.h"
#include "UserMgr.h"
#include "Parameter.h"
#include "VarDefine.h"
#include "LevelPrize.h"
#include "LevelPrizeSvrS.h"
using namespace NLevelPrize;
class CQQAlarmMgr 
{
    public:
        CQQAlarmMgr()  
        { };
        virtual ~CQQAlarmMgr(){};
        ELevelActStatus TakePrize(CUser &rUser,UINT16 wActID);
        void  GetState(CUser &rUser,UINT16 wActID);
    protected:
    private:
        std::set<UINT64> _setUser; //临时数据
};
#endif
extern CQQAlarmMgr g_QQAlarmMgr; 
