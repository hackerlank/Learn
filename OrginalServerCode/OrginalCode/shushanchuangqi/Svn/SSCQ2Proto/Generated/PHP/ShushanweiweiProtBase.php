<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    ShushanweiweiProt.php
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class EPkgResult
{
	const ePackError = 0; //错误
	const ePackGain = 1; //已经领取
	const ePackFull = 2; //背包已满
	const ePackSuccess = 3; //成功
}

//领奖类型
class EPkgType
{
	const eWeibo = 0; //微博
	const eWeixin = 1; //微信
	const eMax = 2; //最大值
}

//奖励信息
final class SPrizeInfo
{
	public $eType; //(枚举类型：EPkgType)奖励类型
	public $dwCount; //(UINT32)当前人数
	public $bListen; //(bool)微博是否收听
	public $bResult; //(bool)个人奖励是否领取
	public $wResult; //(UINT16)全服奖励领取结果

	//构造函数
	function __construct()
	{
		$this->eType = 0;
		$this->dwCount = 0;
		$this->bListen = false;
		$this->bResult = false;
		$this->wResult = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->eType = $this->eType;
		$obj->dwCount = $this->dwCount;
		$obj->bListen = $this->bListen;
		$obj->bResult = $this->bResult;
		$obj->wResult = $this->wResult;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPrizeInfo;
		$s->eType = ByteUtil::readUINT8($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		$s->bListen = ByteUtil::readBool($data);
		$s->bResult = ByteUtil::readBool($data);
		$s->wResult = ByteUtil::readUINT16($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPrizeInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->eType);
		ByteUtil::writeUINT32($data, $this->dwCount);
		ByteUtil::writeBool($data, $this->bListen);
		ByteUtil::writeBool($data, $this->bResult);
		ByteUtil::writeUINT16($data, $this->wResult);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[TakePrize:获取礼包]的返回的参数组成的结构体
class SRetParam_TakePrize
{
	public $eRetType; //(枚举类型：EPkgType)活动类型返回
	public $wRetIndex; //(UINT16)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
	public $eRet; //(枚举类型：EPkgResult)操作结果返回

	//构造函数
	function __construct()
	{
		$this->eRetType = 0;
		$this->wRetIndex = 0;
		$this->eRet = 0;
	}
};

//函数[ListenWeibo:收听微博]的返回的参数组成的结构体
class SRetParam_ListenWeibo
{
	public $eRet; //(枚举类型：EPkgResult)操作结果返回

	//构造函数
	function __construct()
	{
		$this->eRet = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：蜀山微微协议
abstract class ShushanweiweiProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取礼包
	function send_TakePrize(
		$eType,  //(枚举类型：EPkgType)活动类型
		$wIndex,  //(UINT16)领奖类型：0表示个人奖励，1..16位 表示领取全服第几个奖励
		$strCDK //(string)CDK
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eType);
		ByteUtil::writeUINT16($data, $wIndex);
		ByteUtil::writeString($data, $strCDK);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获得玩家奖励信息
	function send_GetPrizeInfo(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：收听微博
	function send_ListenWeibo(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：同步玩家奖励信息
	abstract function onRecv_SyncPrizeInfo(
		$vecResult //(SPrizeInfo的数组)奖励结果
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取礼包
	abstract function onReturn_TakePrize(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TakePrize)返回的参数
	);

	//返回：收听微博
	abstract function onReturn_ListenWeibo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ListenWeibo)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：同步玩家奖励信息
	private function _doRecv_SyncPrizeInfo($data)
	{
		$vecResult = SPrizeInfo::vectorFromStream($data);
		return $this->onRecv_SyncPrizeInfo($vecResult);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：获取礼包
	private function _doReturn_TakePrize($data)
	{
		$retParam = new SRetParam_TakePrize;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRetType = ByteUtil::readUINT8($data); //(枚举类型：EPkgType)活动类型返回
		$wRetIndex = ByteUtil::readUINT16($data); //(无符号16位整数)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EPkgResult)操作结果返回
		$retParam->eRetType = $eRetType;
		$retParam->wRetIndex = $wRetIndex;
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakePrize($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取礼包
	private function _onTimeOut_TakePrize($sessionID)
	{
		$retParam = new SRetParam_TakePrize;
		$this->onReturn_TakePrize(2, $retParam);
	}

	//返回处理：收听微博
	private function _doReturn_ListenWeibo($data)
	{
		$retParam = new SRetParam_ListenWeibo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eRet = ByteUtil::readUINT8($data); //(枚举类型：EPkgResult)操作结果返回
		$retParam->eRet = $eRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ListenWeibo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：收听微博
	private function _onTimeOut_ListenWeibo($sessionID)
	{
		$retParam = new SRetParam_ListenWeibo;
		$this->onReturn_ListenWeibo(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 93;
		$this->_recvFuncList[0] = '_doRecv_SyncPrizeInfo'; //FuncID: 1

		$this->_retFuncList[0] = '_doReturn_TakePrize'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_ListenWeibo'; //FuncID: 2

		$this->_timeFuncList[0] = '_onTimeOut_TakePrize'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_ListenWeibo'; //FuncID: 2
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