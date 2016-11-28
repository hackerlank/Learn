<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    Formation.php
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('RoleInfoDefineBase.php');

/////////////////////以下为类型定义/////////////////////
//阵型解锁属性
class EFormationAttr
{
	const eFormAttrNone = 0; //无加成
	const eFormAttrSpeed = 1; //身法
	const eFormAttrHit = 2; //命中
	const eFormAttrEva = 3; //闪避
	const eFormAttrCrit = 4; //暴击
	const eFormAttrAntiCrit = 5; //抗暴
	const eFormAttrCount = 6; //反击
	const eFormAttrAntiCount = 7; //抵抗
	const eFormAttrAp = 8; //破击
	const eFormAttrMax = 9; //最大
}

//阵形、阵灵、兽魂操作结果
class EFormPetType
{
	const eFormPetSucc = 0; //成功
	const eFormPetFalied = 1; //失败
	const eFormPetMainFighterErr = 2; //主将不能下阵
	const eFormPetItemErr = 3; //解锁道具不足
	const eFormPetPetLevelItemErr = 4; //阵灵升级道具不足
}

//兽魂操作返回结果
class EBeastSoulResult
{
	const eBeastSoulSucces = 0; //操作成功
	const eBeastSoulFailed = 1; //操作失败
	const eBeastSoulLackOfMoney = 2; //对应货币不足
	const eBeastSoulRankMax = 3; //已经是最大等级
	const eBeastSoulLevelLimit = 4; //玩家等级不足
}

//阵型信息
final class SLineup
{
	public $qwInstID; //(UINT64)散仙唯一ID
	public $iPos; //(INT32)位置

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->iPos = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->iPos = $this->iPos;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SLineup;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->iPos = ByteUtil::readINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SLineup::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeINT32($data, $this->iPos);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//兽魂奖励道具信息
final class SBeastSoulItem
{
	public $wItemID; //(UINT16)模板ID
	public $dwCount; //(UINT32)数量

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->dwCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->dwCount = $this->dwCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SBeastSoulItem;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SBeastSoulItem::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT32($data, $this->dwCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[FormationUp:上阵/下阵]的返回的参数组成的结构体
class SRetParam_FormationUp
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[SetFormation:设置阵形]的返回的参数组成的结构体
class SRetParam_SetFormation
{
	public $bRet; //(bool)结果

	//构造函数
	function __construct()
	{
		$this->bRet = false;
	}
};

//函数[PetsGet:取得所有阵灵信息]的返回的参数组成的结构体
class SRetParam_PetsGet
{
	public $vecPets; //(SPetDataInfo的数组)阵灵信息列表

	//构造函数
	function __construct()
	{
		$this->vecPets = array();
	}
};

//函数[PetsActive:激活阵灵]的返回的参数组成的结构体
class SRetParam_PetsActive
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[PetsStatus:设置阵灵状态]的返回的参数组成的结构体
class SRetParam_PetsStatus
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[PetsUpgrade:阵灵幻化]的返回的参数组成的结构体
class SRetParam_PetsUpgrade
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[PetsLevelUp:阵灵升级]的返回的参数组成的结构体
class SRetParam_PetsLevelUp
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[QuickPetsLevelUp:阵灵一键升级]的返回的参数组成的结构体
class SRetParam_QuickPetsLevelUp
{
	public $eResult; //(枚举类型：EFormPetType)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[GetBeastSoul:获取兽魂信息]的返回的参数组成的结构体
class SRetParam_GetBeastSoul
{
	public $eResult; //(枚举类型：EBeastSoulResult)获取结果
	public $vecBeastSoul; //(SBeastSoulInfo的数组)兽魂信息

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecBeastSoul = array();
	}
};

//函数[UpgradeBeastSoul:升级兽魂]的返回的参数组成的结构体
class SRetParam_UpgradeBeastSoul
{
	public $eResult; //(枚举类型：EBeastSoulResult)获取结果
	public $vecBeastSoul; //(SBeastSoulInfo的数组)兽魂信息
	public $vecItem; //(SBeastSoulItem的数组)包裹或仓库中道具的列表

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecBeastSoul = array();
		$this->vecItem = array();
	}
};

////////////////////////////////////////////////////////////
//协议类：阵灵相关协议
abstract class FormationProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：上阵/下阵
	function send_FormationUp(
		$qwInstID,  //(UINT64)散仙唯一ID
		$iPos //(INT32)目标位置: [0-8]为上阵 <-1时为下阵
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeINT32($data, $iPos);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置阵形
	function send_SetFormation(
		$vecSLineup //(SLineup的数组)阵形列表
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		SLineup::vectorToStream($data, $vecSLineup);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：取得所有阵灵信息
	function send_PetsGet(
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

	//发送：激活阵灵
	function send_PetsActive(
		$wPetID //(UINT16)阵灵ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wPetID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：设置阵灵状态
	function send_PetsStatus(
		$wPetID,  //(UINT16)阵灵ID
		$byType //(UINT8)状态: 1-出战且显示 2-出战隐藏
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wPetID);
		ByteUtil::writeUINT8($data, $byType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：阵灵幻化
	function send_PetsUpgrade(
		$wPetID //(UINT16)阵灵ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 6);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wPetID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：阵灵升级
	function send_PetsLevelUp(
		$wPetID,  //(UINT16)阵灵ID
		$byType //(UINT8)升级消耗类型 0-朱果 1-蟠桃
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wPetID);
		ByteUtil::writeUINT8($data, $byType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：阵灵一键升级
	function send_QuickPetsLevelUp(
		$wPetID //(UINT16)阵灵ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wPetID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取兽魂信息
	function send_GetBeastSoul(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：升级兽魂
	function send_UpgradeBeastSoul(
		$eType //(枚类型：RoleInfoDefine::EBeastSoulType)兽魂种类
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 10);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eType);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：阵形信息
	abstract function onRecv_FormationNotify(
		$wFormationID, //(UINT16)阵形ID
		$bySelected //(UINT8)状态: 0-未启用 1-未启用
	);

	//接收：阵灵信息
	abstract function onRecv_PetDataNotify(
		$wPetID, //(UINT16)阵灵ID
		$bySelected, //(UINT8)状态: 0-未启用 1-出战且显示 2-出战隐藏
		$byLevel, //(UINT8)阵灵等级
		$dwExp //(UINT32)经验
	);

	//接收：全局阵灵信息
	abstract function onRecv_RolePetNotify(
		$sRolePetInfo //(类类型：RoleInfoDefine::SRolePetInfo)阵灵全局信息
	);

	//接收：兽魂信息
	abstract function onRecv_BeastNotify(
		$wBeastID //(UINT16)兽魂ID
	);

	//接收：兽魂信息
	abstract function onRecv_BeastSoulNotify(
		$vecBeastSoul //(SBeastSoulInfo的数组)兽魂信息
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：上阵/下阵
	abstract function onReturn_FormationUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FormationUp)返回的参数
	);

	//返回：设置阵形
	abstract function onReturn_SetFormation(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_SetFormation)返回的参数
	);

	//返回：取得所有阵灵信息
	abstract function onReturn_PetsGet(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_PetsGet)返回的参数
	);

	//返回：激活阵灵
	abstract function onReturn_PetsActive(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_PetsActive)返回的参数
	);

	//返回：设置阵灵状态
	abstract function onReturn_PetsStatus(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_PetsStatus)返回的参数
	);

	//返回：阵灵幻化
	abstract function onReturn_PetsUpgrade(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_PetsUpgrade)返回的参数
	);

	//返回：阵灵升级
	abstract function onReturn_PetsLevelUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_PetsLevelUp)返回的参数
	);

	//返回：阵灵一键升级
	abstract function onReturn_QuickPetsLevelUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_QuickPetsLevelUp)返回的参数
	);

	//返回：获取兽魂信息
	abstract function onReturn_GetBeastSoul(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetBeastSoul)返回的参数
	);

	//返回：升级兽魂
	abstract function onReturn_UpgradeBeastSoul(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UpgradeBeastSoul)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：阵形信息
	private function _doRecv_FormationNotify($data)
	{
		$wFormationID = ByteUtil::readUINT16($data);
		$bySelected = ByteUtil::readUINT8($data);
		return $this->onRecv_FormationNotify($wFormationID, $bySelected);
	}

	//接收处理：阵灵信息
	private function _doRecv_PetDataNotify($data)
	{
		$wPetID = ByteUtil::readUINT16($data);
		$bySelected = ByteUtil::readUINT8($data);
		$byLevel = ByteUtil::readUINT8($data);
		$dwExp = ByteUtil::readUINT32($data);
		return $this->onRecv_PetDataNotify($wPetID, $bySelected, $byLevel, $dwExp);
	}

	//接收处理：全局阵灵信息
	private function _doRecv_RolePetNotify($data)
	{
		$sRolePetInfo = SRolePetInfo::fromStream($data);
		return $this->onRecv_RolePetNotify($sRolePetInfo);
	}

	//接收处理：兽魂信息
	private function _doRecv_BeastNotify($data)
	{
		$wBeastID = ByteUtil::readUINT16($data);
		return $this->onRecv_BeastNotify($wBeastID);
	}

	//接收处理：兽魂信息
	private function _doRecv_BeastSoulNotify($data)
	{
		$vecBeastSoul = SBeastSoulInfo::vectorFromStream($data);
		return $this->onRecv_BeastSoulNotify($vecBeastSoul);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：上阵/下阵
	private function _doReturn_FormationUp($data)
	{
		$retParam = new SRetParam_FormationUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FormationUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：上阵/下阵
	private function _onTimeOut_FormationUp($sessionID)
	{
		$retParam = new SRetParam_FormationUp;
		$this->onReturn_FormationUp(2, $retParam);
	}

	//返回处理：设置阵形
	private function _doReturn_SetFormation($data)
	{
		$retParam = new SRetParam_SetFormation;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$bRet = ByteUtil::readBool($data); //结果
		$retParam->bRet = $bRet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SetFormation($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置阵形
	private function _onTimeOut_SetFormation($sessionID)
	{
		$retParam = new SRetParam_SetFormation;
		$this->onReturn_SetFormation(2, $retParam);
	}

	//返回处理：取得所有阵灵信息
	private function _doReturn_PetsGet($data)
	{
		$retParam = new SRetParam_PetsGet;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecPets = SPetDataInfo::vectorFromStream($data); //阵灵信息列表
		$retParam->vecPets = $vecPets;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_PetsGet($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取得所有阵灵信息
	private function _onTimeOut_PetsGet($sessionID)
	{
		$retParam = new SRetParam_PetsGet;
		$this->onReturn_PetsGet(2, $retParam);
	}

	//返回处理：激活阵灵
	private function _doReturn_PetsActive($data)
	{
		$retParam = new SRetParam_PetsActive;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_PetsActive($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：激活阵灵
	private function _onTimeOut_PetsActive($sessionID)
	{
		$retParam = new SRetParam_PetsActive;
		$this->onReturn_PetsActive(2, $retParam);
	}

	//返回处理：设置阵灵状态
	private function _doReturn_PetsStatus($data)
	{
		$retParam = new SRetParam_PetsStatus;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_PetsStatus($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：设置阵灵状态
	private function _onTimeOut_PetsStatus($sessionID)
	{
		$retParam = new SRetParam_PetsStatus;
		$this->onReturn_PetsStatus(2, $retParam);
	}

	//返回处理：阵灵幻化
	private function _doReturn_PetsUpgrade($data)
	{
		$retParam = new SRetParam_PetsUpgrade;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_PetsUpgrade($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：阵灵幻化
	private function _onTimeOut_PetsUpgrade($sessionID)
	{
		$retParam = new SRetParam_PetsUpgrade;
		$this->onReturn_PetsUpgrade(2, $retParam);
	}

	//返回处理：阵灵升级
	private function _doReturn_PetsLevelUp($data)
	{
		$retParam = new SRetParam_PetsLevelUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_PetsLevelUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：阵灵升级
	private function _onTimeOut_PetsLevelUp($sessionID)
	{
		$retParam = new SRetParam_PetsLevelUp;
		$this->onReturn_PetsLevelUp(2, $retParam);
	}

	//返回处理：阵灵一键升级
	private function _doReturn_QuickPetsLevelUp($data)
	{
		$retParam = new SRetParam_QuickPetsLevelUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFormPetType)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_QuickPetsLevelUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：阵灵一键升级
	private function _onTimeOut_QuickPetsLevelUp($sessionID)
	{
		$retParam = new SRetParam_QuickPetsLevelUp;
		$this->onReturn_QuickPetsLevelUp(2, $retParam);
	}

	//返回处理：获取兽魂信息
	private function _doReturn_GetBeastSoul($data)
	{
		$retParam = new SRetParam_GetBeastSoul;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EBeastSoulResult)获取结果
		$vecBeastSoul = SBeastSoulInfo::vectorFromStream($data); //兽魂信息
		$retParam->eResult = $eResult;
		$retParam->vecBeastSoul = $vecBeastSoul;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetBeastSoul($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取兽魂信息
	private function _onTimeOut_GetBeastSoul($sessionID)
	{
		$retParam = new SRetParam_GetBeastSoul;
		$this->onReturn_GetBeastSoul(2, $retParam);
	}

	//返回处理：升级兽魂
	private function _doReturn_UpgradeBeastSoul($data)
	{
		$retParam = new SRetParam_UpgradeBeastSoul;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EBeastSoulResult)获取结果
		$vecBeastSoul = SBeastSoulInfo::vectorFromStream($data); //兽魂信息
		$vecItem = SBeastSoulItem::vectorFromStream($data); //包裹或仓库中道具的列表
		$retParam->eResult = $eResult;
		$retParam->vecBeastSoul = $vecBeastSoul;
		$retParam->vecItem = $vecItem;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UpgradeBeastSoul($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：升级兽魂
	private function _onTimeOut_UpgradeBeastSoul($sessionID)
	{
		$retParam = new SRetParam_UpgradeBeastSoul;
		$this->onReturn_UpgradeBeastSoul(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 22;
		$this->_recvFuncList[0] = '_doRecv_FormationNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_PetDataNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_RolePetNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_BeastNotify'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_BeastSoulNotify'; //FuncID: 5

		$this->_retFuncList[0] = '_doReturn_FormationUp'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_SetFormation'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_PetsGet'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_PetsActive'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_PetsStatus'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_PetsUpgrade'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_PetsLevelUp'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_QuickPetsLevelUp'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_GetBeastSoul'; //FuncID: 9
		$this->_retFuncList[9] = '_doReturn_UpgradeBeastSoul'; //FuncID: 10

		$this->_timeFuncList[0] = '_onTimeOut_FormationUp'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_SetFormation'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_PetsGet'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_PetsActive'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_PetsStatus'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_PetsUpgrade'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_PetsLevelUp'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_QuickPetsLevelUp'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_GetBeastSoul'; //FuncID: 9
		$this->_timeFuncList[9] = '_onTimeOut_UpgradeBeastSoul'; //FuncID: 10
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