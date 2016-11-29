#ifndef  DBTOTAL_SHIPREPORT_TABLE_H__
#define  DBTOTAL_SHIPREPORT_TABLE_H__
#include "ShipProt.h"
using namespace NShipProt;
typedef function<void(TVecShipReport vecShipReport)> QueryShipReportFun;
class CDBShipReportManager 
{ 
    public:
        void AddShipReport(UINT64 qwRoleID,const NShipProt::ShipReport& sShipData);//给这个人增加一条记录
        void DelShipReport(UINT64 qwRoleID,UINT64 qwInsID);
        void LoadShipReport(UINT64 qwRoleID,QueryShipReportFun fun);
};
extern CDBShipReportManager g_CDBShipReportManager;
#endif

