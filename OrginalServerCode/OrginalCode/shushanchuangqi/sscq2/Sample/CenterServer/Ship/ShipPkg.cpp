#include "ShipPkg.h"
#include "Protocols.h"
#include "User.h"
#include "ShipManager.h"
#include "VarDefine.h"
void CShipPkg::SetSelfData(const PlayerSelfShipData &rData)
{
    _stSelfData = rData;

}

void CShipPkg::SetShipReportList(const TVecShipReport& rvecReport)
{
    _vecReport = rvecReport;
    CheckDelReport();
}

void CShipPkg::AddReport(const ShipReport & rReport)
{
    _vecReport.push_back(rReport);
    /*放到manager里面实现
      g_Center2DBCommC.Send_AddShipReport(_rUser.GetUserID(),rReport);

      _rUser.SendPkg(g_ShipProtS.BuildPkg_UpDateShipReportAdd(rReport));
      */

}
bool CShipPkg::CheckDelReport()
{
    set<UINT64> setDelReport;
    UINT32 dwNow = time(NULL);
    for(auto pos = _vecReport.begin();pos != _vecReport.end();)
    {
        ShipReport &rPort = *pos;
        if(!Time::sameDay(rPort.dwFinishTimer,dwNow) && dwNow > rPort.dwFinishTimer)
        {
            setDelReport.insert(rPort.qwInsID);
            pos = _vecReport.erase(pos);

        }
        else
        {
            pos++;
        }
    }
    for(auto iter = setDelReport.begin();iter != setDelReport.end();iter++)
    {
        g_Center2DBCommC.Send_DelShipReport(_rUser.GetUserID(),*iter);

    }
    return !setDelReport.empty();

}

void CShipPkg::GetShipReportList(TVecShipReport& rvecReport)
{
    rvecReport = _vecReport;
}

void CShipPkg::Update2DBSelfData()
{
    string strData;
    COutArchive iar(strData);
    iar << _stSelfData;
    g_Center2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), NRoleInfoDefine::eTypeShip, eOpUpdate, strData);
}


void CShipPkg::SendShipReportList()
{
    TVecShipReportForClient vecReport;
    for(auto it = _vecReport.begin() ; it != _vecReport.end();it++)
    {
        ShipReport &rData = *it;
        ShipReportForClient  rClient;
        g_ShipManager.CreateClientShipReport(rClient,rData);
        vecReport.push_back(rClient);
    }
    _rUser.SendPkg(g_ShipProtS.BuildPkg_SendRePort(vecReport));
}

PlayerSelfShipData& CShipPkg::GetSelfData()
{
    return _stSelfData;
}
void  CShipPkg::Send2ClientSelfData()
{
    PlayerSelfShipData& rData = GetSelfData();
    PlayerSelfView SelfView;
    SelfView.stData = rData;
    SelfView.dwRobTimes = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerShipRobTimes);//今日抢劫次数
    SelfView.byDefenseTimes = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerShipDefenseTimes); //护送次数
    SelfView.dwOpenShipTimes  = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerShipOpenTimes);
    SelfView.dwReFluseTimes  = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerShipReFluseTimes);
    SelfView.dwBuyRobTimes  = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerBuyRoBShipTimesToday);
    SelfView.dwBuyOpenShipTimesToday  = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerBuyOpenShipTimesToday);
    SelfView.dwBuyRlushShipTimesToday  = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerBuyReflushShipTimesToday);
    SelfView.dwFreezBattleTime = _rUser.GetCenterVar().GetVar(NVarDefine::ePlayerFreezShipTimer);
    SelfView.qwSelfShip = g_ShipManager.GetShipByOwer(_rUser.GetUserID());
    SelfView.qwDefenseShip = g_ShipManager.GetShipByDefense(_rUser.GetUserID());
    g_PHPProtS.GetNameByID(rData.qwInviteDefense,SelfView.strInviteDefenseName);
    if(SelfView.qwSelfShip >0 )
    {
        RunShip * pShip = g_ShipManager.GetShipByID(SelfView.qwSelfShip);
        if(pShip)
        {
            SelfView.dwBeginTimer = pShip->sRunShip.dwBeginTimer;
            SelfView.dwEndTimer = pShip->sRunShip.dwEndTimer;

        }
    }
    _rUser.SendPkg(g_ShipProtS.BuildPkg_SendView(SelfView));



}
