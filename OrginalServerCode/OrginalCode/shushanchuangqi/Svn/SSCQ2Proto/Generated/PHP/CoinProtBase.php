<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    CoinProt.php
//  Purpose:      888礼券协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class EResultInCoinProt
{
	const eCoinError = 0; //错误
	const eCoinGain = 1; //已经领取
	const eCoinSuccess = 2; //成功
}

//函数[GetCoinPacket:获取礼包]的返回的参数组成的结构体
class SRetParam_GetCoinPacket
{
	public $eResult; //(枚举类型：EResultInCoinProt)操作结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：888礼券协议
abstract class CoinProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取礼包
	function send_GetCoinPacket(
		$eType,  //(枚类型：ProtoCommon::EMoneyType)礼包类型
		$dwMoney //(UINT32)数量
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eType);
		ByteUtil::writeUINT32($data, $dwMoney);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取礼包
	abstract function onReturn_GetCoinPacket(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetCoinPacket)返回的参数
	);

	//返回处理：获取礼包
	private function _doReturn_GetCoinPacket($data)
	{
		$retParam = new SRetParam_GetCoinPacket;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EResultInCoinProt)操作结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetCoinPacket($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取礼包
	private function _onTimeOut_GetCoinPacket($sessionID)
	{
		$retParam = new SRetParam_GetCoinPacket;
		$this->onReturn_GetCoinPacket(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 91;

		$this->_retFuncList[0] = '_doReturn_GetCoinPacket'; //FuncID: 1

		$this->_timeFuncList[0] = '_onTimeOut_GetCoinPacket'; //FuncID: 1
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