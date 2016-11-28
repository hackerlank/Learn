<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    WonderActivityProt.php
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class EWActResult
{
	const eWActResult_none = 0; //无此活动
	const eWActResult_success = 1; //操作成功
	const eWActResult_error = 2; //操作失败
}

//领奖操作结果
class EGainResult
{
	const eGainResult_none = 0; //无此奖励
	const eGainResult_success = 1; //领奖成功
	const eGainResult_alreadyGain = 2; //奖励已领
	const eGainResult_fullBag = 3; //背包满
	const eGainResult_notGet = 4; //条件未达到
	const eGainResult_error = 5; //操作失败
}

//活动类型
class EWActType
{
	const eWActType_NONE = 0; //无活动
	const eWActType_RANKPOINT = 702; //战力排行榜
	const eWActType_LEVELACT = 703; //全服等级奖励
	const eWActType_HORSEACT = 704; //坐骑收集奖励
	const eWActType_DUNGON = 705; //全服副本奖励
	const eWActType_FIGHTER = 706; //全服散仙奖励
	const eWActType_FORMATION = 707; //全服阵灵奖励
	const eWActType_TRUMP = 708; //全服法宝奖励
	const eWActType_RANKLEVEL = 709; //等级排行榜
	const eWActType_RANKPET = 710; //阵灵排行榜
	const eWActType_RANKFIGHTER = 711; //散仙排行榜
	const eWActType_RANKARENA = 712; //斗剑排行榜
	const eWActType_RANKGUILD = 713; //帮派排行榜
	const eWActType_RANKTRUMP = 717; //法宝排行榜
	const eWActType_QQCOIN = 715; //Q养成活动
	const eWActType_BEAUTYACT = 716; //美女奖励
	const eWActType_POINT = 718; //战力奖励
	const eWActType_OpenBuy = 719; //开服购买礼包
	const eWActType_MAX = 720; //活动最大值
}

//活动状态
class EWActState
{
	const eWActState_Init = 0; //初始状态
	const eWActState_Advance = 1; //活动预告
	const eWActState_Begin = 2; //活动开始
	const eWActState_End = 3; //活动结束
	const eWActState_Retain = 4; //活动保留时间
}

//活动奖励类型
class EWActPrizeType
{
	const eWActPrizeType_default = 0; //全部奖励
	const eWActPrizeType_first = 1; //第一名玩家奖励
	const eWActPrizeType_one = 2; //一等奖
	const eWActPrizeType_two = 3; //二等奖
	const eWActPrizeType_three = 4; //三等奖
	const eWActPrizeType_MAX = 5; //奖励最大值
}

//奖励道具信息
final class SItemConfig
{
	public $dwItemID; //(UINT32)道具ID
	public $dwCount; //(UINT32)道具数量

	//构造函数
	function __construct()
	{
		$this->dwItemID = 0;
		$this->dwCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwItemID = $this->dwItemID;
		$obj->dwCount = $this->dwCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SItemConfig;
		$s->dwItemID = ByteUtil::readUINT32($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItemConfig::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwItemID);
		ByteUtil::writeUINT32($data, $this->dwCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//奖励道具信息
final class SPrizeConfig
{
	public $ePrizeType; //(枚举类型：EWActPrizeType)奖励类型
	public $vecItems; //(SItemConfig的数组)道具

	//构造函数
	function __construct()
	{
		$this->ePrizeType = 0;
		$this->vecItems = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->ePrizeType = $this->ePrizeType;
		$obj->vecItems = $this->vecItems;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPrizeConfig;
		$s->ePrizeType = ByteUtil::readUINT8($data);
		$s->vecItems = SItemConfig::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPrizeConfig::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->ePrizeType);
		SItemConfig::vectorToStream($data, $this->vecItems);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//活动具体配置信息
final class SWActConfig
{
	public $wWActID; //(UINT16)活动ID
	public $wCfgID; //(UINT16)活动配置ID
	public $eWactPrizeType; //(枚举类型：EWActPrizeType)奖励类型
	public $vecItemConfig; //(SItemConfig的数组)奖励道具列表

	//构造函数
	function __construct()
	{
		$this->wWActID = 0;
		$this->wCfgID = 0;
		$this->eWactPrizeType = 0;
		$this->vecItemConfig = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wWActID = $this->wWActID;
		$obj->wCfgID = $this->wCfgID;
		$obj->eWactPrizeType = $this->eWactPrizeType;
		$obj->vecItemConfig = $this->vecItemConfig;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SWActConfig;
		$s->wWActID = ByteUtil::readUINT16($data);
		$s->wCfgID = ByteUtil::readUINT16($data);
		$s->eWactPrizeType = ByteUtil::readUINT8($data);
		$s->vecItemConfig = SItemConfig::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SWActConfig::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wWActID);
		ByteUtil::writeUINT16($data, $this->wCfgID);
		ByteUtil::writeUINT8($data, $this->eWactPrizeType);
		SItemConfig::vectorToStream($data, $this->vecItemConfig);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//人物信息
final class SWActPlayerInfo
{
	public $wWActID; //(UINT16)活动ID
	public $wID; //(UINT16)散仙|阵灵ID
	public $qwPlayerID; //(UINT64)玩家ID
	public $strName; //(string)玩家名字|帮主名
	public $eCareer; //(枚类型：ProtoCommon::ECareerType)玩家职业
	public $eSex; //(枚类型：ProtoCommon::ESexType)玩家性别
	public $strName1; //(string)帮派名
	public $dwValue1; //(UINT32)参数1(战力，等级，散仙，阵灵，帮派）排名
	public $dwValue2; //(UINT32)参数2(战力，等级，散仙战力，阵灵战力，帮派等级)

	//构造函数
	function __construct()
	{
		$this->wWActID = 0;
		$this->wID = 0;
		$this->qwPlayerID = new Math_BigInteger;
		$this->strName = '';
		$this->eCareer = 0;
		$this->eSex = 0;
		$this->strName1 = '';
		$this->dwValue1 = 0;
		$this->dwValue2 = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wWActID = $this->wWActID;
		$obj->wID = $this->wID;
		$obj->qwPlayerID = $this->qwPlayerID;
		$obj->strName = $this->strName;
		$obj->eCareer = $this->eCareer;
		$obj->eSex = $this->eSex;
		$obj->strName1 = $this->strName1;
		$obj->dwValue1 = $this->dwValue1;
		$obj->dwValue2 = $this->dwValue2;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SWActPlayerInfo;
		$s->wWActID = ByteUtil::readUINT16($data);
		$s->wID = ByteUtil::readUINT16($data);
		$s->qwPlayerID = ByteUtil::readUINT64($data);
		$s->strName = ByteUtil::readString($data);
		$s->eCareer = ByteUtil::readUINT8($data);
		$s->eSex = ByteUtil::readUINT8($data);
		$s->strName1 = ByteUtil::readString($data);
		$s->dwValue1 = ByteUtil::readUINT32($data);
		$s->dwValue2 = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SWActPlayerInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wWActID);
		ByteUtil::writeUINT16($data, $this->wID);
		ByteUtil::writeUINT64($data, $this->qwPlayerID);
		ByteUtil::writeString($data, $this->strName);
		ByteUtil::writeUINT8($data, $this->eCareer);
		ByteUtil::writeUINT8($data, $this->eSex);
		ByteUtil::writeString($data, $this->strName1);
		ByteUtil::writeUINT32($data, $this->dwValue1);
		ByteUtil::writeUINT32($data, $this->dwValue2);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//活动时间信息
final class STime
{
	public $wWActID; //(UINT16)活动ID
	public $dwAdvTime; //(UINT32)活动预告时间
	public $dwBeginTime; //(UINT32)活动开始时间
	public $dwEndTime; //(UINT32)活动结束时间
	public $dwRetainTime; //(UINT32)活动预留时间

	//构造函数
	function __construct()
	{
		$this->wWActID = 0;
		$this->dwAdvTime = 0;
		$this->dwBeginTime = 0;
		$this->dwEndTime = 0;
		$this->dwRetainTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wWActID = $this->wWActID;
		$obj->dwAdvTime = $this->dwAdvTime;
		$obj->dwBeginTime = $this->dwBeginTime;
		$obj->dwEndTime = $this->dwEndTime;
		$obj->dwRetainTime = $this->dwRetainTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STime;
		$s->wWActID = ByteUtil::readUINT16($data);
		$s->dwAdvTime = ByteUtil::readUINT32($data);
		$s->dwBeginTime = ByteUtil::readUINT32($data);
		$s->dwEndTime = ByteUtil::readUINT32($data);
		$s->dwRetainTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STime::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wWActID);
		ByteUtil::writeUINT32($data, $this->dwAdvTime);
		ByteUtil::writeUINT32($data, $this->dwBeginTime);
		ByteUtil::writeUINT32($data, $this->dwEndTime);
		ByteUtil::writeUINT32($data, $this->dwRetainTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//数据库信息
final class SWonderPrize2DB
{
	public $qwRoleID; //(UINT64)玩家ID
	public $wActID; //(UINT16)活动ID
	public $wActType; //(UINT16)活动类型
	public $wCond; //(UINT32)活动条件
	public $byStatus; //(UINT8)活动状态

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->wActID = 0;
		$this->wActType = 0;
		$this->wCond = 0;
		$this->byStatus = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wActID = $this->wActID;
		$obj->wActType = $this->wActType;
		$obj->wCond = $this->wCond;
		$obj->byStatus = $this->byStatus;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SWonderPrize2DB;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wActID = ByteUtil::readUINT16($data);
		$s->wActType = ByteUtil::readUINT16($data);
		$s->wCond = ByteUtil::readUINT32($data);
		$s->byStatus = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SWonderPrize2DB::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wActID);
		ByteUtil::writeUINT16($data, $this->wActType);
		ByteUtil::writeUINT32($data, $this->wCond);
		ByteUtil::writeUINT8($data, $this->byStatus);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//状态信息
final class SPrizeStatus
{
	public $qwRoleID; //(UINT64)玩家ID
	public $wActID; //(UINT16)活动ID
	public $vecStatus; //(UINT8数组)活动状态

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->wActID = 0;
		$this->vecStatus = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wActID = $this->wActID;
		$obj->vecStatus = $this->vecStatus;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPrizeStatus;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wActID = ByteUtil::readUINT16($data);
		$s->vecStatus = ByteUtil::readVecUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPrizeStatus::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wActID);
		ByteUtil::writeVecUINT8($data, $this->vecStatus);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家在活动中的状态信息
final class SRoleStatus
{
	public $wCond; //(UINT32)活动ID
	public $dwMaxRole; //(UINT32)活动达到条件人数
	public $dwCurRole; //(UINT32)活动目前人数
	public $byStatus; //(UINT8)活动状态

	//构造函数
	function __construct()
	{
		$this->wCond = 0;
		$this->dwMaxRole = 0;
		$this->dwCurRole = 0;
		$this->byStatus = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wCond = $this->wCond;
		$obj->dwMaxRole = $this->dwMaxRole;
		$obj->dwCurRole = $this->dwCurRole;
		$obj->byStatus = $this->byStatus;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SRoleStatus;
		$s->wCond = ByteUtil::readUINT32($data);
		$s->dwMaxRole = ByteUtil::readUINT32($data);
		$s->dwCurRole = ByteUtil::readUINT32($data);
		$s->byStatus = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SRoleStatus::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->wCond);
		ByteUtil::writeUINT32($data, $this->dwMaxRole);
		ByteUtil::writeUINT32($data, $this->dwCurRole);
		ByteUtil::writeUINT8($data, $this->byStatus);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家在活动中的保留值
final class SRetain
{
	public $qwRoleID; //(UINT64)玩家ID
	public $strName; //(string)玩家名字
	public $byCareer; //(UINT8)玩家职业
	public $bySex; //(UINT8)性别
	public $wActID; //(UINT16)活动ID
	public $wID; //(UINT16)保留值（散仙ID,帮派ID,阵灵ID.....)
	public $strGuildName; //(string)帮派名字
	public $wType; //(UINT16)保留类型
	public $dwValue; //(UINT32)保留值
	public $dwTime; //(UINT32)时间

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->strName = '';
		$this->byCareer = 0;
		$this->bySex = 0;
		$this->wActID = 0;
		$this->wID = 0;
		$this->strGuildName = '';
		$this->wType = 0;
		$this->dwValue = 0;
		$this->dwTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->strName = $this->strName;
		$obj->byCareer = $this->byCareer;
		$obj->bySex = $this->bySex;
		$obj->wActID = $this->wActID;
		$obj->wID = $this->wID;
		$obj->strGuildName = $this->strGuildName;
		$obj->wType = $this->wType;
		$obj->dwValue = $this->dwValue;
		$obj->dwTime = $this->dwTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SRetain;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->strName = ByteUtil::readString($data);
		$s->byCareer = ByteUtil::readUINT8($data);
		$s->bySex = ByteUtil::readUINT8($data);
		$s->wActID = ByteUtil::readUINT16($data);
		$s->wID = ByteUtil::readUINT16($data);
		$s->strGuildName = ByteUtil::readString($data);
		$s->wType = ByteUtil::readUINT16($data);
		$s->dwValue = ByteUtil::readUINT32($data);
		$s->dwTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SRetain::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeString($data, $this->strName);
		ByteUtil::writeUINT8($data, $this->byCareer);
		ByteUtil::writeUINT8($data, $this->bySex);
		ByteUtil::writeUINT16($data, $this->wActID);
		ByteUtil::writeUINT16($data, $this->wID);
		ByteUtil::writeString($data, $this->strGuildName);
		ByteUtil::writeUINT16($data, $this->wType);
		ByteUtil::writeUINT32($data, $this->dwValue);
		ByteUtil::writeUINT32($data, $this->dwTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家在所有活动中的信息
final class SRoleAllStatus
{
	public $wActID; //(UINT16)活动ID
	public $vecAllState; //(SRoleStatus的数组)状态

	//构造函数
	function __construct()
	{
		$this->wActID = 0;
		$this->vecAllState = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wActID = $this->wActID;
		$obj->vecAllState = $this->vecAllState;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SRoleAllStatus;
		$s->wActID = ByteUtil::readUINT16($data);
		$s->vecAllState = SRoleStatus::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SRoleAllStatus::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wActID);
		SRoleStatus::vectorToStream($data, $this->vecAllState);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//七星龙珠活动信息
final class SDragonBallAct
{
	public $dwBeginTime; //(UINT32)活动开始时间
	public $dwEndTime; //(UINT32)活动结束时间
	public $dwRecharge; //(UINT32)今日充值仙石数
	public $byIdx; //(UINT8)第几期活动
	public $byDay; //(UINT8)今日完成的龙珠数
	public $byAll; //(UINT8)完成的龙珠总数
	public $byRemain; //(UINT8)今日之前剩余可点亮的龙珠数

	//构造函数
	function __construct()
	{
		$this->dwBeginTime = 0;
		$this->dwEndTime = 0;
		$this->dwRecharge = 0;
		$this->byIdx = 0;
		$this->byDay = 0;
		$this->byAll = 0;
		$this->byRemain = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwBeginTime = $this->dwBeginTime;
		$obj->dwEndTime = $this->dwEndTime;
		$obj->dwRecharge = $this->dwRecharge;
		$obj->byIdx = $this->byIdx;
		$obj->byDay = $this->byDay;
		$obj->byAll = $this->byAll;
		$obj->byRemain = $this->byRemain;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SDragonBallAct;
		$s->dwBeginTime = ByteUtil::readUINT32($data);
		$s->dwEndTime = ByteUtil::readUINT32($data);
		$s->dwRecharge = ByteUtil::readUINT32($data);
		$s->byIdx = ByteUtil::readUINT8($data);
		$s->byDay = ByteUtil::readUINT8($data);
		$s->byAll = ByteUtil::readUINT8($data);
		$s->byRemain = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SDragonBallAct::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwBeginTime);
		ByteUtil::writeUINT32($data, $this->dwEndTime);
		ByteUtil::writeUINT32($data, $this->dwRecharge);
		ByteUtil::writeUINT8($data, $this->byIdx);
		ByteUtil::writeUINT8($data, $this->byDay);
		ByteUtil::writeUINT8($data, $this->byAll);
		ByteUtil::writeUINT8($data, $this->byRemain);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//七日消费活动信息
final class SSevenConsumeAct
{
	public $dwBeginTime; //(UINT32)活动开始时间
	public $dwEndTime; //(UINT32)活动结束时间
	public $dwConsume; //(UINT32)七日总消费仙石数
	public $byInfo; //(UINT8)奖励领取状态信息(从低到高按位取,1已领取 0未领取)

	//构造函数
	function __construct()
	{
		$this->dwBeginTime = 0;
		$this->dwEndTime = 0;
		$this->dwConsume = 0;
		$this->byInfo = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwBeginTime = $this->dwBeginTime;
		$obj->dwEndTime = $this->dwEndTime;
		$obj->dwConsume = $this->dwConsume;
		$obj->byInfo = $this->byInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SSevenConsumeAct;
		$s->dwBeginTime = ByteUtil::readUINT32($data);
		$s->dwEndTime = ByteUtil::readUINT32($data);
		$s->dwConsume = ByteUtil::readUINT32($data);
		$s->byInfo = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SSevenConsumeAct::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwBeginTime);
		ByteUtil::writeUINT32($data, $this->dwEndTime);
		ByteUtil::writeUINT32($data, $this->dwConsume);
		ByteUtil::writeUINT8($data, $this->byInfo);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//Q币养成活动信息
final class SQQCoinActInfo
{
	public $dwTime; //(UINT32)活动剩余时间
	public $byLevel; //(UINT8)当前兑换的等级
	public $dwMaxValue; //(UINT32)奖励最大值
	public $dwCurValue; //(UINT32)当前值

	//构造函数
	function __construct()
	{
		$this->dwTime = 0;
		$this->byLevel = 0;
		$this->dwMaxValue = 0;
		$this->dwCurValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwTime = $this->dwTime;
		$obj->byLevel = $this->byLevel;
		$obj->dwMaxValue = $this->dwMaxValue;
		$obj->dwCurValue = $this->dwCurValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SQQCoinActInfo;
		$s->dwTime = ByteUtil::readUINT32($data);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->dwMaxValue = ByteUtil::readUINT32($data);
		$s->dwCurValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SQQCoinActInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwTime);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT32($data, $this->dwMaxValue);
		ByteUtil::writeUINT32($data, $this->dwCurValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GetConfigTime:获得活动时间配置]的返回的参数组成的结构体
class SRetParam_GetConfigTime
{
	public $sTimes; //(类类型：STime)时间
	public $eRet; //(枚举类型：EWActResult)操作结果

	//构造函数
	function __construct()
	{
		$this->sTimes = new STime;
		$this->eRet = 0;
	}
};

//函数[GetAllPrize:获得活动所有奖励配置]的返回的参数组成的结构体
class SRetParam_GetAllPrize
{
	public $wActID; //(UINT16)活动ID
	public $sFirstPlayer; //(类类型：SWActPlayerInfo)第一名玩家信息
	public $sSelfPlayer; //(类类型：SWActPlayerInfo)玩家自己信息
	public $vecPrizeConfig; //(SPrizeConfig的数组)奖励信息
	public $eRet; //(枚举类型：EWActResult)操作结果

	//构造函数
	function __construct()
	{
		$this->wActID = 0;
		$this->sFirstPlayer = new SWActPlayerInfo;
		$this->sSelfPlayer = new SWActPlayerInfo;
		$this->vecPrizeConfig = array();
		$this->eRet = 0;
	}
};

//函数[GetActList:获得活动列表]的返回的参数组成的结构体
class SRetParam_GetActList
{
	public $vecTimes; //(STime的数组)奖励信息
	public $eRet; //(枚举类型：EWActResult)操作结果

	//构造函数
	function __construct()
	{
		$this->vecTimes = array();
		$this->eRet = 0;
	}
};

//函数[TakePrize:玩家领奖]的返回的参数组成的结构体
class SRetParam_TakePrize
{
	public $wActIDRet; //(UINT16)返回活动ID
	public $wCondRet; //(UINT32)返回条件

	//构造函数
	function __construct()
	{
		$this->wActIDRet = 0;
		$this->wCondRet = 0;
	}
};

//函数[GetRoleActInfo:玩家活动信息]的返回的参数组成的结构体
class SRetParam_GetRoleActInfo
{
	public $wActIDRet; //(UINT16)活动ID
	public $vecRet; //(SRoleStatus的数组)操作结果

	//构造函数
	function __construct()
	{
		$this->wActIDRet = 0;
		$this->vecRet = array();
	}
};

//函数[GetRoleAllState:玩家在所有活动中的状态]的返回的参数组成的结构体
class SRetParam_GetRoleAllState
{
	public $vecRet; //(SRoleAllStatus的数组)结果

	//构造函数
	function __construct()
	{
		$this->vecRet = array();
	}
};

//函数[GetDragonBallAct:请求七星龙珠活动信息]的返回的参数组成的结构体
class SRetParam_GetDragonBallAct
{
	public $byRet; //(UINT8)0活动未开启 >0活动已开启

	//构造函数
	function __construct()
	{
		$this->byRet = 0;
	}
};

//函数[GetSevenConsumeAct:请求七日消费活动信息]的返回的参数组成的结构体
class SRetParam_GetSevenConsumeAct
{
	public $byRet; //(UINT8)0活动未开启 >0活动已开启

	//构造函数
	function __construct()
	{
		$this->byRet = 0;
	}
};

//函数[ExChange:兑换仙石或者领取Q币]的返回的参数组成的结构体
class SRetParam_ExChange
{
	public $eResult; //(枚举类型：EWActResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：精彩活动
abstract class WonderActivityProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获得活动时间配置
	function send_GetConfigTime(
		$wWActID //(UINT16)精彩活动ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wWActID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得活动所有奖励配置
	function send_GetAllPrize(
		$wWActID //(UINT16)精彩活动ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wWActID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得活动列表
	function send_GetActList(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：玩家领奖
	function send_TakePrize(
		$wActID,  //(UINT16)精彩活动ID
		$wCond //(UINT32)条件
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wActID);
		ByteUtil::writeUINT32($data, $wCond);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：玩家活动信息
	function send_GetRoleActInfo(
		$wActID //(UINT16)活动ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wActID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：玩家在所有活动中的状态
	function send_GetRoleAllState(
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

	//发送：请求七星龙珠活动信息
	function send_GetDragonBallAct(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求七日消费活动信息
	function send_GetSevenConsumeAct(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求Q养成活动信息
	function send_GetQQCoinAct(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：兑换仙石或者领取Q币
	function send_ExChange(
		$byType //(UINT8)0表示Q币，1表示仙石
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byType);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：领奖状态通知
	abstract function onRecv_SendTakePrizeNtf(
		$wActID, //(UINT16)活动ID
		$wCond, //(UINT32)条件ID
		$eRet //(枚举类型：EGainResult)状态
	);

	//接收：达到条件通知
	abstract function onRecv_SendReachCondNtf(
		$wActID, //(UINT16)活动ID
		$wCond //(UINT32)条件ID
	);

	//接收：更新七星龙珠活动信息
	abstract function onRecv_UpdateDragonBallAct(
		$oDragonBallAct //(类类型：SDragonBallAct)七星龙珠活动信息
	);

	//接收：更新七日消费活动信息
	abstract function onRecv_UpdateSevenConsumeAct(
		$oSevenConsumeAct //(类类型：SSevenConsumeAct)七日消费活动信息
	);

	//接收：同步QQ养成信息
	abstract function onRecv_SyncQQCoinInfo(
		$oQQCoinInfo //(类类型：SQQCoinActInfo)Q养成活动信息
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获得活动时间配置
	abstract function onReturn_GetConfigTime(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetConfigTime)返回的参数
	);

	//返回：获得活动所有奖励配置
	abstract function onReturn_GetAllPrize(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetAllPrize)返回的参数
	);

	//返回：获得活动列表
	abstract function onReturn_GetActList(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetActList)返回的参数
	);

	//返回：玩家领奖
	abstract function onReturn_TakePrize(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TakePrize)返回的参数
	);

	//返回：玩家活动信息
	abstract function onReturn_GetRoleActInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetRoleActInfo)返回的参数
	);

	//返回：玩家在所有活动中的状态
	abstract function onReturn_GetRoleAllState(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetRoleAllState)返回的参数
	);

	//返回：请求七星龙珠活动信息
	abstract function onReturn_GetDragonBallAct(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetDragonBallAct)返回的参数
	);

	//返回：请求七日消费活动信息
	abstract function onReturn_GetSevenConsumeAct(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetSevenConsumeAct)返回的参数
	);

	//返回：兑换仙石或者领取Q币
	abstract function onReturn_ExChange(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ExChange)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：领奖状态通知
	private function _doRecv_SendTakePrizeNtf($data)
	{
		$wActID = ByteUtil::readUINT16($data);
		$wCond = ByteUtil::readUINT32($data);
		$eRet = ByteUtil::readUINT8($data);
		return $this->onRecv_SendTakePrizeNtf($wActID, $wCond, $eRet);
	}

	//接收处理：达到条件通知
	private function _doRecv_SendReachCondNtf($data)
	{
		$wActID = ByteUtil::readUINT16($data);
		$wCond = ByteUtil::readUINT32($data);
		return $this->onRecv_SendReachCondNtf($wActID, $wCond);
	}

	//接收处理：更新七星龙珠活动信息
	private function _doRecv_UpdateDragonBallAct($data)
	{
		$oDragonBallAct = SDragonBallAct::fromStream($data);
		return $this->onRecv_UpdateDragonBallAct($oDragonBallAct);
	}

	//接收处理：更新七日消费活动信息
	private function _doRecv_UpdateSevenConsumeAct($data)
	{
		$oSevenConsumeAct = SSevenConsumeAct::fromStream($data);
		return $this->onRecv_UpdateSevenConsumeAct($oSevenConsumeAct);
	}

	//接收处理：同步QQ养成信息
	private function _doRecv_SyncQQCoinInfo($data)
	{
		$oQQCoinInfo = SQQCoinActInfo::fromStream($data);
		return $this->onRecv_SyncQQCoinInfo($oQQCoinInfo);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：获得活动时间配置
	private function _doReturn_GetConfigTime($data)
	{
		$retParam = new SRetParam_GetConfigTime;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$sTimes = STime::fromStream($data); //时间
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EWActResult)操作结果
		$retParam->sTimes = $sTimes;
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetConfigTime($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得活动时间配置
	private function _onTimeOut_GetConfigTime($sessionID)
	{
		$retParam = new SRetParam_GetConfigTime;
		$this->onReturn_GetConfigTime(2, $retParam);
	}

	//返回处理：获得活动所有奖励配置
	private function _doReturn_GetAllPrize($data)
	{
		$retParam = new SRetParam_GetAllPrize;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wActID = ByteUtil::readUINT16($data); //(无符号16位整数)活动ID
		$sFirstPlayer = SWActPlayerInfo::fromStream($data); //第一名玩家信息
		$sSelfPlayer = SWActPlayerInfo::fromStream($data); //玩家自己信息
		$vecPrizeConfig = SPrizeConfig::vectorFromStream($data); //奖励信息
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EWActResult)操作结果
		$retParam->wActID = $wActID;
		$retParam->sFirstPlayer = $sFirstPlayer;
		$retParam->sSelfPlayer = $sSelfPlayer;
		$retParam->vecPrizeConfig = $vecPrizeConfig;
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetAllPrize($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得活动所有奖励配置
	private function _onTimeOut_GetAllPrize($sessionID)
	{
		$retParam = new SRetParam_GetAllPrize;
		$this->onReturn_GetAllPrize(2, $retParam);
	}

	//返回处理：获得活动列表
	private function _doReturn_GetActList($data)
	{
		$retParam = new SRetParam_GetActList;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTimes = STime::vectorFromStream($data); //奖励信息
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EWActResult)操作结果
		$retParam->vecTimes = $vecTimes;
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetActList($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得活动列表
	private function _onTimeOut_GetActList($sessionID)
	{
		$retParam = new SRetParam_GetActList;
		$this->onReturn_GetActList(2, $retParam);
	}

	//返回处理：玩家领奖
	private function _doReturn_TakePrize($data)
	{
		$retParam = new SRetParam_TakePrize;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wActIDRet = ByteUtil::readUINT16($data); //(无符号16位整数)返回活动ID
		$wCondRet = ByteUtil::readUINT32($data); //(无符号32位整数)返回条件
		$retParam->wActIDRet = $wActIDRet;
		$retParam->wCondRet = $wCondRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakePrize($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：玩家领奖
	private function _onTimeOut_TakePrize($sessionID)
	{
		$retParam = new SRetParam_TakePrize;
		$this->onReturn_TakePrize(2, $retParam);
	}

	//返回处理：玩家活动信息
	private function _doReturn_GetRoleActInfo($data)
	{
		$retParam = new SRetParam_GetRoleActInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wActIDRet = ByteUtil::readUINT16($data); //(无符号16位整数)活动ID
		$vecRet = SRoleStatus::vectorFromStream($data); //操作结果
		$retParam->wActIDRet = $wActIDRet;
		$retParam->vecRet = $vecRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetRoleActInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：玩家活动信息
	private function _onTimeOut_GetRoleActInfo($sessionID)
	{
		$retParam = new SRetParam_GetRoleActInfo;
		$this->onReturn_GetRoleActInfo(2, $retParam);
	}

	//返回处理：玩家在所有活动中的状态
	private function _doReturn_GetRoleAllState($data)
	{
		$retParam = new SRetParam_GetRoleAllState;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecRet = SRoleAllStatus::vectorFromStream($data); //结果
		$retParam->vecRet = $vecRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetRoleAllState($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：玩家在所有活动中的状态
	private function _onTimeOut_GetRoleAllState($sessionID)
	{
		$retParam = new SRetParam_GetRoleAllState;
		$this->onReturn_GetRoleAllState(2, $retParam);
	}

	//返回处理：请求七星龙珠活动信息
	private function _doReturn_GetDragonBallAct($data)
	{
		$retParam = new SRetParam_GetDragonBallAct;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$byRet = ByteUtil::readUINT8($data); //(无符号8位整数)0活动未开启 >0活动已开启
		$retParam->byRet = $byRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetDragonBallAct($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求七星龙珠活动信息
	private function _onTimeOut_GetDragonBallAct($sessionID)
	{
		$retParam = new SRetParam_GetDragonBallAct;
		$this->onReturn_GetDragonBallAct(2, $retParam);
	}

	//返回处理：请求七日消费活动信息
	private function _doReturn_GetSevenConsumeAct($data)
	{
		$retParam = new SRetParam_GetSevenConsumeAct;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$byRet = ByteUtil::readUINT8($data); //(无符号8位整数)0活动未开启 >0活动已开启
		$retParam->byRet = $byRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetSevenConsumeAct($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求七日消费活动信息
	private function _onTimeOut_GetSevenConsumeAct($sessionID)
	{
		$retParam = new SRetParam_GetSevenConsumeAct;
		$this->onReturn_GetSevenConsumeAct(2, $retParam);
	}

	//返回处理：兑换仙石或者领取Q币
	private function _doReturn_ExChange($data)
	{
		$retParam = new SRetParam_ExChange;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EWActResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ExChange($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：兑换仙石或者领取Q币
	private function _onTimeOut_ExChange($sessionID)
	{
		$retParam = new SRetParam_ExChange;
		$this->onReturn_ExChange(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 199;
		$this->_recvFuncList[0] = '_doRecv_SendTakePrizeNtf'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_SendReachCondNtf'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_UpdateDragonBallAct'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_UpdateSevenConsumeAct'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_SyncQQCoinInfo'; //FuncID: 5

		$this->_retFuncList[0] = '_doReturn_GetConfigTime'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_GetAllPrize'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GetActList'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_TakePrize'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_GetRoleActInfo'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_GetRoleAllState'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_GetDragonBallAct'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_GetSevenConsumeAct'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_ExChange'; //FuncID: 9

		$this->_timeFuncList[0] = '_onTimeOut_GetConfigTime'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_GetAllPrize'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GetActList'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_TakePrize'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_GetRoleActInfo'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_GetRoleAllState'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_GetDragonBallAct'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_GetSevenConsumeAct'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_ExChange'; //FuncID: 9
	}

	function handleMessage($data)
	{
		$funcID = ByteUtil::readINT8($data);
		if($funcID == 0 || $funcID > count($this->_recvFuncList)
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