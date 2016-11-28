<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    ExchangeShopProt.php
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//兑换商店错误码
class EExchangeShop
{
	const eExchangeShop_Sucess = 0; //成功
	const eExchangeShop_CfgLimit = 1; //没有该兑换商品
	const eExchangeShop_MoneyLimit = 2; //钱不够
	const eExchangeShop_CondLimit = 3; //购买条件不满足
	const eExchangeShop_CountLimit = 4; //购买数量限制
	const eExchangeShop_ErrorItemID = 5; //物品配置找不到
	const eExchangeShop_ErrorPack = 6; //背包满无法添加物品
}

//已兑换信息列表
final class ExchangeInfo
{
	public $qwRoleID; //(UINT64)角色ID
	public $dwExchangeID; //(UINT32)兑换ID
	public $dwCount; //(UINT32)已兑换次数
	public $dwFinishTime; //(UINT32)兑换时间

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->dwExchangeID = 0;
		$this->dwCount = 0;
		$this->dwFinishTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->dwExchangeID = $this->dwExchangeID;
		$obj->dwCount = $this->dwCount;
		$obj->dwFinishTime = $this->dwFinishTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new ExchangeInfo;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->dwExchangeID = ByteUtil::readUINT32($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		$s->dwFinishTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = ExchangeInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT32($data, $this->dwExchangeID);
		ByteUtil::writeUINT32($data, $this->dwCount);
		ByteUtil::writeUINT32($data, $this->dwFinishTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[ExchangeItem:兑换物品]的返回的参数组成的结构体
class SRetParam_ExchangeItem
{
	public $dwRet; //(UINT32)结果

	//构造函数
	function __construct()
	{
		$this->dwRet = 0;
	}
};

//函数[ExchangeItemList:已兑换列表]的返回的参数组成的结构体
class SRetParam_ExchangeItemList
{
	public $vecExchangeInfo; //(ExchangeInfo的数组)已兑换列表

	//构造函数
	function __construct()
	{
		$this->vecExchangeInfo = array();
	}
};

////////////////////////////////////////////////////////////
//协议类：兑换商店
abstract class ExchangeShopProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：兑换物品
	function send_ExchangeItem(
		$dwExchangeID,  //(UINT32)兑换id
		$dwCount //(UINT32)兑换数量
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT32($data, $dwExchangeID);
		ByteUtil::writeUINT32($data, $dwCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：已兑换列表
	function send_ExchangeItemList(
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
	//接收：已兑换信息更新
	abstract function onRecv_ExchangeItemUpdate(
		$oExchangeInfo //(类类型：ExchangeInfo)更新已兑换信息
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：兑换物品
	abstract function onReturn_ExchangeItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ExchangeItem)返回的参数
	);

	//返回：已兑换列表
	abstract function onReturn_ExchangeItemList(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ExchangeItemList)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：已兑换信息更新
	private function _doRecv_ExchangeItemUpdate($data)
	{
		$oExchangeInfo = ExchangeInfo::fromStream($data);
		return $this->onRecv_ExchangeItemUpdate($oExchangeInfo);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：兑换物品
	private function _doReturn_ExchangeItem($data)
	{
		$retParam = new SRetParam_ExchangeItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwRet = ByteUtil::readUINT32($data); //(无符号32位整数)结果
		$retParam->dwRet = $dwRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ExchangeItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：兑换物品
	private function _onTimeOut_ExchangeItem($sessionID)
	{
		$retParam = new SRetParam_ExchangeItem;
		$this->onReturn_ExchangeItem(2, $retParam);
	}

	//返回处理：已兑换列表
	private function _doReturn_ExchangeItemList($data)
	{
		$retParam = new SRetParam_ExchangeItemList;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecExchangeInfo = ExchangeInfo::vectorFromStream($data); //已兑换列表
		$retParam->vecExchangeInfo = $vecExchangeInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ExchangeItemList($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：已兑换列表
	private function _onTimeOut_ExchangeItemList($sessionID)
	{
		$retParam = new SRetParam_ExchangeItemList;
		$this->onReturn_ExchangeItemList(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 101;
		$this->_recvFuncList[0] = '_doRecv_ExchangeItemUpdate'; //FuncID: 1

		$this->_retFuncList[0] = '_doReturn_ExchangeItem'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_ExchangeItemList'; //FuncID: 2

		$this->_timeFuncList[0] = '_onTimeOut_ExchangeItem'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_ExchangeItemList'; //FuncID: 2
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