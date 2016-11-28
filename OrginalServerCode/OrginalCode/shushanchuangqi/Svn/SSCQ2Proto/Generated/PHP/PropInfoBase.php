<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    PropInfo.php
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');

/////////////////////以下为类型定义/////////////////////
//变更对象类型
class EPropClass
{
	const eClassRole = 0; //角色
	const eClassFighter = 1; //将
	const eClassEquip = 2; //装备
	const eClassORole = 3; //其他角色
}

//属性的类型
class EPropType
{
	const ePropNone = 0; //无
	const ePropGold = 1; //仙石
	const ePropSilver = 2; //银币
	const ePropCoupon = 3; //礼券
	const eProppGiftCoin = 4; //金券
	const ePropExpTemp = 5; //经验(占位)
	const ePropPrestige = 6; //声望
	const ePropSoul = 7; //魂魄
	const ePropHonor = 8; //荣誉
	const ePropPExp = 9; //修为
	const ePropSigil = 10; //符印
	const ePropCentsY = 11; //仙元
	const ePropAction = 12; //体力
	const ePropSop = 13; //阅历
	const ePropTaoism = 14; //道术
	const ePropPoten = 15; //渡劫点数
	const ePropReiki = 16; //副本星级
	const ePropHFP = 17; //寻仙积分
	const ePropDemonSoul = 18; //锁妖塔魂值
	const ePropSoulAttack = 19; //攻击之魂
	const ePropSoulHp = 20; //生命之魂
	const ePropSoulCritical = 21; //暴击之魂
	const ePropSoulCounter = 22; //反击之魂
	const ePropSoulSpeed = 23; //身法之魂
	const ePropSoulDefence = 24; //防御之魂
	const ePropSoulHit = 25; //命中之魂
	const ePropSoulDodge = 26; //闪避之魂
	const ePropAchievementAP = 27; //成就点
	const ePropCollectAP = 28; //收藏点
	const ePropGuildContrib = 29; //帮派贡献
	const ePropStampHuang = 30; //黄阶除魔印
	const ePropStampXuan = 31; //玄阶除魔印
	const ePropStampDi = 32; //地阶除魔印
	const ePropStampTian = 33; //天阶除魔印
	const ePropStampXing = 34; //星阶除魔印
	const ePropStampYue = 35; //月阶除魔印
	const ePropStampDi2 = 36; //帝阶除魔印
	const ePropStampXian = 37; //仙阶除魔印
	const ePropStampSheng = 38; //圣阶除魔印
	const ePropStampFo = 39; //佛阶除魔印
	const ePropLoveHeart = 40; //爱心
	const ePropBlueFairyFate = 51; //蓝色仙缘
	const ePropPurpleFairyFate = 52; //紫色仙缘
	const ePropOrangeFairyFate = 53; //橙色仙缘
	const ePropDuJieFu = 56; //渡劫符
	const ePropLuckyCoupon = 57; //抽奖券
	const ePropMoneyEnd = 100; //钱币属性结束标志
	const ePropCommon = 200; //普通定义
	const ePropTotalRecharge = 201; //总充值数
	const ePropBTPoint = 202; //战斗力
	const ePropHero = 300; //将定义
	const ePropPos = 301; //将在阵型中的位置
	const ePropTroopPos = 302; //将在队伍中的位置
	const ePropPotential = 303; //潜力
	const ePropCapacity = 304; //资质
	const ePropLevel = 305; //等级
	const ePropLucky = 306; //机缘值
	const ePropExp = 307; //经验 -- UINT64
	const ePropLianPi = 308; //炼皮
	const ePropTongJin = 309; //通筋
	const ePropQiangJi = 310; //强肌
	const ePropDuanGu = 311; //锻骨
	const ePropMax = 312; //属性枚举最大值
}

//属性操作的结果
class EPropResult
{
	const ePropSucceed = 0; //无
	const ePropGoldErr = 1; //仙石不够
	const ePropSilverErr = 2; //银币不够
	const ePropCouponErr = 3; //礼券不够
	const ePropOtherErr = 4; //其它错误
}

//兑换结果
class EExchangeResult
{
	const eExchangeResultSuccess = 0; //兑换成功
	const eExchangeResultFailed = 1; //兑换失败
	const eExchangeResultLack = 2; //兑换数量不足
	const eExchangeResultLimit = 3; //兑换已达上限
	const eExchangeResultMax = 4; //兑换结果最大值
}

//属性信息
final class SPropValue
{
	public $ePropType; //(枚举类型：EPropType)属性类型
	public $value; //(UINT32)属性值，需要根据类型来转换

	//构造函数
	function __construct()
	{
		$this->ePropType = 0;
		$this->value = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->ePropType = $this->ePropType;
		$obj->value = $this->value;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPropValue;
		$s->ePropType = ByteUtil::readUINT16($data);
		$s->value = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPropValue::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->ePropType);
		ByteUtil::writeUINT32($data, $this->value);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//属性信息
final class SPropQWValue
{
	public $ePropType; //(枚举类型：EPropType)属性类型
	public $value; //(UINT64)属性值，需要根据类型来转换

	//构造函数
	function __construct()
	{
		$this->ePropType = 0;
		$this->value = new Math_BigInteger;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->ePropType = $this->ePropType;
		$obj->value = $this->value;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPropQWValue;
		$s->ePropType = ByteUtil::readUINT16($data);
		$s->value = ByteUtil::readUINT64($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPropQWValue::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->ePropType);
		ByteUtil::writeUINT64($data, $this->value);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//扩展属性信息
final class SPropValExt
{
	public $ePropType; //(枚举类型：EPropType)属性类型
	public $value; //(float)属性值，需要根据类型来转换
	public $ext; //(INT32)扩展值，不同用途作不同的解释

	//构造函数
	function __construct()
	{
		$this->ePropType = 0;
		$this->value = 0;
		$this->ext = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->ePropType = $this->ePropType;
		$obj->value = $this->value;
		$obj->ext = $this->ext;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPropValExt;
		$s->ePropType = ByteUtil::readUINT16($data);
		$s->value = ByteUtil::readFloat($data);
		$s->ext = ByteUtil::readINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPropValExt::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->ePropType);
		ByteUtil::writeFloat($data, $this->value);
		ByteUtil::writeINT32($data, $this->ext);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//扩展属性信息
final class SPropQWValExt
{
	public $ePropType; //(枚举类型：EPropType)属性类型
	public $value; //(UINT64)属性值，需要根据类型来转换
	public $ext; //(INT32)扩展值，不同用途作不同的解释

	//构造函数
	function __construct()
	{
		$this->ePropType = 0;
		$this->value = new Math_BigInteger;
		$this->ext = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->ePropType = $this->ePropType;
		$obj->value = $this->value;
		$obj->ext = $this->ext;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPropQWValExt;
		$s->ePropType = ByteUtil::readUINT16($data);
		$s->value = ByteUtil::readUINT64($data);
		$s->ext = ByteUtil::readINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPropQWValExt::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->ePropType);
		ByteUtil::writeUINT64($data, $this->value);
		ByteUtil::writeINT32($data, $this->ext);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[MoneyExchange:货币兑换]的返回的参数组成的结构体
class SRetParam_MoneyExchange
{
	public $eResult; //(枚举类型：EExchangeResult)兑换结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：属性相关协议
abstract class PropInfoBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：货币兑换
	function send_MoneyExchange(
		$eSrcProp,  //(枚举类型：EPropType)源货币
		$eDestProp,  //(枚举类型：EPropType)目标货币
		$dwCount //(UINT32)数量
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $eSrcProp);
		ByteUtil::writeUINT16($data, $eDestProp);
		ByteUtil::writeUINT32($data, $dwCount);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：属性列表通知(改变后通知)
	abstract function onRecv_PropListNotify(
		$qwInstID, //(UINT64)变更对象ID
		$eClass, //(枚举类型：EPropClass)变更对象类型
		$vecPropValue //(SPropValue的数组)属性列表
	);

	//接收：属性列表通知(改变后通知)
	abstract function onRecv_PropNotify(
		$qwInstID, //(UINT64)变更对象ID
		$eClass, //(枚举类型：EPropClass)变更对象类型
		$vecPropValue, //(SPropValue的数组)属性列表
		$bType //(bool)是否飘字
	);

	//接收：扩展属性列表通知(改变后通知)
	abstract function onRecv_PropExtListNotify(
		$qwInstID, //(UINT64)变更对象ID
		$eClass, //(枚举类型：EPropClass)变更对象类型
		$vecPropValExt //(SPropValExt的数组)扩展属性列表
	);

	//接收：属性列表通知(改变后通知)
	abstract function onRecv_PropQWListNotify(
		$qwInstID, //(UINT64)变更对象ID
		$eClass, //(枚举类型：EPropClass)变更对象类型
		$vecPropValue //(SPropQWValue的数组)属性列表
	);

	//接收：扩展属性列表通知(改变后通知)
	abstract function onRecv_PropQWExtListNotify(
		$qwInstID, //(UINT64)变更对象ID
		$eClass, //(枚举类型：EPropClass)变更对象类型
		$vecPropValExt //(SPropQWValExt的数组)扩展属性列表
	);

	//接收：Creature的名字改变通知
	abstract function onRecv_NameChangeNotify(
		$qwCreatureID, //(UINT64)生物ID
		$strName //(string)新名字
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：货币兑换
	abstract function onReturn_MoneyExchange(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MoneyExchange)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：属性列表通知(改变后通知)
	private function _doRecv_PropListNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$eClass = ByteUtil::readUINT8($data);
		$vecPropValue = SPropValue::vectorFromStream($data);
		return $this->onRecv_PropListNotify($qwInstID, $eClass, $vecPropValue);
	}

	//接收处理：属性列表通知(改变后通知)
	private function _doRecv_PropNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$eClass = ByteUtil::readUINT8($data);
		$vecPropValue = SPropValue::vectorFromStream($data);
		$bType = ByteUtil::readBool($data);
		return $this->onRecv_PropNotify($qwInstID, $eClass, $vecPropValue, $bType);
	}

	//接收处理：扩展属性列表通知(改变后通知)
	private function _doRecv_PropExtListNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$eClass = ByteUtil::readUINT8($data);
		$vecPropValExt = SPropValExt::vectorFromStream($data);
		return $this->onRecv_PropExtListNotify($qwInstID, $eClass, $vecPropValExt);
	}

	//接收处理：属性列表通知(改变后通知)
	private function _doRecv_PropQWListNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$eClass = ByteUtil::readUINT8($data);
		$vecPropValue = SPropQWValue::vectorFromStream($data);
		return $this->onRecv_PropQWListNotify($qwInstID, $eClass, $vecPropValue);
	}

	//接收处理：扩展属性列表通知(改变后通知)
	private function _doRecv_PropQWExtListNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$eClass = ByteUtil::readUINT8($data);
		$vecPropValExt = SPropQWValExt::vectorFromStream($data);
		return $this->onRecv_PropQWExtListNotify($qwInstID, $eClass, $vecPropValExt);
	}

	//接收处理：Creature的名字改变通知
	private function _doRecv_NameChangeNotify($data)
	{
		$qwCreatureID = ByteUtil::readUINT64($data);
		$strName = ByteUtil::readString($data);
		return $this->onRecv_NameChangeNotify($qwCreatureID, $strName);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：货币兑换
	private function _doReturn_MoneyExchange($data)
	{
		$retParam = new SRetParam_MoneyExchange;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EExchangeResult)兑换结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MoneyExchange($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：货币兑换
	private function _onTimeOut_MoneyExchange($sessionID)
	{
		$retParam = new SRetParam_MoneyExchange;
		$this->onReturn_MoneyExchange(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 17;
		$this->_recvFuncList[0] = '_doRecv_PropListNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_PropNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_PropExtListNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_PropQWListNotify'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_PropQWExtListNotify'; //FuncID: 5
		$this->_recvFuncList[5] = '_doRecv_NameChangeNotify'; //FuncID: 6

		$this->_retFuncList[0] = '_doReturn_MoneyExchange'; //FuncID: 1

		$this->_timeFuncList[0] = '_onTimeOut_MoneyExchange'; //FuncID: 1
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