#include "stdafx.h"
#include "Protocols.h"
#include "Lottery.h"
#include "UserMgr.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "Tokenizer.h"
#include "Random.h"

CLottery g_Lottery;

static void ParseString(TVecItemGenInfo& vecItem,string& strInfo)
{
    if("" == strInfo)
    {
        LOG_INF <<" LotteryPrize err.";
        return;
    }
    Tokenizer tk(strInfo,"|");
    for(size_t i=0; i<tk.size(); ++i)
    {
        Tokenizer tk1(tk[i],",");
        SItemGenInfo oItem;
        oItem.wItemID = atoi(tk1[0].c_str());
        oItem.dwCount = atoi(tk1[1].c_str());
        oItem.eBindType = eBindGet;
        vecItem.push_back(oItem);
    }
}
/////////////////////////////
CLottery::CLottery() :
    dwCount(0)
    ,dwTotalNum(5)
    ,dwSelfNum(5)
{
    _vecTotalInfo.clear();
    _mapID2VecID.clear();
}

CLottery::~CLottery() 
{
    vecNum.clear();
}

bool CLottery::Init()
{
    if(!LoadConfig())
    {
        LOG_CRI << " Load Lottery Config Err.";
        return false;
    }
    InitLotteryNum();
    return true;
}

bool CLottery::LoadConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/Lottery.xml";
    CLotteryLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oLottery LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SLotteryCFG* p = oLoader._vecData[i];
        if(p)
        {
            SLotteryCFGExPtr pEx(new SLotteryCFGEx);
            pEx->wLotteryID = p->_ID;
            pEx->byCount = p->_Count;
            ParseString(pEx->vecItems,p->_Content);
            _mapID2Config[pEx->wLotteryID] = pEx;
        }
    }
    return true;
}

void CLottery::InitLotteryNum()
{
    for(auto& it : _mapID2Config)
    {
        SLotteryCFGExPtr pEx = it.second;
        if(pEx)
        {
            for(size_t i=0; i<pEx->byCount; ++i)
                vecNum.push_back(pEx->wLotteryID);
        }
    }
}

SLotteryCFGExPtr CLottery::GetConfig(UINT16 wLotteryID)
{
    auto it = _mapID2Config.find(wLotteryID);
    if(it != _mapID2Config.end())
        return it->second;
    return NULL;
}

ELotteryRes CLottery::Draw(CUser& rUser,UINT16 &wLotteryID)
{
    if(!rUser.CanSubMoney(EMONEY_LUCKYCOUPON,1))
    {
        LOG_INF << "qwRoleID" << rUser.GetRoleID() << " dwLotteryCoupon = 0";
        return eLotteryRes_LackMoney;
    }
    
    wLotteryID = CRandom::RandVecElem(vecNum);
    SLotteryCFGExPtr pConfig = GetConfig(wLotteryID);
    if(!pConfig)
    {
        LOG_INF<<"wLotteryID ="<<wLotteryID<<" Config Err.";
        return eLotteryRes_Error;
    }
    if(!pConfig->vecItems.empty())
    {
        CPack& oPack = rUser.GetPack();
        if(!oPack.CanAddItem(pConfig->vecItems))
        {
            return eLotteryRes_PackFul;
        }
        else
        {
            DrawRet(rUser,pConfig);
        }
    }
    return eLotteryRes_Sucess;
}

void CLottery::DrawRet(CUser& rUser,SLotteryCFGExPtr pConfig)
{
    if(!pConfig)
        return;
    CPack& oPack = rUser.GetPack();
    oPack.AddItem(pConfig->vecItems,NLogDataDefine::ItemFrom_Lottery,true,false);
    rUser.SubMoney(EMONEY_LUCKYCOUPON,1,NLogDataDefine::ItemTo_Lottery);

    //处理登记信息 
    {
       SLotteryInfo oInfo;
       oInfo.strName = rUser.GetUserName();
       oInfo.dwLotteryID = pConfig->wLotteryID; 
       _vecTotalInfo.push_back(oInfo);
       
       TVecUINT32& oVec = _mapID2VecID[rUser.GetRoleID()];
       oVec.push_back(pConfig->wLotteryID);
    }
    //同步一次
    //OnSync(rUser,dwTotalNum,dwSelfNum);
}

void CLottery::SendLottery(CUser& rUser,UINT32 dwTotal,UINT32 dwSelf)
{
    dwTotalNum = dwTotal;
    dwSelfNum  = dwSelf;
   
    OnSync(rUser,dwTotal,dwSelf);
}

void CLottery::OnSync(CUser& rUser,UINT32 dwTotal /* = 10 */, UINT32 dwSelf/* = 10 */)
{
    TVecLotteryInfo vecTotalInfo;
    TVecLotteryInfo vecSelfInfo;
    for(auto it=_vecTotalInfo.rbegin(); it!=_vecTotalInfo.rend(); ++it)
    {
        if(!dwTotal)
            break;

        SLotteryInfo oInfo;
        oInfo.dwLotteryID = it->dwLotteryID;
        oInfo.strName = it->strName;
        
        vecTotalInfo.push_back(oInfo);
        
        --dwTotal;
    }

    GetLotterInfo(rUser,vecSelfInfo,dwSelf);
    UINT32 dwLottery = rUser.GetMoney(EMONEY_LUCKYCOUPON);
    string strPkg = g_MiscProtS.BuildPkg_SyncLotteryInfo(dwLottery,vecTotalInfo,vecSelfInfo);
    
    rUser.SendPkg(strPkg);    
}

void CLottery::GetLotterInfo(CUser& rUser,TVecLotteryInfo& vecInfo,UINT32 dwSelf)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    auto it = _mapID2VecID.find(qwRoleID);
    if(it == _mapID2VecID.end())
        return;
    string strName = rUser.GetUserName();
    TVecUINT32& vecID = it->second;
    for(auto oIt=vecID.rbegin(); oIt!=vecID.rend(); ++oIt)
    {
        if(!dwSelf)
            break;

        SLotteryInfo sInfo;
        sInfo.strName = strName;
        sInfo.dwLotteryID = *oIt;
        vecInfo.push_back(sInfo);
        --dwSelf;
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

