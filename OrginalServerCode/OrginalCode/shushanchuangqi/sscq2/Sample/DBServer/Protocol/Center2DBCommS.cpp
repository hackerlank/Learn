#include "Center2DBCommS.h"
#include "stdafx.h"
#include "Protocols.h"
#include "DBRoleMgr.h"
#include "MailProt.h"
#include "DBRoleNameManager.h"
#include "DBArenaManger.h"
#include "DBRoleCittaTable.h"
#include "DBRoleFashionTable.h"
#include "DBDemonTower.h"
#include "Parameter.h"
#include "DBRoleRankMgr.h"
#include "DBTripodTable.h"
#include "DBTripodHelpTable.h"
#include "DBOffLineEventManager.h"
#include "DBNoticeTable.h"
#include "DBTripodLogTable.h"
#include "DBWonderPrizeTable.h"
#include "DBWonderRetainTable.h"
#include "Game2CenterComm.h"
#include "DBShipManger.h"
#include "DBCenterDataTable.h"
#include "DBShipReportManager.h"
#include "DBRoleGodMonsterTable.h"
#include "DBRoleLimitPrizeTable.h"
#include "DBActivityCenterDBTable.h"
#include "DBLadderRobotManger.h"
using namespace NMailProt;

//接收：心跳
void CCenter2DBCommS::OnRecv_KeepAlive(
        )
{
    UINT32 dwSvrID = GetCurSvrID();
    NetMgr.GetSvrHandler(eHostCenter)->OnKeepAlive(dwSvrID);
}

//接收：DBServer状态请求
bool CCenter2DBCommS::OnRecv_GetStatus(
        shared_func<SGetStatusAck>& fnAck //返回回调函数
        )
{
    return Config._bInited &&  Config.IsPreLoad();
}

//接收：插入玩家充值仙石信息(未创角预先充值)
void CCenter2DBCommS::OnRecv_InsertRecharge(
        const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
        )
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrecharge(strNo,qwRoleID,wGoldID,dwCount,dwGold,byStatus,dwHappenedTime) Values(";
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

//接收：加载玩家未创角预先充值的仙石信息
bool CCenter2DBCommS::OnRecv_LoadPrepaid(
        shared_func<SLoadPrepaidAck>& fnAck //返回回调函数
        )
{
    mysqlpp::SQLStream opstr(NULL);
    opstr << "select * from tblprepaid;";
    CDBMgr::Instance().DoRechargeSelectQuery(opstr.str(),NULL,[fnAck,opstr](INT8 byRet, mysqlpp::StoreQueryResult& dataRes)
            {
            UINT32 dwCount = dataRes.size();
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << opstr.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
            if(byRet != 0)
            {
            fnAck(true);
            return;
            }
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
            mysqlpp::Row& rRow = dataRes[dwIndex];
            SPrepaid oPrepaid(rRow["qwRoleID"], rRow["dwGold"]);
            fnAck->vecPrepaid.push_back(oPrepaid);
            }
            fnAck(true);
            });

    return true;
}

//接收：更新玩家未创角预先充值信息
void CCenter2DBCommS::OnRecv_UpdatePrepaid(
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        UINT64 qwRoleID, //玩家ID
        UINT32 dwGold //仙石数量
        )
{
    mysqlpp::SQLStream opstr(NULL);
    if (eUpdateType == eOpDel)
    {
        opstr << "Delete from tblprepaid Where qwRoleID = ";
        opstr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
        opstr << ";";
    }
    else
    {
        opstr << "Replace into tblprepaid(qwRoleID,dwGold) Values(";
        opstr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
        opstr << "," <<(mysqlpp::sql_int_unsigned)dwGold;
        opstr << ");";
    }
    CDBMgr::Instance().DoRechargeModifyQuery(opstr.str(),NULL,[opstr](INT8 byRet, mysqlpp::SimpleResult& res)
            {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << opstr.str() << "result:" << byRet;
            });

    if (eUpdateType == eOpDel)
    {
        mysqlpp::SQLStream ostr(NULL);
        ostr << "Update tblrecharge set byStatus = 2 Where qwRoleID = ";
        ostr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
        ostr << ";";
        CDBMgr::Instance().DoRechargeModifyQuery(ostr.str(),NULL,[ostr](INT8 byRet, mysqlpp::SimpleResult& res)
                {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << ostr.str() << "result:" << byRet;
                });
    }
}

//接收：替换帐号
bool CCenter2DBCommS::OnRecv_ReplaceUser(
        UINT64 qwUsrID, //帐号ID
        shared_func<SReplaceUserAck>& fnAck //返回回调函数
        )
{
    NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
    /*
       SUserDataPtr pUserData = CUserMgr::GetUserData(qwUsrID);
       if(pUserData == NULL)
       {
       LOG_CRI << "pUserData == NULL";
       return false;
       }*/
    /* pUserData->SetUserState(eUserReplace);*/
    SDBRoleData *pData =  CDBRoleMgr::Instance().GetRoleData(qwUsrID);
    if (pData == NULL)
    {
        LOG_CRI << "SDBRoleData *pData == NULL";
        return false;
    }
    pData->SetUserState(eUserReplace);
    return true;
}

//接收：加载离线玩家数据
bool CCenter2DBCommS::OnRecv_LoadOffLineUserData(
        UINT64 qwUsrID, //账号ID
        shared_func<SLoadOffLineUserDataAck>& fnAck //返回回调函数
        )
{
    CDBRoleMgr::Instance().LoadRoleData(qwUsrID,eLoadOterSvr, 
            [fnAck,this](SDBRoleData* pData, EEnterResult eResult)
            {
            if(eResult != eEnterSucceed)
            fnAck->byRet = 1;
            else
            {
            if(pData != NULL)
            {
            CDBRoleMgr::Instance().GetAllInfo(fnAck->RoleData,*pData);
            if(pData->GetUserState() == eUserNone)
            CDBRoleMgr::Instance().CheckRoleState(pData,false);
            }

            }
            fnAck(true);
            });

    return true;
}

//接收：一行数据更新
void CCenter2DBCommS::OnRecv_RoleDataUpdate(
        UINT64 qwRoleId, //角色Id
        NRoleInfoDefine::EDataType eDataType, //更新数据块
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const std::string& strData //更新数据
        )
{
    CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(qwRoleId,eDataType,eUpdateType,strData);
}

//接收：获取排行榜数据（启动预加载用）
void CCenter2DBCommS::OnRecv_GetRankInfo(
        )
{
    CDBRoleRankMgr::Instance().LoadAllRankData();
}

//接收：排行榜数据更新
void CCenter2DBCommS::OnRecv_RankDataUpdate(
        UINT64 qwInstID, //唯一ID
        NRankProt::ERankType eDataType, //更新数据类型
        NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
        const std::string& strData //更新数据
        )
{
    if (eDataType >= eRTRoleRankBegin && eDataType < eRTRoleRankEnd)
        CDBRoleRankMgr::Instance().RankDataOperate(qwInstID, eDataType, eUpdateType, strData);
}

//接收：获取崇拜信息
void CCenter2DBCommS::OnRecv_GetAdoreInfo(
        )
{
    CDBRoleRankMgr::Instance().LoadAllAdoreData();
}

//接收：崇拜数据更新
void CCenter2DBCommS::OnRecv_AdoreDataUpdate(
        UINT64 qwInstID, //唯一ID
        NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
        const std::string& strData //更新数据
        )
{
    CDBRoleRankMgr::Instance().AdoreDataOperate(qwInstID, eUpdateType, strData);
}

//接收：获取账号ID或主角色名请求
void CCenter2DBCommS::OnRecv_UserIDNameReq(
        NServerCommon::EUserReqType eType, //类型
        UINT64 qwUsrID, //帐号ID
        const std::string& strName, //主角色名称
        UINT64 qwUsrData //用户数据
        )
{
    // TODO: 请求查询好友信息
#if 0
    UINT32 dwSvrID = GetCurSvrID();
    SUsrIDNameInfoPtr pUsrIDNameInfo(new SUsrIDNameInfo(qwUsrID, strName, dwSvrID, eHostCenter, qwUsrData, eType));
    if(pUsrIDNameInfo != NULL)
    {
        CUserMgr::GetUsrIDOrName(pUsrIDNameInfo);
    }
    else
    {
        SUsrIDNameInfo oUsrIDNameInfo(qwUsrID, strName, dwSvrID, eHostCenter, qwUsrData, eType);
        oUsrIDNameInfo.SendUsrIDNameInfo();
    }
#endif
}
/*
//接收：更新过期邮件状态
bool CCenter2DBCommS::OnRecv_UpdateOvertimeMail(
const TVecMailDelData& vecqwMailIds, //更新的 vecqwMailIds,
shared_func<SUpdateOvertimeMailAck>& fnAck //返回回调函数
)
{
mysqlpp::SQLStream sql(NULL);
sql << "update tblrolemail set byInvalid  = 1 where ";
for (size_t i = 0; i < vecqwMailIds.size() - 1; ++i)
sql << "qwMailId = " << vecqwMailIds[i].qwMailId <<" or ";
sql << "qwMailId = " << vecqwMailIds[vecqwMailIds.size() - 1].qwMailId << ";";
CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL, [fnAck,sql,vecqwMailIds](INT8 byRet_, mysqlpp::SimpleResult& res){
LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet_;
if (byRet_ != 0)
{
fnAck->byRet = byRet_;
return fnAck(false);
}
DelMailAttach(vecqwMailIds,false,[fnAck](INT8 byRet){
if(byRet != 0)
{
fnAck->byRet = byRet;
fnAck(false);
}
fnAck(true);
});
});

return true;
}

//接收：删除过期邮件
bool CCenter2DBCommS::OnRecv_RemoveOvertimeMail(
const TVecMailDelData& vecqwMailIds, //更新的qwMailId
shared_func<SRemoveOvertimeMailAck>& fnAck //返回回调函数
)
{
mysqlpp::SQLStream sql(NULL);
sql << "delete from tblrolemail where ";
for (size_t i = 0; i < vecqwMailIds.size() - 1; ++i)
sql << "qwMailId = " << vecqwMailIds[i].qwMailId <<" or ";
sql << "qwMailId = " << vecqwMailIds[vecqwMailIds.size() - 1].qwMailId << ";";
CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL, [this,vecqwMailIds,fnAck,sql](INT8 byRet_, mysqlpp::SimpleResult& res){
LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet_;
if (byRet_ != 0)
{
fnAck->byRet = byRet_;
return fnAck(false);
}
DelMailAttach(vecqwMailIds,false,[fnAck](INT8 byRet){
if(byRet != 0)
{
fnAck->byRet = byRet;
fnAck(false);
}
fnAck(true);
});
});
return true;

}
*/
//接收：获得邮件列表
bool CCenter2DBCommS::OnRecv_GetAllMailList(
        UINT64 qwRoleID, //玩家ID
        UINT32 dwOverTime, //过期时间
        shared_func<SGetAllMailListAck>& fnAck //返回回调函数
        )
{
    mysqlpp::SQLStream sql(NULL);
    sql << "select * from tblrolemail where qwReceiveID = ";
    sql << qwRoleID;
    sql << " and byInvalid = 0 and dwSendTime > ";
    sql << dwOverTime;
    CDBMgr::Instance().DoMailSelectQuery(sql.str(),NULL, [this,fnAck,sql](INT8 byRet, mysqlpp::StoreQueryResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if (byRet != 0)
            return fnAck(false);
            UINT32 dwMailSize =  res.size();
            for (size_t i = 0; i < res.size(); ++i)
            {
            const mysqlpp::Row& row = res[i];

            SMailDetail stDetail;

            stDetail.qwMailID = row["qwMailId"];
            UINT8 byType = row["byMailType"];
            stDetail.eMailType = static_cast<EMailType>(byType);
            stDetail.byGeted = row["byGetted"];
            stDetail.vecMailAttachment.clear();
            UINT8 byState = row["byMailState"];
            stDetail.eMailState = static_cast<EMailState>(byState);
            stDetail.dwSendTime = row["dwSendTime"];
            row["strMailTitle"].to_string(stDetail.strTitle);
            row["strSenderName"].to_string(stDetail.strSendName);
            row["strMailMsg"].to_string(stDetail.strMessage);
            /* TODO:
               const mysqlpp::String& str = row["InfoProp"];
               if (str != mysqlpp::null && !str.empty())
               str.to_string(stDetail.strAttachment);
               */
            if(stDetail.eMailType == EMAILTYPE_SYSTEM && (stDetail.byGeted > 0 && stDetail.byGeted < ATTACH_MAX))
            {
                LoadMailAttach(stDetail.qwMailID,stDetail.byGeted,[dwMailSize,fnAck,stDetail](INT8 byRet,std::shared_ptr<TVecMailAttachment> vecAttachPtr){
                        if(byRet == 0)
                        {
                        SMailDetail stNewDetail(stDetail);
                        if( vecAttachPtr != NULL)
                        {
                        stNewDetail.vecMailAttachment = *vecAttachPtr;
                        }
                        fnAck->vecMails.push_back(stNewDetail);
                        }
                        else
                        {

                        LOG_CRI << "Load Mail Dtetail  False : ID" <<stDetail.qwMailID;
                        fnAck->vecMails.push_back(stDetail); 
                        }
                        if( fnAck->vecMails.size() == dwMailSize)
                        {
                        fnAck(true); 
                        }

                });
            }
            else
            {
                fnAck->vecMails.push_back(stDetail);
                if( fnAck->vecMails.size() == dwMailSize)
                {
                    fnAck(true); 
                }
            }
            }

    });
    return true;
}

//接收：保存邮件
bool CCenter2DBCommS::OnRecv_SaveMail(
        UINT64 qwMailId, //邮件ID
        UINT64 qwReceiveID, //接受者ID
        UINT64 qwSenderID, //发送者ID
        const std::string& strSenderName, //发送者名字
        NMailProt::EMailType eMailType, //邮件类型
        NMailProt::EMailState eMailState, //邮件状态
        UINT32 dwSendTime, //发送时间
        const std::string& strTitle, //标题
        const std::string& strMsg, //邮件内容
        //      const std::string& strAttachment, //附件?
        shared_func<SSaveMailAck>& fnAck //返回回调函数
        )
{

    mysqlpp::SQLStream sql(NULL);
    sql<<"INSERT INTO tblrolemail ";
    sql<<"(qwMailId, byMailType, strMailTitle, strSenderName, byMailState, dwSendTime, qwSenderID, qwReceiveID, strMailMsg";//, InfoProp";
    // sql<<",ProtocolVersion"
    sql<<")";
    sql<<" VALUES("
        <<qwMailId
        <<","<<(mysqlpp::sql_tinyint_unsigned)eMailType
        <<","<<mysqlpp::quote<<(mysqlpp::sql_char)strTitle.c_str()
        <<","<<mysqlpp::quote<<(mysqlpp::sql_char)strSenderName.c_str()
        <<","<<(mysqlpp::sql_tinyint_unsigned)eMailState
        <<","<<dwSendTime
        <<","<<qwSenderID
        <<","<<qwReceiveID
        <<","<<mysqlpp::quote<<(mysqlpp::sql_char)strMsg.c_str()
        <<")";

    string str = sql.str();
    if (eMailType == NMailProt::EMAILTYPE_SYSTEM)
    {
        CDBMgr::Instance().DoMailModifyQuery(str,NULL,
                [fnAck,str](INT8 byRet, mysqlpp::SimpleResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << str << "result:" << byRet;
                if(byRet != 0)
                {
                fnAck->byRet = byRet;
                fnAck(true);
                }
                fnAck(true);
                });
    }
    else
    {
        mysqlpp::SQLStream sqlCount(NULL);
        sqlCount<<"Select count(*) as number from  tblrolemail  where qwReceiveID  = ";
        sqlCount<<qwReceiveID;
        sqlCount<<" and  byMailType = ";
        sqlCount<<NMailProt::EMAILTYPE_NORMAL;
        sqlCount<<" and  byInvalid = 0 ;";
        CDBMgr::Instance().DoMailSelectQuery(sqlCount.str(),NULL, [this,fnAck,sqlCount,str](INT8 byRet, mysqlpp::StoreQueryResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlCount.str() << "result:" << byRet;
                if (byRet != 0 ||res.size() != 1)
                {
                fnAck->byRet = byRet == 0 ? 1: byRet;
                fnAck(true);
                return ;
                }
                const mysqlpp::Row& row = res[0];
                UINT32 dwMailCount = row["number"];
                LOG_INF << "Mail count is" << dwMailCount;
                if( dwMailCount >= SParamConfig::wMailMaxNum)
                {
                fnAck->byRet = 1;
                fnAck(true);
                return ;
                }
                CDBMgr::Instance().DoMailModifyQuery(str,NULL,
                    [fnAck,str](INT8 byRet, mysqlpp::SimpleResult& res) {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << str << "result:" << byRet;
                    if(byRet != 0)
                    {
                    fnAck->byRet = byRet;
                    }
                    fnAck(true);
                    });
        });

    }
    return true;
}

//接收：删除邮件
bool CCenter2DBCommS::OnRecv_DeleteMail(
        UINT64 qwRoleID, //玩家ID
        const TVecMailDelData& vecqwMailIds, //邮件ID列表
        shared_func<SDeleteMailAck>& fnAck //返回回调函数
        )
{
    if(vecqwMailIds.empty())
        return true;
    mysqlpp::SQLStream sql(NULL);
    //sql<<"DELETE FROM tblrolemail WHERE ReceiveID="<<qwRoleID<<" AND ";
    sql << "update tblrolemail set byInvalid = 1 where qwReceiveID="<<qwRoleID<<" and ";
    if(vecqwMailIds.size() == 1)
        sql<<"qwMailId="<<vecqwMailIds[0].qwMailID;
    else
    {
        sql<<"qwMailId in (";
        for(size_t i=0; i<vecqwMailIds.size(); ++i)
        {
            if(i>0)
                sql<<",";
            sql<<vecqwMailIds[i].qwMailID;
        }
        sql<<")";
    }
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL
            , [this,vecqwMailIds,fnAck,sql](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if(byRet != 0)
            {
            fnAck->byRet = byRet;
            return fnAck(false);
            }
            DelMailAttach(vecqwMailIds,false,[fnAck](INT8 byRet){
                if(byRet != 0)
                {
                fnAck->byRet = byRet;
                fnAck(false);
                }
                fnAck(true);
                });
            });
    return true;
}

//接收：保存系统邮件
bool CCenter2DBCommS::OnRecv_SaveSystemMail(
        const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
        const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
        shared_func<SSaveSystemMailAck>& fnAck //返回回调函数
        )
{
    mysqlpp::SQLStream sql(NULL);
    sql<<"INSERT INTO tblrolemail "
        "(qwMailId, byMailType, strMailTitle, strSenderName, byMailState, dwSendTime,byGetted, qwSenderID, qwReceiveID, strMailMsg)"//, InfoProp)"
        " VALUES";
    for (auto v = vecSystemMailTargetInfo.begin(); v != vecSystemMailTargetInfo.end(); ++v)
    {

        sql << "("
            << v->qwMailID
            <<","<<(mysqlpp::sql_tinyint_unsigned)rSystemMailInfo.eMailType
            <<","<<mysqlpp::quote<<(mysqlpp::sql_char)rSystemMailInfo.strTitle.c_str()
            <<","<<mysqlpp::quote<<(mysqlpp::sql_char)rSystemMailInfo.strSender.c_str()
            <<","<<(mysqlpp::sql_tinyint_unsigned)rSystemMailInfo.eMailState
            <<","<<rSystemMailInfo.dwSendTime
            <<","<<(mysqlpp::sql_tinyint_unsigned)rSystemMailInfo.byGet
            <<","<<(mysqlpp::sql_tinyint_unsigned)0
            <<","<<v->qwReceiveID
            <<","<<mysqlpp::quote<<(mysqlpp::sql_char)rSystemMailInfo.strMsg.c_str();
        //TODO:
        // <<","<<mysqlpp::quote<<rSystemMailInfo.strAttachment;

        if (v == vecSystemMailTargetInfo.end() - 1)
        {
            sql << ")";
        }
        else
        {
            sql << "),";
        }
    }

    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL,[this,fnAck,sql,vecSystemMailTargetInfo,rSystemMailInfo](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if(byRet != 0)
            {
            fnAck->byRet = byRet;
            return fnAck(false);
            }
            //附件存储
            SaveMailAttach(vecSystemMailTargetInfo,rSystemMailInfo,[fnAck](INT8 byRet){
                if(byRet != 0)
                {
                fnAck->byRet = byRet;
                fnAck(false);
                }
                fnAck(true);
                });
            });
    return true;
}

//接收：更新邮件状态
bool CCenter2DBCommS::OnRecv_UpdateMailStatus(
        UINT64 qwMailId, //邮件ID
        NMailProt::EMailState eMailState,
        shared_func<SUpdateMailStatusAck>& fnAck
        )
{
    mysqlpp::SQLStream sql(NULL);
    sql << "update tblrolemail set byMailState = ";
    sql << (mysqlpp::sql_tinyint_unsigned)eMailState;
    sql << " where qwMailId = ";
    sql << qwMailId;
    sql <<";";
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL,[fnAck,sql](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if(byRet != 0)
            {
            fnAck->byRet = byRet;
            return fnAck(false);
            }
            return fnAck(true);
            });
    return true;

}

bool CCenter2DBCommS::OnRecv_GetUserIDFromName(
        const std::string& strName, //主角色名称
        shared_func<SGetUserIDFromNameAck>& fnAck //返回回调函数
        ) 
{
    fnAck->qwUsrID = RoleNameManager::Instance().GetPlayerIdByName(strName);
    return true;   
}

//接收：查看玩家私聊信息
bool CCenter2DBCommS::OnRecv_GetWhisperInfo(
        UINT64 qwRoleID, //玩家的ID
        shared_func<SGetWhisperInfoAck>& fnAck //返回回调函数
        )
{
    mysqlpp::SQLStream sql(NULL);
    sql << "SELECT ft.wFighterID, ft.byLevel, p.strName, p.eSex, p.strSign, p.wMood FROM tblrolefighter as ft, tblroledata as p  WHERE ft.qwRoleID = " << qwRoleID << " AND ft.qwRoleID = p.qwRoleID AND wFighterID < 20;";

    CDBMgr::Instance().DoSelectQuery(sql.str(), NULL, [qwRoleID, fnAck] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            if(0 == byRet && 1 == dataRes.size())
            {
            const mysqlpp::Row& rRow = dataRes[0];

            fnAck->whisperInfo.qwUserID = qwRoleID;
            UINT8 bySex;
            GET_UTINYINT(eSex, bySex);
            fnAck->whisperInfo.eSex = static_cast<NProtoCommon::ESexType>(bySex);
            GET_USMALLINT(wFighterID, fnAck->whisperInfo.wFighterID);
            GET_UTINYINT(byLevel, fnAck->whisperInfo.byLevel);
            GET_USMALLINT(wMood, fnAck->whisperInfo.wMood);
            GET_STRING_CHAR(strSign, fnAck->whisperInfo.strSign);
            GET_STRING_CHAR(strName, fnAck->whisperInfo.strName);
            fnAck->whisperInfo.byQuality = 1; 
            fnAck(true);
            return;
            }
            else
            {
            fnAck(true);
            return;
            }
    });

    return true;
}

void  CCenter2DBCommS::SaveMailAttach(const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
        const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
        function<void(INT8)> funReSult)
{
    const TVecMailAttachment& vecMailAttach = rSystemMailInfo.vecMailAttachment;
    if( vecSystemMailTargetInfo.empty() || vecMailAttach.empty())
    {
        funReSult(0);
        return ;
    }

    size_t szTotal = vecMailAttach.size();
    QueryRecordPtr TotalPtr(new QueryRecord());
    TotalPtr->dwTotal = szTotal;
    for (size_t i = 0 ; i != szTotal ; i++)
    {
        SMailBaseAttachmentPtr itemPtr = vecMailAttach[i];
        switch (itemPtr->GetClassType())
        {
            case eType_SItemAttachment:
                {

                    SItemAttachmentPtr pAttach = dynamic_pointer_cast<SItemAttachment>(itemPtr);
                    if( pAttach == NULL)
                    {
                        TotalPtr->AddAndCheck(0,funReSult);
                        break;
                    }
                    TVecMailItemInfo &rvecItemInfo = pAttach->vecItemInfo;
                    if(rvecItemInfo.empty())
                    {
                        TotalPtr->AddAndCheck(0,funReSult); 
                        break;
                    }
                    QueryRecordPtr SubPtr(new QueryRecord());
                    SubPtr->dwTotal = vecSystemMailTargetInfo.size();
                    for(auto iter = vecSystemMailTargetInfo.begin();iter != vecSystemMailTargetInfo.end();iter++)
                    {
                        const SSystemMailTargetInfo &rTarget = *(iter);

                        SaveSingleMailAttach(rTarget.qwMailID,rvecItemInfo,[funReSult,SubPtr,TotalPtr](INT8 byRet){
                                if(SubPtr->AddAndCheck(byRet,NULL))
                                {
                                TotalPtr->AddAndCheck(SubPtr->byStatus,funReSult);

                                }
                                });

                    }


                }
                break;
            case eType_SItemBaseCT:
                {
                    SItemBaseCTPtr pAttach = dynamic_pointer_cast<SItemBaseCT>(itemPtr);
                    if( pAttach == NULL)
                    {
                        TotalPtr->AddAndCheck(0,funReSult);
                        break;
                    }
                    NItemProt::TVecItem &rvecItemInfo = pAttach->vecItems;
                    if(rvecItemInfo.empty())
                    {
                        TotalPtr->AddAndCheck(0,funReSult); 
                        break;
                    }
                    //把一个实例发给多个人,不允许
                    if(vecSystemMailTargetInfo.size() > 1)
                    {
                        LOG_CRI <<"INSTANCE TO More PERSONS!!!!";
                        TotalPtr->AddAndCheck(0,funReSult); 
                        break;
                    }
                    const SSystemMailTargetInfo &rTarget = vecSystemMailTargetInfo[0];
                    SaveSingleMailInstance(rTarget.qwMailID,rvecItemInfo,[funReSult,TotalPtr](INT8 byRet){
                            TotalPtr->AddAndCheck(byRet,funReSult);
                            });

                }
                break;
            default:
                TotalPtr->AddAndCheck(0,funReSult); 
                break;

        }
    }
}

void  CCenter2DBCommS::LoadMailAttach(UINT64 qwMailID,UINT8 byGet,function<void(INT8,std::shared_ptr<TVecMailAttachment> vecAttachPtr)> funReSult)
{
    if( byGet == 0 || byGet == ATTACH_MAX)
    {
        TVecMailAttachment attach;
        funReSult(0,NULL);
        return ;
    }
    std::shared_ptr<TVecMailAttachment> PtrVecAttach(new TVecMailAttachment());
    QueryRecordPtr pRecord(new QueryRecord());
    pRecord->dwTotal = 2;
    if((byGet & (1 << ATTACH_ITEM)) > 0)  
    {
        LoadSingleMailAttach(qwMailID,[pRecord,PtrVecAttach,funReSult](INT8 byRet,TVecMailItemInfo rVecItem)
                {
                if(!rVecItem.empty())
                {
                SItemAttachmentPtr ptrItem(new SItemAttachment());
                ptrItem->vecItemInfo = rVecItem;
                PtrVecAttach->push_back(ptrItem);
                }
                if(pRecord->AddAndCheck(byRet,NULL))
                {
                funReSult(pRecord->byStatus,PtrVecAttach); 
                }
                });


    }
    else
    {
        if(pRecord->AddAndCheck(0,NULL))
        {
            funReSult(pRecord->byStatus,PtrVecAttach); 
        }


    }

    if((byGet & (1 << ATTACH_INSTANCE)) > 0)  
    {
        LoadSingleMailInstance(qwMailID,[pRecord,PtrVecAttach,funReSult](INT8 byRet,NItemProt::TVecItem rVecInstance)
                {
                if (!rVecInstance.empty())
                {
                SItemBaseCTPtr  ptrItem(new SItemBaseCT());
                ptrItem->vecItems = rVecInstance;
                PtrVecAttach->push_back(ptrItem);
                } 
                if(pRecord->AddAndCheck(byRet,NULL))
                {
                funReSult(pRecord->byStatus,PtrVecAttach); 
                }
                });


    }
    else
    {
        if(pRecord->AddAndCheck(0,NULL))
        {
            funReSult(pRecord->byStatus,PtrVecAttach); 
        }


    }
}

void  CCenter2DBCommS::DelMailAttach(const TVecMailDelData& vecqwMailDatas,bool bIsDraw,function<void(INT8)> funReSult)
{
    QueryRecordPtr pRecord(new QueryRecord());
    pRecord->dwTotal = vecqwMailDatas.size();
    for (auto iter = vecqwMailDatas.begin();iter != vecqwMailDatas.end();++iter)
    {
        const MailDelData &rDelData = *iter;
        if( rDelData.byGet == 0 || rDelData.byGet ==ATTACH_MAX)
        {
            pRecord->AddAndCheck(0,funReSult);
            continue;
        }
        QueryRecordPtr pSubRecord(new QueryRecord());
        pSubRecord->dwTotal = 2;
        UINT64 qwMailId = rDelData.qwMailID;
        LOG_INF << "DelMail Item :" <<"rDelData.byGet IS" <<(int)rDelData.byGet;  
        //模板数据
        if((rDelData.byGet & (1 << ATTACH_ITEM)) > 0)
        {
            DelSingleMailAttach(qwMailId ,bIsDraw,[funReSult,pRecord,pSubRecord](INT8 byRet)
                    {
                    if(pSubRecord->AddAndCheck(byRet,NULL))
                    {
                    pRecord->AddAndCheck(pSubRecord->byStatus,funReSult);
                    }
                    });
        }
        else
        {
            if(pSubRecord->AddAndCheck(0,NULL))
            {
                pRecord->AddAndCheck(pSubRecord->byStatus,funReSult);
            }

        }
        //实例数据
        if((rDelData.byGet &  (1<<ATTACH_INSTANCE)) > 0)
        {
            DelSingleMailInstance(qwMailId ,bIsDraw,[funReSult,pRecord,pSubRecord](INT8 byRet)
                    {
                    if(pSubRecord->AddAndCheck(byRet,NULL))
                    {
                    pRecord->AddAndCheck(pSubRecord->byStatus,funReSult);
                    }
                    });
        }
        else
        {   if(pSubRecord->AddAndCheck(0,NULL))
            {
                pRecord->AddAndCheck(pSubRecord->byStatus,funReSult);
            }

        }

    }
}


void CCenter2DBCommS::SaveSingleMailAttach(UINT64 qwMailId,TVecMailItemInfo &rvecItemInfo, function<void(INT8)> funReSult)
{
    if(rvecItemInfo.empty())
    {
        funReSult(0);
        return ;
    }
    mysqlpp::SQLStream sql(NULL);
    sql <<"insert into tblrolemailattachtype(qwMailId,wItemID,eItemQuelity,wCount,eBindType,byExpired,dwExpireTime,qwOPID) VALUES";
    for (size_t it = 0 ; it < rvecItemInfo.size();it++)
    { 
        SMailItemInfo& rItem = rvecItemInfo[it];
        if(it != 0 )
        {
            sql <<",";
        }
        sql << "(";
        sql <<(mysqlpp::sql_bigint_unsigned)qwMailId;
        sql << ",";
        sql <<(mysqlpp::sql_smallint_unsigned)rItem.wItemID;               
        sql <<",";
        sql <<(mysqlpp::sql_tinyint_unsigned)rItem.eItemQuelity;
        sql <<",";
        sql <<(mysqlpp::sql_int_unsigned)rItem.wCount;
        sql <<",";
        sql <<(mysqlpp::sql_tinyint_unsigned)rItem.eBindType;
        sql <<",";
        sql <<(mysqlpp::sql_tinyint_unsigned)rItem.byExpired;
        sql <<",";
        sql <<(mysqlpp::sql_int_unsigned)rItem.dwExpireTime;
        sql <<",";
        sql <<(mysqlpp::sql_bigint_unsigned)rItem.qwOPID;
        sql <<")";
    }
    sql <<";";
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL,
            [funReSult,sql](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            funReSult(byRet);
            });

}

void CCenter2DBCommS::SaveSingleMailInstance(UINT64 qwMailId,NItemProt::TVecItem& rVectorItem,function<void(INT8)> funReSult) 
{
    if(rVectorItem.empty())
    {
        funReSult(0);
        return ;
    }
    QueryRecordPtr ptrTotal(new QueryRecord());
    ptrTotal->dwTotal = rVectorItem.size();
    for(auto iter = rVectorItem.begin();iter != rVectorItem.end();iter++)
    {
        QueryRecordPtr ptrSub(new QueryRecord());
        ptrSub->dwTotal = 2;
        SItemPtr pItemPtr = *(iter);
        CDBRoleItemTable ItemTable(qwMailId);
        ItemTable.InitDataByBase(pItemPtr->sItemInfo);
        string Itemsql;
        ItemTable.GetInsertSqlStr(Itemsql);
        CDBMgr::Instance().DoMailModifyQuery(Itemsql,NULL
                , [funReSult,Itemsql,ptrSub,ptrTotal](INT8 byRet, mysqlpp::SimpleResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Itemsql << "result:" << byRet;
                if(ptrSub->AddAndCheck(byRet,NULL))
                {
                ptrTotal->AddAndCheck(ptrSub->byStatus,funReSult);
                }
                });
        if(pItemPtr->GetClassType() == eType_SCitta)
        {
            SCittaPtr pCitta = NULL;
            pCitta = dynamic_pointer_cast<SCitta>(pItemPtr);
            if( pCitta == NULL)
            {
                if(ptrSub->AddAndCheck(0,NULL))
                {
                    ptrTotal->AddAndCheck(ptrSub->byStatus,funReSult);
                }
                return;
            }

            DBRoleCittaTable CittaTable;
            pCitta->qwOwnerID = qwMailId;
            CittaTable.InitDataByCitta(pCitta);
            string Cittasql;
            CittaTable.GetInsertSqlStr(Cittasql);
            CDBMgr::Instance().DoMailModifyQuery(Cittasql,NULL
                    , [funReSult,Cittasql,ptrSub,ptrTotal](INT8 byRet, mysqlpp::SimpleResult& res) {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Cittasql << "result:" << byRet;
                    if(ptrSub->AddAndCheck(byRet,NULL))
                    {
                    ptrTotal->AddAndCheck(ptrSub->byStatus,funReSult);
                    }
                    });



        }
        else if(pItemPtr->GetClassType() ==  eType_SFashion)
        {
            SFashionPtr pFashion = NULL;
            pFashion = dynamic_pointer_cast<SFashion>(pItemPtr);
            if( pFashion == NULL)
            {
                if(ptrSub->AddAndCheck(0,NULL))
                {
                    ptrTotal->AddAndCheck(ptrSub->byStatus,funReSult);
                }
                return;
            }

            CDBRoleFashionTable FashionTable(qwMailId);
            FashionTable.InitDataByFashion(pFashion);
            string Fashionsql;
            FashionTable.GetInsertSqlStr(Fashionsql);
            CDBMgr::Instance().DoMailModifyQuery(Fashionsql,NULL
                    , [funReSult,Fashionsql,ptrSub,ptrTotal](INT8 byRet, mysqlpp::SimpleResult& res) {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Fashionsql << "result:" << byRet;
                    if(ptrSub->AddAndCheck(byRet,NULL))
                    {
                    ptrTotal->AddAndCheck(ptrSub->byStatus,funReSult);
                    }
                    });

        }
        else
        {
            ptrTotal->AddAndCheck(0,funReSult);

        }

    }
}

void CCenter2DBCommS::LoadSingleMailAttach(UINT64 qwMailId,function<void(INT8,TVecMailItemInfo)> funReSult)
{
    mysqlpp::SQLStream sql(NULL);
    sql <<"select * from tblrolemailattachtype where qwMailId = ";
    sql <<(mysqlpp::sql_bigint_unsigned)qwMailId;
    sql <<";";
    CDBMgr::Instance().DoMailSelectQuery(sql.str(),NULL, [this,funReSult,sql](INT8 byRet, mysqlpp::StoreQueryResult& DataRes) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            TVecMailItemInfo vecAttach;
            if (byRet != 0)
            {
            funReSult(byRet,vecAttach);
            return ;
            }
            UINT32 ncount = DataRes.size(); 
            for (UINT32 i = 0 ; i <  ncount;i++)
            {
            mysqlpp::Row& rRow = DataRes[i];
            SMailItemInfo stItem;
            GET_USMALLINT(wItemID,stItem.wItemID);
            UINT8 byQuelity;
            GET_UTINYINT(eItemQuelity,byQuelity);
            stItem.eItemQuelity = static_cast<NItemProt::EItemQuality>(byQuelity);
            GET_INT(wCount,stItem.wCount);
            UINT8 byBind;
            GET_UTINYINT(eBindType,byBind);
            stItem.eBindType = static_cast<NItemProt::EBindType>(byBind);
            GET_UTINYINT(byExpired,stItem.byExpired);
            GET_UINT(dwExpireTime,stItem.dwExpireTime);
            GET_UBIGINT(qwOPID,stItem.qwOPID);
            vecAttach.push_back(stItem);

            }
    funReSult(byRet,vecAttach);   
    });

}

void CCenter2DBCommS::LoadSingleMailInstance(UINT64 qwMailId,function<void(INT8,NItemProt::TVecItem)> funReSult)
{   
    std::shared_ptr<RoleDataInfo> tempRolePtr(new RoleDataInfo());
    tempRolePtr->qwRoleId = qwMailId;
    std::shared_ptr<CDBRoleItemTableManager> tempItemPtr(new CDBRoleItemTableManager(qwMailId,0));
    std::shared_ptr<DBRoleCittaTableManager> tempCittaPtr(new DBRoleCittaTableManager(qwMailId,0));
    std::shared_ptr<CDBRoleFashionTableManager> tempFashionPtr(new  CDBRoleFashionTableManager(qwMailId,0));

    tempItemPtr->QueryDataByRoleId(qwMailId,
            [tempRolePtr,tempItemPtr,tempCittaPtr,tempFashionPtr,funReSult] (INT8 byRet,UINT32 dwCount)
            {
            if(byRet != 0)
            {
            NItemProt::TVecItem vecItem;
            funReSult(byRet,vecItem);
            return ;
            }
            tempItemPtr->GetALLInfo(*tempRolePtr);
            QueryRecordPtr ptrRecord(new QueryRecord());
            ptrRecord->dwTotal = 2;
            tempCittaPtr->QueryDataByRoleId(tempRolePtr->qwRoleId,
                [tempRolePtr,tempCittaPtr,funReSult,ptrRecord](INT8 byRet,UINT32 dwCount)
                {
                if(byRet == 0)
                {
                tempCittaPtr->GetALLInfo(*tempRolePtr);
                }
                if(ptrRecord->AddAndCheck(byRet,NULL))
                {
                funReSult(byRet,tempRolePtr->vecRoleItemInfo);
                }
                });

            tempFashionPtr->QueryDataByRoleId(tempRolePtr->qwRoleId,
                    [tempRolePtr,tempFashionPtr,funReSult,ptrRecord](INT8 byRet,UINT32 dwCount)
                    {
                    if(byRet == 0)
                    {
                    tempFashionPtr->GetALLInfo(*tempRolePtr);
                    }
                    if(ptrRecord->AddAndCheck(byRet,NULL))
                    {
                    funReSult(byRet,tempRolePtr->vecRoleItemInfo);
                    }
                    });
            });  
}

void CCenter2DBCommS::DelSingleMailAttach(UINT64 qwMailId,bool bIsDraw,function<void(INT8)> funReSult)
{
    mysqlpp::SQLStream sql(NULL);
    sql <<"delete from tblrolemailattachtype where qwMailId =";
    sql << qwMailId;
    sql << ";" ;
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL
            , [funReSult,sql](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            funReSult(byRet);
            });

}
void CCenter2DBCommS::DelSingleMailInstance(UINT64 qwMailId,bool bIsDraw,function<void(INT8)> funReSult)
{
    mysqlpp::SQLStream sql(NULL);
    sql <<"delete from  tblroleitemdata  where qwRoleID =";
    sql << qwMailId;
    sql << ";";
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL
            , [funReSult,sql,qwMailId](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if ( byRet != 0 )
            {
            funReSult(byRet);
            return;
            }
            QueryRecordPtr ptrRecord(new QueryRecord());
            ptrRecord->dwTotal = 2;
            //citta
            {
            mysqlpp::SQLStream Subsql(NULL);  
            Subsql <<"delete from  tblrolecittadata  where qwRoleID =";   
            Subsql << qwMailId;
            Subsql << ";";
            CDBMgr::Instance().DoMailModifyQuery(Subsql.str(),NULL
                , [funReSult,Subsql,qwMailId,ptrRecord](INT8 byRet, mysqlpp::SimpleResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Subsql.str() << "result:" << byRet;
                ptrRecord->AddAndCheck(byRet,funReSult);
                });
            }
            //fashion
            {
                mysqlpp::SQLStream Subsql(NULL);  
                Subsql <<"delete from  tblrolefashion  where qwRoleID =";   
                Subsql << qwMailId;
                Subsql << ";";
                CDBMgr::Instance().DoMailModifyQuery(Subsql.str(),NULL
                        , [funReSult,Subsql,qwMailId,ptrRecord](INT8 byRet, mysqlpp::SimpleResult& res) {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Subsql.str() << "result:" << byRet;
                        ptrRecord->AddAndCheck(byRet,funReSult);
                        });
            }

            });
}
//接收：删除邮件附件
bool CCenter2DBCommS::OnRecv_DelMailAttach(
        const MailDelData& stDelData, //删除提示
        shared_func<SDelMailAttachAck>& fnAck //返回回调函数
        ) 
{
    mysqlpp::SQLStream sql(NULL);
    sql << "update tblrolemail set byGetted = 255";
    sql << " where qwMailId = ";
    sql << stDelData.qwMailID;
    sql << ";";
    CDBMgr::Instance().DoMailModifyQuery(sql.str(),NULL,[fnAck,sql,stDelData,this](INT8 byRet, mysqlpp::SimpleResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if(byRet != 0)
            {
            fnAck->byRet = byRet;
            return fnAck(false);
            }
            TVecMailDelData vecData;
            vecData.push_back(stDelData);
            DelMailAttach(vecData,true,[fnAck](INT8 byRet){
                fnAck->byRet = byRet;
                fnAck(byRet == 0);
                });
            });
    return true;

}

//接收：请求所有玩家
void CCenter2DBCommS::OnRecv_GetAllUserIDAndName(
        )
{
    RoleNameManager::Instance().GetAllUserIDAndName();
}

//接收：请求所有玩家
void CCenter2DBCommS::OnRecv_GetAllNotice(
        )
{
    g_CDBNoticeTable.LoadNotice();
}

//接收：增加公告
void CCenter2DBCommS::OnRecv_AddNotice(
        const NPHPProt::SNotice& sNotice //公告内容
        )
{
    g_CDBNoticeTable.AddNotice(sNotice);
}

//接收：删除公告
void CCenter2DBCommS::OnRecv_DelNotice(
        UINT32 dwNoticeID //公告ID
        )
{
    g_CDBNoticeTable.DelNotice(dwNoticeID);
}

//接收：请求斗剑信息
void CCenter2DBCommS::OnRecv_GetAllArena(
        UINT32 dwPageSize //发送条数
        ) 
{
    g_CDBTotalArenaManager.GetAllArena(dwPageSize);
    g_CDBTotalLadderRobotManager.GetAllLadderRobot();
}

//接收：更新斗剑数据
void CCenter2DBCommS::OnRecv_UpdateAllArena(
        const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
        ) 
{
    for(auto iter=vecUpdate.begin();iter != vecUpdate.end();iter++)
    {
        const SArenaPlayerBaseDataUpdate& rData = *(iter);
        g_CDBTotalArenaManager.UpdateData(rData.qwRoleID,rData.stBaseData);
    }
}

//接收：删除玩家斗剑数据
void CCenter2DBCommS::OnRecv_DelPlayerArena(
        const TVecUINT64& vecDel //删除玩家斗剑信息
        )
{
    for(auto iter = vecDel.begin();iter != vecDel.end();iter++)
    {
        g_CDBTotalArenaManager.DelData(*iter);
    }

}

//接收：请求系统Var数据
bool CCenter2DBCommS::OnRecv_GetGameVar(
        shared_func<SGetGameVarAck>& fnAck //返回回调函数
        ) 
{
    g_CDBTotalGameVarsManager.LoadData([fnAck,this](vecSGameVarsDBInfoPtr pVec
                ){
            for(auto iter = pVec->begin();iter != pVec->end();++iter)
            {
            if((*iter).byServerType == (mysqlpp::sql_tinyint_unsigned)eHostCenter)
            {
            fnAck->vecVar.push_back(*iter);
            }

            }
            fnAck(true);

            });
    return true;

}

//接收：更新系统Var数据
void CCenter2DBCommS::OnRecv_UpdateGameVar(
        const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
        )
{
    g_CDBTotalGameVarsManager.UpdateData(Var);
}

//接收：删除Var数据
void CCenter2DBCommS::OnRecv_DelGameVar(
        UINT16 wVarID //删除的VarID
        )
{
    g_CDBTotalGameVarsManager.DelData(wVarID);
}

//接收：增加系统Var数据
void CCenter2DBCommS::OnRecv_AddGameVar(
        const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
        ) 
{ 

    g_CDBTotalGameVarsManager.UpdateData(Var);
}

bool CCenter2DBCommS::OnRecv_GetArenaFighterByID(
        UINT64 qwRoleID, //玩家的ID
        shared_func<SGetArenaFighterByIDAck>& fnAck //返回回调函数
        )
{
    g_CDBTotalArenaManager.QueryFighterData(qwRoleID,[fnAck](INT8 byRet,SArenaFighterPtr pFigther)
            {
            if(NULL != pFigther)
            {
            fnAck->stFighter = *pFigther;
            }
            fnAck(byRet==0);
            }
            );
    return true;
};

//接收：获取镇妖塔信息（启动预加载调用）
bool CCenter2DBCommS::OnRecv_GetDemonTowerInfo(
        shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
        )
{
    CDBDemonTowerPlayerManager::Instance().GetALLInfo(fnAck->vecDemonTowerPlayer);
    return true;
}

//接收：更新镇妖塔玩家信息
void CCenter2DBCommS::OnRecv_UpateDemonTowerInfo(
        NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
        const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
        )
{
    if(eDbType == eDemonTowerDB_Delete)
    {
        CDBDemonTowerPlayerManager::Instance().DelData(oDemonTowerPlayer);
    }
    else
    {
        CDBDemonTowerPlayerManager::Instance().Update(oDemonTowerPlayer);
    }

}
void CCenter2DBCommS::GetBattleReportFun(UINT64 qwRoleID, //玩家的ID
        NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
        NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
        function<void(INT8 byRet,NRoleInfoDefine::TVecBattleRePort vecReport)> fnAck)
{
    mysqlpp::SQLStream sql(NULL);
    sql << "select * from tblBattleReport where qwRoleID = ";
    sql << qwRoleID;
    sql << " and eType = ";
    sql << eBattleType;
    if(eAction == NRoleInfoDefine::eTypeALL)
    {
        sql << " and (eActionType = ";
        sql << NRoleInfoDefine::eTypeAttack ;
        sql <<" or eActionType = ";
        sql << NRoleInfoDefine::eTypeDefense;
        sql <<" ) order by dwIndex;";
    }
    else
    {
        sql << " and eActionType = ";
        sql << eAction;
        sql <<" order by dwIndex;";
    }
    CDBMgr::Instance().DoMailSelectQuery(sql.str(),NULL, [this,fnAck,sql](INT8 byRet, mysqlpp::StoreQueryResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            NRoleInfoDefine::TVecBattleRePort vecReport;
            if (byRet != 0)
            {
            fnAck(byRet,vecReport);
            return ;
            }
            for( size_t it = 0; it != res.size();it++)
            {
            const mysqlpp::Row& rRow = res[it];
            SBattleRePort sReport;
            GET_UBIGINT(qwRoleID,sReport.qwRoleID);
            GET_UBIGINT(qwBattleID,sReport.qwBattleID);
            GET_UBIGINT(qwAttackID,sReport.qwAttackID);
            GET_STRING_CHAR(strAttackID, sReport.strAttackID);
            UINT8 eActionType;
            GET_UTINYINT_SAME(eActionType);
            sReport.eActionType = static_cast<NRoleInfoDefine::EBattleActionType>(eActionType);
            UINT8 eType;
            GET_UTINYINT_SAME(eType);
            sReport.eType = static_cast<NRoleInfoDefine::EBattleReportType>(eType);
            UINT8 eSuc;
            GET_UTINYINT_SAME(eSuc);
            sReport.eSuc = static_cast<NRoleInfoDefine::EBattleActionType>(eSuc);
            GET_UINT(dwTime,sReport.dwTime);
            GET_UINT(dwParam1,sReport.dwParam1);
            GET_UINT(dwParam2,sReport.dwParam2);
            GET_UINT(dwParam3,sReport.dwParam3);
            vecReport.push_back(sReport);
            }
    fnAck(0,vecReport);
    });

}

//接收：获得玩家战报信息
bool CCenter2DBCommS::OnRecv_GetBattleReport(
        UINT64 qwRoleID, //玩家的ID
        NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
        NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
        shared_func<SGetBattleReportAck>& fnAck //返回回调函数
        ) 
{
    GetBattleReportFun(qwRoleID,eBattleType,eAction,[fnAck](INT8 byRet,NRoleInfoDefine::TVecBattleRePort vecReport){
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
}
void CCenter2DBCommS::AddBattleReportFun(UINT64 qwRoleID,const NRoleInfoDefine::SBattleRePort& sReport,UINT8 byNum,function<void (INT8 byRet,TVecUINT64 vecBattleID)> fnAck)
{
    TVecUINT64 vecBattleID;
    if(byNum ==0)
    {
        AddBattleReport(qwRoleID,sReport, vecBattleID,fnAck);
    }
    else
    {
        mysqlpp::SQLStream sql(NULL);
        sql << "select qwBattleID  from tblBattleReport  where qwRoleID = ";
        sql << qwRoleID;
        sql << " and eType = ";
        sql << sReport.eType; 
        sql << " order by dwIndex";
        sql <<" ;";
        CDBMgr::Instance().DoMailSelectQuery(sql.str(),NULL, [qwRoleID,this,fnAck,sql,sReport,byNum](INT8 byRet, mysqlpp::StoreQueryResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
                TVecUINT64 vecBattleID;
                if(byRet  != 0 )
                {
                fnAck(byRet,vecBattleID);
                return ;
                }
                UINT32 dwDelCount = 0;
                if(res.size() >= byNum)
                {
                dwDelCount = res.size()- byNum + 1;
                }
                if(dwDelCount > 0)
                {
                mysqlpp::SQLStream delsql(NULL);
                delsql << "delete from tblBattleReport where  qwRoleID = ";
                delsql << qwRoleID;
                delsql << " and qwBattleID in (";   
                for(UINT32 it = 0; it != dwDelCount;it++)
                {
                    UINT64 qwBattleID;
                    const mysqlpp::Row& rRow = res[it];
                    GET_BIGINT_SAME(qwBattleID);
                    delsql << (mysqlpp::sql_bigint_unsigned)qwBattleID;
                    vecBattleID.push_back(qwBattleID);
                    if(it != dwDelCount-1)
                    {
                        delsql << ",";
                    }
                    else
                    {
                        delsql <<");";
                    }
                }
        CDBMgr::Instance().DoMailModifyQuery(delsql.str(),NULL,
                [delsql,fnAck,qwRoleID,sReport,this,vecBattleID](INT8 byRet, mysqlpp::SimpleResult& res) {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << delsql.str() << "result:" << byRet;
                if(byRet == 0)
                {
                AddBattleReport(qwRoleID,sReport,vecBattleID,fnAck);
                }
                else
                {
                fnAck(byRet,vecBattleID);
                return ;
                }
                });

                }
                else
                {
                    AddBattleReport(qwRoleID,sReport,vecBattleID,fnAck);
                }

        });
    }


}

//接收：增加玩家战报信息
bool CCenter2DBCommS::OnRecv_AddBattleReport(
        UINT64 qwRoleID, //玩家的ID
        const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
        UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
        shared_func<SAddBattleReportAck>& fnAck //返回回调函数
        ) 
{
    AddBattleReportFun(qwRoleID,sReport,byNum,[fnAck](INT8 byRet,TVecUINT64 vecBattleID)
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

void CCenter2DBCommS::AddBattleReport(UINT64 qwRoleID, const NRoleInfoDefine::SBattleRePort& sReport,const TVecUINT64& vecBattleID,function<void (INT8 byRet,TVecUINT64 vecBattleID)> fnAck)
{
    mysqlpp::SQLStream sql(NULL);
    //找出最大序号
    sql << "select  max(dwIndex) as MaxIndex,count(dwIndex) as Count  from tblBattleReport where qwRoleID = ";
    sql << qwRoleID;
    sql << " and eType = ";
    sql << sReport.eType;
    sql <<" ;";
    CDBMgr::Instance().DoMailSelectQuery(sql.str(),NULL, [qwRoleID,this,fnAck,sql,sReport,vecBattleID](INT8 byRet, mysqlpp::StoreQueryResult& res) {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sql.str() << "result:" << byRet;
            if(byRet  != 0 || res.size() > 1)
            {
            fnAck(byRet,vecBattleID);
            return;
            }
            UINT32 dwMaxIndex = 0;
            if(res.size() == 1)
            {
            const mysqlpp::Row& rRow = res[0]; 
            UINT32 dwCount = 0;
            GET_UINT(Count,dwCount);
            if(dwCount > 1)
            {
            GET_UINT(MaxIndex,dwMaxIndex);
            }
            }
            dwMaxIndex++;
            mysqlpp::SQLStream Insertsql(NULL);
            Insertsql << " insert into tblBattleReport  (qwRoleID,  qwBattleID,     qwAttackID,     strAttackID,    eActionType,    eType,  eSuc,   dwTime,     dwParam1,   dwParam2,   dwParam3,   dwIndex) values(";
            Insertsql << (mysqlpp::sql_bigint_unsigned) sReport.qwRoleID;
            Insertsql << "," <<(mysqlpp::sql_bigint_unsigned) sReport.qwBattleID;
            Insertsql << "," <<(mysqlpp::sql_bigint_unsigned) sReport.qwAttackID;
            Insertsql << "," << mysqlpp::quote << (mysqlpp::sql_char)sReport.strAttackID;
            Insertsql << "," <<(mysqlpp::sql_tinyint_unsigned) sReport.eActionType;
            Insertsql << "," <<(mysqlpp::sql_tinyint_unsigned) sReport.eType;
            Insertsql << "," <<(mysqlpp::sql_tinyint_unsigned) sReport.eSuc;
            Insertsql << "," <<(mysqlpp::sql_int_unsigned) sReport.dwTime;
            Insertsql << "," <<(mysqlpp::sql_int_unsigned) sReport.dwParam1;
            Insertsql << "," <<(mysqlpp::sql_int_unsigned) sReport.dwParam2;
            Insertsql << "," <<(mysqlpp::sql_int_unsigned) sReport.dwParam3;
            Insertsql <<","<<(mysqlpp::sql_int_unsigned)dwMaxIndex;
            Insertsql << ");";
            CDBMgr::Instance().DoMailModifyQuery(Insertsql.str(),NULL,
                    [Insertsql,fnAck,vecBattleID](INT8 byRet, mysqlpp::SimpleResult& res) {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << Insertsql.str() << "result:" << byRet;
                    fnAck(0,vecBattleID);
                    });
    });

}
//接收：重新加载表格
void CCenter2DBCommS::OnRecv_ReloadTable(
        const TVecString& vecTableName //表格名字
        ) 
{
    for(auto it=vecTableName.begin() ; it!=vecTableName.end() ; ++it)
    {
        bool bUpdate = true;
        if("Parameter.xml" == *it)
        {
            bUpdate =  CParamMgr::Init(); 
        }
        else 
        {
            bUpdate = false;
        }
        if(bUpdate)
        {
            LOG_CRI << "Reload table " <<*it<<" Suc";
        }
    }
}

//接收：请求所有九疑鼎信息
void CCenter2DBCommS::OnRecv_GetAllTripod(
        UINT32 dwPageSize //发送条数
        )
{
    g_CDBTripodTableManager.GetAllTripod(dwPageSize);
}

//接收：请求所有九疑鼎的协助信息
void CCenter2DBCommS::OnRecv_GetAllTripodHelper(
        UINT32 dwPageSize //发送条数
        )
{
    g_CDBTripodHelpTableManager.GetAllTripodHelper(dwPageSize);
}

//接收：请求所有九疑鼎的动态信息
void CCenter2DBCommS::OnRecv_GetAllTripodLog(
        UINT32 dwPageSize //发送条数
        )
{
    // TODO: 
    g_CDBTripodLogTableManager.GetAllTripodLog(dwPageSize);
}

//接收：新玩家九疑鼎信息
void CCenter2DBCommS::OnRecv_UpdateTripod(
        UINT64 qwRoleID, //玩家的ID
        const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
        )
{
    if (!qwRoleID)
        return;
    g_CDBTripodTableManager.UpdateData(qwRoleID, oTripodInfo, true);
}

//接收：更新玩家九疑鼎协助信息
void CCenter2DBCommS::OnRecv_UpateTripodHelp(
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
        )
{
    if (eUpdateType == eOpUpdate || eUpdateType == eOpAdd)
        g_CDBTripodHelpTableManager.Update(oTripodHelp);
    else if (eUpdateType == eOpDel)
        g_CDBTripodHelpTableManager.DelData(oTripodHelp);
}

//接收：更新玩家九疑鼎动态信息
void CCenter2DBCommS::OnRecv_UpdateTripodLog(
        UINT64 qwRoleID, //玩家的ID
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
        )
{
    // TODO: 
    g_CDBTripodLogTableManager.Update(oTripodLog);
}

//接收：增加离线事件
void CCenter2DBCommS::OnRecv_AddOffLineEvent(
        const TVecUINT64& vecRoleID, //玩家的ID
        const NRoleInfoDefine::SEventOffLine& sEventData 
        )
{
    //TODO:
    g_CDBOffLineEventManager.AddOffLineEvent(eHostCenter,vecRoleID, sEventData);
}
//接收：对玩家封号
void CCenter2DBCommS::OnRecv_FreezePlayer(
        UINT64 qwUserID, //玩家的ID
        UINT32 dwFreezeTimer //封号
        ) 
{
    CDBRoleMgr::Instance().LoadRoleData(qwUserID,eLoadUpdate, [this,dwFreezeTimer](SDBRoleData* pRoleData, EEnterResult eResult){
            if(!pRoleData || eResult != eEnterSucceed)
            return ;
            TableManagerBaseForRole* pBaseMgr = pRoleData->GetDataManagerByType(eTypeRoleBaseInfo);
            if(pBaseMgr)
            {
            DBRoleBaseTableManager* pMgr = static_cast<DBRoleBaseTableManager*>(pBaseMgr);
            if(pMgr)
            {
            pMgr->Freeze(dwFreezeTimer);
            CDBRoleMgr::Instance().CheckRoleState(pRoleData,true);
            }
            }
            });
}
//接收：对玩家禁言
void CCenter2DBCommS::OnRecv_ForbitChat(
        UINT64 qwUserID, //玩家的ID
        UINT32 dwForbitTimer //禁言时间
        ) 
{
    CDBRoleMgr::Instance().LoadRoleData(qwUserID,eLoadUpdate, [dwForbitTimer,this](SDBRoleData* pRoleData, EEnterResult eResult){
            if(!pRoleData || eResult != eEnterSucceed)
            return ;
            TableManagerBaseForRole* pBaseMgr = pRoleData->GetDataManagerByType(eTypeRoleBaseInfo);
            if(pBaseMgr)
            {
            DBRoleBaseTableManager* pMgr = static_cast<DBRoleBaseTableManager*>(pBaseMgr);
            if(pMgr)
            {
            pMgr->ForbitChat(dwForbitTimer);
            CDBRoleMgr::Instance().CheckRoleState(pRoleData,true);
            }
            }
            });

}

//接收：将玩家登录时IP写入数据库
void CCenter2DBCommS::OnRecv_UpdateLoginIP(
        UINT64 qwUserID, //玩家的ID
        const std::string& strLoginIP //登录时IP
        )
{
    CDBRoleMgr::Instance().LoadRoleData(qwUserID,eLoadUpdate, [this,strLoginIP](SDBRoleData* pRoleData, EEnterResult eResult){
            if(!pRoleData || eResult != eEnterSucceed)
            return ;
            TableManagerBaseForRole* pBaseMgr = pRoleData->GetDataManagerByType(eTypeRoleBaseInfo);
            if(pBaseMgr)
            {
            DBRoleBaseTableManager* pMgr = static_cast<DBRoleBaseTableManager*>(pBaseMgr);
            if(pMgr)
            {
            pMgr->UpdateLoginIP(strLoginIP);
            CDBRoleMgr::Instance().CheckRoleState(pRoleData,true);
            }
            }
            });
}

//接收：请求拉取进入参数
void CCenter2DBCommS::OnRecv_GetPlatformParam(
        )
{
    CDBRoleMgr::Instance().GetAllPlatformParam(20);
}

//接收：数据库查询
void CCenter2DBCommS::OnRecv_GetResult2DB(
        const SBaseCond& sBaseCond //查询条件
        )
{
#if 0
    std::map<UINT64,UINT8> _mapID2Level;
    CDBWonderPrizeTableManager::Instance().GetALLInfo(_mapID2Level);
    UINT8 byLevel = sBaseCond.byLevel;
    TVecUINT64 vecPlayerID;
    UINT32 dwResult = 0;
    for(auto &it : _mapID2Level)
    {
        if(it.second == byLevel)
        {
            dwResult ++;
            vecPlayerID.push_back(it.first);
        }
    }
    SBaseResult sResult; //查询结果
    sResult.dwResult = dwResult;
    sResult.vecPlayerID.assign(vecPlayerID.begin(),vecPlayerID.end());
    Send_SendResult2Cent(sBaseCond,sResult);
#endif
}

//接收：查询玩家奖励状态
bool CCenter2DBCommS::OnRecv_GetPrizeStatus(
        shared_func<SGetPrizeStatusAck>& fnAck //返回回调函数
        )
{
    CDBWonderPrizeTableManager::Instance().GetALLInfo(fnAck->vecRet);
    return true;
}

//接收：更新玩家奖励状态
void CCenter2DBCommS::OnRecv_UpdatePrizeStatus(
        const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
        NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
        )
{
    switch(eUpdateType)
    {
        case eOpDel:
            {
                CDBWonderPrizeTableManager::Instance().DelData(sPrize2DB);
            }
            break;
        case eOpAdd:
            {
                CDBWonderPrizeTableManager::Instance().Update(sPrize2DB, true);
            }
            break;
        case eOpUpdate:
            {
                CDBWonderPrizeTableManager::Instance().Update(sPrize2DB, false);
            }
            break;
        default:
            break;
    }

}

//接收：删除玩家数据
void CCenter2DBCommS::OnRecv_DelActPrizeData(
        UINT16 wActID //活动ID
        ) 
{
    CDBWonderPrizeTableManager::Instance().DelData(wActID);
}
//接收：删除玩家保留数据
void CCenter2DBCommS::OnRecv_DelActRetainData(
        UINT16 wActID //活动ID
        )
{
    CDBWonderRetainTableManager::Instance().DelData(wActID);
}

//接收：查询所有玩家等级
bool CCenter2DBCommS::OnRecv_GetAllRoleLevel(
        UINT8 byType, //类型
        shared_func<SGetAllRoleLevelAck>& fnAck //返回回调函数
        )
{
    fnAck->byTypeRet = byType;
    switch(byType)
    {
        case NGame2CenterComm::eActLevel:
            {
                GetRoleLevels(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActTrump:
            {
                GetRoleTrumps(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActFighter:
            {
                GetRoleFighters(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActDungon:
            {
                GetRoleDungons(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActFormation:
            {
                GetRolePets(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActBeauty:
            {
                GetRoleBeautys(fnAck->vecRoleLevel);
            }
            break;
        case NGame2CenterComm::eActHorse:
            {
                GetRoleHorses(fnAck->vecRoleLevel);
            }
            break;
    }
    return true;
}

//接收：查询玩家保留信息
bool CCenter2DBCommS::OnRecv_GetRetain(
        shared_func<SGetRetainAck>& fnAck //返回回调函数
        )
{
    CDBWonderRetainTableManager::Instance().GetALLInfo(fnAck->vecRet);
    return true;
}

//接收：更新玩家保留信息
void CCenter2DBCommS::OnRecv_UpdateRetain(
        const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
        NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
        ) 
{
    switch(eUpdateType)
    {
        case eOpDel:
            {
                CDBWonderRetainTableManager::Instance().DelData(sRetain);
            }
            break;
        case eOpAdd:
            {
                CDBWonderRetainTableManager::Instance().Update(sRetain, true);
            }
            break;
        case eOpUpdate:
            {
                CDBWonderRetainTableManager::Instance().Update(sRetain, false);
            }
            break;
        default:
            break;
    }
}

void  CCenter2DBCommS::GetRoleLevels(TVecRoleLevel& vecRet)
{
    std::map<UINT64,UINT8> _mapID2Level;
    CDBWonderPrizeTableManager::Instance().GetALLInfo(_mapID2Level);
    UINT8 byMaxLevel = 0;
    UINT8 byMinLevel = 1;
    for(auto &it : _mapID2Level)
    {
        if(byMaxLevel < it.second)
            byMaxLevel = it.second;  
        if(byMinLevel > it.second)
            byMinLevel = it.second; 
    }

    for(UINT8 i=byMinLevel; i<=byMaxLevel; ++i)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(i);
        for(auto &oIt : _mapID2Level)
        {
            if(i == oIt.second)
            {
                oLevel.vecRole.push_back(oIt.first);
            }
        }
        vecRet.push_back(oLevel);
    }

}
void  CCenter2DBCommS::GetRoleTrumps(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT16> _mapID2Trump;
    CDBWonderPrizeTableManager::Instance().GetInfoForTrump(_mapID2Trump);
    TSetUINT16 setTrumpIDs;
    for(auto &it : _mapID2Trump)
    {
        if(!setTrumpIDs.count(it.second))
        {
            setTrumpIDs.insert(it.second);

        }
    }

    for(auto &oIt : setTrumpIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(oIt);
        for(auto &It : _mapID2Trump)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }

}
void  CCenter2DBCommS::GetRolePets(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT16> _mapID2Formation;
    CDBWonderPrizeTableManager::Instance().GetInfoForFormation(_mapID2Formation);
    TSetUINT16 setFormationIDs;
    for(auto &it : _mapID2Formation)
    {
        if(!setFormationIDs.count(it.second))
        {
            setFormationIDs.insert(it.second);
        }
    }

    for(auto &oIt : setFormationIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(oIt);
        for(auto &It : _mapID2Formation)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }
}
void  CCenter2DBCommS::GetRoleFighters(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT16> _mapID2Fighter;
    CDBWonderPrizeTableManager::Instance().GetInfoForFighter(_mapID2Fighter);
    TSetUINT16 setFighterIDs;
    for(auto &it : _mapID2Fighter)
    {
        if(!setFighterIDs.count(it.second))
        {
            setFighterIDs.insert(it.second);
        }
    }

    for(auto &oIt : setFighterIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(oIt);
        for(auto &It : _mapID2Fighter)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }
}

void  CCenter2DBCommS::GetRoleBeautys(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT16> _mapID2Beauty;
    CDBWonderPrizeTableManager::Instance().GetInfoForBeauty(_mapID2Beauty);
    TSetUINT16 setBeautyIDs;
    for(auto &it : _mapID2Beauty)
    {
        if(!setBeautyIDs.count(it.second))
        {
            setBeautyIDs.insert(it.second);
        }
    }

    for(auto &oIt : setBeautyIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(oIt);
        for(auto &It : _mapID2Beauty)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }
}

void  CCenter2DBCommS::GetRoleHorses(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT32> _mapID2Horse;
    CDBWonderPrizeTableManager::Instance().GetInfoForHorse(_mapID2Horse);
    TSetUINT32 setHorseIDs;
    for(auto &it : _mapID2Horse)
    {
        if(!setHorseIDs.count(it.second))
        {
            setHorseIDs.insert(it.second);
        }
    }

    for(auto &oIt : setHorseIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = static_cast<UINT32>(oIt);
        for(auto &It : _mapID2Horse)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }
}
void  CCenter2DBCommS::GetRoleDungons(TVecRoleLevel& vecRet)
{
    std::multimap<UINT64,UINT32> _mapID2Dungon;
    CDBWonderPrizeTableManager::Instance().GetInfoForDungon(_mapID2Dungon);
    TSetUINT32 setDungonIDs;
    for(auto &it : _mapID2Dungon)
    {
        if(!setDungonIDs.count(it.second))
        {
            setDungonIDs.insert(it.second);
        }
    }

    for(auto &oIt : setDungonIDs)
    {
        SRoleLevel oLevel;
        oLevel.dwID = oIt;
        for(auto &It : _mapID2Dungon)
        {
            if(oIt == It.second)
            {
                oLevel.vecRole.push_back(It.first);
            }
        }
        vecRet.push_back(oLevel);
    }
}

//接收：请求金船信息
void  CCenter2DBCommS::OnRecv_GetAllShip(
        UINT32 dwPageSize //发送条数
        ) 
{
    g_CDBTotalShipManager.GetAllShip(dwPageSize);  
}

//接收：更新金船数据
void  CCenter2DBCommS::OnRecv_UpdateShip(
        const NShipProt::PlayerShip& UpdateInfo //更新信息
        ) 

{

    g_CDBTotalShipManager.UpdateData(UpdateInfo);
}

//接收：删除金船数据
void  CCenter2DBCommS::OnRecv_DelShip(
        UINT64 qwInsID //删除金船信息
        ) 
{
    g_CDBTotalShipManager.DelData(qwInsID);
}

//接收：增加金船报告
void  CCenter2DBCommS::OnRecv_AddShipReport(
        UINT64 qwRoleID, //报告拥有者
        const NShipProt::ShipReport& sReport //报告内容
        ) 
{

    g_CDBShipReportManager.AddShipReport(qwRoleID,sReport);
}

//接收：删除金船报告
void  CCenter2DBCommS::OnRecv_DelShipReport(
        UINT64 qwRoleID, //报告拥有者
        UINT64 qwInsID //金船唯一ID
        ) 
{
    g_CDBShipReportManager.DelShipReport(qwRoleID,qwInsID);
}

//接收：获取中心服数据
bool CCenter2DBCommS::OnRecv_GetCenterData(
        shared_func<SGetCenterDataAck>& fnAck //返回回调函数
        )
{
    CDBCenterDataDBTableManager::Instance().GetALLInfo(fnAck->vecCenterData);
    return true;
}

//接收：更新中心服数据
void CCenter2DBCommS::OnRecv_UpateCenterData(
        const SCenterData& oCenterData, //中心服数据
        bool bDelete //删除/更新
        )
{
    if(bDelete)
    {
        CDBCenterDataDBTableManager::Instance().DelData(oCenterData);
    }
    else
    {
        CDBCenterDataDBTableManager::Instance().Update(oCenterData);
    }
}

//接收：天元神兽同步玩家信息
void CCenter2DBCommS::OnRecv_SyncMonsterUserInfo(
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const NGodMonsterProt::SGuildUser2DB& sUser //数据
        )
{
    switch(eUpdateType)
    {
        case eOpDel:
            {
                CDBRoleGodMonsterTableManager::Instance().DelData(sUser);
            }
            break;
        case eOpAdd:
            {
                CDBRoleGodMonsterTableManager::Instance().Update(sUser, true);
            }
            break;
        case eOpUpdate:
            {
                CDBRoleGodMonsterTableManager::Instance().Update(sUser, false);
            }
            break;
        default:
            break;
    }
}

//接收：获取天元神兽信息（启动预加载调用）
bool CCenter2DBCommS::OnRecv_GetGodMonsterInfo(
        shared_func<SGetGodMonsterInfoAck>& fnAck //返回回调函数
        )
{
    CDBRoleGodMonsterTableManager::Instance().GetALLInfo(fnAck->vecUser);
    return true;
}

//接收：天元神兽同步玩家限购礼包信息
void CCenter2DBCommS::OnRecv_SyncLimitPrizeInfo(
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
        ) 
{
    switch(eUpdateType)
    {
        case eOpAdd:
            {
                CDBRoleLimitPrizeTableManager::Instance().Update(oLimitPrize);
            }
            break;
        default:
            break;
    }
}

//接收：获取天元神兽玩家限购礼包信息（启动预加载调用）
bool CCenter2DBCommS::OnRecv_GetLimitPrizeInfo(
        shared_func<SGetLimitPrizeInfoAck>& fnAck //返回回调函数
        )
{
    CDBRoleLimitPrizeTableManager::Instance().GetALLInfo(fnAck->vecLimitPrize);
    return true;
}
//接收：运营活动中心同步信息
void CCenter2DBCommS::OnRecv_SyncActivityCenterInfo(
        NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
        const NProtoCommon::SActivityOpt& oActOpt //数据
        )
{
    switch(eUpdateType)
    {
        case eOpDel:
            {
                CDBActivityCenterTableManager::Instance().DelData(oActOpt);
            }
            break;
        case eOpAdd:
            {
                CDBActivityCenterTableManager::Instance().Update(oActOpt, true);
            }
            break;
        case eOpUpdate:
            {
                CDBActivityCenterTableManager::Instance().Update(oActOpt, false);
            }
            break;
        default:
            break;
    }
}

//接收：运营活动中心操作（启动预加载调用）
bool CCenter2DBCommS::OnRecv_GetActivityCenterInfo(
        shared_func<SGetActivityCenterInfoAck>& fnAck //返回回调函数
        )
{
    CDBActivityCenterTableManager::Instance().GetALLInfo(fnAck->vecActOpt);
    return true;
}
//接收：增加机器人新信息
void  CCenter2DBCommS::OnRecv_AddLadderRobot(
        const NArenaGS::TVecLadderRobot& vecData //数据
        )
{
    for(auto iter = vecData.begin();iter != vecData.end();iter++)
    {
        g_CDBTotalLadderRobotManager.UpdateData(*iter);
    }
}

//接收：增加机器人新信息
void  CCenter2DBCommS::OnRecv_UpdateLadderRobot(
        const NArenaGS::SLadderRobot& SData //数据
        )
{
    g_CDBTotalLadderRobotManager.UpdateData(SData);
}

