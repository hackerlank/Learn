<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    LangHuanBlessProt.php
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class ELHBResult
{
	const eLHBResult_none = 0; //无此技能
	const eLHBResult_empty = 1; //次数用完
	const eLHBResult_inCD = 2; //技能CD中
	const eLHBResult_hasBuff = 3; //身上有Buff
	const eLHBResult_success = 4; //操作成功
	const eLHBResult_CMapError = 5; //创建地图失败
	const eLHBResult_enterMapError = 6; //进入地图失败
	const eLHBResult_otherError = 7; //其他错误
	const eLHBResult_lowLevel = 8; //玩家等级不够
	const eLHBResult_notBegin = 9; //活动未开始
	const eLHBResult_end = 10; //玩家已经结束
	const eLHBResult_wait5min = 11; //玩家逃跑需要等待5分钟
}

//活动状态
class ELHBState
{
	const eLHBState_none = 0; //无状态
	const eLHBState_alarm = 1; //警告
	const eLHBState_ready = 2; //报名开始
	const eLHBState_begin = 3; //活动开始
	const eLHBState_end = 4; //活动结束
}

//技能类型
class ELHBSkillType
{
	const eLHBSkillType_eNone = 0; //无技能
	const eLHBSkillType_eAskTaoism = 1; //问道技能
	const eLHBSkillType_eTalkTaoism = 2; //论道技能
	const eLHBSkillType_eWander = 3; //开小差技能
	const eLHBSkillType_eSit = 4; //打坐技能
	const eLHBSkillType_max = 5; //技能最大值
}

//技能信息
final class SLHBSkillInfo
{
	public $eLHBSkillType; //(枚举类型：ELHBSkillType)技能类型
	public $byCD; //(UINT8)技能CD
	public $wScore; //(UINT32)修为值
	public $byTimes; //(UINT8)使用次数

	//构造函数
	function __construct()
	{
		$this->eLHBSkillType = 0;
		$this->byCD = 0;
		$this->wScore = 0;
		$this->byTimes = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->eLHBSkillType = $this->eLHBSkillType;
		$obj->byCD = $this->byCD;
		$obj->wScore = $this->wScore;
		$obj->byTimes = $this->byTimes;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SLHBSkillInfo;
		$s->eLHBSkillType = ByteUtil::readUINT8($data);
		$s->byCD = ByteUtil::readUINT8($data);
		$s->wScore = ByteUtil::readUINT32($data);
		$s->byTimes = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SLHBSkillInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->eLHBSkillType);
		ByteUtil::writeUINT8($data, $this->byCD);
		ByteUtil::writeUINT32($data, $this->wScore);
		ByteUtil::writeUINT8($data, $this->byTimes);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//总的信息
final class SLHBTotalInfo
{
	public $byState; //(枚举类型：ELHBState)活动状态
	public $dwTime; //(UINT32)玩家持续时间
	public $dwXiuwei; //(UINT32)获得的修为值
	public $dwExp; //(UINT32)获得的经验值
	public $vecLHBSkillInfo; //(SLHBSkillInfo的数组)技能使用信息

	//构造函数
	function __construct()
	{
		$this->byState = 0;
		$this->dwTime = 0;
		$this->dwXiuwei = 0;
		$this->dwExp = 0;
		$this->vecLHBSkillInfo = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->byState = $this->byState;
		$obj->dwTime = $this->dwTime;
		$obj->dwXiuwei = $this->dwXiuwei;
		$obj->dwExp = $this->dwExp;
		$obj->vecLHBSkillInfo = $this->vecLHBSkillInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SLHBTotalInfo;
		$s->byState = ByteUtil::readUINT8($data);
		$s->dwTime = ByteUtil::readUINT32($data);
		$s->dwXiuwei = ByteUtil::readUINT32($data);
		$s->dwExp = ByteUtil::readUINT32($data);
		$s->vecLHBSkillInfo = SLHBSkillInfo::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SLHBTotalInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->byState);
		ByteUtil::writeUINT32($data, $this->dwTime);
		ByteUtil::writeUINT32($data, $this->dwXiuwei);
		ByteUtil::writeUINT32($data, $this->dwExp);
		SLHBSkillInfo::vectorToStream($data, $this->vecLHBSkillInfo);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[EnterMap:进入LangHuanBless地图]的返回的参数组成的结构体
class SRetParam_EnterMap
{
	public $eLHBResult; //(枚举类型：ELHBResult)结果

	//构造函数
	function __construct()
	{
		$this->eLHBResult = 0;
	}
};

//函数[SelectSkill:选择问道]的返回的参数组成的结构体
class SRetParam_SelectSkill
{
	public $eRetLHBSkillType; //(枚举类型：ELHBSkillType)返回使用技能
	public $eLHBResult; //(枚举类型：ELHBResult)结果

	//构造函数
	function __construct()
	{
		$this->eRetLHBSkillType = 0;
		$this->eLHBResult = 0;
	}
};

//函数[GetScore:获得的修为值]的返回的参数组成的结构体
class SRetParam_GetScore
{
	public $wScore; //(UINT32)修为值

	//构造函数
	function __construct()
	{
		$this->wScore = 0;
	}
};

//函数[GetSustainTime:获得游戏中持续时间]的返回的参数组成的结构体
class SRetParam_GetSustainTime
{
	public $dwTime; //(UINT32)时间值

	//构造函数
	function __construct()
	{
		$this->dwTime = 0;
	}
};

//函数[GetTotalInfo:获得玩家所有信息]的返回的参数组成的结构体
class SRetParam_GetTotalInfo
{
	public $sTotalInfo; //(类类型：SLHBTotalInfo)时间值
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->sTotalInfo = new SLHBTotalInfo;
		$this->bRet = false;
	}
};

//函数[GetSkillInfo:获得技能使用信息]的返回的参数组成的结构体
class SRetParam_GetSkillInfo
{
	public $vecLHBSkillInfo; //(SLHBSkillInfo的数组)技能使用信息
	public $eLHBResult; //(枚举类型：ELHBResult)结果

	//构造函数
	function __construct()
	{
		$this->vecLHBSkillInfo = array();
		$this->eLHBResult = 0;
	}
};

//函数[LeaveMap:离开LangHuanBless地图]的返回的参数组成的结构体
class SRetParam_LeaveMap
{
	public $eLHBResult; //(枚举类型：ELHBResult)结果

	//构造函数
	function __construct()
	{
		$this->eLHBResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：中午挂机活动
abstract class LangHuanBlessProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：进入LangHuanBless地图
	function send_EnterMap(
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

	//发送：选择问道
	function send_SelectSkill(
		$qwPlayerID,  //(UINT64)被选择的玩家
		$eLHBSkillType //(枚举类型：ELHBSkillType)技能类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwPlayerID);
		ByteUtil::writeUINT8($data, $eLHBSkillType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得的修为值
	function send_GetScore(
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

	//发送：获得游戏中持续时间
	function send_GetSustainTime(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得玩家所有信息
	function send_GetTotalInfo(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得技能使用信息
	function send_GetSkillInfo(
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

	//发送：离开LangHuanBless地图
	function send_LeaveMap(
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

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：挂机活动报名开始
	abstract function onRecv_EnrollNotify(
		$dwEnrollTime //(UINT32)开始时间
	);

	//接收：挂机活动开始
	abstract function onRecv_BeginNotify(
		$dwBeginTime //(UINT32)开始时间
	);

	//接收：发送经验值和修为值
	abstract function onRecv_PrizeNotify(
		$dwXiuwei, //(UINT32)修为值
		$dwExp //(UINT32)经验值
	);

	//接收：发送玩家在副本中的信息
	abstract function onRecv_TotalInfo(
		$qwPlayerID, //(UINT64)玩家ID
		$sTotalInfo //(类类型：SLHBTotalInfo)玩家信息
	);

	//接收：发送技能信息
	abstract function onRecv_SkillInfo(
		$qwAtkPlayerID, //(UINT64)攻击者
		$qwDfePlayerID, //(UINT64)被攻击者
		$eLHBSkillType //(枚举类型：ELHBSkillType)使用的技能ID
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：进入LangHuanBless地图
	abstract function onReturn_EnterMap(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_EnterMap)返回的参数
	);

	//返回：选择问道
	abstract function onReturn_SelectSkill(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SelectSkill)返回的参数
	);

	//返回：获得的修为值
	abstract function onReturn_GetScore(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetScore)返回的参数
	);

	//返回：获得游戏中持续时间
	abstract function onReturn_GetSustainTime(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetSustainTime)返回的参数
	);

	//返回：获得玩家所有信息
	abstract function onReturn_GetTotalInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTotalInfo)返回的参数
	);

	//返回：获得技能使用信息
	abstract function onReturn_GetSkillInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetSkillInfo)返回的参数
	);

	//返回：离开LangHuanBless地图
	abstract function onReturn_LeaveMap(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_LeaveMap)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：挂机活动报名开始
	private function _doRecv_EnrollNotify($data)
	{
		$dwEnrollTime = ByteUtil::readUINT32($data);
		return $this->onRecv_EnrollNotify($dwEnrollTime);
	}

	//接收处理：挂机活动开始
	private function _doRecv_BeginNotify($data)
	{
		$dwBeginTime = ByteUtil::readUINT32($data);
		return $this->onRecv_BeginNotify($dwBeginTime);
	}

	//接收处理：发送经验值和修为值
	private function _doRecv_PrizeNotify($data)
	{
		$dwXiuwei = ByteUtil::readUINT32($data);
		$dwExp = ByteUtil::readUINT32($data);
		return $this->onRecv_PrizeNotify($dwXiuwei, $dwExp);
	}

	//接收处理：发送玩家在副本中的信息
	private function _doRecv_TotalInfo($data)
	{
		$qwPlayerID = ByteUtil::readUINT64($data);
		$sTotalInfo = SLHBTotalInfo::fromStream($data);
		return $this->onRecv_TotalInfo($qwPlayerID, $sTotalInfo);
	}

	//接收处理：发送技能信息
	private function _doRecv_SkillInfo($data)
	{
		$qwAtkPlayerID = ByteUtil::readUINT64($data);
		$qwDfePlayerID = ByteUtil::readUINT64($data);
		$eLHBSkillType = ByteUtil::readUINT8($data);
		return $this->onRecv_SkillInfo($qwAtkPlayerID, $qwDfePlayerID, $eLHBSkillType);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：进入LangHuanBless地图
	private function _doReturn_EnterMap($data)
	{
		$retParam = new SRetParam_EnterMap;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eLHBResult = ByteUtil::readUINT8($data); //(枚举类型：ELHBResult)结果
		$retParam->eLHBResult = $eLHBResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_EnterMap($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：进入LangHuanBless地图
	private function _onTimeOut_EnterMap($sessionID)
	{
		$retParam = new SRetParam_EnterMap;
		$this->onReturn_EnterMap(2, $retParam);
	}

	//返回处理：选择问道
	private function _doReturn_SelectSkill($data)
	{
		$retParam = new SRetParam_SelectSkill;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRetLHBSkillType = ByteUtil::readUINT8($data); //(枚举类型：ELHBSkillType)返回使用技能
		$eLHBResult = ByteUtil::readUINT8($data); //(枚举类型：ELHBResult)结果
		$retParam->eRetLHBSkillType = $eRetLHBSkillType;
		$retParam->eLHBResult = $eLHBResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SelectSkill($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：选择问道
	private function _onTimeOut_SelectSkill($sessionID)
	{
		$retParam = new SRetParam_SelectSkill;
		$this->onReturn_SelectSkill(2, $retParam);
	}

	//返回处理：获得的修为值
	private function _doReturn_GetScore($data)
	{
		$retParam = new SRetParam_GetScore;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wScore = ByteUtil::readUINT32($data); //(无符号32位整数)修为值
		$retParam->wScore = $wScore;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetScore($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得的修为值
	private function _onTimeOut_GetScore($sessionID)
	{
		$retParam = new SRetParam_GetScore;
		$this->onReturn_GetScore(2, $retParam);
	}

	//返回处理：获得游戏中持续时间
	private function _doReturn_GetSustainTime($data)
	{
		$retParam = new SRetParam_GetSustainTime;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwTime = ByteUtil::readUINT32($data); //(无符号32位整数)时间值
		$retParam->dwTime = $dwTime;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetSustainTime($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得游戏中持续时间
	private function _onTimeOut_GetSustainTime($sessionID)
	{
		$retParam = new SRetParam_GetSustainTime;
		$this->onReturn_GetSustainTime(2, $retParam);
	}

	//返回处理：获得玩家所有信息
	private function _doReturn_GetTotalInfo($data)
	{
		$retParam = new SRetParam_GetTotalInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$sTotalInfo = SLHBTotalInfo::fromStream($data); //时间值
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->sTotalInfo = $sTotalInfo;
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTotalInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得玩家所有信息
	private function _onTimeOut_GetTotalInfo($sessionID)
	{
		$retParam = new SRetParam_GetTotalInfo;
		$this->onReturn_GetTotalInfo(2, $retParam);
	}

	//返回处理：获得技能使用信息
	private function _doReturn_GetSkillInfo($data)
	{
		$retParam = new SRetParam_GetSkillInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecLHBSkillInfo = SLHBSkillInfo::vectorFromStream($data); //技能使用信息
		$eLHBResult = ByteUtil::readUINT8($data); //(枚举类型：ELHBResult)结果
		$retParam->vecLHBSkillInfo = $vecLHBSkillInfo;
		$retParam->eLHBResult = $eLHBResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetSkillInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获得技能使用信息
	private function _onTimeOut_GetSkillInfo($sessionID)
	{
		$retParam = new SRetParam_GetSkillInfo;
		$this->onReturn_GetSkillInfo(2, $retParam);
	}

	//返回处理：离开LangHuanBless地图
	private function _doReturn_LeaveMap($data)
	{
		$retParam = new SRetParam_LeaveMap;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eLHBResult = ByteUtil::readUINT8($data); //(枚举类型：ELHBResult)结果
		$retParam->eLHBResult = $eLHBResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_LeaveMap($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：离开LangHuanBless地图
	private function _onTimeOut_LeaveMap($sessionID)
	{
		$retParam = new SRetParam_LeaveMap;
		$this->onReturn_LeaveMap(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 79;
		$this->_recvFuncList[0] = '_doRecv_EnrollNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_BeginNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_PrizeNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_TotalInfo'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_SkillInfo'; //FuncID: 5

		$this->_retFuncList[0] = '_doReturn_EnterMap'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_SelectSkill'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GetScore'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_GetSustainTime'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_GetTotalInfo'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_GetSkillInfo'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_LeaveMap'; //FuncID: 7

		$this->_timeFuncList[0] = '_onTimeOut_EnterMap'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_SelectSkill'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GetScore'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_GetSustainTime'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_GetTotalInfo'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_GetSkillInfo'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_LeaveMap'; //FuncID: 7
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