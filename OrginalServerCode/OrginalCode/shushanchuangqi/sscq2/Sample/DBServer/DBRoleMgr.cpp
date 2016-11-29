#include "stdafx.h"
#include "DBRoleMgr.h"
#include "DBConfig.h"
#include "Network/Protocols.h"
#include "GUIDMgr.h"
#include "DBRoleNameManager.h"
#include "NameCheckMgr.h"
#include "ProtoCommon.h"
#include "DBRoleDgnInfo.h"
#include "LogDataDefine.h"
#include "DBServerLog.h"
#include "DBOffLineEventManager.h"
#include "DBRoleYDTable.h"
#include "DBShipReportManager.h"

CDBRoleMgr::~CDBRoleMgr()
{
    for(auto p=_mapRole2Data.begin(),e=_mapRole2Data.end(); p!=e; ++p)
        delete p->second;
    _mapRole2Data.clear();
}

bool CDBRoleMgr::AddRoleData(SDBRoleData& rRoleData)
{
    UINT64 qwRoleID = rRoleData._qwRoleId;
    auto p = _mapRole2Data.insert(make_pair(qwRoleID, &rRoleData));
    if(!p.second)
    {
        LOG_CRI << "Role already loaded: " << qwRoleID;
        return false;
    }
    NoticeLeaveAway(qwRoleID);
    return true;
}

SDBRoleData* CDBRoleMgr::GetRoleData(UINT64 qwRoleID)
{
    auto  it = _mapRole2Data.find(qwRoleID);
    if(it == _mapRole2Data.end())
        return NULL;
    return it->second;
}
UINT8 CDBRoleMgr::GetFreeDBLine(UINT64 qwRoleID)
{
    SDBRoleData* pData = GetRoleData(qwRoleID);
    if(pData)
    {
        return pData->GetLine();
    }
    return 0;
}

void CDBRoleMgr::CreateRole(UINT64 qwRoleID, const SCreateRoleInfo & stCreateData,  function<void(SDBRoleData*, ECreateRoleResult)> cb)
{
    const string & strName  = stCreateData.strName;
    /*
    if(strName.size() > MAX_ROLENAME_LENGTH)
        return cb(NULL,eRoleNameTooLong);
    if(strName.size() < MIN_ROLENAME_LENGTH)
        return cb(NULL, eRoleNameTooShort);
    if(g_PingBiZhi.IsPingBi(strName))
        return cb(NULL, eRoleNameInvalid);
    */
    ENameLenRes res = CNameCheckMgr::CheckNameValid(const_cast<string &>(strName),MIN_ROLENAME_LENGTH,MAX_ROLENAME_LENGTH);
    switch(res)
    {
        case eNameLenTooShort:
        {
             return cb(NULL, eRoleNameTooShort);
        }
        break;
        case eNameLenTooLong:
        {
            return cb(NULL,eRoleNameTooLong);
        }
        break;
        case eNameValid:
        {
            return cb(NULL, eRoleNameInvalid);
        }
        break;
        default:
        break;
    }
    string strServerRoleName = RoleNameManager::Instance().MakeName(qwRoleID, strName);
    if (RoleNameManager::Instance().CheckNameIsExist(strServerRoleName))
        return cb(NULL,eRoleNameExist);
    if(RoleNameManager::Instance().HasRole(qwRoleID))
        return cb(NULL, eRoleExist);
    if (stCreateData.eCareer <= NProtoCommon::ECAREER_ALL || stCreateData.eCareer >=  NProtoCommon::ECAREER_MAX)
    {
        return cb(NULL, eRoleJobErr);
    }
    if (stCreateData.eSex <= NProtoCommon::ESEX_ALL || stCreateData.eSex >=  NProtoCommon::ESEX_MAX)
    {
        return cb(NULL, eRoleSexErr);
    }
    SDBRoleData* pRoleData = new SDBRoleData(qwRoleID);
    if (pRoleData == NULL)
        return cb(NULL, eRoleOtherErr);
    RoleBaseInfo stCreate;
    stCreate.byLevel = 1;
    stCreate.strName = strServerRoleName;
    stCreate.eCareer = stCreateData.eCareer;
    stCreate.eSex = stCreateData.eSex;
    stCreate.wMapID = 1; 
    stCreate.dwCreateTime = time(NULL);
    stCreate.strCreateIP= stCreateData.strIP;
    if("" != stCreateData.strInviteRoleID)
    {
        stCreate.qwInvitedID = strtoll(stCreateData.strInviteRoleID.c_str(),NULL,10);

    }
    DoCreateRole(pRoleData,stCreate,cb);
}

void CDBRoleMgr::DoCreateRole( SDBRoleData* pRoleData,const RoleBaseInfo &stCreatedata,function<void(SDBRoleData*, ECreateRoleResult)> cb )
{
    TableManagerBaseForRole* pManager = pRoleData->GetDataManagerByType(eTypeRoleBaseInfo);
    if( NULL == pManager)
    {
        return  cb(pRoleData, eRoleOtherErr);
    }

    string strData;
    COutArchive iar(strData);
    iar << stCreatedata;
    pManager->Update(strData,true);
    pManager->DumpToDB(
            [this,pRoleData,cb,stCreatedata](UINT32 nQuerynum,UINT32 nErrNum)
            {
            if (!( nQuerynum == 1 && nErrNum ==0))
            {
            delete pRoleData;
            return cb(NULL, eRoleOtherErr);
            }
            //ERR
            if (!CDBRoleMgr::Instance().AddRoleData(*pRoleData))
            {
            delete pRoleData;
            return cb(NULL, eRoleOtherErr); 
            }
            cb(pRoleData,eRoleSucceed);
            RoleNameManager::Instance().AddPlayerName(pRoleData->_qwRoleId,stCreatedata.strName,false);

            NLogDataDefine::SRegisterLogPtr ptrLog(new NLogDataDefine::SRegisterLog);
            if(NULL == ptrLog)
            return;
            NLogDataDefine::SRegisterLog& rLog = *ptrLog;

            rLog.serverId = Config._wGroup;
            rLog.playerId = pRoleData->_qwRoleId;
            rLog.playerName =  RoleNameManager::Instance().GetPlayerName(pRoleData->_qwRoleId);
            CDBServerLog::LogToDB(ptrLog);
            });
}

void CDBRoleMgr::NoticeLeaveAway(UINT64 qwRoleID)
{
    _mapLeaveAway[qwRoleID] = time(NULL) ;
}

void CDBRoleMgr::DoLoadOver(UINT64 qwRoleID,SDBRoleData* pRoleData,
                    EEnterResult result)
{
    if(result == eEnterSucceed)
    {
        AddRoleData(*pRoleData);

    }
    else
    {
        delete pRoleData;
        pRoleData = NULL;
    }
    mapLoadFun &rMap = map_InLoad[qwRoleID];
    for(auto iter = rMap.begin();iter != rMap.end();iter++)
    {
    VecLoadFun &rVec = iter->second;
    for(auto it = rVec.begin();it != rVec.end(); it++)
    {
        LoadUserFun &pFun = *it;
        if(pFun != NULL)
        {
            pFun(pRoleData,result);
        }
        
    }
    }
    map_InLoad.erase(qwRoleID);
}

//
// bref
//   SDBRoleData 人物属性基本信息

void CDBRoleMgr::LoadRoleData(UINT64 qwRoleID,ELoadSource eSource, function<void(SDBRoleData*, EEnterResult)> funcLoaded)
{
    SDBRoleData* pRoleData = GetRoleData(qwRoleID);
    if(pRoleData != NULL)
    {
        return funcLoaded(pRoleData, eEnterSucceed);
    }
    if(!InsertLoad(qwRoleID,eSource,funcLoaded))
    {
        return ;
    }
    pRoleData = new SDBRoleData(qwRoleID);
    if (NULL == pRoleData)
    {
        return DoLoadOver(qwRoleID,pRoleData,eEnterOtherErr);
    }

    TableManagerBaseForRole* pManager = pRoleData->GetDataManagerByType(eTypeRoleBaseInfo); 
    if (NULL == pManager)
    {
        return DoLoadOver(qwRoleID,pRoleData,eEnterOtherErr);
    }
    UINT64 qwLoadTimer = GetTickCount();  // 获得系统的毫秒数
    pManager->QueryDataByRoleId(qwRoleID,[qwRoleID,this,pRoleData,qwLoadTimer](INT8 Ret,UINT32 nQuerynum){
            if ( Ret != 0)
            {
            return DoLoadOver(qwRoleID,pRoleData,eEnterOtherErr);
            }
            if (nQuerynum == 0)
            {
            return DoLoadOver(qwRoleID,pRoleData,eRoleNoExist);
            }
            pRoleData->nMaxUpdata = pRoleData->_mapDataManager.size()-1;
            if (pRoleData->nMaxUpdata == 0)
            {
            return DoLoadOver(qwRoleID,pRoleData,eEnterSucceed);
            }
            pRoleData->nMaxUpdata++;//此处为离线事件所加
            pRoleData->nMaxUpdata++;//元江金船战报加
            pRoleData->nNowUpdata = 0;
            for (auto iter = pRoleData->_mapDataManager.begin();iter !=pRoleData->_mapDataManager.end();iter++)
            {
            if (iter->first == eTypeRoleBaseInfo)
            continue;

            iter->second->QueryDataByRoleId(pRoleData->_qwRoleId,[this,qwLoadTimer,pRoleData,qwRoleID](INT8 byRet,UINT32 nQuerynum){
                    pRoleData->nNowUpdata++;
                    if (pRoleData->nNowUpdata == pRoleData->nMaxUpdata)
                    {
                    return DoLoadOver(qwRoleID,pRoleData,eEnterSucceed);

                    LOG_INF<<"--------Load"<<pRoleData->_qwRoleId<<" RoleData timer is "<<GetTickCount() - qwLoadTimer<<" miscseconds";

                    }
                    }); 
            }
    g_CDBOffLineEventManager.LoadOffLineEvent(pRoleData->_qwRoleId,[this,pRoleData,qwRoleID](TVecEventOffLine vecEventOffLine)
            {
            pRoleData->nNowUpdata++;
            pRoleData->vecEventOffLine = vecEventOffLine;
            if (pRoleData->nNowUpdata == pRoleData->nMaxUpdata)
            {
            return DoLoadOver(qwRoleID,pRoleData,eEnterSucceed);
            }

            });
    g_CDBShipReportManager.LoadShipReport(pRoleData->_qwRoleId,[this,pRoleData,qwRoleID](TVecShipReport vecShipReport)
            {
            pRoleData->nNowUpdata++;
            pRoleData->vecShipReport = vecShipReport;
            if (pRoleData->nNowUpdata == pRoleData->nMaxUpdata)
            {
            return DoLoadOver(qwRoleID,pRoleData,eEnterSucceed);
            }
            });

    });
}

void CDBRoleMgr::OnRecv_RoleDataUpdate(
        UINT64 qwRoleId, //角色Id
        EDataType eDataType, //更新数据块
        EDataChange eUpdateType, //更新类型，增加，删除，修改
        const std::string& strupData //更新数据
        )
{
    LoadRoleData(qwRoleId,eLoadUpdate, 
            [this, qwRoleId, eDataType, eUpdateType, strupData](SDBRoleData* pData, EEnterResult eResult)
            {
                if(eResult != eEnterSucceed)
                    return;
                TableManagerBaseForRole* pManager = pData->GetDataManagerByType(eDataType);
                if (pManager == NULL)
                    return;

                string strData(strupData);
                switch(eUpdateType)
                {
                    case eOpAdd:
                        {
                            switch (eDataType)
                            {
                                case eTypeCittaInfo:
                                case eTypeTrumpInfo:
                                case eTypeFashionInfo:
                                case eTypeGemstone:
                                case eTypeEquipTrumpInfo:
                                    {
                                        TableManagerBaseForRole* pManager = pData->GetDataManagerByType(eTypeItemInfo);
                                        if (pManager)
                                            pManager->Update(strData, true);
                                        else
                                            return;
                                        TableManagerBaseForRole* pEXManager = pData->GetDataManagerByType(eDataType);
                                        if(pEXManager)
                                            pEXManager->Update(strData, true);
                                    }
                                    break;

                                case eTypeRoleBaseInfo:
                                    break;
                                default:
                                    pManager->Update(strData, true);
                            }

                        }
                        break;

                    case eOpDel:
                        {
                            switch (eDataType)
                            {
                                case eTypeCittaInfo:
                                case eTypeTrumpInfo:
                                case eTypeFashionInfo:
                                case eTypeGemstone:
                                case eTypeEquipTrumpInfo:
                                    {
                                        TableManagerBaseForRole* pManager = pData->GetDataManagerByType(eTypeItemInfo);
                                        if (pManager)
                                            pManager->DelData(strData);
                                        else
                                            return;
                                        TableManagerBaseForRole* pEXManager = pData->GetDataManagerByType(eDataType);
                                        if(pEXManager)
                                            pEXManager->DelData(strData);
                                    }
                                    break;
                                case eTypeRoleBaseInfo:
                                    break;

                                default:
                                    pManager->DelData(strData);
                            }

                        }
                        break;

                    case eOpUpdate:
                        {
                            switch (eDataType)
                            {
                                case eTypeCittaInfo:
                                case eTypeTrumpInfo:
                                case eTypeFashionInfo:
                                case eTypeGemstone:
                                case eTypeEquipTrumpInfo:
                                    {
                                        TableManagerBaseForRole* pManager = pData->GetDataManagerByType(eTypeItemInfo);
                                        if (pManager)
                                            pManager->Update(strData, false);
                                        else
                                            return;
                                        TableManagerBaseForRole* pEXManager = pData->GetDataManagerByType(eDataType);
                                        if(pEXManager)
                                            pEXManager->Update(strData, false);
                                    }
                                    break;

                                    //  case eTypeRoleBaseInfo:
                                    //    break;
                                default:
                                    pManager->Update(strData, false);
                            }
                        }
                        break;

                    default:
                        break;
                }

                if(pData->HasUpdateNum())
                    this->CheckRoleState(pData, true);
            });
}

bool CDBRoleMgr::CheckRoleState(SDBRoleData* pRoleData,bool IsUpdate)
{
    if (IsUpdate)
    {
        if (pRoleData->_eUpdateDataStatus != SDBRoleData::DATAUPDATA_WILL)
        {
            pRoleData->_eUpdateDataStatus = SDBRoleData::DATAUPDATA_WILL;
            _queueUpdate.push(pRoleData->_qwRoleId);
        }
    }
    else
    {
        if( pRoleData->_eOffLineStatus != SDBRoleData::IN_OFFQUEUE)
        {
            pRoleData->_eOffLineStatus = SDBRoleData::IN_OFFQUEUE;
            _queueOffLine.push(pRoleData->_qwRoleId);
        }
    }
    return true;
}

void CDBRoleMgr::GateOff(UINT32 dwGateOff)
{
    for (auto iter = _mapRole2Data.begin();iter != _mapRole2Data.end(); ++iter)
    {
        UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(iter->first);
        if (dwGateID == dwGateOff)
        {
            iter->second->SetUserState(eUserLeaveOff);
            CheckRoleState(iter->second,false);
            if (iter->second->nServerId != 0)
            {
                g_Game2DBCommS.SendSvr_UserLogoutNtf(&(iter->second->nServerId),1,iter->first,eLeaveExcept);
                iter->second->nServerId = 0;
            }
        }
    }
}

void CDBRoleMgr::SavePlayer(bool bIsAll)
{
    //服务器关闭所有在线玩家置离线时间
    if(bIsAll)
    {
        for(auto iter = _mapRole2Data.begin();iter != _mapRole2Data.end();iter++)
        {
            iter->second->SetUserState(eUserLeaveAway);
        }
    }

    UINT32 TotalUpdate = 500;
    UINT32 CurrentNum = 0;
    while( !_queueUpdate.empty()&& (bIsAll || CurrentNum < TotalUpdate))
    {
        SDBRoleData* pData =  GetRoleData(_queueUpdate.front());
        _queueUpdate.pop();
        if(pData == NULL)
        {
            continue;
        }
        pData->_eUpdateDataStatus = SDBRoleData::DATAUPDATE_NONE;
        pData->nMaxUpdata = pData->_mapDataManager.size();
        CurrentNum +=pData->UpDateNum();
        pData->nNowUpdata = 0;
        for (auto iter = pData->_mapDataManager.begin();iter != pData->_mapDataManager.end();iter++)
        {
            if(iter->second->GetUpdataNum())
            {
                iter->second->DumpToDB([pData,this](UINT32 Num,UINT32 nErrNum){
                        pData->nNowUpdata++;
                        if (pData->nNowUpdata == pData->nMaxUpdata)
                        {
                        if(pData->HasUpdateNum())
                        {
                        this->CheckRoleState(pData, true);
                        }
                        if(pData->GetUserState() == eUserLeaveOff||pData->GetUserState() == eUserNone)
                        {
                        this->CheckRoleState(pData, false);
                        }
                        }
                        });
            }
            else
            {
                pData->nNowUpdata++;  
                if(pData->nNowUpdata == pData->nMaxUpdata)
                {
                    if(pData->HasUpdateNum()) 
                    {
                        this->CheckRoleState(pData, true);
                    }
                    if (pData->GetUserState() == eUserLeaveOff)
                    {
                        this->CheckRoleState(pData, false); 
                    }
                }
            }
        }
    }
}

void CDBRoleMgr::TimerCheck(time_t tNow)
{
    for (auto iter = _mapLeaveAway.begin();iter != _mapLeaveAway.end();)
    {
        SDBRoleData* pData = GetRoleData(iter->first);
        if (pData == NULL)
        {
            iter = _mapLeaveAway.erase(iter);
            continue;
        }
        if(pData->GetUserState() != eUserLeaveAway &&  pData->GetUserState() != eUserNone)
        {
            iter = _mapLeaveAway.erase(iter);
            continue;
        }
        if (tNow - iter->second > 15 * 60 )
        {
            pData->SetUserState(eUserLeaveOff);
            CheckRoleState(pData, false);
            iter = _mapLeaveAway.erase(iter);
            continue;
        }
        ++iter;
    }
    //数据更新
    SavePlayer(false);
    //离线数据处理
    UINT32 dwCurrentSize = _mapRole2Data.size();
    UINT32 dwHighMark =5000;
    UINT32 dwLowMark  =4000;
    UINT32 dwReuce =0;
    if (dwCurrentSize > dwHighMark)
    {
        dwReuce = dwCurrentSize -  dwLowMark;
        LOG_CRI << "Remove Data size is " << dwReuce;
    }
    while(dwReuce > 0 && !_queueOffLine.empty())
    {
        SDBRoleData* pData = GetRoleData(_queueOffLine.front());
        do
        {
            if(pData == NULL)
            {
                break;
            }
            pData->_eOffLineStatus = SDBRoleData::OUTOF_OFFQUEUE;
            if (pData->_eUpdateDataStatus == SDBRoleData::DATAUPDATA_WILL)
            {
                break;
            }
            if( pData->HasUpdateNum())
            {
                this->CheckRoleState(pData, true);
                break;
            }
            if (pData->GetUserState() != eUserLeaveOff && pData->GetUserState() != eUserNone)
            {
                break;
            }
            _mapRole2Data.erase(pData->_qwRoleId);
            delete pData;
            pData = NULL;
        }while(0);
        --dwReuce;
        _queueOffLine.pop();
    }
    static UINT32 _dwLastCountTimer = 0;
    if( tNow > _dwLastCountTimer +10*60 )
    {
        _dwLastCountTimer = tNow;
        //LOG_CRI << "Now DB keep data is " << _mapRole2Data.size();
        //LOG_CRI << "Now DB _queueUpdate is " << _queueUpdate.size();
        //LOG_CRI << "Now DB _queueOffLine is " << _queueOffLine.size();
    }

}

bool CDBRoleMgr::EnterGame(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    if (SendDataToGameServer(rRoleData,eEnterLogin,vecPlatformParam, vecString))
        g_RoleEnterGameProtSvrS.SendClt_EnterGameAck(&rRoleData._qwRoleId,1,eEnterSucceed,time(NULL));
    else
        g_RoleEnterGameProtSvrS.SendClt_EnterGameAck(&rRoleData._qwRoleId,1,eEnterOtherErr,time(NULL));
    rRoleData.SetUserState(eUserInGame);
    return true;
}

bool CDBRoleMgr::ReEnterGame(SDBRoleData& rRoleData,UINT32 dwGateId, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    g_Game2DBCommS.SendSvr_UserReEnterNotify(&rRoleData.nServerId, 1, rRoleData._qwRoleId, dwGateId, vecPlatformParam, vecString);
    g_RoleEnterGameProtSvrS.SendClt_EnterGameAck(&rRoleData._qwRoleId,1,eEnterSucceed,time(NULL));
    rRoleData.SetUserState(eUserInGame);
    return true;
}

bool CDBRoleMgr::AddLoadOrCreate(UINT64 qwRoleId)
{
    if (_setLoadOrCreate.find(qwRoleId) != _setLoadOrCreate.end())
    {
        return false;
    }
    _setLoadOrCreate.insert(qwRoleId);
    return true;
}

void CDBRoleMgr::RemoveLoadOrCreate(UINT64 qwRoleId)
{
    _setLoadOrCreate.erase(qwRoleId);
}

void CDBRoleMgr::GetAllInfo(NRoleInfoDefine::RoleDataInfo &rInfo,SDBRoleData& rRoleData)
{
    for (auto iter = rRoleData._mapDataManager.begin(); iter != rRoleData._mapDataManager.end();iter++)
    {
        iter->second->GetALLInfo(rInfo);
    }
    rInfo.stBaseInfo.strName = RoleNameManager::Instance().MakeName(rRoleData._qwRoleId, rInfo.stBaseInfo.strName);
    rInfo.qwRoleId = rRoleData._qwRoleId;
    rInfo.vecEventOffLine = rRoleData.vecEventOffLine;
    rInfo.vecShipReport =  rRoleData.vecShipReport;

}

bool CDBRoleMgr::SendDataToGameServer(SDBRoleData& rRoleData,EEnterType eEnterType,const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    UINT16 wMapID = rRoleData.GetMapID();
    UINT32 dwGameSvrIdx = CDBConfig::Instance().GetSvrIDByMapID(wMapID);
    UINT32 dwGateId = NetMgr.GetGateHandler()->GetGateID(rRoleData._qwRoleId);
    if(dwGateId == 0 || dwGameSvrIdx == 0 )
    {
        LOG_CRI << "dwGateID||dwGameSvrIdx is 0! UsrID: " <<rRoleData._qwRoleId;
        return false;
    }
    rRoleData.nServerId = dwGameSvrIdx;
    NRoleInfoDefine::RoleDataInfo  Info; 
    GetAllInfo(Info,rRoleData);
    g_Game2DBCommS.SendSvr_UserLoginNtf(&dwGameSvrIdx, 1, eEnterType, vecPlatformParam, vecString, dwGateId, rRoleData._qwRoleId,Info);
    return true;
}

bool CDBRoleMgr::JumpGameServer(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    return SendDataToGameServer(rRoleData,eEnterJump,vecPlatformParam, vecString);
}

bool CDBRoleMgr::JumpToCrossServer(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    return SendDataToGameServer(rRoleData,eEnterToCross,vecPlatformParam, vecString);
}

bool CDBRoleMgr::JumpFromCrossServer(SDBRoleData& rRoleData ,const TVecPlatformParam& vecPlatformParam, const TVecString& vecString)
{
    return SendDataToGameServer(rRoleData,eEnterFromCross,vecPlatformParam, vecString);
}

void CDBRoleMgr::KickUserOffLine(UINT64 qwUsrID, bool bException)
{
    UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
    if(dwGateID == 0)
    {
        LOG_CRI << "dwGateID is 0! UsrID: " << qwUsrID;
        return;
    }
    LOG_INF << "KickUserOffLine! UsrID: " << qwUsrID;
    ELeaveType eLeaveType = bException ? eLeaveExcept : eLeaveKick;
    g_Gate2DBCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, eLeaveType);
}
bool  CDBRoleMgr::OnRecv_SaveOffLineDgnInfo(
        UINT64 qwUsrID, //账号ID
        UINT32 dwDgnType, //副本类型
        UINT8 byIsFail //0:表示成功保存，1：表示失败保存
        )
{       
    LoadRoleData(qwUsrID,eLoadUpdate, [this, qwUsrID, dwDgnType, byIsFail](SDBRoleData* pData, EEnterResult eResult) {
            if(eResult != eEnterSucceed)
            return ;

            TableManagerBaseForRole* pManager = pData->GetDataManagerByType(eTypePlayerDgn);
            if (pManager == NULL)
            return;
            DBRoleDgnTableManager* pGdnManager = dynamic_cast<DBRoleDgnTableManager*>(pManager);
            if(pGdnManager == NULL)
            {
            return ;
            }
            if (pGdnManager->OnRecv_SaveOffLineDgnInfo(dwDgnType,byIsFail))
            {
            this->CheckRoleState(pData,true);
            }
            else if(pData->GetUserState() == eUserNone)
            {
            this->CheckRoleState(pData,false);
            }
            });

    return true;
}

void CDBRoleMgr::GetAllPlatformParam(UINT32 dwPageSize)
{
    if (!dwPageSize)
    {
        LOG_CRI << "dwPageSize == 0.";
        return;
    }

    for (auto& rPair : CDBRoleYDTableManager::s_mapRoleYDTable)
    {
        if (rPair.second)
        {
            delete rPair.second;
            rPair.second = NULL;
        }
    }
    CDBRoleYDTableManager::s_mapRoleYDTable.clear();

    QueryPlatformParamData(dwPageSize,
            [dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
            TVecUINT64 vecRoleID;
            TVecPlatformParam vecPlatformParam;
            UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
            if(dwTotalSize % dwPageSize != 0)
            dwTotalPage++;
            UINT32 dwTotalCount = 0;
            if(dwTotalPage == 0)//无记录
            {
            SendPlatformParamToCenter(dwTotalPage, dwTotalSize, vecRoleID, vecPlatformParam);
            return ;
            }
            UINT32 dwIndex = 0;
            for (auto& rPair : CDBRoleYDTableManager::s_mapRoleYDTable)
            {
            ++dwTotalCount;
            ++dwIndex;
            if (!rPair.second)
            continue;
            rPair.second->GetAllInfo(vecRoleID, vecPlatformParam);
            if(dwIndex == dwPageSize)
            {
                SendPlatformParamToCenter(dwTotalCount,dwTotalSize, vecRoleID, vecPlatformParam);     
                vecPlatformParam.clear();
                vecRoleID.clear();
                dwIndex = 0;
            }
            }
    if (dwIndex)
        SendPlatformParamToCenter(dwTotalCount, dwTotalSize, vecRoleID, vecPlatformParam);     
            });
}

void CDBRoleMgr::SendPlatformParamToCenter(UINT32 dwTotalCount, UINT32 dwTotalSize, const TVecUINT64& rvecRoleID, const TVecPlatformParam& rvecPlatform) const
{
    g_Center2DBCommS.Send_PlatformParamInfoNotify(dwTotalCount, dwTotalSize, rvecRoleID, rvecPlatform);
}

void CDBRoleMgr::QueryPlatformParamData(UINT32 dwPageSize, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(distinct(qwRoleID)) as dwCount from tblroleyd";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,
            [this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
            {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
            UINT32 dwCount = 0;
            if(byRet == 0 && rDataRes.size()== 1)
            {
            mysqlpp::Row& rRow = rDataRes[0];
            GET_UINT_SAME(dwCount);
            }
            else
            {
            queryfun(byRet,dwCount);
            return ;
            }
            if(dwCount == 0)
            {
            queryfun(byRet, dwCount);
            return ;
            }

            UINT32 dwTotalPage = (dwCount % dwPageSize != 0) ? (dwCount/dwPageSize + 1) : (dwCount / dwPageSize);
            for(UINT32 dwPage = 0; dwPage != dwTotalPage; dwPage++)
            {
                mysqlpp::SQLStream querysql(NULL);
                querysql << "SELECT distinct(qwRoleID) FROM tblroleyd LIMIT ";
                querysql << dwPage * dwPageSize << "," << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,
                        [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                        UINT32 dwDataCount = rDataRes.size();
                        for (UINT32 dwIndex = 0; dwIndex< dwDataCount; ++ dwIndex)
                        {
                        mysqlpp::Row& rRow = rDataRes[dwIndex];
                        UINT64 qwRoleID;
                        GET_UBIGINT_SAME(qwRoleID);
                        if (!qwRoleID)
                        continue;
                        auto it = CDBRoleYDTableManager::s_mapRoleYDTable.find(qwRoleID);
                        CDBRoleYDTableManager* pManager = NULL;
                        if (it == CDBRoleYDTableManager::s_mapRoleYDTable.end())
                        pManager = new CDBRoleYDTableManager(qwRoleID, CDBMgr::Instance().GetFreeLine());
                        else
                        pManager = it->second;
                        pManager->QueryDataByRoleId(qwRoleID,
                            [dwCount, queryfun, qwLoadTimer, pManager, qwRoleID](INT8 byRet, UINT32 nQuerynum)
                            {
                            CDBRoleYDTableManager::s_mapRoleYDTable[qwRoleID] = pManager;
                            if(CDBRoleYDTableManager::s_mapRoleYDTable.size() == dwCount)
                            {
                            LOG_WRN << "s_mapRoleYDTable.size() = " << CDBRoleYDTableManager::s_mapRoleYDTable.size() << ", dwCount = " << dwCount << ".";
                            queryfun(byRet, dwCount);
                            LOG_INF << "Load tblroleyd is " << GetTickCount() - qwLoadTimer << " miscseconds. Count: " << dwCount << ".";
                            }
                            });
                        }
                        });
            }
            });
}

bool CDBRoleMgr::InsertLoad(UINT64 qwRoleID,ELoadSource eSource,LoadUserFun fun)
{
    bool bFirst = map_InLoad.find(qwRoleID) == map_InLoad.end();
    map_InLoad[qwRoleID][eSource].push_back(fun);
    return bFirst;
    
}

