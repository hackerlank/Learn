<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    FightFormation.php
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('RoleInfoDefineBase.php');

/////////////////////以下为类型定义/////////////////////
//新阵型相关协议
class EFightFormationResult
{
	const eFightFormationResult_Succes = 0; //操作成功
	const eFightFormationResult_Fail = 1; //设置错误
}

//阵型信息
final class SBattlePosInfo
{
	public $qwInstID; //(UINT64)散仙唯一ID
	public $byPos; //(INT8)位置

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->byPos = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->byPos = $this->byPos;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SBattlePosInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->byPos = ByteUtil::readINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SBattlePosInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeINT8($data, $this->byPos);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//战斗阵型信息
final class FightFormationInfo
{
	public $wFormationID; //(UINT16)当前阵形ID
	public $vecBattlePosInfo; //(SBattlePosInfo的数组)位置

	//构造函数
	function __construct()
	{
		$this->wFormationID = 0;
		$this->vecBattlePosInfo = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wFormationID = $this->wFormationID;
		$obj->vecBattlePosInfo = $this->vecBattlePosInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new FightFormationInfo;
		$s->wFormationID = ByteUtil::readUINT16($data);
		$s->vecBattlePosInfo = SBattlePosInfo::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = FightFormationInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wFormationID);
		SBattlePosInfo::vectorToStream($data, $this->vecBattlePosInfo);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//战斗散仙信息
final class FightHeroInfo
{
	public $qwInstID; //(UINT64)散仙InstID
	public $dwHP; //(UINT32)当前生命值
	public $dwMaxHP; //(UINT32)最大生命值（可能用到）
	public $dwAura; //(UINT32)灵气值
	public $dwMaxAura; //(UINT32)最大灵气值

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->dwHP = 0;
		$this->dwMaxHP = 0;
		$this->dwAura = 0;
		$this->dwMaxAura = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->dwHP = $this->dwHP;
		$obj->dwMaxHP = $this->dwMaxHP;
		$obj->dwAura = $this->dwAura;
		$obj->dwMaxAura = $this->dwMaxAura;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new FightHeroInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->dwHP = ByteUtil::readUINT32($data);
		$s->dwMaxHP = ByteUtil::readUINT32($data);
		$s->dwAura = ByteUtil::readUINT32($data);
		$s->dwMaxAura = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = FightHeroInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT32($data, $this->dwHP);
		ByteUtil::writeUINT32($data, $this->dwMaxHP);
		ByteUtil::writeUINT32($data, $this->dwAura);
		ByteUtil::writeUINT32($data, $this->dwMaxAura);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GetFightFormation:取得阵形信息]的返回的参数组成的结构体
class SRetParam_GetFightFormation
{
	public $oFightFormation; //(类类型：FightFormationInfo)战斗阵形信息

	//构造函数
	function __construct()
	{
		$this->oFightFormation = new FightFormationInfo;
	}
};

//函数[SetFightFormation:设置阵形信息]的返回的参数组成的结构体
class SRetParam_SetFightFormation
{
	public $eRet; //(枚举类型：EFightFormationResult)操作结果

	//构造函数
	function __construct()
	{
		$this->eRet = 0;
	}
};

//函数[GetFightHeroInfo:战斗散仙信息]的返回的参数组成的结构体
class SRetParam_GetFightHeroInfo
{
	public $vecFightHeroInfo; //(FightHeroInfo的数组)战斗阵形信息

	//构造函数
	function __construct()
	{
		$this->vecFightHeroInfo = array();
	}
};

////////////////////////////////////////////////////////////
//协议类：新阵型相关协议
abstract class FightFormationBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：取得阵形信息
	function send_GetFightFormation(
		$wBattleType //(UINT16)战斗类型 EBattleType
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wBattleType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置阵形信息
	function send_SetFightFormation(
		$wBattleType,  //(UINT16)战斗类型
		$oFightFormation //(类类型：FightFormationInfo)阵形ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wBattleType);
		$oFightFormation->toStream($data);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：战斗散仙信息
	function send_GetFightHeroInfo(
		$wBattleType //(UINT16)战斗类型 EBattleType
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wBattleType);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：取得阵形信息
	abstract function onReturn_GetFightFormation(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetFightFormation)返回的参数
	);

	//返回：设置阵形信息
	abstract function onReturn_SetFightFormation(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SetFightFormation)返回的参数
	);

	//返回：战斗散仙信息
	abstract function onReturn_GetFightHeroInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetFightHeroInfo)返回的参数
	);

	//返回处理：取得阵形信息
	private function _doReturn_GetFightFormation($data)
	{
		$retParam = new SRetParam_GetFightFormation;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oFightFormation = FightFormationInfo::fromStream($data); //战斗阵形信息
		$retParam->oFightFormation = $oFightFormation;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetFightFormation($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取得阵形信息
	private function _onTimeOut_GetFightFormation($sessionID)
	{
		$retParam = new SRetParam_GetFightFormation;
		$this->onReturn_GetFightFormation(2, $retParam);
	}

	//返回处理：设置阵形信息
	private function _doReturn_SetFightFormation($data)
	{
		$retParam = new SRetParam_SetFightFormation;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EFightFormationResult)操作结果
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SetFightFormation($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置阵形信息
	private function _onTimeOut_SetFightFormation($sessionID)
	{
		$retParam = new SRetParam_SetFightFormation;
		$this->onReturn_SetFightFormation(2, $retParam);
	}

	//返回处理：战斗散仙信息
	private function _doReturn_GetFightHeroInfo($data)
	{
		$retParam = new SRetParam_GetFightHeroInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecFightHeroInfo = FightHeroInfo::vectorFromStream($data); //战斗阵形信息
		$retParam->vecFightHeroInfo = $vecFightHeroInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetFightHeroInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：战斗散仙信息
	private function _onTimeOut_GetFightHeroInfo($sessionID)
	{
		$retParam = new SRetParam_GetFightHeroInfo;
		$this->onReturn_GetFightHeroInfo(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 132;

		$this->_retFuncList[0] = '_doReturn_GetFightFormation'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_SetFightFormation'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GetFightHeroInfo'; //FuncID: 3

		$this->_timeFuncList[0] = '_onTimeOut_GetFightFormation'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_SetFightFormation'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GetFightHeroInfo'; //FuncID: 3
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