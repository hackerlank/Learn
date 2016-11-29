
#include "stdafx.h"
#include "HorseMgr.h"
#include "Protocols.h"
#include "CommonDef.h"
#include "ProtoCommon.h"
#include "User.h"
#include "Player.h"
#include "FighterMgr.h"
#include "SkillAttr.h"
#include "Random.h"
#include "HorseSvrS.h"
#include "FighterManager.h"
#include "SysMsgDefine.h"
#include "Tokenizer.h"
#include "EventMgr.h"
#include "Map.h"
#include "GetCondMgr.h"
#include "GameServerLog.h"

using namespace NProtoCommon;

bool g_OpenHorseLog = true;

bool CHorse::HorseInit(UINT32 dwHorseID)
{
    auto itrCFG = CHorseMgr::_mapHorseBaseCFGPtr.find(dwHorseID);
    if(itrCFG == CHorseMgr::_mapHorseBaseCFGPtr.end())
    {
        LOG_CRI<<"Error HorseBaseCFG HorseID:"<<dwHorseID;
        return false;
    }

    UINT32 dwHorseLevelID = SKILLANDLEVEL(dwHorseID,1);

    SHorseUpgradeCFGPtr pHorseUpgradeCFG = CHorseMgr::GetHorseUpgradeCFG(dwHorseLevelID);
    if(NULL == pHorseUpgradeCFG)
    {
        LOG_CRI<<"Error pHorseUpgradeCFG HorseLevelID:"<<dwHorseLevelID;
        return false;
    }


    _dwHorseSpeed = pHorseUpgradeCFG->_Speed;

    _oHorseDB.qwUserID = _rUser.GetUserID();
    _oHorseDB.qwRoleID = _rUser.GetRoleID();
    _oHorseDB.dwHorseID = dwHorseID;

    _oHorseDB.dwHorseLevel  = 1; //初始化1级
    _oHorseDB.dwModelID     = pHorseUpgradeCFG->_ModelID;
    _oHorseDB.dwExp         = 0;
    _oHorseDB.dwPos         = 0;
    _oHorseDB.dwLock        = 0;

    RebuildAttr();

    Update2DB(_oHorseDB,eOpAdd);

    return true;

}

void CHorse::RebuildAttr()
{
    _vecAttr.clear();


    UINT32 dwHorseLevelID = SKILLANDLEVEL(_oHorseDB.dwHorseID,_oHorseDB.dwHorseLevel);

    SHorseUpgradeCFGPtr pHorseUpgradeCFG = CHorseMgr::GetHorseUpgradeCFG(dwHorseLevelID);
    if(NULL == pHorseUpgradeCFG)
    {
        LOG_CRI<<"Error pHorseUpgradeCFG HorseLevel:"<<dwHorseLevelID;
        return;
    }


    _dwHorseSpeed = pHorseUpgradeCFG->_Speed;

    SSkillAttrPtr pSkillAttr = g_SkillAttrMgr.GetSkillAttrByID(pHorseUpgradeCFG->_SkillAttrID);
    if(NULL == pSkillAttr)
    {
        LOG_CRI<<"Error SkillAttr: "<<pHorseUpgradeCFG->_SkillAttrID;
        return;
    }

    _vecAttr += pSkillAttr->_vecAttr; 



    //解锁技能（暂时不开发）
    /*
       for(size_t i = 0; i < _vecSkillAttr.size(); ++i)
       {
       UINT32 dwSkillAttrID = _vecSkillAttr[i];
       SSkillAttrPtr pSkillAttr = g_SkillAttrMgr.GetSkillAttrByID(dwSkillAttrID);
       if(NULL == pSkillAttr)
       {
       LOG_CRI<<"RebuildAttr Error Invalid SkillAttrID "<<dwSkillAttrID;
       continue;
       }

       _vecAttr += pSkillAttr->_vecAttr;

       }
       */

}

void CHorse::LoadFromDB(const SHorseDB& sInfo)
{
    _oHorseDB = sInfo;
    UpdateSkillVec();
    RebuildAttr();
}

void CHorse::Update2DB(SHorseDB& rInfo, EDataChange eDataChange /*= eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypeHorseDBInfo, eDataChange, strData);

}
void CHorse::Update2DB()
{
    Update2DB(_oHorseDB);

}

void CHorse::ChangePos(UINT8 byPos)
{
    _oHorseDB.dwPos = byPos;

    Update2DB(_oHorseDB);

}

UINT32 CHorse::GetHorseAttrID()
{
    return SKILLANDLEVEL(_oHorseDB.dwHorseID,_oHorseDB.dwHorseLevel);
}

//升阶
UINT8 CHorse::ActiveUpgrade(bool bAll)
{
    UINT32 dwHorseLevelID = SKILLANDLEVEL(_oHorseDB.dwHorseID,_oHorseDB.dwHorseLevel);

    SHorseUpgradeCFGPtr pHorseUpgradeCFG = CHorseMgr::GetHorseUpgradeCFG(dwHorseLevelID);
    if(NULL == pHorseUpgradeCFG)
    {
        LOG_CRI<<"HorseUpgradeCFG Error dwHorseID: "<<_oHorseDB.dwHorseID<<" dwHorseLevel: "<<_oHorseDB.dwHorseLevel; 
        _rUser.SendSysMsg(eMsgHorseErrorUprageCFG);
        return 0;
    }

    UINT32 dwNextHorseLevelID = dwHorseLevelID + 1;

    SHorseUpgradeCFGPtr pHorseUpgradeCFGNext = CHorseMgr::GetHorseUpgradeCFG(dwNextHorseLevelID); 
    if(NULL == pHorseUpgradeCFGNext)
    {
        _rUser.SendSysMsg(eMsgHorseMaxLevel);
        return 0;
    }
    CStore* pStore = _rUser.GetStoreByType(eStorePack);
    if(!pStore)
        return 0;

    UINT16 wNeedItemID  = pHorseUpgradeCFG->_NeedItemID;
    UINT16 wNeedItemCnt = pHorseUpgradeCFG->_NeedItemCnt;

    UINT16 wTotalItemCnt = 0;
    UINT32 dwMaxCount = 0;
    do
    {
        if(dwMaxCount>99999)
        {
            LOG_CRI<<"dead while!!!";
            break;
        }

        if(pStore->GetItemCount(wNeedItemID) < wTotalItemCnt+wNeedItemCnt)
        {
            _rUser.SendSysMsg(eMsgHorseNotFullItem);
            break;
        }

        if(0== wNeedItemCnt)
        {
            LOG_CRI<<"Error HorseUpgradeCFG 0== wNeedItemCnt";
            break;
        }


        dwMaxCount++;

        wTotalItemCnt += wNeedItemCnt;


        UINT32 dwMinExp = pHorseUpgradeCFG->_ExpLow;
        UINT32 dwMaxExp = pHorseUpgradeCFG->_ExpHigh;
        UINT32 dwExp = CRandom::RandInt(dwMinExp,dwMaxExp);

        UINT8 byNum = 1;
#if ON_OFF
        UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
        if (wRand < RANDVALUE_A)
            byNum = 10;
        else if (wRand < RANDVALUE_B)
            byNum = 5;
        else if (wRand < RANDVALUE_C)
            byNum = 2;

        if (TWO_NOTIFY==byNum)
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eHorseCrit, eTwoMultipleCrit));
        else if (FIVE_NOTIFY==byNum)
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eHorseCrit, eFiveMultipleCrit));
        else if(TEN_NOTIFY==byNum)
        {
            CPlayerPtr pPlayer = _rUser.GetPlayer();
            if (pPlayer)
            {
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(byNum));
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgHorseUpgrade, vecstring);
            }
            _rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eHorseCrit, eTenMultipleCrit));
        }
#endif
        _oHorseDB.dwExp += (dwExp * byNum);

        if(_oHorseDB.dwExp >= pHorseUpgradeCFG->_NeedExp )
        {
            _oHorseDB.dwExp -= pHorseUpgradeCFG->_NeedExp;

            pStore->DelItemByItemID(wNeedItemID, wTotalItemCnt, true, NLogDataDefine::ItemTo_HorseUpgrade);
            _oHorseDB.dwHorseLevel += 1;
            RebuildAttr();
            Update2DB(_oHorseDB);
            //事件
            CPlayerPtr pPlayer = _rUser.GetPlayer();
            if(pPlayer)
            {
                TVecINT32 vecParam;
                vecParam.push_back(GetHorseID());
                vecParam.push_back(_oHorseDB.dwHorseLevel);
                vecParam.push_back(dwMaxCount);
                const TMapHorsePtr& mapHorsePtr = _rHorseMgr.GetHorseList();
                for(auto itr = mapHorsePtr.begin(); itr != mapHorsePtr.end(); itr++)
                {
                    //vecParam.push_back(itr->second->GetHorseID());
                    if(itr->second->GetHorseID() != GetHorseID())
                        vecParam.push_back(itr->second->GetHorseLevel());
                }
                CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
                if(pEventMgr)
                    pEventMgr->OnEvent(eEventType_HorseUpgrade,vecParam);
                if(_oHorseDB.dwHorseLevel >= 9)
                {
                    NGlobalChatProt::SShowInfo stShow;
                    stShow.qwInstID = pPlayer->GetUserID();
                    GetShowInfo(stShow);
                    NGlobalChatProt::TVecShowInfo vecShow;
                    TVecString vecstring;
                    vecstring.push_back(NumberToString(pPlayer->GetColor()));
                    vecstring.push_back(pPlayer->GetName());
                    vecShow.push_back(stShow);
                    g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgRideTop,vecstring,vecShow);
                }

                _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_SpecialHorseLvl);
            }

            return 1;
        }

        if(!bAll)
        {
            break;
        }
    } while(1);

    if(wTotalItemCnt != 0)
    {
        pStore->DelItemByItemID(wNeedItemID, wTotalItemCnt, true, NLogDataDefine::ItemTo_HorseUpgrade);
        //事件
        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if(pPlayer)
        {
            TVecINT32 vecParam;
            vecParam.push_back(GetHorseID());
            vecParam.push_back(_oHorseDB.dwHorseLevel);
            vecParam.push_back(dwMaxCount);
            const TMapHorsePtr& mapHorsePtr = _rHorseMgr.GetHorseList();
            for(auto itr = mapHorsePtr.begin(); itr != mapHorsePtr.end(); itr++)
            {
                //vecParam.push_back(itr->second->GetHorseID());
                if(itr->second->GetHorseID() != GetHorseID())
                    vecParam.push_back(itr->second->GetHorseLevel());
            }
            CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
            if(pEventMgr)
                pEventMgr->OnEvent(eEventType_HorseUpgrade,vecParam);
            if(_oHorseDB.dwHorseLevel >= 9)
            {
                NGlobalChatProt::SShowInfo stShow;
                stShow.qwInstID = pPlayer->GetUserID();
                GetShowInfo(stShow);
                NGlobalChatProt::TVecShowInfo vecShow;
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecShow.push_back(stShow);
                g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgRideTop,vecstring,vecShow);

            }

        }

        Update2DB(_oHorseDB);
    }

    return 2;

}

bool CHorse::IsSkillAttrLock(UINT32 dwPos)
{
    if((_oHorseDB.dwLock>>(dwPos-1))&1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CHorse::UnLockSkillAttr(UINT32 dwPos)
{
    _oHorseDB.dwLock &= 1<<(dwPos-1);
    UpdateSkillVec();
}

void CHorse::GetHorseInfo(SHorseInfo& rHorseInfo)
{
    rHorseInfo.dwHorseID = _oHorseDB.dwHorseID;
    rHorseInfo.dwHorseLevel = _oHorseDB.dwHorseLevel;
    rHorseInfo.dwExp = _oHorseDB.dwExp;
    rHorseInfo.dwPos = _oHorseDB.dwPos;

}

UINT32 GetSkillAttr(UINT32 dwPos, SHorseBaseCFGPtr& pHorseBaseCFGPtr)
{
    UINT32 dwSkillAttrID = 0;
    switch(dwPos)
    {
        case 1:
            {
                dwSkillAttrID =  pHorseBaseCFGPtr->_SkillAttrID1;
            }
            break;
        case 2:
            {
                dwSkillAttrID =  pHorseBaseCFGPtr->_SkillAttrID2;
            }
            break;
        case 3:
            {
                dwSkillAttrID =  pHorseBaseCFGPtr->_SkillAttrID3;
            }
            break;
        case 4:
            {
                dwSkillAttrID = pHorseBaseCFGPtr->_SkillAttrID4;
            }
            break;
        case 5:
            {
                dwSkillAttrID = pHorseBaseCFGPtr->_SkillAttrID5;
            }
            break;
        default:
            break;
    }

    return dwSkillAttrID;
}

void CHorse::UpdateSkillVec()
{
    _vecSkillAttr.clear();

    SHorseBaseCFGPtr pHorseBaseCFGPtr =  CHorseMgr::GetHorseBaseCFG(GetHorseID()); 
    if(NULL == pHorseBaseCFGPtr)
    {
        return;
    }

    for(UINT32 i = 1; i <=5; i++)
    {
        if(_oHorseDB.dwLock>>i &1)
        {
            UINT32 dwSkillAttrID = GetSkillAttr(i,pHorseBaseCFGPtr);
            if(0 != dwSkillAttrID)
            {
                _vecSkillAttr.push_back(dwSkillAttrID);
            }

        }

    }

}
void CHorse::GetShowInfo(NGlobalChatProt::SShowInfo& stShow)
{
    NGlobalChatProt::SFlauntHorse sInfo;
    sInfo.wFighterID = GetHorseID();
    sInfo.byLevel = GetHorseLevel();
    COutArchive iar(stShow.strShowInfo);
    iar << UINT8(NGlobalChatProt::eShowHorse);
    iar << sInfo; 

}


//////////////////////////////////////////////////////////////////////CHorseMgr

TMapHorseBaseCFGPtr CHorseMgr::_mapHorseBaseCFGPtr;
TMapHorseUpgradeCFGPtr CHorseMgr::_mapHorseUpgradeCFGPtr;

bool CHorseMgr::HorseMgrInit()
{
    string strPath = Config._strConfigDir + "Conf/Table/HorseBase.xml";
    CHorseBaseLoader oHorseBaseLoader;
    if(!oHorseBaseLoader.LoadData(strPath))
    {
        return false;
    }

    _mapHorseBaseCFGPtr.clear();

    for(size_t i = 0; i < oHorseBaseLoader._vecData.size(); ++i)
    {
        if(!oHorseBaseLoader._vecData[i])
        {
            LOG_CRI<<"CHorseMgr::HorseMgrInit Unknow Error!";
            return false;
        }

        SHorseBaseCFGPtr oTmp(new SHorseBaseCFG);
        *oTmp=*(oHorseBaseLoader._vecData[i]);
        _mapHorseBaseCFGPtr.insert(make_pair(oTmp->_ID,oTmp));
    }


    strPath = Config._strConfigDir + "Conf/Table/HorseUpgrade.xml";

    CHorseUpgradeLoader oHorseUpgradeLoader;
    if(!oHorseUpgradeLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oHorseUpgradeLoader._vecData.size(); ++i)
    {

        SHorseUpgradeCFGPtr oTmp(new SHorseUpgradeCFG);
        *oTmp=*(oHorseUpgradeLoader._vecData[i]);
        _mapHorseUpgradeCFGPtr.insert(make_pair(oTmp->_HorseLevel,oTmp));

    }


    return true;
}

bool CHorseMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("HorseBase.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/HorseBase.xml";
        CHorseBaseLoader oHorseBaseLoader;
        if(!oHorseBaseLoader.LoadData(strPath))
        {
            return false;
        }

        _mapHorseBaseCFGPtr.clear();

        for(size_t i = 0; i < oHorseBaseLoader._vecData.size(); ++i)
        {
            if(!oHorseBaseLoader._vecData[i])
            {
                LOG_CRI<<"CHorseMgr::HorseMgrInit Unknow Error!";
                return false;
            }

            SHorseBaseCFGPtr oTmp(new SHorseBaseCFG);
            *oTmp=*(oHorseBaseLoader._vecData[i]);
            _mapHorseBaseCFGPtr.insert(make_pair(oTmp->_ID,oTmp));
        }
    }else if("HorseUpGrade.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/HorseUpgrade.xml";

        CHorseUpgradeLoader oHorseUpgradeLoader;
        if(!oHorseUpgradeLoader.LoadData(strPath))
        {
            return false;
        }

        for(size_t i = 0; i < oHorseUpgradeLoader._vecData.size(); ++i)
        {

            SHorseUpgradeCFGPtr oTmp(new SHorseUpgradeCFG);
            *oTmp=*(oHorseUpgradeLoader._vecData[i]);
            _mapHorseUpgradeCFGPtr.insert(make_pair(oTmp->_HorseLevel,oTmp));

        }
    }

    return true;

}
SHorseBaseCFGPtr CHorseMgr::GetHorseBaseCFG(UINT32 dwHorseID)
{
    auto itr = CHorseMgr::_mapHorseBaseCFGPtr.find(dwHorseID);
    if(itr != CHorseMgr::_mapHorseBaseCFGPtr.end())
    {
        return itr->second;
    }

    return NULL;

}

SHorseUpgradeCFGPtr CHorseMgr::GetHorseUpgradeCFG(UINT32 dwHorseLevel)
{
    // UINT32 dwHorseUpradeID = SKILLANDLEVEL(dwHorseID,dwHorseLevel);

    UINT32 dwHorseUpradeID = dwHorseLevel;
    auto itr = CHorseMgr::_mapHorseUpgradeCFGPtr.find(dwHorseUpradeID);
    if(itr != CHorseMgr::_mapHorseUpgradeCFGPtr.end())
    {
        return itr->second;
    }

    return NULL;

}

void UnPack(string strTmp, TVecUINT32& vecModelID )
{
    Tokenizer tk(strTmp, "|"); // XXX: dwModelID|dwModelID
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT32 dwModelID = atoi(tk[i].c_str());
        vecModelID.push_back(dwModelID);              
        LOG_INF<<"dwModelID:"<<dwModelID;
    }

}

void CHorseMgr::LoadFromDB(const TVecHorseDB& vecHorseDB)
{
    LOG_INF<<"CHorseMgr::LoadFromDB "<<vecHorseDB.size();
    for(size_t i= 0; i < vecHorseDB.size(); ++i)
    {
        CHorsePtr pHorse(new CHorse(_rUser,*this));
        if(!pHorse)
        {
            LOG_CRI<<"CHorsePtr pHorse(new CHorse) failed !";
            return;
        }
        pHorse->LoadFromDB(vecHorseDB[i]);
        _mapHorsePtr.insert(make_pair(pHorse->GetHorseID(),pHorse));
        if(pHorse->IsMounted())
        {
            _dwMountHorseID = pHorse->GetHorseID();
            _dwMountHorseLevel = pHorse->GetHorseLevel();
            _dwHorseSpeed = pHorse->GetHorseSpeed();

        }

        //SHorseDB oHorseDB = vecHorseDB[i];
        //_dwMountHorseID = oHorseDB.dwHorseID; 
        //_dwHorseLevel = oHorseDB.dwHorseLevel;
        //_dwExp = oHorseDB.dwExp;
        //_dwPos = oHorseDB.dwPos;
        //oHorseDB.dwLock
        //if(g_OpenHorseLog)
        //LOG_INF<<"LoadFromDB _dwMountHorseID:"<<_dwMountHorseID<<" _dwHorseLevel:"<<_dwHorseLevel<<" _dwExp:"<<_dwExp<<" _dwPos:"<<_dwPos;
        //UnPack(oHorseDB.strModel,_vecModelID);
    }

    if(vecHorseDB.size())
    {
        RebuildAttr();
        UpateGroupAttr();
    }

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
        pPlayer->CalSpeed(true);
    //LOG_CRI<<"_dwHorseSpeed:"<<_dwHorseSpeed;
    return;
}

void Pack(TVecUINT32 vecModelID,string& strPack)
{
    ostringstream oStram;
    for(size_t i = 0; i<vecModelID.size(); ++i )
    {
        oStram<<vecModelID[i];
        if((i+1) != vecModelID.size())
            oStram<<"|";
    }
    strPack = oStram.str();
}


bool CHorseMgr::UnLockHorseSkillAttr(UINT32 dwHorseID, UINT32 dwPos)
{
    /*
       CHorsePtr pHorse = GetHorse(dwHorseID);
       if(NULL == pHorse)
       {
       _rUser.SendSysMsg(eMsgHorseInvalidID);
       return false;
       }

       if(!pHorse->IsSkillAttrLock(dwPos))
       {
       _rUser.SendSysMsg(eMsgHorseUnLockSkill);
       return false;
       }

    //检查条件

    pHorse->UnLockSkillAttr(dwPos);

    SHorseInfo oHorseInfo;
    pHorse->GetHorseInfo(oHorseInfo);
    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseBaseUpdateNotify(oHorseInfo));
    */
    return true;
}

//激活坐骑
bool CHorseMgr::ActiveHorse(UINT32 dwHorseID, bool bForce /* = false */)
{
    LOG_INF<<"ActiveHorse dwHorseID:"<<dwHorseID;

    if(IsActiveModel(dwHorseID))
    {
        LOG_INF<<"have Actived dwHorseID:"<<dwHorseID;
        return true;
    }

    auto itrCFG = CHorseMgr::_mapHorseBaseCFGPtr.find(dwHorseID);
    if(itrCFG == CHorseMgr::_mapHorseBaseCFGPtr.end())
    {
        LOG_INF<<"BaseCFG failed dwHorseID:"<<dwHorseID;
        _rUser.SendSysMsg(eMsgHorseInvalidID);
        return false;
    }


    if (!bForce)
    {
        UINT16 wCondID = itrCFG->second->_ItemID;
        if (!wCondID || !CGetCondMgr::Instance().TestCond(_rUser, wCondID))
            return false;

        if (!CGetCondMgr::Instance().ProcessCond(_rUser, wCondID, NLogDataDefine::ItemTo_HorseActive))
            return false;
    }


    CHorsePtr pHorse(new CHorse(_rUser,*this));
    if(NULL == pHorse)
    {
        return false;
    }

    if(!pHorse->HorseInit(dwHorseID))
    {
        return false;
    }

    _mapHorsePtr.insert(make_pair(dwHorseID,pHorse));

    //_vecModelID.push_back(dwHorseID);


    pHorse->Update2DB();

    HorseNotifyList();
    SHorseInfo oHorseInfo;
    pHorse->GetHorseInfo(oHorseInfo);
    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseInfoChangeNotifyList(eHorseOpType_Add,oHorseInfo)); 

    
    RebuildAttr();
    UpateGroupAttr();

    NotifyAttrList(dwHorseID);

    //事件
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(dwHorseID);
        vecParam.push_back(_mapHorsePtr.size());
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_HorseActive,vecParam);

        //坐骑收集活动
        g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActHorse,pPlayer->GetRoleID(),dwHorseID);
    }
        if(itrCFG->second->_Quality >= NProtoCommon::ECOLOR_PURPLE)
        {
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            pHorse->GetShowInfo(stShow);
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPurpleRideGet,vecstring,vecShow);
        }
    return true;
}

//坐骑进阶
UINT8 CHorseMgr::UpgradeHorse(UINT32 dwHorseID,bool bAll)
{

    CHorsePtr pHorse = GetHorseByID(dwHorseID);
    if(NULL == pHorse)
    {
        return 0;
    }

    UINT8 byRet = pHorse->ActiveUpgrade(bAll);

    if(!byRet)
    {
        return 0;
    }

    RebuildAttr();
    UpateGroupAttr();

    NotifyAttrList(dwHorseID);

    HorseNotifyList();

    SHorseInfo oHorseInfo;
    pHorse->GetHorseInfo(oHorseInfo);
    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseInfoChangeNotifyList(eHorseOpType_Add,oHorseInfo)); 

    if(_dwMountHorseID == dwHorseID)
    {
        _dwMountHorseLevel = pHorse->GetHorseLevel();
        BroadLookChange();
    }
    //_rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_MountsUp);

    // 记入LogServer日志
    WriteHorseLog(dwHorseID);
    return byRet;
}

void CHorseMgr::WriteHorseLog(UINT32 dwID)
{
    SHorseBaseCFGPtr pConfig = GetHorseBaseCFG(dwID);
    if(pConfig == NULL)
        return ;
    CHorsePtr pHorse = GetHorseByID(dwID);
    if(NULL == pHorse)
    {
        return ;
    }
    NLogDataDefine::SHorseLogPtr ptrLog(new NLogDataDefine::SHorseLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SHorseLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = _rUser.GetRoleID();
    rLog.sName       = pConfig->_ModelName;
    rLog.dwID        = dwID;
    rLog.dwLevel      = pHorse->GetHorseLevel();
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

//通知坐骑属性
bool CHorseMgr::NotifyAttrList(UINT32 dwHorseID)
{

    LOG_INF<<"NotifyAttrList";
    if(dwHorseID)
    {
        CHorsePtr pHorse = GetHorseByID(dwHorseID);
        if(NULL == pHorse)
        {
            return false;
        }

        const TVecFloat& vecAttr = pHorse->GetAttrVec();
        TVecFtAttrMod vecAttrInfo;
        for(UINT32 i = 0; i< vecAttr.size(); ++i)
        {
            if(vecAttr[i]>0)
            {
                SFtAttrMod oInfo;
                oInfo._eAttr = (EFighterAttr)i;
                oInfo._fValue = vecAttr[i];
                vecAttrInfo.push_back(oInfo);
                LOG_INF<<i<<"|"<<vecAttr[i];
            }
        }

        _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseAttrNotify(dwHorseID,vecAttrInfo));

        return true;
    }


    TVecFtAttrMod vecAttrInfo;
    for(UINT32 i = 0; i< _vecAttr.size(); ++i)
    {
        if(_vecAttr[i]>0)
        {
            SFtAttrMod oInfo;
            oInfo._eAttr = (EFighterAttr)i;
            oInfo._fValue = _vecAttr[i];
            vecAttrInfo.push_back(oInfo);
            LOG_INF<<i<<"|"<<_vecAttr[i];
        }
    }

    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseAttrNotify(dwHorseID,vecAttrInfo));

    return true;
}

void CHorseMgr::HorseList(TVecHorseInfo& vecHorseInfo)
{
    for(auto itr = _mapHorsePtr.begin(); itr != _mapHorsePtr.end(); ++itr)
    {
        SHorseInfo oHorseInfo;
        itr->second->GetHorseInfo(oHorseInfo);
        vecHorseInfo.push_back(oHorseInfo);
    }

    return;
}

void CHorseMgr::HorseNotifyList()
{
    LOG_INF<<"HorseNotifyList";

    //SHorseInfo oHorseInfo;
    //oHorseInfo.dwHorseID = _dwMountHorseID;
    //oHorseInfo.dwHorseLevel = _dwHorseLevel;
    //oHorseInfo.dwExp = _dwExp;
    //oHorseInfo.dwPos = _dwPos;

    //oHorseInfo.vecHorseID.insert(oHorseInfo.vecHorseID.begin(),_vecModelID.begin(),_vecModelID.end());

    //LOG_INF<<"dwHorseID:"<<_dwMountHorseID<<" dwHorseLevel:"<<_dwHorseLevel<<" dwExp:"<<_dwExp<<" dwPos:"<<_dwPos;

    TVecHorseInfo vecHorseInfo;
    for(auto itr = _mapHorsePtr.begin(); itr != _mapHorsePtr.end(); ++itr)
    {
        SHorseInfo oHorseInfo;
        itr->second->GetHorseInfo(oHorseInfo);
        LOG_INF<<"dwHorseID:"<<itr->second->GetHorseID();
        vecHorseInfo.push_back(oHorseInfo);
    }
    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseNotifyList(vecHorseInfo));

    return;
}

void CHorseMgr::RebuildAttr()
{
    _vecAttr.clear();
    for(auto itr = _mapHorsePtr.begin(); itr != _mapHorsePtr.end(); ++itr)
    {
        SHorseInfo oHorseInfo;
        _vecAttr += itr->second->GetAttrVec();
    }

    for(size_t i = 0; i < _vecAttr.size(); ++i)
    {
        if(_vecAttr[i]>0)
        {
            LOG_INF<<"attrid: "<<i<<" value:"<<_vecAttr[i];
        }
    }

    return;
}

void CHorseMgr::UpateGroupAttr()
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        CFighterManagerPtr& pFighterManager =pPlayer->GetFighterManager();
        if(pFighterManager)
        {
            pFighterManager->SetDirty(eAttrGpHorse);
        }
    }
}

bool CHorseMgr::IsActiveModel(UINT32 dwHorseID)
{
    CHorsePtr pHorse = GetHorseByID(dwHorseID);
    return NULL != pHorse;

}

bool CHorseMgr::SetHorseStatus(UINT32 dwHorseID,UINT32 dwPos)
{
    LOG_INF<<"SetHorseStatus dwPos:"<<dwPos;

    CHorsePtr pHorse = GetHorseByID(dwHorseID);
    if(NULL == pHorse)
    {
        return false;
    }

    if(eHorseStatusMounted == dwPos)
    {
        if(dwHorseID != _dwMountHorseID)
        {
            CHorsePtr pHorseMouted = GetHorseByID(_dwMountHorseID);
            if(pHorseMouted)
            {
                pHorseMouted->ChangePos(eHorseStatusUnMount);
                SHorseInfo oHorseInfo;
                pHorseMouted->GetHorseInfo(oHorseInfo);
                _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseInfoChangeNotifyList(eHorseOpType_Update,oHorseInfo)); 


            }

            _dwMountHorseID = dwHorseID;
            _dwMountHorseLevel = pHorse->GetHorseLevel();
            _dwHorseSpeed = pHorse->GetHorseSpeed(); 
            //事件
            CPlayerPtr pPlayer = _rUser.GetPlayer();
            if(pPlayer)
            {
                TVecINT32 vecParam;
                vecParam.push_back(dwHorseID);
                CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
                if(pEventMgr)
                    pEventMgr->OnEvent(eEventType_HorseGetUsed,vecParam);
            }
           _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_ActMounts, 1);


        }
    }
    else
    {
        if(dwHorseID == _dwMountHorseID)
        {
            _dwMountHorseID = 0;
            _dwMountHorseLevel = 0;
            _dwHorseSpeed = 0;
        }
    }

    pHorse->ChangePos(dwPos);

    SHorseInfo oHorseInfo;
    pHorse->GetHorseInfo(oHorseInfo);
    _rUser.SendPkg(g_HorseSvrS.BuildPkg_HorseInfoChangeNotifyList(eHorseOpType_Update,oHorseInfo)); 

    BroadLookChange();
    HorseNotifyList();

    return 0;
}

//开启坐骑系统
void CHorseMgr::Open()
{
    RebuildAttr();
    UpateGroupAttr();

    HorseNotifyList();
}

void CHorseMgr::BroadLookChange()
{


    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        pPlayer->CalSpeed(false);
        CGameMapPtr pMap= pPlayer->GetMap();
        if(NULL != pMap)
        {
            LOG_CRI<<"BroadLookChange";
            pMap->AppearToSurround(*pPlayer);
        }


        // SPlayerAppear appear;
        // pPlayer->GetPlayerAppear(appear);
        // pPlayer->NotifyMeAndSurround(g_MapProtS.BuildPkg_PlayerAppear(pPlayer->GetRoleID(), appear, pPlayer->GetPoint(), pPlayer->GetDir(), pPlayer->GetAppearState(),false));
        //pPlayer->NotifyMeAndSurround(g_HorseSvrS.BuildPkg_HorseLookChangeNotify(pPlayer->GetRoleID(),_dwMountHorseID,_dwMountHorseLevel));
    }
}

CHorsePtr CHorseMgr::GetHorseByID(UINT32 dwHorseID)
{
    auto itr = _mapHorsePtr.find(dwHorseID);
    if(itr != _mapHorsePtr.end())
    {
        return itr->second;
    }

    return NULL;

}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

