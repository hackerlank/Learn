<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    BossProt.php
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//购买加持类型
class EBossBuyType
{
	const eGold = 0; //金币购买
	const eSliver = 1; //银币购买
}

//boss奖励类型
class EWorldBossPrize
{
	const eWorldBossPrizeTop = 1; //排名奖励
	const eWorldBossPrizeDamage = 2; //伤害奖励
	const eWorldBossPrizeRandom = 3; //幸运奖励
	const eWorldBossPrizeNPC = 4; //参与奖励
	const eWorldBossPrizeKillBoss = 5; //击杀世界boss奖励
	const eWorldBossPrizeBossHP = 6; //伤害boss百分比血量奖励
}

//排行帮信息
final class SPlayerInfo
{
	public $dwNo; //(UINT32)名次
	public $qwUserID; //(UINT64)uid
	public $strUserName; //(string)玩家名字
	public $dwDamageHP; //(UINT32)伤害的总血量
	public $dwBossMaxHP; //(UINT32)Boss的总血量

	//构造函数
	function __construct()
	{
		$this->dwNo = 0;
		$this->qwUserID = new Math_BigInteger;
		$this->strUserName = '';
		$this->dwDamageHP = 0;
		$this->dwBossMaxHP = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwNo = $this->dwNo;
		$obj->qwUserID = $this->qwUserID;
		$obj->strUserName = $this->strUserName;
		$obj->dwDamageHP = $this->dwDamageHP;
		$obj->dwBossMaxHP = $this->dwBossMaxHP;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPlayerInfo;
		$s->dwNo = ByteUtil::readUINT32($data);
		$s->qwUserID = ByteUtil::readUINT64($data);
		$s->strUserName = ByteUtil::readString($data);
		$s->dwDamageHP = ByteUtil::readUINT32($data);
		$s->dwBossMaxHP = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPlayerInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwNo);
		ByteUtil::writeUINT64($data, $this->qwUserID);
		ByteUtil::writeString($data, $this->strUserName);
		ByteUtil::writeUINT32($data, $this->dwDamageHP);
		ByteUtil::writeUINT32($data, $this->dwBossMaxHP);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//货币列表
final class SPrizeMoneyInfo
{
	public $dwMoneyType; //(UINT32)货币类型
	public $dwMoneyValue; //(UINT32)货币值

	//构造函数
	function __construct()
	{
		$this->dwMoneyType = 0;
		$this->dwMoneyValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwMoneyType = $this->dwMoneyType;
		$obj->dwMoneyValue = $this->dwMoneyValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPrizeMoneyInfo;
		$s->dwMoneyType = ByteUtil::readUINT32($data);
		$s->dwMoneyValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPrizeMoneyInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwMoneyType);
		ByteUtil::writeUINT32($data, $this->dwMoneyValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//货币列表
final class SPrizeIteminfo
{
	public $dwItemID; //(UINT32)物品id
	public $dwItemCount; //(UINT32)物品数量

	//构造函数
	function __construct()
	{
		$this->dwItemID = 0;
		$this->dwItemCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwItemID = $this->dwItemID;
		$obj->dwItemCount = $this->dwItemCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPrizeIteminfo;
		$s->dwItemID = ByteUtil::readUINT32($data);
		$s->dwItemCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPrizeIteminfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwItemID);
		ByteUtil::writeUINT32($data, $this->dwItemCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//排行帮信息
final class SPlayerPrize
{
	public $dwPrizeType; //(UINT8)奖励类型
	public $vecPrizeMoneyInfo; //(SPrizeMoneyInfo的数组)货币奖励
	public $vecPrizeItemInfo; //(SPrizeIteminfo的数组)物品奖励

	//构造函数
	function __construct()
	{
		$this->dwPrizeType = 0;
		$this->vecPrizeMoneyInfo = array();
		$this->vecPrizeItemInfo = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwPrizeType = $this->dwPrizeType;
		$obj->vecPrizeMoneyInfo = $this->vecPrizeMoneyInfo;
		$obj->vecPrizeItemInfo = $this->vecPrizeItemInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPlayerPrize;
		$s->dwPrizeType = ByteUtil::readUINT8($data);
		$s->vecPrizeMoneyInfo = SPrizeMoneyInfo::vectorFromStream($data);
		$s->vecPrizeItemInfo = SPrizeIteminfo::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPlayerPrize::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->dwPrizeType);
		SPrizeMoneyInfo::vectorToStream($data, $this->vecPrizeMoneyInfo);
		SPrizeIteminfo::vectorToStream($data, $this->vecPrizeItemInfo);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[WBAlive:世界BOSS中复活]的返回的参数组成的结构体
class SRetParam_WBAlive
{
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->bRet = false;
	}
};

//函数[WBStrength:加持]的返回的参数组成的结构体
class SRetParam_WBStrength
{
	public $dwSilverBufferCnt; //(UINT32)银币加持次数
	public $dwGoldBufferCnt; //(UINT32)金币加持次数
	public $dwSilverBufferCdTime; //(UINT32)银币加持cd
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->dwSilverBufferCnt = 0;
		$this->dwGoldBufferCnt = 0;
		$this->dwSilverBufferCdTime = 0;
		$this->bRet = false;
	}
};

//函数[WBAttack:直接攻击boss]的返回的参数组成的结构体
class SRetParam_WBAttack
{
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->bRet = false;
	}
};

//函数[EnterMap:进入boss地图]的返回的参数组成的结构体
class SRetParam_EnterMap
{
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->bRet = false;
	}
};

//函数[LeaveMap:离开boss地图]的返回的参数组成的结构体
class SRetParam_LeaveMap
{
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->bRet = false;
	}
};

////////////////////////////////////////////////////////////
//协议类：BOSS相关协议
abstract class BossProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：世界BOSS中复活
	function send_WBAlive(
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

	//发送：加持
	function send_WBStrength(
		$eBuyType //(枚举类型：EBossBuyType)购买类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eBuyType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：直接攻击boss
	function send_WBAttack(
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

	//发送：获取排行榜信息
	function send_GetTopList(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取玩家自己的排行榜信息
	function send_GetSelfInfo(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取boss信息
	function send_GetBossInfo(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：进入boss地图
	function send_EnterMap(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：离开boss地图
	function send_LeaveMap(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：世界BOSS信息通知
	abstract function onRecv_BossInfoNotify(
		$dwBoosID, //(UINT32)bossID
		$dwCurHP, //(UINT32)当前血量
		$dwMaxHP, //(UINT32)最大血量
		$dwPlayerCnt //(UINT32)当前地图人数
	);

	//接收：排行榜通知
	abstract function onRecv_TopListNotify(
		$vecTopList //(SPlayerInfo的数组)排行榜列表
	);

	//接收：个人信息通知
	abstract function onRecv_SelfInfoNotify(
		$oSelfInfo, //(类类型：SPlayerInfo)玩家信息
		$dwBeginTime, //(UINT32)开始时间
		$dwEndTime, //(UINT32)结束时间
		$dwReliveTime, //(UINT32)复活时间
		$dwSilverBufferCdTime, //(UINT32)银币加持cd
		$dwSilverBufferCnt, //(UINT32)银币加持次数
		$dwGoldBufferCnt, //(UINT32)金币加持次数
		$dwGoldAttackCnt //(UINT32)直接攻击次数
	);

	//接收：伤害boss信息
	abstract function onRecv_AtkInfoNotify(
		$dwDamage, //(UINT32)本次伤害
		$dwExp, //(UINT32)本次活动经验值
		$dwTotalDamage, //(UINT32)总伤害
		$dwBossMaxHp //(UINT32)boss最大血量
	);

	//接收：玩家名次变化通知
	abstract function onRecv_NoChangeNotify(
		$dwNo //(UINT32)玩家名次
	);

	//接收：玩家奖励获取通知
	abstract function onRecv_PrizeNotify(
		$vecPlayerPrize //(SPlayerPrize的数组)玩家奖励列表
	);

	//接收：玩家复活时间通知
	abstract function onRecv_ReliveTimeNotify(
		$dwReliveTime //(UINT32)复活时间
	);

	//接收：活动结束通知
	abstract function onRecv_EndNotify(
		$dwLeaveTime //(UINT32)离开时间
	);

	//接收：玩家直接攻击次数
	abstract function onRecv_AttackCountNotify(
		$dwAttackCount //(UINT16)玩家直接攻击次数
	);

	//接收：结算通知
	abstract function onRecv_GainPrizeNotify(
		$dwNo, //(UINT32)玩家名次
		$dwExp, //(UINT32)总共获得经验
		$bKillBoss //(bool)是否击杀boss
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：世界BOSS中复活
	abstract function onReturn_WBAlive(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_WBAlive)返回的参数
	);

	//返回：加持
	abstract function onReturn_WBStrength(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_WBStrength)返回的参数
	);

	//返回：直接攻击boss
	abstract function onReturn_WBAttack(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_WBAttack)返回的参数
	);

	//返回：进入boss地图
	abstract function onReturn_EnterMap(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_EnterMap)返回的参数
	);

	//返回：离开boss地图
	abstract function onReturn_LeaveMap(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_LeaveMap)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：世界BOSS信息通知
	private function _doRecv_BossInfoNotify($data)
	{
		$dwBoosID = ByteUtil::readUINT32($data);
		$dwCurHP = ByteUtil::readUINT32($data);
		$dwMaxHP = ByteUtil::readUINT32($data);
		$dwPlayerCnt = ByteUtil::readUINT32($data);
		return $this->onRecv_BossInfoNotify($dwBoosID, $dwCurHP, $dwMaxHP, $dwPlayerCnt);
	}

	//接收处理：排行榜通知
	private function _doRecv_TopListNotify($data)
	{
		$vecTopList = SPlayerInfo::vectorFromStream($data);
		return $this->onRecv_TopListNotify($vecTopList);
	}

	//接收处理：个人信息通知
	private function _doRecv_SelfInfoNotify($data)
	{
		$oSelfInfo = SPlayerInfo::fromStream($data);
		$dwBeginTime = ByteUtil::readUINT32($data);
		$dwEndTime = ByteUtil::readUINT32($data);
		$dwReliveTime = ByteUtil::readUINT32($data);
		$dwSilverBufferCdTime = ByteUtil::readUINT32($data);
		$dwSilverBufferCnt = ByteUtil::readUINT32($data);
		$dwGoldBufferCnt = ByteUtil::readUINT32($data);
		$dwGoldAttackCnt = ByteUtil::readUINT32($data);
		return $this->onRecv_SelfInfoNotify($oSelfInfo, $dwBeginTime, $dwEndTime, $dwReliveTime, $dwSilverBufferCdTime, $dwSilverBufferCnt, $dwGoldBufferCnt, $dwGoldAttackCnt);
	}

	//接收处理：伤害boss信息
	private function _doRecv_AtkInfoNotify($data)
	{
		$dwDamage = ByteUtil::readUINT32($data);
		$dwExp = ByteUtil::readUINT32($data);
		$dwTotalDamage = ByteUtil::readUINT32($data);
		$dwBossMaxHp = ByteUtil::readUINT32($data);
		return $this->onRecv_AtkInfoNotify($dwDamage, $dwExp, $dwTotalDamage, $dwBossMaxHp);
	}

	//接收处理：玩家名次变化通知
	private function _doRecv_NoChangeNotify($data)
	{
		$dwNo = ByteUtil::readUINT32($data);
		return $this->onRecv_NoChangeNotify($dwNo);
	}

	//接收处理：玩家奖励获取通知
	private function _doRecv_PrizeNotify($data)
	{
		$vecPlayerPrize = SPlayerPrize::vectorFromStream($data);
		return $this->onRecv_PrizeNotify($vecPlayerPrize);
	}

	//接收处理：玩家复活时间通知
	private function _doRecv_ReliveTimeNotify($data)
	{
		$dwReliveTime = ByteUtil::readUINT32($data);
		return $this->onRecv_ReliveTimeNotify($dwReliveTime);
	}

	//接收处理：活动结束通知
	private function _doRecv_EndNotify($data)
	{
		$dwLeaveTime = ByteUtil::readUINT32($data);
		return $this->onRecv_EndNotify($dwLeaveTime);
	}

	//接收处理：玩家直接攻击次数
	private function _doRecv_AttackCountNotify($data)
	{
		$dwAttackCount = ByteUtil::readUINT16($data);
		return $this->onRecv_AttackCountNotify($dwAttackCount);
	}

	//接收处理：结算通知
	private function _doRecv_GainPrizeNotify($data)
	{
		$dwNo = ByteUtil::readUINT32($data);
		$dwExp = ByteUtil::readUINT32($data);
		$bKillBoss = ByteUtil::readBool($data);
		return $this->onRecv_GainPrizeNotify($dwNo, $dwExp, $bKillBoss);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：世界BOSS中复活
	private function _doReturn_WBAlive($data)
	{
		$retParam = new SRetParam_WBAlive;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_WBAlive($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：世界BOSS中复活
	private function _onTimeOut_WBAlive($sessionID)
	{
		$retParam = new SRetParam_WBAlive;
		$this->onReturn_WBAlive(2, $retParam);
	}

	//返回处理：加持
	private function _doReturn_WBStrength($data)
	{
		$retParam = new SRetParam_WBStrength;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwSilverBufferCnt = ByteUtil::readUINT32($data); //(无符号32位整数)银币加持次数
		$dwGoldBufferCnt = ByteUtil::readUINT32($data); //(无符号32位整数)金币加持次数
		$dwSilverBufferCdTime = ByteUtil::readUINT32($data); //(无符号32位整数)银币加持cd
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->dwSilverBufferCnt = $dwSilverBufferCnt;
		$retParam->dwGoldBufferCnt = $dwGoldBufferCnt;
		$retParam->dwSilverBufferCdTime = $dwSilverBufferCdTime;
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_WBStrength($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：加持
	private function _onTimeOut_WBStrength($sessionID)
	{
		$retParam = new SRetParam_WBStrength;
		$this->onReturn_WBStrength(2, $retParam);
	}

	//返回处理：直接攻击boss
	private function _doReturn_WBAttack($data)
	{
		$retParam = new SRetParam_WBAttack;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_WBAttack($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：直接攻击boss
	private function _onTimeOut_WBAttack($sessionID)
	{
		$retParam = new SRetParam_WBAttack;
		$this->onReturn_WBAttack(2, $retParam);
	}

	//返回处理：进入boss地图
	private function _doReturn_EnterMap($data)
	{
		$retParam = new SRetParam_EnterMap;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_EnterMap($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：进入boss地图
	private function _onTimeOut_EnterMap($sessionID)
	{
		$retParam = new SRetParam_EnterMap;
		$this->onReturn_EnterMap(2, $retParam);
	}

	//返回处理：离开boss地图
	private function _doReturn_LeaveMap($data)
	{
		$retParam = new SRetParam_LeaveMap;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_LeaveMap($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：离开boss地图
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
		$this->_protID = 25;
		$this->_recvFuncList[0] = '_doRecv_BossInfoNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_TopListNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_SelfInfoNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_AtkInfoNotify'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_NoChangeNotify'; //FuncID: 5
		$this->_recvFuncList[5] = '_doRecv_PrizeNotify'; //FuncID: 6
		$this->_recvFuncList[6] = '_doRecv_ReliveTimeNotify'; //FuncID: 7
		$this->_recvFuncList[7] = '_doRecv_EndNotify'; //FuncID: 8
		$this->_recvFuncList[8] = '_doRecv_AttackCountNotify'; //FuncID: 9
		$this->_recvFuncList[9] = '_doRecv_GainPrizeNotify'; //FuncID: 10

		$this->_retFuncList[0] = '_doReturn_WBAlive'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_WBStrength'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_WBAttack'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_EnterMap'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_LeaveMap'; //FuncID: 5

		$this->_timeFuncList[0] = '_onTimeOut_WBAlive'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_WBStrength'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_WBAttack'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_EnterMap'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_LeaveMap'; //FuncID: 5
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