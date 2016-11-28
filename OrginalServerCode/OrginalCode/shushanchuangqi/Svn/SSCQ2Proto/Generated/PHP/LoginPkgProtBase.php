<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    LoginPkgProt.php
//  Purpose:      累计登入礼包协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class EResultInLoginProt
{
	const ePkgError = 0; //错误
	const ePkgGain = 1; //已经领取
	const ePkgFull = 2; //背包已满
	const ePkgSuccess = 3; //成功
}

//函数[GetLoginPkg:获取礼包]的返回的参数组成的结构体
class SRetParam_GetLoginPkg
{
	public $wResult; //(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
	public $eResult; //(枚举类型：EResultInLoginProt)操作结果

	//构造函数
	function __construct()
	{
		$this->wResult = 0;
		$this->eResult = 0;
	}
};

//函数[GetPkgInfo:登入礼包信息]的返回的参数组成的结构体
class SRetParam_GetPkgInfo
{
	public $wDays; //(UINT16)连续登入的天数
	public $wResult; //(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领

	//构造函数
	function __construct()
	{
		$this->wDays = 0;
		$this->wResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：累计登入礼包协议
abstract class LoginPkgProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取礼包
	function send_GetLoginPkg(
		$byIndex //(UINT8)累计天数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：登入礼包信息
	function send_GetPkgInfo(
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

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：登入礼包信息
	abstract function onRecv_SendPkgInfo(
		$wDays, //(UINT16)连续登入的天数
		$wResult //(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取礼包
	abstract function onReturn_GetLoginPkg(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetLoginPkg)返回的参数
	);

	//返回：登入礼包信息
	abstract function onReturn_GetPkgInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetPkgInfo)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：登入礼包信息
	private function _doRecv_SendPkgInfo($data)
	{
		$wDays = ByteUtil::readUINT16($data);
		$wResult = ByteUtil::readUINT16($data);
		return $this->onRecv_SendPkgInfo($wDays, $wResult);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：获取礼包
	private function _doReturn_GetLoginPkg($data)
	{
		$retParam = new SRetParam_GetLoginPkg;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wResult = ByteUtil::readUINT16($data); //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EResultInLoginProt)操作结果
		$retParam->wResult = $wResult;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetLoginPkg($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取礼包
	private function _onTimeOut_GetLoginPkg($sessionID)
	{
		$retParam = new SRetParam_GetLoginPkg;
		$this->onReturn_GetLoginPkg(2, $retParam);
	}

	//返回处理：登入礼包信息
	private function _doReturn_GetPkgInfo($data)
	{
		$retParam = new SRetParam_GetPkgInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$wDays = ByteUtil::readUINT16($data); //(无符号16位整数)连续登入的天数
		$wResult = ByteUtil::readUINT16($data); //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
		$retParam->wDays = $wDays;
		$retParam->wResult = $wResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetPkgInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：登入礼包信息
	private function _onTimeOut_GetPkgInfo($sessionID)
	{
		$retParam = new SRetParam_GetPkgInfo;
		$this->onReturn_GetPkgInfo(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 92;
		$this->_recvFuncList[0] = '_doRecv_SendPkgInfo'; //FuncID: 1

		$this->_retFuncList[0] = '_doReturn_GetLoginPkg'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_GetPkgInfo'; //FuncID: 2

		$this->_timeFuncList[0] = '_onTimeOut_GetLoginPkg'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_GetPkgInfo'; //FuncID: 2
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