#pragma once
#include "Center2DBCommSvr.h"
#include "DBGameVarsMananger.h"
using namespace NMailProt;
using namespace NCenter2DBComm;
struct QueryRecord
{
    UINT32 dwTotal;
    UINT32 dwCurrent;
    INT8  byStatus;
    QueryRecord()
    {
        dwTotal =0;
        dwCurrent =0;
        byStatus = 0;
    }
    bool AddAndCheck(INT8 set_byStatus,function<void(INT8)> funReSult)
    {
        dwCurrent++;
        if(byStatus == 0 && set_byStatus != 0)
        {
            byStatus = set_byStatus;
        }
        if(dwCurrent == dwTotal)
        { 
            if(funReSult != NULL)
            {
                funReSult(byStatus);
            }
            return true;
        }
        else if(dwCurrent > dwTotal)
        {
            LOG_CRI <<"LOGIC ERR";
        }
        return false;
    }
};
typedef std::shared_ptr<QueryRecord> QueryRecordPtr;

class CCenter2DBCommS : public CCenter2DBCommSvr
{
    public:
        //接收：心跳
        virtual void OnRecv_KeepAlive(
                );

        //接收：DBServer状态请求
        virtual bool OnRecv_GetStatus(
                shared_func<SGetStatusAck>& fnAck //返回回调函数
                );

        //接收：插入玩家充值仙石信息(未创角预先充值)
        virtual void OnRecv_InsertRecharge(
                const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
                );

        //接收：更新玩家未创角预先充值信息
        virtual void OnRecv_UpdatePrepaid(
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                UINT64 qwRoleID, //玩家ID
                UINT32 dwGold //仙石数量
                );

        //接收：加载玩家未创角预先充值的仙石信息
        virtual bool OnRecv_LoadPrepaid(
                shared_func<SLoadPrepaidAck>& fnAck //返回回调函数
                );

        //接收：替换帐号
        virtual bool OnRecv_ReplaceUser(
                UINT64 qwUsrID, //帐号ID
                shared_func<SReplaceUserAck>& fnAck //返回回调函数
                );

        //接收：加载离线玩家数据
        virtual bool OnRecv_LoadOffLineUserData(
                UINT64 qwUsrID, //账号ID
                shared_func<SLoadOffLineUserDataAck>& fnAck //返回回调函数
                );

        //接收：一行数据更新
        virtual void OnRecv_RoleDataUpdate(
                UINT64 qwRoleId, //角色Id
                NRoleInfoDefine::EDataType eDataType, //更新数据块
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const std::string& strData //更新数据
                );

        //接收：获取排行榜数据（启动预加载用）
        virtual void OnRecv_GetRankInfo(
                );

        //接收：排行榜数据更新
        virtual void OnRecv_RankDataUpdate(
                UINT64 qwInstID, //唯一ID
                NRankProt::ERankType eDataType, //更新数据类型
                NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
                const std::string& strData //更新数据
                );

        //接收：获取崇拜信息
        virtual void OnRecv_GetAdoreInfo(
                );


        //接收：崇拜数据更新
        virtual void OnRecv_AdoreDataUpdate(
                UINT64 qwInstID, //唯一ID
                NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
                const std::string& strData //更新数据
                );

        //接收：根据名字获取ID请求
        virtual bool OnRecv_GetUserIDFromName(
                const std::string& strName, //主角色名称
                shared_func<SGetUserIDFromNameAck>& fnAck //返回回调函数
                ) ;
        //接收：获取账号ID或主角色名请求
        virtual void OnRecv_UserIDNameReq(
                NServerCommon::EUserReqType eType, //类型
                UINT64 qwUsrID, //帐号ID
                const std::string& strName, //主角色名称
                UINT64 qwUsrData //用户数据
                );
        /*
        //接收：更新过期邮件状态
        virtual bool OnRecv_UpdateOvertimeMail(
        const TVecMailDelData& vecMailIDs, //更新的MailID
        shared_func<SUpdateOvertimeMailAck>& fnAck //返回回调函数
        );
        //接收：删除过期邮件
        virtual bool OnRecv_RemoveOvertimeMail(
        const TVecMailDelData& vecqwMailDatas, //更新的MailID
        shared_func<SRemoveOvertimeMailAck>& fnAck //返回回调函数
        );
        */
        //接收：获得邮件列表
        virtual bool OnRecv_GetAllMailList(
                UINT64 qwRoleID, //玩家ID
                UINT32 dwOverTime, //过期时间
                shared_func<SGetAllMailListAck>& fnAck //返回回调函数
                );
        //接收：保存邮件
        virtual bool OnRecv_SaveMail(
                UINT64 qwMailID, //邮件ID
                UINT64 qwReceiveID, //接受者ID
                UINT64 qwSenderID, //发送者ID
                const std::string& strSenderName, //发送者名字
                NMailProt::EMailType eMailType, //邮件类型
                NMailProt::EMailState eMailState, //邮件状态
                UINT32 dwSendTime, //发送时间
                const std::string& strTitle, //标题
                const std::string& strMsg, //邮件内容
                //		const std::string& strAttachment, //附件?
                shared_func<SSaveMailAck>& fnAck //返回回调函数
                );
        //接收：删除邮件
        virtual bool OnRecv_DeleteMail(
                UINT64 qwRoleID, //玩家ID
                const TVecMailDelData& vecqwMailIds, //邮件ID列表
                shared_func<SDeleteMailAck>& fnAck //返回回调函数
                );

        //接收：保存系统邮件
        virtual bool OnRecv_SaveSystemMail(
                const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
                const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
                shared_func<SSaveSystemMailAck>& fnAck //返回回调函数

                );
        /*
        //接收：更新邮件信息
        virtual bool OnRecv_UpdateMailInfo(
        UINT64 qwMailID, //邮件ID
        const std::string& strMailAttachment ,//邮件附件
        shared_func<SUpdateMailInfoAck>& fnAck
        );
        */
        //接收：更新邮件状态
        virtual bool  OnRecv_UpdateMailStatus(
                UINT64 qwMailID, //邮件ID
                NMailProt::EMailState eMailState, //邮件状态
                shared_func<SUpdateMailStatusAck>& fnAck
                );
        //接收：删除邮件附件
        virtual bool OnRecv_DelMailAttach(
                const MailDelData& stDelData, //删除提示
                shared_func<SDelMailAttachAck>& fnAck //返回回调函数
                ) ;

        //接收：请求所有玩家
        virtual void OnRecv_GetAllUserIDAndName(
                );

        //接收：请求所有玩家
        virtual void OnRecv_GetAllNotice(
                );

        //接收：增加公告
        virtual void OnRecv_AddNotice(
                const NPHPProt::SNotice& sNotice //公告内容
                );

        //接收：删除公告
        virtual void OnRecv_DelNotice(
                UINT32 dwNoticeID //公告ID
                );

        //接收：请求斗剑信息
        virtual void OnRecv_GetAllArena(
                UINT32 dwPageSize //发送条数
                );

        //接收：更新斗剑数据
        virtual void OnRecv_UpdateAllArena(
                const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
                );

        //接收：删除玩家斗剑数据
        virtual void OnRecv_DelPlayerArena(
                const TVecUINT64& vecDel //删除玩家斗剑信息
                );

        //接收：请求系统Var数据
        virtual bool OnRecv_GetGameVar(
                shared_func<SGetGameVarAck>& fnAck //返回回调函数
                );
        //接收：更新系统Var数据
        virtual void OnRecv_UpdateGameVar(
                const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
                );

        //接收：删除Var数据
        virtual void OnRecv_DelGameVar(
                UINT16 wVarID //删除的VarID
                );
        //接收：增加系统Var数据
        virtual void OnRecv_AddGameVar(
                const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
                ) ;
        //接受：根据玩家ID获得竞技场数据 
        virtual bool OnRecv_GetArenaFighterByID(
                UINT64 qwRoleID, //玩家的ID
                shared_func<SGetArenaFighterByIDAck>& fnAck //返回回调函数
                );

        //接收：获取镇妖塔信息（启动预加载调用）
        virtual bool OnRecv_GetDemonTowerInfo(
                shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
                );

        //接收：更新镇妖塔玩家信息
        virtual void OnRecv_UpateDemonTowerInfo(
                NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
                const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
                );

        //接收：查看玩家私聊信息
        virtual bool OnRecv_GetWhisperInfo(
                UINT64 qwRoleID, //玩家的ID
                shared_func<SGetWhisperInfoAck>& fnAck //返回回调函数
                );
        //接收：获得玩家战报信息
        virtual bool OnRecv_GetBattleReport(
                UINT64 qwRoleID, //玩家的ID
                NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
                NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
                shared_func<SGetBattleReportAck>& fnAck //返回回调函数
                );

        //接收：增加玩家战报信息
        virtual bool OnRecv_AddBattleReport(
                UINT64 qwRoleID, //玩家的ID
                const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
                UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
                shared_func<SAddBattleReportAck>& fnAck //返回回调函数
                );
        //接收：重新加载表格
        virtual void OnRecv_ReloadTable(
                const TVecString& vecTableName //表格名字
                );

        //接收：请求所有九疑鼎信息
        virtual void OnRecv_GetAllTripod(
                UINT32 dwPageSize //发送条数
                );
        //接收：请求所有九疑鼎的协助信息
        virtual void OnRecv_GetAllTripodHelper(
                UINT32 dwPageSize //发送条数
                );
        //接收：请求所有九疑鼎的动态信息
        virtual void OnRecv_GetAllTripodLog(
                UINT32 dwPageSize //发送条数
                );
        //接收：新玩家九疑鼎信息
        virtual void OnRecv_UpdateTripod(
                UINT64 qwRoleID, //玩家的ID
                const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
                );
        //接收：更新玩家九疑鼎协助信息
        virtual void OnRecv_UpateTripodHelp(
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
                );
        //接收：更新玩家九疑鼎动态信息
        virtual void OnRecv_UpdateTripodLog(
                UINT64 qwRoleID, //玩家的ID
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
                );

        //接收：增加离线事件
        virtual void OnRecv_AddOffLineEvent(
                const TVecUINT64& vecRoleID, //玩家的ID
                const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
                );
        //接收：对玩家封号
        virtual    void OnRecv_FreezePlayer(
                UINT64 qwRoleID, //玩家的ID
                UINT32 dwFreezeTimer //封号
                ) ;
        //接收：对玩家禁言
        virtual void OnRecv_ForbitChat(
                UINT64 qwRoleID, //玩家的ID
                UINT32 dwForbitTimer //禁言时间
                ) ;

        //接收：将玩家登录时IP写入数据库
        virtual void OnRecv_UpdateLoginIP(
                UINT64 qwUserID, //玩家的ID
                const std::string& strLoginIP //登录时IP
                );

        //接收：请求拉取进入参数
        virtual void OnRecv_GetPlatformParam(
                );
        //接收：数据库查询
        virtual void OnRecv_GetResult2DB(
                const SBaseCond& sBaseCond //查询条件
                );
        //接收：查询玩家奖励状态
        virtual bool OnRecv_GetPrizeStatus(
                shared_func<SGetPrizeStatusAck>& fnAck //返回回调函数
                );

        //接收：更新玩家奖励状态
        virtual void OnRecv_UpdatePrizeStatus(
                const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
                NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
                );
        //接收：删除玩家数据
        virtual void OnRecv_DelActPrizeData(
                UINT16 wActID //活动ID
                );
        //接收：查询所有玩家等级
        virtual bool OnRecv_GetAllRoleLevel(
                UINT8 byType, //类型
                shared_func<SGetAllRoleLevelAck>& fnAck //返回回调函数
                );
        //接收：查询玩家保留信息
        virtual bool OnRecv_GetRetain(
                shared_func<SGetRetainAck>& fnAck //返回回调函数
                );
        //接收：更新玩家保留信息
        virtual void OnRecv_UpdateRetain(
                const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
                NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
                );
        //接收：删除玩家保留数据
        virtual void OnRecv_DelActRetainData(
                UINT16 wActID //活动ID
                );
        //接收：请求金船信息
        virtual void OnRecv_GetAllShip(
                UINT32 dwPageSize //发送条数
                ) ;

        //接收：更新金船数据
        virtual void OnRecv_UpdateShip(
                const NShipProt::PlayerShip& UpdateInfo //更新信息
                ) ;

        //接收：删除金船数据
        virtual void OnRecv_DelShip(
                UINT64 qwInsID //删除金船信息
                ) ;

        //接收：增加金船报告
        virtual void OnRecv_AddShipReport(
                UINT64 qwRoleID, //报告拥有者
                const NShipProt::ShipReport& sReport //报告内容
                ) ;

        //接收：删除金船报告
        virtual void OnRecv_DelShipReport(
                UINT64 qwRoleID, //报告拥有者
                UINT64 qwInsID //金船唯一ID
                ) ;

        //接收：天元神兽同步玩家信息
        virtual void OnRecv_SyncMonsterUserInfo(
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const NGodMonsterProt::SGuildUser2DB& sUser //数据
                );

        //接收：获取天元神兽信息（启动预加载调用）
        virtual bool OnRecv_GetGodMonsterInfo(
                shared_func<SGetGodMonsterInfoAck>& fnAck //返回回调函数
                );

        //接收：天元神兽同步玩家限购礼包信息
        virtual void OnRecv_SyncLimitPrizeInfo(
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
                );

        //接收：获取天元神兽玩家限购礼包信息（启动预加载调用）
        virtual bool OnRecv_GetLimitPrizeInfo(
                shared_func<SGetLimitPrizeInfoAck>& fnAck //返回回调函数
                );

        virtual void OnRecv_SyncActivityCenterInfo(
                NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
                const NProtoCommon::SActivityOpt& oActOpt //数据
                );

        //接收：运营活动中心操作（启动预加载调用）
        virtual bool OnRecv_GetActivityCenterInfo(
                shared_func<SGetActivityCenterInfoAck>& fnAck //返回回调函数
                );
        //接收：获取中心服数据
        virtual bool OnRecv_GetCenterData(
                shared_func<SGetCenterDataAck>& fnAck //返回回调函数
                );

        //接收：更新中心服数据
        virtual void OnRecv_UpateCenterData(
                const SCenterData& oCenterData, //中心服数据
                bool bDelete //删除/更新
                );
        //接收：增加机器人新信息
        virtual void  OnRecv_AddLadderRobot(
                const NArenaGS::TVecLadderRobot& vecData //数据
                );

        //接收：增加机器人新信息
        virtual void  OnRecv_UpdateLadderRobot(
                const NArenaGS::SLadderRobot& SData //数据
                );	

    private:
        void SaveMailAttach(const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
                const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
                function<void(INT8)> funReSult);
        void LoadMailAttach(UINT64 qwMailID,UINT8 byGet,function<void(INT8,std::shared_ptr<TVecMailAttachment> vecAttachPtr)> funReSult);
        void DelMailAttach(const TVecMailDelData& vecqwMailDatas,bool bIsDraw,function<void(INT8)> funReSult);
        //存储附件
        void SaveSingleMailAttach(UINT64 qwMailId,TVecMailItemInfo &rvecItemInfo , function<void(INT8)> funReSult);
        void SaveSingleMailInstance(UINT64 qwMailId,NItemProt::TVecItem& rVectorItem,function<void(INT8)> funReSult); 
        //加载附件
        void LoadSingleMailAttach(UINT64 qwMailId,function<void(INT8,TVecMailItemInfo)> funReSult);
        void LoadSingleMailInstance(UINT64 qwMailId,function<void(INT8,NItemProt::TVecItem)> funReSult);
        //删除附件
        void DelSingleMailAttach(UINT64 qwMailId,bool bIsDraw,function<void(INT8)> funReSult);
        void DelSingleMailInstance(UINT64 qwMailId,bool bIsDraw,function<void(INT8)> funReSult);
        void AddBattleReport(UINT64 qwRoleID, const NRoleInfoDefine::SBattleRePort& sReport,const TVecUINT64& vecBattleID,function<void (INT8 byRet,TVecUINT64 vecBattleID)> funAck);
    public:
        void GetBattleReportFun(UINT64 qwRoleID, //玩家的ID
                NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
                NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
                function<void(INT8 byRet,NRoleInfoDefine::TVecBattleRePort vecReport)> fnAck);
        void AddBattleReportFun(UINT64 qwRoleID,const NRoleInfoDefine::SBattleRePort& sReport,UINT8 byNum,function<void (INT8 byRet,TVecUINT64 vecBattleID)> funAck);

        bool  GetLevelInfo(UINT8 &byLevel,TVecUINT64& vecPlayerID,UINT32& dwResult);
        void  GetRoleLevels(TVecRoleLevel& vecInfo);
        void  GetRoleTrumps(TVecRoleLevel& vecInfo);
        void  GetRolePets(TVecRoleLevel& vecInfo);
        void  GetRoleFighters(TVecRoleLevel& vecInfo);
        void  GetRoleDungons(TVecRoleLevel& vecInfo);
        void  GetRoleBeautys(TVecRoleLevel& vecInfo);
        void  GetRoleHorses(TVecRoleLevel& vecInfo);

};
