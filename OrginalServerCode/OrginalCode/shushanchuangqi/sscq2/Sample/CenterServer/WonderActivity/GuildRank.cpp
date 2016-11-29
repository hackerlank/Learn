#include "GuildRank.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivity.h"
#include "RankMgr.h"

bool CGuildRank::SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    UINT32 dwTmp = wHigh; 
    if(_setRank.count(wHigh))
    {
        LOG_CRI << "SendMail two.";
        return false;
    }
    
    if(!CRankMgr::Instance().SendMailForGuild(wHigh,wLow,vecItem,wMailID,wContentID))
    {
        LOG_INF << " SendMail Error";
        return false;
    }
    _setRank.insert(dwTmp);
    return true;
}

    
bool CGuildRank::GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF << "wActID = " <<wActID;
        return false;
    }
    if(!CRankMgr::Instance().GetPlayerInfoForGuild(wActID,bType,qwPlayerID,sPlayer,GetState()))
    {
        LOG_INF << "GetPlayerInfo Error";
        return false;
    }
    return true;
}


void CGuildRank::OnEnd()
{
    CWonderActivity::OnEnd();
    UINT16 wActID = GetActID();
    if(GetActType() == eWActType_RANKGUILD)
    {
        CRankMgr::Instance().SaveRoleInfoForGuild(wActID);
        
        if(!OnMail())
        {
            LOG_INF <<"WonderActivity ID = " <<_wActID <<" Send Mail Error";
        }
    }

}

void CGuildRank::OnRetain()
{
    CWonderActivity::OnRetain();
    _setRank.clear();
    UINT16 wActID = GetActID();
    LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
    //g_Center2DBCommC.Send_DelActPrizeData(wActID);
    g_Center2DBCommC.Send_DelActRetainData(wActID);

}

