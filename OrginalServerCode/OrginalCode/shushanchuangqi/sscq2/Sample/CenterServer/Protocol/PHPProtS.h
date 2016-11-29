
#pragma once
#include "PHPProtSvr.h"

using namespace NPHPProt;

class CPHPProtS : public CPHPProtSvr
{
public:
    CPHPProtS() : _MaxNoticeNum(0) {}
    ~CPHPProtS() {}

public:
	//接收：玩家充值仙石
	virtual bool OnRecv_OnUserRecharge(
        UINT16 wServerNo, //区服ID
		const std::string& strToken, //memcach校验
        const std::string& strNo, //充值流水号
		UINT64 qwUserID, //用户ID
        UINT16 wID, //仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])或者Q点直购道具ID
		UINT32 dwValue, //充值的仙石包数量或者Q点直购道具数量
        const std::string& strUINT, //单位,默认发QQCOIN(Q点)
        const std::string& strMoney, //仙石对应的QQCOIN值
		const std::string& strParam, //用来url请求
		shared_func<SOnUserRechargeAck>& fnAck //返回回调函数
	);

	//接收：修改玩家各种活动积分信息
	virtual bool OnRecv_ModifyActivityIntegral(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //用户ID
		EActivityType eType, //活动ID
		INT32 dwActCount, //活动积分
		shared_func<SModifyActivityIntegralAck>& fnAck //返回回调函数
	);

    //接收：获取玩家信息
	virtual bool OnRecv_GetPlayerInfo(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
	);

    virtual bool OnRecv_GetOnlineNum(
		UINT16 wServerNo, //区服ID
		shared_func<SGetOnlineNumAck>& fnAck //返回回调函数
	);

    //接收：获取玩家背包信息
	virtual bool OnRecv_GetPlayerBagInfo(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
	);

    //接收：删除物品
	virtual bool OnRecv_DelItem(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		UINT8 byType, //1；背包，2：仓库
		UINT64 qwInstID, //物品唯一ID
		UINT16 wCount, //堆叠数
		shared_func<SDelItemAck>& fnAck //返回回调函数
	);

    //接收：封号/解封
	virtual bool OnRecv_LockOrUnlockUser(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台操作类型
		UINT32 dwEndTime, //时间
		const std::string& strArgument, //理由
		shared_func<SLockOrUnlockUserAck>& fnAck //返回回调函数
	);

    //接收：禁言/解禁
	virtual bool OnRecv_LockOrUnlockSpeak(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台操作类型
		UINT32 dwEndTime, //时间
		const std::string& strArgument, //理由
		shared_func<SLockOrUnlockSpeakAck>& fnAck //返回回调函数
	);

    //接收：发放物品/货币
	virtual bool OnRecv_SendItem(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendItemAck>& fnAck //返回回调函数
	);

    //接收：减少货币数量
	virtual bool OnRecv_SubMoney(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		shared_func<SSubMoneyAck>& fnAck //返回回调函数
	);

    //接收：发放VIP物品
	virtual bool OnRecv_SendVIPItem(
		UINT16 wServerNo, //区服ID
		UINT8 byVIPMinLevel, //VIP最小等级
		UINT8 byVIPMaxLevel, //VIP最大等级
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendVIPItemAck>& fnAck //返回回调函数
	);

    //接收：发放帮派物品
	virtual bool OnRecv_SendClanItem(
		UINT16 wServerNo, //区服ID
		UINT64 qwClanID, //帮派ID
		ESendTarget eTarget, //对象
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendClanItemAck>& fnAck //返回回调函数
	);

    //接收：全区发放物品
	virtual bool OnRecv_GlobalSendItem(
		UINT16 wServerNo, //区服ID
		ESendTarget eTarget, //对象
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SGlobalSendItemAck>& fnAck //返回回调函数
	);

    //接收：发送邮件
	virtual bool OnRecv_SendMail(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		shared_func<SSendMailAck>& fnAck //返回回调函数
	);

    //接收：全区发送邮件
	virtual bool OnRecv_GlobalSendMail(
		UINT16 wServerNo, //区服ID
	    ESendTarget eTarget, //对象
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		shared_func<SGlobalSendMailAck>& fnAck //返回回调函数
	);

    //接收：发送公告
	virtual bool OnRecv_GlobalSendNotice(
		UINT16 wServerNo, //区服ID
		const std::string& strContent, //系统弹窗内容
		EPlatformType ePlatformType, //平台类型
		EShowType eShowType, //显示区域
		ERollType eRollType, //是否滚动
		ESendType eSendType, //是否立即发送
		UINT32 dwBeginTime, //公告开始时间(注：如果选择立即发送，dwBeginTime为0)
		UINT32 dwEndTime, //公告结束时间(注：如果选择立即发送，dwEndTime为0)
		shared_func<SGlobalSendNoticeAck>& fnAck //返回回调函数
	);

    //接收：发送系统弹窗
	virtual bool OnRecv_GlobalSendSysDialog(
		UINT16 wServerNo, //区服ID
		EPlatformType ePlatformType, //平台类型
		EDialogType eDialogType, //弹窗类型
		shared_func<SGlobalSendSysDialogAck>& fnAck //返回回调函数
	);

    //接收：设置玩家等级
	virtual bool OnRecv_SetPlayerLevel(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		UINT16 wLevel, //等级
		shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
	);

	//接收：设置玩家VIP等级
	virtual bool OnRecv_SetPlayerVIPLevel(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		UINT32 wLevelOrGrowthValue, //等级or成长值
		shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
	);

	//接收：日常任务管理
	virtual bool OnRecv_TaskManager(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		EPHPTaskType eTaskType, //任务类型
		shared_func<STaskManagerAck>& fnAck //返回回调函数
    );

    //接收：获取活动列表信息
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	);

    //接收：开启指定活动
	virtual bool OnRecv_OpenAct(
		EActivityType eType, //活动ID
		UINT32 dwBegin, //活动开启时间
		UINT32 dwEnd, //活动结束时间
		shared_func<SOpenActAck>& fnAck //返回回调函数
    );

    //接收：开启商城限购活动
	virtual bool OnRecv_OpenDiscountActivity(
		UINT16 wServerNo, //区服ID
		UINT8 byPos, //限购位置(0,1,2表示)
		UINT8 byOptType, //操作类型(0：增加；1：删除)
		const std::string& strDisItems, //限购道具信息(itemID,原价,折扣价|...)
		UINT8 byLimitType, //类型限制(0无条件、1充值限购、2消费限购)
		UINT32 dwLimitValue, //达到的仙石数量限制(0无条件、1充值限购、2消费限购)
		UINT16 wLimitCount, //购买道具个数限制
		UINT32 dwBeginTime, //限购开始时间
		UINT32 dwEndTime, //限购结束时间
		shared_func<SOpenDiscountActivityAck>& fnAck //返回回调函数
	);

    //接收：平台信息
	virtual void OnRecv_PlatformInfo(
		EPlatformType byPtType, //平台类型
		EQQPlatformType byQQPtType, //QQ平台类型
		UINT8 byQQPtLv, //QQ平台类型等级
		UINT8 byQQPtYearType, //是否年费
		UINT8 byQQPtLuxuryType, //是否豪华
		const std::string& customPar1, //广告主来源
		const std::string& customPar2, //广告次来源
		const std::string& strOpenId, //openID
		const std::string& strOpenKey //openKey
	);

	//接收：任务集市中任务状态查询
	bool OnRecv_GetTaskState(
		UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
		UINT32 dwTaskID, //任务ID
		UINT8 byStep, //步骤ID
		ETaskOpt eTaskOpt, //任务操作
		shared_func<SGetTaskStateAck>& fnAck //返回回调函数
	);

	//接收：Test
	virtual void OnRecv_TestPHP(
	);

private:
    //发送邮件
    bool SendMail(
        const std::string& strTitle,
        const std::string& strContent, 
        TVecUINT64 vecReceiveID);

    //通过邮件发放物品
    bool SendItemByMail(
        const std::string& strTitle,
        const std::string& strContent, 
        const std::string& strItem, 
        TVecUINT64 vecReceiveID);

	//接收：同步微信微博人数
	virtual bool OnRecv_SynWeiweiPersonNum(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //任务ID
		UINT32 dwCount, //步骤ID
		shared_func<SSynWeiweiPersonNumAck>& fnAck //返回回调函数
	);

	//接收：检测CDK
	virtual bool OnRecv_CheckCDK(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK, //CDK码
		shared_func<SCheckCDKAck>& fnAck //返回回调函数
	);
	//接收：QQAlarm安装
	virtual bool OnRecv_SynQQAlarm(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		shared_func<SSynQQAlarmAck>& fnAck //返回回调函数
	);
	//接收：天赐宝箱活动参数修改
	virtual bool OnRecv_ModifyChest(
		const SChestInfo& sInfo, //数据
		shared_func<SModifyChestAck>& fnAck //返回回调函数
	);

	//接收：设置汇灵盏奖励池
	virtual bool OnRecv_SetPool(
		UINT8 byType, //类型，0表示设置奖励池最大值，1表示设置奖励池现有值
		UINT32 dwValue, //数据
		shared_func<SSetPoolAck>& fnAck //返回回调函数
	);
	
    //接收：请求玩家累计登入天数
	virtual bool OnRecv_GetLoginDays(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
	);
public:
    //系统公告定时滚动检测
	void TimerCheck();

    //加载所有玩家ID和名字
    void LoadFromDB();

    //接受所有玩家ID和名字
    void RecvAllUserIDAndName(
            UINT32 dwTotalSize, //总条数
            const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
        );

    //加载所有公告
    void LoadNoticeFromDB();

    //接受所有公告
    void RecvAllNotice(
            const NPHPProt::TVecNotice& vecNotice //公告信息
        );

    //通过userID查名字
    bool GetNameByID(UINT64 qwUsrID,string& strName);

    //通过名字查userID
    bool GetIDByName(const string& strName, UINT64 &qwUsrID);

    bool IsActOpen(EActivityType eType);
    string MakeName(UINT16 wServerNo, const string& strName);
    
    //GM发放帮派物品
    bool GMSendClanItem(
            UINT64 qwClanID, //帮派ID
            const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
            const std::string& strTitle, //邮件标题
            const std::string& strContent //邮件内容
        );

    bool GMGlobalSendItem(
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent //邮件内容
        );

    bool GMSendItem(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent //邮件内容
        );

    bool GMLockOrUnlockUser(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        UINT8 byOptType, //操作类型((1:封号；2：解封)
        UINT32 dwEndTime //时间
        );

    bool GMLockOrUnlockSpeak(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        UINT8 byOptType, //后台操作类型
        UINT32 dwEndTime //时间
        );
    void PullWeiboNum(); //定时拉微博收听人数
    

    /* 测试
    bool OnSendItem(
        UINT16 wServerNo, //区服ID
        const std::string& strUserID, //格式：用户AID|户BID|..
        const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        const std::string& strArgument //理由
        );
     */   
    bool GMGlobalSendNotice(const std::string& strContent);

	//接收：发送工会聊天信息
	virtual bool OnRecv_SendQQGroupMsg(
		UINT64 qwGroupUserID, //绑定qq的玩家ID
		UINT16 wServerNo, //聊天玩家区号ID
		UINT64 qwUserID, //聊天玩家账号ID
		const std::string& strChatMsg, //聊天
		shared_func<SSendQQGroupMsgAck>& fnAck //返回回调函数
	);
	//接收：删除公告
	virtual bool OnRecv_GlobalDelNotice(
		UINT16 wServerNo, //区服ID
		UINT32 dwNoticeID, //公告ID
		shared_func<SGlobalDelNoticeAck>& fnAck //返回回调函数
	);
	//接收：添加称号
	bool OnRecv_SendTitle(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID, //TitleID
		shared_func<SSendTitleAck>& fnAck //返回回调函数
	);

public:
    string GetUserNameByID(UINT64 qwRoleID);
private:

    UINT32 _MaxNoticeNum;
    TVecUINT64 _vecUserID; //全区userID
    map<UINT64, string> _mapUserIDAndName; //全区userID和名字
    map<string, UINT64> _mapUserNameAndID; //全区userID和名字
    map<UINT32, SNotice> _mapNotice; //所有公告
};

extern CPHPProtS g_PHPProtS;
