<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    PHPProt.php
//  Purpose:      PHP相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//后台操作结果
class EOptResult
{
	const eOptResultSucc = 0; //成功
	const eOptResultFailed = 1; //失败
}

//后台操作类型
class EOptType
{
	const eOptNone = 0; //无
	const eOptLockUser = 1; //封号
	const eOptUnlockUser = 2; //解封
	const eOptLockSpeak = 3; //禁言
	const eOptUnlockSpeak = 4; //解禁
	const eOptSetPlayerVIPLevel = 5; //设置玩家VIP等级
	const eOptAddGrowthValue = 6; //增加玩家成长值
	const eOptEnd = 7; //结束
}

//日常任务类型
class EPHPTaskType
{
	const ePHPTaskNone = 0; //无
	const ePHPYaMenTask = 1; //衙门任务
	const ePHPShiMenTask = 2; //师门任务
	const ePHPTaskEnd = 3; //结束
}

//发放对象
class ESendTarget
{
	const eSendTargetNone = 0; //无
	const eIsOnline = 1; //在线玩家
	const eAll = 2; //所有玩家
	const eClanMember = 3; //帮派成员
	const eClanBag = 4; //帮派仓库
	const eSendTargetEnd = 5; //结束
}

//任务集市中任务操作
class ETaskOpt
{
	const eTaskOptNone = 0; //无
	const eTaskOptComplete = 1; //任务是否完成
	const eTaskOptCompAndReward = 2; //任务是否完成，若完成发放奖励
	const eTaskOptReward = 3; //发放奖励
	const eTaskOptEnd = 4; //结束
}

//任务集市状态返回
class ETaskState
{
	const eTaskStateNone = 0; //无
	const eTaskStateSuc = 1; //奖励发放成功或任务步骤完成
	const eTaskStateNoRole = 2; //玩家没有创建角色
	const eTaskStateNoComp = 3; //任务步骤没有完成
	const eTaskStateSended = 4; //奖励已经发放过
	const eTaskStateSendErr = 5; //发放奖励错误
	const eTaskStateParamErr = 6; //请求参数错误
	const eTaskStateOtherErr = 7; //其他错误
	const eTaskStateEnd = 8; //结束
}

//平台类型
class EPlatformType
{
	const ePlatformNone = 0; //无
	const ePlatformTypeQQYellow = 1; //QQ黄钻平台/Qzone
	const ePlatformTypeQQPengyou = 2; //QQ朋友/校友/黄钻
	const ePlatformTypeQQWeibo = 3; //QQ微博平台
	const ePlatformTypeQQPlus = 4; //QQ/Q+平台
	const ePlatformTypeQQGame = 5; //QQ蓝钻/游戏平台
	const ePlatformTypeQQ3366 = 6; //QQ蓝钻/3366平台/包子
	const ePlatformTypeQQKingxin = 7; //QQ官网平台/QQ会员
	const ePlatformTypeKingxin = 8; //恺英官网平台
	const ePlatformTypeEnd = 9; //结束
}

//QQ平台类型
class EQQPlatformType
{
	const eQQPlatformTypeNone = 0; //无
	const eQQPlatformTypeYellow = 1; //黄钻平台
	const eQQPlatformTypeBlue = 2; //蓝钻平台
	const eQQPlatformTypeRed = 3; //红钻/VIP平台
	const eQQPlatformTypeEnd = 4; //结束
}

//平台类型定义
class EPHPPtType
{
	const ePHPPtTypeNone = 0; //无
	const ePHPPtTypeQQYellow = 1; //QQ黄钻平台/Qzone
	const ePHPPtTypeQQPengyou = 2; //QQ朋友/校友/黄钻
	const ePHPPtTypeQQWeibo = 3; //QQ微博平台
	const ePHPPtTypeQQPlus = 4; //QQ/Q+平台
	const ePHPPtTypeQQGame = 5; //QQ蓝钻/游戏平台
	const ePHPPtTypeQQ3366 = 6; //QQ蓝钻/3366平台/包子
	const ePHPPtTypeQQKingxin = 7; //QQ官网平台/QQ会员
	const ePHPPtTypeKingxin = 8; //恺英官网平台
	const ePHPPtTypeMax = 9; //最大值
}

//公告显示区域类型
class EShowType
{
	const eShowNone = 0; //无
	const eChatWindowNotice = 1; //聊天窗口显示公告
	const eAllNotice = 2; //全部显示
	const eShowEnd = 3; //结束
}

//是否滚动
class ERollType
{
	const eRollNone = 0; //无
	const eIsRoll = 1; //滚动
	const eNoRoll = 2; //不滚动
	const eRollEnd = 3; //结束
}

//是否立即发送
class ESendType
{
	const eSendNone = 0; //无
	const eIsImmediateSend = 1; //立即发送
	const eNoImmediateSend = 2; //不立即发送
	const eSendEnd = 3; //结束
}

//弹窗类型
class EDialogType
{
	const eDialogNone = 0; //无
	const eUpdateNoticeDialog = 1; //更新公告弹窗
	const eSysDialog = 2; //系统弹窗
	const eDialogEnd = 3; //结束
}

//类型
class EActivityType
{
	const eActivity_None = 0; //无
	const eActivity_WorldBoss = 1; //世界boss活动
	const eActivity_LangHuanBless = 2; //琅环活动
	const eActivity_DragonBall = 3; //七星龙珠活动
	const eActivity_SevenConsume = 4; //七日消费活动
	const eActivity_QQCoin = 5; //Q币养成活动
	const eActivity_Max = 6; //结束
}

//UserID和Name
final class SUserIDAndName
{
	public $qwUserID; //(UINT64)用户ID
	public $strName; //(string)角色名称

	//构造函数
	function __construct()
	{
		$this->qwUserID = new Math_BigInteger;
		$this->strName = '';
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwUserID = $this->qwUserID;
		$obj->strName = $this->strName;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SUserIDAndName;
		$s->qwUserID = ByteUtil::readUINT64($data);
		$s->strName = ByteUtil::readString($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SUserIDAndName::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwUserID);
		ByteUtil::writeString($data, $this->strName);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//公告
final class SNotice
{
	public $dwNoticeID; //(UINT32)公告ID
	public $byNoticeType; //(UINT8)公告类型
	public $strContent; //(string)公告内容
	public $dwBeginTime; //(UINT32)公告开始时间
	public $dwEndTime; //(UINT32)公告结束

	//构造函数
	function __construct()
	{
		$this->dwNoticeID = 0;
		$this->byNoticeType = 0;
		$this->strContent = '';
		$this->dwBeginTime = 0;
		$this->dwEndTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwNoticeID = $this->dwNoticeID;
		$obj->byNoticeType = $this->byNoticeType;
		$obj->strContent = $this->strContent;
		$obj->dwBeginTime = $this->dwBeginTime;
		$obj->dwEndTime = $this->dwEndTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SNotice;
		$s->dwNoticeID = ByteUtil::readUINT32($data);
		$s->byNoticeType = ByteUtil::readUINT8($data);
		$s->strContent = ByteUtil::readString($data);
		$s->dwBeginTime = ByteUtil::readUINT32($data);
		$s->dwEndTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SNotice::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwNoticeID);
		ByteUtil::writeUINT8($data, $this->byNoticeType);
		ByteUtil::writeString($data, $this->strContent);
		ByteUtil::writeUINT32($data, $this->dwBeginTime);
		ByteUtil::writeUINT32($data, $this->dwEndTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家信息
final class SPlayerInfo
{
	public $qwUserID; //(UINT64)用户ID
	public $strName; //(string)角色名称
	public $wLevel; //(UINT16)等级
	public $strGuildName; //(string)帮派名
	public $qwGuildID; //(UINT64)帮派ID
	public $byJob; //(UINT8)职业(1、儒；2、释；3、道；4、墨)
	public $bySex; //(UINT8)性别(1、男；2、女)
	public $dwSilver; //(UINT32)银币
	public $dwGold; //(UINT32)仙石
	public $dwCoupon; //(UINT32)礼券
	public $byForbExpire; //(UINT8)是否禁言(0、否；1、是)
	public $byLockExpire; //(UINT8)是否封号(0、否；1、是)
	public $byVIPLevel; //(UINT8)VIP等级
	public $dwPrestige; //(UINT32)声望
	public $dwHonor; //(UINT32)荣誉
	public $dwDJ; //(UINT32)斗剑排名
	public $dwHistoryDJ; //(UINT32)历史最高斗剑
	public $dwCreateTime; //(UINT32)创角时间
	public $wShiMenTask; //(UINT16)师门任务
	public $wYaMenTaTask; //(UINT16)衙门任务

	//构造函数
	function __construct()
	{
		$this->qwUserID = new Math_BigInteger;
		$this->strName = '';
		$this->wLevel = 0;
		$this->strGuildName = '';
		$this->qwGuildID = new Math_BigInteger;
		$this->byJob = 0;
		$this->bySex = 0;
		$this->dwSilver = 0;
		$this->dwGold = 0;
		$this->dwCoupon = 0;
		$this->byForbExpire = 0;
		$this->byLockExpire = 0;
		$this->byVIPLevel = 0;
		$this->dwPrestige = 0;
		$this->dwHonor = 0;
		$this->dwDJ = 0;
		$this->dwHistoryDJ = 0;
		$this->dwCreateTime = 0;
		$this->wShiMenTask = 0;
		$this->wYaMenTaTask = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwUserID = $this->qwUserID;
		$obj->strName = $this->strName;
		$obj->wLevel = $this->wLevel;
		$obj->strGuildName = $this->strGuildName;
		$obj->qwGuildID = $this->qwGuildID;
		$obj->byJob = $this->byJob;
		$obj->bySex = $this->bySex;
		$obj->dwSilver = $this->dwSilver;
		$obj->dwGold = $this->dwGold;
		$obj->dwCoupon = $this->dwCoupon;
		$obj->byForbExpire = $this->byForbExpire;
		$obj->byLockExpire = $this->byLockExpire;
		$obj->byVIPLevel = $this->byVIPLevel;
		$obj->dwPrestige = $this->dwPrestige;
		$obj->dwHonor = $this->dwHonor;
		$obj->dwDJ = $this->dwDJ;
		$obj->dwHistoryDJ = $this->dwHistoryDJ;
		$obj->dwCreateTime = $this->dwCreateTime;
		$obj->wShiMenTask = $this->wShiMenTask;
		$obj->wYaMenTaTask = $this->wYaMenTaTask;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPlayerInfo;
		$s->qwUserID = ByteUtil::readUINT64($data);
		$s->strName = ByteUtil::readString($data);
		$s->wLevel = ByteUtil::readUINT16($data);
		$s->strGuildName = ByteUtil::readString($data);
		$s->qwGuildID = ByteUtil::readUINT64($data);
		$s->byJob = ByteUtil::readUINT8($data);
		$s->bySex = ByteUtil::readUINT8($data);
		$s->dwSilver = ByteUtil::readUINT32($data);
		$s->dwGold = ByteUtil::readUINT32($data);
		$s->dwCoupon = ByteUtil::readUINT32($data);
		$s->byForbExpire = ByteUtil::readUINT8($data);
		$s->byLockExpire = ByteUtil::readUINT8($data);
		$s->byVIPLevel = ByteUtil::readUINT8($data);
		$s->dwPrestige = ByteUtil::readUINT32($data);
		$s->dwHonor = ByteUtil::readUINT32($data);
		$s->dwDJ = ByteUtil::readUINT32($data);
		$s->dwHistoryDJ = ByteUtil::readUINT32($data);
		$s->dwCreateTime = ByteUtil::readUINT32($data);
		$s->wShiMenTask = ByteUtil::readUINT16($data);
		$s->wYaMenTaTask = ByteUtil::readUINT16($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPlayerInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwUserID);
		ByteUtil::writeString($data, $this->strName);
		ByteUtil::writeUINT16($data, $this->wLevel);
		ByteUtil::writeString($data, $this->strGuildName);
		ByteUtil::writeUINT64($data, $this->qwGuildID);
		ByteUtil::writeUINT8($data, $this->byJob);
		ByteUtil::writeUINT8($data, $this->bySex);
		ByteUtil::writeUINT32($data, $this->dwSilver);
		ByteUtil::writeUINT32($data, $this->dwGold);
		ByteUtil::writeUINT32($data, $this->dwCoupon);
		ByteUtil::writeUINT8($data, $this->byForbExpire);
		ByteUtil::writeUINT8($data, $this->byLockExpire);
		ByteUtil::writeUINT8($data, $this->byVIPLevel);
		ByteUtil::writeUINT32($data, $this->dwPrestige);
		ByteUtil::writeUINT32($data, $this->dwHonor);
		ByteUtil::writeUINT32($data, $this->dwDJ);
		ByteUtil::writeUINT32($data, $this->dwHistoryDJ);
		ByteUtil::writeUINT32($data, $this->dwCreateTime);
		ByteUtil::writeUINT16($data, $this->wShiMenTask);
		ByteUtil::writeUINT16($data, $this->wYaMenTaTask);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家背包信息
final class SPlayerBagInfo
{
	public $qwInstID; //(UINT64)物品唯一ID
	public $wItemID; //(UINT16)物品模板
	public $byType; //(UINT8)1；背包，2：仓库
	public $wCount; //(UINT16)堆叠数
	public $byBind; //(UINT8)0：非绑定，1：绑定

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->wItemID = 0;
		$this->byType = 0;
		$this->wCount = 0;
		$this->byBind = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->wItemID = $this->wItemID;
		$obj->byType = $this->byType;
		$obj->wCount = $this->wCount;
		$obj->byBind = $this->byBind;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPlayerBagInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->byType = ByteUtil::readUINT8($data);
		$s->wCount = ByteUtil::readUINT16($data);
		$s->byBind = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPlayerBagInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT8($data, $this->byType);
		ByteUtil::writeUINT16($data, $this->wCount);
		ByteUtil::writeUINT8($data, $this->byBind);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//天赐宝箱活动参数修改
final class SChestInfo
{
	public $dwTime; //(UINT32)开启时间
	public $byBig; //(UINT8)大宝箱个数
	public $byMid; //(UINT8)中宝箱个数
	public $bySmall; //(UINT8)小宝箱个数
	public $byPeroid; //(UINT8)活动持续时间
	public $wMapID; //(UINT16)宝箱刷新地图

	//构造函数
	function __construct()
	{
		$this->dwTime = 0;
		$this->byBig = 0;
		$this->byMid = 0;
		$this->bySmall = 0;
		$this->byPeroid = 0;
		$this->wMapID = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwTime = $this->dwTime;
		$obj->byBig = $this->byBig;
		$obj->byMid = $this->byMid;
		$obj->bySmall = $this->bySmall;
		$obj->byPeroid = $this->byPeroid;
		$obj->wMapID = $this->wMapID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SChestInfo;
		$s->dwTime = ByteUtil::readUINT32($data);
		$s->byBig = ByteUtil::readUINT8($data);
		$s->byMid = ByteUtil::readUINT8($data);
		$s->bySmall = ByteUtil::readUINT8($data);
		$s->byPeroid = ByteUtil::readUINT8($data);
		$s->wMapID = ByteUtil::readUINT16($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SChestInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwTime);
		ByteUtil::writeUINT8($data, $this->byBig);
		ByteUtil::writeUINT8($data, $this->byMid);
		ByteUtil::writeUINT8($data, $this->bySmall);
		ByteUtil::writeUINT8($data, $this->byPeroid);
		ByteUtil::writeUINT16($data, $this->wMapID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[OnUserRecharge:玩家充值仙石]的返回的参数组成的结构体
class SRetParam_OnUserRecharge
{
	public $byRet; //(UINT8)充值返回值(值为0:成功 非0其他错误)
	public $strError; //(string)错误码字符串(若成功为空)

	//构造函数
	function __construct()
	{
		$this->byRet = 0;
		$this->strError = '';
	}
};

//函数[ModifyActivityIntegral:修改玩家各种活动积分信息]的返回的参数组成的结构体
class SRetParam_ModifyActivityIntegral
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GetPlayerInfo:获取玩家信息]的返回的参数组成的结构体
class SRetParam_GetPlayerInfo
{
	public $vecPlayerInfo; //(SPlayerInfo的数组)玩家信息

	//构造函数
	function __construct()
	{
		$this->vecPlayerInfo = array();
	}
};

//函数[GetPlayerBagInfo:获取玩家背包信息]的返回的参数组成的结构体
class SRetParam_GetPlayerBagInfo
{
	public $vecPlayerBagInfo; //(SPlayerBagInfo的数组)玩家背包信息

	//构造函数
	function __construct()
	{
		$this->vecPlayerBagInfo = array();
	}
};

//函数[DelItem:删除物品]的返回的参数组成的结构体
class SRetParam_DelItem
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GetActList:获取活动列表信息]的返回的参数组成的结构体
class SRetParam_GetActList
{
	public $vecIDs; //(UINT16数组)活动列表

	//构造函数
	function __construct()
	{
		$this->vecIDs = array();
	}
};

//函数[OpenAct:开启指定活动]的返回的参数组成的结构体
class SRetParam_OpenAct
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[LockOrUnlockUser:封号/解封]的返回的参数组成的结构体
class SRetParam_LockOrUnlockUser
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[LockOrUnlockSpeak:禁言/解禁]的返回的参数组成的结构体
class SRetParam_LockOrUnlockSpeak
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GetOnlineNum:获取在线人数]的返回的参数组成的结构体
class SRetParam_GetOnlineNum
{
	public $dwOnlineNum; //(UINT32)在线人数

	//构造函数
	function __construct()
	{
		$this->dwOnlineNum = 0;
	}
};

//函数[SendItem:发放物品/货币]的返回的参数组成的结构体
class SRetParam_SendItem
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SubMoney:减少货币数量]的返回的参数组成的结构体
class SRetParam_SubMoney
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SendVIPItem:发放VIP物品]的返回的参数组成的结构体
class SRetParam_SendVIPItem
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SendClanItem:发放帮派物品]的返回的参数组成的结构体
class SRetParam_SendClanItem
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GlobalSendItem:全区发放物品]的返回的参数组成的结构体
class SRetParam_GlobalSendItem
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SendMail:发送邮件]的返回的参数组成的结构体
class SRetParam_SendMail
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GlobalSendMail:全区发送邮件]的返回的参数组成的结构体
class SRetParam_GlobalSendMail
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GlobalSendNotice:发送公告]的返回的参数组成的结构体
class SRetParam_GlobalSendNotice
{
	public $dwNoticeID; //(UINT32)返回公告ID
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->dwNoticeID = 0;
		$this->eOptResult = 0;
	}
};

//函数[GlobalDelNotice:删除公告]的返回的参数组成的结构体
class SRetParam_GlobalDelNotice
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GlobalSendSysDialog:发送系统弹窗]的返回的参数组成的结构体
class SRetParam_GlobalSendSysDialog
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[OpenDiscountActivity:开启商城限购活动]的返回的参数组成的结构体
class SRetParam_OpenDiscountActivity
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SetPlayerLevel:设置玩家等级]的返回的参数组成的结构体
class SRetParam_SetPlayerLevel
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SetPlayerVIPLevel:设置玩家VIP等级]的返回的参数组成的结构体
class SRetParam_SetPlayerVIPLevel
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[TaskManager:日常任务管理]的返回的参数组成的结构体
class SRetParam_TaskManager
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GetTaskState:任务集市中任务状态查询]的返回的参数组成的结构体
class SRetParam_GetTaskState
{
	public $wServerNo; //(UINT16)区服ID
	public $eTaskState; //(枚举类型：ETaskState)状态返回

	//构造函数
	function __construct()
	{
		$this->wServerNo = 0;
		$this->eTaskState = 0;
	}
};

//函数[SynWeiweiPersonNum:同步微信微博人数]的返回的参数组成的结构体
class SRetParam_SynWeiweiPersonNum
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[CheckCDK:检测CDK]的返回的参数组成的结构体
class SRetParam_CheckCDK
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SynQQAlarm:QQAlarm安装]的返回的参数组成的结构体
class SRetParam_SynQQAlarm
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[ModifyChest:天赐宝箱活动参数修改]的返回的参数组成的结构体
class SRetParam_ModifyChest
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SetPool:设置汇灵盏奖励池]的返回的参数组成的结构体
class SRetParam_SetPool
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[GetLoginDays:请求玩家累计登入天数]的返回的参数组成的结构体
class SRetParam_GetLoginDays
{
	public $dwDays; //(UINT32)累计登入天数
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->dwDays = 0;
		$this->eOptResult = 0;
	}
};

//函数[SendQQGroupMsg:发送工会聊天信息]的返回的参数组成的结构体
class SRetParam_SendQQGroupMsg
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

//函数[SendTitle:添加称号]的返回的参数组成的结构体
class SRetParam_SendTitle
{
	public $eOptResult; //(枚举类型：EOptResult)后台操作结果

	//构造函数
	function __construct()
	{
		$this->eOptResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：PHP相关协议
abstract class PHPProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家充值仙石
	function send_OnUserRecharge(
		$wServerNo,  //(UINT16)区服ID
		$strToken,  //(string)memcach校验
		$strNo,  //(string)充值流水号
		$qwUserID,  //(UINT64)用户ID
		$wID,  //(UINT16)仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])或者Q点直购道具ID
		$dwValue,  //(UINT32)充值的仙石包数量或者Q点直购道具数量
		$strUINT,  //(string)单位,默认发QQCOIN(Q点)
		$strMoney,  //(string)仙石对应的QQCOIN值
		$strParam //(string)用来url请求
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strToken);
		ByteUtil::writeString($data, $strNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT16($data, $wID);
		ByteUtil::writeUINT32($data, $dwValue);
		ByteUtil::writeString($data, $strUINT);
		ByteUtil::writeString($data, $strMoney);
		ByteUtil::writeString($data, $strParam);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：修改玩家各种活动积分信息
	function send_ModifyActivityIntegral(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID,  //(UINT64)用户ID
		$eType,  //(枚举类型：EActivityType)活动ID
		$dwActCount //(INT32)活动积分(负数表明减少)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT8($data, $eType);
		ByteUtil::writeINT32($data, $dwActCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取玩家信息
	function send_GetPlayerInfo(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID //(UINT64)用户ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取玩家背包信息
	function send_GetPlayerBagInfo(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID //(UINT64)用户ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：删除物品
	function send_DelItem(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID,  //(UINT64)用户ID
		$byType,  //(UINT8)1；背包，2：仓库
		$qwInstID,  //(UINT64)物品唯一ID
		$wCount //(UINT16)堆叠数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT8($data, $byType);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取活动列表信息
	function send_GetActList(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 6);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：开启指定活动
	function send_OpenAct(
		$eType,  //(枚举类型：EActivityType)活动ID
		$dwBegin,  //(UINT32)活动开启时间
		$dwEnd //(UINT32)活动结束时间
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eType);
		ByteUtil::writeUINT32($data, $dwBegin);
		ByteUtil::writeUINT32($data, $dwEnd);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：封号/解封
	function send_LockOrUnlockUser(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID,  //(UINT64)用户ID
		$eOptType,  //(枚举类型：EOptType)后台操作类型(eOptLockUser/eOptUnlockUser)
		$dwEndTime,  //(UINT32)时间
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeINT8($data, $eOptType);
		ByteUtil::writeUINT32($data, $dwEndTime);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：禁言/解禁
	function send_LockOrUnlockSpeak(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID,  //(UINT64)用户ID
		$eOptType,  //(枚举类型：EOptType)后台操作类型(eOptLockSpeak/eOptUnlockSpeak)
		$dwEndTime,  //(UINT32)时间
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeINT8($data, $eOptType);
		ByteUtil::writeUINT32($data, $dwEndTime);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取在线人数
	function send_GetOnlineNum(
		$wServerNo //(UINT16)区服ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 10);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发放物品/货币
	function send_SendItem(
		$wServerNo,  //(UINT16)区服ID
		$strUserID,  //(string)格式：用户AID|户BID|..
		$strName,  //(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		$strItem,  //(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		$strTitle,  //(string)邮件标题
		$strContent,  //(string)邮件内容
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 11);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 11;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strUserID);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeString($data, $strItem);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：减少货币数量
	function send_SubMoney(
		$wServerNo,  //(UINT16)区服ID
		$strUserID,  //(string)格式：用户AID|户BID|..
		$strName,  //(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		$strItem //(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 12);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 12;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strUserID);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeString($data, $strItem);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发放VIP物品
	function send_SendVIPItem(
		$wServerNo,  //(UINT16)区服ID
		$byVIPMinLevel,  //(UINT8)VIP最小等级
		$byVIPMaxLevel,  //(UINT8)VIP最大等级
		$strItem,  //(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		$strTitle,  //(string)邮件标题
		$strContent,  //(string)邮件内容
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 13);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 13;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT8($data, $byVIPMinLevel);
		ByteUtil::writeUINT8($data, $byVIPMaxLevel);
		ByteUtil::writeString($data, $strItem);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发放帮派物品
	function send_SendClanItem(
		$wServerNo,  //(UINT16)区服ID
		$qwClanID,  //(UINT64)帮派ID
		$eTarget,  //(枚举类型：ESendTarget)对象
		$strItem,  //(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		$strTitle,  //(string)邮件标题
		$strContent,  //(string)邮件内容
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 14);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 14;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwClanID);
		ByteUtil::writeUINT8($data, $eTarget);
		ByteUtil::writeString($data, $strItem);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：全区发放物品
	function send_GlobalSendItem(
		$wServerNo,  //(UINT16)区服ID
		$eTarget,  //(枚举类型：ESendTarget)对象
		$strItem,  //(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		$strTitle,  //(string)邮件标题
		$strContent,  //(string)邮件内容
		$strArgument //(string)理由
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 15);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 15;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT8($data, $eTarget);
		ByteUtil::writeString($data, $strItem);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		ByteUtil::writeString($data, $strArgument);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发送邮件
	function send_SendMail(
		$wServerNo,  //(UINT16)区服ID
		$strUserID,  //(string)格式：用户AID|户BID|..
		$strName,  //(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		$strTitle,  //(string)邮件标题
		$strContent //(string)邮件内容
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 16);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 16;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strUserID);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：全区发送邮件
	function send_GlobalSendMail(
		$wServerNo,  //(UINT16)区服ID
		$eTarget,  //(枚举类型：ESendTarget)对象
		$strTitle,  //(string)邮件标题
		$strContent //(string)邮件内容
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 17);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 17;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT8($data, $eTarget);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strContent);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发送公告
	function send_GlobalSendNotice(
		$wServerNo,  //(UINT16)区服ID
		$strContent,  //(string)系统弹窗内容
		$ePlatformType,  //(枚举类型：EPlatformType)平台类型
		$eShowType,  //(枚举类型：EShowType)显示区域
		$eRollType,  //(枚举类型：ERollType)是否滚动
		$eSendType,  //(枚举类型：ESendType)是否立即发送
		$dwBeginTime,  //(UINT32)公告开始时间(注：如果选择立即发送，dwBeginTime为0)
		$dwEndTime //(UINT32)公告结束时间(注：如果选择立即发送，dwEndTime为0)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 18);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 18;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strContent);
		ByteUtil::writeUINT8($data, $ePlatformType);
		ByteUtil::writeUINT8($data, $eShowType);
		ByteUtil::writeUINT8($data, $eRollType);
		ByteUtil::writeUINT8($data, $eSendType);
		ByteUtil::writeUINT32($data, $dwBeginTime);
		ByteUtil::writeUINT32($data, $dwEndTime);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：删除公告
	function send_GlobalDelNotice(
		$wServerNo,  //(UINT16)区服ID
		$dwNoticeID //(UINT32)公告ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 19);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 19;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT32($data, $dwNoticeID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发送系统弹窗
	function send_GlobalSendSysDialog(
		$wServerNo,  //(UINT16)区服ID
		$ePlatformType,  //(枚举类型：EPlatformType)平台类型
		$eDialogType //(枚举类型：EDialogType)弹窗类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 20);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 20;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT8($data, $ePlatformType);
		ByteUtil::writeUINT8($data, $eDialogType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：开启商城限购活动
	function send_OpenDiscountActivity(
		$wServerNo,  //(UINT16)区服ID
		$byPos,  //(UINT8)限购位置(0,1,2表示)
		$byOptType,  //(UINT8)操作类型(0：增加；1：删除)
		$strDisItems,  //(string)限购道具信息(itemID,原价,折扣价|...)
		$byLimitType,  //(UINT8)类型限制(0无条件、1充值限购、2消费限购)
		$dwLimitValue,  //(UINT32)达到的仙石数量限制(0无条件、1充值限购、2消费限购)
		$wLimitCount,  //(UINT16)购买道具个数限制
		$dwBeginTime,  //(UINT32)限购开始时间
		$dwEndTime //(UINT32)限购结束时间
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 21);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 21;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT8($data, $byPos);
		ByteUtil::writeUINT8($data, $byOptType);
		ByteUtil::writeString($data, $strDisItems);
		ByteUtil::writeUINT8($data, $byLimitType);
		ByteUtil::writeUINT32($data, $dwLimitValue);
		ByteUtil::writeUINT16($data, $wLimitCount);
		ByteUtil::writeUINT32($data, $dwBeginTime);
		ByteUtil::writeUINT32($data, $dwEndTime);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置玩家等级
	function send_SetPlayerLevel(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID,  //(UINT64)用户ID
		$wLevel //(UINT16)等级
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 22);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 22;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT16($data, $wLevel);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置玩家VIP等级
	function send_SetPlayerVIPLevel(
		$wServerNo,  //(UINT16)区服ID
		$strName,  //(string)角色名称
		$qwUserID,  //(UINT64)用户ID
		$eOptType,  //(枚举类型：EOptType)后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		$wLevelOrGrowthValue //(UINT32)等级or成长值
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 23);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 23;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeINT8($data, $eOptType);
		ByteUtil::writeUINT32($data, $wLevelOrGrowthValue);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：日常任务管理
	function send_TaskManager(
		$wServerNo,  //(UINT16)区服ID
		$strUserID,  //(string)格式：用户AID|户BID|..
		$strName,  //(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		$ePHPTaskType //(枚举类型：EPHPTaskType)任务类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 24);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 24;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeString($data, $strUserID);
		ByteUtil::writeString($data, $strName);
		ByteUtil::writeUINT8($data, $ePHPTaskType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：平台信息
	function send_PlatformInfo(
		$byPtType,  //(枚举类型：EPlatformType)平台类型
		$byQQPtType,  //(枚举类型：EQQPlatformType)QQ平台类型
		$byQQPtLv,  //(UINT8)QQ平台类型等级
		$byQQPtYearType,  //(UINT8)是否年费
		$byQQPtLuxuryType,  //(UINT8)是否豪华
		$customPar1,  //(string)广告主来源
		$customPar2,  //(string)广告次来源
		$strOpenId,  //(string)openID
		$strOpenKey //(string)openKey
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 25;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT8($data, $byPtType);
		ByteUtil::writeUINT8($data, $byQQPtType);
		ByteUtil::writeUINT8($data, $byQQPtLv);
		ByteUtil::writeUINT8($data, $byQQPtYearType);
		ByteUtil::writeUINT8($data, $byQQPtLuxuryType);
		ByteUtil::writeString($data, $customPar1);
		ByteUtil::writeString($data, $customPar2);
		ByteUtil::writeString($data, $strOpenId);
		ByteUtil::writeString($data, $strOpenKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：任务集市中任务状态查询
	function send_GetTaskState(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID,  //(UINT64)玩家ID
		$dwTaskID,  //(UINT32)任务ID
		$byStep,  //(UINT8)步骤ID
		$eTaskOpt //(枚举类型：ETaskOpt)任务操作
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 25);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 26;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT32($data, $dwTaskID);
		ByteUtil::writeUINT8($data, $byStep);
		ByteUtil::writeUINT8($data, $eTaskOpt);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：同步微信微博人数
	function send_SynWeiweiPersonNum(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID,  //(UINT64)玩家ID
		$byType,  //(UINT8)任务ID
		$dwCount //(UINT32)步骤ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 26);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 27;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT8($data, $byType);
		ByteUtil::writeUINT32($data, $dwCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：检测CDK
	function send_CheckCDK(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID,  //(UINT64)玩家ID
		$strCDK //(string)CDK码
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 27);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 28;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeString($data, $strCDK);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：QQAlarm安装
	function send_SynQQAlarm(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID //(UINT64)玩家ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 28);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 29;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：天赐宝箱活动参数修改
	function send_ModifyChest(
		$sInfo //(类类型：SChestInfo)数据
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 29);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 30;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		$sInfo->toStream($data);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置汇灵盏奖励池
	function send_SetPool(
		$byType,  //(UINT8)类型，0表示设置奖励池最大值，1表示设置奖励池现有值
		$dwValue //(UINT32)数据
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 30);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 31;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byType);
		ByteUtil::writeUINT32($data, $dwValue);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求玩家累计登入天数
	function send_GetLoginDays(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID //(UINT64)玩家ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 31);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 32;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：发送工会聊天信息
	function send_SendQQGroupMsg(
		$qwGroupUserID,  //(UINT64)绑定qq的玩家ID
		$wServerNo,  //(UINT16)聊天玩家区号ID
		$qwUserID,  //(UINT64)聊天玩家账号ID
		$strChatMsg //(string)聊天
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 32);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 33;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwGroupUserID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeString($data, $strChatMsg);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：添加称号
	function send_SendTitle(
		$wServerNo,  //(UINT16)区服ID
		$qwUserID,  //(UINT64)玩家ID
		$wTitleID //(UINT16)TitleID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 33);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 34;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wServerNo);
		ByteUtil::writeUINT64($data, $qwUserID);
		ByteUtil::writeUINT16($data, $wTitleID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：Test
	function send_TestPHP(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 35;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：玩家充值仙石
	abstract function onReturn_OnUserRecharge(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_OnUserRecharge)返回的参数
	);

	//返回：修改玩家各种活动积分信息
	abstract function onReturn_ModifyActivityIntegral(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ModifyActivityIntegral)返回的参数
	);

	//返回：获取玩家信息
	abstract function onReturn_GetPlayerInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetPlayerInfo)返回的参数
	);

	//返回：获取玩家背包信息
	abstract function onReturn_GetPlayerBagInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetPlayerBagInfo)返回的参数
	);

	//返回：删除物品
	abstract function onReturn_DelItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_DelItem)返回的参数
	);

	//返回：获取活动列表信息
	abstract function onReturn_GetActList(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetActList)返回的参数
	);

	//返回：开启指定活动
	abstract function onReturn_OpenAct(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_OpenAct)返回的参数
	);

	//返回：封号/解封
	abstract function onReturn_LockOrUnlockUser(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_LockOrUnlockUser)返回的参数
	);

	//返回：禁言/解禁
	abstract function onReturn_LockOrUnlockSpeak(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_LockOrUnlockSpeak)返回的参数
	);

	//返回：获取在线人数
	abstract function onReturn_GetOnlineNum(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetOnlineNum)返回的参数
	);

	//返回：发放物品/货币
	abstract function onReturn_SendItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendItem)返回的参数
	);

	//返回：减少货币数量
	abstract function onReturn_SubMoney(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SubMoney)返回的参数
	);

	//返回：发放VIP物品
	abstract function onReturn_SendVIPItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendVIPItem)返回的参数
	);

	//返回：发放帮派物品
	abstract function onReturn_SendClanItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendClanItem)返回的参数
	);

	//返回：全区发放物品
	abstract function onReturn_GlobalSendItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GlobalSendItem)返回的参数
	);

	//返回：发送邮件
	abstract function onReturn_SendMail(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendMail)返回的参数
	);

	//返回：全区发送邮件
	abstract function onReturn_GlobalSendMail(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GlobalSendMail)返回的参数
	);

	//返回：发送公告
	abstract function onReturn_GlobalSendNotice(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GlobalSendNotice)返回的参数
	);

	//返回：删除公告
	abstract function onReturn_GlobalDelNotice(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GlobalDelNotice)返回的参数
	);

	//返回：发送系统弹窗
	abstract function onReturn_GlobalSendSysDialog(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GlobalSendSysDialog)返回的参数
	);

	//返回：开启商城限购活动
	abstract function onReturn_OpenDiscountActivity(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_OpenDiscountActivity)返回的参数
	);

	//返回：设置玩家等级
	abstract function onReturn_SetPlayerLevel(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SetPlayerLevel)返回的参数
	);

	//返回：设置玩家VIP等级
	abstract function onReturn_SetPlayerVIPLevel(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SetPlayerVIPLevel)返回的参数
	);

	//返回：日常任务管理
	abstract function onReturn_TaskManager(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TaskManager)返回的参数
	);

	//返回：任务集市中任务状态查询
	abstract function onReturn_GetTaskState(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTaskState)返回的参数
	);

	//返回：同步微信微博人数
	abstract function onReturn_SynWeiweiPersonNum(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SynWeiweiPersonNum)返回的参数
	);

	//返回：检测CDK
	abstract function onReturn_CheckCDK(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_CheckCDK)返回的参数
	);

	//返回：QQAlarm安装
	abstract function onReturn_SynQQAlarm(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SynQQAlarm)返回的参数
	);

	//返回：天赐宝箱活动参数修改
	abstract function onReturn_ModifyChest(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ModifyChest)返回的参数
	);

	//返回：设置汇灵盏奖励池
	abstract function onReturn_SetPool(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SetPool)返回的参数
	);

	//返回：请求玩家累计登入天数
	abstract function onReturn_GetLoginDays(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetLoginDays)返回的参数
	);

	//返回：发送工会聊天信息
	abstract function onReturn_SendQQGroupMsg(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendQQGroupMsg)返回的参数
	);

	//返回：添加称号
	abstract function onReturn_SendTitle(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SendTitle)返回的参数
	);

	//返回处理：玩家充值仙石
	private function _doReturn_OnUserRecharge($data)
	{
		$retParam = new SRetParam_OnUserRecharge;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$byRet = ByteUtil::readUINT8($data); //(无符号8位整数)充值返回值(值为0:成功 非0其他错误)
		$strError = ByteUtil::readString($data); //错误码字符串(若成功为空)
		$retParam->byRet = $byRet;
		$retParam->strError = $strError;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_OnUserRecharge($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：玩家充值仙石
	private function _onTimeOut_OnUserRecharge($sessionID)
	{
		$retParam = new SRetParam_OnUserRecharge;
		$this->onReturn_OnUserRecharge(2, $retParam);
	}

	//返回处理：修改玩家各种活动积分信息
	private function _doReturn_ModifyActivityIntegral($data)
	{
		$retParam = new SRetParam_ModifyActivityIntegral;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ModifyActivityIntegral($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：修改玩家各种活动积分信息
	private function _onTimeOut_ModifyActivityIntegral($sessionID)
	{
		$retParam = new SRetParam_ModifyActivityIntegral;
		$this->onReturn_ModifyActivityIntegral(2, $retParam);
	}

	//返回处理：获取玩家信息
	private function _doReturn_GetPlayerInfo($data)
	{
		$retParam = new SRetParam_GetPlayerInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecPlayerInfo = SPlayerInfo::vectorFromStream($data); //玩家信息
		$retParam->vecPlayerInfo = $vecPlayerInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetPlayerInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取玩家信息
	private function _onTimeOut_GetPlayerInfo($sessionID)
	{
		$retParam = new SRetParam_GetPlayerInfo;
		$this->onReturn_GetPlayerInfo(2, $retParam);
	}

	//返回处理：获取玩家背包信息
	private function _doReturn_GetPlayerBagInfo($data)
	{
		$retParam = new SRetParam_GetPlayerBagInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecPlayerBagInfo = SPlayerBagInfo::vectorFromStream($data); //玩家背包信息
		$retParam->vecPlayerBagInfo = $vecPlayerBagInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetPlayerBagInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取玩家背包信息
	private function _onTimeOut_GetPlayerBagInfo($sessionID)
	{
		$retParam = new SRetParam_GetPlayerBagInfo;
		$this->onReturn_GetPlayerBagInfo(2, $retParam);
	}

	//返回处理：删除物品
	private function _doReturn_DelItem($data)
	{
		$retParam = new SRetParam_DelItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_DelItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：删除物品
	private function _onTimeOut_DelItem($sessionID)
	{
		$retParam = new SRetParam_DelItem;
		$this->onReturn_DelItem(2, $retParam);
	}

	//返回处理：获取活动列表信息
	private function _doReturn_GetActList($data)
	{
		$retParam = new SRetParam_GetActList;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecIDs = ByteUtil::readVecUINT16($data); //(无符号16位整数)活动列表
		$retParam->vecIDs = $vecIDs;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetActList($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取活动列表信息
	private function _onTimeOut_GetActList($sessionID)
	{
		$retParam = new SRetParam_GetActList;
		$this->onReturn_GetActList(2, $retParam);
	}

	//返回处理：开启指定活动
	private function _doReturn_OpenAct($data)
	{
		$retParam = new SRetParam_OpenAct;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_OpenAct($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：开启指定活动
	private function _onTimeOut_OpenAct($sessionID)
	{
		$retParam = new SRetParam_OpenAct;
		$this->onReturn_OpenAct(2, $retParam);
	}

	//返回处理：封号/解封
	private function _doReturn_LockOrUnlockUser($data)
	{
		$retParam = new SRetParam_LockOrUnlockUser;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_LockOrUnlockUser($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：封号/解封
	private function _onTimeOut_LockOrUnlockUser($sessionID)
	{
		$retParam = new SRetParam_LockOrUnlockUser;
		$this->onReturn_LockOrUnlockUser(2, $retParam);
	}

	//返回处理：禁言/解禁
	private function _doReturn_LockOrUnlockSpeak($data)
	{
		$retParam = new SRetParam_LockOrUnlockSpeak;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_LockOrUnlockSpeak($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：禁言/解禁
	private function _onTimeOut_LockOrUnlockSpeak($sessionID)
	{
		$retParam = new SRetParam_LockOrUnlockSpeak;
		$this->onReturn_LockOrUnlockSpeak(2, $retParam);
	}

	//返回处理：获取在线人数
	private function _doReturn_GetOnlineNum($data)
	{
		$retParam = new SRetParam_GetOnlineNum;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwOnlineNum = ByteUtil::readUINT32($data); //(无符号32位整数)在线人数
		$retParam->dwOnlineNum = $dwOnlineNum;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetOnlineNum($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取在线人数
	private function _onTimeOut_GetOnlineNum($sessionID)
	{
		$retParam = new SRetParam_GetOnlineNum;
		$this->onReturn_GetOnlineNum(2, $retParam);
	}

	//返回处理：发放物品/货币
	private function _doReturn_SendItem($data)
	{
		$retParam = new SRetParam_SendItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发放物品/货币
	private function _onTimeOut_SendItem($sessionID)
	{
		$retParam = new SRetParam_SendItem;
		$this->onReturn_SendItem(2, $retParam);
	}

	//返回处理：减少货币数量
	private function _doReturn_SubMoney($data)
	{
		$retParam = new SRetParam_SubMoney;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SubMoney($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：减少货币数量
	private function _onTimeOut_SubMoney($sessionID)
	{
		$retParam = new SRetParam_SubMoney;
		$this->onReturn_SubMoney(2, $retParam);
	}

	//返回处理：发放VIP物品
	private function _doReturn_SendVIPItem($data)
	{
		$retParam = new SRetParam_SendVIPItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendVIPItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发放VIP物品
	private function _onTimeOut_SendVIPItem($sessionID)
	{
		$retParam = new SRetParam_SendVIPItem;
		$this->onReturn_SendVIPItem(2, $retParam);
	}

	//返回处理：发放帮派物品
	private function _doReturn_SendClanItem($data)
	{
		$retParam = new SRetParam_SendClanItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendClanItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发放帮派物品
	private function _onTimeOut_SendClanItem($sessionID)
	{
		$retParam = new SRetParam_SendClanItem;
		$this->onReturn_SendClanItem(2, $retParam);
	}

	//返回处理：全区发放物品
	private function _doReturn_GlobalSendItem($data)
	{
		$retParam = new SRetParam_GlobalSendItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GlobalSendItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：全区发放物品
	private function _onTimeOut_GlobalSendItem($sessionID)
	{
		$retParam = new SRetParam_GlobalSendItem;
		$this->onReturn_GlobalSendItem(2, $retParam);
	}

	//返回处理：发送邮件
	private function _doReturn_SendMail($data)
	{
		$retParam = new SRetParam_SendMail;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendMail($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发送邮件
	private function _onTimeOut_SendMail($sessionID)
	{
		$retParam = new SRetParam_SendMail;
		$this->onReturn_SendMail(2, $retParam);
	}

	//返回处理：全区发送邮件
	private function _doReturn_GlobalSendMail($data)
	{
		$retParam = new SRetParam_GlobalSendMail;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GlobalSendMail($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：全区发送邮件
	private function _onTimeOut_GlobalSendMail($sessionID)
	{
		$retParam = new SRetParam_GlobalSendMail;
		$this->onReturn_GlobalSendMail(2, $retParam);
	}

	//返回处理：发送公告
	private function _doReturn_GlobalSendNotice($data)
	{
		$retParam = new SRetParam_GlobalSendNotice;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwNoticeID = ByteUtil::readUINT32($data); //(无符号32位整数)返回公告ID
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->dwNoticeID = $dwNoticeID;
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GlobalSendNotice($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发送公告
	private function _onTimeOut_GlobalSendNotice($sessionID)
	{
		$retParam = new SRetParam_GlobalSendNotice;
		$this->onReturn_GlobalSendNotice(2, $retParam);
	}

	//返回处理：删除公告
	private function _doReturn_GlobalDelNotice($data)
	{
		$retParam = new SRetParam_GlobalDelNotice;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GlobalDelNotice($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：删除公告
	private function _onTimeOut_GlobalDelNotice($sessionID)
	{
		$retParam = new SRetParam_GlobalDelNotice;
		$this->onReturn_GlobalDelNotice(2, $retParam);
	}

	//返回处理：发送系统弹窗
	private function _doReturn_GlobalSendSysDialog($data)
	{
		$retParam = new SRetParam_GlobalSendSysDialog;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GlobalSendSysDialog($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发送系统弹窗
	private function _onTimeOut_GlobalSendSysDialog($sessionID)
	{
		$retParam = new SRetParam_GlobalSendSysDialog;
		$this->onReturn_GlobalSendSysDialog(2, $retParam);
	}

	//返回处理：开启商城限购活动
	private function _doReturn_OpenDiscountActivity($data)
	{
		$retParam = new SRetParam_OpenDiscountActivity;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_OpenDiscountActivity($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：开启商城限购活动
	private function _onTimeOut_OpenDiscountActivity($sessionID)
	{
		$retParam = new SRetParam_OpenDiscountActivity;
		$this->onReturn_OpenDiscountActivity(2, $retParam);
	}

	//返回处理：设置玩家等级
	private function _doReturn_SetPlayerLevel($data)
	{
		$retParam = new SRetParam_SetPlayerLevel;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SetPlayerLevel($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置玩家等级
	private function _onTimeOut_SetPlayerLevel($sessionID)
	{
		$retParam = new SRetParam_SetPlayerLevel;
		$this->onReturn_SetPlayerLevel(2, $retParam);
	}

	//返回处理：设置玩家VIP等级
	private function _doReturn_SetPlayerVIPLevel($data)
	{
		$retParam = new SRetParam_SetPlayerVIPLevel;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SetPlayerVIPLevel($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置玩家VIP等级
	private function _onTimeOut_SetPlayerVIPLevel($sessionID)
	{
		$retParam = new SRetParam_SetPlayerVIPLevel;
		$this->onReturn_SetPlayerVIPLevel(2, $retParam);
	}

	//返回处理：日常任务管理
	private function _doReturn_TaskManager($data)
	{
		$retParam = new SRetParam_TaskManager;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TaskManager($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：日常任务管理
	private function _onTimeOut_TaskManager($sessionID)
	{
		$retParam = new SRetParam_TaskManager;
		$this->onReturn_TaskManager(2, $retParam);
	}

	//返回处理：任务集市中任务状态查询
	private function _doReturn_GetTaskState($data)
	{
		$retParam = new SRetParam_GetTaskState;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wServerNo = ByteUtil::readUINT16($data); //(无符号16位整数)区服ID
		$eTaskState = ByteUtil::readUINT8($data); //(枚举类型：ETaskState)状态返回
		$retParam->wServerNo = $wServerNo;
		$retParam->eTaskState = $eTaskState;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTaskState($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：任务集市中任务状态查询
	private function _onTimeOut_GetTaskState($sessionID)
	{
		$retParam = new SRetParam_GetTaskState;
		$this->onReturn_GetTaskState(2, $retParam);
	}

	//返回处理：同步微信微博人数
	private function _doReturn_SynWeiweiPersonNum($data)
	{
		$retParam = new SRetParam_SynWeiweiPersonNum;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SynWeiweiPersonNum($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：同步微信微博人数
	private function _onTimeOut_SynWeiweiPersonNum($sessionID)
	{
		$retParam = new SRetParam_SynWeiweiPersonNum;
		$this->onReturn_SynWeiweiPersonNum(2, $retParam);
	}

	//返回处理：检测CDK
	private function _doReturn_CheckCDK($data)
	{
		$retParam = new SRetParam_CheckCDK;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_CheckCDK($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：检测CDK
	private function _onTimeOut_CheckCDK($sessionID)
	{
		$retParam = new SRetParam_CheckCDK;
		$this->onReturn_CheckCDK(2, $retParam);
	}

	//返回处理：QQAlarm安装
	private function _doReturn_SynQQAlarm($data)
	{
		$retParam = new SRetParam_SynQQAlarm;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SynQQAlarm($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：QQAlarm安装
	private function _onTimeOut_SynQQAlarm($sessionID)
	{
		$retParam = new SRetParam_SynQQAlarm;
		$this->onReturn_SynQQAlarm(2, $retParam);
	}

	//返回处理：天赐宝箱活动参数修改
	private function _doReturn_ModifyChest($data)
	{
		$retParam = new SRetParam_ModifyChest;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ModifyChest($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：天赐宝箱活动参数修改
	private function _onTimeOut_ModifyChest($sessionID)
	{
		$retParam = new SRetParam_ModifyChest;
		$this->onReturn_ModifyChest(2, $retParam);
	}

	//返回处理：设置汇灵盏奖励池
	private function _doReturn_SetPool($data)
	{
		$retParam = new SRetParam_SetPool;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SetPool($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置汇灵盏奖励池
	private function _onTimeOut_SetPool($sessionID)
	{
		$retParam = new SRetParam_SetPool;
		$this->onReturn_SetPool(2, $retParam);
	}

	//返回处理：请求玩家累计登入天数
	private function _doReturn_GetLoginDays($data)
	{
		$retParam = new SRetParam_GetLoginDays;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwDays = ByteUtil::readUINT32($data); //(无符号32位整数)累计登入天数
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->dwDays = $dwDays;
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetLoginDays($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求玩家累计登入天数
	private function _onTimeOut_GetLoginDays($sessionID)
	{
		$retParam = new SRetParam_GetLoginDays;
		$this->onReturn_GetLoginDays(2, $retParam);
	}

	//返回处理：发送工会聊天信息
	private function _doReturn_SendQQGroupMsg($data)
	{
		$retParam = new SRetParam_SendQQGroupMsg;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendQQGroupMsg($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：发送工会聊天信息
	private function _onTimeOut_SendQQGroupMsg($sessionID)
	{
		$retParam = new SRetParam_SendQQGroupMsg;
		$this->onReturn_SendQQGroupMsg(2, $retParam);
	}

	//返回处理：添加称号
	private function _doReturn_SendTitle($data)
	{
		$retParam = new SRetParam_SendTitle;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOptResult = ByteUtil::readINT8($data); //(枚举类型：EOptResult)后台操作结果
		$retParam->eOptResult = $eOptResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SendTitle($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：添加称号
	private function _onTimeOut_SendTitle($sessionID)
	{
		$retParam = new SRetParam_SendTitle;
		$this->onReturn_SendTitle(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 90;

		$this->_retFuncList[0] = '_doReturn_OnUserRecharge'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_ModifyActivityIntegral'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GetPlayerInfo'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_GetPlayerBagInfo'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_DelItem'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_GetActList'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_OpenAct'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_LockOrUnlockUser'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_LockOrUnlockSpeak'; //FuncID: 9
		$this->_retFuncList[9] = '_doReturn_GetOnlineNum'; //FuncID: 10
		$this->_retFuncList[10] = '_doReturn_SendItem'; //FuncID: 11
		$this->_retFuncList[11] = '_doReturn_SubMoney'; //FuncID: 12
		$this->_retFuncList[12] = '_doReturn_SendVIPItem'; //FuncID: 13
		$this->_retFuncList[13] = '_doReturn_SendClanItem'; //FuncID: 14
		$this->_retFuncList[14] = '_doReturn_GlobalSendItem'; //FuncID: 15
		$this->_retFuncList[15] = '_doReturn_SendMail'; //FuncID: 16
		$this->_retFuncList[16] = '_doReturn_GlobalSendMail'; //FuncID: 17
		$this->_retFuncList[17] = '_doReturn_GlobalSendNotice'; //FuncID: 18
		$this->_retFuncList[18] = '_doReturn_GlobalDelNotice'; //FuncID: 19
		$this->_retFuncList[19] = '_doReturn_GlobalSendSysDialog'; //FuncID: 20
		$this->_retFuncList[20] = '_doReturn_OpenDiscountActivity'; //FuncID: 21
		$this->_retFuncList[21] = '_doReturn_SetPlayerLevel'; //FuncID: 22
		$this->_retFuncList[22] = '_doReturn_SetPlayerVIPLevel'; //FuncID: 23
		$this->_retFuncList[23] = '_doReturn_TaskManager'; //FuncID: 24
		$this->_retFuncList[24] = '_doReturn_GetTaskState'; //FuncID: 25
		$this->_retFuncList[25] = '_doReturn_SynWeiweiPersonNum'; //FuncID: 26
		$this->_retFuncList[26] = '_doReturn_CheckCDK'; //FuncID: 27
		$this->_retFuncList[27] = '_doReturn_SynQQAlarm'; //FuncID: 28
		$this->_retFuncList[28] = '_doReturn_ModifyChest'; //FuncID: 29
		$this->_retFuncList[29] = '_doReturn_SetPool'; //FuncID: 30
		$this->_retFuncList[30] = '_doReturn_GetLoginDays'; //FuncID: 31
		$this->_retFuncList[31] = '_doReturn_SendQQGroupMsg'; //FuncID: 32
		$this->_retFuncList[32] = '_doReturn_SendTitle'; //FuncID: 33

		$this->_timeFuncList[0] = '_onTimeOut_OnUserRecharge'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_ModifyActivityIntegral'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GetPlayerInfo'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_GetPlayerBagInfo'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_DelItem'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_GetActList'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_OpenAct'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_LockOrUnlockUser'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_LockOrUnlockSpeak'; //FuncID: 9
		$this->_timeFuncList[9] = '_onTimeOut_GetOnlineNum'; //FuncID: 10
		$this->_timeFuncList[10] = '_onTimeOut_SendItem'; //FuncID: 11
		$this->_timeFuncList[11] = '_onTimeOut_SubMoney'; //FuncID: 12
		$this->_timeFuncList[12] = '_onTimeOut_SendVIPItem'; //FuncID: 13
		$this->_timeFuncList[13] = '_onTimeOut_SendClanItem'; //FuncID: 14
		$this->_timeFuncList[14] = '_onTimeOut_GlobalSendItem'; //FuncID: 15
		$this->_timeFuncList[15] = '_onTimeOut_SendMail'; //FuncID: 16
		$this->_timeFuncList[16] = '_onTimeOut_GlobalSendMail'; //FuncID: 17
		$this->_timeFuncList[17] = '_onTimeOut_GlobalSendNotice'; //FuncID: 18
		$this->_timeFuncList[18] = '_onTimeOut_GlobalDelNotice'; //FuncID: 19
		$this->_timeFuncList[19] = '_onTimeOut_GlobalSendSysDialog'; //FuncID: 20
		$this->_timeFuncList[20] = '_onTimeOut_OpenDiscountActivity'; //FuncID: 21
		$this->_timeFuncList[21] = '_onTimeOut_SetPlayerLevel'; //FuncID: 22
		$this->_timeFuncList[22] = '_onTimeOut_SetPlayerVIPLevel'; //FuncID: 23
		$this->_timeFuncList[23] = '_onTimeOut_TaskManager'; //FuncID: 24
		$this->_timeFuncList[24] = '_onTimeOut_GetTaskState'; //FuncID: 25
		$this->_timeFuncList[25] = '_onTimeOut_SynWeiweiPersonNum'; //FuncID: 26
		$this->_timeFuncList[26] = '_onTimeOut_CheckCDK'; //FuncID: 27
		$this->_timeFuncList[27] = '_onTimeOut_SynQQAlarm'; //FuncID: 28
		$this->_timeFuncList[28] = '_onTimeOut_ModifyChest'; //FuncID: 29
		$this->_timeFuncList[29] = '_onTimeOut_SetPool'; //FuncID: 30
		$this->_timeFuncList[30] = '_onTimeOut_GetLoginDays'; //FuncID: 31
		$this->_timeFuncList[31] = '_onTimeOut_SendQQGroupMsg'; //FuncID: 32
		$this->_timeFuncList[32] = '_onTimeOut_SendTitle'; //FuncID: 33
	}

	function handleMessage($data)
	{
		$funcID = ByteUtil::readINT8($data);
		if($funcID == 0
			 || $funcID < -count($this->_retFuncList))
			return false;
		if($funcID > 0)
			$func = $this->_recvFuncList[$funcID - 1];
		else
			$func = $this->_retFuncList[-$funcID - 1];
		if($func != null)
			return call_user_func(array($this, $func), $data);
		return false;
	}

	function onTimeOut($funcID, $sessionID)
	{
		if($funcID == 0 || $funcID > count($this->_timeFuncList))
			return;
		$this->_timeFuncList[$funcID - 1]($sessionID);
	}
}

?>