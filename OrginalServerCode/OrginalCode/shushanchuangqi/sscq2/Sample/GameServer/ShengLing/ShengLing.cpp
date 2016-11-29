#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "ShengLingMgr.h"
#include "VIPMgr.h"
#include "MonsterMgr.h"
#include "TimerPriceMgr.h"
#include "Battle.h"
#include "GUIDMgr.h"
#include "HeroFighter.h"
#include "SysMsgDefine.h"
#include <algorithm>
#define ERROR 255
const static UINT8 MAXGRID = 40;
const static UINT8 MAXMONTER = 6;
// 下一次遥骰子时间
const static UINT8 NEXTDRAWDICE = 4;
const static UINT8 MONSTERNUM1 = 4;
const static UINT8 MONSTERNUM2 = 6;
const static UINT8 MONSTERNUM3 = 6;

/////////////////////////////////////
CShengLing::CShengLing(CPlayer &rPlayer)
    : _rPlayer(rPlayer)
{
    _bLog = false;
    _bTest = false;
    _bNextDice = true;
    _wPassword = 6666;
    _bLeave = true;
    _eState = eShengLingNone;
    _qwLastDrawDice = time(NULL);
    MAXLEVEL = SParamConfig::wRichMaxLevel;
    if(MAXLEVEL == 0)
    {
        LOG_CRI <<"ShengLing maxLevel = 0,set default maxlevel = 13";
        MAXLEVEL = 13;
    }
    for(size_t j=1; j<=MAXLEVEL; ++j)
    {
        TVecGrid vecGrid;
        for(size_t i=1; i<=MAXGRID; ++i)
        {
            SGrid oGrid;
            oGrid.byLevel = j;
            oGrid.byIndex = i;
            vecGrid.push_back(oGrid);
        }
        
        if(!_mapID2VecGridInfo.insert(make_pair(j,vecGrid)).second)
        {
            LOG_INF<<"_mapID2VecGridInfo insert Err.";
        }
    }
}

CShengLing::~CShengLing()
{
    _mapID2VecGridInfo.clear();
}

//策划需求，每个人一生只有一次免费的遥控骰子
bool CShengLing::CheckControlDiceSended()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return false;
    CGameVar &rVar = pUser->GetVars();
    return rVar.GetVar(NVarDefine::ePlayerVarControlDiceSended) ? true : false; 
}

void CShengLing::SetControlDiceSended(bool bFlag)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    CGameVar &rVar = pUser->GetVars();
    if(bFlag)
        rVar.SetVar(NVarDefine::ePlayerVarControlDiceSended,1); 
    else
        rVar.SetVar(NVarDefine::ePlayerVarControlDiceSended,0); 
}

void CShengLing::OnOpen(UINT8 &byUseEnter,UINT8 &byBuyEnter,UINT8 &byBuyEnterToday,bool &bContinue)
{
    byUseEnter = GetUseEnter();
    byBuyEnter = GetBuyEnter();
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    CGameVar& rVar = pUser->GetVars();
    byBuyEnterToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyEnterTimes); 
    bContinue = rVar.GetVar(NVarDefine::ePlayerVarCheckContinue) ? true : false;
    if(_bLog)
        LOG_INF<<"byUseEnter="<<byUseEnter<<",byBuyEnter="<<byBuyEnter<<",bContinue = " << bContinue;
}
void CShengLing::SendPrizeInfo(TVecItemGenInfo &vecItem)
{
    if(!vecItem.empty())
        _rPlayer.SendPkg(g_ShengLingProtS.BuildPkg_GetPrizeInfo(vecItem));
    //记录玩家获得的奖励 
    UpdatePrize2DB(eOpAdd,vecItem);
    if(_bLog)
    {
        LOG_INF<<"============================PRIZEITEM BEGIN=========================";
        LOG_INF<<"Time("<<time(NULL)<<") qwRoleID="<<_rPlayer.GetRoleID()<<" Recv PrizeItem detail : ";
        for(auto it : vecItem)
            LOG_INF<<"ItemID="<<it.wItemID<<",Count="<<it.dwCount;
        LOG_INF<<"============================PRIZEITEM END=========================";
    }
}

//很坑,还要检测数据
bool CShengLing::CheckVarAndDB()
{
    UINT8 byLevel = GetCurLevel();
    UINT8 byIndex = GetCurIndex();
    SGrid *pGrid = GetGrid(byLevel,byIndex);
    if(!pGrid)
    {
        LOG_INF<<"pGrid("<<byLevel<<","<<byIndex<<") null.";
        return false;
    }
    //小游戏不做检测
    if(pGrid->eGridType == EGridType_Motu || pGrid->eGridType == EGridType_Zadan || pGrid->eGridType == EGridType_Pintu)
        return true;
    if(pGrid->bFinished == false)
    {
        SetCurIndex(1);
        SetPreIndex(1);
    }
    return true;
}

//进入圣陵
EShengLingResult CShengLing::OnEnter(SShengLingInfo &rInfo)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return EShengLingResultError;
    CGameVar& rVar = pUser->GetVars();
    bool bEverEnter = rVar.GetVar(NVarDefine::ePlayerVarCheckContinue) ? true : false;
    do
    {
        if(bEverEnter)
            break;  
        if(!CheckEnter())
        {
            LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Lack Enter.";
            return EShengLingResultEnterLack;
        }
    }while(0);
    
    //数据检测
    /*
    if(!CheckVarAndDB())
        LOG_INF<<"ShengLing Var and DB diff.";
    */
    UINT8 byFirst = rVar.GetVar(NVarDefine::ePlayerVarFirstEnterShengLing);
    rInfo.byFirst = byFirst;
    if(byFirst == 0)
        rVar.SetVar(NVarDefine::ePlayerVarFirstEnterShengLing,1);
    if(GetCurLevel() == 0 && GetCurIndex() == 0)
        SetStep(SParamConfig::wRichCrushTime);
    rInfo.qwRoleID = _rPlayer.GetRoleID();
    rInfo.byLevel = GetCurLevel();
    if(rInfo.byLevel == 0)
    {
        rInfo.byLevel = 1;
        SetCurLevel(rInfo.byLevel);
        SetPreLevel(rInfo.byLevel);
    }
    rInfo.byIndex = GetCurIndex();
    if(rInfo.byIndex == 0)
    {
        rInfo.byIndex = 1;
        SetCurIndex(1);
        SetPreIndex(1);
        SetDir(true);
    }
    rInfo.byDir = GetDir();
    rInfo.byBuyLife = GetBuyLife();
    rInfo.byUseLife = GetUseLife();
    rInfo.byStep = GetStep();
    rInfo.byScore = GetScore();
    rInfo.byBit = GetPrizeBit();
    rInfo.wPassword = _wPassword;
    if(GetCurLevel() > MAXLEVEL)
    {
        LOG_INF<<"GetCurLevel() > 13";
        return EShengLingResultError;
    }
    TVecGrid *pvecGrid = GetAllGridByLevel(GetCurLevel());
    //没有找到或者需要更新
    if(!pvecGrid || CheckReflush(*pvecGrid))
    {
        if(!pvecGrid)
        {
            LOG_CRI <<" pvecGrid null.byLevel = " << GetCurLevel();
        }
        LOG_CRI<<"Need Random Grid.Level="<<GetCurLevel()<<",GridNum="<<pvecGrid->size();
        if(!RandAllGrid())
        {
            LOG_INF<<"RandAllGrid Err.";
            return EShengLingResultError;
        }
        //数据更新，重置玩家的位置
        {
            rInfo.byIndex = 1;
            SetCurIndex(rInfo.byIndex);
            SetPreIndex(rInfo.byIndex);
        }
    }

    rInfo.vecGrid.insert(rInfo.vecGrid.begin(),pvecGrid->begin(),pvecGrid->end());
    if(!GetCardInfo(rInfo.vecCard))
    {
        LOG_INF<<"GetCardInfo Err.";
        return EShengLingResultError;
    }
    //如果曾经进来过但是没有死，则不减少进入次数
    if(!bEverEnter) 
        //减少进入次数
        SubEnterNum(1);
    
    rInfo.byBuyLifeToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyLifeTimes); 
    GetPrizeInfo(rInfo.vecItem);
    _bLeave = false;
    //设置进入标志
    rVar.SetVar(NVarDefine::ePlayerVarCheckContinue,1);
    _eState = eShengLingIn; 
    /*
    if(_bLog)
    {
        for(auto it : rInfo.vecGrid)
        {
            LOG_CRI <<"byIndex="<<it.byIndex<<",byLevel="<<it.byLevel<<",GridType="<<it.eGridType<<",wNoteID="<<it.wNoteID<<",bFinish="<<it.bFinished<<",bRandom="<<it.bRandom; 
        }
    }
    */
    return EShengLingResultSuc;
}

bool CShengLing::CheckReflush(TVecGrid &vecGrid)
{
    if(vecGrid.size() != MAXGRID)
        return true;
    SGrid& rGrid = vecGrid.at(MAXGRID - 1);
    if(rGrid.eGridType == EGridType_Go && rGrid.bFinished == true)
    {
        LOG_INF<<"The Level finished.";
        return true;
    }
    
    SGrid& rInitGrid = vecGrid.at(0);
    if(rInitGrid.bFinished == false && rGrid.bFinished == false)
    {
        LOG_INF<<" player not in this level. byLevel="<<GetCurLevel();
        return true;
    }
    return false;
}

//摇骰子
EShengLingResult CShengLing::OnDrawDice(UINT8 &byNum,SPlayerInfo &sInfo,bool bControlDice,UINT64 &qwBattleID)
{
    if(_bLeave)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Leave.";
        return EShengLingResultError;
    }
    if(!CheckLife())
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Lack Life.";
        return EShengLingResultLifeLack;
    }
    if(_rPlayer.GetUserPtr()->GetPack().GetEmptyCount() <= SParamConfig::wRichRequirePack)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Pack Lack.";
        _rPlayer.SendSysMsg(eShengLingPackFul);
        return EShengLingResultPackFul;
    }
    SGrid *pGrid = GetGrid(GetCurLevel(),GetCurIndex());
    if(!pGrid || pGrid->bFinished == false)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Not Finish this Grid.";
        return EShengLingResultNotFinish;
    }
    if(!_bNextDice /* || ((time(NULL) - _qwLastDrawDice) < NEXTDRAWDICE) */)
    {
        LOG_INF<<"DrawDice too much!";
        return EShengLingResultError;
    }
    _qwLastDrawDice = time(NULL);
    
    if(!bControlDice)
        byNum = CRandom::RandInt(1,6);
    bool bNext;
    if(!ProcessDice(byNum,qwBattleID,bNext))
    {
        LOG_INF<<"ProcessDice Error,Dice("<<byNum<<").";
   
        _bNextDice = true;
        return EShengLingResultError;
    }
    //查看是否播放特效
    CheckPlayEffect();
    
    sInfo.qwRoleID = _rPlayer.GetRoleID();
    sInfo.byCurLevel = GetCurLevel();
    sInfo.byCurIndex = GetCurIndex();
    sInfo.byPreLevel = GetPreLevel();
    sInfo.byPreIndex = GetPreIndex();
    sInfo.byBuy = GetBuyLife();
    sInfo.byUse = GetUseLife();
    sInfo.byNext = (UINT8)bNext;
    if(bNext)
    {
        TVecGrid *pvecGrid = GetAllGridByLevel(GetCurLevel());
        if(pvecGrid)
            sInfo.vecGrid.insert(sInfo.vecGrid.begin(),pvecGrid->begin(),pvecGrid->end());
    }
    if(_bLog)
    {
        LOG_INF << "qwBattleID=" << qwBattleID;
        LOG_INF<<"====================================PLAYERINFO BEGIN===========================";
        LOG_INF<<"qwRoleID="<<sInfo.qwRoleID<<",byCurLevel="<<sInfo.byCurLevel<<",byCurIndex="<<sInfo.byCurIndex<<",byPreLevel="<<sInfo.byPreLevel<<",byPreIndex="<<sInfo.byPreIndex<<",byUseLife="<<sInfo.byUse<<",byBuy="<<sInfo.byBuy;
        LOG_INF<<"====================================PLAYERINFO END===========================";
    }
    _bNextDice = true;

    TVecINT32 vecParam;
    vecParam.push_back(pGrid->eGridType);
    vecParam.push_back(GetCurIndex());
    vecParam.push_back(GetCurLevel());
    _rPlayer.OnEvent(eEventType_ShenglingPlay,vecParam);
    if(bControlDice)
    {
        _rPlayer.OnEvent(eEventType_ShenglingControl,vecParam);
    }

    return EShengLingResultSuc;
}

//使用卡片
EShengLingResult CShengLing::OnUseCard(ECardType eCardType,UINT8 byNum,SCard &sCard,SPlayerInfo &rInfo,UINT64 &qwBattleID)
{
    if(_bLeave)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Leave.";
        return EShengLingResultError;
    }
    if(!CheckLife())
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Lack Life.";
        return EShengLingResultLifeLack;
    }
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return EShengLingResultError;
    CGameVar &rVar = pUser->GetVars();
   if(eCardType == ECardType_ControlDice)
   {
       if(byNum <= 0 || byNum > 6)
           return EShengLingResultError;
       if(!CheckControlDice())
       {
           LOG_INF<<"Lack ControlDice.";
           return EShengLingResultControlDiceLack;
       }
       OnDrawDice(byNum,rInfo,true,qwBattleID);
       //if(eResult == EShengLingResultSuc)
       SubControlNum(1); 
       sCard.eCardType = ECardType_ControlDice;
       sCard.byUse = GetUseControlDice();
       sCard.byBuy = GetBuyControlDice();
       sCard.byBuyForToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyControlDiceTimes);

   }else if(eCardType == ECardType_TurnDice)
   {
       if(GetCurIndex() == 1)
       {
           LOG_INF<<"Index=1,Not use TrunCard.";
           return EShengLingResultError;
       }
       if(!CheckTurnDice())
       {
           LOG_INF<<"Lack TurnDice.";
           return EShengLingResultTurnDiceLack;
       }
       SubTurnNum(1);
       //改变方向
       if(GetDir())
           SetDir(false);
       else
           SetDir(true);
       sCard.eCardType = ECardType_TurnDice;
       sCard.byUse = GetUseTurnDice();
       sCard.byBuy = GetBuyTurnDice();
       sCard.byBuyForToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyTurnDiceTimes);

       //转向
       TVecINT32 vecParam;
       vecParam.push_back(GetCurIndex());
       vecParam.push_back(GetCurLevel());
       _rPlayer.OnEvent(eEventType_ShenglingReturn,vecParam);
   }else
   {
       LOG_INF<<" CardType Err.";
       return EShengLingResultError;
   }

   if(_bLog)
   {
       if(qwBattleID != 0)
           LOG_INF << "qwBattleID=" << qwBattleID;
       LOG_INF<<"====================================PLAYERINFO BEGIN===========================";
       LOG_INF<<"qwRoleID="<<rInfo.qwRoleID<<",byCurLevel="<<rInfo.byCurLevel<<",byCurIndex="<<rInfo.byCurIndex<<",byPreLevel="<<rInfo.byPreLevel<<",byPreIndex="<<rInfo.byPreIndex<<",byUseLife="<<rInfo.byUse<<",byBuy="<<rInfo.byBuy;
       LOG_INF<<"====================================PLAYERINFO END===========================";
   }
   return EShengLingResultSuc;
}

//玩家购买
EShengLingResult CShengLing::OnBuy(EBuyType eBuyType,UINT8 byNum,UINT8 &byBuy,UINT8 &byUse,UINT8 &byBuyToday)
{
    EShengLingResult eResult = EShengLingResultError;
    do
    {
        if(eBuyType == EBuyType_Enter)
            break;
        if(_bLeave)
        {
            LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Leave.";
            return EShengLingResultError;
        }
    }while(0);

    UINT16 wGold = 0;
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return eResult;
    CGameVar& rVar = pUser->GetVars();
    switch(eBuyType)
    {
        case EBuyType_Enter:
            {
                UINT8 byEnterTimes = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyEnterTimes);
                byEnterTimes += byNum;
                const STimesPriceCFG *pPrizeCfg = NULL;
                pPrizeCfg = g_TimesPriceManager.GetConfigByTimes(byEnterTimes);
                if(!pPrizeCfg)
                    return eResult;
                wGold = pPrizeCfg->_RichTimes;
                if(!pUser->CanSubMoney(EMONEY_GOLD,wGold))
                    eResult = EShengLingResultGoldLack;
                else
                {
                    pUser->SubMoney(EMONEY_GOLD,wGold,NLogDataDefine::ItemTo_ShengLing);
                    AddEnterNum(byNum);
                    rVar.SetVar(NVarDefine::ePlayerVarPlayerBuyEnterTimes,byEnterTimes);
                    eResult = EShengLingResultSuc;
                    byBuy = GetBuyEnter();
                    byUse = GetUseEnter();
                    byBuyToday = byEnterTimes;
                }
            }
            break;
        case EBuyType_Life:
            {
                UINT8 byLifeTimes = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyLifeTimes);
                byLifeTimes += byNum;
                const STimesPriceCFG *pPrizeCfg = NULL;
                pPrizeCfg = g_TimesPriceManager.GetConfigByTimes(byLifeTimes);
                if(!pPrizeCfg)
                    return eResult;
                wGold = pPrizeCfg->_RichLife;
                if(!pUser->CanSubMoney(EMONEY_GOLD,wGold))
                    eResult = EShengLingResultGoldLack;
                else
                {
                    pUser->SubMoney(EMONEY_GOLD,wGold,NLogDataDefine::ItemTo_ShengLing);
                    AddLifeNum(byNum);
                    rVar.SetVar(NVarDefine::ePlayerVarPlayerBuyLifeTimes,byLifeTimes);
                    eResult = EShengLingResultSuc;
                    byUse = GetUseLife();
                    byBuy = GetBuyLife();
                    byBuyToday = byLifeTimes;
                }
            }
            break;
        case EBuyType_ControlDice:
            {
                UINT8 byControlDiceTimes = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyControlDiceTimes);
                byControlDiceTimes += byNum;
                const STimesPriceCFG *pPrizeCfg = NULL;
                pPrizeCfg = g_TimesPriceManager.GetConfigByTimes(byControlDiceTimes);
                if(!pPrizeCfg)
                    return eResult;
                wGold = pPrizeCfg->_CtrlDice;
                if(!pUser->CanSubMoney(EMONEY_GOLD,wGold))
                    eResult = EShengLingResultGoldLack;
                else
                {
                    pUser->SubMoney(EMONEY_GOLD,wGold,NLogDataDefine::ItemTo_ShengLing);
                    AddControlNum(byNum);
                    rVar.SetVar(NVarDefine::ePlayerVarPlayerBuyControlDiceTimes,byControlDiceTimes);
                    eResult = EShengLingResultSuc;
                    byUse = GetUseControlDice();
                    byBuy = GetBuyControlDice();
                    byBuyToday = byControlDiceTimes;
                }

            }
            break;
        case EBuyType_TurnCard:
            {
                UINT8 byTurnDiceTimes = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyTurnDiceTimes);
                byTurnDiceTimes += byNum;
                const STimesPriceCFG *pPrizeCfg = NULL;
                pPrizeCfg = g_TimesPriceManager.GetConfigByTimes(byTurnDiceTimes);
                if(!pPrizeCfg)
                    return eResult;
                wGold = pPrizeCfg->_ComeBack;
                if(!pUser->CanSubMoney(EMONEY_GOLD,wGold))
                    eResult = EShengLingResultGoldLack;
                else
                {
                    pUser->SubMoney(EMONEY_GOLD,wGold,NLogDataDefine::ItemTo_ShengLing);
                    AddTurnNum(byNum);
                    rVar.SetVar(NVarDefine::ePlayerVarPlayerBuyTurnDiceTimes,byTurnDiceTimes);
                    eResult = EShengLingResultSuc;
                    byUse = GetUseTurnDice();
                    byBuy = GetBuyTurnDice();
                    byBuyToday = byTurnDiceTimes;
                }

            }
            break;
        case EBuyType_Step:
            {
                wGold = SParamConfig::wRichCrushBoughtPrice;
                wGold = wGold * byNum;
                //优先消耗礼券
                eResult = SubMoneyInShengLing(pUser,wGold);
                if(eResult == EShengLingResultGoldLack)
                    return eResult;
                byBuy = GetStep();
                UINT8 byTmp = byBuy + byNum * 5;
                SetStep(byTmp);
                byUse = 0;
                byBuy = byTmp;
                eResult = EShengLingResultSuc;
            }
            break;
        default:
            break;
    }
   
   if(_bLog)
   {
       LOG_INF<<"====================================BUYINFO BEGIN===========================";
       LOG_INF<<"qwRoleID="<<_rPlayer.GetRoleID()<<",Buy Card, CardType="<<eBuyType<<",TodayBuyNum="<<byBuyToday<<",TotalBuyNum="<<byBuy<<",today byUseNum="<<byUse;
       LOG_INF<<"====================================BUYINFO END===========================";
   }
    return eResult;
}

EShengLingResult CShengLing::SubMoneyInShengLing(CUserPtr pUser,UINT16 wGold)
{
    //优先消耗礼券
    if(pUser->CanSubMoney(EMONEY_COUPON,wGold))
    {
        pUser->SubMoney(EMONEY_COUPON,wGold,NLogDataDefine::ItemTo_ShengLing);
        return EShengLingResultSuc;
    }else if(pUser->CanSubMoney(EMONEY_GOLD,wGold))
    {
        pUser->SubMoney(EMONEY_GOLD,wGold,NLogDataDefine::ItemTo_ShengLing); 
        return EShengLingResultSuc;
    }
    return EShengLingResultGoldLack;
}
//玩家领奖
EShengLingResult CShengLing::OnTakePrize(EGridType eType,UINT8 byIndex,UINT8 &byBit)
{
    byBit = 0;
    UINT16 wGetScore = 0;
    UINT16 wConfigScore = 0;
    if(_bLeave)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Lack Life.";
        return EShengLingResultError;
    }
    if(!(eType == EGridType_Motu || eType == EGridType_Pintu || eType == EGridType_Zadan))
    {
        LOG_INF <<"eGridType Error.";
        return EShengLingResultError;
    }
    SGrid *pGrid = GetGrid(GetCurLevel(),GetCurIndex());
    if(!pGrid || pGrid->eGridType != eType)
    {
        LOG_INF<<"pGrid Null or eType Err.";
        return EShengLingResultError;
    }
    if(pGrid->bFinished == true)
    {
        LOG_INF<<"pGrid->bFinished = true.";
        return EShengLingResultPrizeTaked;
    }
    
    if(eType == EGridType_Zadan)
    {
        if(!GetPrize(*pGrid))
        {
            LOG_INF<<"GetPrize Err.";
            return EShengLingResultError;
        }
    }
    else if(eType == EGridType_Pintu)
    {
        CUserPtr pUser = _rPlayer.GetUserPtr();
        if(!pUser)
            return EShengLingResultError;
        UINT16 wGold = 0;
        //一键完成
        if(byIndex == 1)
        {
            //需要策划配置(优先消耗礼券）
            EShengLingResult eResult;
            wGold = SParamConfig::wRich1PicFinishPrice;
            eResult = SubMoneyInShengLing(pUser,wGold);
            if(eResult == EShengLingResultGoldLack)
                return eResult;
        }
        ShengLingLevelPtr pLevel = g_ShengLingMgr.GetLevelConfig(pGrid->byLevel);
        if(!pLevel)
            return EShengLingResultError;
        
        if(!pLevel->vecPintuPrize.empty())
        {
            CPack& oPack = _rPlayer.GetUserPtr()->GetPack();
            if(!oPack.CanAddItem(pLevel->vecPintuPrize))
            {
                _rPlayer.SendSysMsg(eShengLingPackFul);
                LOG_CRI <<" Pack ful. Check Config file.";
                return EShengLingResultError;
            }
            oPack.AddItem(pLevel->vecPintuPrize,NLogDataDefine::ItemFrom_ShengLing);
            //发送物品
            SendPrizeInfo(pLevel->vecPintuPrize);
            pGrid->bFinished = true;
        }
    }
    else
    {
        UINT8 byTmp = GetPrizeBit();
        //是否可以领取,true可以领
        bool bTake = byTmp & (1 << byIndex) ? false : true;
        if(!bTake)
            return EShengLingResultPrizeTaked;
        ShengLingLevelPtr pLevel = g_ShengLingMgr.GetLevelConfig(pGrid->byLevel);
        if(!pLevel)
            return EShengLingResultError;
        TVecItemGenInfo vecItem;
        switch(byIndex)
        {
            case 0://积分第一档子
                wConfigScore = SParamConfig::wRichCrushLevel1Score;
                vecItem.insert(vecItem.begin(),pLevel->vecDropGroup1.begin(),pLevel->vecDropGroup1.end());
                break;
            case 1:
                wConfigScore = SParamConfig::wRichCrushLevel2Score;
                vecItem.insert(vecItem.begin(),pLevel->vecDropGroup2.begin(),pLevel->vecDropGroup2.end());
                break;
            case 2:
                wConfigScore = SParamConfig::wRichCrushLevel3Score;
                vecItem.insert(vecItem.begin(),pLevel->vecDropGroup3.begin(),pLevel->vecDropGroup3.end());
                break;
            case 3:
                wConfigScore = SParamConfig::wRichCrushLevel4Score;
                vecItem.insert(vecItem.begin(),pLevel->vecDropGroup4.begin(),pLevel->vecDropGroup4.end());
                break;
            default:
                break;
        }
        wGetScore = GetScore();
        if(wGetScore < wConfigScore)
            return EShengLingResultScoreLack;
        if(!vecItem.empty())
        {
            CPack& oPack = _rPlayer.GetUserPtr()->GetPack();
            oPack.AddItem(vecItem,NLogDataDefine::ItemFrom_ShengLing);
            if(!oPack.CanAddItem(vecItem))
            {
                _rPlayer.SendSysMsg(eShengLingPackFul);
                LOG_CRI <<" Pack ful. Check Config file.";
                return EShengLingResultError;
            }
            byTmp |= (1 << byIndex);
            SetPrizeBit(byTmp);
            byBit = byTmp;
            //发送物品
            SendPrizeInfo(vecItem);
        }
    }

   if(_bLog)
   {
       LOG_INF<<"====================================PRIZEINFO BEGIN===========================";
       LOG_INF<<"qwRoleID="<<_rPlayer.GetRoleID()<<" take prize, GridType="<<eType<<",prize index="<<byIndex<<",Total pirze state="<<byBit<<"wGetScore="<<wGetScore<<",wConfigScore="<<wConfigScore;
       LOG_INF<<"====================================PRIZEINFO END===========================";
   }
    return EShengLingResultSuc;
}
//玩家 玩三消
EShengLingResult CShengLing::AddScore(UINT16 wScore,UINT8 byStep,UINT16 wPassword,UINT16 &wPwd,UINT8 &byReminStep,UINT16 &wTotalScore)
{
    if(_bLeave)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Leave.";
        return EShengLingResultError;
    }
    SGrid* pGrid = GetGrid(GetCurLevel(),GetCurIndex());
    UINT8 byTmpStep  = 0;
    if(pGrid->eGridType != EGridType_Motu)
    {
        LOG_INF<<"pGrid type Err.";
        return EShengLingResultTypeError;
    }
    //提前处理 
    {
        wPwd = wPassword;
        byReminStep = GetStep();
        wTotalScore = GetScore();
    }

    if(wPassword != _wPassword)
    {
        LOG_INF<<"password err.";
        return EShengLingResultError;
    }
    //一键消除 扣仙石
    if(byStep == 20)
    {
        CUserPtr pUser = _rPlayer.GetUserPtr();
        EShengLingResult eResult;
        if(!pUser)
            return EShengLingResultError;
        UINT16 wGold = SParamConfig::wRich1CrushFinishPrice;
        eResult = SubMoneyInShengLing(pUser,wGold);
        if(eResult == EShengLingResultGoldLack)
            return eResult;
    }
    else 
    {
        if(byStep > GetStep())
        {
            LOG_INF<<"byStep > GetStep().";
            return EShengLingResultStepLack;
        }
        byTmpStep = GetStep() - byStep;
        SetStep(byTmpStep);
    }

    UINT16 wTmpScore = wScore + GetScore();
    SetScore(wTmpScore);
    wPwd = CRandom::RandInt(1,65535);
    _wPassword = wPwd;
    byReminStep = GetStep();
    wTotalScore = wTmpScore;
    
    if(_bLog)
    {
        LOG_INF<<"qwRoleID="<<_rPlayer.GetRoleID()<<" byReminStep:"<<byReminStep<<",wTotalScore:"<<wTmpScore<<",pNextPwd:"<<wPwd;
    }

    TVecINT32 vecParam;
    vecParam.push_back(wTotalScore);
    _rPlayer.OnEvent(eEventType_ShenglingThreeGameOver,vecParam);

    return EShengLingResultSuc;
}

//玩家完成或者放弃小游戏 处理格子
EShengLingResult CShengLing::OnFinishTrap()
{
    if(_bLeave)
    {
        LOG_INF<<"qwRoleID(" << _rPlayer.GetRoleID()<<") Lack Life.";
        return EShengLingResultError;
    }
    SGrid *pGrid = GetGrid(GetCurLevel(),GetCurIndex());
    if(!pGrid || !(pGrid->eGridType == EGridType_Motu || pGrid->eGridType == EGridType_Pintu || pGrid->eGridType == EGridType_Zadan))
        return EShengLingResultError;

    if(pGrid->eGridType == EGridType_Pintu )
    {
        TVecINT32 vecParam;
        vecParam.push_back(pGrid->bFinished);
        _rPlayer.OnEvent(eEventType_ShenglingPuzzOver,vecParam);
    }

    pGrid->bFinished = true;
    if(pGrid->eGridType == EGridType_Motu)
    {
        SetScore(0);
        SetStep(SParamConfig::wRichCrushTime);
        SetPrizeBit(0);
    }
    if(_bLog)
    {
        LOG_INF<<"qwRoleID="<<_rPlayer.GetRoleID()<<" finish or give up grid! Grid("<<GetCurLevel()<<","<<GetCurIndex()<<").";
    }
    return EShengLingResultSuc;
}

bool CShengLing::ProcessDice(UINT8 byNum,UINT64 &qwBattleID,bool &bNext)
{
    bool bBack = GetDir() ? false : true;
    bNext = false; 
    UINT8 byCurLevel = GetCurLevel();
    UINT8 byCurIndex = GetCurIndex();
    UINT8 byPreIndex = GetPreIndex();
   
    INT8 byDistance = 0;
    if(bBack)
        byDistance = byCurIndex - byNum;
    else
        byDistance = byCurIndex + byNum;
    if(bBack && byDistance <= 1)
    {
        byPreIndex = byCurIndex;
        byCurIndex = 1;
        SetCurIndex(byCurIndex);
        SetPreIndex(byPreIndex);
            
        SetDir(true);
        return true;
    }
    if(!bBack && byDistance >= MAXGRID)
    {
        bNext = true;
        SetGridState(byCurLevel,MAXGRID,true);
        
        //玩家通关
        if(byCurLevel == MAXLEVEL)
        {
            _wPassword = 6666;
            SetCurIndex(MAXGRID);
            _rPlayer.SendPkg(g_ShengLingProtS.BuildPkg_Clearance());  
            OnLeave();
            return true;
        }
        SetPreIndex(MAXGRID);
        byCurLevel += 1; 
        SetCurLevel(byCurLevel);
        SetCurIndex(1);
        
        if(!RandAllGrid())
        {
            LOG_INF<<"RandAllGrid Err.";
            return false;
        }
        /*
        SetGridState(byCurLevel,byCurIndex,true);
        TVecGrid *pvecGrid = GetAllGridByLevel(GetCurLevel());
        if(!pvecGrid) 
        {
            LOG_INF<<"pvecGrid null.";
            return false;
        }
         
        //更新数据库 
        Update2DB(*pvecGrid);
        */
        return true;
    }
    UINT8 byTmp = byCurIndex;
    if(bBack)
        byCurIndex -= byNum;
    else 
        byCurIndex += byNum;
    SGrid *pGrid = GetGrid(byCurLevel,byCurIndex);
    if(pGrid == NULL)
    {
        LOG_INF<<"pGrid NULL,Level="<<byCurLevel<<",Index=" << byCurIndex;
        return false;
    }
    bool bRet = ProcessGrid(*pGrid,qwBattleID);
    if(!bRet)
    {
        LOG_INF<<"Battle Failed.";
        return true;
    }
    SetPreIndex(byTmp);
    SetCurIndex(byCurIndex);
    if(GetPreLevel() != GetCurLevel())
        SetPreLevel(GetCurLevel());
    if(!(pGrid->eGridType == EGridType_Motu || pGrid->eGridType == EGridType_Pintu || pGrid->eGridType == EGridType_Zadan))
        SetGridState(byCurLevel,byCurIndex,true); 
    return true;
}

//玩家离开，需要恢复什么
void CShengLing::Regen()
{
    //第一层第一个格子
    SetCurIndex(1);
    SetCurLevel(1);
LOG_CRI<<"Regen";
    SetStep(SParamConfig::wRichCrushTime);
    SetScore(0);
    SetPrizeBit(0);
    SetDir(true);
    
    SetUseLife(0);
    SetUseControlDice(0);
    SetUseTurnDice(0);
    //清初进入标志,下一次 要减少次数
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarCheckContinue,0);
    }
    //清空本次获得的奖励
    TVecItemGenInfo vecItem;
    UpdatePrize2DB(eOpDel,vecItem);
}

void CShengLing::SetGridState(UINT8 byLevel,UINT8 byIndex,bool bState)
{
    SGrid *pGrid = GetGrid(byLevel,byIndex);
    if(pGrid)
    {
        LOG_INF << " Grid("<<byLevel<<","<<byIndex<<")SetGridState = " <<bState;
        pGrid->bFinished = bState;
        if(bState)
        {
            TVecGrid vecGrid;
            vecGrid.push_back(*pGrid);
            Update2DB(vecGrid);
        }
    }
}

bool CShengLing::CheckPlayEffect()
{
    if(GetCurLevel() != 1)
        return false;
    UINT8 byIndex = GetBigBoxIndex();
    if(byIndex > 40 || byIndex == 0)
        return false;
    if((GetCurIndex() < byIndex) && (byIndex - GetCurIndex() <= 6)) 
    {
        CUserPtr pUser = _rPlayer.GetUserPtr();
        if(!pUser)
            return false;
        CGameVar &rVar = pUser->GetVars();
        bool bFlag = rVar.GetVar(NVarDefine::ePlayerVarPlayDiceEffect) ? true : false;
        if(bFlag)
            return false;
        //赠送遥控骰子 
        if(!CheckControlDiceSended())
        {
            UINT8 byTmp = GetBuyControlDice();
            byTmp += 1;
            SetBuyControlDice(byTmp);
            SetControlDiceSended(true);
        }
        //播放特效
        _rPlayer.SendPkg(g_ShengLingProtS.BuildPkg_PlayEffect());
        rVar.SetVar(NVarDefine::ePlayerVarPlayDiceEffect,1);
    }
    return false;
}

bool CShengLing::ProcessGrid(SGrid &rGrid,UINT64 &qwBattleID)
{
    EGridType eType = rGrid.eGridType;
    bool bWin = false;
    //格子已经完成
    if(rGrid.bFinished == true)
    {
        return !bWin;
    }
    if(eType == EGridType_Normal || eType == EGridType_Elite || eType == EGridType_Boss)
    {
        if(!OnBattle(rGrid.wNoteID,qwBattleID,bWin))
            return false;
        if(!bWin)
        {
            SubLifeNum(1);
            return bWin;
        }
    }
    if(bWin || eType == EGridType_Big || eType == EGridType_Mid || eType == EGridType_Small)
    {
        if(!GetPrize(rGrid))
        {
            LOG_CRI<<"GetPrize Err.";
            return false;
        }
    }
    return true;
}

bool CShengLing::OnBattle(UINT32 dwEnemyID,UINT64 &qwBattleID,bool &bPlayerWin)
{
    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));

    TVecBattleFighterPtr vecBattleFighter;
    _rPlayer.GetBattleFighterList(vecBattleFighter);
    
    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    UINT64 qwTmpInstID =  1;
    qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwEnemyID, qwTmpInstID, vecBattleFighter);
    if (!qwTmpInstID)
        return false;
    pBS->PutFighters(0, _rPlayer.GetMainFighter()->GetInstID(), _rPlayer.GetLevel(), vecBattleFighter, _rPlayer.GetRoleID());
    pBS->PutFighters(1, qwTmpInstID, CMonsterMgr::GetMonsterLevel(dwEnemyID), vecvecBattleFighter2[0], 1);

    IBattleFighterPtr pFighter = CMonster::GetSceneFighter(dwEnemyID);
    if (!pFighter)
        pFighter = _rPlayer.GetSceneFighter();
    pBS->PutScene(pFighter);
    pBS->Start(EBTMonster);
    qwBattleID = pBS->GetBattleID();
    EBattleResult eRet = pBS->GetFinalWinner();
    if(eRet == EBResultAttackWin)
        bPlayerWin = true;
    else if(eRet == EBResultDefenseWin)
        bPlayerWin = false;
    else
        bPlayerWin = true;
    return true;
}
bool CShengLing::GetPrize(SGrid &rGrid)
{
    UINT32 dwNoteID = (UINT32)rGrid.wNoteID;
    if(dwNoteID == 0)
    {
        LOG_INF<<"wNoteID 0";
        return false;
    }
    if(_bLog)
        LOG_INF <<" Recv qwRoleID="<<_rPlayer.GetRoleID()<<" TakePrize,Grid("<<rGrid.byLevel<<","<<rGrid.byIndex<<").";
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    if(rGrid.eGridType == EGridType_Normal || rGrid.eGridType == EGridType_Elite || rGrid.eGridType == EGridType_Boss)
    {
        string strName;
        CMonsterPtr pMonster = CMonsterMgr::CreateMonster(dwNoteID,strName);
        if(!pMonster)
            return false;
        pMonster->DropToPlayer(dwNoteID,_rPlayer,true,&vecItems,&vecRes);
        for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
        {
            SItemGenInfo tepInfo;
            SResource &rRes = *it;
            tepInfo.wItemID = rRes._eRes;
            tepInfo.dwCount = rRes._dwValue;
            vecItems.push_back(tepInfo);
        }
        //发送物品
        SendPrizeInfo(vecItems);
        //清除怪物
        CMonsterMgr::DestroyMonster(pMonster);
        return true;
    }
    LOOT.Roll(dwNoteID, vecItems,vecRes);
    for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
    {
        SItemGenInfo tepInfo;
        SResource &rRes = *it;
        tepInfo.wItemID = rRes._eRes;
        tepInfo.dwCount = rRes._dwValue;
        vecItems.push_back(tepInfo);

    }
    if(!vecItems.empty())
    {
        CPack& oPack = _rPlayer.GetUserPtr()->GetPack();
        if(!oPack.CanAddItem(vecItems))
        {
            _rPlayer.SendSysMsg(eShengLingPackFul);
            LOG_CRI <<" Pack ful. Check Config file.";
            return false;
        }
        oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_ShengLing);
        rGrid.bFinished = true;
        //发送物品
        SendPrizeInfo(vecItems);
        if(_bLog)
            LOG_INF <<"qwRoleID="<<_rPlayer.GetRoleID()<<" TakePrize Suc! Grid("<<rGrid.byLevel<<","<<rGrid.byIndex<<").";
    }
    return true;
}

SGrid* CShengLing::GetGrid(UINT8 byLevel,UINT8 byIndex)
{
    auto it = _mapID2VecGridInfo.find(byLevel);
    if(it == _mapID2VecGridInfo.end())
        return NULL;
    TVecGrid& vecGrid = it->second;
    if(vecGrid.size() < MAXGRID)
        return NULL;
    return &vecGrid[byIndex - 1];
}

void CShengLing::GetPrizeInfo(TVecItemGenInfo &vecItem)
{
    for(auto it : _mapID2Num)
    {
        SItemGenInfo oInfo;
        oInfo.wItemID = it.first;
        oInfo.dwCount = it.second;
        oInfo.eBindType = eBindGet;
        vecItem.push_back(oInfo);
    }
}

void CShengLing::LoadFromDB(const TVecShengLingInfo2DB &rvecDBInfo,const TVecShengLingPrize2DB &rvecDBPrizeInfo)
{
    for(auto it : rvecDBInfo)
    {
         TVecGrid& vecGrid = _mapID2VecGridInfo[it.byLevel];
         SGrid& oGrid = vecGrid.at(it.byIndex - 1);
         oGrid.eGridType = (EGridType)it.byType;
         oGrid.wNoteID = it.wNoteID;
         oGrid.bFinished = (bool)it.byFinish;
         oGrid.bRandom = (bool)it.byRandom;
         if(_bTest)
         {
             LOG_CRI<<"Level="<<it.byLevel<<",byIndex="<<it.byIndex<<",Type="<<it.byType<<",wNoteID="<<it.wNoteID;

         }
    }
    for(auto it : rvecDBPrizeInfo)
        _mapID2Num[it.wItemID] = it.wNum;
}

void CShengLing::Update2DB(TVecGrid &vecGrid)
{
    for(auto it : vecGrid)
    {
        SShengLingInfo2DB oDBInfo;
        oDBInfo.qwRoleID = _rPlayer.GetRoleID();
        oDBInfo.byLevel = it.byLevel;
        oDBInfo.byIndex = it.byIndex;
        oDBInfo.byType  = it.eGridType;
        oDBInfo.wNoteID = it.wNoteID;
        oDBInfo.byFinish = it.bFinished;
        oDBInfo.byRandom = it.bRandom;
        
        //发送数据库 
        string strData;
        COutArchive iar(strData);
        iar << oDBInfo;

        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeShengLing, eOpAdd, strData);
    }
}
void CShengLing::UpdatePrize2DB(EDataChange eDataChange,const TVecItemGenInfo &vecItem)
{
    string strData;
    COutArchive iar(strData);
    UINT64 qwRoleID = _rPlayer.GetRoleID();
    if(eDataChange == eOpDel)
    {
        iar << qwRoleID;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeShengLingPrize, eDataChange, strData);
        return;
    }
    //更新本地奖励列表,然后更新数据库
    for(auto it : vecItem)
    {
        UINT16 wTmp = it.dwCount;
        auto oIt = _mapID2Num.find(it.wItemID);
        if(oIt == _mapID2Num.end())
           _mapID2Num[it.wItemID] = it.dwCount;
        else 
        {
            oIt->second += it.dwCount;
            wTmp = oIt->second;
        }

        SShengLingPrize2DB oDBInfo;
        oDBInfo.qwRoleID = qwRoleID;
        oDBInfo.wItemID = it.wItemID;
        oDBInfo.wNum = wTmp;

        iar << oDBInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeShengLingPrize, eDataChange, strData);
    }
}

void CShengLing::OnLeave()
{
    //玩家离开
    _bLeave = true;
    _eState = eShengLingOut;
    //SubEnterNum(1);
    if(_bLog)
        LOG_INF<<"qwRoleID="<<_rPlayer.GetRoleID()<<" OnLeave!";
    //设置本层第一个格子 不曾来过
    SetGridState(GetCurLevel(),1,false);
    Regen();
}

void CShengLing::UserOffLine()
{
    if(_eState == eShengLingIn)
    {
        if(!CheckLife() || (GetPreLevel() == MAXLEVEL && GetPreIndex() == MAXGRID))
            OnLeave();
    }
}

bool CShengLing::RandAllGrid()
{
    EGridType eType;
    bool bInsertBigBox = false;
    UINT8 byMonsterNote = 0;
    TVecGrid *pvecGrid = NULL;
    SGrid* pGrid = NULL;
    SGrid *pBossGrid1,*pBossGrid2,*pBigBoxGrid;
    pBossGrid1 = pBossGrid2 = pBigBoxGrid = pGrid;
    pvecGrid = GetAllGridByLevel(GetCurLevel());
    if(!pvecGrid || pvecGrid->size() == 0)
    {
        LOG_INF<<"pvecGrid null or size 0.";
        return false;
    }
    //处理前34个格子
    for(size_t i=0; i<34; ++i)
    {
        pGrid = &pvecGrid->at(i);
        pGrid->bRandom = false;
        pGrid->bFinished = false;
        if(!pGrid)
        {
            LOG_INF<<"pGrid null.index = " << i + 1;
            continue;
        }
        if(0 == i)
        {
            //第一层第一个格子
            //if(GetCurLevel() == 1)
            pGrid->bFinished = true;
            pGrid->eGridType = EGridType_Born;
            pGrid->wNoteID = 0;
            continue;
        }
        if(!RandOneGrid(*pGrid,true,false))
        {
            LOG_INF<<"Random one Grid Err.index="<<i + 1;
            continue;
        }
        if(!pGrid->bRandom 
                && (pGrid->eGridType == EGridType_Normal 
                || pGrid->eGridType == EGridType_Elite)
           )
            byMonsterNote ++;
        if(byMonsterNote >= MAXMONTER)
        {
            if(!RandOneGrid(*pGrid,true,true))
            {
                LOG_INF<<"Random Monster Grid Err.index="<<i + 1;
                continue;
            }
            byMonsterNote = 0;
        }
    }
    
    //处理后6个格子
    for(size_t i=34; i<MAXGRID;)
    {
        pGrid = &pvecGrid->at(i);
        pGrid->bRandom = false;
        pGrid->bFinished = false;
        if(39 == i)
        {
            pGrid->eGridType = EGridType_Go;
            pGrid->wNoteID = 0;
            break;
        }
        if(36 == i && !bInsertBigBox)
        {
            goto Lable;
        }
        if(!bInsertBigBox)
            eType = g_ShengLingMgr.GetRandom(true);
        else 
            eType = g_ShengLingMgr.GetRandom(false);
        if(eType != EGridType_Boss)
        {
            pGrid->eGridType = eType;
            if(!g_ShengLingMgr.GetNoteID(pGrid->byLevel,eType,pGrid->wNoteID))
                return false;
           
            i = i + 1;
        }
        else 
        {
Lable:      pBossGrid1 = &pvecGrid->at(i);
            pBigBoxGrid = &pvecGrid->at(i + 1);
            pBossGrid2 = &pvecGrid->at(i + 2);
            GetBossAndBigBoxGrid(*pBossGrid1,*pBossGrid2,*pBigBoxGrid);
            bInsertBigBox = true;
            
            i = i + 3;
        }
    }

    //检测第35个格子是否需要调整
    SGrid &r35Grid = pvecGrid->at(33);
    if(!CheckOneGrid(r35Grid,*pvecGrid))
    {
        EGridType eType = EGridType_None;
        eType = g_ShengLingMgr.RandomGrid(r35Grid.byIndex,true,true); 
        if(eType == EGridType_None)
        {
            LOG_INF<<"RandOneGrid Err.";
            return false;
        }
        r35Grid.eGridType = eType;
        if(!g_ShengLingMgr.GetNoteID(r35Grid.byLevel,eType,r35Grid.wNoteID))
        {
            LOG_INF<<"GetNoteID Err.";
            return false;
        }
    }
    //策划需求
    RejustGrid(*pvecGrid); 
   
    if(_bTest)
    {
        for(auto it : *pvecGrid)
        {
            LOG_CRI <<"byIndex="<<it.byIndex<<",byLevel="<<it.byLevel<<",GridType="<<it.eGridType<<",wNoteID="<<it.wNoteID<<",bFinish="<<it.bFinished<<",bRandom="<<it.bRandom; 
        }
    }
    //更新数据库
    Update2DB(*pvecGrid);
    return true;
}
//调整生成格子
bool CShengLing::RejustGrid(TVecGrid &vecGrid)
{
    UINT8 byTmp = 0;
    byTmp = CheckRejust(2,16,MONSTERNUM1,vecGrid);
    if(byTmp)
        Rejust(2,16,byTmp,vecGrid);
    byTmp = CheckRejust(17,29,MONSTERNUM2,vecGrid);
    if(byTmp)
        Rejust(17,29,byTmp,vecGrid);
    byTmp = CheckRejust(30,39,MONSTERNUM2,vecGrid);
    if(byTmp)
        Rejust(30,39,byTmp,vecGrid);
    return true;
}

UINT8 CShengLing::CheckRejust(UINT8 byUp,UINT8 byDown,UINT8 byNum,TVecGrid& vecGrid)
{
    UINT8 byTmp = 0;
    for(UINT8 i=byUp - 1; i<byDown; ++i)
    {
        SGrid &rGrid = vecGrid.at(i);
        if(rGrid.eGridType == EGridType_Normal || rGrid.eGridType == EGridType_Elite || rGrid.eGridType == EGridType_Boss)
        {
            if(rGrid.bRandom == 0)
                byTmp ++;
        }
    }
    if(byTmp >= byNum)
        return 0;
    return byNum - byTmp;
}
void CShengLing::Rejust(UINT8 byUp,UINT8 byDown,UINT8 byNum,TVecGrid &vecGrid)
{
    UINT8 byPos = byUp - 1;
    for(UINT8 i=0; i<byNum; ++i)
    {
        for(UINT8 byIndex=byPos; byIndex<byDown; ++byIndex)
        {
            SGrid &rGrid = vecGrid.at(byIndex);
            if(rGrid.eGridType == EGridType_Big || rGrid.bRandom == 1)
                continue;
            if(rGrid.eGridType != EGridType_Normal && rGrid.eGridType != EGridType_Elite && rGrid.eGridType != EGridType_Boss)
            {
                if(CheckOneGrid(rGrid,vecGrid))
                {
                    bool bNormal = CRandom::RandInt(0,1);
                    if(bNormal)
                    {
                        rGrid.eGridType = EGridType_Normal;
                        if(!g_ShengLingMgr.GetNoteID(rGrid.byLevel,EGridType_Normal,rGrid.wNoteID))
                        {
                            LOG_INF<<"GetNormalMonster NoteID Err.";
                            return;
                        }
                    }else
                    {
                        rGrid.eGridType = EGridType_Elite;
                        if(!g_ShengLingMgr.GetNoteID(rGrid.byLevel,EGridType_Elite,rGrid.wNoteID))
                        {
                            LOG_INF<<"GetEliteMonster NoteID Err.";
                            return;
                        }
                    }
                    byPos = byIndex;
                }
            }
        }
    }
}

bool CShengLing::CheckOneGrid(SGrid &rGrid,TVecGrid &vecGrid)
{
    UINT8 byTmp,byBegin,byEnd;
    UINT8 byPos = rGrid.byIndex;
    byTmp = byBegin = byEnd = 0;
    if(byPos + 5 > 39)
        byEnd = 39;
    else 
        byEnd = byPos + 5;
    if(byPos < 8)
        byBegin = 2;
    else 
        byBegin = byPos - 5;
    EGridType eType = rGrid.eGridType;
    rGrid.eGridType = EGridType_Elite;
    for(UINT8 byIndex=byBegin - 1; byIndex<byEnd; ++ byIndex)
    {
        SGrid &oGrid = vecGrid.at(byIndex);
        if(oGrid.bRandom == 1)
        {
            byTmp = 0;
            continue;
        }
        if(oGrid.eGridType == EGridType_Normal || oGrid.eGridType == EGridType_Elite || oGrid.eGridType == EGridType_Boss)
        {
            byTmp ++;
            if(byTmp == 6)
            {
                rGrid.eGridType = eType;
                return false;
            }
        }else
            byTmp = 0;
    }
    rGrid.eGridType = eType;
    return true;
}

UINT8 CShengLing::GetBigBoxIndex()
{
    if(GetCurLevel() != 1)
        return ERROR;
    TVecGrid *pvecGrid = GetAllGridByLevel(1);
    if(!pvecGrid || pvecGrid->size() == 0)
        return 0;
    for(auto it : *pvecGrid)
    {
        if(it.eGridType == EGridType_Big)
            return it.byIndex;
    }
    return 0;
}

TVecGrid* CShengLing::GetAllGridByLevel(UINT8 byLevel)
{
    auto it = _mapID2VecGridInfo.find(byLevel);
    if(it != _mapID2VecGridInfo.end())
        return &it->second;
    return NULL;
}

bool CShengLing::GetBossAndBigBoxGrid(SGrid& rBossGrid1,SGrid& rBossGrid2,SGrid& rBigBoxGrid)
{
    UINT16 wBoss1;
    UINT16 wBoss2;
    UINT16 wBigBox;
    UINT8 byLevel = rBigBoxGrid.byLevel;
    g_ShengLingMgr.GetBossMonster(byLevel,wBoss1,wBoss2);
    if(!g_ShengLingMgr.GetNoteID(byLevel,EGridType_Big,wBigBox))
    {
        LOG_INF<<"GetBig NoteID Err.";
        return false;
    }
    rBossGrid1.bFinished = rBossGrid2.bFinished = rBigBoxGrid.bFinished = false;
    rBossGrid1.bRandom = rBossGrid2.bRandom = rBigBoxGrid.bRandom = false;
    rBossGrid1.eGridType = rBossGrid2.eGridType = EGridType_Boss;
    rBossGrid1.wNoteID = wBoss1;
    rBossGrid2.wNoteID = wBoss2;
    rBigBoxGrid.eGridType = EGridType_Big;
    rBigBoxGrid.wNoteID = wBigBox;
    return true;
}

bool CShengLing::RandOneGrid(SGrid& rGrid,bool bAll,bool bExceptMonster)
{
    EGridType eType = EGridType_None;
    eType = g_ShengLingMgr.RandomGrid(rGrid.byIndex,bExceptMonster,bAll); 
    if(eType == EGridType_None)
    {
        LOG_INF<<"RandOneGrid Err.";
        return false;
    }
   
    //在所有中随机并且随机出一个 随机格子,重新随机（去掉随机格子）
    if(bAll && eType == EGridType_Random)
    {
        eType = g_ShengLingMgr.RandomGrid(rGrid.byIndex,false,false);
        if(eType == EGridType_None)
        {
            LOG_INF<<"RandOneGrid Err.";
            return false;
        }
        rGrid.bRandom = true;
    }
    rGrid.eGridType = eType;
    if(!g_ShengLingMgr.GetNoteID(rGrid.byLevel,eType,rGrid.wNoteID))
    {
        LOG_INF<<"getNoteID Err.";
        return false;
    }
    if(_bTest)
    {
        LOG_CRI<<"Index="<<rGrid.byIndex<<",eType="<<eType<<",NoteID="<<rGrid.wNoteID;
    }
    return true;
}

UINT8 CShengLing::GetUseLife()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarShengLingUseLife);
    }
    return ERROR;
}

UINT8 CShengLing::GetBuyLife()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarShengLingBuyLife);
    }
    return 0;
}

UINT8 CShengLing::GetFreeLife()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return 1;
    UINT8 byLv = pUser->GetVIPLevel();
    SVIPLevelCFGEx* pVIP = CVIPMgr::Instance().GetVIPLevelCfg(byLv);
    if(pVIP)
        return pVIP->_RichLife;
    return 1;
}

void CShengLing::SetUseLife(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarShengLingUseLife,byTmp);
    }
}

void CShengLing::SetBuyLife(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarShengLingBuyLife,byTmp);
    }
}

UINT8 CShengLing::GetUseControlDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarUseControlDice);
    }
    return ERROR;
}

UINT8 CShengLing::GetBuyControlDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarBuyControlDice);
    }
    return 0;
}

UINT8 CShengLing::GetFreeControlDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return 1;
    UINT8 byLv = pUser->GetVIPLevel();
    SVIPLevelCFGEx* pVIP = CVIPMgr::Instance().GetVIPLevelCfg(byLv);
    if(pVIP)
        return pVIP->_RichCtrlDiceTime;
    return 1;

}

void  CShengLing::SetUseControlDice(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarUseControlDice,byTmp);
    }
}

void  CShengLing::SetBuyControlDice(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarBuyControlDice,byTmp);
    }
}

UINT8 CShengLing::GetUseTurnDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarUseTurnDice);
    }
    return ERROR;
}
UINT8 CShengLing::GetBuyTurnDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarBuyTurnDice);
    }
    return 0;
}
UINT8 CShengLing::GetFreeTurnDice()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return 1;
    UINT8 byLv = pUser->GetVIPLevel();
    SVIPLevelCFGEx* pVIP = CVIPMgr::Instance().GetVIPLevelCfg(byLv);
    if(pVIP)
        return pVIP->_RichComBackTime;
    return 1;
}

void  CShengLing::SetUseTurnDice(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarUseTurnDice,byTmp);
    }
}

void  CShengLing::SetBuyTurnDice(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarBuyTurnDice,byTmp);
    }
}
//策划新需求
bool CShengLing::CheckEnter()
{
    UINT8 byUse = GetUseEnter();
    if(byUse <= GetFreeEnter())
        return true;
    return GetBuyEnter() ? true : false; 
}

bool CShengLing::CheckLife()
{
    UINT8 byUse = GetUseLife();
    if(byUse <= GetFreeLife())
        return true;
    return GetBuyLife() ? true : false; 
}
bool CShengLing::CheckControlDice()
{
    UINT8 byUse = GetUseControlDice();
    if(byUse <= GetFreeControlDice())
        return true;
    return GetBuyControlDice() ? true : false; 

}
bool CShengLing::CheckTurnDice()
{
    UINT8 byUse = GetUseTurnDice();
    if(byUse <= GetFreeTurnDice())
        return true;
    return GetBuyTurnDice() ? true : false; 
}

bool CShengLing::CheckPrizeState(UINT8 byIndex)
{
    bool bTake = false;
    UINT8 byBit = GetPrizeBit();
    bTake = (byBit & (1 << byIndex)) ? true : false;
    return bTake;
}

UINT8 CShengLing::GetUseEnter()
{

    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarShengLingUseEnter);
    }
    return ERROR;
}

UINT8 CShengLing::GetBuyEnter()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarShengLingBuyEnter);
    }
    return 0;

}

UINT8 CShengLing::GetFreeEnter()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return 1;
    UINT8 byLv = pUser->GetVIPLevel();
    SVIPLevelCFGEx* pVIP = CVIPMgr::Instance().GetVIPLevelCfg(byLv);
    if(pVIP)
        return pVIP->_RichTime;
    return 1;
}

void  CShengLing::SetUseEnter(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarShengLingUseEnter,byTmp);
        LOG_INF<<"set UserEnter"<<byTmp;
    }
}
void  CShengLing::SetBuyEnter(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarShengLingBuyEnter,byTmp);
    }
}
void CShengLing::SubEnterNum(UINT8 byNum)
{
    UINT8 byFree = GetFreeEnter();
    UINT8 byUse = GetUseEnter();
    if(byUse >= byFree)
    {
        UINT8 byBuy = GetBuyEnter();
        byBuy -= byNum;
        SetBuyEnter(byBuy);
        LOG_CRI <<" qwRoleID="<<_rPlayer.GetRoleID()<<" EnterNum has used 1";
    }
    byUse += byNum;
    SetUseEnter(byUse);
}
void CShengLing::SubControlNum(UINT8 byNum)
{
    UINT8 byFree = GetFreeControlDice();
    UINT8 byUse = GetUseControlDice();
    if(byUse >= byFree)
    {
        UINT8 byBuy = GetBuyControlDice();
        byBuy -= byNum;
        SetBuyControlDice(byBuy);
    }
    byUse += byNum;
    SetUseControlDice(byUse);
}
void CShengLing::SubTurnNum(UINT8 byNum)
{
    UINT8 byFree = GetFreeTurnDice();
    UINT8 byUse = GetUseTurnDice();
    if(byUse >= byFree)
    {
        UINT8 byBuy = GetBuyTurnDice();
        byBuy -= byNum;
        SetBuyTurnDice(byBuy);
    }
    byUse += byNum;
    SetUseTurnDice(byUse);
}

void CShengLing::SubLifeNum(UINT8 byNum)
{
    UINT8 byFree = GetFreeLife();
    UINT8 byUse = GetUseLife();
    if(byUse >= byFree)
    {
        UINT8 byBuy = GetBuyLife();
        byBuy -= byNum;
        SetBuyLife(byBuy);
    }
    byUse += byNum;
    SetUseLife(byUse);
}

void CShengLing::AddEnterNum(UINT8 byNum)
{
    UINT8 byBuy = GetBuyEnter();
    SetBuyEnter(byBuy + byNum);
}

void CShengLing::AddControlNum(UINT8 byNum)
{
    UINT8 byBuy = GetBuyControlDice();
    SetBuyControlDice(byBuy + byNum);
}

void CShengLing::AddTurnNum(UINT8 byNum)
{
    UINT8 byBuy = GetBuyTurnDice();
    SetBuyTurnDice(byBuy + byNum);
}
void CShengLing::AddLifeNum(UINT8 byNum)
{
    UINT8 byBuy = GetBuyLife();
    SetBuyLife(byBuy + byNum);
}

UINT8 CShengLing::GetCurLevel()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarPlayerLevel);
    }
    return ERROR;
}

UINT8 CShengLing::GetCurIndex()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarPlayerGridIndex);
    }
    return 1;

}

void  CShengLing::SetCurLevel(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarPlayerLevel,byTmp);
    }
}
void  CShengLing::SetCurIndex(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarPlayerGridIndex,byTmp);
    }
}

UINT8 CShengLing::GetPreLevel()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarPlayerPreLevel);
    }
    return ERROR;
}
UINT8 CShengLing::GetPreIndex()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarPlayerPreGridIndex);
    }
    return ERROR;

}
void  CShengLing::SetPreLevel(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarPlayerPreLevel,byTmp);
    }

}
void  CShengLing::SetPreIndex(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarPlayerPreGridIndex,byTmp);
    }
}

bool CShengLing::GetCardInfo(TVecCard &vecCard)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    CGameVar &rVar = pUser->GetVars();
    SCard oControlDice;
    oControlDice.eCardType = ECardType_ControlDice;
    oControlDice.byBuy = GetBuyControlDice();
    oControlDice.byUse = GetUseControlDice();
    oControlDice.byBuyForToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyControlDiceTimes);
    vecCard.push_back(oControlDice);
    if(_bLog)
    {
        LOG_CRI <<"ControlDice:byTotalBuy="<<oControlDice.byBuy<<",byUse="<<oControlDice.byUse<<",todayBuy="<<oControlDice.byBuyForToday;
    }

    SCard oTurnDice;
    oTurnDice.eCardType = ECardType_TurnDice;
    oTurnDice.byBuy = GetBuyTurnDice();
    oTurnDice.byUse = GetUseTurnDice();
    oTurnDice.byBuyForToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyTurnDiceTimes);
    vecCard.push_back(oTurnDice);
    if(_bLog)
    {
        LOG_CRI <<"TurnDice:byBuy="<<oTurnDice.byBuy<<",byUse="<<oTurnDice.byUse<<",todayBuy="<<oTurnDice.byBuyForToday;
    }
    return true;
}

UINT8 CShengLing::GetStep()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarMotuStep);
    }
    return ERROR;
}
UINT16 CShengLing::GetScore()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return rVar.GetVar(NVarDefine::ePlayerVarMotuScore);
    }
    return ERROR;
}
UINT8 CShengLing::GetPrizeBit()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return (UINT8)rVar.GetVar(NVarDefine::ePlayerVarMotuPrizeState);
    }
    return 255;
}
void  CShengLing::SetStep(UINT8 byTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarMotuStep,byTmp);
    }
}

void  CShengLing::SetScore(UINT16 wTmp)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarMotuScore,wTmp);
    }
    
}

void  CShengLing::SetPrizeBit(UINT8 byIndex)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarMotuPrizeState,byIndex);
    }
}
bool CShengLing::GetDir()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        return (bool)rVar.GetVar(NVarDefine::ePlayerVarPlayerDir);
    }
    return false;
}
void CShengLing::SetDir(bool bDir)
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(pUser)
    {
        CGameVar &rVar = pUser->GetVars();
        rVar.SetVar(NVarDefine::ePlayerVarPlayerDir,(UINT8)bDir);
    }
}

void CShengLing::SyncData()
{
    SShengLingInfo rInfo;
    rInfo.qwRoleID = _rPlayer.GetRoleID();
    rInfo.byLevel = GetCurLevel();
    rInfo.byIndex = GetCurIndex();
    rInfo.byDir = GetDir();
    rInfo.byBuyLife = GetBuyLife();
    rInfo.byUseLife = GetUseLife();
    rInfo.byStep = GetStep();
    rInfo.byScore = GetScore();
    rInfo.byBit = GetPrizeBit();
    rInfo.wPassword = _wPassword;
    TVecGrid *pvecGrid = GetAllGridByLevel(GetCurLevel());
    if(!pvecGrid)
    {
        LOG_CRI <<" pvecGrid null.byLevel = " << GetCurLevel();
        return;
    }
    rInfo.vecGrid.insert(rInfo.vecGrid.begin(),pvecGrid->begin(),pvecGrid->end());
    if(!GetCardInfo(rInfo.vecCard))
    {
        LOG_INF<<"GetCardInfo Err.";
        return;
    }
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    CGameVar& rVar = pUser->GetVars();
    rInfo.byBuyLifeToday = rVar.GetVar(NVarDefine::ePlayerVarPlayerBuyLifeTimes); 
    GetPrizeInfo(rInfo.vecItem);
    UINT8 byFirst = rVar.GetVar(NVarDefine::ePlayerVarFirstEnterShengLing);
    rInfo.byFirst = byFirst;
    _rPlayer.SendPkg(g_ShengLingProtS.BuildPkg_SyncData(rInfo));
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

