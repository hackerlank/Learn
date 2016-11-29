
#include "stdafx.h"
#include "Protocols.h"
#include "GodMonster.h"
#include "GodMonsterMgr.h"
#include "UserMgr.h"
#include "User.h"

void CLimitPrize::Update2DB(UINT64 qwRoleID,UINT16 wNum)
{
    //LOG_CRI << " LimitPrize WriteToDB.";
    SLimitPrize2DB oLimit;
    oLimit.qwRoleID  = qwRoleID;
    oLimit.wPrizeID = _wID;
    oLimit.wNum = wNum;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        LOG_CRI<<"pUser NULL";
        return;
    }
    //g_Center2DBCommC.BuildPkg_SyncLimitPrizeInfo(eOpAdd,oLimit));
    g_Center2DBCommC.Send_SyncLimitPrizeInfo(eOpAdd,oLimit);
    //LOG_CRI<<"Send Data";
}

////////////////////////////////////////
bool CLimitPrizeMgr::LoadFromDB()
{
	g_Center2DBCommC.Send_GetLimitPrizeInfo(
           [this](UINT8 byRet_, //0为成功，1为失败，2为超时
			const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
            ){
           //LOG_CRI << "byRet_ = " <<byRet_;
             if(byRet_)
             {
                LOG_INF << " LoadLimitPrizeInfo Err.";
                return;
             }
             Load(vecLimitPrize);
           });
    return true;
    
}

void CLimitPrizeMgr::Load(const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize)
{
    for(auto it=vecLimitPrize.begin(); it!=vecLimitPrize.end(); ++it)
    {
        UINT16 wNum = 0;
        SKey oKey(it->qwRoleID,it->wPrizeID);
        LOG_INF << " LoadLimitPrize:" << it->qwRoleID<<",wID =" <<it->wPrizeID;
        auto oIt = setCache.find(oKey);
        if(oIt != setCache.end())
        {
            SKey o = static_cast<SKey>(*oIt);
            wNum = o.GetNum();
            setCache.erase(oIt);
        }
        wNum += it->wNum;
        oKey.Add(wNum);
        setCache.insert(oKey);
    }
    for(auto& it : setCache)
    {
        GodMonsterUserPtr pUser = NULL;
        g_GodMonsterMgr.GetMonsterUser(it._qwRoleID,pUser);
        if(!pUser)
        {
            LOG_INF<<"pUser Null.";
            continue;
        }
        LimitPrizePtr pLimit(new CLimitPrize(it._wPrizeID));
        pLimit->SetCurNum(it._wNum);
        pUser->AddLimitPrize(pLimit);
    }
}

///////////////////////////////////////////////
CGodMonsterUser::CGodMonsterUser(UINT64 qwUserID):
    _qwRoleID(qwUserID),
    _qwGuildID(0),
    _dwFruit(1000),
    _dwDevote(0),
    _bTaking(false),
    _bBuying(false)
{
    _dwTotalScore = 0;
}

CGodMonsterUser::~CGodMonsterUser()
{

}

EMonsterResult CGodMonsterUser::TakePrize(EMonsterPrizeType eType)
{
    EMonsterResult eResult = EMonsterResult_Err;
    GodMonsterCFGPtr pConfig = NULL;
    UINT8 byIndex = eType;
    pConfig = g_GodMonsterMgr.GetConfig(eGodMonsterDayPkg,byIndex);
    if(!pConfig)
       return eResult;
    UINT32 dwMaxDayScore = pConfig->dwDayScore;
    UINT32 dwCurDayScore = GetDayScore();
    if(dwCurDayScore < dwMaxDayScore)
    {
        LOG_INF <<" Devote Lack.";
        return EMonsterResult_Devote;
    }
    TVecUserItem vecUserItem; 
    for(auto it=pConfig->vecItems.begin(); it!=pConfig->vecItems.end(); ++it)
    {
        SUserItem oItem;
        oItem.dwTypeID = it->wItemID;
        oItem.dwCount = it->dwCount;
        vecUserItem.push_back(oItem);
    }
    UINT64 qwRoleID = GetRoleID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return eResult;
    UINT32 dwServerID = pUser->GetGameSvrID();
    if(_bTaking)
    {
        LOG_INF<<" qwRoleID" << _qwRoleID<<" is taking!";
        return eResult;
    }
    _bTaking = true;
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemFrom_GodMonster,vecUserItem,[qwRoleID,eType,this](UINT8 byRet_, UINT8 byError)
                                {
                                    ResetTakeing();//去掉领奖标志
                                    if(byRet_ || byError)
                                    {   
                                        return;
                                    }
                                    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                                    if(pUser)
                                    {
                                        CCenterVar& rVar = pUser->GetCenterVar();
                                        UINT32 wResult = rVar.GetVar(NVarDefine::ePlayerVarDayPackage);
                                        wResult = wResult | (1 << eType);
                                        rVar.SetVar(NVarDefine::ePlayerVarDayPackage,wResult);
                                        LOG_INF << "qwRoleID("<<qwRoleID<<") TakePrize Suc.";
                                    }

                                });
    return EMonsterResult_suc;
}

bool CGodMonsterUser::IsTake(EMonsterPrizeType eType)
{
    bool bTake = false;
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(!pUser)
       return false;
    CCenterVar &rVar = pUser->GetCenterVar();
    UINT32 wResult = rVar.GetVar(ePlayerVarDayPackage);
    bTake = wResult & (1 << eType) ? false : true;
    LOG_INF<<"qwRoleID" << _qwRoleID<<",wResult="<<wResult<<",bTake="<<bTake;
    return bTake;
}

EMonsterResult CGodMonsterUser::OneFeed(UINT32 dwFruit /* = 1*/)
{
    EMonsterResult eResult = EMonsterResult_Err;
    if(dwFruit > _dwFruit)
        return eResult;
    _dwFruit -= dwFruit; 
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(!pUser)
    {
        LOG_INF <<"pUser null.";
        return eResult;
    }
    CCenterVar &rVar = pUser->GetCenterVar();
    UINT64 qwRet = rVar.GetVar(ePlayerVarFruit);
    qwRet += dwFruit;
    //设置当天喂养朱果数
    rVar.SetVar(ePlayerVarFruit,qwRet);
    //设置玩家总积分
    _dwTotalScore += dwFruit * BASESCORE;
    //设置在当前帮派中的贡献积分
    _dwDevote += dwFruit * BASESCORE;
    //LOG_INF <<"qwRoleID=" <<_qwRoleID<<" feed Monster: " <<dwFruit<<",玩家总积分："<<_dwTotalScore <<",在帮派中的积分："<< _dwDevote;
    
    Update2DB();
    return EMonsterResult_suc;
}

void CGodMonsterUser::Update2DB()
{
    SGuildUser2DB oUser;
    oUser.qwRoleID = _qwRoleID;
    oUser.qwGuildID = _qwGuildID;
    oUser.dwFruit = _dwFruit;
    oUser.dwScore = _dwDevote; 
    oUser.dwTotalScore = _dwTotalScore; 
    //LOG_INF<<"Update2DB: 玩家ID:" << _qwRoleID <<",帮会："<<_qwGuildID<<",朱果："<<_dwFruit<<",贡献:"<<_dwDevote<<",总积分："<< _dwTotalScore;
    g_Center2DBCommC.Send_SyncMonsterUserInfo(eOpUpdate,oUser);
}

void CGodMonsterUser::LoadFromDB(const SGuildUser2DB& sUser)
{
    _qwGuildID = sUser.qwGuildID;
    _dwFruit = sUser.dwFruit;
    _dwDevote = sUser.dwScore;
    _dwTotalScore = sUser.dwTotalScore;
}

UINT32 CGodMonsterUser::GetTotalScore()
{
    return _dwTotalScore;
}

UINT32 CGodMonsterUser::GetDayScore()
{
    UINT32 dwRet = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(!pUser)
    {
        LOG_INF <<"pUser null.";
        return dwRet;
    }
    CCenterVar &rVar = pUser->GetCenterVar();
    dwRet = rVar.GetVar(ePlayerVarFruit);
    return dwRet * BASESCORE;
}

void CGodMonsterUser::GetPrizeInfo(TVecMonsterPrize& vecInfo)
{
    if(!IsGuildUser())
    {
        LOG_INF << " qwRoleID=" << GetRoleID() << " not in Guild.";
        return;
    }
    UINT16 wResult = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(!pUser)
    {
        LOG_INF <<"pUser null.";
        return ;
    }
    GodMonsterCFGPtr pConfig = NULL;
    CCenterVar &rVar = pUser->GetCenterVar();
    wResult = rVar.GetVar(ePlayerVarDayPackage);
    for(UINT8 byI = 1; byI!=EMonsterPrize_End; ++byI)
    {
        SMonsterPrize oPrize;
        oPrize.eType = static_cast<EMonsterPrizeType>(byI);
        if(wResult & (1 << byI))
            oPrize.byType = 2;
        else
        {
            pConfig = g_GodMonsterMgr.GetConfig(eGodMonsterDayPkg,byI);
            if(pConfig)
            {
                if(GetDayScore() < pConfig->dwDayScore)
                    oPrize.byType = 0;
                else 
                    oPrize.byType = 1;
                LOG_INF<<"DayScore="<<GetDayScore()<<",ID="<<byI<<" ConfigScore="<<pConfig->dwDayScore;
            }
        }
        LOG_INF<<"qwRoleID="<<pUser->GetRoleID() << ",DayPkgID="<<byI << ",State="<<oPrize.byType;
        vecInfo.push_back(oPrize);
    }
}

EMonsterResult CGodMonsterUser::Buy(UINT16 wIndex,UINT16 wCount)
{
    GodMonsterLimitPrizeCFGPtr pEx = NULL;
    pEx = g_GodMonsterMgr.GetLimitPrizeConfig(wIndex);
    if(!pEx)
    {
        LOG_INF << " pEx Null.";
        return EMonsterResult_not;
    }
    UINT16 wMax = pEx->byNum;
    LimitPrizePtr pLimit = GetLimitPrize(wIndex);
    UINT16 wTmp = 0;
    if(pLimit)
    {
        wTmp = pLimit->GetCurNum();
    }
    if(wTmp + wCount > wMax)
    {
        LOG_INF << "ID=" << wIndex << " Lack.";
        return EMonsterResult_Num;
    }

    GodMonsterPtr pMonster = g_GodMonsterMgr.GetMonster(_qwGuildID);
    if(!pMonster)
    {
        LOG_INF << " pMonster Err.";
        return EMonsterResult_Err;
    }
    UINT8 byPeroid = pMonster->GetPeroid();
    if(byPeroid < pEx->byCond)
    {
        LOG_INF << " Level Lack";
        return EMonsterResult_Level;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(!pUser)
    {
        LOG_INF << " pUser Null.";
        return EMonsterResult_Err;
    }
    UINT32 dwGold = pUser->GetGold();
    UINT32 dwNeed = wCount * pEx->wCurPrice;
    if(dwGold < dwNeed)
    {
        LOG_INF << "gold Lack.";
        return EMonsterResult_lack;
    }
    //pLimit->SetCurPrize(pEx->wCurPrice);
    UINT16 wCurPrice = pEx->wCurPrice;
    TVecUserItem vecUserItem;
    for(auto it=pEx->vecItems.begin(); it!=pEx->vecItems.end(); ++it)
    {
        SUserItem oItem;
        oItem.dwTypeID = it->wItemID;
        oItem.dwCount = it->dwCount;
        vecUserItem.push_back(oItem);
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    if(_bBuying)
    {
        LOG_INF<<"qwRoleID=" << _qwRoleID<<" is buying.";
        return EMonsterResult_Err;
    }
    _bBuying = true;
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,_qwRoleID,NLogDataDefine::ItemFrom_GodMonster,vecUserItem,[this,wIndex,wCount,dwServerID,wCurPrice](UINT8 byRet_, UINT8 byError)
                                {
                                    ResetBuying();
                                    if(byRet_ || byError)
                                    { 
                                       LOG_INF << " BuyErr.";
                                        return;
                                    }   
                                    OnSuc(wIndex,wCount,dwServerID,wCurPrice);
                                });

    return EMonsterResult_suc;
}

void CGodMonsterUser::OnSuc(UINT16 wIndex,UINT16 wCount,UINT32 dwServerID,UINT16 wCurPrice)
{
    UINT32 dwMoney = 0;
    LimitPrizePtr pLimit = NULL;
    pLimit = GetLimitPrize(wIndex);
    if(pLimit)
    {
        pLimit->AddCurNum(wCount);
        dwMoney = wCount * wCurPrice;
    }else
    {
        pLimit = LimitPrizePtr(new CLimitPrize(wIndex));
        pLimit->SetCurPrize(wCurPrice);
        pLimit->SetCurNum(wCount);
        AddLimitPrize(pLimit);
    }
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,_qwRoleID,NLogDataDefine::ItemTo_GodMonster,
                                NProtoCommon::eGoldCoin,dwMoney,[this,wIndex,wCount,dwMoney](UINT8 byRet_,UINT8 byRet)
                                {
                                       if(byRet_ || byRet)
                                       {
                                              LOG_INF <<"qwRoleID="<<GetRoleID()<<" ,buy Index="<<wIndex<<" dwCount=" << wCount << ",dwMoney=" << dwMoney<<" err.";
                                              return;
                                       }
                                       LOG_INF << " Reduce Gold Suc.";
                                });
    pLimit->Update2DB(_qwRoleID,wCount);
}

void CGodMonsterUser::AddLimitPrize(LimitPrizePtr pLimit)
{
    if(!pLimit)
    {
        LOG_INF << " pLimit null.";
        return;
    }
    UINT16 wID = pLimit->GetID();
    auto it = _mapID2Prize.find(wID);
    if(it == _mapID2Prize.end())
        _mapID2Prize.insert(make_pair(wID,pLimit));
}

LimitPrizePtr CGodMonsterUser::GetLimitPrize(UINT16 wIndex)
{
    auto it = _mapID2Prize.find(wIndex);
    if(it != _mapID2Prize.end())
        return it->second;
    return NULL;
}

void CGodMonsterUser::BuyFruit(UINT32 dwCount)
{

}

void CGodMonsterUser::GetLimitInfo(TVecLimitPrize &vecLimitPrize)
{ 
    UINT16 wID = 0;
    for(auto& it : vecLimitPrize)
    {
        wID = it.wPrizeID;
        LimitPrizePtr pLimit = GetLimitPrize(wID);
        if(pLimit)
            it.wCurNum = pLimit->GetCurNum();
        LOG_INF<<"礼包ID："<<wID <<",已经购买："<<it.wCurNum<<",最大值："<<it.wMaxNum;
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

