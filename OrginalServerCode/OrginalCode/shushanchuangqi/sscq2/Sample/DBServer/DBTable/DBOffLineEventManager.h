#ifndef  DBTOTAL_OFFLINEEVENT_TABLE_H__
#define  DBTOTAL_OFFLINEEVENT_TABLE_H__
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
typedef function<void(TVecEventOffLine vecEventOffLine)> QueryOffEventFun;
class CDBOffLineEventManager 
{ 
    public:
        void AddOffLineEvent(UINT8 byServerType,const TVecUINT64& vecRoleID,const NRoleInfoDefine::SEventOffLine& sEventData);
        void DelOffLineEvent(UINT64 qwRoleID,const NRoleInfoDefine::TVecEventOffLine& vecEventType);
        void LoadOffLineEvent(UINT64 qwRoleID,QueryOffEventFun fun);
};
extern CDBOffLineEventManager g_CDBOffLineEventManager;
#endif

