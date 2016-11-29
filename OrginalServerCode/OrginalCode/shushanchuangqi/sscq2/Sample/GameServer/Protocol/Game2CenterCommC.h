#pragma once
#include "Game2CenterCommClt.h"
#include "RoleInfoDefine.h"
#include "ItemType.h"
#include "ServerDefine.h"
using namespace NGame2CenterComm;
using namespace NRoleInfoDefine;
using namespace NMailProt;
struct SItemCFG;
typedef function<void(bool,bool,UINT64)> BattleResult; 
class CGame2CenterCommC : public CGame2CenterCommClt
{
    public:

        //接收：替换帐号
        virtual bool OnRecv_ReplaceUser(
                UINT64 qwUsrID, //帐号ID
                shared_func<SReplaceUserAck>& fnAck //返回回调函数
                );

        //接收：GM指令
        virtual bool OnRecv_GMCmd(
                UINT64 qwUsrID, //帐号ID
                const std::string& strInfo, //GM指令信息
                shared_func<SGMCmdAck>& fnAck //返回回调函数
                );
        //接收：充值接口
        virtual bool OnRecv_AddTotalRecharge(
            const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
            const std::string& strUdp1, //udpLog参数1(平台传来的)
            const std::string& strUdp2, //udpLog参数2(平台传来的)
            shared_func<SAddTotalRechargeAck>& fnAck //返回回调函数
        );
        //接收：充值接口(改版:加仙石礼包到邮件)
        virtual bool OnRecv_AddRechargeMailItem(
            const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
            const std::string& strUdp1, //udpLog参数1(平台传来的)
            const std::string& strUdp2, //udpLog参数2(平台传来的)
            shared_func<SAddRechargeMailItemAck>& fnAck //返回回调函数
        );
        //接收：补偿玩家未创建预先充值的仙石
        virtual bool OnRecv_AddTotalPrepaid(
            UINT64 qwUsrID, //帐号ID
            UINT32 dwGold, //仙石数量
            shared_func<SAddTotalPrepaidAck>& fnAck //返回回调函数
        );

        //接收：Q点直购道具
        virtual bool OnRecv_AddQQCoinBuyItem(
            UINT64 qwUsrID, //帐号ID
            const TVecUserItem& vecUserItem, //物品列表
            shared_func<SAddQQCoinBuyItemAck>& fnAck //返回回调函数
        );

        //接收：询问可否提取附件
        virtual bool OnRecv_CheckMailAttch(
                UINT64 qwUsrID, //帐号ID
                UINT64 qwMailID, //邮件ID
                const NMailProt::TVecMailAttachment& vecItemInfo, //附件
                shared_func<SCheckMailAttchAck>& fnAck //返回回调函数
                ) ;
        //接收：发送附件
        virtual void OnRecv_SendMailAttch(
                UINT64 qwUsrID, //帐号ID
                UINT64 qwMailID, //邮件ID
                const NMailProt::TVecMailAttachment& vecItemInfo //附件
                ) ;

        //接收：修改签名
        virtual void OnRecv_SetSign(
                UINT64 qwUsrID, //帐号ID
                const std::string& strSign //签名
                );

        //接收：修改表情
        virtual void OnRecv_SetMood(
                UINT64 qwUsrID, //帐号ID
                UINT16 wMood //表情
                );
        //请求和他人发起战斗
        virtual bool OnRecv_FigtherToOther(
                UINT64 qwUsrID, //帐号ID
                UINT64 qwOtherID, //他人的ID
                UINT32 dwCost, //花费的游戏币
                NBattleGS::EBattleType eBattleType,
				UINT32 dwBufferID, //临时增加的buffer
				UINT32 dwSkillAttrID, //增加的属性
				UINT32 dwCount, //buffer叠加层数
                shared_func<SFigtherToOtherAck>& fnAck //返回回调函数
                );
        //接收：询问可否放下掉落
        virtual bool OnRecv_CanPushLoot(
                UINT64 qwUsrID, //帐号ID
                UINT32 dwLootId, //掉落的ID
                shared_func<SCanPushLootAck>& fnAck //返回回调函数
                );

        //接收：掉落到玩家包裹
        virtual void OnRecv_PushLoot(
                UINT64 qwUsrID, //帐号ID
                EOpSource eSource, //原因
		        NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
                UINT32 dwLootId //掉落的ID
                );
        //接收：扣钱或物品
        virtual bool OnRecv_ReduceItem(
                UINT64 qwUsrID, //帐号ID
		        NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
                UINT32 dwID, //钱或物品ID
                UINT32 dwCount,//数量
                shared_func<SReduceItemAck>& fnAck //返回回调函数
                ); 

        //接收：物品数量是否够
        virtual bool OnRecv_CanReduceItem(
                UINT64 qwUsrID, //帐号ID
                UINT32 dwItemID, //物品ID
                UINT32 dwCount, //数量
                shared_func<SCanReduceItemAck>& fnAck //返回回调函数
                );
        //接收：查询玩家属性
        virtual bool OnRecv_GetUserUINTProp(
                UINT64 qwUsrID, //帐号ID
                EPlayerUINTProp eUINTPropType, //属性类型
                shared_func<SGetUserUINTPropAck>& fnAck //返回回调函数
                );

        //接收：设置玩家属性
        virtual bool OnRecv_SetUserUINTProp(
                UINT64 qwUsrID, //帐号ID
                EPlayerUINTProp eUINTPropType, //属性类型
                UINT32 dwValue, //属性值
                shared_func<SSetUserUINTPropAck>& fnAck //返回回调函数
                );

        //接收：扣除物品/钱币
        virtual bool OnRecv_UserSubItem(
                UINT64 qwUsrID, //帐号ID
		        NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
                const TVecUserItem& vecUserItem, //物品列表
                shared_func<SUserSubItemAck>& fnAck //返回回调函数
                );

        //接收：添加物品/钱币
        virtual bool OnRecv_UserAddItem(
                UINT64 qwUsrID, //帐号ID
		        NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
                const TVecUserItem& vecUserItem, //物品列表
                shared_func<SUserAddItemAck>& fnAck //返回回调函数
                );


        //接收：转发系统消息
        virtual void OnRecv_SendSysMsg(
                UINT64 qwUsrID, //帐号ID
                UINT16 wMsgID //消息ID
                );

        //接收：任务事件通知
        virtual void OnRecv_ActionNotify(
                UINT64 qwUsrID, //帐号ID
                UINT16 wAction //通知类型
                );

        //接收：气泡事件通知
        virtual void OnRecv_BubbleNotify(
                UINT64 qwUsrID, //帐号ID
                NProtoCommon::EDataChange eType, //修改类型
                UINT16 wMsgID, //通知类型
                const TVecINT64& vecParam, //整型变量
                const TVecString& vecString //字符串型变量
                );

        //接收：玩家帮派等级更新
        virtual void OnRecv_GuildLevelUpdated(
                UINT64 qwRoleID, //玩家ID
                UINT16 wLevel //帮派等级
                );

        //接收：玩家帮派名有更新
        virtual void OnRecv_GuildNameUpdated(
                UINT64 qwRoleID, //玩家ID
                const std::string& strGuildName //帮派名称
                );

        //接收：帮派技能属性更新
        virtual void OnRecv_GuildTechUpdate(
                UINT64 qwRoleID, //玩家唯一ID
                const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
                const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
                );

        //接收：重新加载表格
        virtual void OnRecv_ReloadTable(
                const TVecString& vecTableName //表格名字
                );

        //接收：玩家九疑鼎属性更新
        virtual void OnRecv_TripodAttrUpdate(
            UINT64 qwRoleID, //玩家唯一ID
            const TVecUINT32& vecValue //九疑鼎ID、等级
        );

        //接收：完成GetCond条件
        virtual bool OnRecv_ProcessCond(
            UINT64 qwUsrID, //玩家ID
            UINT16 wCondID, //条件ID
		    NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
            shared_func<SProcessCondAck>& fnAck //返回回调函数
        );

        //接收：玩家升级九疑鼎
        virtual bool OnRecv_UpgradeTripod(
            UINT64 qwUsrID, //玩家ID
            UINT8 byTripodID, //九疑鼎ID
            UINT8 byLevel, //九疑鼎当前等级
            UINT32 dwExp, //九疑鼎当前经验值
		    UINT8 byOneKey, //是否一键
            shared_func<SUpgradeTripodAck>& fnAck //返回回调函数
        );

        //接收：加速九疑鼎炼丹(道具入鼎)
        virtual bool OnRecv_SpeedTripod(
            UINT64 qwUsrID, //玩家ID
            UINT32 dwCurSoul, //当前九疑鼎的火种元气值
            UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
            const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
            shared_func<SSpeedTripodAck>& fnAck //返回回调函数
        );

        //接收：判断玩家是否拥有散仙
        bool OnRecv_CheckHasFighter(
            UINT64 qwUsrID, //玩家ID
            UINT16 wFighterID, //散仙ID
            shared_func<SCheckHasFighterAck>& fnAck //返回回调函数
        );

        //接收：获取战斗力
        virtual bool OnRecv_GetBattlePoint(
                UINT64 qwUsrID, //玩家ID
                shared_func<SGetBattlePointAck>& fnAck //返回回调函数
                );

	    //接收：玩家发事件中心消息
	    virtual void OnRecv_OnPlayerEvent(
		    UINT64 qwUsrID, //玩家ID
		    NEventCenter::EventType eEventType, //事件类型
		    const TVecINT32& vecParam, //事件参数
			const std::string& strParam, //事件参数
		    bool bLog //事件参数
        );

        //接收：增加或者设置玩家GameVar数值
        virtual void OnRecv_AddORSetGameVar(
            UINT64 qwUsrID, //玩家ID
            UINT8 byType, //0增加 >0设置
            const TVecUINT16& vecVars, //varID列表
            const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
        );

        //接收：清除GameVar
        virtual void OnRecv_DeleteGameVar(
            UINT64 qwUsrID, //玩家ID
            const TVecUINT16& vecVars //varID列表
        );

        //接收：增加商城限购活动
        virtual void OnRecv_AddMallDiscount(
            const NMallProt::SDiscount& oDiscount//限购道具列表
        );
        
        //接收：清除商城限购活动
        void OnRecv_ClearMallDiscount(
            UINT8 byPos //限购道具栏位
        );

        //接收：设置玩家等级
        virtual bool OnRecv_SetPlayerLevel(
            UINT64 qwUserID, //玩家ID
            UINT16 wLevel, //玩家等级
            shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
        );

        //接收：设置玩家VIP等级
        virtual bool OnRecv_SetPlayerVIPLevel(
            UINT64 qwUserID, //玩家ID
            NPHPProt::EOptType eOptType, //后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
            UINT32 dwLevelOrGrowthValue, //等级or成长值
            shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
        );

        //接收：设置日常任务
        virtual bool OnRecv_SetDayTask(
            const TVecUINT64& vecUserID, //UserID
            NPHPProt::EPHPTaskType eTaskType, //日常任务类型
            shared_func<SSetDayTaskAck>& fnAck //返回回调函数
        );

        //接收：获取玩家信息
        virtual bool OnRecv_GetPlayerInfo(
            UINT64 qwUserID, //玩家ID
            shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
        );

        //接收：获取玩家背包信息
        virtual bool OnRecv_GetPlayerBagInfo(
                UINT64 qwUserID, //玩家ID
                shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
        );

        //接收：删除玩家物品
        virtual bool OnRecv_DelPlayerItem(
            UINT64 qwUserID, //用户ID
            UINT8 byType, //1；背包，2：仓库
            UINT64 qwInstID, //物品唯一ID
            UINT16 wCount, //堆叠数
            shared_func<SDelPlayerItemAck>& fnAck //返回回调函数
        );

        //接收：扣除玩家钱币
        virtual bool OnRecv_SubPlayerMoney(
            const TVecUINT64& vecUserID, //玩家ID
            const TVecUserItem& vecUserItem, //物品列表
            shared_func<SSubPlayerMoneyAck>& fnAck //返回回调函数
        );
     
        //接收：给玩家用掉落包发系统邮件
	 void OnRecv_SendSysMailByLootId(
		UINT64 qwUserID, //用户ID
		UINT16 wTitle, //邮件标题
		UINT16 wText, //邮件正文
		const TVecString& vecParam, //邮件参数
		UINT32 dwLootId, //掉落包
        UINT32 dwRate //倍率
	);

	//接收：任务集市查询
	bool OnRecv_GetTaskStateForPlatfrom(
		UINT64 qwUserID, //玩家ID
		UINT32 dwTaskID, //任务ID
		UINT8 byStep, //步骤ID
		UINT8 byOpt, //操作类型
		shared_func<SGetTaskStateForPlatfromAck>& fnAck //返回回调函数
	);

	//接收：同步微信微博人数
	virtual void OnRecv_SynWeiweiPersonNum(
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	);

	//接收：检测CDK
	virtual void OnRecv_CheckCDK(
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	);

	//接收：QQAlarm安装
	virtual void OnRecv_SynQQAlarm(
		UINT64 qwUserID //玩家ID
	);
	
	//接收：运营修改宝箱信息
	virtual void OnRecv_ModifyChest(
		const NPHPProt::SChestInfo& sChestInfo //信息
	);

    //接收：Center2Game活动时间同步
	virtual void OnRecv_SyncActivityTime(
		const NProtoCommon::SActivityTime& sActTime //信息
	);
    //接收：同步活动状态
	virtual void OnRecv_SyncActState(
		const SActivityState& oInfo, //数据
        bool bNotify
	);

	//接收：请求累计登入天数
	virtual bool OnRecv_GetLoginDays(
		UINT64 qwUserID, //玩家ID
		shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
	);
	
    //接收：添加Title
	virtual void OnRecv_SyncTitle(
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	);

    //接收：扣除礼卷钻石
    virtual bool OnRecv_SubGoldOrCoupon(
	    UINT64 qwUsrID, //帐号ID
	    NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	    UINT32 dwCount, //扣款数量
	    shared_func<SSubGoldOrCouponAck>& fnAck //返回回调函数
    );

    public:
        void TransMailAttachToItem(const NMailProt::TVecMailAttachment& vecItemInfo,vector<CItemPtr>& rVecCItem,TVecResource& vecRes);
        void TransMailAttachToItem(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo);
        void AddMailItemProp(CItemPtr pItem,const SMailItemInfo& rMailInfo);
        /*
           void CreateMailEquip(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo);
           void CreateMailFashion(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo);
           void CreateMailCitta(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo);
           */
        void CreateMailItem(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo,SItemCFG& rItemCfg);
        void CreateMailItemWithNum(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo,UINT16 wCount,UINT16 wEachCount);
        void TransMailStance(vector<CItemPtr>& rVecCItem, SItemPtr ItemPtr);
        bool SetDayTask(const UINT64 qwUserID, NPHPProt::EPHPTaskType eTaskType);
        bool SubPlayerMoney(const UINT64 qwUserID, const TVecUserItem& vecUserItem);
        bool GetPlayerInfo(UINT64 qwUserID, NPHPProt::SPlayerInfo& sPlayerInfo);
        
        void TimerCheck();
        bool IsCenterInited() const { return _bCenterInited; }
        CGame2CenterCommC() : _bCenterInited(false),_bTimerClosed(false) { }
    public:
        void  FighterToOther(UINT64 qwUsrID,UINT64 qwOtherID,bool bDrop,
                NBattleGS::EBattleType eBattleType, //战斗类型
	            UINT32 dwBufferID, //临时增加的buffer
		        UINT32 dwSkillAttrID, //增加的属性
		        UINT32 dwCount, //buffer叠加层数
                BattleResult fun);
    private:
        bool _bCenterInited;
        bool _bTimerClosed;
};
