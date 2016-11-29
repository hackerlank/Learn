#include "TrumpRank.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivity.h"
#include "RankMgr.h"

bool CTrumpRank::SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    if(!CRankMgr::Instance().SendMail(eRTTrump,wHigh,wLow,vecItem,wMailID,wContentID))
    {
        LOG_INF << " SendMail Error";
        return false;
    }
    return true;
}

    
bool CTrumpRank::GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    if(!CRankMgr::Instance().GetPlayerInfoForTrump(wActID,bType,qwPlayerID,sPlayer,GetState()))
    {
        LOG_INF << "GetPlayerInfo Error";
        return false;
    }
    return true;
}


void CTrumpRank::OnEnd()
{
    CWonderActivity::OnEnd();
    UINT16 wActID = GetActID();
    if(GetActType() == eWActType_RANKTRUMP)
    {
        if(!OnMail())
        {
            LOG_INF <<"WonderActivity ID = " <<_wActID <<" Send Mail Error";
        }
        CRankMgr::Instance().SaveRoleInfoForTrump(wActID);
    }

}

void CTrumpRank::OnRetain()
{
    CWonderActivity::OnRetain();
    UINT16 wActID = GetActID();
    LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
    g_Center2DBCommC.Send_DelActPrizeData(wActID);

}

