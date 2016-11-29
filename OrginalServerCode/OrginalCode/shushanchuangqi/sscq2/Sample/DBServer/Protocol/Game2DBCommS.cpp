#include "stdafx.h"
#include "Protocols.h"
#include "DBRoleMgr.h"
#include "DBBossMgr.h"
#include "DBRoleNameManager.h"
#include "DBOffLineEventManager.h"
#include "DBMallDiscount.h"
#include "DBGuildNewBattleHistoryTable.h"
//接收：心跳
void CGame2DBCommS::OnRecv_KeepAlive(
        )
{
    UINT32 dwSvrID = GetCurSvrID();
    NetMgr.GetSvrHandler(eHostGame)->OnKeepAlive(dwSvrID);
}

//接收：DBServer状态请求
bool CGame2DBCommS::OnRecv_GetStatus(
        shared_func<SGetStatusAck>& fnAck //返回回调函数
        )
{
    return Config._bInited && Config.IsPreLoad();
}

//接收：更新玩家充值仙石信息
void CGame2DBCommS::OnRecv_UpdateRecharge(
    const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
)
{
    //g_CDBRechargeManager.Update(oRecharge);
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Replace into tblrecharge(strNo,qwRoleID,wGoldID,dwCount,dwGold,byStatus,dwHappenedTime) Values(";
    ostr <<"'"<< (mysqlpp::sql_char)oRecharge.strNo<<"'";
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)oRecharge.qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)oRecharge.wGoldID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)oRecharge.dwCount;
    ostr << "," <<(mysqlpp::sql_int_unsigned)oRecharge.dwGold;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)oRecharge.byStatus;
    ostr << "," <<(mysqlpp::sql_int_unsigned)oRecharge.dwHappenedTime;
    ostr << ");";

    CDBMgr::Instance().DoRechargeModifyQuery(ostr.str(),NULL,[ostr](INT8 byRet, mysqlpp::SimpleResult& res)
            {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << ostr.str() << "result:" << byRet;
            });
}

inline bool Equal(float fLeft, float fRight)
{
    return fabsf(fLeft - fRight) < 0.1;
}

void CGame2DBCommS::OnRecv_RoleDataUpdate(UINT64 qwRoleId, NRoleInfoDefine::EDataType eDataType, NProtoCommon::EDataChange eChangeType, const string& strUpdate)
{
    CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(qwRoleId,eDataType,eChangeType,strUpdate);
}

//接收：请求保存账号数据
bool CGame2DBCommS::OnRecv_SaveUserDataReq(
            UINT64 qwUsrID, //账号ID
            ESaveType eSaveType, //保存类型
            const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
            shared_func<SSaveUserDataReqAck>& fnAck //返回回调函数
	)
{
    TVecString vecString;
    SDBRoleData* pUserData = CDBRoleMgr::Instance().GetRoleData(qwUsrID);
    if(pUserData == NULL)
    {
        LOG_CRI << "Can't find UserData! qwUsrID: " << qwUsrID;
        return false;
    }

    switch(eSaveType)
    {
        case eSaveAway:
            pUserData->SetUserState(eUserLeaveAway);
            CDBRoleMgr::Instance().NoticeLeaveAway(qwUsrID);
            break;
        case eSaveOff:
        case eSaveKick:
            pUserData->SetUserState(eUserLeaveOff);
            CDBRoleMgr::Instance().CheckRoleState(pUserData,false);
            break;
        case eSaveExcept:
            pUserData->SetUserState(eUserLeaveOff);
            CDBRoleMgr::Instance().CheckRoleState(pUserData,false);
            return true;
        case eSaveData:
        case eSaveJump:
        case eSaveToCross:
        case eSaveFromCross:
            break;
        default:
            LOG_CRI << "Wrong SaveType: " << eSaveType;
            goto FAIL;
    }

    if(eSaveType != eSaveJump && eSaveType != eSaveToCross && eSaveType != eSaveFromCross)
        return true;
    switch(eSaveType)
    {
        case eSaveJump:
            if (CDBRoleMgr::Instance().JumpGameServer(*pUserData, vecPlatformParam, vecString))
                return true;
            break;
        case eSaveToCross:
            if (CDBRoleMgr::Instance().JumpToCrossServer(*pUserData, vecPlatformParam, vecString))
                return true;
            break;
        case eSaveFromCross:
            if (CDBRoleMgr::Instance().JumpFromCrossServer(*pUserData, vecPlatformParam, vecString))
                return true;
            break;
        default:
            break;
    }

FAIL:
    LOG_CRI << "Save User Data fails! eSaveType: " << eSaveType << ", UsrID: " <<qwUsrID;
    CDBRoleMgr::Instance().KickUserOffLine(qwUsrID);
    return false;

}
bool  CGame2DBCommS::OnRecv_SaveOffLineDgnInfo(
        UINT64 qwUsrID, //账号ID
        UINT32 dwDgnType, //副本类型
        UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
        shared_func<SSaveOffLineDgnInfoAck>& fnAck //返回回调函数
        ) 
{
    return CDBRoleMgr::Instance().OnRecv_SaveOffLineDgnInfo(qwUsrID,dwDgnType,byIsFail);
}

bool CGame2DBCommS::OnRecv_LoadOffLineUserData(
        UINT64 qwRoleID, //账号ID
        shared_func<SLoadOffLineUserDataAck>& fnAck //返回回调函数
        )

{
    CDBRoleMgr::Instance().LoadRoleData(qwRoleID,eLoadOterSvr,[fnAck,this](SDBRoleData* pData, EEnterResult eResult)
            {
            if(eResult != eEnterSucceed)
            {
            fnAck->byRet = 1;
            }
            else
            {
            if(pData != NULL)
            {
            CDBRoleMgr::Instance().GetAllInfo(fnAck->RoleData,*pData);
            if(pData->GetUserState() == eUserNone)
            {
            CDBRoleMgr::Instance().CheckRoleState(pData,false);
            }
            }

            }
            fnAck(true);
            });

    return true;
}

//接收：加载世界BOSS信息
bool CGame2DBCommS::OnRecv_LoadWorldBossInfo(
        shared_func<SLoadWorldBossInfoAck>& fnAck //返回回调函数
        )
{
    CDBBossMgr::Instance().LoadWorldBoss(fnAck);
    return true;
}

//接收：存储世界BOSS信息
void CGame2DBCommS::OnRecv_SaveWorldBossInfo(
        const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
        )
{
    CDBBossMgr::Instance().SaveWorldBoss(sWorldBossInfo);
}

bool CGame2DBCommS::OnRecv_GetUserIDFromName(
        const std::string& strName, //主角色名称
        shared_func<SGetUserIDFromNameAck>& fnAck //返回回调函数
        ) 
{
    fnAck->qwUsrID = RoleNameManager::Instance().GetPlayerIdByName(strName);
    return true;   
}
//接收：获得玩家战报信息
bool CGame2DBCommS::OnRecv_GetBattleReport(
        UINT64 qwRoleID, //玩家的ID
        NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
        NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
        shared_func<SGetBattleReportAck>& fnAck //返回回调函数
        ) 
{
    g_Center2DBCommS.GetBattleReportFun(qwRoleID,eBattleType,eAction,[fnAck](INT8 byRet,NRoleInfoDefine::TVecBattleRePort vecReport){
            if(byRet != 0)
            {
            fnAck(false);
            return ;
            }
            fnAck->vecReport = vecReport;
            fnAck(true);
            return;
            });
    return true;

    //return g_Center2DBCommS.OnRecv_GetBattleReport(qwRoleID,eBattleType,eAction,fnAck);

}

//接收：增加玩家战报信息
bool CGame2DBCommS::OnRecv_AddBattleReport(
        UINT64 qwRoleID, //
        const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
        UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
        shared_func<SAddBattleReportAck>& fnAck //返回回调函数
        ) 
{
    //return g_Center2DBCommS.OnRecv_AddBattleReport(qwRoleID,sReport,byNum,fnAck);
    g_Center2DBCommS.AddBattleReportFun(qwRoleID,sReport,byNum,[fnAck](INT8 byRet,TVecUINT64 vecBattleID)
            {
            if(byRet != 0)
            {
            fnAck(false);
            return;
            }
            fnAck->vecBattleID = vecBattleID;
            fnAck(true);

            });
    return true;
}
//接收：增加离线事件
void CGame2DBCommS::OnRecv_AddOffLineEvent(
        const TVecUINT64& vecRoleID, //
        const NRoleInfoDefine::SEventOffLine& sEventData
        ) 
{
    //TODO:

    g_CDBOffLineEventManager.AddOffLineEvent(eHostGame,vecRoleID,sEventData);
}


//接收：删除离线事件
void CGame2DBCommS::OnRecv_DelOffLineEvent(
        UINT64 qwRoleID, //
        const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
        ) 
{
    //TODO:
    g_CDBOffLineEventManager.DelOffLineEvent(qwRoleID,vecEventType);
}

//接收：加载商城限购信息
bool CGame2DBCommS::OnRecv_LoadMallDiscount(
    shared_func<SLoadMallDiscountAck>& fnAck //返回回调函数
)
{
    g_CDBMallDiscountManager.GetALLInfo(fnAck->vecDisItems);
    return true;
}

//接收：更新商城限购
void CGame2DBCommS::OnRecv_UpdateMallDiscount(
    NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
    const NMallProt::TVecDiscount& vecDisItems //限购道具
)
{
    if (eUpdateType == eOpUpdate || eUpdateType == eOpAdd)
        g_CDBMallDiscountManager.Update(vecDisItems);
    else if (eUpdateType == eOpDel)
        g_CDBMallDiscountManager.DelAllData();
}

//接收：获取新帮派战历史
void CGame2DBCommS::OnRecv_GetNewGuildBattleHistory(
        )
{
    UINT32 dwID = GetCurSvrID();
    CDBGuildNewBattleHistoryTableManager::Instance().QueryAllData(
            [this, dwID](INT8 byRet, UINT32 dwCount)
            {
                if (byRet != 0)
                {
                    TVecDBGuildNewBattleHistoryInfo vecInfo;
                    g_Game2DBCommS.SendSvr_NewGuildBattleHistoryNotify(&dwID, 1, 0, 0, vecInfo);
                }
                else
                {
                    UINT32 dwIndex = 0;
                    UINT32 dwMaxCount = 0;
                    UINT32 dwCount = 20;
                    UINT32 dwCurIndex = 0;
                    do
                    {
                        TVecDBGuildNewBattleHistoryInfo vecInfo;
                        CDBGuildNewBattleHistoryTableManager::Instance().GetAllInfo(vecInfo, dwIndex, dwCount, dwCurIndex, dwMaxCount);
                        dwIndex = dwCurIndex + vecInfo.size();
                        g_Game2DBCommS.SendSvr_NewGuildBattleHistoryNotify(&dwID, 1, dwIndex, dwMaxCount, vecInfo);
                        if (dwIndex >= dwMaxCount)
                            break;
                    } while (1);
                }
                

            });
}

//接收：新增新帮派战历史
void CGame2DBCommS::OnRecv_AddNewGuildBattleHistory(
        const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
        )
{
    string strData;
    COutArchive ar(strData);

    ar << vecInfo;

    CDBGuildNewBattleHistoryTableManager::Instance().InsertNewData(strData);
}

