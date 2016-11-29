#include "EverydayRecharge.h"
#include "Tokenizer.h"
#include "UserMgr.h"
#include "IconAppearManager.h"
#include "GameServerSysMail.h"
#include "EveryDayRechargeCFG.h"
#include "ActivityIDProt.h"
static const UINT16 wRechargeIcon = 106;
CEveryDayRechargeMgr g_EveryDayRechargeMgr ;
CEveryDayRechargeMgr::CEveryDayRechargeMgr()
{
    _bGetDragon = false;
    _bOpen =false;
}
bool CEveryDayRechargeMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/EveryDayRecharge.xml";
    CEveryDayRechargeLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "Err Load " << strPath;
    }
    for(auto it = oLoader._vecData.begin();it != oLoader._vecData.end();++it)
    {
        SEveryDayRechargeCFG* pCfg = *it;
        AwardEveryDay sAward;
        sAward.wLimit = pCfg->_Limit;
        buf::Tokenizer tkDate(pCfg->_Time, '|');
        if(tkDate.size() != 3)
        {
            LOG_CRI << "Err Load " << strPath << " for time" << pCfg->_Time;
            return false;
        }
        UINT32 dwDate = atoi(tkDate[0].c_str())*10000+atoi(tkDate[1].c_str())*100 + atoi(tkDate[2].c_str());
        AwardEveryDay award;
        award.wLimit = pCfg->_Limit;
        buf::Tokenizer tkReward(pCfg->_Reward, '|'); 
        for(size_t pos = 0;pos != tkReward.size(); pos++)
        {
            buf::Tokenizer tkItem(tkReward[pos], ',');
            if(tkItem.size() != 2)
            {
                LOG_CRI << "Err Load " << strPath << " for Reward" <<pCfg->_Reward;
                return false;

            }
            SItemGenInfo sItem;
            sItem.wItemID = atoi(tkItem[0].c_str());
            sItem.dwCount = atoi(tkItem[1].c_str()); 
            award.vecItem.push_back(sItem);

        }
        if(award.vecItem.empty())
        {
            LOG_CRI << "Err Load " << strPath << " for Reward" <<pCfg->_Reward;
            return false;

        }
        _mapDayAward[dwDate] = award;

    }
    return true;

}

bool CEveryDayRechargeMgr::CheckSystemOpen()
{
    //龙珠活动结束
    if(!_bOpen)
        return false;
    //当日有奖励
    return GetAwardByDate() != NULL;
}

UINT32 CEveryDayRechargeMgr::GetDate()
{
    Time _Now;
    UINT32 dwDay = _Now.year()*10000 + _Now.month()*100 + _Now.day();
    return dwDay;
}

const AwardEveryDay* CEveryDayRechargeMgr::GetAwardByDate()
{
    auto it = _mapDayAward.find(GetDate());
    if(it == _mapDayAward.end())
    {
        return NULL;
    }
    return &(it->second);
}

void CEveryDayRechargeMgr::GetAward(CUser &rUser,NMiscProt::EEveryDayReChargeAward & eResult)
{
    if(!CheckSystemOpen())
    {
        eResult = NMiscProt::eEveryDayReChargeAward_NoAward;
        return ;
    }
    const AwardEveryDay* pAward = GetAwardByDate() ; 
    if(rUser.GetVars().GetVar(NVarDefine::ePlayerVarRechargeToday) < pAward->wLimit)
    {
        eResult = NMiscProt::eEveryDayReChargeAward_LowMoney;
        return ;
    }
    if(rUser.GetVars().GetVar(NVarDefine::ePlayerVarGetRechargeAward) > 0)
    {
        eResult = NMiscProt::eEveryDayReChargeAward_HasDone;
        return ;
    }
    //发送邮件
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_RECHARGEAWARD;
    TVecUINT64 vecTargets;
    vecTargets.push_back(rUser.GetUserID());
    GameServerSysMail::SendSysMail(SEND_RECHARGEAWARD,TITLE_RECHARGEAWARD,stBody,vecTargets,const_cast<TVecItemGenInfo*>(&(pAward->vecItem)));

    CIconAppearMgr::Instance().CloseActionToClient(rUser,wRechargeIcon);
    rUser.GetVars().AddVar(NVarDefine::ePlayerVarGetRechargeAward,1);

    eResult = NMiscProt::eEveryDayReChargeAward_Sucess;

}

void CEveryDayRechargeMgr::CheckIconIsOpen(CUser &rUser,bool bZero)
{
    if(!bZero)
    {
        if(!CheckSystemOpen())
            return ;
        if(rUser.GetVars().GetVar(NVarDefine::ePlayerVarGetRechargeAward) > 0)
        {
            return ;
        }
        TVecUINT16 vecIcon;
        vecIcon.push_back(wRechargeIcon);
        CIconAppearMgr::Instance().OpenActionToClient(rUser,vecIcon);
    }
    else
    {
        bool bOpen = false;
        do{
            if(!CheckSystemOpen())
            {

                break;
            }
            if(rUser.GetVars().GetVar(NVarDefine::ePlayerVarGetRechargeAward) > 0)
            {
                break;
            }
            bOpen =true;
        }while(0);
        if(bOpen)
        {
            TVecUINT16 vecIcon;
            vecIcon.push_back(wRechargeIcon);
            CIconAppearMgr::Instance().OpenActionToClient(rUser,vecIcon);
        }
        else
        {
            CIconAppearMgr::Instance().CloseActionToClient(rUser,wRechargeIcon);
        }



    }

}

void CEveryDayRechargeMgr::SetDragonState(bool bOpen)
{

    if(!_bGetDragon)
    {
        _bGetDragon = true;
        //首次开启
        if(!bOpen)
        {
            _bOpen = true;
        }

    }
    else
    {
        if(_bOpen) //原先开启，现在关闭
        {
            _bOpen = !bOpen;

            if(bOpen)
            {
                //所有关闭
                CIconAppearMgr::Instance().CloseActionToClientForAll(wRechargeIcon);

            }
        }
        else//原先关闭，现在开启
        {
            _bOpen = !bOpen;
            if(!bOpen)
            {
                //所有人开启
                TMapID2Usr mapID2Usr;
                CUserMgr::GetOnlineUser(mapID2Usr);
                for(auto it = mapID2Usr.begin();it != mapID2Usr.end();++it)
                {
                    if(it->second)
                    {
                        CheckIconIsOpen(*it->second,false);
                    }
                }
            }
        }

    }

}

