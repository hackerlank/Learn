#include "PointRank.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivity.h"
#include "RankMgr.h"

bool CPointRank::SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    UINT32 dwHighTmp = wHigh;
    
    if(_setRank.count(wHigh))
    {
        LOG_CRI << "SendMail two.";
        return false;
    }
    
    if(!CRankMgr::Instance().SendMail(eRTBattlePoint,wHigh,wLow,vecItem,wMailID,wContentID))
    {
        LOG_INF << " SendMail Error";
        return false;
    }
    _setRank.insert(dwHighTmp);
    return true;
}

    
bool CPointRank::GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer)
{
    UINT16 wActID = GetActID();
    if(GetState() == eWActState_Init)
    {
       LOG_INF << " Wonderful Activity wActID = " << wActID << "  need 1Min to start Suc.";
       return false;
    }
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    if(!CRankMgr::Instance().GetPlayerInfo(wActID,bType,qwPlayerID,wType,sPlayer,GetState()))
    {
        LOG_INF << "GetPlayerInfo Error";
        return false;
    }
    return true;
}


void CPointRank::OnEnd()
{
    CWonderActivity::OnEnd();
    UINT16 wActID = GetActID();
    if(GetActType() == eWActType_RANKPOINT)
    {
        if(!OnMail())
        {
            LOG_INF <<"WonderActivity ID = " <<_wActID <<" Send Mail Error";
        }
        CRankMgr::Instance().SaveRoleInfoForAct(wActID);
    }

}

void CPointRank::OnRetain()
{
    CWonderActivity::OnRetain();
    _setRank.clear();
    UINT16 wActID = GetActID();
    LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
    //g_Center2DBCommC.Send_DelActPrizeData(wActID);
    g_Center2DBCommC.Send_DelActRetainData(wActID);

}
