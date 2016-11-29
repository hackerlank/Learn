#ifndef SHIPPKG_H__
#define SHIPPKG_H__
class CUser;
#include "ShipProt.h"
using namespace NShipProt;
const UINT32 dwAgreeTime = 60;
class CShipPkg
{
    public:
        CShipPkg(CUser &rUser):_rUser(rUser){}
        void SetSelfData(const PlayerSelfShipData &rData);
        void SetShipReportList(const TVecShipReport& rvecReport);
        void AddReport(const ShipReport & rReport);
        void GetShipReportList(TVecShipReport& rvecReport);
        bool CheckDelReport();
        void SendShipReportList();  
        PlayerSelfShipData& GetSelfData();
        void Update2DBSelfData();
        void Send2ClientSelfData();
    private:
        CUser& _rUser;
        TVecShipReport _vecReport;
        PlayerSelfShipData _stSelfData;

};
#endif
