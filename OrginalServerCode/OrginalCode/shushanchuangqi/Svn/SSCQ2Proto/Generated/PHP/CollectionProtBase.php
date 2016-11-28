<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    CollectionProt.php
//  Purpose:      收藏协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//EDataType:eTypeCollectionInfo
final class SCollectionInfo
{
	public $qwRoleID; //(UINT64)角色ID
	public $wCollectionID; //(UINT16)收藏ID
	public $dwCount; //(UINT32)0是否完成
	public $dwProcess; //(UINT32)当前进度(持续型事件记录数据)
	public $dwFinishTime; //(UINT32)完成时间

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->wCollectionID = 0;
		$this->dwCount = 0;
		$this->dwProcess = 0;
		$this->dwFinishTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wCollectionID = $this->wCollectionID;
		$obj->dwCount = $this->dwCount;
		$obj->dwProcess = $this->dwProcess;
		$obj->dwFinishTime = $this->dwFinishTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SCollectionInfo;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wCollectionID = ByteUtil::readUINT16($data);
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
			$s = SCollectionInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wCollectionID);
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

//函数[GeCollectionInfo:获取收藏信息]的返回的参数组成的结构体
class SRetParam_GeCollectionInfo
{
	public $vecCollectionInfo; //(SCollectionInfo的数组)收藏榜信息
	public $wLevel; //(UINT16)收藏等级
	public $dwAP; //(UINT32)收藏点

	//构造函数
	function __construct()
	{
		$this->vecCollectionInfo = array();
		$this->wLevel = 0;
		$this->dwAP = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：收藏协议
abstract class CollectionProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：获取收藏信息
	function send_GeCollectionInfo(
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

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：收藏点通知
	abstract function onRecv_APNotify(
		$dwAP //(UINT32)收藏点
	);

	//接收：收藏等级通知
	abstract function onRecv_CollectionLevelNotify(
		$wLevel //(UINT16)收藏等级
	);

	//接收：收藏等级通知
	abstract function onRecv_CollectionInfoNotify(
		$oCollectionInfo //(类类型：SCollectionInfo)收藏信息
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：获取收藏信息
	abstract function onReturn_GeCollectionInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GeCollectionInfo)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：收藏点通知
	private function _doRecv_APNotify($data)
	{
		$dwAP = ByteUtil::readUINT32($data);
		return $this->onRecv_APNotify($dwAP);
	}

	//接收处理：收藏等级通知
	private function _doRecv_CollectionLevelNotify($data)
	{
		$wLevel = ByteUtil::readUINT16($data);
		return $this->onRecv_CollectionLevelNotify($wLevel);
	}

	//接收处理：收藏等级通知
	private function _doRecv_CollectionInfoNotify($data)
	{
		$oCollectionInfo = SCollectionInfo::fromStream($data);
		return $this->onRecv_CollectionInfoNotify($oCollectionInfo);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：获取收藏信息
	private function _doReturn_GeCollectionInfo($data)
	{
		$retParam = new SRetParam_GeCollectionInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecCollectionInfo = SCollectionInfo::vectorFromStream($data); //收藏榜信息
		$wLevel = ByteUtil::readUINT16($data); //(无符号16位整数)收藏等级
		$dwAP = ByteUtil::readUINT32($data); //(无符号32位整数)收藏点
		$retParam->vecCollectionInfo = $vecCollectionInfo;
		$retParam->wLevel = $wLevel;
		$retParam->dwAP = $dwAP;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GeCollectionInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取收藏信息
	private function _onTimeOut_GeCollectionInfo($sessionID)
	{
		$retParam = new SRetParam_GeCollectionInfo;
		$this->onReturn_GeCollectionInfo(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 78;
		$this->_recvFuncList[0] = '_doRecv_APNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_CollectionLevelNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_CollectionInfoNotify'; //FuncID: 3

		$this->_retFuncList[0] = '_doReturn_GeCollectionInfo'; //FuncID: 1

		$this->_timeFuncList[0] = '_onTimeOut_GeCollectionInfo'; //FuncID: 1
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