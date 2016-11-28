<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    AchievementProt.php
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//成就完成进度
class EAchievementRet
{
	const eAchievementRet_Sucess = 0; //成功
	const eAchievementRet_NotFinish = 1; //未完成
	const eAchievementRet_TakePrized = 2; //已领奖
	const eAchievementRet_ErrorCFG = 3; //配置错误
	const eAchievementRet_PackFull = 4; //包满
}

//成就完成进度
class EAchievementProcess
{
	const eAchievementProcess_Init = 0; //未完成
	const eAchievementProcess_Finish = 1; //已完成
	const eAchievementProcess_TakePrize = 2; //已领奖
}

//成就分享类型
class EAchievementShareType
{
	const eAchievementShareType_Invalid = 0; //无效类型
	const eAchievementShareType_Friend = 1; //qq好友分享
	const eAchievementShareType_Game = 2; //游戏内炫耀
}

//EDataType:eTypeAchievementInfo
final class SAchievementInfo
{
	public $qwRoleID; //(UINT64)角色ID
	public $wAchievementID; //(UINT16)成就ID
	public $dwCount; //(UINT32)EAchievementProcess类型成就完成进度
	public $dwProcess; //(UINT32)当前进度(持续型事件记录数据)
	public $dwFinishTime; //(UINT32)完成时间

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->wAchievementID = 0;
		$this->dwCount = 0;
		$this->dwProcess = 0;
		$this->dwFinishTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wAchievementID = $this->wAchievementID;
		$obj->dwCount = $this->dwCount;
		$obj->dwProcess = $this->dwProcess;
		$obj->dwFinishTime = $this->dwFinishTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SAchievementInfo;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wAchievementID = ByteUtil::readUINT16($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		$s->dwProcess = ByteUtil::readUINT32($data);
		$s->dwFinishTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SAchievementInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wAchievementID);
		ByteUtil::writeUINT32($data, $this->dwCount);
		ByteUtil::writeUINT32($data, $this->dwProcess);
		ByteUtil::writeUINT32($data, $this->dwFinishTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//成就分享列表
final class SAchievementShare
{
	public $wAchievementID; //(UINT16)成就ID
	public $eProcess; //(枚举类型：EAchievementProcess)分享状态

	//构造函数
	function __construct()
	{
		$this->wAchievementID = 0;
		$this->eProcess = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wAchievementID = $this->wAchievementID;
		$obj->eProcess = $this->eProcess;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SAchievementShare;
		$s->wAchievementID = ByteUtil::readUINT16($data);
		$s->eProcess = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SAchievementShare::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wAchievementID);
		ByteUtil::writeUINT8($data, $this->eProcess);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GeAchievementInfo:获取成就信息]的返回的参数组成的结构体
class SRetParam_GeAchievementInfo
{
	public $vecAchievementInfo; //(SAchievementInfo的数组)成就榜信息
	public $wLevel; //(UINT16)成就等级
	public $dwAP; //(UINT32)成就点

	//构造函数
	function __construct()
	{
		$this->vecAchievementInfo = array();
		$this->wLevel = 0;
		$this->dwAP = 0;
	}
};

//函数[TakePrize:获取成就奖励]的返回的参数组成的结构体
class SRetParam_TakePrize
{
	public $eRet; //(枚举类型：EAchievementRet)结果

	//构造函数
	function __construct()
	{
		$this->eRet = 0;
	}
};

//函数[GeAchievementShareList:获取成就分享信息]的返回的参数组成的结构体
class SRetParam_GeAchievementShareList
{
	public $vecAchievementShare; //(SAchievementShare的数组)成就分享信息

	//构造函数
	function __construct()
	{
		$this->vecAchievementShare = array();
	}
};

//函数[TakeSharePrize:获取成就分享奖励]的返回的参数组成的结构体
class SRetParam_TakeSharePrize
{
	public $eRet; //(枚举类型：EAchievementRet)结果

	//构造函数
	function __construct()
	{
		$this->eRet = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：成就相关协议
abstract class AchievementProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取成就信息
	function send_GeAchievementInfo(
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

	//发送：获取成就奖励
	function send_TakePrize(
		$wAchievementID //(UINT16)成就ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wAchievementID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取成就分享信息
	function send_GeAchievementShareList(
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

	//发送：获取成就分享奖励
	function send_TakeSharePrize(
		$wAchievementID //(UINT16)成就ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wAchievementID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：成就点通知
	abstract function onRecv_APNotify(
		$dwAP //(UINT32)成就点
	);

	//接收：成就等级通知
	abstract function onRecv_AchievementLevelNotify(
		$wLevel //(UINT16)成就等级
	);

	//接收：成就等级通知
	abstract function onRecv_AchievementInfoNotify(
		$oAchievementInfo //(类类型：SAchievementInfo)成就信息
	);

	//接收：成就分享通知
	abstract function onRecv_AchievementShareNotify(
		$oAchievementShare //(类类型：SAchievementShare)成就分享信息
	);

	//接收：零点通知
	abstract function onRecv_MidnightNotify(
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取成就信息
	abstract function onReturn_GeAchievementInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GeAchievementInfo)返回的参数
	);

	//返回：获取成就奖励
	abstract function onReturn_TakePrize(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TakePrize)返回的参数
	);

	//返回：获取成就分享信息
	abstract function onReturn_GeAchievementShareList(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GeAchievementShareList)返回的参数
	);

	//返回：获取成就分享奖励
	abstract function onReturn_TakeSharePrize(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TakeSharePrize)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：成就点通知
	private function _doRecv_APNotify($data)
	{
		$dwAP = ByteUtil::readUINT32($data);
		return $this->onRecv_APNotify($dwAP);
	}

	//接收处理：成就等级通知
	private function _doRecv_AchievementLevelNotify($data)
	{
		$wLevel = ByteUtil::readUINT16($data);
		return $this->onRecv_AchievementLevelNotify($wLevel);
	}

	//接收处理：成就等级通知
	private function _doRecv_AchievementInfoNotify($data)
	{
		$oAchievementInfo = SAchievementInfo::fromStream($data);
		return $this->onRecv_AchievementInfoNotify($oAchievementInfo);
	}

	//接收处理：成就分享通知
	private function _doRecv_AchievementShareNotify($data)
	{
		$oAchievementShare = SAchievementShare::fromStream($data);
		return $this->onRecv_AchievementShareNotify($oAchievementShare);
	}

	//接收处理：零点通知
	private function _doRecv_MidnightNotify($data)
	{
		return $this->onRecv_MidnightNotify();
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：获取成就信息
	private function _doReturn_GeAchievementInfo($data)
	{
		$retParam = new SRetParam_GeAchievementInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecAchievementInfo = SAchievementInfo::vectorFromStream($data); //成就榜信息
		$wLevel = ByteUtil::readUINT16($data); //(无符号16位整数)成就等级
		$dwAP = ByteUtil::readUINT32($data); //(无符号32位整数)成就点
		$retParam->vecAchievementInfo = $vecAchievementInfo;
		$retParam->wLevel = $wLevel;
		$retParam->dwAP = $dwAP;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GeAchievementInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取成就信息
	private function _onTimeOut_GeAchievementInfo($sessionID)
	{
		$retParam = new SRetParam_GeAchievementInfo;
		$this->onReturn_GeAchievementInfo(2, $retParam);
	}

	//返回处理：获取成就奖励
	private function _doReturn_TakePrize($data)
	{
		$retParam = new SRetParam_TakePrize;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EAchievementRet)结果
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakePrize($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取成就奖励
	private function _onTimeOut_TakePrize($sessionID)
	{
		$retParam = new SRetParam_TakePrize;
		$this->onReturn_TakePrize(2, $retParam);
	}

	//返回处理：获取成就分享信息
	private function _doReturn_GeAchievementShareList($data)
	{
		$retParam = new SRetParam_GeAchievementShareList;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecAchievementShare = SAchievementShare::vectorFromStream($data); //成就分享信息
		$retParam->vecAchievementShare = $vecAchievementShare;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GeAchievementShareList($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取成就分享信息
	private function _onTimeOut_GeAchievementShareList($sessionID)
	{
		$retParam = new SRetParam_GeAchievementShareList;
		$this->onReturn_GeAchievementShareList(2, $retParam);
	}

	//返回处理：获取成就分享奖励
	private function _doReturn_TakeSharePrize($data)
	{
		$retParam = new SRetParam_TakeSharePrize;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EAchievementRet)结果
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakeSharePrize($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取成就分享奖励
	private function _onTimeOut_TakeSharePrize($sessionID)
	{
		$retParam = new SRetParam_TakeSharePrize;
		$this->onReturn_TakeSharePrize(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 75;
		$this->_recvFuncList[0] = '_doRecv_APNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_AchievementLevelNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_AchievementInfoNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_AchievementShareNotify'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_MidnightNotify'; //FuncID: 5

		$this->_retFuncList[0] = '_doReturn_GeAchievementInfo'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_TakePrize'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_GeAchievementShareList'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_TakeSharePrize'; //FuncID: 4

		$this->_timeFuncList[0] = '_onTimeOut_GeAchievementInfo'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_TakePrize'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_GeAchievementShareList'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_TakeSharePrize'; //FuncID: 4
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