
#include "GameVar.h"
#include "VarDefine.h"
UINT64 CGameVar::GetVar(UINT16 wVar)
{
    bool bDel = false;
    iterator i = _vars.end();
    UINT64 qwValue = Vars::GetVar(wVar, i, &bDel);
    UINT32 dwExpired = 0;
    if (i != _vars.end())
        dwExpired = i->second.end;

    if (bDel)
    {
        if (i != _vars.end())
            _vars.erase(i);
        Update2DB(wVar, qwValue, dwExpired, eOpDel);
    }
    return qwValue;
}
UINT32 CGameVar::GetVar32(UINT16 wVar)
{
    return static_cast<UINT32>(GetVar(wVar));
}
UINT64 CGameVar::AddVar(UINT16 wVar, UINT64 qwValue, UINT32 dwOffset, time_t now)
{
    iterator i = _vars.end();
    if (Vars::AddVar(wVar, qwValue, now, dwOffset, i))
        Update2DB(wVar, i->second.val, i->second.end, eOpUpdate);
    else
        Update2DB(wVar, i->second.val, i->second.end, eOpAdd);
    return GetVar(wVar);
}

void CGameVar::SetVar(UINT16 wVar, UINT64 qwValue, UINT32 dwOffset, time_t now)
{
    iterator i = _vars.end();
    bool bUpdate = Vars::SetVar(wVar, qwValue, now, dwOffset,i);
    if (i != _vars.end())
    {
        if(bUpdate)
        {
            Update2DB(wVar, i->second.val, i->second.end, eOpUpdate);
        }
        else
        {
            Update2DB(wVar, i->second.val, i->second.end, eOpAdd);
        }
    }
}

void CGameVar::DelVar(UINT16 wVar)
{
    if (Vars::DelVar(wVar))
        Update2DB(wVar, 0, 0, eOpDel);
}

void CGameVar::SetExpiredTime(UINT16 wVar, UINT32 dwExpired)
{
    iterator i = _vars.end();
    bool bUpdate = Vars::SetExpiredTime(wVar, dwExpired, i);
    if (i != _vars.end())
    {
        if(bUpdate)
        {
            Update2DB(wVar, i->second.val, i->second.end, eOpUpdate);
        }
        else
        {
            Update2DB(wVar, i->second.val, i->second.end, eOpAdd);
        }
    }
}

UINT32 CGameVar::GetExpiredTime(UINT16 wVar)
{
    return Vars::GetExpiredTime(wVar);
}

void CGameVar::SetVarFromDB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired)
{
    Vars::SetVar(wVar, qwValue, dwExpired);
}

CGameVar::CGameVar()
{
    Register();
}

void CGameVar::Register()
{
    //global
    DecVar(NVarDefine::eSystemVarArena,VARRECYCLE_DAY);
    DecVar(NVarDefine::eSystemVarGuildStatue,VARRECYCLE_DAY);
    DecVar(NVarDefine::eSystemVarGuildBattleAward,VARRECYCLE_WEEK);
    DecVar(NVarDefine::eSystemVarDemonTowerMaxTop,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVarQQCoinConsumeValue,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVarQQCoinMaxValue,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVarAnswer,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVarAnswerTopicID,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVarZeroTime,VARRECYCLE_NONE); 
    DecVar(NVarDefine::eSystemVarOpenServerActivity,VARRECYCLE_NONE);

    DecVar(NVarDefine::eSystemVar_WorldBossActBeginTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_WorldBossActEndTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_LangHuanBlessActBeginTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_LangHuanBlessActEndTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_DragonBallActBeginTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_DragonBallActEndTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_DragonBallActPeriod,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::eSystemVar_SevenConsumeActEndTime,VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate1HP, VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate2HP, VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate3HP, VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate1Attack, VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate2Attack, VARRECYCLE_NONE);
	DecVar(NVarDefine::eSystemVar_NewGuildBattleGate3Attack, VARRECYCLE_NONE);

    /************CenterServer begin************/
    DecVar(NVarDefine::ePlayerVarArenaWirship,VARRECYCLE_DAY); 
    DecVar(NVarDefine::ePlayerVarArenaChallengeFree,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarArenaChallengeFlush,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarArenaChallenge0,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarArenaChallenge12,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarArenaChallenge18,VARRECYCLE_DAY);  
    DecVar(NVarDefine::ePlayerVarSendMail,VARRECYCLE_HOUR);  

    DecVar(NVarDefine::ePlayerVarGuildDonate,VARRECYCLE_DAY);  
    DecVar(NVarDefine::ePlayerVarGuildWorship,VARRECYCLE_DAY);  
    DecVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarLadderUpdate,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarLadderChallenge,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarChallegeAward,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarAdoreCount,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarTripodShanfeng, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarTripodHelp, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerNoticeUpdateMark, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerSysDialogMark, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerSysDialogMark, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerAnswer, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerShipRobTimes, VARRECYCLE_DAY);//抢劫次数
    DecVar(NVarDefine::ePlayerShipDefenseTimes, VARRECYCLE_DAY);//护送次数
    DecVar(NVarDefine::ePlayerShipOpenTimes, VARRECYCLE_DAY);//开船次数
    DecVar(NVarDefine::ePlayerShipReFluseTimes, VARRECYCLE_DAY);//刷新次数
    DecVar(NVarDefine::ePlayerBuyOpenShipTimesToday, VARRECYCLE_DAY);//今日购买的运船次数
    DecVar(NVarDefine::ePlayerBuyRoBShipTimesToday, VARRECYCLE_DAY);//今日购买的抢劫次数
    DecVar(NVarDefine::ePlayerBuyReflushShipTimesToday, VARRECYCLE_DAY);//今日购买的刷新次数
    DecVar(NVarDefine::ePlayerFreezShipTimer, VARRECYCLE_NONE);//金船战败冷却时间
    DecVar(NVarDefine::ePlayerInvites, VARRECYCLE_DAY);//每日邀请好友数量
    DecVar(NVarDefine::ePlayerVarXiheHelpCount, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarBuyLadderTimes, VARRECYCLE_NONE);//购买天梯挑战次数
    DecVar(NVarDefine::ePlayerVarBuyLadderTimesToday,VARRECYCLE_DAY );//每日购买天梯挑战次
    DecVar(NVarDefine::ePlayerVarGuildExchangedItemToday, VARRECYCLE_DAY);//玩家今日帮派战兑换物品数量
    DecVar(NVarDefine::ePlayerVarFruit, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarDayPackage, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarMonsterPackage, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarTotalScore, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerQQCoinLevel, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerTeamPos1Cache, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerTeamPos2Cache, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerTeamPos3Cache, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarDayRechargeCenter,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarDragonBall_TodayCount,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarDragonBall_AllCount,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerVarSevenConsumeGold, VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerVarSevenConsumeAwardInfo, VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMinLadderRank, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerQQCoinExchangeCount, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerQQCoinExchangeValue, VARRECYCLE_NONE);

    /************CenterServer end************/

    /************GameServer begin************/
    DecVar(NVarDefine::ePlayerVarRecharge, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarConsume, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarFirstRechrgeStatus, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarDayEvent, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerFlushGroupTask, VARRECYCLE_DAY);  
    DecVar(NVarDefine::ePlayerFlushYaMenTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerFinishGroupTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerFinishYaMenTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerGetGroupPExp, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerBuyGroupTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerBuyYaMenTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerGetYaMenPExp, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerActivity, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerActivityTask, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerActivityAward, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVIPEndTime, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVIPGrowthValue, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVIPType, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVIPDayTime, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVIPGetDayPack, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVIPGetLevelAward, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVIPUsedGold, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarIndulgeTime,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarSittingTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarTaskMark,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerYDDayBag,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerYDNewBag,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerYDYearBag,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerYDLuxuryBag,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerYDGrowBag,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerYDHorseBag,VARRECYCLE_NONE);
    DecVar(NVarDefine::eDemonTowerAtkMonsterCd,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweiwei,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweibo,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweixin,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerTaskMarket,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerWeiboNum,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerWeixinNum,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerQQAlarm,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarLoginDays,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarCuiTiCount,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarSecondRechrgeStatus, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarSecondRechargeValue, VARRECYCLE_NONE);
   
    DecVar(NVarDefine::ePlayerVarShengLingUseLife, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarShengLingBuyLife, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarShengLingBuyEnter, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarShengLingUseEnter, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarUseControlDice, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarBuyControlDice, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarUseTurnDice, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarBuyTurnDice, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMotuScore, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMotuStep, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMotuPrizeState, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerLevel, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerGridIndex, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerPreLevel, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerPreGridIndex, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerDir, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayerBuyControlDiceTimes, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarPlayerBuyTurnDiceTimes, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarPlayerBuyEnterTimes, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarPlayerBuyLifeTimes, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarRechargeToday, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarGetRechargeAward, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarControlDiceSended, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarCheckContinue, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarPlayDiceEffect, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarFenbaoyan, VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarFirstEnterShengLing, VARRECYCLE_NONE);

    //体力相关
    DecVar(NVarDefine::ePlayerVarBuyActionCnt,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarActionRegain1, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarActionRegain2, VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarMaxAction,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarActionAdd,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarActionBuffer,VARRECYCLE_NONE);
    DecVar(NVarDefine::eTeamDgnAward,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerOnLineTime,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerGetInvite,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerSign,VARRECYCLE_MONTH);
    DecVar(NVarDefine::ePlayerTHKillNum,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerTGSL,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerBJGX,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerTLHZ,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerTHCond,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweiwei,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweibo,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerShushanweixin,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerWeixinNum,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerWeiboNum,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerGEMEntryNum,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerGEMBuyEntryNum,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerGEMMissionStatus,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerMoneyTreeCount,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysA,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysB,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysC,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysD,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysE,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysF,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerRegisterSevenDaysG,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerCurDayBuyMark,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerFighterBuyMark,VARRECYCLE_NONE);

    DecVar(NVarDefine::ePlayerMallDiscountPos1,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos2,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos3,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos1Recharge,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos2Recharge,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos3Recharge,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos1Consume,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos2Consume,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos3Consume,VARRECYCLE_ABS);
    DecVar(NVarDefine::ePlayerMallDiscountPos1Mark,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerMallDiscountPos2Mark,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerMallDiscountPos3Mark,VARRECYCLE_NONE);

    DecVar(NVarDefine::ePlayerLoginPkg,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerLeaveLHB,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerMallDayLimitFresh,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerLHBSkill1,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerLHBSkill2,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerLHBSkill3,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerLHBLoginTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerZeroDay,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarDayRechargeGame,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarShushanFoundInfo,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarShushanFoundLoginDays,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerCircleTaskStar,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerCircleTaskNum,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerlixianDgnBuyTimes,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerlixianDgnBuyTimesToday,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerlixianDgnPassToday,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarChongZhi,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerDujieFailTimes,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerDujieCount,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMonthCardEndTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMonthCardGetTime,VARRECYCLE_NONE);
    DecVar(NVarDefine::ePlayerVarMonthCardOverNotice,VARRECYCLE_NONE);

    DecVar(NVarDefine::ePlayerDrawCount,VARRECYCLE_DAY);
    DecVar(NVarDefine::ePlayerVarZhanQi,VARRECYCLE_NONE);
    /************GameServer end************/

}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

