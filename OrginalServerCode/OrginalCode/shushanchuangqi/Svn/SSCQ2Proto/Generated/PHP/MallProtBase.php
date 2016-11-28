<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    MallProt.php
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//商城类型
class EMallType
{
	const eMallGold = 1; //奇珍商城
	const eMallFashion = 2; //时装商城
	const eMallVIP = 3; //VIP商城
	const eMallPrestige = 4; //声望商城
	const eMallHonor = 5; //荣誉商城
	const eMallCoupon = 6; //礼券商城
	const eMallSilver = 7; //银币商城
	const eMallLimit = 8; //限购商城
	const eMallGem = 9; //宝石商城
	const eMallEnd = 10; //商城
}

//商城操作结果
class EMallResult
{
	const eMallResultSucc = 0; //成功
	const eMallResultFailed = 1; //失败
	const eMallResultStore = 2; //背包空间不足
	const eMallResultStoreAdd = 3; //物品加入背包出错
	const eMallResultMoney = 4; //购买时相应货币不足
	const eMallResultNoItem = 5; //所购买的物品已下架
	const eMallResultFashionErr = 6; //所购买的时装不能加入背包
	const eMallResultFashionAlready = 7; //所购买的时装已存在
	const eMallPresentSucc = 8; //赠送成功
	const eMallPresentNoTarget = 9; //赠送的玩家不存在
	const eMallResultDiscountOverTime = 10; //限购活动已过期
	const eMallResultDiscountFull = 11; //超出限购数量限制
	const eMallResultDiscountRechargeErr = 12; //未达到限购充值仙石数量
	const eMallResultDiscountConsumeErr = 13; //未达到限购消耗仙石数量
	const eMallResultItemCount = 14; //没有购买次数
}

//使用钱币标志
class EUseMoneyMark
{
	const eUseBindMoney = 0; //使用绑定钱币
	const eUseNoBindMoney = 1; //使用非绑定钱币
}

//限购限制类型
class EDiscountLimitType
{
	const eDiscountLimitTypeNO = 0; //无条件
	const eDiscountLimitTypeRecharge = 1; //充值限购
	const eDiscountLimitTypeConsume = 2; //消费限购
	const eDiscountLimitTypeEnd = 3; //限购类型
}

//商城信息
final class SMallInfo
{
	public $dwInstID; //(UINT32)商品编号
	public $strName; //(string)商品名称
	public $wItemID; //(UINT16)物品ID
	public $dwItemCount; //(UINT32)物品数量
	public $eMoneyType; //(枚类型：ProtoCommon::EMoneyType)所需货币类型
	public $dwPrice; //(UINT32)价格
	public $byVIP; //(UINT8)VIP等级限制
	public $wIcon; //(UINT16)图标
	public $dwDayCntLimit; //(UINT32)限购数量

	//构造函数
	function __construct()
	{
		$this->dwInstID = 0;
		$this->strName = '';
		$this->wItemID = 0;
		$this->dwItemCount = 0;
		$this->eMoneyType = 0;
		$this->dwPrice = 0;
		$this->byVIP = 0;
		$this->wIcon = 0;
		$this->dwDayCntLimit = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwInstID = $this->dwInstID;
		$obj->strName = $this->strName;
		$obj->wItemID = $this->wItemID;
		$obj->dwItemCount = $this->dwItemCount;
		$obj->eMoneyType = $this->eMoneyType;
		$obj->dwPrice = $this->dwPrice;
		$obj->byVIP = $this->byVIP;
		$obj->wIcon = $this->wIcon;
		$obj->dwDayCntLimit = $this->dwDayCntLimit;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SMallInfo;
		$s->dwInstID = ByteUtil::readUINT32($data);
		$s->strName = ByteUtil::readString($data);
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->dwItemCount = ByteUtil::readUINT32($data);
		$s->eMoneyType = ByteUtil::readUINT8($data);
		$s->dwPrice = ByteUtil::readUINT32($data);
		$s->byVIP = ByteUtil::readUINT8($data);
		$s->wIcon = ByteUtil::readUINT16($data);
		$s->dwDayCntLimit = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SMallInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwInstID);
		ByteUtil::writeString($data, $this->strName);
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT32($data, $this->dwItemCount);
		ByteUtil::writeUINT8($data, $this->eMoneyType);
		ByteUtil::writeUINT32($data, $this->dwPrice);
		ByteUtil::writeUINT8($data, $this->byVIP);
		ByteUtil::writeUINT16($data, $this->wIcon);
		ByteUtil::writeUINT32($data, $this->dwDayCntLimit);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//商城折扣物品
final class SDiscountItem
{
	public $wItemID; //(UINT16)物品ID
	public $wOriginalPrice; //(UINT16)原价
	public $wDiscountPrice; //(UINT16)折扣价

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->wOriginalPrice = 0;
		$this->wDiscountPrice = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->wOriginalPrice = $this->wOriginalPrice;
		$obj->wDiscountPrice = $this->wDiscountPrice;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SDiscountItem;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->wOriginalPrice = ByteUtil::readUINT16($data);
		$s->wDiscountPrice = ByteUtil::readUINT16($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SDiscountItem::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT16($data, $this->wOriginalPrice);
		ByteUtil::writeUINT16($data, $this->wDiscountPrice);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//商城折扣物品信息
final class SDiscount
{
	public $byPos; //(UINT8)限购位置(0,1,2表示)
	public $qwMarkID; //(UINT64)栏位版本ID
	public $vecDisItems; //(SDiscountItem的数组)限购道具
	public $byLimitType; //(UINT8)类型限制(0无条件、1充值限购、2消费限购)
	public $dwLimitValue; //(UINT32)达到的仙石数量限制(0无条件、1充值限购、2消费限购)
	public $wLimitCount; //(UINT16)购买道具个数限制
	public $dwBeginTime; //(UINT32)限购开始时间
	public $dwEndTime; //(UINT32)限购结束时间

	//构造函数
	function __construct()
	{
		$this->byPos = 0;
		$this->qwMarkID = new Math_BigInteger;
		$this->vecDisItems = array();
		$this->byLimitType = 0;
		$this->dwLimitValue = 0;
		$this->wLimitCount = 0;
		$this->dwBeginTime = 0;
		$this->dwEndTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->byPos = $this->byPos;
		$obj->qwMarkID = $this->qwMarkID;
		$obj->vecDisItems = $this->vecDisItems;
		$obj->byLimitType = $this->byLimitType;
		$obj->dwLimitValue = $this->dwLimitValue;
		$obj->wLimitCount = $this->wLimitCount;
		$obj->dwBeginTime = $this->dwBeginTime;
		$obj->dwEndTime = $this->dwEndTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SDiscount;
		$s->byPos = ByteUtil::readUINT8($data);
		$s->qwMarkID = ByteUtil::readUINT64($data);
		$s->vecDisItems = SDiscountItem::vectorFromStream($data);
		$s->byLimitType = ByteUtil::readUINT8($data);
		$s->dwLimitValue = ByteUtil::readUINT32($data);
		$s->wLimitCount = ByteUtil::readUINT16($data);
		$s->dwBeginTime = ByteUtil::readUINT32($data);
		$s->dwEndTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SDiscount::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->byPos);
		ByteUtil::writeUINT64($data, $this->qwMarkID);
		SDiscountItem::vectorToStream($data, $this->vecDisItems);
		ByteUtil::writeUINT8($data, $this->byLimitType);
		ByteUtil::writeUINT32($data, $this->dwLimitValue);
		ByteUtil::writeUINT16($data, $this->wLimitCount);
		ByteUtil::writeUINT32($data, $this->dwBeginTime);
		ByteUtil::writeUINT32($data, $this->dwEndTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//物品购买信息
final class SBuyItemInfo
{
	public $dwInstID; //(UINT32)实例ID
	public $dwCount; //(UINT32)物品数量

	//构造函数
	function __construct()
	{
		$this->dwInstID = 0;
		$this->dwCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwInstID = $this->dwInstID;
		$obj->dwCount = $this->dwCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SBuyItemInfo;
		$s->dwInstID = ByteUtil::readUINT32($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SBuyItemInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwInstID);
		ByteUtil::writeUINT32($data, $this->dwCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[MalGet:预览商城信息]的返回的参数组成的结构体
class SRetParam_MalGet
{
	public $vecMallInfo; //(SMallInfo的数组)商场信息列表

	//构造函数
	function __construct()
	{
		$this->vecMallInfo = array();
	}
};

//函数[MalBuy:商场购买]的返回的参数组成的结构体
class SRetParam_MalBuy
{
	public $eResult; //(枚举类型：EMallResult)购买结果返回

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[MallPresent:商场赠送]的返回的参数组成的结构体
class SRetParam_MallPresent
{
	public $eResult; //(枚举类型：EMallResult)赠送结果返回

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[BuyDiscountItem:购买商场限购道具]的返回的参数组成的结构体
class SRetParam_BuyDiscountItem
{
	public $eResult; //(枚举类型：EMallResult)购买结果返回
	public $byPos; //(UINT8)限购位置(0,1,2)
	public $wCount; //(UINT16)购买个数

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->byPos = 0;
		$this->wCount = 0;
	}
};

//函数[GetBuyItemList:获取物品购买数量列表]的返回的参数组成的结构体
class SRetParam_GetBuyItemList
{
	public $vecBuyItemInfo; //(SBuyItemInfo的数组)购买数量列表

	//构造函数
	function __construct()
	{
		$this->vecBuyItemInfo = array();
	}
};

////////////////////////////////////////////////////////////
//协议类：商城相关协议
abstract class MallProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：预览商城信息
	function send_MalGet(
		$eType //(枚举类型：EMallType)商城类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeINT8($data, $eType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：商场购买
	function send_MalBuy(
		$eMark,  //(枚举类型：EUseMoneyMark)使用钱币标志
		$eType,  //(枚举类型：EMallType)商城类型
		$wInstID,  //(UINT32)实例ID
		$wCount //(UINT16)物品个数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeINT8($data, $eMark);
		ByteUtil::writeINT8($data, $eType);
		ByteUtil::writeUINT32($data, $wInstID);
		ByteUtil::writeUINT16($data, $wCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：商场赠送
	function send_MallPresent(
		$eMark,  //(枚举类型：EUseMoneyMark)使用钱币标志
		$eType,  //(枚举类型：EMallType)商城类型
		$wInstID,  //(UINT32)物品ID
		$wCount,  //(UINT16)物品个数
		$strReceiveName,  //(string)接受者姓名
		$strTitle,  //(string)邮件标题
		$strMsg //(string)邮件内容
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeINT8($data, $eMark);
		ByteUtil::writeINT8($data, $eType);
		ByteUtil::writeUINT32($data, $wInstID);
		ByteUtil::writeUINT16($data, $wCount);
		ByteUtil::writeString($data, $strReceiveName);
		ByteUtil::writeString($data, $strTitle);
		ByteUtil::writeString($data, $strMsg);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：预览商城限购信息
	function send_GetMallDiscountInfo(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：购买商场限购道具
	function send_BuyDiscountItem(
		$byPos,  //(UINT8)限购位置(0,1,2)
		$wCount //(UINT16)购买个数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byPos);
		ByteUtil::writeUINT16($data, $wCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取物品购买数量列表
	function send_GetBuyItemList(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取玩家首次充值活动完成信息(在商城界面的奖励)
	function send_GetChongZhiActInfo(
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：通知玩家商城限购信息
	abstract function onRecv_UpdateMallDiscountInfo(
		$vecDiscount, //(SDiscount的数组)限购信息列表
		$wCountPos1, //(UINT32)限购位置1购买道具数
		$wCountPos2, //(UINT32)限购位置2购买道具数
		$wCountPos3, //(UINT32)限购位置3购买道具数
		$wRechargePos1, //(UINT32)位置1充值限购期间充值仙石数
		$wRechargePos2, //(UINT32)位置2充值限购期间充值仙石数
		$wRechargePos3, //(UINT32)位置3充值限购期间充值仙石数
		$wConsumePos1, //(UINT32)位置1消费限购期间消费仙石数
		$wConsumePos2, //(UINT32)位置2消费限购期间消费仙石数
		$wConsumePos3 //(UINT32)位置3消费限购期间消费仙石数
	);

	//接收：通过栏位通知玩家商城限购信息
	abstract function onRecv_UpdateMallDiscountInfoByPos(
		$oDiscount //(类类型：SDiscount)限购信息列表
	);

	//接收：物品购买数量更新
	abstract function onRecv_BuyItemNotify(
		$oBuyItemInfo //(类类型：SBuyItemInfo)更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
	);

	//接收：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
	abstract function onRecv_UpdateChongZhiActInfo(
		$byIdx, //(UINT8)当前充值完成的第几个
		$dwCount, //(UINT32)当前充值了几个仙石包
		$byInfo //(UINT8)按位取(低6位,每位为1表明已完成)
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：预览商城信息
	abstract function onReturn_MalGet(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MalGet)返回的参数
	);

	//返回：商场购买
	abstract function onReturn_MalBuy(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MalBuy)返回的参数
	);

	//返回：商场赠送
	abstract function onReturn_MallPresent(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MallPresent)返回的参数
	);

	//返回：购买商场限购道具
	abstract function onReturn_BuyDiscountItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_BuyDiscountItem)返回的参数
	);

	//返回：获取物品购买数量列表
	abstract function onReturn_GetBuyItemList(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetBuyItemList)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：通知玩家商城限购信息
	private function _doRecv_UpdateMallDiscountInfo($data)
	{
		$vecDiscount = SDiscount::vectorFromStream($data);
		$wCountPos1 = ByteUtil::readUINT32($data);
		$wCountPos2 = ByteUtil::readUINT32($data);
		$wCountPos3 = ByteUtil::readUINT32($data);
		$wRechargePos1 = ByteUtil::readUINT32($data);
		$wRechargePos2 = ByteUtil::readUINT32($data);
		$wRechargePos3 = ByteUtil::readUINT32($data);
		$wConsumePos1 = ByteUtil::readUINT32($data);
		$wConsumePos2 = ByteUtil::readUINT32($data);
		$wConsumePos3 = ByteUtil::readUINT32($data);
		return $this->onRecv_UpdateMallDiscountInfo($vecDiscount, $wCountPos1, $wCountPos2, $wCountPos3, $wRechargePos1, $wRechargePos2, $wRechargePos3, $wConsumePos1, $wConsumePos2, $wConsumePos3);
	}

	//接收处理：通过栏位通知玩家商城限购信息
	private function _doRecv_UpdateMallDiscountInfoByPos($data)
	{
		$oDiscount = SDiscount::fromStream($data);
		return $this->onRecv_UpdateMallDiscountInfoByPos($oDiscount);
	}

	//接收处理：物品购买数量更新
	private function _doRecv_BuyItemNotify($data)
	{
		$oBuyItemInfo = SBuyItemInfo::fromStream($data);
		return $this->onRecv_BuyItemNotify($oBuyItemInfo);
	}

	//接收处理：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
	private function _doRecv_UpdateChongZhiActInfo($data)
	{
		$byIdx = ByteUtil::readUINT8($data);
		$dwCount = ByteUtil::readUINT32($data);
		$byInfo = ByteUtil::readUINT8($data);
		return $this->onRecv_UpdateChongZhiActInfo($byIdx, $dwCount, $byInfo);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：预览商城信息
	private function _doReturn_MalGet($data)
	{
		$retParam = new SRetParam_MalGet;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecMallInfo = SMallInfo::vectorFromStream($data); //商场信息列表
		$retParam->vecMallInfo = $vecMallInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MalGet($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：预览商城信息
	private function _onTimeOut_MalGet($sessionID)
	{
		$retParam = new SRetParam_MalGet;
		$this->onReturn_MalGet(2, $retParam);
	}

	//返回处理：商场购买
	private function _doReturn_MalBuy($data)
	{
		$retParam = new SRetParam_MalBuy;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readINT8($data); //(枚举类型：EMallResult)购买结果返回
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MalBuy($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：商场购买
	private function _onTimeOut_MalBuy($sessionID)
	{
		$retParam = new SRetParam_MalBuy;
		$this->onReturn_MalBuy(2, $retParam);
	}

	//返回处理：商场赠送
	private function _doReturn_MallPresent($data)
	{
		$retParam = new SRetParam_MallPresent;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readINT8($data); //(枚举类型：EMallResult)赠送结果返回
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MallPresent($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：商场赠送
	private function _onTimeOut_MallPresent($sessionID)
	{
		$retParam = new SRetParam_MallPresent;
		$this->onReturn_MallPresent(2, $retParam);
	}

	//返回处理：购买商场限购道具
	private function _doReturn_BuyDiscountItem($data)
	{
		$retParam = new SRetParam_BuyDiscountItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readINT8($data); //(枚举类型：EMallResult)购买结果返回
		$byPos = ByteUtil::readUINT8($data); //(无符号8位整数)限购位置(0,1,2)
		$wCount = ByteUtil::readUINT16($data); //(无符号16位整数)购买个数
		$retParam->eResult = $eResult;
		$retParam->byPos = $byPos;
		$retParam->wCount = $wCount;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_BuyDiscountItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：购买商场限购道具
	private function _onTimeOut_BuyDiscountItem($sessionID)
	{
		$retParam = new SRetParam_BuyDiscountItem;
		$this->onReturn_BuyDiscountItem(2, $retParam);
	}

	//返回处理：获取物品购买数量列表
	private function _doReturn_GetBuyItemList($data)
	{
		$retParam = new SRetParam_GetBuyItemList;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecBuyItemInfo = SBuyItemInfo::vectorFromStream($data); //购买数量列表
		$retParam->vecBuyItemInfo = $vecBuyItemInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetBuyItemList($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取物品购买数量列表
	private function _onTimeOut_GetBuyItemList($sessionID)
	{
		$retParam = new SRetParam_GetBuyItemList;
		$this->onReturn_GetBuyItemList(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 27;
		$this->_recvFuncList[0] = '_doRecv_UpdateMallDiscountInfo'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_UpdateMallDiscountInfoByPos'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_BuyItemNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_UpdateChongZhiActInfo'; //FuncID: 4

		$this->_retFuncList[0] = '_doReturn_MalGet'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_MalBuy'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_MallPresent'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_BuyDiscountItem'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_GetBuyItemList'; //FuncID: 5

		$this->_timeFuncList[0] = '_onTimeOut_MalGet'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_MalBuy'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_MallPresent'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_BuyDiscountItem'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_GetBuyItemList'; //FuncID: 5
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