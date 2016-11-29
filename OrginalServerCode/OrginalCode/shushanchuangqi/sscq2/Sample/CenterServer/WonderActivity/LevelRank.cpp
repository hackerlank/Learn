#include "LevelRank.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivity.h"
#include "RankMgr.h"

bool CLevelRank::SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    UINT32 wHighTmp = wHigh;
    
    if(_setRank.count(wHigh))
    {
        LOG_CRI << "SendMail two.";
        return false;
    }
    
    LOG_CRI << "SendMail wHigh = "<<wHigh<<" | wLow = " <<wLow;
    if(!CRankMgr::Instance().SendMail(eRTLevel,wHigh,wLow,vecItem,wMailID,wContentID))
    {
        LOG_INF << " SendMail Error";
        return false;
    }
    _setRank.insert(wHighTmp);
    return true;
}

    
bool CLevelRank::GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer)
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
    if(!CRankMgr::Instance().GetPlayerInfoForLevel(wActID,bType,qwPlayerID,sPlayer,GetState()))
    {
        LOG_INF << "GetPlayerInfo Error";
        return false;
    }
    return true;
}


void CLevelRank::OnEnd()
{
    CWonderActivity::OnEnd();
    UINT16 wActID = GetActID();
    if(GetActType() == eWActType_RANKLEVEL)
    {
        if(!OnMail())
        {
            LOG_INF <<"WonderActivity ID = " <<_wActID <<" Send Mail Error";
        }
        CRankMgr::Instance().SaveRoleInfoForLevel(wActID);
    }
}

void CLevelRank::OnRetain()
{
    CWonderActivity::OnRetain();
    _setRank.clear();
    UINT16 wActID = GetActID();
    LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
    //g_Center2DBCommC.Send_DelActPrizeData(wActID);
    g_Center2DBCommC.Send_DelActRetainData(wActID);

}

