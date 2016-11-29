#include "stdafx.h"
#include "CollectionMgr.h"
#include "Tokenizer.h"
#include "Player.h"
#include "ItemMgr.h"
#include "FighterManager.h"
#include "Protocols.h"
#include "CollectionProtS.h"
TMapCollectionCFGExPtr CCollectionMgr::_mapCollectionCFGExPtr;
TVecCollectionLevelCFGExPtr CCollectionMgr::_VecCollectionLevelCFGExPtr;

CCollectionMgr::CCollectionMgr(CPlayer& rPlayer):CRegiserterEvent(eActClass_Collect,rPlayer),
    _rPlayer(rPlayer)
{
    _vecAttr.resize(EFIGHTATTR_MAX, 0.f);

    _bLog = true;
    _bGetData = false;
}

bool CCollectionMgr::CollectionInit()
{


    string strPath = Config._strConfigDir + "Conf/Table/Collection.xml";
    CCollectionLoader oCollectionLoader;
    if(!oCollectionLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oCollectionLoader._vecData.size(); ++i)
    {
       SCollectionCFG* pCFG = oCollectionLoader._vecData[i];
       if(pCFG)
       {
            SCollectionCFGExPtr pCollection(new SCollectionCFGEx);
            pCollection->CopyFrom(*pCFG);
            /*
            Tokenizer tk(pCFG->_TypePara, ","); 
            for (size_t i = 0; i < tk.size(); ++i)
            {
                UINT32 dwValue = atoi(tk[i].c_str());
                pCollection->_vecParam.push_back(dwValue);
            }
            */

            //SItemAttrCFGEx* pSItemAttrCFGEx = CItemMgr::GetItemAttrConfig(pCollection->_PropAward);
            //if(pSItemAttrCFGEx)
            //{
            //    SetIntoVec(TVecFloat& rvecAttr)
            //}

            _mapCollectionCFGExPtr.insert(make_pair(pCollection->_ID,pCollection));

         }
    }

    strPath = Config._strConfigDir + "Conf/Table/CollectionLevel.xml";
    CCollectionLevelLoader oCollectionLevelLoader;
    if(!oCollectionLevelLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oCollectionLevelLoader._vecData.size(); ++i)
    {
       SCollectionLevelCFG* pCFG = oCollectionLevelLoader._vecData[i];
       if(pCFG)
       {
            SCollectionLevelCFGExPtr pCollectionLevel(new SCollectionLevelCFGEx);
            pCollectionLevel->CopyFrom(*pCFG);
            _VecCollectionLevelCFGExPtr.push_back(pCollectionLevel);
       }
    }
    return true;
}

bool CCollectionMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("Collection.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Collection.xml";
        CCollectionLoader oCollectionLoader;
        if(!oCollectionLoader.LoadData(strPath))
        {
            return false;
        }

        for(size_t i = 0; i < oCollectionLoader._vecData.size(); ++i)
        {
           SCollectionCFG* pCFG = oCollectionLoader._vecData[i];
           if(pCFG)
           {
                SCollectionCFGExPtr pCollection(new SCollectionCFGEx);
                pCollection->CopyFrom(*pCFG);
                _mapCollectionCFGExPtr.insert(make_pair(pCollection->_ID,pCollection));

           }
        }
    }else if("CollectionLevel.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/CollectionLevel.xml";
        CCollectionLevelLoader oCollectionLevelLoader;
        if(!oCollectionLevelLoader.LoadData(strPath))
        {
            return false;
        }
        _VecCollectionLevelCFGExPtr.clear();
        for(size_t i = 0; i < oCollectionLevelLoader._vecData.size(); ++i)
        {
           SCollectionLevelCFG* pCFG = oCollectionLevelLoader._vecData[i];
           if(pCFG)
           {
                SCollectionLevelCFGExPtr pCollectionLevel(new SCollectionLevelCFGEx);
                pCollectionLevel->CopyFrom(*pCFG);
                _VecCollectionLevelCFGExPtr.push_back(pCollectionLevel);
           }
        }
    }
    return true;

}

bool CCollectionMgr::IsFinished(UINT16 dwCollectID)
{
   auto itr = _mapCollectionInfo.find(dwCollectID);
  if(itr != _mapCollectionInfo.end())
  {
      //已经完成
      if(itr->second.dwCount != 0 )
      {
          return true;
      }
 }

  return false;
  
}

void CCollectionMgr::OnFinishCollection(const SCollectionCFGExPtr& pCollectionCFGEx)
{

  UINT16 wCollectionId = pCollectionCFGEx->_ID;

  auto itr = _mapCollectionInfo.find(wCollectionId);
  if(itr != _mapCollectionInfo.end())
  {
      //已经完成
      if(itr->second.dwCount)
      {

      }
      else
      {
          itr->second.dwCount = 1;
          itr->second.dwFinishTime = time(NULL);
          OnNewFinishCollection(pCollectionCFGEx);
          UpdateToDB(itr->second);
          //_rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionInfoNotify(itr->second));
          NotifyInfo(itr->second);
      }
  }
  else
  {
      SCollectionInfo oInfo;                                 
      oInfo.dwCount = 1;                              
      oInfo.qwRoleID = _rPlayer.GetRoleID();
      oInfo.wCollectionID = wCollectionId;
      oInfo.dwFinishTime = time(NULL);
      _mapCollectionInfo.insert(make_pair(wCollectionId,oInfo)); 
      OnNewFinishCollection(pCollectionCFGEx);
      UpdateToDB(oInfo);
      //_rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionInfoNotify(oInfo));
      NotifyInfo(oInfo);
  }

  if(_bLog)
  {
      LOG_INF<<"OnFinishCollection wCollectionId: "<<wCollectionId;
  }

}

void CCollectionMgr::OnNewFinishCollection(const SCollectionCFGExPtr& pCollectionCFGEx)
{
  CUser& rUser = _rPlayer.GetUser();

  rUser.AddMoney(EMONEY_COLLECTAP,pCollectionCFGEx->_CP,NLogDataDefine::ItemFrom_NewCollection,false);

  _rPlayer.SendPkg(g_CollectionProtS.BuildPkg_APNotify(rUser.GetMoney(EMONEY_COLLECTAP)));

  OnCheckLevel();

 }

UINT32 CCollectionMgr::GetProcess(UINT16 wCollectionID)
{
  auto itr = _mapCollectionInfo.find(wCollectionID);
  if(itr != _mapCollectionInfo.end())
  {
      return itr->second.dwProcess;
  }
  return 0;
}

void CCollectionMgr::SetProcess(UINT16 wCollectionID,UINT32 dwTotal)
{
  auto itr = _mapCollectionInfo.find(wCollectionID);

  if(itr != _mapCollectionInfo.end())
  {
      itr->second.dwProcess = dwTotal;
      UpdateToDB(itr->second);
      //_rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionInfoNotify(itr->second));
      NotifyInfo(itr->second);
      
  }
  else
  {
      SCollectionInfo oInfo;
      oInfo.dwProcess = dwTotal;
      oInfo.qwRoleID  = _rPlayer.GetRoleID();
      oInfo.wCollectionID = wCollectionID;
      _mapCollectionInfo.insert(make_pair(wCollectionID,oInfo));
      UpdateToDB(oInfo);
      //_rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionInfoNotify(oInfo));
      NotifyInfo(oInfo);

  }

  if(_bLog)
  {
      LOG_INF<<"SetProcess wCollectionID: "<<wCollectionID<<" dwTotal: "<<dwTotal;
  }
}
 
void CCollectionMgr::LoadFromDB(const TVecCollectionInfo& vecCollectionInfo)
{
    RebuildAttr();
    CFighterManagerPtr& pFighterManager = _rPlayer.GetFighterManager();
    if(pFighterManager)
    {
        pFighterManager->SetDirty(eAttrGpCollection);
    }

    if(_bLog)
    {
        LOG_INF<<"CCollectionMgr::LoadFromDB "<<vecCollectionInfo.size();
    }

    for(auto itr = vecCollectionInfo.begin(); itr != vecCollectionInfo.end(); ++itr)
    {
        _mapCollectionInfo.insert(make_pair(itr->wCollectionID,*itr));
        if(_bLog)
        {
            //LOG_INF<<"wCollectionID: "<<itr->wCollectionID<<"dwCount: "<<itr->dwCount <<"dwProcess: "<<itr->dwProcess;
        }
    }

    LOG_INF<<"CCollectionMgr addevent";
    //遍历收藏
    for(auto itr = CCollectionMgr::_mapCollectionCFGExPtr.begin(); itr != CCollectionMgr::_mapCollectionCFGExPtr.end(); ++itr)
    {
        UINT32 dwCollectID = itr->second->_ID;
        if(IsFinished(dwCollectID))
        {
            continue;
        }
        AddEvent(itr->second->_EventID,dwCollectID);
    }
    LOG_INF<<"CCollectionMgr addevent end";
}

void CCollectionMgr::UpdateToDB(SCollectionInfo& rInfo,EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeCollectionInfo, eDataChange, strData);

}

//检查升级
void CCollectionMgr::OnCheckLevel()
{
    CUser& rUser = _rPlayer.GetUser();
    rUser.GetMoney(EMONEY_COLLECTAP);
    UINT16 wLevel = _rPlayer.GetCollectionLevel();
    UINT16 wNextLevel = wLevel + 1;
    UINT16 wNewLevel = wLevel;

    UINT16 wCheckWhile = 0;

    while(1)
    {
        wCheckWhile++;
        if(wCheckWhile > 100000)
        {
            LOG_CRI<<" while not End! Error!!!!";
            return;
        }
        SCollectionLevelCFGExPtr pCFG = CCollectionMgr::GetCollectionLevelCFGByLevel(wNextLevel);
        if(NULL == pCFG)
        {
            break;
        }

        if(rUser.CanSubMoney(EMONEY_COLLECTAP,pCFG->_Point))
        {
            //rUser.SubMoney(EMONEY_COLLECTAP,pCFG->_Point,false);
            wNewLevel = wNextLevel;

            //next
            wNextLevel += 1;
           _rPlayer.SendPkg(g_CollectionProtS.BuildPkg_APNotify(rUser.GetMoney(EMONEY_COLLECTAP)));
        }
        else
        {
            break;
        }
    }

    if(wLevel != wNewLevel)
    {
        if(_bLog)
        {
            LOG_INF<<"Collection upgrade: Level: "<<wLevel<<" -> "<<wNewLevel;
        }
        _rPlayer.SetCollectionLevel(wNewLevel);
        RebuildAttr();
        CFighterManagerPtr& pFighterManager = _rPlayer.GetFighterManager();
        if(pFighterManager)
        {
            pFighterManager->SetDirty(eAttrGpCollection);
        }

        _rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionLevelNotify(wNewLevel));

    }

    if(_bLog)
    {
        LOG_INF<<"EMONEY_COLLECTAP: "<< rUser.GetMoney(EMONEY_COLLECTAP);
    }
 
}

void CCollectionMgr::RebuildAttr()
{
    VECATTR_RESET(_vecAttr);

    SCollectionLevelCFGExPtr pCFG = CCollectionMgr::GetCollectionLevelCFGByLevel(_rPlayer.GetCollectionLevel());
    if(pCFG)
    {
        SItemAttrCFGEx* pSItemAttrCFGEx = CItemMgr::GetItemAttrConfig(pCFG->_PropAward);
        if(pSItemAttrCFGEx)
        {
            pSItemAttrCFGEx->SetIntoVec(_vecAttr);
            if(_bLog)
            {
            LOG_INF<<"CCollectionMgr::RebuildAttr!:"<<pCFG->_PropAward;
            for(size_t i = 0; i < _vecAttr.size(); ++i)
            {
                if(_vecAttr[i]>0)
                    LOG_INF<<"id: "<<i<<"value: "<<_vecAttr[i]; 
            }
            }
        }
    }

}

SCollectionLevelCFGExPtr CCollectionMgr::GetCollectionLevelCFGByLevel(UINT32 dwLevel)
{
    UINT32 dwIndexLevel = dwLevel -1;
    if(dwIndexLevel < _VecCollectionLevelCFGExPtr.size())
    {
        return _VecCollectionLevelCFGExPtr[dwIndexLevel];
    }
    return NULL;
}

void CCollectionMgr::GetCollectionInfo(TVecCollectionInfo& vecCollectionInfo)
{
    if(_bLog)
    {
        //LOG_INF<<"CCollectionMgr::GetCollectionInfo:"<<_mapCollectionInfo.size();
    }
    for(auto itr = _mapCollectionInfo.begin(); itr != _mapCollectionInfo.end(); ++itr)
    {
        if(_bLog)
        {
            //LOG_INF<<"wCollectionID:"<<itr->second.wCollectionID;
        }
        vecCollectionInfo.push_back(itr->second);
    }

    _bGetData = true;

}

SCollectionCFGExPtr CCollectionMgr::GetCollectCFG(UINT32 dwCollectID)
{
    auto itr = CCollectionMgr::_mapCollectionCFGExPtr.find(dwCollectID);
    if(itr != CCollectionMgr::_mapCollectionCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}
//事件中心发过来的消息
void CCollectionMgr::OnEvent(SEventInfoPtr pEventInfo)
{
    if(NULL == pEventInfo)
    {
        return;
    }

    UINT32 dwCollectID = pEventInfo->dwApplyID;

    LOG_INF<<"CCollectionMgr::OnEvent dwCollectID "<<dwCollectID;

    if(pEventInfo->dwParam1)
    {
        SetProcess(dwCollectID,pEventInfo->dwParam1);
    }

    if(eEventStatus_Finish == pEventInfo->wEventStatus)
    {
        SCollectionCFGExPtr pCollectionCFGEx =  CCollectionMgr::GetCollectCFG(dwCollectID);
        if(pCollectionCFGEx)
        {
            //if(pEventInfo->dwParam1)
            OnFinishCollection(pCollectionCFGEx);
        }
        else
        {
            LOG_CRI<<"cfg error wcollectID:"<<dwCollectID;
        }

        RemoveEvent(pEventInfo->dwEventInstID,pEventInfo->dwApplyID);
    }

}

void CCollectionMgr::NotifyInfo(SCollectionInfo& rInfo)
{
    if(!_bGetData)
    {
        return;
    }

    _rPlayer.SendPkg(g_CollectionProtS.BuildPkg_CollectionInfoNotify(rInfo));

}

