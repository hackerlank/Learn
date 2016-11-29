#pragma once
#include "Game2DBCommSvr.h"

using namespace NGame2DBComm;
using namespace NRoleInfoDefine;
struct SRoleData;

class CGame2DBCommS : public CGame2DBCommSvr
{
    public:
        //接收：心跳
        virtual void OnRecv_KeepAlive(
                );

        //接收：DBServer状态请求
        virtual bool OnRecv_GetStatus(
                shared_func<SGetStatusAck>& fnAck //返回回调函数
                );
        virtual void OnRecv_RoleDataUpdate(UINT64 qwRoleId, NRoleInfoDefine::EDataType eDataType, NProtoCommon::EDataChange eChangeType, const string& strUpdate);

        //接收：更新玩家充值仙石信息
        virtual void OnRecv_UpdateRecharge(
            const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
        );

        //接收：请求保存账号数据
        virtual bool OnRecv_SaveUserDataReq(
                UINT64 qwUsrID, //账号ID
                ESaveType eSaveType, //保存类型
                const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
                shared_func<SSaveUserDataReqAck>& fnAck //返回回调函数
                );
        virtual bool OnRecv_SaveOffLineDgnInfo(
                UINT64 qwUsrID, //账号ID
                UINT32 dwDgnType, //副本类型
                UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
                shared_func<SSaveOffLineDgnInfoAck>& fnAck //返回回调函数
                );
        virtual  bool OnRecv_LoadOffLineUserData(
                UINT64 qwUsrID, //账号ID
                shared_func<SLoadOffLineUserDataAck>& fnAck //返回回调函数
                );
        //接收：加载世界BOSS信息
        virtual bool OnRecv_LoadWorldBossInfo(
                shared_func<SLoadWorldBossInfoAck>& fnAck //返回回调函数
                );

        //接收：存储世界BOSS信息
        virtual void OnRecv_SaveWorldBossInfo(
                const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
                );

        //接收：根据名字获取ID请求
        virtual bool OnRecv_GetUserIDFromName(
                const std::string& strName, //主角色名称
                shared_func<SGetUserIDFromNameAck>& fnAck //返回回调函数
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
                UINT64 qwRoleID, //
                const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
                UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
                shared_func<SAddBattleReportAck>& fnAck //返回回调函数
                );
        //接收：增加离线事件
        virtual void OnRecv_AddOffLineEvent(
                const TVecUINT64& vecRoleID, //
                const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
                );

        //接收：删除离线事件
        virtual void OnRecv_DelOffLineEvent(
                UINT64 qwRoleID, //
                const NRoleInfoDefine::TVecEventOffLine& vecEventType 
                );

        //接收：加载商城限购信息
        virtual bool OnRecv_LoadMallDiscount(
            shared_func<SLoadMallDiscountAck>& fnAck //返回回调函数
        );

        //接收：更新商城限购
        virtual void OnRecv_UpdateMallDiscount(
            NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
            const NMallProt::TVecDiscount& vecDisItems //限购道具
        );

        //接收：获取新帮派战历史
        virtual void OnRecv_GetNewGuildBattleHistory(
                );

        //接收：新增新帮派战历史
        virtual void OnRecv_AddNewGuildBattleHistory(
                const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
                );

};
