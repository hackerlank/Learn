<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    YelloDiamondProt.php
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//操作结果
class EOpResult
{
	const eOtherError = 0; //其他错误
	const eShortLevel = 1; //等级不够
	const eNotActive = 2; //未开通QQ黄钻
	const eNotYear = 3; //未开通年费黄钻贵族
	const eNotLuxury = 4; //未开通QQ豪华黄钻
	const eAreadyGain = 5; //已经领取
	const eBagFull = 6; //背包空间不足
	const eSuccess = 7; //操作成功
}

//礼包类型
class EBagType
{
	const EBagType_eNone = 0; //无礼包可领取
	const EBagType_eDayBag = 1; //黄钻日常礼包
	const EBagType_eYearBag = 2; //年黄钻礼包
	const EBagType_eLuxuryBag = 3; //豪华QQ黄钻礼包
	const EBagType_eNewBag = 4; //新手礼包
	const EBagType_eGrowBag = 5; //成长礼包
	const EBagType_eHorseBag = 6; //座机礼包
	const EBagType_eMax = 7; //最大值
}

//QQ黄钻类型
class EYDType
{
	const EYDType_eNone = 0; //未开通QQ黄钻
	const EYDType_eDayType = 1; //普通QQ黄钻
	const EYDType_eYearType = 2; //年QQ黄钻
	const EYDType_eLuxuryType = 3; //豪华QQ黄钻
}

//QQ黄钻信息
final class SYDInfo
{
	public $bGainDayBag; //(bool)是否领取每日礼包
	public $bGainYearBag; //(bool)是否领取年费礼包
	public $bGainLuxuryBag; //(bool)是否领取豪华礼包
	public $bGainHorseBag; //(bool)是否领取座机礼包
	public $dGrowBag; //(UINT16)已领取成长礼包等级 从低位开始向高位 1表示领取，0表示未领取
	public $bGainNewBag; //(bool)是否领取新手礼包

	//构造函数
	function __construct()
	{
		$this->bGainDayBag = false;
		$this->bGainYearBag = false;
		$this->bGainLuxuryBag = false;
		$this->bGainHorseBag = false;
		$this->dGrowBag = 0;
		$this->bGainNewBag = false;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->bGainDayBag = $this->bGainDayBag;
		$obj->bGainYearBag = $this->bGainYearBag;
		$obj->bGainLuxuryBag = $this->bGainLuxuryBag;
		$obj->bGainHorseBag = $this->bGainHorseBag;
		$obj->dGrowBag = $this->dGrowBag;
		$obj->bGainNewBag = $this->bGainNewBag;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SYDInfo;
		$s->bGainDayBag = ByteUtil::readBool($data);
		$s->bGainYearBag = ByteUtil::readBool($data);
		$s->bGainLuxuryBag = ByteUtil::readBool($data);
		$s->bGainHorseBag = ByteUtil::readBool($data);
		$s->dGrowBag = ByteUtil::readUINT16($data);
		$s->bGainNewBag = ByteUtil::readBool($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SYDInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeBool($data, $this->bGainDayBag);
		ByteUtil::writeBool($data, $this->bGainYearBag);
		ByteUtil::writeBool($data, $this->bGainLuxuryBag);
		ByteUtil::writeBool($data, $this->bGainHorseBag);
		ByteUtil::writeUINT16($data, $this->dGrowBag);
		ByteUtil::writeBool($data, $this->bGainNewBag);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GainYDBag:获取黄钻礼包]的返回的参数组成的结构体
class SRetParam_GainYDBag
{
	public $eOpResult; //(枚举类型：EOpResult)操作结果

	//构造函数
	function __construct()
	{
		$this->eOpResult = 0;
	}
};

//函数[GetYDBagInfo:获取黄钻礼包领取信息]的返回的参数组成的结构体
class SRetParam_GetYDBagInfo
{
	public $ydInfo; //(类类型：SYDInfo)黄钻信息

	//构造函数
	function __construct()
	{
		$this->ydInfo = new SYDInfo;
	}
};

////////////////////////////////////////////////////////////
//协议类：QQ黄钻协议
abstract class YelloDiamondProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取黄钻礼包
	function send_GainYDBag(
		$eBagType,  //(枚举类型：EBagType)礼包类型
		$dLevel //(UINT16)玩家等级成长礼包
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eBagType);
		ByteUtil::writeUINT16($data, $dLevel);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取黄钻礼包领取信息
	function send_GetYDBagInfo(
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

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取黄钻礼包
	abstract function onReturn_GainYDBag(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GainYDBag)返回的参数
	);

	//返回：获取黄钻礼包领取信息
	abstract function onReturn_GetYDBagInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetYDBagInfo)返回的参数
	);

	//返回处理：获取黄钻礼包
	private function _doReturn_GainYDBag($data)
	{
		$retParam = new SRetParam_GainYDBag;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eOpResult = ByteUtil::readUINT8($data); //(枚举类型：EOpResult)操作结果
		$retParam->eOpResult = $eOpResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GainYDBag($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取黄钻礼包
	private function _onTimeOut_GainYDBag($sessionID)
	{
		$retParam = new SRetParam_GainYDBag;
		$this->onReturn_GainYDBag(2, $retParam);
	}

	//返回处理：获取黄钻礼包领取信息
	private function _doReturn_GetYDBagInfo($data)
	{
		$retParam = new SRetParam_GetYDBagInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$ydInfo = SYDInfo::fromStream($data); //黄钻信息
		$retParam->ydInfo = $ydInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetYDBagInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取黄钻礼包领取信息
	private function _onTimeOut_GetYDBagInfo($sessionID)
	{
		$retParam = new SRetParam_GetYDBagInfo;
		$this->onReturn_GetYDBagInfo(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 200;

		$this->_retFuncList[0] = '_doReturn_GainYDBag'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_GetYDBagInfo'; //FuncID: 2

		$this->_timeFuncList[0] = '_onTimeOut_GainYDBag'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_GetYDBagInfo'; //FuncID: 2
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