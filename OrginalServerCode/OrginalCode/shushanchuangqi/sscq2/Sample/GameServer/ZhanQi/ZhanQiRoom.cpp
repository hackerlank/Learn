#include "stdafx.h"
#include "ZhanQiRoom.h"
#include "Player.h"
#include "User.h"
#include "SysMsgDefine.h"
#include "ItemMgr.h"
#include "Monster.h"
#include "MonsterMgr.h"
#include "VIPMgr.h"
#include "HeroFighter.h"
#include "FighterManager.h"
#include "FightHeroInfoMgr.h"
#include "FightFormationMgr.h"
#include "GUIDMgr.h"

CZhanQiRoom::CZhanQiRoom()
{
    _dwRoomID          = 0;
    _dwMoveEndTime     = 0;
    _wTurns            = 0;
    _wFreshTurn        = 0;
    _bAllOver          = false;
    _eStatus           = eZhanQiRoomStatus_Init;
    _dwNextStatusTime  = 0;
    _wFreshPlayCnt     = 1;
    _wMaxFreshTurn     = 3;
    
}

//玩家 初始玩家队列
bool  CZhanQiRoom::StartGame(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,TVecUINT16& vecInitPath,UINT16 dwMapSize)
{
    if(vecZhanQiPlayerPtr.size() > vecInitPath.size())
    {
        LOG_CRI<<"vecInitPath too small!!!";
        return false;
    }

    if(0 == dwMapSize)
    {
        LOG_CRI<<"Error 0 == dwMapSize";
        return false;
    }

    LOG_INF<<"StartGame dwMapSize:"<<dwMapSize;

    SLingShanCFGExPtr pLingShanCFGEx =  g_ZhanQiMgr.GetCurLingShanCFG();
    if(NULL == pLingShanCFGEx)
        return false;

    //大宝箱初始化位置
    _wGodBoxPos = pLingShanCFGEx->_BornBigID;

    _dwNormalBoxModelID = pLingShanCFGEx->_NormalBoxModelID;

    _dwGodBoxModelID  = pLingShanCFGEx->_GodBoxModelID;

    _wMaxFreshTurn    = pLingShanCFGEx->_SpawPlayerTurns;

    _wFreshPlayCnt    = pLingShanCFGEx->_SpawPlayerCnt;

    LOG_INF<<"BOX model:"<<pLingShanCFGEx->_NormalBoxModelID<<"God Box:"<<pLingShanCFGEx->_GodBoxModelID;


    _bAllOver = false;

    //配置地图格子
    _vecMapGrid.resize(dwMapSize);

    for(size_t i=0; i<vecZhanQiPlayerPtr.size(); i++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = vecZhanQiPlayerPtr[i];
        if(NULL == pZhanQiPlayer)
            continue;
        if(!PutObjIntoGrid(pZhanQiPlayer,vecInitPath[i],false))
        {
            return false;
        }
    }

    //刷新大宝箱
    OnSpawGodBox(); 

    //刷新普通宝箱
    OnSpawBox();

    //notify player
    SetStatus(eZhanQiRoomStatus_GameStart);

    //1秒开始时间
    _dwNextStatusTime = time(NULL);

    return true;
}

//把玩家放入格子
bool  CZhanQiRoom::PutObjIntoGrid(SZhanQiObjPtr pZhanQiObjPtr, UINT16 wPos,bool bCollide)
{
    if(NULL == pZhanQiObjPtr)
    {
        LOG_CRI<<"NULL == pZhanQiPlayer";
        return false;
    }

    if(0 == wPos)
    {
        LOG_CRI<<"0 == wPos";
        return false;
    }
    
    //取当前活动配置地图
    // TVecLingShanMapCFGExPtr& g_ZhanQiMgr.GetCurMapCFG();

    if(wPos >= _vecMapGrid.size())
    {
        LOG_CRI<<"Error wPos:"<<wPos<<" MapSize:"<<_vecMapGrid.size();
        return false;
    }

    pZhanQiObjPtr->wSrcID = wPos;

    if(pZhanQiObjPtr->IsObj(eZhanQiObjType_Player))
    {
        SZhanQiPlayerPtr pZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pZhanQiObjPtr);
        if(pZhanQiPlayer)
        {
            pZhanQiPlayer->dwRoomID = GetRoomID();
            pZhanQiPlayer->fHPRate = 1.0;  //满血复活
            pZhanQiPlayer->dwSelfTurns = 1; //第1回合;
            CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
            if(pPlayer)
            {
                LOG_INF<<"clear db!!!!";
                CFightFormationMgrPtr pFightFormationMgr = pPlayer->GetFightFormationMgr();
                if(pFightFormationMgr)
                {
                    pFightFormationMgr->ClearFormation(EBLingshan);
                }

                if (pPlayer->GetFightHeroInfoMgr())
                    pPlayer->GetFightHeroInfoMgr()->ClearByBattleType(EBLingshan);
 

            }

            pZhanQiPlayer->vecTakePrizeLog.clear();

            _mapZhanQiPlayerPtr.insert(make_pair(pZhanQiPlayer->qwRoleID,pZhanQiPlayer));
            LOG_INF<<"EnterRoom:"<<GetRoomID()<<" qwRoleID"<<pZhanQiPlayer->qwRoleID<<" wPos:"<<wPos;
        }
        else
        {
            LOG_CRI<<"unkown error!~!";
        }
    }

    _vecMapGrid[wPos].pZhanQiObjPtr = pZhanQiObjPtr;

   return true;
}


//进入新的玩家
void CZhanQiRoom::Push_Player(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,TVecUINT16& vecEmptyPos)
{
    if(vecEmptyPos.size() < vecZhanQiPlayerPtr.size())
    {
        return;
    }

    for(size_t i=0;i < vecZhanQiPlayerPtr.size();i++)
    {
        if(vecZhanQiPlayerPtr[i])
        {
            vecZhanQiPlayerPtr[i]->wSrcID = vecEmptyPos[i];
            PutObjIntoGrid(vecZhanQiPlayerPtr[i],vecEmptyPos[i],false);
        }
    }
}

//玩家移动
ELingShanOP  CZhanQiRoom::OnMove(SZhanQiPlayerPtr pZhanQiPlayer,UINT16 wPos)
{
    if(NULL == pZhanQiPlayer)
    {
        return eLingShanOP_Fail;
    }

    if(eZhanQiRoomStatus_Move != _eStatus)
    {
        LOG_CRI<<"unmove status!";
        return eLingShanOP_NoMove;
    }

    auto itr = _mapZhanQiPlayerPtr.find(pZhanQiPlayer->qwRoleID);
    if(itr == _mapZhanQiPlayerPtr.end())
    {
        LOG_CRI<<"Unkown Error!!!";
        return eLingShanOP_Fail;
    }


    SLingShanMapCFGExPtr pLingShanMapCFGEx = GetPlayerCurGridCFG(pZhanQiPlayer);
    if(NULL == pLingShanMapCFGEx)
    {
        LOG_CRI<<"eLingShanOP_MapCFG";
        return eLingShanOP_MapCFG;
    }

    //检查是否有路径
    if(pLingShanMapCFGEx->setPath.find(wPos) == pLingShanMapCFGEx->setPath.end())
    {
        return eLingShanOP_ErrorPath;
    }

    pZhanQiPlayer->wDstID = wPos;


    return eLingShanOP_Sucess;
}

//玩家模型改变
void  CZhanQiRoom::OnChangeModel(SZhanQiPlayerPtr pPlayer,UINT32 dwModelID)
{
    if(NULL == pPlayer)
        return;
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    GetAllVisitUser(vecUserID);
    if(!vecUserID.empty())
    g_LingShanProtS.SendClt_PlayerChangeModelNotify(vecUserID.data(),(UINT16)vecUserID.size(),pPlayer->qwRoleID,dwModelID,GetRoomID());

}


//当前棋盘信息
void CZhanQiRoom::OnGetMatchInfo(SZhanQiPlayerPtr pZhanQiPlayer,shared_func<CLingShanProtS::SGetMatchInfoAck>& fnAck)
{
    if(NULL == pZhanQiPlayer)
        return;
    for(size_t i = 1; i < _vecMapGrid.size(); i++)
    {
        SMapGrid& rGrid = _vecMapGrid[i];
        if(rGrid.pZhanQiObjPtr)
        {
            EZhanQiObjType eObjType = rGrid.pZhanQiObjPtr->eZhanQiObjType;
            switch(eObjType)
            {
                case eZhanQiObjType_Box:
                    {
                        SBoxInfo oBoxInfo;
                        oBoxInfo.wPos      = i;
                        if(rGrid.pZhanQiObjPtr->wGodBox)
                        {
                            oBoxInfo.dwModelID = _dwGodBoxModelID;
                        }
                        else
                        {
                            oBoxInfo.dwModelID = _dwNormalBoxModelID;
                        }
                        
                        fnAck->vecBoxInfo.push_back(oBoxInfo);
                    }
                    break;
                case eZhanQiObjType_Player:
                    {
                        SZhanQiPlayerPtr pPlayerObj = dynamic_pointer_cast<SZhanQiPlayer>(rGrid.pZhanQiObjPtr);
                        if(NULL == pPlayerObj)
                        {
                            continue;
                        }
                        SRoomPlayInfo oRoomPlayInfo;
                        oRoomPlayInfo.qwRoleID = pPlayerObj->qwRoleID;
                        oRoomPlayInfo.dwModelID = pPlayerObj->dwModelID;
                        oRoomPlayInfo.dwKillCnt = pPlayerObj->dwKillCnt;
                        oRoomPlayInfo.bGodBox   = pPlayerObj->wGodBox; 
                        oRoomPlayInfo.wPos      = i;
                        fnAck->vecRoomPlayInfo.push_back(oRoomPlayInfo);
                        //LOG_INF<<"Room:"<<GetRoomID()<<"qwRoleID:"<<pPlayerObj->qwRoleID<<" wPos:"<<i;
                    }
                    break;
                case eZhanQiObjType_Monster:
                    {
                    }
                    break;
                default:
                    {
                    }
                    break;
            }
        }
    }


    fnAck->wRoomID = GetRoomID();
    fnAck->dwFreshTurn = GetNexFreshTurns();
    fnAck->dwTurn      = _wTurns;
    GetRoomPlayerStatus(fnAck->eStatus,fnAck->dwParam);
    fnAck->dwTime = time(NULL);
    //fnAck->oPlayMovieInfo =_oSPlayMovieInfo;

    //if(0 == pZhanQiPlayer->GetVisitRoomID())
    //{
    //    fnAck->vecTakePrizeLog = pZhanQiPlayer->vecTakePrizeLog;
    //}

    //LOG_INF<<"player size:"<<fnAck->vecRoomPlayInfo.size()<<"eStatus:"<<fnAck->eStatus;
}

//
void CZhanQiRoom::OnChat(CPlayer& rPlayer,const std::string& strChatMsg)
{
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    GetAllVisitUser(vecUserID);
    if(!vecUserID.empty())
    {
       g_LingShanProtS.SendClt_ChatNotify(vecUserID.data(),(UINT16)vecUserID.size(),rPlayer.GetRoleID(),strChatMsg,GetRoomID());
    }

}

//进入参观房间
void CZhanQiRoom::OnEnterVisitRoom(SZhanQiPlayerPtr pPlayer)
{
    if(NULL == pPlayer)
        return;
    auto itr = _mapVisitPlayerPtr.find(pPlayer->qwRoleID);
    if(itr != _mapVisitPlayerPtr.end())
    {
        return;
    }

    _mapVisitPlayerPtr.insert(make_pair(pPlayer->qwRoleID,pPlayer));
}

//离开参观房间
void CZhanQiRoom::OnLeaveVisitRoom(SZhanQiPlayerPtr pPlayer)
{
    if(NULL == pPlayer)
        return;

    auto itr = _mapVisitPlayerPtr.find(pPlayer->qwRoleID);
    if(itr != _mapVisitPlayerPtr.end())
    {
        _mapVisitPlayerPtr.erase(itr);
    }

}

//接收：获取动画播放信息
ELingShanOP CZhanQiRoom::OnGetRoomPlayMovieInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetPlayMovieInfoAck> fnAck)
{
    fnAck->oPlayMovieInfo =_oSPlayMovieInfo;
    fnAck->wRoomID = GetRoomID();

    auto itr = _mapZhanQiPlayerPtr.find(rPlayer.GetRoleID());
    if(itr == _mapZhanQiPlayerPtr.end())
        return eLingShanOP_Sucess;

    fnAck->vecTakePrizeLog = itr->second->vecTakePrizeLog;
    fnAck->dwTurn      = _wTurns;
    return eLingShanOP_Sucess;
}



//刷新宝箱
void  CZhanQiRoom::OnSpawBox()
{
    //1号开始
    for(size_t i=1; i < _vecMapGrid.size(); i++)
    {
        SMapGrid& rMapGrid= _vecMapGrid[i];
        if(rMapGrid.pZhanQiObjPtr)
            continue;
        SZhanQiBoxPtr pZhanQiBox(new SZhanQiBox);
        rMapGrid.pZhanQiObjPtr = pZhanQiBox;
    }

}

//刷新大宝箱
bool  CZhanQiRoom::OnSpawGodBox()
{
    SZhanQiBoxPtr pZhanQiBox(new SZhanQiBox);
    pZhanQiBox->wGodBox = 1;
    return PutObjIntoGrid(pZhanQiBox,_wGodBoxPos,false);
}


//刷新怪物
void CZhanQiRoom::OnSpawMonster()
{
}

//玩家离开
void  CZhanQiRoom::OnPlayerLeave(SZhanQiPlayerPtr pZhanQiPlayer)
{
    CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pZhanQiPlayer->dwSelfTurns);
        pPlayer->OnEvent(eEventType_MysteryTreasureAliveTime,vecParam);
    }

    pZhanQiPlayer->ResetWait();
    g_ZhanQiMgr.PushWait(pZhanQiPlayer);
    LOG_INF<<"OnPlayerLeave Room:"<<GetRoomID()<<"qwRoleID:"<<pZhanQiPlayer->qwRoleID;
    
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    GetAllVisitUser(vecUserID);
    if(!vecUserID.empty())
    {
        g_LingShanProtS.SendClt_KickPlayerNotify(vecUserID.data(),(UINT16)vecUserID.size(),
                pZhanQiPlayer->qwRoleID,
                GetRoomID());
    }

}

void SetRandomDstPos(SZhanQiPlayerPtr pPlayer,TVecUINT16& vecPos)
{
    if(NULL == pPlayer)
        return;
    if(vecPos.empty())
        return;

    UINT32 wSelect = rand()%vecPos.size();
    pPlayer->wDstID = vecPos[wSelect];
    if(0 == pPlayer->wDstID)
    {
        LOG_CRI<<"SetRandomDstPos Error";
    }
    //LOG_INF<<"SetRandomDstPos:"<<vecPos[wSelect]<<"|size:"<<vecPos.size()<<"qwRoleID:"<<pPlayer->qwRoleID<<" wPos"<<pPlayer->wDstID;
}

//获取当前格子配置
SLingShanMapCFGExPtr CZhanQiRoom::GetPlayerCurGridCFG(SZhanQiObjPtr pZhanQiPlayer)
{
    TVecLingShanMapCFGExPtr& vecMapCfg = g_ZhanQiMgr.GetCurMapCFG();

    if(NULL == pZhanQiPlayer)
        return NULL;

    if(pZhanQiPlayer->wSrcID>= vecMapCfg.size())
    {
        LOG_CRI<<"Error wSrcID:"<<pZhanQiPlayer->wSrcID;
        return NULL;
    }

    SLingShanMapCFGExPtr pLingShanMapCFGEx = vecMapCfg[pZhanQiPlayer->wSrcID];

    return pLingShanMapCFGEx;
}


void  CZhanQiRoom::SetRandomMove(SZhanQiPlayerPtr pZhanQiPlayer,TVecLingShanMapCFGExPtr& vecMapCfg)
{
    if(NULL == pZhanQiPlayer)
        return;
    if(pZhanQiPlayer->wSrcID>= vecMapCfg.size())
    {
        LOG_CRI<<"Error wSrcID:"<<pZhanQiPlayer->wSrcID;
        return;
    }

    SLingShanMapCFGExPtr pLingShanMapCFGEx = vecMapCfg[pZhanQiPlayer->wSrcID];
    if(NULL == pLingShanMapCFGEx)
    {
        LOG_CRI<<"Error CFG:"<<pZhanQiPlayer->wSrcID;
        return;
    }

    TVecUINT16 vecBox;
    TVecUINT16 vecNormal;
    for(auto itr = pLingShanMapCFGEx->setPath.begin(); itr != pLingShanMapCFGEx->setPath.end(); itr++)
    {
        if(*itr >= _vecMapGrid.size())
        {
            LOG_CRI<<"path error!!:"<<*itr;
            continue;
        }
        SZhanQiObjPtr pObj = _vecMapGrid[*itr].pZhanQiObjPtr;
        if(pObj&&pObj->IsObj(eZhanQiObjType_Box))
        {
            vecBox.push_back(*itr);
        }
        else
        {
            vecNormal.push_back(*itr);
        }
    }

    if(vecBox.empty())
    {
        SetRandomDstPos(pZhanQiPlayer,vecNormal);

    }
    else
    {
        SetRandomDstPos(pZhanQiPlayer,vecBox);
    }

    if(0 == pZhanQiPlayer->wDstID)
    {
        LOG_CRI<<"random error !!!";
    }
}

//未移动的玩家或怪物移动
void CZhanQiRoom::CheckRandomMove()
{
    TVecLingShanMapCFGExPtr& vecMapCfg = g_ZhanQiMgr.GetCurMapCFG();

    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(pZhanQiPlayer)
        {
            if(pZhanQiPlayer->wDstID)
                continue;
            SetRandomMove(pZhanQiPlayer,vecMapCfg);
        }
    }
}

//路径相遇检测
void  CZhanQiRoom::OnMovePathCheck()
{
    _mapSamePathObjPtr.clear();

    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            continue;
        }

        if(0 == pZhanQiPlayer->wSrcID || 0 == pZhanQiPlayer->wDstID)
        {
            LOG_CRI<<"Unkown Error Pos qwRoleID:"<<pZhanQiPlayer->qwRoleID;
            continue;
        }

        if(pZhanQiPlayer->wSrcID == pZhanQiPlayer->wDstID)
        {
            LOG_CRI<<"Same Pos qwRoleID:"<<pZhanQiPlayer->qwRoleID;
            continue;
        }

        UINT16 wMinPos = 0;
        UINT16 wMaxPos = 0;
        if(pZhanQiPlayer->wSrcID > pZhanQiPlayer->wDstID)
        {
            wMinPos = pZhanQiPlayer->wDstID;
            wMaxPos = pZhanQiPlayer->wSrcID;
        }
        else
        {
            wMinPos = pZhanQiPlayer->wSrcID;
            wMaxPos = pZhanQiPlayer->wDstID;
        }

        UINT32 dwPath = wMaxPos*1000 + wMinPos;

        SCollideObj& rCollideObj = _mapSamePathObjPtr[dwPath];
        rCollideObj.vecZhanQiObjPtr.push_back(pZhanQiPlayer);
    }
}

//在同一个格子检查
void  CZhanQiRoom::OnSameGridCheck()
{
    _mapSameGridObjPtr.clear();
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            continue;
        }

        if(0 == pZhanQiPlayer->wSrcID || 0 == pZhanQiPlayer->wDstID)
        {
            LOG_CRI<<"Unkown Error Pos qwRoleID:"<<pZhanQiPlayer->qwRoleID;
            continue;
        }

        if(pZhanQiPlayer->wSrcID == pZhanQiPlayer->wDstID)
        {
            LOG_CRI<<"Same Pos qwRoleID:"<<pZhanQiPlayer->qwRoleID;

        }

        SCollideObj& rCollideObj = _mapSameGridObjPtr[pZhanQiPlayer->wDstID];
        if(0 == pZhanQiPlayer->byFail)
        {
            rCollideObj.vecZhanQiObjPtr.push_back(pZhanQiPlayer);
        }
    }
}

void PutPlayer(IBattleSimulatorPtr pBS,CPlayerPtr pAtkPlayer,UINT8 bySide,TVecBattleFighterPtr& rvecBattleFighter)
{
    if(NULL == pBS || NULL == pAtkPlayer)
        return;
    pAtkPlayer->GetBattleFighterList(rvecBattleFighter,EBLingshan);
    TVecUINT16 vecFighterID;
    for (size_t i=0;i < rvecBattleFighter.size(); i++)
    {
        //死的不加载技能
        if(rvecBattleFighter[i]->GetHP())
        {
            CFighterPtr pFigter = pAtkPlayer->GetFighterByInstID(rvecBattleFighter[i]->GetInstID()); 
            if(pFigter)
                vecFighterID.push_back(pFigter->GetID());
        }
    }

    pAtkPlayer->GetFighterManager()->ResetCombinationSkill(vecFighterID,eCombEquipToEMei);

    pBS->PutFighters(bySide,pAtkPlayer->GetMainFighter()->GetInstID(), pAtkPlayer->GetLevel(),rvecBattleFighter, pAtkPlayer->GetRoleID(), false, pAtkPlayer->GetAppearFeature());
}

void RestorHP(TVecBattleFighterPtr& vecBattleFighter,float fRate)
{
        for(size_t i = 0; i < vecBattleFighter.size(); i++)
        {
            IBattleFighterPtr pBattleFighter = vecBattleFighter[i];
            if(pBattleFighter)
            {
                if(pBattleFighter->GetHP())
                {
                    UINT32 dwHp = pBattleFighter->GetHP() + pBattleFighter->GetMaxHP() * fRate;
                    pBattleFighter->SetHP(dwHp);
                }
            }
        }
}

float GetHPRate(TVecBattleFighterPtr& vecBattleFighter)
{
    UINT32 dwMaxHP = 0;
    UINT32 dwHp    = 0;
    for(size_t i = 0; i < vecBattleFighter.size(); i++)
    {
        IBattleFighterPtr pBattleFighter = vecBattleFighter[i];
        if(pBattleFighter)
        {
            dwMaxHP += pBattleFighter->GetMaxHP();
            dwHp    += pBattleFighter->GetHP();
        }
    }

    if(0 == dwMaxHP)
        return 0;
    return dwHp * 1.0 / dwMaxHP;
}


UINT64 OnBattleFight(CPlayerPtr pAtkPlayer,CPlayerPtr pDefPlayer,EBattleResult& eRet,float& fAtkHPRate,float& fDefHPRate)
{
    if(NULL == pAtkPlayer || NULL == pDefPlayer)
    {
        return 0;
    }

    TVecBattleFighterPtr vecBattleFighterAtk;
    TVecBattleFighterPtr vecBattleFighterDef;

    IBattleFighterPtr pScene;
    pScene = pAtkPlayer->GetSceneFighter();
    if(NULL == pScene)
        return 0;

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    PutPlayer(pBS,pAtkPlayer,0,vecBattleFighterAtk);
    PutPlayer(pBS,pDefPlayer,1,vecBattleFighterDef);
    pBS->PutScene(pScene);
    pBS->Start(EBLingshan);

    eRet = pBS->GetFinalWinner();

    //LOG_INF<<"OnBattleFight: qwAtkRoleID:"<<pAtkPlayer->GetRoleID()
    //    <<" vs qwDefRoleID:"<<pDefPlayer->GetRoleID()<<" eRet:"<<eRet;
     
    //恢复连携技能
    pAtkPlayer->GetFighterManager()->ResetCombinationSkill();
    pDefPlayer->GetFighterManager()->ResetCombinationSkill();

    if(eRet == EBResultAttackWin)
    {
        RestorHP(vecBattleFighterAtk,0.05);

    }
    
    if(eRet == EBResultDefenseWin)
    {
        RestorHP(vecBattleFighterDef,0.05);
    }

    //保存散仙信息
    pAtkPlayer->SaveBattleFighterInfo(EBLingshan,vecBattleFighterAtk);
    pDefPlayer->SaveBattleFighterInfo(EBLingshan,vecBattleFighterDef);

    fAtkHPRate = GetHPRate(vecBattleFighterAtk); 
    fDefHPRate = GetHPRate(vecBattleFighterDef);
    //LOG_INF<<"qwAtkRoleID:"<<pAtkPlayer->GetRoleID()<<" fHPRate:"<<fAtkHPRate;
    //LOG_INF<<"qwDefRoleID:"<<pDefPlayer->GetRoleID()<<" fHPRate:"<<fDefHPRate;
 
    eRet = pBS->GetFinalWinner();
    return pBS->GetBattleID();
}

SZhanQiObjPtr CZhanQiRoom::ObjFightResult(SZhanQiObjPtr pAtkObj, SZhanQiObjPtr pDefObj,ECollideType eType)
{
    if(NULL == pAtkObj || NULL == pDefObj)
    {
        return NULL;
    }

    SZhanQiPlayerPtr pAtkZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pAtkObj);
    SZhanQiPlayerPtr pDefZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pDefObj);
    if(NULL == pAtkZhanQiPlayer || NULL == pDefZhanQiPlayer)
        return NULL;

    CPlayerPtr pAtkPlayer = pAtkZhanQiPlayer->pPlayer.lock();
    CPlayerPtr pDefPlayer = pDefZhanQiPlayer->pPlayer.lock();
    if(NULL == pAtkPlayer || NULL == pDefPlayer)
    {
        return NULL;
    }

    if(pAtkPlayer == pDefPlayer)
    {
        return pAtkObj;
    }

    EBattleResult eRet;
    UINT64 qwReportID = OnBattleFight(pAtkPlayer,pDefPlayer,eRet,pAtkZhanQiPlayer->fHPRate,pDefZhanQiPlayer->fHPRate);
    if(!qwReportID)
    {
        return NULL;
    }

    //if(eRet == EBResultTie)
    //    return NULL;

    SZhanQiObjPtr pFailObj;
    SZhanQiObjPtr pWinObj;

    CPlayerPtr pWinPlayer;
    CPlayerPtr pFailPlayer;
 
    std::string strFailName;
    std::string strWinName;
     if(eRet == EBResultAttackWin)
     {
         pWinObj = pAtkObj;
         pFailObj  = pDefObj;
         strFailName = pDefPlayer->GetName();
         strWinName  = pAtkPlayer->GetName();

         pWinPlayer = pAtkPlayer;
         pFailPlayer = pDefPlayer;
     }
     else
     {

         pWinObj  = pDefObj;
         pFailObj = pAtkObj;

         strFailName = pAtkPlayer->GetName();
         strWinName  = pDefPlayer->GetName();

         pWinPlayer = pDefPlayer;
         pFailPlayer = pAtkPlayer;
     }

    
     {
        //胜利
        pWinObj->dwKillCnt++;
        STakePrizeLog oTakePrizeLog;
        oTakePrizeLog.eType  = eLingShanPrizeType_Win;
        oTakePrizeLog.wTakeBoxCount = 1;
        oTakePrizeLog.strFailName = strFailName;
        oTakePrizeLog.qwReportID = qwReportID;
        oTakePrizeLog.eCollideType = eType;

        SZhanQiPlayerPtr pWindZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pWinObj);
        if(pWindZhanQiPlayer)
        {

            oTakePrizeLog.fHPRate   = pWindZhanQiPlayer->fHPRate;
            pWindZhanQiPlayer->vecTakePrizeLog.push_back(oTakePrizeLog);

            pWindZhanQiPlayer->dwSuiYuan += g_ZhanQiMgr.GetLastKillPrize(pWinObj->dwKillCnt);
            pWindZhanQiPlayer->dwNormalBoxCnt++; 

            {
                TVecINT32 vecParam;
                vecParam.push_back(1);
                pWinPlayer->OnEvent(eEventType_MysteryTreasureBox,vecParam);
            }
            
            oTakePrizeLog.dwSuiYuan = g_ZhanQiMgr.GetLastKillPrize(pWinObj->dwKillCnt);
            //LOG_INF<<"WIN: qwRoldID:"<<pWindZhanQiPlayer->qwRoleID<<" "<<strWinName;
        }

        TVecINT32 vecParam;
        vecParam.push_back(1);
        vecParam.push_back(pFailObj->wGodBox);
        pWinPlayer->OnEvent(eEventType_MysteryTreasureWin,vecParam);
     }

     {
        //失败原因
        pFailObj->byFail = eType;
        pFailObj->dwKillCnt = 0;

        STakePrizeLog oTakePrizeLog;
        oTakePrizeLog.eType  = eLingShanPrizeType_Fail;
        oTakePrizeLog.strFailName = strWinName;
        oTakePrizeLog.qwReportID = qwReportID;
        oTakePrizeLog.eCollideType = eType; 
        SZhanQiPlayerPtr pFailZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pFailObj);
        if(pFailZhanQiPlayer)
        {
            oTakePrizeLog.fHPRate = pFailZhanQiPlayer->fHPRate;
            pFailZhanQiPlayer->vecTakePrizeLog.push_back(oTakePrizeLog);
            //LOG_INF<<"Fail:qwRoleID:"<<pFailZhanQiPlayer->qwRoleID<<" "<<strFailName;
        }

        TVecINT32 vecParam;
        vecParam.push_back(0);
        vecParam.push_back(pWinObj->wGodBox);
        pFailPlayer->OnEvent(eEventType_MysteryTreasureWin,vecParam);

     }

    
    if(pFailObj->wGodBox)
    {
        pFailObj->wGodBox = 0;
        pWinObj->wGodBox  = 1;
    }

    if(eCollideType_Path == eType)
    {
        SPathCollideInfo oPathCollideInfo;
        if(pWinObj->wSrcID > pWinObj->wDstID)
        {
            oPathCollideInfo.wMinPos  = pWinObj->wDstID;
            oPathCollideInfo.wMaxtPos = pWinObj->wSrcID;
        }
        else
        {
            oPathCollideInfo.wMinPos  = pWinObj->wSrcID;
            oPathCollideInfo.wMaxtPos = pWinObj->wDstID;
        }


        oPathCollideInfo.qwWinPlayer = static_pointer_cast<SZhanQiPlayer>(pWinObj)->qwRoleID;
        oPathCollideInfo.qwFailPlayer = (dynamic_pointer_cast<SZhanQiPlayer>(pFailObj))->qwRoleID;
        _vecPathCollideInfo.push_back(oPathCollideInfo);
    }

    return pWinObj;
}

SZhanQiObjPtr CZhanQiRoom::CollideBattle(TVecZhanQiObjPtr& vecObj,ECollideType eType)
{
    //必须有两个人才能战斗
    if(vecObj.size()<2)
        return NULL;

    INT32 dwFrom = 0;
    INT32 dwTo = vecObj.size() - 1;

    for(UINT32 i= 0; i < vecObj.size(); i++)
    {
        while(dwFrom < dwTo )
        {
            SZhanQiObjPtr pRetObj = ObjFightResult(vecObj[dwFrom],vecObj[dwTo],eType);
            if(pRetObj == vecObj[dwTo])
            {
                //胜利者放到前面
                SZhanQiObjPtr pTmp = vecObj[dwFrom];
                vecObj[dwFrom] = vecObj[dwTo];
                vecObj[dwTo]   = pTmp;
            }

            dwTo--;
            dwFrom++;
        }

        if(dwTo <= 0)
        {
            break;
        }
        else
        {
            dwFrom = 0;
        }
    }

    SZhanQiObjPtr pWinObj = vecObj[0];

    /*
    for(size_t i=1; i < vecObj.size(); i++)
    {
        SZhanQiObjPtr pRetObj= ObjFightResult(pWinObj,vecObj[i],eType);
        if(pRetObj)
        {
            pWinObj = pRetObj;
        }
    }
    */

    if(NULL == pWinObj)
        return NULL;
    if(eCollideType_Grid == eType)
    {
        SGridCollideInfo oGridCollideInfo;
        oGridCollideInfo.wPos = pWinObj->wDstID;
        oGridCollideInfo.qwWinPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pWinObj)->qwRoleID;
        for(size_t i=0;i < vecObj.size(); i++)
        {
            SZhanQiObjPtr pObj = vecObj[i];
            if(pObj&&pObj->byFail)
            {
                oGridCollideInfo.vecFailPlayer.push_back(dynamic_pointer_cast<SZhanQiPlayer>(pObj)->qwRoleID);
                _vecGridCollideInfo.push_back(oGridCollideInfo);
            }
        }

    }

    return pWinObj;
}

void CZhanQiRoom::OnFight(TMapZhanQiObjPtr& mapFight,ECollideType eType)
{
    for(auto itr = mapFight.begin(); itr != mapFight.end(); itr++)
    {
        SCollideObj& rCollideObj  = itr->second;

        if(rCollideObj.vecZhanQiObjPtr.size() <= 1)
            continue;

        rCollideObj.pObjPtr = CollideBattle(rCollideObj.vecZhanQiObjPtr,eType);
    }

}
//移动开始
void CZhanQiRoom::OnTurnMove()
{
    SetAllUserStatus(eLingShanStatus_Move,_dwMoveEndTime);
}

//玩家移动的信息
void CZhanQiRoom::SendMoveNotify()
{
   TVecUINT64 vecUserID;
   GetAllUser(vecUserID);

   TVecPlayerMoveInfo vecPlayerMoveInfo;
   for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
   {
       SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
       if(pZhanQiPlayer)
       {
           SPlayerMoveInfo oPlayerMoveInfo;
           oPlayerMoveInfo.qwRoleID = pZhanQiPlayer->qwRoleID;
           oPlayerMoveInfo.wSrcPos  = pZhanQiPlayer->wSrcID;
           oPlayerMoveInfo.wDstPos  = pZhanQiPlayer->wDstID;
           _oSPlayMovieInfo.vecPlayerMoveInfo.push_back(oPlayerMoveInfo);
       }
   }

   //观赛者
  // GetAllVisitUser(vecUserID);
  // if(!vecUserID.empty())
  // {
  //     g_LingShanProtS.SendClt_PlayerMoveNotify(vecUserID.data(),(UINT16)vecUserID.size(),vecPlayerMoveInfo,GetRoomID());
  // }
}

//玩家信息更新
void CZhanQiRoom::SendPlayerUpdateNotify()
{
   TVecUINT64 vecUserID;
   GetAllUser(vecUserID);
   
   TVecRoomPlayInfo vecRoomPlayInfo;
   for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
   {
       SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
       if(pZhanQiPlayer)
       {
           SRoomPlayInfo oRoomPlayInfo;
           pZhanQiPlayer->GetRoomInfo(oRoomPlayInfo);
           _oSPlayMovieInfo.vecRoomPlayInfo.push_back(oRoomPlayInfo);
       }
   }

   //观赛者
   //GetAllVisitUser(vecUserID);
   //if(!vecUserID.empty())
   //{
   //    g_LingShanProtS.SendClt_PlayerUpdateNotify(vecUserID.data(),(UINT16)vecUserID.size(),vecRoomPlayInfo,GetRoomID());
   //}
}

void CZhanQiRoom::CheckPlayer()
{
  for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end();)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            itr =_mapZhanQiPlayerPtr.erase(itr);
            continue;
        }
        
        CPlayerPtr pPlayer= pZhanQiPlayer->pPlayer.lock();
        if(NULL == pPlayer)
        {
             OnPlayerLeaveGrid(pZhanQiPlayer);
             OnPlayerLeave(pZhanQiPlayer);
             LOG_CRI<<"CheckPlayer qwRoleID:"<<pZhanQiPlayer->qwRoleID;

             itr =_mapZhanQiPlayerPtr.erase(itr);

        }
        else
        {
             itr++;
        }
    }
}

//移动结束开始处理逻辑
void CZhanQiRoom::OnMoveEnd()
{

   CheckPlayer();

   SetAllUserStatus(eLingShanStatus_PlayMovie,_dwPlayerEndTime);
   TVecUINT64 vecUserID;
   GetAllUser(vecUserID);

   //观赛者
   GetAllVisitUser(vecUserID);
 
   //未移动的单元随机移动
   CheckRandomMove();

   //路径碰撞战斗
   OnMovePathCheck();
   OnFight(_mapSamePathObjPtr,eCollideType_Path);

   //发送
   TVecPathCollideInfo vecPathCollideInfo;
   for(auto itr = _mapSamePathObjPtr.begin(); itr != _mapSamePathObjPtr.end(); itr++)
   {
       //UINT32 dwPath = wMaxPos*1000 + wMinPos;
       SCollideObj& rCollideObj = itr->second;
       if(rCollideObj.vecZhanQiObjPtr.size() != 2)
           continue;
       SPathCollideInfo oPathCollideInfo;
       oPathCollideInfo.wMinPos = itr->first%1000;
       oPathCollideInfo.wMaxtPos = itr->first/1000;
       LOG_INF<<"SamePath:";
       for(size_t i = 0; i<rCollideObj.vecZhanQiObjPtr.size(); i++ )
       {
           SZhanQiPlayerPtr pZhanQiObj = dynamic_pointer_cast<SZhanQiPlayer>(rCollideObj.vecZhanQiObjPtr[i]);
           if(pZhanQiObj)
           {
               if(pZhanQiObj->byFail)
               {
                   oPathCollideInfo.qwFailPlayer = pZhanQiObj->qwRoleID;
                   //LOG_INF<<"qwFailPlayer:"<<pZhanQiObj->qwRoleID;
               }
               else
               {
                   oPathCollideInfo.qwWinPlayer = pZhanQiObj->qwRoleID;
                   oPathCollideInfo.dwWinKillCnt = pZhanQiObj->dwKillCnt;
                   //LOG_INF<<"qwWinPlayer:"<<pZhanQiObj->qwRoleID<<" dwKillCnt:"<<pZhanQiObj->dwKillCnt;
               }

           }
       }
       _oSPlayMovieInfo.vecPathCollideInfo.push_back(oPathCollideInfo);
   }

//   if(!vecUserID.empty())
//   {
//       g_LingShanProtS.SendClt_PathCollideNotify(vecUserID.data(),(UINT16)vecUserID.size(),vecPathCollideInfo,GetRoomID());
//   }
   //相同格子战斗
   OnSameGridCheck();
   OnFight(_mapSameGridObjPtr,eCollideType_Grid);
   
   TVecGridCollideInfo vecGridCollideInfo;
   for(auto itr = _mapSameGridObjPtr.begin(); itr != _mapSameGridObjPtr.end(); itr++)
   {
       //UINT32 dwPath = wMaxPos*1000 + wMinPos;
       SCollideObj& rCollideObj = itr->second;
       if(rCollideObj.vecZhanQiObjPtr.size() < 2)
           continue;
       SGridCollideInfo oGridCollideInfo;
       oGridCollideInfo.wPos = itr->first;
       LOG_INF<<"SameGrid:";
       for(size_t i = 0; i<rCollideObj.vecZhanQiObjPtr.size(); i++ )
       {
           SZhanQiPlayerPtr pZhanQiObj = dynamic_pointer_cast<SZhanQiPlayer>(rCollideObj.vecZhanQiObjPtr[i]);
           if(pZhanQiObj)
           {
               if(0 == pZhanQiObj->byFail)
               {
                   oGridCollideInfo.qwWinPlayer = pZhanQiObj->qwRoleID;
                   oGridCollideInfo.dwWinKillCnt = pZhanQiObj->dwKillCnt; 
                   //LOG_INF<<"qwWinPlayer:"<<pZhanQiObj->qwRoleID<<" dwKillCnt:"<<pZhanQiObj->dwKillCnt;
               }
               else
               {

                   oGridCollideInfo.vecFailPlayer.push_back(pZhanQiObj->qwRoleID);
                   //LOG_INF<<"FailPlayer:"<<pZhanQiObj->qwRoleID;
               }
           }
           else
           {
               LOG_CRI<<"ERRIR!!";
           }
       }

       _oSPlayMovieInfo.vecGridCollideInfo.push_back(oGridCollideInfo);
   }

 
  // if(!vecUserID.empty()&& !vecGridCollideInfo.empty())
  // {
  //     LOG_INF<<"SendClt_GridCollideNotify:"<<vecGridCollideInfo.size();
  //     g_LingShanProtS.SendClt_GridCollideNotify(vecUserID.data(),(UINT16)vecUserID.size(),vecGridCollideInfo,GetRoomID());
  // }

   //notify move restult
   SendMoveNotify();
   
   //玩家信息更新
   SendPlayerUpdateNotify();

 }
 
 void RandomVec(TVecUINT16& vecEmptyPos)
 {
     UINT32 dwMaxRand = vecEmptyPos.size();
     while(dwMaxRand>0)
     {
         UINT32 dwRand = rand()%dwMaxRand;
         UINT16 wEnd = vecEmptyPos[dwMaxRand-1];
        vecEmptyPos[dwMaxRand-1] = vecEmptyPos[dwRand];
        vecEmptyPos[dwRand] = wEnd;
        dwMaxRand--;
    }
}
//刷新事件
void CZhanQiRoom::OnFreshTurn()
{
   
    //获取空余格子数量
    TVecUINT16 vecEmptyPos;
    for(size_t i = 1; i < _vecMapGrid.size(); i++)
    {
        if(_vecMapGrid[i].IsEmpty())
        {
            vecEmptyPos.push_back(i);
        }
    }

    UINT32 dwNeedCnt = _wFreshPlayCnt > vecEmptyPos.size()?vecEmptyPos.size():_wFreshPlayCnt;

    //出队一定数量的等待玩家
    TVecZhanQiPlayerPtr vecZhanQiPlayerPtr;
    g_ZhanQiMgr.GetWaitPlayer(vecZhanQiPlayerPtr,dwNeedCnt);
    RandomVec(vecEmptyPos);
    Push_Player(vecZhanQiPlayerPtr,vecEmptyPos);
   
    TVecRoomPlayInfo vecRoomPlayInfo;
    for(size_t i=0; i< vecZhanQiPlayerPtr.size();i++)
    {
        SZhanQiPlayerPtr pPlayer = vecZhanQiPlayerPtr[i];
        if(pPlayer)
        {
            SRoomPlayInfo oRoomPlayInfo;
            pPlayer->GetRoomInfo(oRoomPlayInfo);
            vecRoomPlayInfo.push_back(oRoomPlayInfo);
        }
    }
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    GetAllVisitUser(vecUserID);
    if(!vecUserID.empty()&& !vecRoomPlayInfo.empty())
    {
        g_LingShanProtS.SendClt_NewPlayerEnterNotify(vecUserID.data(),(UINT16)vecUserID.size(),vecRoomPlayInfo,GetRoomID());
    }
    //刷新新宝箱
    OnSpawBox();

    for(size_t i=0; i< vecZhanQiPlayerPtr.size();i++)
    {
        OnEnterRoom(vecZhanQiPlayerPtr[i]);
    }
 }

//玩家离开格子
void CZhanQiRoom::OnPlayerLeaveGrid(SZhanQiObjPtr pObj)
{
    if(NULL == pObj)
        return;

    SZhanQiPlayerPtr pZhanQiPlayer = dynamic_pointer_cast<SZhanQiPlayer>(pObj);
    if(NULL == pZhanQiPlayer)
    {
        return;
    }

    if(pZhanQiPlayer->wSrcID>=_vecMapGrid.size())
        return;
    SMapGrid& rGridObj = _vecMapGrid[pObj->wSrcID];
    
    if(pObj != rGridObj.pZhanQiObjPtr)
    {
        LOG_CRI<<"Error Grid:"<<pObj->wSrcID<<" qwRoleID:"<<pZhanQiPlayer->qwRoleID;
    }

    rGridObj.pZhanQiObjPtr = NULL;

    /*
   if(!pZhanQiPlayer->vecTakePrizeLog.empty())
   {
       CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
       if(pPlayer)
       {
            //pPlayer->SendPkg(g_LingShanProtS.BuildPkg_PlayerPrizeLogNotify(pZhanQiPlayer->vecTakePrizeLog));
            //LOG_INF<<"OnPlayerLeaveGrid Faillog size:"<<pZhanQiPlayer->vecTakePrizeLog.size();
            //pZhanQiPlayer->vecTakePrizeLog.clear();
       }
   }
   */

}


//玩家进入新格子
void CZhanQiRoom::OnPlayerEnterGrid(SZhanQiObjPtr pObj)
{
    if(NULL == pObj)
        return;

    SZhanQiPlayerPtr pPlayerObj = dynamic_pointer_cast<SZhanQiPlayer>(pObj);
    if(NULL == pPlayerObj)
    {
        return;
    }

    //
   if(pPlayerObj->wDstID>=_vecMapGrid.size())
        return;

   UINT32 dwTakeBoxCnt = 0;
   //带大宝箱
   if(pPlayerObj->wGodBox)
   {
       pPlayerObj->dwNormalBoxCnt++;
       dwTakeBoxCnt++;
       STakePrizeLog oTakePrizeLog;
       oTakePrizeLog.eType  = eLingShanPrizeType_MoveByGodBox;
       oTakePrizeLog.wTakeBoxCount = 1;
       oTakePrizeLog.fHPRate=pPlayerObj->fHPRate;
       pPlayerObj->vecTakePrizeLog.push_back(oTakePrizeLog);
   }


   SMapGrid& rGridObj = _vecMapGrid[pObj->wDstID];
   if(rGridObj.pZhanQiObjPtr && rGridObj.pZhanQiObjPtr->IsObj(eZhanQiObjType_Box))
   {
       pPlayerObj->dwNormalBoxCnt++;

       STakePrizeLog oTakePrizeLog;

       //带有大宝箱
       if(rGridObj.pZhanQiObjPtr->wGodBox)
       {
           pPlayerObj->wGodBox = 1;
           rGridObj.pZhanQiObjPtr->wGodBox = 0;
           oTakePrizeLog.eType  = eLingShanPrizeType_PickGodBox;
       }
       else
       {
           oTakePrizeLog.eType  = eLingShanPrizeType_PickNormalBox;
       }

       dwTakeBoxCnt++;

       oTakePrizeLog.wTakeBoxCount = 1;
       pPlayerObj->vecTakePrizeLog.push_back(oTakePrizeLog);
       pPlayerObj->dwSuiYuan += SParamConfig::wSecretAreaGetBoxSuiYuan;
       oTakePrizeLog.fHPRate=pPlayerObj->fHPRate;
       oTakePrizeLog.dwSuiYuan = SParamConfig::wSecretAreaGetBoxSuiYuan;
       //

       rGridObj.pZhanQiObjPtr = NULL;

   }

   //移动增加随缘值
   pPlayerObj->dwSuiYuan += SParamConfig::wSecretAreaMoveSuiYuan;

   if(NULL != rGridObj.pZhanQiObjPtr)
   {
       LOG_CRI<<"Error SamGrid";
   }

   //放入玩家
   rGridObj.pZhanQiObjPtr = pObj;

   //玩家移动
   pPlayerObj->wSrcID = pPlayerObj->wDstID;
   pPlayerObj->wDstID = 0;
   pPlayerObj->byFail = 0;

   //LOG_INF<<"OnPlayerEnterGrid Room:"<<GetRoomID()<<" qwRoleID:"<<pPlayerObj->qwRoleID<<" wPos:"<<pObj->wSrcID
     //  <<" TakeBoxCnt:"<<dwTakeBoxCnt;
   CPlayerPtr pPlayer = pPlayerObj->pPlayer.lock();
   if(pPlayer)
   {
        TVecINT32 vecParam;
        vecParam.push_back(dwTakeBoxCnt);
        pPlayer->OnEvent(eEventType_MysteryTreasureBox,vecParam);
   }

}

//一轮开始
void CZhanQiRoom::OnTurnStart()
{
    _wFreshTurn++;

    bool bFresh = false;
    //_wFreshTurn表示新一轮
    if( _wFreshTurn >= _wMaxFreshTurn)
    {
        LOG_INF<<"fresh new turn!!!"<<_wFreshTurn;
        OnFreshTurn();
        _wFreshTurn = 1;
        bFresh = true;
    }
    
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    GetAllVisitUser(vecUserID);
    if(!vecUserID.empty())
    {
        g_LingShanProtS.SendClt_NewTurnBeginNotify(vecUserID.data(),(UINT16)vecUserID.size(),bFresh,GetRoomID(),GetNexFreshTurns());
    }

}


//一轮结束
void CZhanQiRoom::OnTurnEnd()
{
    
   //进入新格子
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); )
    {
       SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            itr=_mapZhanQiPlayerPtr.erase(itr);
            continue;
        }
  
        OnPlayerLeaveGrid(pZhanQiPlayer);

        itr++;
    }

    //进入新格子
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); )
    {
       SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            itr=_mapZhanQiPlayerPtr.erase(itr);
            continue;
        }
  
        
        if(pZhanQiPlayer->byFail)
        {
            itr++;
            continue;
        }
 
        OnPlayerEnterGrid(pZhanQiPlayer);

        //save db
        g_ZhanQiMgr.SaveItem(pZhanQiPlayer);


        itr++;
    }

}

//播放动画结束
void CZhanQiRoom::OnPlayMovieEnd()
{
    _oSPlayMovieInfo.vecPlayerMoveInfo.clear();
    _oSPlayMovieInfo.vecPathCollideInfo.clear();
    _oSPlayMovieInfo.vecGridCollideInfo.clear();
    _oSPlayMovieInfo.vecRoomPlayInfo.clear();
  
   //clear log,kick failplayer  
   for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); )
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(NULL == pZhanQiPlayer)
        {
            itr=_mapZhanQiPlayerPtr.erase(itr);
            continue;
        }

        pZhanQiPlayer->vecTakePrizeLog.clear(); 

        if(pZhanQiPlayer->byFail)
        {
            OnPlayerLeave(pZhanQiPlayer);
            g_ZhanQiMgr.SaveItem(pZhanQiPlayer); 
            itr=_mapZhanQiPlayerPtr.erase(itr);
            continue;
        }

        itr++;

        //存活轮数+1
        pZhanQiPlayer->dwSelfTurns++;
    }

}


//时钟
void  CZhanQiRoom::OnSecUpdate()
{
    //LOG_INF<<"OnSecUpdate eStatus:"<<_eStatus;
    switch(_eStatus)
    {
        case eZhanQiRoomStatus_GameStart:
        {
            _wTurns++;
            LOG_INF<<"RoomID:"<<GetRoomID()<<"Turn:"<<_wTurns<<" begin!";
            SetStatus(eZhanQiRoomStatus_Move);
            _dwMoveEndTime = time(NULL) + SParamConfig::wSecretAreaMoveTime;
            //移动10s 动画10s + 2s update
            //_dwPlayerEndTime = _dwMoveEndTime + SParamConfig::wSecretAreaPlayTime + 1;

            OnTurnStart();

            LOG_INF<<"wSecretAreaMoveTime:"<<SParamConfig::wSecretAreaMoveTime<<" wSecretAreaPlayTime:"<<SParamConfig::wSecretAreaPlayTime;

            //可以移动了
            OnTurnMove();

            //LOG_INF<<"eZhanQiRoomStatus_Move";
        }
        break;
        case eZhanQiRoomStatus_Move:
        {
            if( time(NULL) >= _dwMoveEndTime)
            {
                
                //移动10s 动画10s
                _dwPlayerEndTime = time(NULL)+ SParamConfig::wSecretAreaPlayTime;

               SetStatus(eZhanQiRoomStatus_Play);
               OnMoveEnd();
               OnTurnEnd();
               LOG_INF<<"OnMoveEnd";
           }

        }
        break;
        case eZhanQiRoomStatus_Play:
        {
            if(time(NULL) >= _dwPlayerEndTime)
            {
                //OnTurnEnd();

                OnPlayMovieEnd();

                SetStatus(eZhanQiRoomStatus_GameStart);
                if(_bAllOver)
                {
                    SetStatus(eZhanQiRoomStatus_End);
                    //LOG_INF<<"eZhanQiRoomStatus_End";
                    SetAllUserStatus(eLingShanStatus_End,0);
                }
                else
                {
                    //LOG_INF<<"NEXT eZhanQiRoomStatus_GameStart";
                    SetStatus(eZhanQiRoomStatus_GameStart);
                }
            }
        }
        break;
        case eZhanQiRoomStatus_End:
        {
        }
        break;
        default:
        {
        }
        break;
    }

}


void CZhanQiRoom::GetAllUser(TVecUINT64& vecUserID)
{
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
         CPlayerPtr pPlayer=itr->second->pPlayer.lock();
         if(pPlayer)
         {
             vecUserID.push_back(pPlayer->GetUserID());
         }
    }
}

//获取参观的玩家
void CZhanQiRoom::GetAllVisitUser(TVecUINT64& vecUserID)
{
    for(auto itr = _mapVisitPlayerPtr.begin(); itr != _mapVisitPlayerPtr.end(); itr++)
    {
        CPlayerPtr pPlayer=itr->second->pPlayer.lock();
        if(pPlayer)
        {
            vecUserID.push_back(pPlayer->GetUserID()); 
        }
    }

}


//设置房间所有玩家状态
void CZhanQiRoom::SetAllUserStatus(ELingShanStatus eStatus,UINT32 dwParam)
{
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
          itr->second->eStatus = eStatus;
    }

    //减少1秒
    dwParam += 1;
    
    //LOG_INF<<"set move status eStatus"<<dwParam;
    //LOG_CRI<<"time check now:"<<time(NULL)<<"-"<<dwParam<<"="<<(time(NULL)-dwParam);
 
    TVecUINT64 vecUserID;
    GetAllUser(vecUserID);
    if(!vecUserID.empty())
    {
       g_LingShanProtS.SendClt_StatusNotify(vecUserID.data(),(UINT16)vecUserID.size(),eStatus,dwParam,time(NULL),GetRoomID());
    }

    //参观者消息
    TVecUINT64 vecVisitUserID;
    GetAllVisitUser(vecVisitUserID);
    if(!vecVisitUserID.empty())
    {
        g_LingShanProtS.SendClt_VisitRoomStatusNotify(vecVisitUserID.data(),(UINT16)vecVisitUserID.size(),eStatus,dwParam,time(NULL));

    }

}


//活动结束
void  CZhanQiRoom::OnGameOver()
{
    _bAllOver = true;
}

//获取下一次刷新宝箱的剩余轮数
UINT32 CZhanQiRoom::GetNexFreshTurns()
{
    if(_wFreshTurn>=_wMaxFreshTurn)
        return 0;

     return _wMaxFreshTurn - _wFreshTurn;
}

//获取房间状态
void CZhanQiRoom::GetRoomPlayerStatus(ELingShanStatus& eStatus,UINT32& dwTime)
{
    switch(_eStatus)
    {
        case eZhanQiRoomStatus_GameStart:
        case eZhanQiRoomStatus_Move:
        {
            eStatus = eLingShanStatus_Move;
            dwTime  = _dwMoveEndTime;
        }
        break;
        case eZhanQiRoomStatus_Play:
        {
            eStatus = eLingShanStatus_PlayMovie;
            dwTime  = _dwPlayerEndTime;
        }
        break;
        case eZhanQiRoomStatus_End:
        {
            eStatus = eLingShanStatus_End;
            dwTime  = time(NULL);
        }
        break;
        default:
        {
        }
        break;
    }

}

//已进入房间事件
void CZhanQiRoom::OnEnterRoom(SZhanQiPlayerPtr pZhanQiPlayer)
{
    UINT32 dwVisitRoomID = pZhanQiPlayer->GetVisitRoomID();
    if(dwVisitRoomID)
    {
        CZhanQiRoomPtr pVisitRoom =  g_ZhanQiMgr.GetRoom(dwVisitRoomID);
        if(pVisitRoom)
        {
            pVisitRoom->OnLeaveVisitRoom(pZhanQiPlayer);
        }

        pZhanQiPlayer->SetVisitRoomID(0);
        CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
        if(pPlayer)
        {
            pPlayer->SendPkg(g_LingShanProtS.BuildPkg_KickViewNotify(GetRoomID()));
        }
    }
}



