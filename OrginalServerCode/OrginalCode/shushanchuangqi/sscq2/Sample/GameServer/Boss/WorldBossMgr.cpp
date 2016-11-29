
#include "stdafx.h"
#include "Protocols.h"
#include "WorldBossMgr.h"
#include "RTime.h"
#include "MapMgr.h"
#include "MonsterMgr.h"
#include "Random.h"
#include "Player.h"
#include "User.h"
#include <algorithm>
#include "DayActProt.h"
#include "SysMsgDefine.h"
#include "Tokenizer.h"
#include "GameServerSysMail.h" 
#include "ExpMgr.h"
#include "SysMsgDefine.h"
#include "ActionBase.h"
#include "SkillAttr.h"

using namespace NDayActProt;

using namespace NBossProt;

const UINT32 ONE_MINUTE = 60;

//排行榜显示数量
const UINT32 TOPLIST_DISP_MAX_COUNT = 10;

const UINT32 WORLDBOSS_MIN_EXP = 1000;

//基准时间10分钟
const UINT32 WORLDBOSS_BASE_TIME = 10 * ONE_MINUTE;

const FLOAT WORLDBOSS_HP_FACTOR = 1.0f;//hp系数

const FLOAT WORLDBOSS_ATK_FACTOR = 0.5f;//atkhp系数


const UINT32 WORLDBOSS_MIN_HP = 20000000;
const UINT32 WORLDBOSS_MAX_HP = 200000000;
const UINT32 WORLDBOSS_MAX_ATK = 1000000000;
const UINT32 WORLDBOSS_MIN_ATK = 50000;
const FLOAT WORLDBOSS_MAX_ASC_HP_FACTOR = 0.40f;
const FLOAT WORLDBOSS_MAX_ASC_ATK_FACTOR = 0.40f;


CWorldBossMgr::CWorldBossMgr() :
    CDayActivity(eActTypeWorldBoss),
    _dwPrepareTime(0), _dwAppearTime(0), _dwDisapperTime(0), _dwPrepareStep(0),
    _iIdx(0), _bDisappered(false), _qwMonsterID(0),_bDataChange(false),_dwMaxHP(WORLDBOSS_MIN_HP), 
    _bLoaded(false)
{
    //默认bossID
    _dwBoosID = 20000;
    _dwExp = 500;

    _dwNPCLevel = 0;
    _qwLastKillID = 0;

    _bLog = true;

    _dwPlayerCnt = 0;
    _dwNotifyPlayerCnt = 0;
    _dwBossBasTime = WORLDBOSS_BASE_TIME; 
    _dwMaxAttackCnt = 100;
}

CWorldBossMgr::~CWorldBossMgr()
{}

bool CWorldBossMgr::Init()
{

    string strPath = Config._strConfigDir + "Conf/Table/WorldBossPrize.xml";
    CWorldBossPrizeLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    _vecWorldBossPrizeCFGExPtr.clear();

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SWorldBossPrizeCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
            SWorldBossPrizeCFGExPtr pCFGEx(new SWorldBossPrizeCFGEx);
            pCFGEx->CopyFrom(*pCFG);
            
            Tokenizer tk(pCFG->_GivenItem, "|"); // XXX: AttrID[[,AttrValue]|AttrID[[,AttrValue]...]
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (dwItemID)
            {
                UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                SItemGenInfo oItemGenInfo;
                oItemGenInfo.wItemID = dwItemID;
                oItemGenInfo.dwCount = dwItemCount;
                oItemGenInfo.eBindType = eBindGet;
                pCFGEx->_vecItemGenInfo.push_back(oItemGenInfo);
            }
        }
            _vecWorldBossPrizeCFGExPtr.push_back(pCFGEx);
        }

    }
 
    return true;
}

bool CWorldBossMgr::LoadBoss()
{
    if(!g_Game2DBCommC.IsDBInited())
    {
        return false;
    }
    //LOG_CRI << __PRETTY_FUNCTION__;
    g_Game2DBCommC.Send_LoadWorldBossInfo( [this]( UINT8 byRet_, //0为成功，1为失败，2为超时
        const NGame2DBComm::TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
    )
        {
            if(0 != byRet_)
            {
                LOG_CRI<<"LoadBoss fail!!";
                return;
            }
            this->LoadBoss(vecWorldBossInfo); 
        }
    );
    return true;
}

bool CWorldBossMgr::LoadBoss(const NGame2DBComm::TVecWBossDBInfo& vecWorldBossInfo)
{
    LOG_INF<<"LoadBoss sucess:"<<vecWorldBossInfo.size();

    for (size_t i = 0; i < vecWorldBossInfo.size(); ++i)
    {
        _mapBossInfo[vecWorldBossInfo[i].wBossID] = vecWorldBossInfo[i];
        const SWBossDBInfo& info = vecWorldBossInfo[i];
        LOG_INF<<"load boss: maxhp:"<<info.dwHP<<"dwAtk:"<<info.dwAtk<<"bossid:"<<info.wBossID;
    }

    if(0 == vecWorldBossInfo.size())
    {
        //添加缺省boss血量
        SWBossDBInfo sInfo;
        sInfo.dwLast = 0;
        sInfo.dwHP = WORLDBOSS_MIN_HP;
        sInfo.dwAtk = 50000;
        sInfo.dwMAtk = 50000;

        sInfo.wBossID = 20000;
        _mapBossInfo[sInfo.wBossID]=sInfo;

        sInfo.wBossID = 20001;
        _mapBossInfo[sInfo.wBossID]=sInfo;
    }

    _bLoaded = true;
    //LOG_CRI << "WORLDBOSS DATA LOADED.";
    return true;
}

void CWorldBossMgr::SaveBoss(CCreature& rBoss)
{
    LOG_CRI << __PRETTY_FUNCTION__;
    CWorldBoss& rWorldBoss = (CWorldBoss&)(rBoss);
    DOUBLE dwLast = time(NULL) - _dwAppearTime;
    rWorldBoss.SetLast(dwLast);


    //需要计算下次boss数据
    SWBossDBInfo sInfo;
    sInfo.wBossID = rWorldBoss.GetMonsterID();
    sInfo.dwLast = rWorldBoss.GetLast();
    sInfo.dwHP = rWorldBoss.GetLastHP();
    sInfo.dwAtk = rWorldBoss.GetLastAtk();
    sInfo.dwMAtk = rWorldBoss.GetLastMAtk();
    sInfo.dwLastEndTime = time(NULL);

    DOUBLE fRate = (_dwBossBasTime/dwLast-1);
    if(fRate > WORLDBOSS_MAX_ASC_HP_FACTOR)
        fRate = WORLDBOSS_MAX_ASC_HP_FACTOR;

    UINT32 dwOldHP = sInfo.dwHP;
    sInfo.dwHP = sInfo.dwHP + fRate * WORLDBOSS_HP_FACTOR * sInfo.dwHP;

    sInfo.dwAtk = sInfo.dwAtk + fRate * WORLDBOSS_ATK_FACTOR * sInfo.dwAtk; 

    if(sInfo.dwAtk > WORLDBOSS_MAX_ATK)
        sInfo.dwAtk = WORLDBOSS_MAX_ATK;
    if(sInfo.dwAtk < WORLDBOSS_MIN_ATK)
        sInfo.dwAtk  = WORLDBOSS_MIN_ATK;

    sInfo.dwMAtk = sInfo.dwMAtk + fRate * WORLDBOSS_ATK_FACTOR * sInfo.dwMAtk;
    if(sInfo.dwMAtk > WORLDBOSS_MAX_ATK)
        sInfo.dwMAtk = WORLDBOSS_MAX_ATK;
    if(sInfo.dwMAtk < WORLDBOSS_MIN_ATK)
        sInfo.dwMAtk = WORLDBOSS_MIN_ATK;

    if(_dwBossBasTime>dwLast && dwOldHP > sInfo.dwHP)
        sInfo.dwHP = WORLDBOSS_MAX_HP;

    if(sInfo.dwHP < (UINT32)WORLDBOSS_MIN_HP)
        sInfo.dwHP = WORLDBOSS_MIN_HP;

    if(sInfo.dwHP > (UINT32)WORLDBOSS_MAX_HP)
        sInfo.dwHP = WORLDBOSS_MAX_HP;

    if(_bLog)
        LOG_INF<<"old hp:"<<rWorldBoss.GetLastHP()<<" new hp:"<<sInfo.dwHP<<"_dwBossBasTime:"<<_dwBossBasTime<<"fRate:"<<fRate<<"atk:"<<sInfo.dwAtk;

    g_Game2DBCommC.Send_SaveWorldBossInfo(sInfo);

    _mapBossInfo[sInfo.wBossID] = sInfo;

}

void CWorldBossMgr::ChangeBossFactor(UINT32 dwSec)
{

    _dwBossBasTime = dwSec;
    LOG_INF << "WORLDBOSS_BASE_TIME: " <<_dwBossBasTime;

}

void CWorldBossMgr::TimerCheck(UINT32 dwNow)
{
    if (!_bLoaded)
    {
        //LOG_CRI << "WORLDBOSS WAITING FOR BOSS DATA.";
        LoadBoss();
        return;
    }

    if(_bDataChange)
    {
        UpdateTopList();

        _bDataChange = false;
    }

}

bool CWorldBossMgr::OnBossDamage(CPlayer& rPlayer, UINT32 dwScore,UINT32 dwBossCurHP)
{
    if(_bLog)
        LOG_INF<<"OnBossDamage: qwUserID:"<<rPlayer.GetUserID()<<" dwScore: "<<dwScore<<" dwBossCurHP:"<<dwBossCurHP<<"_dwMaxHP: "<<_dwMaxHP;
    if(0 == _dwMaxHP)
    {
        LOG_CRI<<"Error boss _dwMaxHP==0";
        return false;
    }

    CGameMapPtr pMap = GetMap();

    if(NULL == pMap)
    {
        LOG_CRI<<"NULL == _pMap";
        return false;
    }
    
    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_WorldBossAttack,vecParam);
    }


    _dwCurHP = dwBossCurHP;
    
    FLOAT fLevelRate = CExpMgr::GetWBossFightRate(rPlayer.GetLevel());
    
    UINT32 dwExp = 0;

    if(fLevelRate > 0 )
    {
        dwExp = dwScore* fLevelRate;
        if (dwExp < WORLDBOSS_MIN_EXP)
            dwExp = WORLDBOSS_MIN_EXP;
        TVecResource vecSource;
        SResource res;
        res._eRes = EMONEY_EXP;
        res._dwValue = dwExp;
        vecSource.push_back(res);
        TVecItemGenInfo vecItem;
        rPlayer.PendDrop(vecItem,vecSource,PendBattle);
    }
    else
    {
        LOG_CRI<<"fLevelRate==0";
    }

    UINT32  dwTotalDamage = 0;

    auto itr = _mapBossPlayerInfoPtr.find(rPlayer.GetUserID());
    if(itr == _mapBossPlayerInfoPtr.end())
    {
        SBossPlayerInfoPtr pBossPlayerInfo(new SBossPlayerInfo);
        pBossPlayerInfo->qwUserID = rPlayer.GetUserID();
        pBossPlayerInfo->qwRoleID = rPlayer.GetRoleID();
        pBossPlayerInfo->strName = rPlayer.GetName();
        pBossPlayerInfo->dwScore = dwScore;
        pBossPlayerInfo->dwLastScoreTime = time(NULL);
        pBossPlayerInfo->dwExp = dwExp;
        pBossPlayerInfo->dwLevel = rPlayer.GetLevel();
        pBossPlayerInfo->wColor = rPlayer.GetColor();

        _mapBossPlayerInfoPtr[pBossPlayerInfo->qwUserID] = pBossPlayerInfo;

        dwTotalDamage = dwScore;

    }
    else
    {

        itr->second->dwScore += dwScore;
        itr->second->dwExp += dwExp;

        itr->second->dwLastScoreTime =time(NULL);

        dwTotalDamage = itr->second->dwScore;

    }

    _bDataChange = true;
    
    //UpdateTopList();

    //OnGetSelfInfo(rPlayer);

    UINT32 dwbossRate = 100.0*_dwCurHP/_dwMaxHP;
    OnBossHpRate(rPlayer,dwbossRate);

    rPlayer.SendPkg(g_BossProtS.BuildPkg_AtkInfoNotify(dwScore,dwExp,dwTotalDamage,_dwMaxHP));

    LOG_INF<<"PlayerDamage: dmg: "<<dwScore<<"Exp"<<dwExp;

    if(pMap)
        pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));

    if(0 != dwBossCurHP)
    {
        OnPlayerDead(rPlayer);

    }
    else
    {
        _qwLastKillID = rPlayer.GetUserID();
        //OnEnd();
        if(_bLog)
            LOG_INF<<"last kill!!!!";
    }

    return true;
}

//玩家死亡
void CWorldBossMgr::OnPlayerDead(CPlayer& rPlayer)
{

    CGameMapPtr pMap = GetMap();
    if(!pMap)
    {
        return;
    }
    
    SPoint oPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
    rPlayer.JumpMap(pMap,oPoint,0);

    UINT32 dwReliveTime = time(NULL) + SParamConfig::byWorldBossReliveTime; 

   

    //死亡buffer
    TVecUINT32 vecParam;
    rPlayer.SetBuff(eWorldBossDeadBufferID,vecParam,dwReliveTime,true);

    auto itr =  _mapBossPlayerInfoPtr.find(rPlayer.GetUserID());
    if(itr != _mapBossPlayerInfoPtr.end())
    {
       itr->second->dwReliveTime = dwReliveTime;
    }


    rPlayer.SendPkg(g_BossProtS.BuildPkg_ReliveTimeNotify(dwReliveTime));

    rPlayer.GetWalker().Abort();
    
}

bool CWorldBossMgr::OnRelive(CPlayer& rPlayer)
{

    CUser&  rUser = rPlayer.GetUser();
    if(rPlayer.HasBuff(eWorldBossDeadBufferID) == false)
    {
        //rUser.SendSysMsg(eMsgNotDead);
        if(_bLog)
        {
            LOG_INF<<"not dead!!!";
        }
        //return true;
    }

    SBossPlayerInfoPtr pBossPlayerInfo = GetPlayerInfo(rPlayer.GetUserID());
    if(NULL == pBossPlayerInfo)
    {
        LOG_CRI<<"Error not in WorldBossMap: "<<rPlayer.GetUserID();
        return false;
    }

    if(GetStatus()!=eDayActivityStatusProcess)
    {
         SetPlayerRelive(rPlayer);
         return true; 
    }




    {
        UINT32 dwNow = time(NULL)+3;
        if(pBossPlayerInfo->dwReliveTime <= dwNow)
        {
           SetPlayerRelive(rPlayer);
           pBossPlayerInfo->dwReliveTime = 0;
            return true;
        }

        //LOG_CRI<<"RELIVETIME:"<<dwNow-pBossPlayerInfo->dwReliveTime;
        
        if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::byWorldBossLifeBuyPrice))
        {                                                        
            rUser.SendSysMsg(eMsgGoldErr);
            return false;                                        
        }

       
        pBossPlayerInfo->dwReliveTime = 0;
        

    }
    rUser.SubMoney(EMONEY_GOLD,SParamConfig::byWorldBossLifeBuyPrice,NLogDataDefine::ItemTo_WorldBossRelive);

    SetPlayerRelive(rPlayer);

    TVecINT32 vecParam;
    vecParam.push_back(1);
    rPlayer.OnEvent(eEventType_WorldBossBuyLive,vecParam);

    return true;
   
}

bool CWorldBossMgr::BuyStrength(CPlayer& rPlayer,UINT32 dwBuyType,UINT32& dwSilverBufferCnt,UINT32& dwGoldBufferCnt,UINT32& dwSilverBufferCdTime)
{

    CUser&  rUser = rPlayer.GetUser();
    if(_dwEndTime < time(NULL))
    {
        LOG_CRI<<"worldboss not open!!!";
        rUser.SendSysMsg(eMsgBossOver);
        return false;
    }


    SBossPlayerInfoPtr pBossPlayerInfo = GetPlayerInfo(rPlayer.GetUserID()); 
    if(NULL == pBossPlayerInfo)
    {
        return false;
    }

    static UINT16 wMaxBufferCnt = 10;

   // if((pBossPlayerInfo->dwSilverBufferCnt + pBossPlayerInfo->dwGoldBufferCnt) >= wMaxBufferCnt)
   // {
   //     rUser.SendSysMsg(eMsgArenaBuyOverTimes);
   //     return false;
   // }



    UINT32 dwBufferID = eWorldBossStrengthID;

    switch(dwBuyType)
    {
        case eGold:
            {
                if(pBossPlayerInfo->dwGoldBufferCnt>=wMaxBufferCnt)
                {
                    rUser.SendSysMsg(eMsgArenaBuyOverTimes);
                    return false;
                }
                dwBufferID = eWorldBossGoldBufferID;
                if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::byWorldBossVipAddPrice))
                {
                    rUser.SendSysMsg(eMsgGoldErr);
                    return false;
                }

           }
            break;
        case eSliver:
            {
                if(pBossPlayerInfo->dwSilverBufferCnt>=wMaxBufferCnt)
                {
                    rUser.SendSysMsg(eMsgArenaBuyOverTimes);
                    return false;
                }
 
                dwBufferID = eWorldBossSilverBufferID;
                if(!rUser.CanSubMoney(EMONEY_SILVER,SParamConfig::wWorldBossNormalAddPrice))
                {
                    rUser.SendSysMsg(eMsgSilverErr);
                    return false;
                }
                if(pBossPlayerInfo->dwSilverBufferCdTime > time(NULL))
                {
                    rUser.SendSysMsg(eMsgWorldBoughtCold); 
                    return false;
                }
            }
            break;
    }


    UINT32 dwLastEnd = _dwEndTime - time(NULL);

    switch(dwBuyType)
    {
        case eGold:
            {
                
                UINT32 dwSkillAttrID = SParamConfig::wWorldBossVipAddAttr; // + pBossPlayerInfo->dwGoldBufferCnt;
                if(NULL == g_SkillAttrMgr.GetSkillAttrByID(dwSkillAttrID))
                {
                    rUser.SendSysMsg(eMsgBufferMaxCnt);
                    return false;
                }
                rUser.SubMoney(EMONEY_GOLD,SParamConfig::byWorldBossVipAddPrice,NLogDataDefine::ItemTo_WorldBossBuyStrength);
                pBossPlayerInfo->dwGoldBufferCnt += 1;
                TVecUINT32 vecParam;
                vecParam.push_back(dwSkillAttrID);
                vecParam.push_back(pBossPlayerInfo->dwGoldBufferCnt);
                rPlayer.SetBuff(dwBufferID,vecParam,dwLastEnd);
                //事件
                {
                 TVecINT32 vecParam;
                 vecParam.push_back(EMONEY_GOLD);
                 vecParam.push_back(1);
                 CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
                 if(pEventMgr)
                     pEventMgr->OnEvent(eEventType_WorldBossInspire,vecParam);
                }


                if(_bLog)
                    LOG_INF<<"eGold: "<<dwSkillAttrID<<"goldbuffcnt: "<<pBossPlayerInfo->dwGoldBufferCnt;

            }
            break;
        case eSliver:
            {
                UINT32 dwSkillAttrID = SParamConfig::wWorldBossNormalAddAttr; // + pBossPlayerInfo->dwSilverBufferCnt;
                if(NULL == g_SkillAttrMgr.GetSkillAttrByID(dwSkillAttrID))
                {                                                         
                     LOG_CRI<<"silver Error dwSkillAttrID:"<<dwSkillAttrID;
                     rUser.SendSysMsg(eMsgBufferMaxCnt);                   
                     return false;                                         
                }                                                         

                rUser.SubMoney(EMONEY_SILVER,SParamConfig::wWorldBossNormalAddPrice,NLogDataDefine::ItemTo_WorldBossBuyStrength);
                pBossPlayerInfo->dwSilverBufferCnt += 1;
                TVecUINT32 vecParam;
                vecParam.push_back(dwSkillAttrID);
                vecParam.push_back(pBossPlayerInfo->dwSilverBufferCnt);
                rPlayer.SetBuff(dwBufferID,vecParam,dwLastEnd);
                //去掉银币加成cd
                //pBossPlayerInfo->dwSilverBufferCdTime = SParamConfig::byWorldBossNormalAddCd + time(NULL);
                //dwSilverBufferCdTime = pBossPlayerInfo->dwSilverBufferCdTime;
                
                //事件
                {
                 TVecINT32 vecParam;
                 vecParam.push_back(EMONEY_SILVER);
                 vecParam.push_back(1);
                 CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
                 if(pEventMgr)
                     pEventMgr->OnEvent(eEventType_WorldBossInspire,vecParam);
                }

                if(_bLog)
                LOG_INF<<"CD:"<<SParamConfig::byWorldBossNormalAddCd<<"pBossPlayerInfo->dwSilverBufferCdTime:"<<pBossPlayerInfo->dwSilverBufferCdTime;
            }
            break;
    }

    dwSilverBufferCnt = pBossPlayerInfo->dwSilverBufferCnt;
    dwGoldBufferCnt = pBossPlayerInfo->dwGoldBufferCnt;
    dwSilverBufferCdTime = pBossPlayerInfo->dwSilverBufferCdTime;

    rPlayer.BufferRebuildAttr();

    rUser.SendSysMsg(eMsgWorldBoughtConfirm);


    return true;
}

extern void AttackCreature(CUser& rUser,UINT64 qwDefenseID);

void CWorldBossMgr::SetPlayerRelive(CPlayer& rPlayer)
{
    rPlayer.RemoveBuff(eWorldBossDeadBufferID);

    rPlayer.SendPkg(g_BossProtS.BuildPkg_ReliveTimeNotify(0));
}

//攻击boss
bool CWorldBossMgr::AttackBoss(CPlayer& rPlayer)
{


    if(rPlayer.IsBattleCD())              
    {                                     
         LOG_CRI<<"IsBattleCD!!!";
         rPlayer.SendSysMsg(eMsgBattleCd);
         return true;                           
    } 
    
    SBossPlayerInfoPtr pPlayerInfo = GetPlayerInfo(rPlayer.GetUserID());
    if(NULL == pPlayerInfo)
    {
        LOG_CRI<<"not find player!!!"<<rPlayer.GetUserID();
        return false;
    }

    if(pPlayerInfo->dwAttackCnt >= _dwMaxAttackCnt)
    {
        return false;
    }

    SetPlayerRelive(rPlayer);

    if(GetStatus()!=eDayActivityStatusProcess)
    {
        return false;
    }

    if(0 == _qwMonsterID)
    {
        return false;
    }

    CUser&  rUser = rPlayer.GetUser();

    if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::byWorldBossAttackNow))
    {                                                        
        rUser.SendSysMsg(eMsgGoldErr);                       
        return false;                                        
    }                                                        

    rUser.SubMoney(EMONEY_GOLD,SParamConfig::byWorldBossAttackNow,NLogDataDefine::ItemTo_WorldAttack);

    AttackCreature(rUser,_qwMonsterID);

    pPlayerInfo->dwAttackCnt += 1;

    rPlayer.SendPkg(g_BossProtS.BuildPkg_AttackCountNotify(pPlayerInfo->dwAttackCnt));
    
    TVecINT32 vecParam;
    vecParam.push_back(1);
    rPlayer.OnEvent(eEventType_WorldBossAttackRightNow,vecParam);

    return true;
}

bool CWorldBossMgr::CheckMsg(UINT32 dwMsgRate,UINT32 dwOlddRate,UINT32 dwNewRate,CPlayer& rPlayer)
{
    LOG_INF<<"CheckMsg:"<<dwMsgRate<<" ! "<<dwOlddRate<<" ! "<<dwNewRate;
    if(dwOlddRate>dwMsgRate && dwNewRate <= dwMsgRate)
    {
        UINT32 dwMsg = eMsgWorldBossHp;
       if(eWorldBossID1545 == _dwBoosID)
       {
           dwMsg = eMsgWorldBossHp2;
       }
      g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,dwMsg,BuildStrVec(rPlayer.GetColor(),rPlayer.GetName(),dwMsgRate));
      return true;
    }

    return false;

}

bool CWorldBossMgr::ChecRatePrize(UINT32 dwMsgRate,UINT32 dwOlddRate,UINT32 dwNewRate,CPlayer& rPlayer)
{
    if(dwOlddRate>dwMsgRate && dwNewRate <= dwMsgRate)
    {
       SDamageRatePrize oTemp(rPlayer.GetRoleID(),dwMsgRate);
       _vecDamageRatePrize.push_back(oTemp);
      return true;
    }
    return false;
}


void CWorldBossMgr::OnBossHpRate(CPlayer& rPlayer,UINT32 dwbossRate)
{
    UINT32 dwMessageRate = 100;
    if(dwbossRate < 5 )
    {
        dwMessageRate = 5;
    }
    else 
    {
        if(0 == (dwMessageRate%10))
        {
            dwMessageRate = dwbossRate;
        }
        else
        {
            dwMessageRate = dwMessageRate - dwMessageRate%10 + 10;
        }
    }

    if(_dwMessageHpRate != dwMessageRate)
    {
        if(CheckMsg(20,_dwMessageHpRate,dwMessageRate,rPlayer))
        {
        }
        else if(CheckMsg(40,_dwMessageHpRate,dwMessageRate,rPlayer))
        {
        }
        else if(CheckMsg(60,_dwMessageHpRate,dwMessageRate,rPlayer))
        {
        }
        else if(CheckMsg(80,_dwMessageHpRate,dwMessageRate,rPlayer))
        {
        }

        //奖励记录
        ChecRatePrize(20,_dwMessageHpRate,dwMessageRate,rPlayer);
        ChecRatePrize(40,_dwMessageHpRate,dwMessageRate,rPlayer);
        ChecRatePrize(60,_dwMessageHpRate,dwMessageRate,rPlayer);
        ChecRatePrize(80,_dwMessageHpRate,dwMessageRate,rPlayer);

        _dwMessageHpRate = dwMessageRate;

    }
 
}

bool CompareBossPlayerInfo(SBossPlayerInfoPtr pT1, SBossPlayerInfoPtr pT2)
{
    if(pT1->dwScore == pT2->dwScore)
    {
        return pT1->dwLastScoreTime < pT2->dwLastScoreTime;
    }

    return pT1->dwScore > pT2->dwScore;

}


void GetCFGPrizeInfo(SWorldBossPrizeCFGExPtr pWorldBossPrizeCFGEx, SPlayerPrize& rPlayerPrize)
{
    if(NULL == pWorldBossPrizeCFGEx)
    {
        return;
    }
    rPlayerPrize.dwPrizeType = pWorldBossPrizeCFGEx->_PrizeType;

    for(auto itr = pWorldBossPrizeCFGEx->_vecItemGenInfo.begin(); itr != pWorldBossPrizeCFGEx->_vecItemGenInfo.end(); ++itr)
    {
        SPrizeIteminfo oPrizeIteminfo;
        oPrizeIteminfo.dwItemID = itr->wItemID;
        oPrizeIteminfo.dwItemCount = itr->dwCount;
        rPlayerPrize.vecPrizeItemInfo.push_back(oPrizeIteminfo);
    }

     //银币
     if(pWorldBossPrizeCFGEx->_ResourceValue1)
     {
         SPrizeMoneyInfo  oPrizeMoneyInfo;
         oPrizeMoneyInfo.dwMoneyType = pWorldBossPrizeCFGEx->_Resource1Type;
         oPrizeMoneyInfo.dwMoneyValue = pWorldBossPrizeCFGEx->_ResourceValue1;
         rPlayerPrize.vecPrizeMoneyInfo.push_back(oPrizeMoneyInfo);
    }

     //荣誉
     if(pWorldBossPrizeCFGEx->_ResourceValue2)
     {
         SPrizeMoneyInfo  oPrizeMoneyInfo;
         oPrizeMoneyInfo.dwMoneyType = pWorldBossPrizeCFGEx->_Resource2Type;
         oPrizeMoneyInfo.dwMoneyValue = pWorldBossPrizeCFGEx->_ResourceValue2;
         rPlayerPrize.vecPrizeMoneyInfo.push_back(oPrizeMoneyInfo);
     }
}


void CWorldBossMgr::UpdateTopList(bool bEnd)
{
    if(0 == _dwMaxHP)
    {
        LOG_CRI<<"worldboss MaxHP == 0";
        return;
    }

    CGameMapPtr pMap = GetMap();
    if(NULL == pMap)
        return;

    TVecBossPlayerInfoPtr vecBossPlayerInfoPtr;
    for(auto itr = _mapBossPlayerInfoPtr.begin(); itr != _mapBossPlayerInfoPtr.end(); ++itr)
    {
        if(itr->second->dwLastScoreTime)
            vecBossPlayerInfoPtr.push_back(itr->second);
    }

    sort(vecBossPlayerInfoPtr.begin(),vecBossPlayerInfoPtr.end(),CompareBossPlayerInfo);

    //无人参加
    if(vecBossPlayerInfoPtr.size() < 1)
    {
        return;
    }

    _vecBossPlayerInfoPtr.clear();

    UINT32 dwRandom = 0;
    SWorldBossPrizeCFGExPtr pNpcPrize; //参与奖
    if(bEnd)
    {
        dwRandom = rand()%vecBossPlayerInfoPtr.size();
    }

    NBossProt::TVecPlayerInfo vecPlayerInfo;
    for(UINT32 i = 0; i< vecBossPlayerInfoPtr.size(); ++i)
    {
        SBossPlayerInfoPtr pPlayer = vecBossPlayerInfoPtr[i];
        if(NULL == pPlayer)
        {
            continue;
        }

        TVecUINT64 vecUserID;
        vecUserID.push_back(pPlayer->qwUserID);

        UINT32 oldNo = pPlayer->dwNo;
        pPlayer->dwNo = i+1;
        if(oldNo != pPlayer->dwNo)
        {
             CPlayerPtr pMapPlayer = pMap->GetPlayer(pPlayer->qwUserID);
            if(pMapPlayer)
            {
                pMapPlayer->SendPkg(g_BossProtS.BuildPkg_NoChangeNotify(pPlayer->dwNo));
            }
        }

        //排行榜显示10个
        if(i < TOPLIST_DISP_MAX_COUNT)
        {
            NBossProt::SPlayerInfo oPlayerInfo;
            oPlayerInfo.dwNo = pPlayer->dwNo;
            oPlayerInfo.qwUserID = pPlayer->qwUserID;
            oPlayerInfo.strUserName = pPlayer->strName;
            oPlayerInfo.dwDamageHP = pPlayer->dwScore;
            oPlayerInfo.dwBossMaxHP = _dwMaxHP;
            vecPlayerInfo.push_back(oPlayerInfo);
            _vecBossPlayerInfoPtr.push_back(pPlayer);
        }

        //结束发奖励
        if(bEnd)
        {
            TVecPlayerPrize vecPlayerPrize;
        //排名奖励
        SWorldBossPrizeCFGExPtr pTopPrize= GetPrize(eWorldBossPrizeTop,pPlayer->dwNo); 
        if(pTopPrize)
        {
            TVecItemGenInfo vecItems;
            GetCFGMailItem(pTopPrize,pPlayer->dwLevel,vecItems);
        
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_WORLDBOSS_TOP;
            stBody.vecParam.push_back(NumberToString(pPlayer->dwNo));
            GameServerSysMail::SendSysMail(SEND_WORLDBOSS_TOP, TITLE_WORLDBOSS_TOP, stBody, vecUserID, &vecItems);


            SPlayerPrize oPlayerPrize;
            GetCFGPrizeInfo(pTopPrize,oPlayerPrize);
            vecPlayerPrize.push_back(oPlayerPrize);
        }

        if(1 == pPlayer->dwNo)
        {
            UINT32 dwMsg = eMsgWorldBossWinner;
            if(eWorldBossID1545 == _dwBoosID)
            {
                dwMsg = eMsgWorldBossWinner2;
            }

            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,dwMsg,BuildStrVec(pPlayer->wColor,pPlayer->strName));
        }
        //伤害奖励
        
        UINT32 dwDamageRate = 100.0 * pPlayer->dwScore/_dwMaxHP;
        if(dwDamageRate >= 3)
        {
            dwDamageRate = 3;
        }

        SWorldBossPrizeCFGExPtr pDamagePrize= GetPrize(eWorldBossPrizeDamage,dwDamageRate);
        if(pDamagePrize)
        {
            TVecItemGenInfo vecItems;
            GetCFGMailItem(pDamagePrize,pPlayer->dwLevel,vecItems);
        
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_WORLDBOSS_DMG;
            stBody.vecParam.push_back(NumberToString(dwDamageRate));
            GameServerSysMail::SendSysMail(SEND_WORLDBOSS_DMG, TITLE_WORLDBOSS_DMG, stBody, vecUserID, &vecItems);
           
            SPlayerPrize oPlayerPrize;                
            GetCFGPrizeInfo(pDamagePrize,oPlayerPrize);  
            vecPlayerPrize.push_back(oPlayerPrize);   

        }
        //随机奖励
        if(dwRandom == i)
        {
            SWorldBossPrizeCFGExPtr pRandomrize= GetPrize(eWorldBossPrizeRandom);
            if(pRandomrize)
            {
                TVecItemGenInfo vecItems;
                GetCFGMailItem(pRandomrize,pPlayer->dwLevel,vecItems);
        
                NMailProt::SysMailSendTxt stBody;
                stBody.dwstrMsgID = BODY_WORLDBOSS_LUCKY;
                //stBody.vecParam.push_back(NumberToString(pPlayerData->_byTotalWin));
                GameServerSysMail::SendSysMail(SEND_WORLDBOSS_LUCKY, TITLE_WORLDBOSS_LUCKY, stBody, vecUserID, &vecItems);
                SPlayerPrize oPlayerPrize;                
                GetCFGPrizeInfo(pRandomrize,oPlayerPrize);  
                vecPlayerPrize.push_back(oPlayerPrize);   

               
                
            }

            UINT32 dwMsg = eMsgWorldBossLuck;
            if(eWorldBossID1545 == _dwBoosID)
            {
                dwMsg = eMsgWorldBossLuck2;
            }

            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,dwMsg,BuildStrVec(pPlayer->wColor,pPlayer->strName)); 
        }

        //参与奖励
        {
            SPlayerPrize oPlayerPrize;                
            GetCFGPrizeInfo(_pNpcPrize,oPlayerPrize);  
            vecPlayerPrize.push_back(oPlayerPrize);   

            TVecItemGenInfo vecItems;
            GetCFGMailItem(_pNpcPrize,pPlayer->dwLevel,vecItems);
        
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_WORLDBOSS_NPC;
            stBody.vecParam.push_back(NumberToString(_dwNPCLevel));
            GameServerSysMail::SendSysMail(SEND_WORLDBOSS_NPC, TITLE_WORLDBOSS_NPC, stBody, vecUserID, &vecItems);



        }

           //击杀奖励
          if(pPlayer->qwUserID == _qwLastKillID)
          {
            SPlayerPrize oPlayerPrize;                
            GetCFGPrizeInfo(_pKillPrize,oPlayerPrize);  
            vecPlayerPrize.push_back(oPlayerPrize);   
            
            TVecItemGenInfo vecItems;
            GetCFGMailItem(_pKillPrize,pPlayer->dwLevel,vecItems);
        

            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_WORLDBOSS_KILL;
            //stBody.vecParam.push_back(NumberToString(_pNpcPrize));
            GameServerSysMail::SendSysMail(SEND_WORLDBOSS_KILL, TITLE_WORLDBOSS_KILL, stBody, vecUserID, &vecItems);
            //g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgWorldBossLastHit,BuildStrVec(pPlayer->strName));

          }


          g_BossProtS.SendClt_PrizeNotify(&pPlayer->qwUserID,1,vecPlayerPrize);
          g_BossProtS.SendClt_GainPrizeNotify(&pPlayer->qwUserID,1,i,pPlayer->dwExp,pPlayer->qwUserID == _qwLastKillID);
        }

    }

    //参与奖发送
    if(bEnd)
    {
        TVecPlayerPrize vecPlayerPrize;
        //排名奖励
        SWorldBossPrizeCFGExPtr pDamagePrize= GetPrize(eWorldBossPrizeBossHP); 
        if(pDamagePrize)
        {
            for(size_t i=0; i <_vecDamageRatePrize.size(); i++)
            {
                SBossPlayerInfoPtr pPlayer = GetPlayerInfo(_vecDamageRatePrize[i]._qwRoleID);
                if(pPlayer)
                {
                    TVecUINT64 vecUserID;
                    vecUserID.push_back(pPlayer->qwUserID);
                    TVecItemGenInfo vecItems;
                    GetCFGMailItem(pDamagePrize,pPlayer->dwLevel,vecItems);
        
                    NMailProt::SysMailSendTxt stBody;
                    stBody.dwstrMsgID = BODY_WORLDBOSS_DMGRATE;
                    stBody.vecParam.push_back(NumberToString(_vecDamageRatePrize[i]._dwDamageRate));
                    GameServerSysMail::SendSysMail(SEND_WORLDBOSS_TOP, TITLE_WORLDBOSS_DMGRATE, stBody, vecUserID, &vecItems);
                }
                else
                {
                    LOG_CRI<<"GetPlayerInfo failed! roleID:"<<_vecDamageRatePrize[i]._qwRoleID;
                }
            
             }

          }

        
      }

    if(pMap)
    {
        pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_TopListNotify(vecPlayerInfo));
    }
   
}

bool CWorldBossMgr::CanEnterBossMap() const
{
    return _dwPrepareStep;
}

bool CWorldBossMgr::IsBossAlive() const
{
    return !_bDisappered;
}

//添加初始化时间事件
void CWorldBossMgr::TimerInit()
{

}
//进入地图
bool CWorldBossMgr::OnEnterMap(CPlayer& rPlayer)
{
    if(rPlayer.GetLevel() < 30)
    {
        rPlayer.SendSysMsg(eMsgSysNotOpenLvlErr);
        return true;
    }
    
    if(GetStatus()!=eDayActivityStatusProcess &&  GetStatus()!=eDayActivityStatusReady)
    {
        LOG_CRI<<"worlboss not open!!!";
        return false; 
    }

    CActionManager& rActionManager= rPlayer.GetActionManager();
    if(rActionManager.CanAddAction(eACTION_WORLDBOSS,true) != eACTION_NONE)
    {
        return true;
    }


    
    CGameMapPtr pMap = GetMap();
    if(pMap)
    {
        SPoint rSrcPoint(rPlayer.GetPoint());
        UINT32 dwMapID = rPlayer.GetCurMapID();
        SPoint rDestPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
        rPlayer.JumpMap(pMap,rDestPoint);

        _dwPlayerCnt = pMap->GetPlayerCount();

        rPlayer.RemoveBuff(eWorldBossSilverBufferID);
        rPlayer.RemoveBuff(eWorldBossGoldBufferID);
 
        auto itr =  _mapBossPlayerInfoPtr.find(rPlayer.GetUserID());
        if(itr != _mapBossPlayerInfoPtr.end())
        {
            if(itr->second->dwReliveTime > time(NULL))
            {
                TVecUINT32 vecParam;
                rPlayer.SetBuff(eWorldBossDeadBufferID,vecParam,itr->second->dwReliveTime,true);
            }

            itr->second->oPoint = rSrcPoint;
            itr->second->dwMapID = dwMapID;

            if(itr->second->dwGoldBufferCnt)
            {
              TVecUINT32 vecParam;
              vecParam.push_back(SParamConfig::wWorldBossVipAddAttr);
              vecParam.push_back(itr->second->dwGoldBufferCnt);
              rPlayer.SetBuff(eWorldBossGoldBufferID,vecParam,_dwEndTime);
            }

            if(itr->second->dwSilverBufferCnt)
            {
              TVecUINT32 vecParam;
              vecParam.push_back(SParamConfig::wWorldBossNormalAddAttr);
              vecParam.push_back(itr->second->dwSilverBufferCnt);
              rPlayer.SetBuff(eWorldBossSilverBufferID,vecParam,_dwEndTime);
            }
   
        }
        else
        {
             SBossPlayerInfoPtr pBossPlayerInfo(new SBossPlayerInfo);
             pBossPlayerInfo->qwUserID = rPlayer.GetUserID();
             pBossPlayerInfo->qwRoleID = rPlayer.GetRoleID();
             pBossPlayerInfo->strName = rPlayer.GetName();
             pBossPlayerInfo->dwLevel = rPlayer.GetLevel();
             pBossPlayerInfo->oPoint = rSrcPoint;
             pBossPlayerInfo->dwMapID = dwMapID;
             pBossPlayerInfo->wColor  = rPlayer.GetColor();
             _mapBossPlayerInfoPtr[pBossPlayerInfo->qwUserID] = pBossPlayerInfo;
             rPlayer.RemoveBuff(eWorldBossSilverBufferID);
             rPlayer.RemoveBuff(eWorldBossGoldBufferID);

        }

    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(_dwBoosID);
        CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_WorldBossEnter,vecParam);
    }


    }
    if(pMap)
        pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));
 
    return true;
}

//离开地图
bool CWorldBossMgr::OnLeaveMap(CPlayer& rPlayer)
{
    CGameMapPtr pMap = rPlayer.GetMap();
    if(NULL == pMap)
    {
        LOG_CRI<<"UnKown Error!";
        return false;
    }

    if(pMap->GetMapType() != eMapWorldBoss)
    {
        LOG_CRI<<"cheater?!!!"; 
        return false;
    }
/*
    SBossPlayerInfoPtr pBossPlayerInfo = GetPlayerInfo(rPlayer.GetUserID());
    if(NULL == pBossPlayerInfo)
    {
         UINT16 wMapID = 1;
         CGameMapPtr pMap = CMapMgr::GetMap(wMapID);
         if(NULL == pMap)
         {
             return false;
         }
         SPoint oPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
         rPlayer.JumpMap(pMap,oPoint,0);
    }
    else
    {
         rPlayer.JumpMap(pBossPlayerInfo->dwMapID,pBossPlayerInfo->oPoint);
    }
*/
    rPlayer.ReturnLastNormalMap();

    if(pMap)
    {
        _dwPlayerCnt = pMap->GetPlayerCount();
    }

    rPlayer.RemoveBuff(eWorldBossDeadBufferID); 
    rPlayer.RemoveBuff(eWorldBossSilverBufferID);
    rPlayer.RemoveBuff(eWorldBossGoldBufferID);
 
    if(GetStatus()==eDayActivityStatusEnd)
    {
   }
    if(pMap)
        pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));
 
    return true;

}
    //排行榜
void CWorldBossMgr::OnGetTopList(CPlayer& rPlayer)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnGetTopList";

    NBossProt::TVecPlayerInfo vecInfo;
    for(size_t i = 0; i < _vecBossPlayerInfoPtr.size(); ++i)
    {
        SBossPlayerInfoPtr pBossPlayerInfo = _vecBossPlayerInfoPtr[i];
        if(NULL == pBossPlayerInfo)
        {
            LOG_CRI<<"Unkown Error!";
            continue;
        }
        NBossProt::SPlayerInfo oInfo;
        oInfo.dwNo = pBossPlayerInfo->dwNo;
        oInfo.qwUserID = pBossPlayerInfo->qwUserID;
        oInfo.strUserName = pBossPlayerInfo->strName;
        oInfo.dwDamageHP = pBossPlayerInfo->dwScore;
        oInfo.dwBossMaxHP = _dwMaxHP; 
        vecInfo.push_back(oInfo);
    }

    rPlayer.SendPkg(g_BossProtS.BuildPkg_TopListNotify(vecInfo));

}

//个人信息
void CWorldBossMgr::OnGetSelfInfo(CPlayer& rPlayer)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnGetSelfInfo";

    NBossProt::SPlayerInfo oSelfInfo;
    oSelfInfo.qwUserID = rPlayer.GetUserID();
    oSelfInfo.strUserName = rPlayer.GetName();
    oSelfInfo.dwBossMaxHP = _dwMaxHP;
    UINT32 dwReliveTime = 0;
    UINT32 dwSliverBuffCdTime = 0;
    UINT32 dwSilverBufferCnt = 0;
    UINT32 dwGoldBufferCnt = 0;
    UINT32 dwAttackCnt = 0;

    SBossPlayerInfoPtr pBossPlayerInfo = GetPlayerInfo(rPlayer.GetUserID());
    if(NULL != pBossPlayerInfo)
    {
       oSelfInfo.dwNo = pBossPlayerInfo->dwNo;
       oSelfInfo.dwDamageHP = pBossPlayerInfo->dwScore;
       dwReliveTime  = pBossPlayerInfo->dwReliveTime;
       dwSliverBuffCdTime = pBossPlayerInfo->dwSilverBufferCdTime;
       dwSilverBufferCnt = pBossPlayerInfo->dwSilverBufferCnt;
       dwGoldBufferCnt = pBossPlayerInfo->dwGoldBufferCnt;
       dwAttackCnt = pBossPlayerInfo->dwAttackCnt;

    }
    if(_bLog)
    {
        LOG_INF<<"dwGoldBufferCnt:"<<dwGoldBufferCnt;
    }
   
   rPlayer.SendPkg(g_BossProtS.BuildPkg_SelfInfoNotify(oSelfInfo,_dwBeginTime,_dwEndTime,dwReliveTime,dwSliverBuffCdTime,dwSilverBufferCnt,dwGoldBufferCnt,dwAttackCnt));

}

void CWorldBossMgr::PrintBossInfo(CPlayer& rPlayer)
{
    auto itr = _mapBossInfo.find(_dwBoosID);
    if(itr != _mapBossInfo.end())
    {
        char szTmp[1024];
        memset(szTmp,0,sizeof(szTmp));
   
        sprintf(szTmp,"maxhp:%u,watk:%d,matk:%d",itr->second.dwHP,itr->second.dwAtk,itr->second.dwMAtk);
   
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgNotify(eChannelAll,szTmp,eSubNone));
        LOG_INF<< "PrintBossInfo" << szTmp;

        SSenderInfo oSenderInfo;
        CUser&  rUser = rPlayer.GetUser();
        oSenderInfo.qwUsrID = rUser.GetUserID();
        oSenderInfo.strName = rUser.GetFixdUserName();
        oSenderInfo.byNation = rUser.GetNation();
        oSenderInfo.byQuality = rUser.GetPlayer()->GetColor();
        TVecShowInfo vecShowInfo;
        ostringstream strInfo;
        strInfo << szTmp;
        string strData = g_ChatProtS.BuildPkg_ChatInfoNotify(eChannelSys, oSenderInfo, strInfo.str(), vecShowInfo);
        rPlayer.SendPkg(strData);
   
    }
}

//boss信息
void CWorldBossMgr::OnGetBossInfo(CPlayer& rPlayer)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnGetBossInfo";

    //if(!_qwMonsterID)
    //{
    //    return;
   // }

    rPlayer.SendPkg(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));

}


void CWorldBossMgr::BossAppear(UINT16 wBossID)
{
    if (_qwMonsterID)
        return;

    SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(wBossID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << wBossID << " .";
        return;
    }

    LOG_CRI << "WORLDBOSS APPEAR.";
    _pMap = CMapMgr::GetMap(pCfg->_MapId);

    CGameMapPtr pMap = GetMap();
    if (NULL == pMap)
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return;
    }

    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(wBossID);
    if(NULL == pMstGroup)
    {
        LOG_CRI << "Can't find wBossID: " << wBossID;
        return;
    }
    else
    {
        CMonsterPtr pMonster = CMonsterMgr::CreateMonster(pMstGroup->_MainMonster,pMstGroup->_Name);
        if(pMonster != NULL)
        {
            pMonster->SetGroupID(wBossID);	

            CWorldBoss* pWorldBoss = (CWorldBoss*)(pMonster.get());

            auto itr = _mapBossInfo.find(wBossID);
            if(itr != _mapBossInfo.end())
            {
                if(itr->second.dwAtk < WORLDBOSS_MIN_ATK)
                {
                    LOG_CRI<<"too small atk:"<<itr->second.dwAtk;
                    itr->second.dwAtk = WORLDBOSS_MIN_ATK;
                }

                pWorldBoss->SetMaxHP(itr->second.dwHP);
                pWorldBoss->SetLastHP(itr->second.dwHP);
                pWorldBoss->SetLastAtk(itr->second.dwAtk);
                pWorldBoss->SetLastMAtk(itr->second.dwMAtk);
            }
            else
            {
                //pWorldBoss->SetMaxHP(WORLDBOSS_MIN_HP);
                //pWorldBoss->SetLastHP(WORLDBOSS_MIN_HP);
                pWorldBoss->SetLastAtk(50000);
                pWorldBoss->SetLastMAtk(50000);

            }

            _dwMaxHP = pWorldBoss->GetMaxHP();
            _dwCurHP = _dwMaxHP;

            pWorldBoss->SetHP(_dwMaxHP);

            LOG_INF<<"boss appear: _dwMaxHP: "<<_dwMaxHP<<"Atk:"<<pWorldBoss->GetLastAtk()<<" wBossID: "<<wBossID;

            pWorldBoss->SetDir(3.14*3/4);

            pMap->MonsterEnter(*pMonster, &pCfg->pos);
            _qwMonsterID = pMonster->GetCreatureID();

            _dwAppearTime = time(NULL);

            if(pMap)
            {
               pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));
            }
 

        }
        else
        {
            LOG_CRI << "Map ID: " << pMap->GetMapID() << " MonsterID: " << wBossID << " is NULL!";
            return ;
        }
    }

    //_mapBossInfo.find(wBossID);

    // 修改地图阻挡点

    _bDisappered = false;
}

void CWorldBossMgr::BossDisappear()
{
    // XXX: Clear Boss
    if (_qwMonsterID)
    {
        CGameMapPtr pMap = GetMap();
        if(NULL == pMap)
            return;
        CMonsterPtr pMonster = pMap->GetMonster(_qwMonsterID); 
        if (pMonster)
            ClearMap(*pMonster);

       _qwMonsterID = 0;
    }

    //结束事件

}

void CWorldBossMgr::ChangeBossHp(UINT32 dwHP)
{
    // XXX: Clear Boss
    if (_qwMonsterID)
    {
        CGameMapPtr pMap = GetMap();
        if(NULL == pMap)
            return;
        CMonsterPtr pMonster = pMap->GetMonster(_qwMonsterID); 
        if (pMonster)
        {
            CWorldBoss* pWorldBoss = (CWorldBoss*)(pMonster.get());
            pWorldBoss->SetHP(dwHP);
        }

    }

    //结束事件

}

void CWorldBossMgr::OnDead(CCreature& rBoss, CCreature& rKiller)
{
    CPlayer& rPlayer = (CPlayer&)rKiller;
    CMonster& rMonster = (CMonster&)rBoss;

    _qwLastKillID = rPlayer.GetUserID();

    SaveBoss(rBoss);
    
    //Reward(rKiller);
    
    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(_dwBoosID);
        CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_WorldBossKill,vecParam);
    }

    SFighterPropCFG& rPropCFG = rMonster.GetFighterPropCfg();
     
    UINT32 dwMsg = eMsgWorldBossLastHit;
    if(eWorldBossID1545 == _dwBoosID)
    {
           dwMsg = eMsgWorldBossLastHit2;
    }
    g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,dwMsg,BuildStrVec(rPlayer.GetColor(),rPlayer.GetName(),rPropCFG._Color,rMonster.GetName()));


    OnEnd();
    if(_bLog)
    {
        LOG_INF<<"OnDead!!!";
    }

}

void CWorldBossMgr::ClearMap(CCreature& rBoss)
{
    SaveBoss(rBoss);
    
    CGameMapPtr pMap = GetMap();
    
    if(NULL == pMap)
         return;
 
    //LOG_CRI << __PRETTY_FUNCTION__;
    // XXX: clear boss
    if (pMap)
    {

        if (!pMap->MonsterDisappearByID(rBoss.GetCreatureID()))
            LOG_CRI << "WORLDBOSS CLEAR ERROR.";
        else
            LOG_CRI << "WORLDBOSS CLEAR SUCC.";
    }
    // XXX: clear all user
}

void CWorldBossMgr::Reward(CCreature& rKiller)
{
    LOG_CRI << __PRETTY_FUNCTION__;
}

void CWorldBossMgr::BossHPNotify(FLOAT fPercent, UINT32 dwHP, UINT32 dwDmgHP)
{
    if (!((int)fPercent%10) || ((int)fPercent) == 5)
    {
    }
}

SWorldBossPrizeCFGExPtr CWorldBossMgr::GetPrize(UINT32 dwPrizeType, UINT32 dwTopIndex)
{
    for(size_t i=0; i < _vecWorldBossPrizeCFGExPtr.size(); i++)
    {
        SWorldBossPrizeCFGExPtr pWorldBossPrizeCFGE = _vecWorldBossPrizeCFGExPtr[i];
        if(pWorldBossPrizeCFGE)
        {
            if(_dwBoosID != pWorldBossPrizeCFGE->_BossID)
                continue;

            if(pWorldBossPrizeCFGE->_PrizeType != dwPrizeType)
            {
                continue;
            }

            if(dwTopIndex>pWorldBossPrizeCFGE->_RankTop && dwTopIndex <= pWorldBossPrizeCFGE->_RankBottom)
            {
                return pWorldBossPrizeCFGE;

            }
        }
    }

    return NULL;
}

void CWorldBossMgr::GetCFGMailItem(SWorldBossPrizeCFGExPtr pWorldBossPrizeCFGEx, UINT32 dwPlayerLevel, TVecItemGenInfo& vecItems)
{
    if(NULL == pWorldBossPrizeCFGEx)
    {
        return;
    }

    vecItems = pWorldBossPrizeCFGEx->_vecItemGenInfo;

    //银币
    if(pWorldBossPrizeCFGEx->_ResourceValue1)
    {
    SItemGenInfo stItemGen;
    stItemGen.wItemID = 2;
    stItemGen.dwCount = pWorldBossPrizeCFGEx->_ResourceValue1;
    stItemGen.eBindType = eBindGet;
    vecItems.push_back(stItemGen);
 
    }

    //荣誉
    if(pWorldBossPrizeCFGEx->_ResourceValue2)
    {
    SItemGenInfo stItemGen;
    stItemGen.wItemID = 8;
    stItemGen.dwCount = pWorldBossPrizeCFGEx->_ResourceValue2;
    stItemGen.eBindType = eBindGet;
    vecItems.push_back(stItemGen);
    }

    FLOAT fLevelRate = CExpMgr::GetWBossPrizeRate(dwPlayerLevel);
    for(auto itr = vecItems.begin(); itr != vecItems.end(); itr++)
    {
        itr->dwCount *= fLevelRate;

        if(itr->dwCount < 1)
        {
            itr->dwCount = 1;
        }

    }
}

void CWorldBossMgr::KickAllPlayer()
{
    CGameMapPtr pMap = GetMap();
    if(NULL == pMap)
        return;
 
    if(pMap)
    {
        const TMapID2Player& mapPlayer = pMap->GetPlayerMap();
        for(auto itr = mapPlayer.begin(); itr != mapPlayer.end();)
        {
            CPlayerPtr pPlayer = itr->second.lock();
            ++itr;
            if(pPlayer)
            {
                OnLeaveMap(*pPlayer);
            }

        }
    }
}

SBossPlayerInfoPtr CWorldBossMgr::GetPlayerInfo(UINT64 qwUserID)
{
    auto itr =  _mapBossPlayerInfoPtr.find(qwUserID);
    if(itr != _mapBossPlayerInfoPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

/*
void CWorldBossMgr::SendMailPrize(SWorldBossPrizeCFGExPtr pWorldBossPrizeCFGEx,UINT32 dwSendID,UINT32 dwTitleID)
{
           //发送邮件
        
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_SHUSHANBATTLE;
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byTotalWin));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byTotalLose));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byMaxKill));
        stBody.vecParam.push_back(NumberToString(byCount));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_wHonor));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byHonorLvl));
        
        TVecUINT64 vecTargets;
        vecTargets.push_back(iter->first);
        GameServerSysMail::SendSysMail(SEND_SHUSHANBATTLE, TITLE_SHUSHANBATTLE, stBody, vecTargets, &vecItems);


}
*/

/////////////////////////
bool CWorldBossMgr::OnAlarm()
{
    bool bRet = CDayActivity::OnAlarm();
    if(!bRet)
    {
        return false;
    }
    
    ClearEvent();

    //AddEvent(eWorldBossEvent_10Tip,_dwReadyTime,10);
    AddEvent(eWorldBossEvent_5Tip,_dwBeginTime - 5*60,5);
    AddEvent(eWorldBossEvent_3Tip,_dwBeginTime - 3*60,3);
    AddEvent(eWorldBossEvent_2Tip,_dwBeginTime - 2*60,2);
    AddEvent(eWorldBossEvent_1Tip,_dwBeginTime - 1*60,1);

    UINT32 dwAttackCd = 2*60;
    AddPeriodEvent(eWorldBossEvent_NPC_ATTACK,_dwBeginTime,100,dwAttackCd);

    if(_dwParam)
        _dwBoosID = _dwParam;
    
    SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return false;
    }

    LOG_CRI << "WORLDBOSS APPEAR.";
    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    if (NULL == GetMap())
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return false;
    }

    return true;


    //AddPeriodEvent(eWorldBossEvent_PlayerCnt,_dwReadyTime,0xFFFFF,5);

}

void CWorldBossMgr::OnReady()
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnReady";
    CDayActivity::OnReady();
    
    SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return;
    }

    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    CGameMapPtr pMap = GetMap(); 
    if (NULL == pMap)
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return;
    }

    if(pMap)
    {
        pMap->ClearAllBlockers();
    }


    //创建阻挡点
    bool bRet = pMap->CreateBlockByIndex(eWorldBossBlockID);
    if(!bRet)
    {
        LOG_CRI<<"CWorldBossMgr CreateBlockByIndex failed!! ";
    }

    bRet = pMap->CreateBlockByIndex(eWorldBossBlockID+1); 
    if(!bRet)
    {
        LOG_CRI<<"CWorldBossMgr CreateBlockByIndex failed!! ";
    }

    //清理数据
    _mapBossPlayerInfoPtr.clear();
    _vecBossPlayerInfoPtr.clear();

    auto itr = _mapBossInfo.find(_dwBoosID);
    if(itr != _mapBossInfo.end())
    {
 /*       
        if(itr->second.dwHP <WORLDBOSS_MIN_HP)
        {
            itr->second.dwHP = WORLDBOSS_MIN_HP;
        }
        if(itr->second.dwAtk <10000)
        {
            itr->second.dwAtk = 10000;
        }

        if(itr->second.dwMAtk < 10000)
        {
            itr->second.dwMAtk = 10000;
        }
*/
        _dwMaxHP = itr->second.dwHP;
        _dwCurHP = _dwMaxHP;
    }

    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgWorldBossReadyNow);

}

void CWorldBossMgr::OnBegin()
{
    CDayActivity::OnBegin();
    BossAppear(_dwBoosID);
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgWorldBossBegin);

    _dwMessageHpRate = 100;

    _vecDamageRatePrize.clear();

    //_dwNPCLevel = random()%5 + 1;
    _dwNPCLevel = 1;
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnBegin: _dwNPCLevel: "<<_dwNPCLevel;


    _pNpcPrize = GetPrize(eWorldBossPrizeNPC,_dwNPCLevel); 
    if(NULL == _pNpcPrize)
    {
        LOG_CRI<<"null _pNpcPrize: "<<_dwNPCLevel;
    }
    _pKillPrize = GetPrize(eWorldBossPrizeKillBoss);

    
    
    CGameMapPtr pMap = GetMap();
    if(pMap)
    {
        pMap->ClearAllBlockers();
    }

}

void CWorldBossMgr::OnEnd()
{
    CDayActivity::OnEnd();
    
    BossDisappear();
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgWorldBossEnd);

    ClearEvent(eWorldBossEvent_NPC_ATTACK);


    UpdateTopList(true);

    UINT32 dwKickTime = 30;
    UINT32 dwEndTime = time(NULL)+dwKickTime;

    AddEvent(eWorldBossEvent_KickPlayer,dwEndTime);

    CGameMapPtr pMap = GetMap();
    if(pMap)
    {
        pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_EndNotify(dwEndTime));
    }
 

}

void CWorldBossMgr::OnEvent(SActEventData& oSActEventData)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnEvent: "<<oSActEventData.dwEventID;

    CGameMapPtr pMap = GetMap();
    switch(oSActEventData.dwEventID)
    {
        case eWorldBossEvent_10Tip:
        case eWorldBossEvent_5Tip:
        case eWorldBossEvent_3Tip:
        case eWorldBossEvent_2Tip:
        case eWorldBossEvent_1Tip:
            {
                LOG_INF<<"BOSS TIP: "<<oSActEventData.dwParam;
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgWorldBossTip,BuildStrVec(oSActEventData.dwParam));
            }
            break;
        case eWorldBossEvent_NPC_ATTACK: //此功能暂时不用
            {
                /*
                LOG_INF<<"NPC ATTACK BOSS!!!!";
                 if (_qwMonsterID)
                  {
                      CMonsterPtr pMonster = _pMap->GetMonster(_qwMonsterID); 
                      if (pMonster)
                      {
                          TVecUINT32 vecParam;
                          vecParam.push_back(1001);
                          pMonster->SetBuff(eWorldBossNpcBufferID,vecParam,30);
                      }
                  }
                  */
        

            }
            break;
        case eWorldBossEvent_KickPlayer:
            {
                KickAllPlayer();
            }
            break;
        case eWorldBossEvent_PlayerCnt:
            {
                if(_dwNotifyPlayerCnt != _dwPlayerCnt)
                {
                    _dwNotifyPlayerCnt = _dwPlayerCnt;
                if(pMap)
                    pMap->NotifyAllMapPlayer(g_BossProtS.BuildPkg_BossInfoNotify(_dwBoosID,_dwCurHP,_dwMaxHP,_dwPlayerCnt));
                }
            }
            break;
        default:
            {
            }
            break;
    }

}

bool CWorldBossMgr::GMOpen()
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::GMOpen";
   
   if(GetStatus()==eDayActivityStatusReady || GetStatus() == eDayActivityStatusProcess)
   {
       return false;
   }

   _dwBoosID = GetParam();
    
   SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return false;
    }

    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    if (!GetMap())
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return false;
    }


   time_t tNow = time(NULL);
   _dwAlarmTime = tNow;
   _dwReadyTime = tNow;
   _dwBeginTime = tNow + 10*60;  //
   _dwEndTime   = tNow + 70*60; //

   //test
   _dwBeginTime = tNow + 30;
   _dwEndTime   = tNow + 600;

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);

   AddEvent(eWorldBossEvent_10Tip,_dwReadyTime,10);
   AddEvent(eWorldBossEvent_5Tip,_dwReadyTime + 5*60,5);
   AddEvent(eWorldBossEvent_3Tip,_dwReadyTime + 7*60,3);
   AddEvent(eWorldBossEvent_2Tip,_dwReadyTime + 8*60,2);
   AddEvent(eWorldBossEvent_1Tip,_dwReadyTime + 9*60,1);

  
   UINT32 dwAttackCd = 2*60;
   AddPeriodEvent(eWorldBossEvent_NPC_ATTACK,_dwBeginTime,100,dwAttackCd);
   //AddPeriodEvent(eWorldBossEvent_PlayerCnt,_dwReadyTime,0xFFFFF,5);
   return true;
}

void CWorldBossMgr::GMOpenBoss(UINT32 dwBossID,UINT32 dwProcessTime /* = 33600 */)
{
   if(_bLog)
        LOG_INF<<"CWorldBossMgr::GMOpen";
   
   if(GetStatus()==eDayActivityStatusReady || GetStatus() == eDayActivityStatusProcess)
   {
       return;
   }

    
   SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return;
    }

    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    if (!GetMap())
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return;
    }


   time_t tNow = time(NULL);
   _dwAlarmTime = tNow;
   _dwReadyTime = tNow;
   _dwBeginTime = tNow + 10*60;  //
   _dwEndTime   = _dwBeginTime + dwProcessTime; //

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);

   AddEvent(eWorldBossEvent_10Tip,_dwReadyTime,10);
   AddEvent(eWorldBossEvent_5Tip,_dwReadyTime + 5*60,5);
   AddEvent(eWorldBossEvent_3Tip,_dwReadyTime + 7*60,3);
   AddEvent(eWorldBossEvent_2Tip,_dwReadyTime + 8*60,2);
   AddEvent(eWorldBossEvent_1Tip,_dwReadyTime + 9*60,1);

  
   UINT32 dwAttackCd = 2*60;
   AddPeriodEvent(eWorldBossEvent_NPC_ATTACK,_dwBeginTime,100,dwAttackCd);

}

//服务器重启活动处理
void CWorldBossMgr::OnReBegin()
{

    CDayActivity::OnAlarm();
    
    if(_dwParam)
        _dwBoosID = _dwParam;


    auto itr = _mapBossInfo.find(_dwBoosID);
    if(itr != _mapBossInfo.end())
    {

        LOG_INF<<"worldboss OnReBegin boss has killed!!!"<<_dwBeginTime<<"-"<<_dwEndTime<<"|"<<itr->second.dwLastEndTime;
        if(itr->second.dwLastEndTime>_dwBeginTime && itr->second.dwLastEndTime<=_dwEndTime)
        {
            SetStatus(eDayActivityStatusEnd);
            return;
        }
    }
    else
    {
        LOG_INF<<"not find boss!!!";
    }

    LOG_INF<<"worldboss OnReBegin!!!!!";

    //test
    _dwAlarmTimeSpan = 0;
    _dwReadyTimeSpan = 30;
    _dwProcessTimeSpan = 600;

 
    _dwAlarmTime = time(NULL);
    _dwReadyTime = _dwAlarmTime + _dwAlarmTimeSpan;
    _dwBeginTime = _dwReadyTime + _dwReadyTimeSpan;
    _dwEndTime   = _dwBeginTime + _dwProcessTimeSpan; 
    ClearEvent();
    SetStatus(eDayActivityStatusReady);

    AddEvent(eWorldBossEvent_10Tip,_dwReadyTime,10);
    AddEvent(eWorldBossEvent_5Tip,_dwReadyTime + 5*60,5);
    AddEvent(eWorldBossEvent_3Tip,_dwReadyTime + 7*60,3);
    AddEvent(eWorldBossEvent_2Tip,_dwReadyTime + 8*60,2);
    AddEvent(eWorldBossEvent_1Tip,_dwReadyTime + 9*60,1);
    
    UINT32 dwAttackCd = 2*60;
    AddPeriodEvent(eWorldBossEvent_NPC_ATTACK,_dwBeginTime,100,dwAttackCd);

    SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return;
    }

    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    if (!GetMap())
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return;
    }



}

bool CWorldBossMgr::OpenActivity(UINT32 dwBegin,UINT32 dwEnd)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::GMOpen";
   
   if(GetStatus()==eDayActivityStatusReady || GetStatus() == eDayActivityStatusProcess)
   {
       return false;
   }

   SWorldBossCFGEx* pCfg = CMonsterMgr::GetWorldBossCfg(_dwBoosID);
    if (!pCfg)
    {
        LOG_CRI << "WORLDBOSS CFG ERROR => " << _dwBoosID << " .";
        return false;
    }

    _pMap = CMapMgr::GetMap(pCfg->_MapId);
    if (!GetMap())
    {
        LOG_CRI << "WORLDBOSS MAP ERROR.";
        return false;
    }

   _dwAlarmTime = dwBegin;
   _dwReadyTime = dwBegin;
   _dwBeginTime = dwBegin;  
   _dwEndTime   = dwEnd; 

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);
  
   UINT32 dwAttackCd = 2*60;
   AddPeriodEvent(eWorldBossEvent_NPC_ATTACK,_dwBeginTime,100,dwAttackCd);
   return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

