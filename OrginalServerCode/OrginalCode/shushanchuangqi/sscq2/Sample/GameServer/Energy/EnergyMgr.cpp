#include "stdafx.h"
#include "Protocols.h"
#include "Player.h"
#include "User.h"
#include "EnergyMgr.h"
#include "SysMsgDefine.h"
#include "MiscProt.h"
#include "EnergyPriceCFG.h"
#include "VIPMgr.h"
#include "MiscProtS.h"
#include "AutoStoreMgr.h"
using namespace NMiscProt;

TVecEnergyPriceCFGPtr CEnergyMgr::_vecEnergyPriceCFGPtr;

CEnergyMgr::CEnergyMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
}
bool CEnergyMgr::CEnergyMgr_Init()
{

    string strPath = Config._strConfigDir + "Conf/Table/EnergyPrice.xml";
    CEnergyPriceLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "CEnergyMgrLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    _vecEnergyPriceCFGPtr.clear();
    _vecEnergyPriceCFGPtr.resize(oLoader._vecData.size());

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SEnergyPriceCFGPtr pItem(new SEnergyPriceCFG);
        *pItem = *(oLoader._vecData[i]);
        _vecEnergyPriceCFGPtr[i]=pItem;
    }

    return true;

}

void CEnergyMgr::OnFirstLogin()
{

    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    rCGameVar.SetVar(NVarDefine::ePlayerVarActionRegain1,1,SParamConfig::dwEnergyRegainTime1);
    rCGameVar.SetVar(NVarDefine::ePlayerVarActionRegain2,1,SParamConfig::dwEnergyRegainTime2);
    rCGameVar.SetVar(NVarDefine::ePlayerVarActionAdd,time(NULL));
}

//初始化
void CEnergyMgr::OnLoad()
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwMaxFlag = rCGameVar.GetVar(NVarDefine::ePlayerVarMaxAction);
    if(!dwMaxFlag)
    {
        rCGameVar.SetVar(NVarDefine::ePlayerVarMaxAction,1);
        rUser.AddMoney(EMONEY_ACTION,SParamConfig::byEnergyMax,NLogDataDefine::ItemFrom_CharInit,false);
    }

    if(rCGameVar.GetVar(NVarDefine::ePlayerVarActionBuffer) != 0)
    {
        TVecUINT32 vecParam;
        _rPlayer.AddBuff(SParamConfig::wEnergyRegainBuffId);
        LOG_DBG<<"CEnergyMgr::OnLoad:"<<SParamConfig::wEnergyRegainBuffId;

    }

    UINT32 dwRegainTime = rCGameVar.GetVar(NVarDefine::ePlayerVarActionAdd); 
    if(0 == dwRegainTime)
    {
        rCGameVar.SetVar(NVarDefine::ePlayerVarActionAdd,time(NULL));
        LOG_INF<<"CEnergyMgr::OnLoad init qwUserID "<<_rPlayer.GetUserID();
    }
    else
    {
    }

    LOG_INF<<"Energy load init qwUserID:"<<_rPlayer.GetUserID()<<" EMONEY_ACTION:"<<rUser.GetMoney(EMONEY_ACTION);

}


UINT32 CEnergyMgr::BuyAction()
{
    LOG_INF<<"CEnergyMgr::BuyAction";
    CUser& rUser = _rPlayer.GetUser();

    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwBuyCnt = rCGameVar.GetVar(NVarDefine::ePlayerVarBuyActionCnt);

    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(NULL == pVIPLvlCfg)
    {
        LOG_INF<<"eBuyActionRet_VIPCFGError";
        return eBuyActionRet_VIPCFGError;
    }

    if(dwBuyCnt >= pVIPLvlCfg->_DailyEnergyBoughtTimes)
    {
        LOG_INF<<"eBuyActionRet_CountLimit "<<dwBuyCnt<<"|"<<pVIPLvlCfg->_DailyEnergyBoughtTimes;
        rUser.SendSysMsg(eMsgExchangeShopCountLimit);
        return eBuyActionRet_CountLimit;
    }

    UINT32 dwPrice = GetBuyPrice();
    bool bUseGold = false;
    if(!rUser.CanSubMoney(EMONEY_COUPON,dwPrice))
    {
        bUseGold = true;
        if(!rUser.CanSubMoney(EMONEY_GOLD,dwPrice))
        {
            LOG_INF<<"eBuyActionRet_MoneyLimit";
            rUser.SendSysMsg(eMsgGoldErr);
            return eBuyActionRet_MoneyLimit;
        }
    }

    //不检查上限
    UINT32 dwAction = rUser.GetMoney(EMONEY_ACTION);
    if(dwAction >= SParamConfig::byEnergyMax)
    {
        //LOG_INF<<"eBuyActionRet_MaxAction";
        //return eBuyActionRet_MaxAction;
    }
    if(bUseGold)
    {
        rUser.SubMoney(EMONEY_GOLD,dwPrice,NLogDataDefine::ItemTo_BuyAction);
    }
    else
    {
        rUser.SubMoney(EMONEY_COUPON,dwPrice,NLogDataDefine::ItemTo_BuyAction);
    }


    //体力增加
    AddAction(SParamConfig::dwEnergyBoughtValue,false);

    //购买次数+1
    rCGameVar.SetVar(NVarDefine::ePlayerVarBuyActionCnt,dwBuyCnt+1);

    return eBuyActionRet_Sucess;
}

UINT32 CEnergyMgr::GetBuyActionCount()
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    return rCGameVar.GetVar(NVarDefine::ePlayerVarBuyActionCnt);
}

//获取购买价格 
UINT32 CEnergyMgr::GetBuyPrice()
{
    if(_vecEnergyPriceCFGPtr.size()<1)
    {
        LOG_CRI<<"_vecEnergyPriceCFGPtr empty!!!";
        return -1;
    }

    UINT32 dwBuyCnt = GetBuyActionCount();
    if(dwBuyCnt >= _vecEnergyPriceCFGPtr.size())
    {
        dwBuyCnt = _vecEnergyPriceCFGPtr.size()-1;
    }
    LOG_INF<<"GetBuyPrice:"<<_vecEnergyPriceCFGPtr[dwBuyCnt]->_Price<<"|"<<dwBuyCnt;

    return _vecEnergyPriceCFGPtr[dwBuyCnt]->_Price;

}

//12点18点刷新体力buffer
void CEnergyMgr::TimerCheck(UINT32 dwNow)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwRegain1 = rCGameVar.GetVar(NVarDefine::ePlayerVarActionRegain1);
    if(0 == dwRegain1)
    {
        //rCGameVar.SetVar(NVarDefine::ePlayerVarActionRegain1,1,SParamConfig::dwEnergyRegainTime1);
        //_rPlayer.AddBuff(SParamConfig::wEnergyRegainBuffId);
        //rCGameVar.SetVar(NVarDefine::ePlayerVarActionBuffer,SParamConfig::byEnergyRegainValue1);
        //SetTakeFlag(1);
        //NotifyActionBuffer();
        //LOG_DBG<<"ADD 1 wEnergyRegainBuffId";
    }

    UINT32 dwRegain2 = rCGameVar.GetVar(NVarDefine::ePlayerVarActionRegain2);
    if(0 == dwRegain2)
    {
        //rCGameVar.SetVar(NVarDefine::ePlayerVarActionRegain2,1,SParamConfig::dwEnergyRegainTime2);
        //_rPlayer.AddBuff(SParamConfig::wEnergyRegainBuffId);
        //rCGameVar.SetVar(NVarDefine::ePlayerVarActionBuffer,SParamConfig::byEnergyRegainValue1);
        //SetTakeFlag(1);
        //NotifyActionBuffer();
        //LOG_DBG<<"ADD 2 wEnergyRegainBuffId";
    }

    if(_rPlayer.GetActionManager().IsInitSweep())
    {
        return;
    }

    UINT32 dwRegainTime = rCGameVar.GetVar(NVarDefine::ePlayerVarActionAdd);
    if(0 == dwRegainTime)
    {
        rCGameVar.SetVar(NVarDefine::ePlayerVarActionAdd,time(NULL));
        LOG_CRI<<"fatal impossible!! qwUserID:"<<_rPlayer.GetUserID();
    }
    else
    {
        if(time(NULL)>=dwRegainTime)
        {
            if(0 == SParamConfig::wEnergyNormalRegainTime)
            {
                LOG_CRI<<"0 == SParamConfig::wEnergyNormalRegainTime";
                return;
            }
            UINT32 dwLastTime = time(NULL) - dwRegainTime;
            UINT32 dwCount = dwLastTime/SParamConfig::wEnergyNormalRegainTime;
            if(dwCount)
            {
                AddAction(SParamConfig::byEnergyRegainValue*dwCount);
                rCGameVar.SetVar(NVarDefine::ePlayerVarActionAdd,dwRegainTime+SParamConfig::wEnergyNormalRegainTime*dwCount);
                LOG_INF<< rUser.GetUserID() <<"  Energ LOAD ADD:"<<SParamConfig::byEnergyRegainValue*dwCount<<"|"<<dwCount;
            }
        }
        else  
        {

            LOG_CRI << "Linux date time change?" << dwRegainTime << ", " << time(NULL);
            //不考虑修改系统时间问题
            rCGameVar.SetVar(NVarDefine::ePlayerVarActionAdd,time(NULL));
        }
    }

}

void CEnergyMgr::AddAction(UINT32 dwAddAction,bool bCheckLimit)
{
    CUser& rUser = _rPlayer.GetUser();
    if(!bCheckLimit)
    {
        rUser.AddMoney(EMONEY_ACTION,dwAddAction,NLogDataDefine::ItemFrom_EnergyBuy);  
        LOG_INF<<"EMONEY_ACTION:"<<rUser.GetMoney(EMONEY_ACTION);
        return;
    }

    UINT32 dwOldAction = rUser.GetMoney(EMONEY_ACTION);
    if(dwOldAction >= SParamConfig::byEnergyMax)
    {
        LOG_INF<<"AddAction FULL qwUserID:"<<_rPlayer.GetUserID()<<"dwOldAction:"<<dwOldAction<<" SParamConfig::byEnergyMax:"<<SParamConfig::byEnergyMax;
        return;
    }

    UINT32 dwNewAction = dwOldAction + dwAddAction;

    UINT32 dwAddReal = dwAddAction;
    if(dwNewAction > SParamConfig::byEnergyMax)
    {
        dwAddReal = SParamConfig::byEnergyMax - dwOldAction;
    }

    rUser.AddMoney(EMONEY_ACTION,dwAddReal,NLogDataDefine::ItemFrom_EnergyBuff);
    LOG_INF<<"AddAction qwUserID:"<<_rPlayer.GetUserID()<<"EMONEY_ACTION:"<<rUser.GetMoney(EMONEY_ACTION);

}

bool CEnergyMgr::CanSubAction(UINT32 dwAddAction)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwBufferValue = rCGameVar.GetVar(NVarDefine::ePlayerVarActionBuffer);
    UINT32 dwOldAction = rUser.GetMoney(EMONEY_ACTION);
    return dwAddAction<=dwBufferValue+dwOldAction;
}

bool CEnergyMgr::SubAction(UINT32 dwAddAction,bool bNotify/*=true*/)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwBufferValue = rCGameVar.GetVar(NVarDefine::ePlayerVarActionBuffer);
    UINT32 dwOldAction = rUser.GetMoney(EMONEY_ACTION);
    if(dwAddAction>dwBufferValue+dwOldAction)
    {
        return false;
    }

    if(0 == dwBufferValue)
    {
        rUser.SubMoney(EMONEY_ACTION,dwAddAction,NLogDataDefine::ItemTo_ConsumeAction);
        return true;
    }

    if(dwBufferValue>dwAddAction)
    {
        dwBufferValue -= dwAddAction;
        rCGameVar.SetVar(NVarDefine::ePlayerVarActionBuffer,dwBufferValue);
        NotifyActionBuffer();
    }
    else
    {
        rCGameVar.SetVar(NVarDefine::ePlayerVarActionBuffer,0);
        rUser.SubMoney(EMONEY_ACTION,dwAddAction-dwBufferValue,NLogDataDefine::ItemTo_ConsumeAction);
        _rPlayer.RemoveBuff(SParamConfig::wEnergyRegainBuffId);
        NotifyActionBuffer();
    }

    return true;
}

void CEnergyMgr::NotifyActionBuffer()
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwBufferValue = rCGameVar.GetVar(NVarDefine::ePlayerVarActionBuffer);
    rUser.SendPkg(g_MiscProtS.BuildPkg_GetActionBuffNotify(dwBufferValue,GetTakeFlag()));
    LOG_DBG<<"NotifyActionBuffer:"<<dwBufferValue<<" uID:"<<rUser.GetUserID();

}

void CEnergyMgr::OnTakeActionBuff()
{
    if(!CEnergyActivity::Instance().IsInProcess())
    {
        LOG_CRI<<"not in  activity time!!!";
        _rPlayer.SendSysMsg(eMsgHuoDongNotOpen);
        return;
    }
    
    if(CEnergyActivity::Instance().IsHasTakedPrize(GetTakeFlag()))
    {
        LOG_CRI<<"hase take buffer!!!:"<<_rPlayer.GetRoleID();
        _rPlayer.SendSysMsg(eMsgSevenDayTakePrized);
        return;
    }
    CUser& rUser = _rPlayer.GetUser();
    //CGameVar& rCGameVar = rUser.GetVars();
    //_rPlayer.AddBuff(SParamConfig::wEnergyRegainBuffId);
    //rCGameVar.SetVar(NVarDefine::ePlayerVarActionBuffer,SParamConfig::byEnergyRegainValue1);
    rUser.AddMoney(EMONEY_ACTION,SParamConfig::byEnergyRegainValue1,NLogDataDefine::ItemFrom_EnergyBuff);
    SetTakeFlag(time(NULL));
    NotifyActionBuffer();

    TVecINT32 vecParam;
    vecParam.push_back(1);
    _rPlayer.OnEvent(eEventType_GetEnergy,vecParam);
 
}
void CEnergyMgr::SetTakeFlag(UINT32 dwFlag)
{
    CAutoStoreMgrPtr pAutoStoreMgr=_rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Action_TakeFlag,0,dwFlag);
    }
}

UINT32 CEnergyMgr::GetTakeFlag()
{
    CAutoStoreMgrPtr pAutoStoreMgr=_rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return (pAutoStoreMgr->GetValue(eAutoStore_Action_TakeFlag,0));
    }

    return 0;
}

