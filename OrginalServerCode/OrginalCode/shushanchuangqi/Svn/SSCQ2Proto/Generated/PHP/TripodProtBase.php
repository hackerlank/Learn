<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    TripodProt.php
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ArenaGSBase.php');
require_once('ItemProtBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//九疑鼎操作结果
class ETripodType
{
	const eTripodSucc = 0; //成功
	const eTripodFailed = 1; //失败
	const eTripodCondIDErr = 2; //激活条件不足
	const eTripodItemErr = 3; //道具不足
	const eTripodNotFire = 4; //未祈火
	const eTripodNoEnoughCnt = 5; //剩余祈火次数不足
	const eTripodYuanqiNotFull = 6; //元气值未满
	const eTripodYuanqiFull = 7; //元气值已满
	const eTripodNotTime = 8; //时间未到
	const eTripodShanfengFull = 9; //扇风次数已满
	const eTripodHelpTimesFull = 10; //协助次数已满
	const eTripodNotHelp = 11; //不能协助
}

//九疑鼎日志类型
class ETripodLogType
{
	const eTripodLogNone = 0; //无效日志类型
	const eTripodLogHelp = 1; //成员日志
	const eTripodLogMax = 2; //日志类型最大值
}

//玩家的九疑鼎数据
final class STripodInfo
{
	public $byTripodID; //(UINT8)九疑鼎ID
	public $byLevel; //(UINT8)九疑鼎等级
	public $dwExp; //(UINT32)九疑鼎当前经验值
	public $wFireID; //(UINT16)火种ID
	public $byFireLvl; //(UINT8)火种等级(品质)
	public $dwStartTime; //(UINT32)上一次结算时间
	public $dwShanfengTime; //(UINT32)上一次扇风时间(为0未扇风)
	public $dwSoul; //(UINT32)当前已结算的总元气值
	public $dwLine; //(UINT32)产物加成系数（万分比）

	//构造函数
	function __construct()
	{
		$this->byTripodID = 0;
		$this->byLevel = 0;
		$this->dwExp = 0;
		$this->wFireID = 0;
		$this->byFireLvl = 0;
		$this->dwStartTime = 0;
		$this->dwShanfengTime = 0;
		$this->dwSoul = 0;
		$this->dwLine = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->byTripodID = $this->byTripodID;
		$obj->byLevel = $this->byLevel;
		$obj->dwExp = $this->dwExp;
		$obj->wFireID = $this->wFireID;
		$obj->byFireLvl = $this->byFireLvl;
		$obj->dwStartTime = $this->dwStartTime;
		$obj->dwShanfengTime = $this->dwShanfengTime;
		$obj->dwSoul = $this->dwSoul;
		$obj->dwLine = $this->dwLine;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STripodInfo;
		$s->byTripodID = ByteUtil::readUINT8($data);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->dwExp = ByteUtil::readUINT32($data);
		$s->wFireID = ByteUtil::readUINT16($data);
		$s->byFireLvl = ByteUtil::readUINT8($data);
		$s->dwStartTime = ByteUtil::readUINT32($data);
		$s->dwShanfengTime = ByteUtil::readUINT32($data);
		$s->dwSoul = ByteUtil::readUINT32($data);
		$s->dwLine = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STripodInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->byTripodID);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT32($data, $this->dwExp);
		ByteUtil::writeUINT16($data, $this->wFireID);
		ByteUtil::writeUINT8($data, $this->byFireLvl);
		ByteUtil::writeUINT32($data, $this->dwStartTime);
		ByteUtil::writeUINT32($data, $this->dwShanfengTime);
		ByteUtil::writeUINT32($data, $this->dwSoul);
		ByteUtil::writeUINT32($data, $this->dwLine);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//九疑鼎散仙协助
final class SFighterHelpInfo
{
	public $wFighterID; //(UINT16)散仙ID
	public $byPos; //(UINT8)协助位置(0,1)
	public $byColor; //(UINT8)散仙协助时的品质
	public $dwStartTime; //(UINT32)开始协助的时间

	//构造函数
	function __construct()
	{
		$this->wFighterID = 0;
		$this->byPos = 0;
		$this->byColor = 0;
		$this->dwStartTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wFighterID = $this->wFighterID;
		$obj->byPos = $this->byPos;
		$obj->byColor = $this->byColor;
		$obj->dwStartTime = $this->dwStartTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterHelpInfo;
		$s->wFighterID = ByteUtil::readUINT16($data);
		$s->byPos = ByteUtil::readUINT8($data);
		$s->byColor = ByteUtil::readUINT8($data);
		$s->dwStartTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterHelpInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wFighterID);
		ByteUtil::writeUINT8($data, $this->byPos);
		ByteUtil::writeUINT8($data, $this->byColor);
		ByteUtil::writeUINT32($data, $this->dwStartTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//九疑鼎玩家协助
final class SPlayerHelpInfo
{
	public $qwRoleID; //(UINT64)协助者(玩家)ID
	public $byPos; //(UINT8)协助位置(0,1,2)
	public $byLevel; //(UINT8)玩家协助时的等级
	public $dwStartTime; //(UINT32)开始协助的时间
	public $stPlayer; //(类类型：ArenaGS::SArenaFighter)玩家的基础信息(外观)
	public $vecPlatforms; //(SPlatformParam的数组)平台信息

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->byPos = 0;
		$this->byLevel = 0;
		$this->dwStartTime = 0;
		$this->stPlayer = new SArenaFighter;
		$this->vecPlatforms = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->byPos = $this->byPos;
		$obj->byLevel = $this->byLevel;
		$obj->dwStartTime = $this->dwStartTime;
		$obj->stPlayer = $this->stPlayer;
		$obj->vecPlatforms = $this->vecPlatforms;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPlayerHelpInfo;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->byPos = ByteUtil::readUINT8($data);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->dwStartTime = ByteUtil::readUINT32($data);
		$s->stPlayer = SArenaFighter::fromStream($data);
		$s->vecPlatforms = SPlatformParam::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPlayerHelpInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT8($data, $this->byPos);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT32($data, $this->dwStartTime);
		$this->stPlayer->toStream($data);
		SPlatformParam::vectorToStream($data, $this->vecPlatforms);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//九疑鼎的协助信息
final class STripodHelp
{
	public $qwRoleID; //(UINT64)九疑鼎的所属玩家的ID
	public $vecFighterHelp; //(SFighterHelpInfo的数组)散仙协助信息
	public $vecPlayerHelp; //(SPlayerHelpInfo的数组)玩家协助信息

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->vecFighterHelp = array();
		$this->vecPlayerHelp = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->vecFighterHelp = $this->vecFighterHelp;
		$obj->vecPlayerHelp = $this->vecPlayerHelp;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STripodHelp;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->vecFighterHelp = SFighterHelpInfo::vectorFromStream($data);
		$s->vecPlayerHelp = SPlayerHelpInfo::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STripodHelp::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		SFighterHelpInfo::vectorToStream($data, $this->vecFighterHelp);
		SPlayerHelpInfo::vectorToStream($data, $this->vecPlayerHelp);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//九疑鼎历史日志
final class STripodLog
{
	public $qwRoleID; //(UINT64)九疑鼎的所属玩家的ID
	public $wMsgID; //(UINT16)对应日志ID（详见Message）
	public $vecParam; //(INT64数组)整型变量
	public $vecString; //(string数组)字符串型变量
	public $dwTime; //(UINT32)日志时间

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->wMsgID = 0;
		$this->vecParam = array();
		$this->vecString = array();
		$this->dwTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wMsgID = $this->wMsgID;
		$obj->vecParam = $this->vecParam;
		$obj->vecString = $this->vecString;
		$obj->dwTime = $this->dwTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STripodLog;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wMsgID = ByteUtil::readUINT16($data);
		$s->vecParam = ByteUtil::readVecINT64($data);
		$s->vecString = ByteUtil::readVecString($data);
		$s->dwTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STripodLog::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wMsgID);
		ByteUtil::writeVecINT64($data, $this->vecParam);
		ByteUtil::writeVecString($data, $this->vecString);
		ByteUtil::writeUINT32($data, $this->dwTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家九疑鼎信息
final class STripodData
{
	public $qwRoleID; //(UINT64)玩家的ID
	public $stPlayer; //(类类型：ArenaGS::SArenaFighter)九疑鼎所属玩家的基础信息
	public $tripodHelpData; //(类类型：STripodHelp)玩家九疑鼎的协助数据
	public $vecTripods; //(STripodInfo的数组)玩家的所有九疑鼎数据
	public $vecTripodLog; //(STripodLog的数组)九疑鼎日志

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->stPlayer = new SArenaFighter;
		$this->tripodHelpData = new STripodHelp;
		$this->vecTripods = array();
		$this->vecTripodLog = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->stPlayer = $this->stPlayer;
		$obj->tripodHelpData = $this->tripodHelpData;
		$obj->vecTripods = $this->vecTripods;
		$obj->vecTripodLog = $this->vecTripodLog;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STripodData;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->stPlayer = SArenaFighter::fromStream($data);
		$s->tripodHelpData = STripodHelp::fromStream($data);
		$s->vecTripods = STripodInfo::vectorFromStream($data);
		$s->vecTripodLog = STripodLog::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STripodData::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		$this->stPlayer->toStream($data);
		$this->tripodHelpData->toStream($data);
		STripodInfo::vectorToStream($data, $this->vecTripods);
		STripodLog::vectorToStream($data, $this->vecTripodLog);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家的九疑鼎火种数据
final class SFireInfo
{
	public $wFireID; //(UINT16)九疑鼎火种ID
	public $dwSucceed; //(UINT32)火种祈火成功次数
	public $dwRemain; //(UINT32)火种剩余祈火次数

	//构造函数
	function __construct()
	{
		$this->wFireID = 0;
		$this->dwSucceed = 0;
		$this->dwRemain = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wFireID = $this->wFireID;
		$obj->dwSucceed = $this->dwSucceed;
		$obj->dwRemain = $this->dwRemain;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFireInfo;
		$s->wFireID = ByteUtil::readUINT16($data);
		$s->dwSucceed = ByteUtil::readUINT32($data);
		$s->dwRemain = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFireInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wFireID);
		ByteUtil::writeUINT32($data, $this->dwSucceed);
		ByteUtil::writeUINT32($data, $this->dwRemain);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家九疑鼎的扇火、协助状态
final class STripodStatus
{
	public $qwRoleID; //(UINT64)玩家的ID
	public $byShanfengst; //(UINT8)是否可以扇火(1是 0否)
	public $byHelpst; //(UINT8)是否可以协助(1是 0否)

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->byShanfengst = 0;
		$this->byHelpst = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->byShanfengst = $this->byShanfengst;
		$obj->byHelpst = $this->byHelpst;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STripodStatus;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->byShanfengst = ByteUtil::readUINT8($data);
		$s->byHelpst = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STripodStatus::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT8($data, $this->byShanfengst);
		ByteUtil::writeUINT8($data, $this->byHelpst);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GetAllTripods:取得玩家所有九疑鼎信息]的返回的参数组成的结构体
class SRetParam_GetAllTripods
{
	public $oTripodData; //(类类型：STripodData)九疑鼎数据列表
	public $byShanfeng; //(UINT8)玩家今日已扇风次数
	public $byHelpTimes; //(UINT8)玩家今日已协助次数(玩家协助)

	//构造函数
	function __construct()
	{
		$this->oTripodData = new STripodData;
		$this->byShanfeng = 0;
		$this->byHelpTimes = 0;
	}
};

//函数[GetAllFires:取得玩家所有九疑鼎的火种信息]的返回的参数组成的结构体
class SRetParam_GetAllFires
{
	public $vecFires; //(SFireInfo的数组)九疑鼎信息列表

	//构造函数
	function __construct()
	{
		$this->vecFires = array();
	}
};

//函数[GetTripodData:取得其他玩家所有九疑鼎信息]的返回的参数组成的结构体
class SRetParam_GetTripodData
{
	public $oTripodData; //(类类型：STripodData)九疑鼎数据列表

	//构造函数
	function __construct()
	{
		$this->oTripodData = new STripodData;
	}
};

//函数[ActiveTripod:激活九疑鼎]的返回的参数组成的结构体
class SRetParam_ActiveTripod
{
	public $byTripodID; //(UINT8)九疑鼎ID
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->byTripodID = 0;
		$this->eResult = 0;
	}
};

//函数[UpgradeTripod:升级九疑鼎]的返回的参数组成的结构体
class SRetParam_UpgradeTripod
{
	public $vecTripods; //(STripodInfo的数组)九疑鼎信息列表
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->vecTripods = array();
		$this->eResult = 0;
	}
};

//函数[MakeFireTripod:九疑鼎祈火(炼丹)]的返回的参数组成的结构体
class SRetParam_MakeFireTripod
{
	public $vecTripods; //(STripodInfo的数组)九疑鼎信息列表
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->vecTripods = array();
		$this->eResult = 0;
	}
};

//函数[ClearFireTripod:清除九疑鼎祈火记录]的返回的参数组成的结构体
class SRetParam_ClearFireTripod
{
	public $byTripodID; //(UINT8)九疑鼎ID
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->byTripodID = 0;
		$this->eResult = 0;
	}
};

//函数[GetTripodAward:获取九疑鼎炼丹果实]的返回的参数组成的结构体
class SRetParam_GetTripodAward
{
	public $vecTripods; //(STripodInfo的数组)九疑鼎信息列表
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->vecTripods = array();
		$this->eResult = 0;
	}
};

//函数[SpeedTripod:加速九疑鼎炼丹(道具入鼎)]的返回的参数组成的结构体
class SRetParam_SpeedTripod
{
	public $vecTripods; //(STripodInfo的数组)九疑鼎信息列表
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->vecTripods = array();
		$this->eResult = 0;
	}
};

//函数[AddTripodExtraSoul:扇火九疑鼎]的返回的参数组成的结构体
class SRetParam_AddTripodExtraSoul
{
	public $vecTripods; //(STripodInfo的数组)所属者的九疑鼎信息列表
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->vecTripods = array();
		$this->eResult = 0;
	}
};

//函数[FighterHelpTripod:散仙协助九疑鼎]的返回的参数组成的结构体
class SRetParam_FighterHelpTripod
{
	public $oFighterHelp; //(类类型：SFighterHelpInfo)散仙协助信息
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->oFighterHelp = new SFighterHelpInfo;
		$this->eResult = 0;
	}
};

//函数[UserHelpTripod:玩家协助九疑鼎]的返回的参数组成的结构体
class SRetParam_UserHelpTripod
{
	public $oPlayerHelp; //(类类型：SPlayerHelpInfo)玩家协助信息
	public $eResult; //(枚举类型：ETripodType)结果

	//构造函数
	function __construct()
	{
		$this->oPlayerHelp = new SPlayerHelpInfo;
		$this->eResult = 0;
	}
};

//函数[ShotOffHelpTripod:踢出九疑鼎协助者]的返回的参数组成的结构体
class SRetParam_ShotOffHelpTripod
{
	public $eResult; //(枚举类型：ETripodType)结果
	public $byPos; //(UINT8)协助位置(0,1,2)
	public $byType; //(UINT8)0散仙 1玩家

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->byPos = 0;
		$this->byType = 0;
	}
};

//函数[GetTripodStatus:请求玩家九疑鼎的能被扇火、协助信息]的返回的参数组成的结构体
class SRetParam_GetTripodStatus
{
	public $vecStatus; //(STripodStatus的数组)玩家九疑鼎的扇火、协助状态

	//构造函数
	function __construct()
	{
		$this->vecStatus = array();
	}
};

////////////////////////////////////////////////////////////
//协议类：九疑鼎相关协议
abstract class TripodProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：取得玩家所有九疑鼎信息
	function send_GetAllTripods(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：取得玩家所有九疑鼎的火种信息
	function send_GetAllFires(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：取得其他玩家所有九疑鼎信息
	function send_GetTripodData(
		$qwRoleID //(UINT64)玩家ID(九疑鼎所属者)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwRoleID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：激活九疑鼎
	function send_ActiveTripod(
		$byTripodID //(UINT8)九疑鼎ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：升级九疑鼎
	function send_UpgradeTripod(
		$byTripodID,  //(UINT8)九疑鼎ID
		$byOneKey //(UINT8)是否一键
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		ByteUtil::writeUINT8($data, $byOneKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：九疑鼎祈火(炼丹)
	function send_MakeFireTripod(
		$byTripodID,  //(UINT8)九疑鼎ID
		$wFireID //(UINT16)火种ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 6);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		ByteUtil::writeUINT16($data, $wFireID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：清除九疑鼎祈火记录
	function send_ClearFireTripod(
		$byTripodID //(UINT8)九疑鼎ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取九疑鼎炼丹果实
	function send_GetTripodAward(
		$byTripodID //(UINT8)九疑鼎ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：加速九疑鼎炼丹(道具入鼎)
	function send_SpeedTripod(
		$byTripodID,  //(UINT8)九疑鼎ID
		$vecItems //(SItemCount的数组)入鼎道具列表
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byTripodID);
		SItemCount::vectorToStream($data, $vecItems);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：扇火九疑鼎
	function send_AddTripodExtraSoul(
		$qwRoleID,  //(UINT64)玩家ID(九疑鼎所属者)
		$byTripodID //(UINT8)九疑鼎ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 10);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwRoleID);
		ByteUtil::writeUINT8($data, $byTripodID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙协助九疑鼎
	function send_FighterHelpTripod(
		$wFighterID,  //(UINT16)自己的散仙ID
		$byPos //(UINT8)协助位置
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 11);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 11;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wFighterID);
		ByteUtil::writeUINT8($data, $byPos);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：玩家协助九疑鼎
	function send_UserHelpTripod(
		$qwRoleID,  //(UINT64)对方玩家ID
		$byPos //(UINT8)协助位置
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 12);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 12;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwRoleID);
		ByteUtil::writeUINT8($data, $byPos);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：踢出九疑鼎协助者
	function send_ShotOffHelpTripod(
		$byPos,  //(UINT8)协助位置(0,1,2)
		$byType //(UINT8)0散仙 1玩家
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 13);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 13;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byPos);
		ByteUtil::writeUINT8($data, $byType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求玩家九疑鼎的能被扇火、协助信息
	function send_GetTripodStatus(
		$vecRoleID //(UINT64数组)好友玩家ID列表
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 14);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 14;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeVecUINT64($data, $vecRoleID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：更新玩家的九疑鼎数据
	abstract function onRecv_UpdateTripod(
		$oTripodData, //(类类型：STripodData)九疑鼎数据列表
		$byShanfeng, //(UINT8)玩家今日已扇风次数
		$byHelpTimes //(UINT8)玩家今日已协助次数(玩家协助)
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：取得玩家所有九疑鼎信息
	abstract function onReturn_GetAllTripods(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetAllTripods)返回的参数
	);

	//返回：取得玩家所有九疑鼎的火种信息
	abstract function onReturn_GetAllFires(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetAllFires)返回的参数
	);

	//返回：取得其他玩家所有九疑鼎信息
	abstract function onReturn_GetTripodData(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTripodData)返回的参数
	);

	//返回：激活九疑鼎
	abstract function onReturn_ActiveTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ActiveTripod)返回的参数
	);

	//返回：升级九疑鼎
	abstract function onReturn_UpgradeTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UpgradeTripod)返回的参数
	);

	//返回：九疑鼎祈火(炼丹)
	abstract function onReturn_MakeFireTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MakeFireTripod)返回的参数
	);

	//返回：清除九疑鼎祈火记录
	abstract function onReturn_ClearFireTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ClearFireTripod)返回的参数
	);

	//返回：获取九疑鼎炼丹果实
	abstract function onReturn_GetTripodAward(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTripodAward)返回的参数
	);

	//返回：加速九疑鼎炼丹(道具入鼎)
	abstract function onReturn_SpeedTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SpeedTripod)返回的参数
	);

	//返回：扇火九疑鼎
	abstract function onReturn_AddTripodExtraSoul(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_AddTripodExtraSoul)返回的参数
	);

	//返回：散仙协助九疑鼎
	abstract function onReturn_FighterHelpTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterHelpTripod)返回的参数
	);

	//返回：玩家协助九疑鼎
	abstract function onReturn_UserHelpTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UserHelpTripod)返回的参数
	);

	//返回：踢出九疑鼎协助者
	abstract function onReturn_ShotOffHelpTripod(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ShotOffHelpTripod)返回的参数
	);

	//返回：请求玩家九疑鼎的能被扇火、协助信息
	abstract function onReturn_GetTripodStatus(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTripodStatus)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：更新玩家的九疑鼎数据
	private function _doRecv_UpdateTripod($data)
	{
		$oTripodData = STripodData::fromStream($data);
		$byShanfeng = ByteUtil::readUINT8($data);
		$byHelpTimes = ByteUtil::readUINT8($data);
		return $this->onRecv_UpdateTripod($oTripodData, $byShanfeng, $byHelpTimes);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：取得玩家所有九疑鼎信息
	private function _doReturn_GetAllTripods($data)
	{
		$retParam = new SRetParam_GetAllTripods;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oTripodData = STripodData::fromStream($data); //九疑鼎数据列表
		$byShanfeng = ByteUtil::readUINT8($data); //(无符号8位整数)玩家今日已扇风次数
		$byHelpTimes = ByteUtil::readUINT8($data); //(无符号8位整数)玩家今日已协助次数(玩家协助)
		$retParam->oTripodData = $oTripodData;
		$retParam->byShanfeng = $byShanfeng;
		$retParam->byHelpTimes = $byHelpTimes;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetAllTripods($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取得玩家所有九疑鼎信息
	private function _onTimeOut_GetAllTripods($sessionID)
	{
		$retParam = new SRetParam_GetAllTripods;
		$this->onReturn_GetAllTripods(2, $retParam);
	}

	//返回处理：取得玩家所有九疑鼎的火种信息
	private function _doReturn_GetAllFires($data)
	{
		$retParam = new SRetParam_GetAllFires;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecFires = SFireInfo::vectorFromStream($data); //九疑鼎信息列表
		$retParam->vecFires = $vecFires;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetAllFires($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取得玩家所有九疑鼎的火种信息
	private function _onTimeOut_GetAllFires($sessionID)
	{
		$retParam = new SRetParam_GetAllFires;
		$this->onReturn_GetAllFires(2, $retParam);
	}

	//返回处理：取得其他玩家所有九疑鼎信息
	private function _doReturn_GetTripodData($data)
	{
		$retParam = new SRetParam_GetTripodData;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oTripodData = STripodData::fromStream($data); //九疑鼎数据列表
		$retParam->oTripodData = $oTripodData;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTripodData($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取得其他玩家所有九疑鼎信息
	private function _onTimeOut_GetTripodData($sessionID)
	{
		$retParam = new SRetParam_GetTripodData;
		$this->onReturn_GetTripodData(2, $retParam);
	}

	//返回处理：激活九疑鼎
	private function _doReturn_ActiveTripod($data)
	{
		$retParam = new SRetParam_ActiveTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$byTripodID = ByteUtil::readUINT8($data); //(无符号8位整数)九疑鼎ID
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->byTripodID = $byTripodID;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ActiveTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：激活九疑鼎
	private function _onTimeOut_ActiveTripod($sessionID)
	{
		$retParam = new SRetParam_ActiveTripod;
		$this->onReturn_ActiveTripod(2, $retParam);
	}

	//返回处理：升级九疑鼎
	private function _doReturn_UpgradeTripod($data)
	{
		$retParam = new SRetParam_UpgradeTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTripods = STripodInfo::vectorFromStream($data); //九疑鼎信息列表
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->vecTripods = $vecTripods;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UpgradeTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：升级九疑鼎
	private function _onTimeOut_UpgradeTripod($sessionID)
	{
		$retParam = new SRetParam_UpgradeTripod;
		$this->onReturn_UpgradeTripod(2, $retParam);
	}

	//返回处理：九疑鼎祈火(炼丹)
	private function _doReturn_MakeFireTripod($data)
	{
		$retParam = new SRetParam_MakeFireTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTripods = STripodInfo::vectorFromStream($data); //九疑鼎信息列表
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->vecTripods = $vecTripods;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MakeFireTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：九疑鼎祈火(炼丹)
	private function _onTimeOut_MakeFireTripod($sessionID)
	{
		$retParam = new SRetParam_MakeFireTripod;
		$this->onReturn_MakeFireTripod(2, $retParam);
	}

	//返回处理：清除九疑鼎祈火记录
	private function _doReturn_ClearFireTripod($data)
	{
		$retParam = new SRetParam_ClearFireTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$byTripodID = ByteUtil::readUINT8($data); //(无符号8位整数)九疑鼎ID
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->byTripodID = $byTripodID;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ClearFireTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：清除九疑鼎祈火记录
	private function _onTimeOut_ClearFireTripod($sessionID)
	{
		$retParam = new SRetParam_ClearFireTripod;
		$this->onReturn_ClearFireTripod(2, $retParam);
	}

	//返回处理：获取九疑鼎炼丹果实
	private function _doReturn_GetTripodAward($data)
	{
		$retParam = new SRetParam_GetTripodAward;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTripods = STripodInfo::vectorFromStream($data); //九疑鼎信息列表
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->vecTripods = $vecTripods;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTripodAward($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取九疑鼎炼丹果实
	private function _onTimeOut_GetTripodAward($sessionID)
	{
		$retParam = new SRetParam_GetTripodAward;
		$this->onReturn_GetTripodAward(2, $retParam);
	}

	//返回处理：加速九疑鼎炼丹(道具入鼎)
	private function _doReturn_SpeedTripod($data)
	{
		$retParam = new SRetParam_SpeedTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTripods = STripodInfo::vectorFromStream($data); //九疑鼎信息列表
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->vecTripods = $vecTripods;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SpeedTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：加速九疑鼎炼丹(道具入鼎)
	private function _onTimeOut_SpeedTripod($sessionID)
	{
		$retParam = new SRetParam_SpeedTripod;
		$this->onReturn_SpeedTripod(2, $retParam);
	}

	//返回处理：扇火九疑鼎
	private function _doReturn_AddTripodExtraSoul($data)
	{
		$retParam = new SRetParam_AddTripodExtraSoul;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecTripods = STripodInfo::vectorFromStream($data); //所属者的九疑鼎信息列表
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->vecTripods = $vecTripods;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_AddTripodExtraSoul($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：扇火九疑鼎
	private function _onTimeOut_AddTripodExtraSoul($sessionID)
	{
		$retParam = new SRetParam_AddTripodExtraSoul;
		$this->onReturn_AddTripodExtraSoul(2, $retParam);
	}

	//返回处理：散仙协助九疑鼎
	private function _doReturn_FighterHelpTripod($data)
	{
		$retParam = new SRetParam_FighterHelpTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oFighterHelp = SFighterHelpInfo::fromStream($data); //散仙协助信息
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->oFighterHelp = $oFighterHelp;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterHelpTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙协助九疑鼎
	private function _onTimeOut_FighterHelpTripod($sessionID)
	{
		$retParam = new SRetParam_FighterHelpTripod;
		$this->onReturn_FighterHelpTripod(2, $retParam);
	}

	//返回处理：玩家协助九疑鼎
	private function _doReturn_UserHelpTripod($data)
	{
		$retParam = new SRetParam_UserHelpTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oPlayerHelp = SPlayerHelpInfo::fromStream($data); //玩家协助信息
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$retParam->oPlayerHelp = $oPlayerHelp;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UserHelpTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：玩家协助九疑鼎
	private function _onTimeOut_UserHelpTripod($sessionID)
	{
		$retParam = new SRetParam_UserHelpTripod;
		$this->onReturn_UserHelpTripod(2, $retParam);
	}

	//返回处理：踢出九疑鼎协助者
	private function _doReturn_ShotOffHelpTripod($data)
	{
		$retParam = new SRetParam_ShotOffHelpTripod;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETripodType)结果
		$byPos = ByteUtil::readUINT8($data); //(无符号8位整数)协助位置(0,1,2)
		$byType = ByteUtil::readUINT8($data); //(无符号8位整数)0散仙 1玩家
		$retParam->eResult = $eResult;
		$retParam->byPos = $byPos;
		$retParam->byType = $byType;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ShotOffHelpTripod($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：踢出九疑鼎协助者
	private function _onTimeOut_ShotOffHelpTripod($sessionID)
	{
		$retParam = new SRetParam_ShotOffHelpTripod;
		$this->onReturn_ShotOffHelpTripod(2, $retParam);
	}

	//返回处理：请求玩家九疑鼎的能被扇火、协助信息
	private function _doReturn_GetTripodStatus($data)
	{
		$retParam = new SRetParam_GetTripodStatus;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecStatus = STripodStatus::vectorFromStream($data); //玩家九疑鼎的扇火、协助状态
		$retParam->vecStatus = $vecStatus;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTripodStatus($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求玩家九疑鼎的能被扇火、协助信息
	private function _onTimeOut_GetTripodStatus($sessionID)
	{
		$retParam = new SRetParam_GetTripodStatus;
		$this->onReturn_GetTripodStatus(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 63;
		$this->_recvFuncList[0] = '_doRecv_UpdateTripod'; //FuncID: 1

		$this->_retFuncList[0] = '_doReturn_GetAllTripods'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_GetAllFires'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GetTripodData'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_ActiveTripod'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_UpgradeTripod'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_MakeFireTripod'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_ClearFireTripod'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_GetTripodAward'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_SpeedTripod'; //FuncID: 9
		$this->_retFuncList[9] = '_doReturn_AddTripodExtraSoul'; //FuncID: 10
		$this->_retFuncList[10] = '_doReturn_FighterHelpTripod'; //FuncID: 11
		$this->_retFuncList[11] = '_doReturn_UserHelpTripod'; //FuncID: 12
		$this->_retFuncList[12] = '_doReturn_ShotOffHelpTripod'; //FuncID: 13
		$this->_retFuncList[13] = '_doReturn_GetTripodStatus'; //FuncID: 14

		$this->_timeFuncList[0] = '_onTimeOut_GetAllTripods'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_GetAllFires'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GetTripodData'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_ActiveTripod'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_UpgradeTripod'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_MakeFireTripod'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_ClearFireTripod'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_GetTripodAward'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_SpeedTripod'; //FuncID: 9
		$this->_timeFuncList[9] = '_onTimeOut_AddTripodExtraSoul'; //FuncID: 10
		$this->_timeFuncList[10] = '_onTimeOut_FighterHelpTripod'; //FuncID: 11
		$this->_timeFuncList[11] = '_onTimeOut_UserHelpTripod'; //FuncID: 12
		$this->_timeFuncList[12] = '_onTimeOut_ShotOffHelpTripod'; //FuncID: 13
		$this->_timeFuncList[13] = '_onTimeOut_GetTripodStatus'; //FuncID: 14
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