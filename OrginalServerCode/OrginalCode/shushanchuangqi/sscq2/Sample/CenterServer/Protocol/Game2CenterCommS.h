#pragma once
#include "Game2CenterCommSvr.h"
#include "stdafx.h"
using namespace NGame2CenterComm;

class CGame2CenterCommS : public CGame2CenterCommSvr
{
    public:
        //接收：心跳
        virtual void OnRecv_KeepAlive(
                );

        //接收：GameServer初始化完成通知
        virtual void OnRecv_GameSvrInitNft(
                );

        //接收：GameServer数据同步请求
        virtual void OnRecv_GameSvrDataSyncReq(
                ESyncKey eSyncKey, //同步Key
                UINT16 wDestGroup, //目的服务器组号
                UINT8 byDestIndex, //目的GameServer(0为全部)
                const TVecINT32& vecParam, //同步参数
                const std::string& strSyncData //同步数据
                );
        //接收：账号进入游戏通知
        virtual void OnRecv_UserLoginNtf(
                UINT64 qwUsrID, //账号ID
                const SUserEnterInfo& rUserInfo //帐号进入信息
                ) ;

        //接收：账号退出游戏通知
        virtual void OnRecv_UserLogoutNtf(
                UINT64 qwUsrID //账号ID
                );

        //接收：账号替换通知
        virtual void OnRecv_UserReplaceNtf(
                UINT64 qwUsrID //账号ID
                );
        //接收：帐号跳GameServer通知
        virtual void OnRecv_UserJumpSvrNtf(
                UINT64 qwUsrID //账号ID
                );

        //接收：角色同步属性通知
        virtual void OnRecv_UserSyncPropNtf(
                UINT64 qwUsrID, //帐号ID
                EUserSyncPropField eField, //同步属性类型
                const std::string& strVal //值
                );

        //接收：是否为好友
        virtual bool OnRecv_IsFriend(
                UINT64 qwUsrID, //账号ID
                UINT64 qwFriID, //好友账号ID
                shared_func<SIsFriendAck>& fnAck //返回回调函数
                );

        //接收：是否为帮派成员
        virtual bool OnRecv_IsSameGuild(
                UINT64 qwUsrID, //账号ID
                UINT64 qwOtherID, //帮派成员ID
                shared_func<SIsSameGuildAck>& fnAck //返回回调函数
                );

        //接收：获取帮派ID
        virtual bool OnRecv_GetGuildID(
                UINT64 qwRoleID, //玩家ID
                shared_func<SGetGuildIDAck>& fnAck //返回回调函数
                );

        //接收：获取帮派ID
        virtual bool OnRecv_GetGuildName(
                UINT64 qwGuildID, //帮派ID
                shared_func<SGetGuildNameAck>& fnAck //返回回调函数
                );

        //接收：帮派广播
        virtual void OnRecv_NotifyGuildInfo(
                UINT64 qwGuildID, //帮派ID
                const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
                const std::string& strData //具体信息
                );

        //接收：发送系统邮件
        virtual void OnRecv_SendMail(
                const std::string& strSender, //发送者
                const std::string& strTitle, //标题
                const NMailProt::SysMailSendTxt& strMsgInfo, //内容
                const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
                const TVecUINT64& vecTargetIDs //接受者IDs
                );
        //接收：同步增加icon
        virtual void OnRecv_SynIconAppear(
                UINT64 qwRoleID, //角色ID
                const std::string& szIcon //功能
                ) ;

        //接收：增加帮派贡献
        virtual void OnRecv_AddGuildContribution(
                UINT64 qwRoleID, //玩家ID
                UINT32 dwContribution //帮派贡献
                );

        //接收：增加玩家九疑鼎火种
        virtual void OnRecv_ActiveTripodFire(
            UINT64 qwRoleID, //玩家ID
            UINT16 wFireID //火种ID
        );
    
	    //接收：CenterServer状态请求
	    virtual bool OnRecv_GetCenterState(
	    	shared_func<SGetCenterStateAck>& fnAck //返回回调函数
	    );

        //接收：更新登录参数
        virtual void OnRecv_UpdatePlatformParam(
                UINT64 qwRoleID, //玩家ID
                const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
                UINT32 dwIndex //当前平台索引
                );
        //接收：更新登录其他参数
        virtual void OnRecv_UpdateEnterString(
                UINT64 qwRoleID, //玩家ID
                const TVecString& vecEnterString //平台参数列表
                );
        //接收：发送全服活动信息
        virtual void OnRecv_SendWonderType(
                EWonderActType eActType, //活动类型
                UINT64 qwRoleID, //玩家ID
                UINT32 dwCond //条件ID
                );
        //接收：扣除帮贡
        virtual bool OnRecv_SubGuildContribution(
                UINT64 qwRoleID, //玩家ID
                UINT32 dwContribution, //帮贡数量
                shared_func<SSubGuildContributionAck>& fnAck //返回回调函数
                );
	    //接收：美女抽奖log
	    virtual void OnRecv_BeautyLotteryLog(
		        const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
	    );
        //接收：邀请好友成功
        virtual void OnRecv_InviteFriend(
	        UINT64 qwUserID, //邀请人
	        UINT64 qwInvitedUserID //被邀请人
        );

        //接收：通知帮派兑换物品开始
        virtual void OnRecv_NotifyGuildExchangedItemBegin(
            const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
        );

        //接收：同步在Center使用的buff结束时间
        virtual void OnRecv_SyncGameBuffUseInCenter(
		    UINT64 qwRoleID, //玩家ID
            UINT16 wBuffID, //buffID
            UINT32 dwEndTime //结束时间
        );

        //接收：同步活动参数
        virtual void OnRecv_SyncGameActiveParam(
                ActiveParam eParam, //参数类型
                const TVecUINT32& vecParam //参数
                ) ;

        //接收：获取全局Var值
        virtual bool OnRecv_GetSystemVar(
                const TVecUINT16& vecVarID, //varID列表
                shared_func<SGetSystemVarAck>& fnAck //返回回调函数
                );
        //接收：设置全局Var值
        virtual bool OnRecv_SetSystemVar(
                const TVecUINT16& vecVars, //varID列表
                const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
                shared_func<SSetSystemVarAck>& fnAck //返回回调函数
                );
};
