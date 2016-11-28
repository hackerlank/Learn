<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    ItemProt.php
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//使用道具结果
class EItemResult
{
	const eItemSucceed = 0; //成功
	const eItemFailed = 1; //失败
	const eItemNotEnougth = 2; //道具使用个数不足
	const eItemNotExist = 3; //道具不存在
	const eItemErrBind = 4; //道具为绑定
	const eItemErrUse = 5; //道具无法使用
	const eItemStoreFull = 6; //包裹或仓库满
	const eItemStoreErr = 7; //包裹或仓库错误
	const eItemRangeErr = 8; //道具距离过远
	const eItemNoStack = 9; //道具为非堆叠的
	const eItemNoCoin = 10; //游戏币不足
	const eItemCoinFull = 11; //游戏币超出上限
	const eItemNoMoney = 12; //仙石不足
	const eItemMoneyFull = 13; //充值货币超出上限
	const eItemErrOper = 14; //操作非法
	const eItemErrCD = 15; //CD时间未到
	const eItemErrSlot = 16; //装备位错误
	const eItemNotNeed = 17; //无需此操作
	const eItemErrName = 18; //名字太长
	const eItemExpired = 19; //道具使用时间过期
	const eItemErrSell = 20; //道具无法出售
	const eItemErrDrop = 21; //道具无法丢弃
	const eItemErrLevel = 22; //使用等级不够
	const eItemErrJob = 23; //使用职业限制
	const eItemNoStuff = 24; //材料不足
	const eItemErrDungeon = 25; //副本中无法使用传送卷轴
	const eItemErrTransfMap = 26; //该地图中无法使用传送卷轴
	const eItemMountExist = 27; //已存在该坐骑
	const eItemMutualEquip = 28; //属性类型
	const eItemMutual = 29; //属性类型
	const eItemNoTakeOff = 30; //无法脱下
	const eItemSkillExist = 31; //该技能已存在
	const eItemFashionExist = 32; //该时装已存在
	const eItemStoreMax = 33; //背包已达上限
	const eItemDepotMax = 34; //仓库已达上限
	const eItemErrOther = 35; //其它错误
}

//心法操作结果
class ECittaResult
{
	const eCittaSuccess = 0; //心法操作成功
	const eCittaFailed = 1; //心法操作失败
	const eCittaPackFull = 2; //心法操作时背包已满
	const eCittaMaterialLack = 3; //材料不足
	const eCittaSlotNotEmpty = 4; //心法槽已满
	const eCittaSlotEmpty = 5; //心法槽为空
	const eCittaSilverLack = 6; //银币不足
}

//装备养成结果
class ETrumpResult
{
	const eTrumpSuccess = 0; //法宝养成成功
	const eTrumpFailed = 1; //法宝养成失败
	const eTrumpExist = 2; //法宝已经存在
	const eTrumpNotifyFailed = 3; //法宝通知失败
	const eTrumpNotActived = 4; //法宝未激活
	const eTrumpNotExist = 5; //法宝不存在
	const eTrumpUpgradeMaterialLack = 6; //法宝强化材料不足
	const eTrumpEvolveMaterialLack = 7; //法宝升阶材料不足
	const eTrumpFull = 8; //法宝位已满
	const eTrumpIsEquiped = 9; //法宝已装备
	const eTrumpNotEquiped = 10; //法宝未装备
	const eTrumpActiveFailed = 11; //法宝解锁失败
}

//时装养成结果
class EFashionResult
{
	const eFashionSucc = 0; //时装养成成功
	const eFashionFailed = 1; //时装养成失败
	const eFashionItemErr = 2; //时装养成时所需物品不足
}

//宝石操作
class EGemstoneResult
{
	const eGemstoneSuccess = 0; //宝石操作成功
	const eGemstoneFailed = 1; //宝石操作失败
	const eGemstoneSlotNotEmpty = 2; //宝石位置非空
	const eGemstoneSlotEmpty = 3; //宝石位置空
	const eGemstonePackFull = 4; //包裹满
	const eGemstoneHeroErr = 5; //将错误
	const eGemstoneNoStone = 6; //没有找到宝石
	const eGemstoneErrStone = 7; //宝石合成目标不存在
	const eGemstoneMaterialLack = 8; //宝石材料不足
	const eGemstoneHasSameType = 9; //已经装备相同类型宝石
}

//道具品质
class EItemQuality
{
	const eColorNone = 0; //无
	const eColorGreen = 1; //绿
	const eColorBlue = 2; //蓝
	const eColorPurple = 3; //紫
	const eColorOrange = 4; //橙
	const eColorBlackGold = 5; //暗金
	const eColorEnd = 6; //结束
}

//存储类型
class EStoreType
{
	const eStoreNone = 0; //无
	const eStorePack = 1; //道具包裹
	const eStoreDepot = 2; //角色仓库
	const eStorePlayerTrump = 3; //法宝栏
	const eStorePlayerCitta = 4; //心法栏
	const eStoreFashion = 5; //时装栏
	const eStoreGemstone = 6; //宝石栏
	const eStoreEquipTrump = 7; //装备法宝栏
}

//道具日志类型
class EItemLoggerType
{
	const eItemLogger1 = 0; //试炼塔道具日志
}

//绑定类型
class EBindType
{
	const eBindNone = 0; //未绑定
	const eBindGet = 1; //获取绑定
	const eBindStren = 2; //强化后绑定
}

//绑定优先使用类型
class EBindUseType
{
	const eBindUseNone = 0; //只使用非绑定
	const eBindUseBind = 1; //只使用绑定
	const eBindUseNoneFirst = 2; //优先使用非绑定
	const eBindUseBindFirst = 3; //优先使用绑定
}

//类型大类型
class EItemType
{
	const eItemNone = 0; //无类型
	const eItemResource = 1; //资源道具
	const eItemNormal = 2; //普通道具
	const eItemTrump = 3; //法宝
	const eItemEquipTrump = 4; //装备法宝
	const eItemFashion = 5; //时装
	const eItemFormation = 6; //阵法
	const eItemCitta = 7; //心法
	const eItemIntensify = 8; //强化
	const eItemSkillBook = 9; //技能书
	const eItemStone = 10; //宝石
	const eItemStuff = 11; //材料
	const eItemTask = 12; //任务
	const eItemSpirit = 13; //注灵
	const eItemSoul = 14; //元神
	const eItemNeidan = 15; //灵宠内丹
	const eItemVigour = 16; //灵宠精魄
	const eItemOther = 17; //其他
	const eItemEnd = 18;
}

//物品子类型
class EItemSubType
{
	const eItemSubNone = 0; //无类型
	const eItemSubResource = 1; //资源
	const eItemSubNormal = 2; //普通
	const eItemSubFasionMaterial = 10; //时装激活材料
	const eItemSubZTMaterial = 20; //本命法宝温养材料
	const eItemSubWepaon = 21; //武器
	const eItemSubRing = 22; //戒指
	const eItemSubNeck = 23; //项链
	const eItemSubHead = 24; //头盔
	const eItemSubChest = 25; //胸甲
	const eItemSubLegging = 26; //护腿
	const eItemSubMounts = 30; //坐骑
	const eItemSubActiveTrump = 32; //主动法宝
	const eItemSubPassiveTrump = 33; //被动法宝
	const eItemSubFashion = 51; //时装-神器
	const eItemSubFashion2 = 52; //时装-神衣
	const eItemSubSpirit = 141; //注灵
	const eItemSubPetSoul = 151; //兽魂
	const eItemSubEquipTrumpInnate = 205; //先天
	const eItemSubEquipTrumpPassive = 206; //被动
	const eItemSubEquipTrumpTransform = 207; //光环
	const eItemSubEquipTrumpHalo = 208; //变身
}

//法宝位类型
class ETrumpSlotType
{
	const eSlotTrump1 = 0; //法宝1
	const eSlotTrump2 = 1; //法宝2
	const eSlotTrump3 = 2; //法宝3
	const eSlotTrump4 = 3; //法宝4
	const eSlotTrump5 = 4; //法宝5
	const eSlotTrump6 = 5; //法宝6
	const eSlotTrump7 = 6; //法宝7
	const eSlotTrump8 = 7; //法宝8
	const eSlotTrump9 = 8; //法宝9
	const eSlotTrump10 = 9; //法宝10
}

//心法位类型
class ECittaSlotType
{
	const eSlotCitta1 = 0; //心法1
	const eSlotCitta2 = 1; //心法2
	const eSlotCitta3 = 2; //心法3
	const eSlotCitta4 = 3; //心法4
	const eSlotCitta5 = 4; //心法5
	const eSlotCitta6 = 5; //心法6
	const eSlotCitta7 = 6; //心法7
	const eSlotCitta8 = 7; //心法8
}

//心法姓名前缀类型
class ECittaNameType
{
	const eNameNone = 0; //破烂之
	const eNameAttack = 1; //力量之
	const eNameDefence = 2; //坚固的
	const eNameMgcDefence = 3; //道心之
	const eNameHP = 4; //长生的
	const eNameHit = 5; //神佑的
	const eNameDodge = 6; //灵猴的
	const eNameCritical = 7; //刺客的
	const eNameAntiCri = 8; //平衡的
	const eNamePiece = 9; //破击之
	const eNameCounter = 10; //反击之
	const eNameResist = 11; //压制的
}

//结构体：SItem的继承体系类型
class EType_SItem
{
	const eType_SItem = 0; //类型：SItem
	const eType_SStack = 1; //类型：SStack
	const eType_SEquipTrump = 2; //类型：SEquipTrump
	const eType_SCitta = 3; //类型：SCitta
	const eType_STrump = 4; //类型：STrump
	const eType_SFashion = 5; //类型：SFashion
	const eType_SGemstone = 6; //类型：SGemstone
}

//显示用的模板数据
final class SItemGenInfo
{
	public $wItemID; //(UINT16)模板ID
	public $dwCount; //(UINT32)数量
	public $byQuality; //(UINT8)品质
	public $eBindType; //(枚举类型：EBindType)绑定类型
	public $dwTimeID; //(UINT32)时钟ID

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->dwCount = 0;
		$this->byQuality = 0;
		$this->eBindType = 0;
		$this->dwTimeID = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->dwCount = $this->dwCount;
		$obj->byQuality = $this->byQuality;
		$obj->eBindType = $this->eBindType;
		$obj->dwTimeID = $this->dwTimeID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SItemGenInfo;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		$s->byQuality = ByteUtil::readUINT8($data);
		$s->eBindType = ByteUtil::readUINT8($data);
		$s->dwTimeID = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItemGenInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT32($data, $this->dwCount);
		ByteUtil::writeUINT8($data, $this->byQuality);
		ByteUtil::writeUINT8($data, $this->eBindType);
		ByteUtil::writeUINT32($data, $this->dwTimeID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//物品列表
final class SInstCount
{
	public $qwInstID; //(UINT64)道具唯一ID
	public $wCount; //(UINT32)道具个数

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->wCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->wCount = $this->wCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SInstCount;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->wCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SInstCount::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT32($data, $this->wCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//物品列表
final class SItemCount
{
	public $wItemID; //(UINT16)道具ID
	public $wCount; //(UINT32)道具个数

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->wCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->wCount = $this->wCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SItemCount;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->wCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItemCount::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT32($data, $this->wCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//资源列表
final class SResource
{
	public $_eRes; //(枚类型：ProtoCommon::EMoneyType)资源(货币)类型
	public $_dwValue; //(UINT32)资源(货币)数量

	//构造函数
	function __construct()
	{
		$this->_eRes = 0;
		$this->_dwValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->_eRes = $this->_eRes;
		$obj->_dwValue = $this->_dwValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SResource;
		$s->_eRes = ByteUtil::readUINT8($data);
		$s->_dwValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SResource::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->_eRes);
		ByteUtil::writeUINT32($data, $this->_dwValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//EDataType:eRoleItemInfo
final class RoleItemInfo
{
	public $qwInstID; //(UINT64)物品唯一ID
	public $wItemID; //(UINT16)物品模板
	public $byStoreType; //(UINT8)背包类型-数据来源：EStoreType
	public $wIndex; //(INT16)所属背包的位置
	public $wCount; //(UINT16)具的堆叠数
	public $byBind; //(UINT8)绑定类型0非绑定，1绑定
	public $byExpired; //(UINT8)是否时效，>0 时效物品
	public $dwExpireTime; //(UINT32)时效过期时间
	public $dwMark; //(UINT32)标记为错误物品,存下标记时间

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->wItemID = 0;
		$this->byStoreType = 0;
		$this->wIndex = 0;
		$this->wCount = 0;
		$this->byBind = 0;
		$this->byExpired = 0;
		$this->dwExpireTime = 0;
		$this->dwMark = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->wItemID = $this->wItemID;
		$obj->byStoreType = $this->byStoreType;
		$obj->wIndex = $this->wIndex;
		$obj->wCount = $this->wCount;
		$obj->byBind = $this->byBind;
		$obj->byExpired = $this->byExpired;
		$obj->dwExpireTime = $this->dwExpireTime;
		$obj->dwMark = $this->dwMark;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new RoleItemInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->byStoreType = ByteUtil::readUINT8($data);
		$s->wIndex = ByteUtil::readINT16($data);
		$s->wCount = ByteUtil::readUINT16($data);
		$s->byBind = ByteUtil::readUINT8($data);
		$s->byExpired = ByteUtil::readUINT8($data);
		$s->dwExpireTime = ByteUtil::readUINT32($data);
		$s->dwMark = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = RoleItemInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT8($data, $this->byStoreType);
		ByteUtil::writeINT16($data, $this->wIndex);
		ByteUtil::writeUINT16($data, $this->wCount);
		ByteUtil::writeUINT8($data, $this->byBind);
		ByteUtil::writeUINT8($data, $this->byExpired);
		ByteUtil::writeUINT32($data, $this->dwExpireTime);
		ByteUtil::writeUINT32($data, $this->dwMark);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//洗炼信息
final class SShuffleInfo
{
	public $dwType; //(UINT32)洗炼类型
	public $dwValue; //(UINT32)洗炼数值

	//构造函数
	function __construct()
	{
		$this->dwType = 0;
		$this->dwValue = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwType = $this->dwType;
		$obj->dwValue = $this->dwValue;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SShuffleInfo;
		$s->dwType = ByteUtil::readUINT32($data);
		$s->dwValue = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SShuffleInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwType);
		ByteUtil::writeUINT32($data, $this->dwValue);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//道具的信息
class SItem
{
	public $sItemInfo; //(类类型：RoleItemInfo)道具信息

	//构造函数
	function __construct()
	{
		$this->sItemInfo = new RoleItemInfo;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SItem;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->sItemInfo = $this->sItemInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SItem;
		$s->sItemInfo = RoleItemInfo::fromStream($data);
		return $s;
	}

	static function superFromStream(&$data)
	{
		$eType = ByteUtil::readUINT8($data);
		switch($eType)
		{
			case EType_SItem::eType_SItem:
				$s = SItem::fromStream($data);
				break;
			case EType_SItem::eType_SStack:
				$s = SStack::fromStream($data);
				break;
			case EType_SItem::eType_SEquipTrump:
				$s = SEquipTrump::fromStream($data);
				break;
			case EType_SItem::eType_SCitta:
				$s = SCitta::fromStream($data);
				break;
			case EType_SItem::eType_STrump:
				$s = STrump::fromStream($data);
				break;
			case EType_SItem::eType_SFashion:
				$s = SFashion::fromStream($data);
				break;
			case EType_SItem::eType_SGemstone:
				$s = SGemstone::fromStream($data);
				break;
			default:
				throw new Exception('Unknown value for EType_SItem:'.eType);
		}
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItem::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	static function superVectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItem::superFromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		$this->sItemInfo->toStream($data);
	}

	public function superToStream(&$data)
	{
		$eType = $this->getClassType();
		ByteUtil::writeUINT8($data, $eType);
		$this->toStream($data);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}

	static function superVectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->superToStream($data);
	}
}

//堆叠道具的信息，只用于识别
final class SStack extends SItem
{
	//构造函数
	function __construct()
	{
		parent::__construct();
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SStack;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SStack;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SStack::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//装备的信息
final class SEquipTrump extends SItem
{
	public $qwOwnerID; //(UINT64)散仙唯一ID，属于散仙的物品时有效
	public $byIntensifyLvl; //(UINT8)当前强化等级
	public $byIntensifyLvlMax; //(UINT8)可强的最高等级
	public $dwBlessing; //(UINT32)强化祝福值
	public $vecShuffleInfo; //(SShuffleInfo的数组)洗炼信息
	public $vecNowReplace; //(SShuffleInfo的数组)可替换的洗炼信息
	public $dwXiLianBlessing; //(UINT32)洗练祝福值

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->qwOwnerID = new Math_BigInteger;
		$this->byIntensifyLvl = 0;
		$this->byIntensifyLvlMax = 0;
		$this->dwBlessing = 0;
		$this->vecShuffleInfo = array();
		$this->vecNowReplace = array();
		$this->dwXiLianBlessing = 0;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SEquipTrump;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->qwOwnerID = $this->qwOwnerID;
		$obj->byIntensifyLvl = $this->byIntensifyLvl;
		$obj->byIntensifyLvlMax = $this->byIntensifyLvlMax;
		$obj->dwBlessing = $this->dwBlessing;
		$obj->vecShuffleInfo = $this->vecShuffleInfo;
		$obj->vecNowReplace = $this->vecNowReplace;
		$obj->dwXiLianBlessing = $this->dwXiLianBlessing;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SEquipTrump;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		$s->byIntensifyLvl = ByteUtil::readUINT8($data);
		$s->byIntensifyLvlMax = ByteUtil::readUINT8($data);
		$s->dwBlessing = ByteUtil::readUINT32($data);
		$s->vecShuffleInfo = SShuffleInfo::vectorFromStream($data);
		$s->vecNowReplace = SShuffleInfo::vectorFromStream($data);
		$s->dwXiLianBlessing = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SEquipTrump::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
		ByteUtil::writeUINT8($data, $this->byIntensifyLvl);
		ByteUtil::writeUINT8($data, $this->byIntensifyLvlMax);
		ByteUtil::writeUINT32($data, $this->dwBlessing);
		SShuffleInfo::vectorToStream($data, $this->vecShuffleInfo);
		SShuffleInfo::vectorToStream($data, $this->vecNowReplace);
		ByteUtil::writeUINT32($data, $this->dwXiLianBlessing);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//心法的信息
final class SCitta extends SItem
{
	public $qwOwnerID; //(UINT64)散仙唯一ID，属于散仙的物品时有效
	public $eCittaNameType; //(枚举类型：ECittaNameType)心法姓名前缀
	public $oAttrVec; //(SFtAttrMod的数组)增加属性
	public $dwSkillID; //(UINT32)附加技能ID
	public $dwSignetID; //(UINT32)印记ID

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->qwOwnerID = new Math_BigInteger;
		$this->eCittaNameType = 0;
		$this->oAttrVec = array();
		$this->dwSkillID = 0;
		$this->dwSignetID = 0;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SCitta;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->qwOwnerID = $this->qwOwnerID;
		$obj->eCittaNameType = $this->eCittaNameType;
		$obj->oAttrVec = $this->oAttrVec;
		$obj->dwSkillID = $this->dwSkillID;
		$obj->dwSignetID = $this->dwSignetID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SCitta;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		$s->eCittaNameType = ByteUtil::readUINT8($data);
		$s->oAttrVec = SFtAttrMod::vectorFromStream($data);
		$s->dwSkillID = ByteUtil::readUINT32($data);
		$s->dwSignetID = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SCitta::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
		ByteUtil::writeUINT8($data, $this->eCittaNameType);
		SFtAttrMod::vectorToStream($data, $this->oAttrVec);
		ByteUtil::writeUINT32($data, $this->dwSkillID);
		ByteUtil::writeUINT32($data, $this->dwSignetID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//法宝信息
final class STrump extends SItem
{
	public $qwRoleID; //(UINT64)拥有者RoleID
	public $byActived; //(UINT8)
	public $byUsed; //(UINT8)法宝是否出战
	public $dwExp; //(UINT32)法宝祭炼值
	public $wLevel; //(UINT16)法宝祭炼等级
	public $wRank; //(UINT16)法宝祭炼阶数

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->qwRoleID = new Math_BigInteger;
		$this->byActived = 0;
		$this->byUsed = 0;
		$this->dwExp = 0;
		$this->wLevel = 0;
		$this->wRank = 0;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_STrump;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->qwRoleID = $this->qwRoleID;
		$obj->byActived = $this->byActived;
		$obj->byUsed = $this->byUsed;
		$obj->dwExp = $this->dwExp;
		$obj->wLevel = $this->wLevel;
		$obj->wRank = $this->wRank;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STrump;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->byActived = ByteUtil::readUINT8($data);
		$s->byUsed = ByteUtil::readUINT8($data);
		$s->dwExp = ByteUtil::readUINT32($data);
		$s->wLevel = ByteUtil::readUINT16($data);
		$s->wRank = ByteUtil::readUINT16($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STrump::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT8($data, $this->byActived);
		ByteUtil::writeUINT8($data, $this->byUsed);
		ByteUtil::writeUINT32($data, $this->dwExp);
		ByteUtil::writeUINT16($data, $this->wLevel);
		ByteUtil::writeUINT16($data, $this->wRank);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//时装信息
final class SFashion extends SItem
{
	public $byLevel; //(UINT8)时装等级
	public $dwExp; //(UINT32)时装经验
	public $bySelected; //(UINT8)是否选中
	public $byHide; //(UINT8)是否隐藏

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->byLevel = 0;
		$this->dwExp = 0;
		$this->bySelected = 0;
		$this->byHide = 0;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SFashion;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->byLevel = $this->byLevel;
		$obj->dwExp = $this->dwExp;
		$obj->bySelected = $this->bySelected;
		$obj->byHide = $this->byHide;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFashion;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->dwExp = ByteUtil::readUINT32($data);
		$s->bySelected = ByteUtil::readUINT8($data);
		$s->byHide = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFashion::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT32($data, $this->dwExp);
		ByteUtil::writeUINT8($data, $this->bySelected);
		ByteUtil::writeUINT8($data, $this->byHide);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//宝石信息
final class SGemstone extends SItem
{
	public $qwOwnerID; //(UINT64)散仙唯一ID

	//构造函数
	function __construct()
	{
		parent::__construct();
		$this->qwOwnerID = new Math_BigInteger;
	}

	//获取继承类的类型
	function getClassType()
	{
		return EType_SItem::eType_SGemstone;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		parent::copyTo($obj);
		$obj->qwOwnerID = $this->qwOwnerID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SGemstone;
		$base = SItem::fromStream($data);
		$base->copyTo($s);
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SGemstone::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		parent::toStream($data);
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//背包信息
final class SStoreStream
{
	public $wCapacity; //(UINT16)背包大小(不发最大值，最大值由两端的配置决定)
	public $vecItem; //(SItem的数组)物品信息

	//构造函数
	function __construct()
	{
		$this->wCapacity = 0;
		$this->vecItem = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wCapacity = $this->wCapacity;
		$obj->vecItem = $this->vecItem;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SStoreStream;
		$s->wCapacity = ByteUtil::readUINT16($data);
		$s->vecItem = SItem::superVectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SStoreStream::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wCapacity);
		SItem::superVectorToStream($data, $this->vecItem);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家道具冷却时间
final class SItemColdTime
{
	public $wID; //(UINT16)冷却ID
	public $dwTime; //(UINT32)冷却到期时间

	//构造函数
	function __construct()
	{
		$this->wID = 0;
		$this->dwTime = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wID = $this->wID;
		$obj->dwTime = $this->dwTime;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SItemColdTime;
		$s->wID = ByteUtil::readUINT16($data);
		$s->dwTime = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SItemColdTime::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wID);
		ByteUtil::writeUINT32($data, $this->dwTime);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家获得道具
final class SAddItemMsg
{
	public $wItemID; //(UINT16)道具的ID
	public $wCount; //(UINT16)道具个数
	public $byQuality; //(UINT8)道具品质

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->wCount = 0;
		$this->byQuality = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->wCount = $this->wCount;
		$obj->byQuality = $this->byQuality;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SAddItemMsg;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->wCount = ByteUtil::readUINT16($data);
		$s->byQuality = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SAddItemMsg::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT16($data, $this->wCount);
		ByteUtil::writeUINT8($data, $this->byQuality);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//记录的道具
final class SLoggedItem
{
	public $wItemID; //(UINT16)道具ID
	public $byQuality; //(UINT8)品质
	public $dwCount; //(UINT32)道具个数
	public $bBind; //(bool)是否绑定

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->byQuality = 0;
		$this->dwCount = 0;
		$this->bBind = false;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->byQuality = $this->byQuality;
		$obj->dwCount = $this->dwCount;
		$obj->bBind = $this->bBind;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SLoggedItem;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->byQuality = ByteUtil::readUINT8($data);
		$s->dwCount = ByteUtil::readUINT32($data);
		$s->bBind = ByteUtil::readBool($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SLoggedItem::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT8($data, $this->byQuality);
		ByteUtil::writeUINT32($data, $this->dwCount);
		ByteUtil::writeBool($data, $this->bBind);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//收件人信息
final class SGMMailTarget
{
	public $qwTargetID; //(UINT64)收件人ID
	public $strTarget; //(string)收件人名

	//构造函数
	function __construct()
	{
		$this->qwTargetID = new Math_BigInteger;
		$this->strTarget = '';
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwTargetID = $this->qwTargetID;
		$obj->strTarget = $this->strTarget;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SGMMailTarget;
		$s->qwTargetID = ByteUtil::readUINT64($data);
		$s->strTarget = ByteUtil::readString($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SGMMailTarget::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwTargetID);
		ByteUtil::writeString($data, $this->strTarget);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//道具信息
final class SGMMailItem
{
	public $wItemID; //(UINT16)道具配置ID
	public $wItemCount; //(UINT32)道具数量

	//构造函数
	function __construct()
	{
		$this->wItemID = 0;
		$this->wItemCount = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wItemID = $this->wItemID;
		$obj->wItemCount = $this->wItemCount;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SGMMailItem;
		$s->wItemID = ByteUtil::readUINT16($data);
		$s->wItemCount = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SGMMailItem::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wItemID);
		ByteUtil::writeUINT32($data, $this->wItemCount);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[GetStore:请求包裹信息(整个包裹)]的原来的参数组成的结构体
class SOrigParam_GetStore
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
	}
};

//函数[GetStore:请求包裹信息(整个包裹)]的返回的参数组成的结构体
class SRetParam_GetStore
{
	public $stStoreStream; //(类类型：SStoreStream)背包信息
	public $dwNextUnlockTime; //(UINT32)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒

	//构造函数
	function __construct()
	{
		$this->stStoreStream = new SStoreStream;
		$this->dwNextUnlockTime = 0;
	}
};

//函数[UseItem:请求使用包裹中的道具]的原来的参数组成的结构体
class SOrigParam_UseItem
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwRoleID; //(UINT64)针对的角色ID
	public $qwMercenID; //(UINT64)针对的佣兵ID
	public $qwInstID; //(UINT64)优先使用的物品实例ID
	public $wStack; //(UINT16)使用个数(只针对堆叠道具)

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwRoleID = new Math_BigInteger;
		$this->qwMercenID = new Math_BigInteger;
		$this->qwInstID = new Math_BigInteger;
		$this->wStack = 0;
	}
};

//函数[UseItem:请求使用包裹中的道具]的返回的参数组成的结构体
class SRetParam_UseItem
{
	public $eResult; //(枚举类型：EItemResult)使用道具结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[ExpandStore:扩充包裹或仓库]的返回的参数组成的结构体
class SRetParam_ExpandStore
{
	public $eResult; //(枚举类型：EItemResult)扩充结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[RelocateStoreItem:包裹或仓库中道具换位置]的原来的参数组成的结构体
class SOrigParam_RelocateStoreItem
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwInstID; //(UINT64)道具的实例ID

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwInstID = new Math_BigInteger;
	}
};

//函数[RelocateStoreItem:包裹或仓库中道具换位置]的返回的参数组成的结构体
class SRetParam_RelocateStoreItem
{
	public $eResult; //(枚举类型：EItemResult)换位置的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[TidyupStore:整理包裹或仓库]的原来的参数组成的结构体
class SOrigParam_TidyupStore
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
	}
};

//函数[TidyupStore:整理包裹或仓库]的返回的参数组成的结构体
class SRetParam_TidyupStore
{
	public $eResult; //(枚举类型：EItemResult)整理的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[SplitStackItem:拆分包裹或仓库中的堆叠类道具]的原来的参数组成的结构体
class SOrigParam_SplitStackItem
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwInstID; //(UINT64)道具的实例ID

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwInstID = new Math_BigInteger;
	}
};

//函数[SplitStackItem:拆分包裹或仓库中的堆叠类道具]的返回的参数组成的结构体
class SRetParam_SplitStackItem
{
	public $eResult; //(枚举类型：EItemResult)拆分的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[MergeStackItem:合并包裹或仓库中的堆叠类道具]的原来的参数组成的结构体
class SOrigParam_MergeStackItem
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwFromInstID; //(UINT64)源道具的实例ID
	public $qwToInstID; //(UINT64)目的道具的实例ID

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwFromInstID = new Math_BigInteger;
		$this->qwToInstID = new Math_BigInteger;
	}
};

//函数[MergeStackItem:合并包裹或仓库中的堆叠类道具]的返回的参数组成的结构体
class SRetParam_MergeStackItem
{
	public $eResult; //(枚举类型：EItemResult)合并的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[DestroyStoreItem:销毁包裹或仓库中的道具]的原来的参数组成的结构体
class SOrigParam_DestroyStoreItem
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwInstID; //(UINT64)道具的实例ID

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwInstID = new Math_BigInteger;
	}
};

//函数[DestroyStoreItem:销毁包裹或仓库中的道具]的返回的参数组成的结构体
class SRetParam_DestroyStoreItem
{
	public $eResult; //(枚举类型：EItemResult)销毁的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[TransferItem:在包裹和仓库之间移动道具]的返回的参数组成的结构体
class SRetParam_TransferItem
{
	public $eResult; //(枚举类型：EItemResult)移动的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[SellItem:请求出售包裹中的道具-出售给系统]的原来的参数组成的结构体
class SOrigParam_SellItem
{
	public $vecInstID; //(UINT64数组)出售的道具实例ID集合

	//构造函数
	function __construct()
	{
		$this->vecInstID = array();
	}
};

//函数[SellItem:请求出售包裹中的道具-出售给系统]的返回的参数组成的结构体
class SRetParam_SellItem
{
	public $eResult; //(枚举类型：EItemResult)使用道具结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[SellItemWithCount:请求按个数出售包裹中的道具-出售给系统]的原来的参数组成的结构体
class SOrigParam_SellItemWithCount
{
	public $eStoreType; //(枚举类型：EStoreType)存储类型
	public $qwInstID; //(UINT64)优先卖出的物品实例ID
	public $wStack; //(UINT16)卖出个数

	//构造函数
	function __construct()
	{
		$this->eStoreType = 0;
		$this->qwInstID = new Math_BigInteger;
		$this->wStack = 0;
	}
};

//函数[SellItemWithCount:请求按个数出售包裹中的道具-出售给系统]的返回的参数组成的结构体
class SRetParam_SellItemWithCount
{
	public $eResult; //(枚举类型：EItemResult)卖出道具结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[UnlockPack:解锁背包格子]的返回的参数组成的结构体
class SRetParam_UnlockPack
{
	public $eResult; //(枚举类型：EItemResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[RecordTransfPoint:记录传送点]的返回的参数组成的结构体
class SRetParam_RecordTransfPoint
{
	public $eResult; //(枚举类型：EItemResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[TransfMapPoint:传送]的返回的参数组成的结构体
class SRetParam_TransfMapPoint
{
	public $eResult; //(枚举类型：EItemResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[WearCitta:请求装备心法]的原来的参数组成的结构体
class SOrigParam_WearCitta
{
	public $qwInstID; //(UINT64)装备的实例ID
	public $eSlotType; //(枚举类型：ECittaSlotType)装备位的类型

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->eSlotType = 0;
	}
};

//函数[WearCitta:请求装备心法]的返回的参数组成的结构体
class SRetParam_WearCitta
{
	public $eResult; //(枚举类型：ECittaResult)穿上装备的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[TakeoffCitta:请求卸下心法]的原来的参数组成的结构体
class SOrigParam_TakeoffCitta
{
	public $eSlotType; //(枚举类型：ECittaSlotType)装备位的类型
	public $wIndex; //(INT16)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置

	//构造函数
	function __construct()
	{
		$this->eSlotType = 0;
		$this->wIndex = 0;
	}
};

//函数[TakeoffCitta:请求卸下心法]的返回的参数组成的结构体
class SRetParam_TakeoffCitta
{
	public $eResult; //(枚举类型：ECittaResult)脱下装备的结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[MergeCitta:请求合成心法]的返回的参数组成的结构体
class SRetParam_MergeCitta
{
	public $eResult; //(枚举类型：ECittaResult)结果
	public $vecItemCitta; //(SItem的数组)新增的道具

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecItemCitta = array();
	}
};

//函数[BreakCitta:请求分解心法]的返回的参数组成的结构体
class SRetParam_BreakCitta
{
	public $eResult; //(枚举类型：ECittaResult)结果
	public $vecItemInfo; //(SItemGenInfo的数组)分解产生的道具

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecItemInfo = array();
	}
};

//函数[ActiveTrump:激活法宝]的返回的参数组成的结构体
class SRetParam_ActiveTrump
{
	public $eResult; //(枚举类型：ETrumpResult)结果
	public $vecTrump; //(STrump的数组)新法宝

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecTrump = array();
	}
};

//函数[EquipTrump:出战法宝]的返回的参数组成的结构体
class SRetParam_EquipTrump
{
	public $eResult; //(枚举类型：ETrumpResult)结果
	public $vecTrump; //(STrump的数组)新法宝

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecTrump = array();
	}
};

//函数[UnEquipTrump:卸下法宝]的返回的参数组成的结构体
class SRetParam_UnEquipTrump
{
	public $eResult; //(枚举类型：ETrumpResult)结果
	public $vecTrump; //(STrump的数组)新法宝

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecTrump = array();
	}
};

//函数[UpgradeTrump:祭炼法宝]的返回的参数组成的结构体
class SRetParam_UpgradeTrump
{
	public $eResult; //(枚举类型：ETrumpResult)结果
	public $vecTrump; //(STrump的数组)新法宝

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecTrump = array();
	}
};

//函数[EvolveTrump:提升法宝品级]的返回的参数组成的结构体
class SRetParam_EvolveTrump
{
	public $eResult; //(枚举类型：ETrumpResult)结果
	public $vecTrump; //(STrump的数组)新法宝

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecTrump = array();
	}
};

//函数[FashionActive:激活时装]的返回的参数组成的结构体
class SRetParam_FashionActive
{
	public $eResult; //(枚举类型：EFashionResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FashionHide:隐藏所选时装]的返回的参数组成的结构体
class SRetParam_FashionHide
{
	public $eResult; //(枚举类型：EFashionResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FashionChange:选择时装]的返回的参数组成的结构体
class SRetParam_FashionChange
{
	public $eResult; //(枚举类型：EFashionResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FashionUpgrade:时装炼化]的返回的参数组成的结构体
class SRetParam_FashionUpgrade
{
	public $eResult; //(枚举类型：EFashionResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[WareGemStone:穿戴宝石]的返回的参数组成的结构体
class SRetParam_WareGemStone
{
	public $eResult; //(枚举类型：EGemstoneResult)结果
	public $qwFighterID; //(UINT64)将ID
	public $byPos; //(UINT8)穿戴位置
	public $Item; //(类类型：SGemstone)宝石

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->qwFighterID = new Math_BigInteger;
		$this->byPos = 0;
		$this->Item = new SGemstone;
	}
};

//函数[TakeOffGemStone:取下宝石]的返回的参数组成的结构体
class SRetParam_TakeOffGemStone
{
	public $eResult; //(枚举类型：EGemstoneResult)结果
	public $qwFighterID; //(UINT64)将ID
	public $byPos; //(UINT8)穿戴位置

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->qwFighterID = new Math_BigInteger;
		$this->byPos = 0;
	}
};

//函数[ComposeGemStone:合成宝石]的返回的参数组成的结构体
class SRetParam_ComposeGemStone
{
	public $eResult; //(枚举类型：EGemstoneResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[ComposeGemStoneOneKey:一键合成宝石]的返回的参数组成的结构体
class SRetParam_ComposeGemStoneOneKey
{
	public $eResult; //(枚举类型：EGemstoneResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：道具相关协议
abstract class ItemProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：请求包裹信息(整个包裹)
	function send_GetStore(
		$eStoreType //(枚举类型：EStoreType)存储类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$origParam = new SOrigParam_GetStore;
		$origParam->eStoreType = $eStoreType;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求使用包裹中的道具
	function send_UseItem(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwRoleID,  //(UINT64)针对的角色ID
		$qwMercenID,  //(UINT64)针对的佣兵ID
		$qwInstID,  //(UINT64)优先使用的物品实例ID
		$wStack //(UINT16)使用个数(只针对堆叠道具)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$origParam = new SOrigParam_UseItem;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwRoleID = $qwRoleID;
		$origParam->qwMercenID = $qwMercenID;
		$origParam->qwInstID = $qwInstID;
		$origParam->wStack = $wStack;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwRoleID);
		ByteUtil::writeUINT64($data, $qwMercenID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wStack);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：扩充包裹或仓库
	function send_ExpandStore(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$byCount,  //(UINT8)扩充个数
		$eCoinType //(枚类型：ProtoCommon::ECoinType)货币类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT8($data, $byCount);
		ByteUtil::writeUINT8($data, $eCoinType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：包裹或仓库中道具换位置
	function send_RelocateStoreItem(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwInstID,  //(UINT64)道具的实例ID
		$wNewIndex //(INT16)道具在包裹中新的位置0开始
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$origParam = new SOrigParam_RelocateStoreItem;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwInstID = $qwInstID;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeINT16($data, $wNewIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：整理包裹或仓库
	function send_TidyupStore(
		$eStoreType //(枚举类型：EStoreType)存储类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$origParam = new SOrigParam_TidyupStore;
		$origParam->eStoreType = $eStoreType;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：拆分包裹或仓库中的堆叠类道具
	function send_SplitStackItem(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwInstID,  //(UINT64)道具的实例ID
		$wStack,  //(UINT16)拆分出来的堆叠数量
		$wIndex //(INT16)拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 6);
		$origParam = new SOrigParam_SplitStackItem;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwInstID = $qwInstID;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wStack);
		ByteUtil::writeINT16($data, $wIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：合并包裹或仓库中的堆叠类道具
	function send_MergeStackItem(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwFromInstID,  //(UINT64)源道具的实例ID
		$qwToInstID //(UINT64)目的道具的实例ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$origParam = new SOrigParam_MergeStackItem;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwFromInstID = $qwFromInstID;
		$origParam->qwToInstID = $qwToInstID;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwFromInstID);
		ByteUtil::writeUINT64($data, $qwToInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：销毁包裹或仓库中的道具
	function send_DestroyStoreItem(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwInstID //(UINT64)道具的实例ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$origParam = new SOrigParam_DestroyStoreItem;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwInstID = $qwInstID;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：在包裹和仓库之间移动道具
	function send_TransferItem(
		$eFromStoreType,  //(枚举类型：EStoreType)源存储类型
		$eToStoreType,  //(枚举类型：EStoreType)目的存储类型
		$qwInstID,  //(UINT64)道具的实例ID
		$wIndex //(INT16)道具在目的存储中的位置(-1表示选第一个空位)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eFromStoreType);
		ByteUtil::writeUINT8($data, $eToStoreType);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeINT16($data, $wIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求出售包裹中的道具-出售给系统
	function send_SellItem(
		$vecInstID //(UINT64数组)出售的道具实例ID集合
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 10);
		$origParam = new SOrigParam_SellItem;
		$origParam->vecInstID = $vecInstID;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeVecUINT64($data, $vecInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求按个数出售包裹中的道具-出售给系统
	function send_SellItemWithCount(
		$eStoreType,  //(枚举类型：EStoreType)存储类型
		$qwInstID,  //(UINT64)优先卖出的物品实例ID
		$wStack //(UINT16)卖出个数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 11);
		$origParam = new SOrigParam_SellItemWithCount;
		$origParam->eStoreType = $eStoreType;
		$origParam->qwInstID = $qwInstID;
		$origParam->wStack = $wStack;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 11;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eStoreType);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wStack);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：解锁背包格子
	function send_UnlockPack(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 12);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 12;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：打开道具日志
	function send_OpenItemLogger(
		$eType //(枚举类型：EItemLoggerType)
	)
	{
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 13;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT8($data, $eType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：记录传送点
	function send_RecordTransfPoint(
		$qwInstID,  //(UINT64)道具ID
		$wIndex //(UINT16)存储序号
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 13);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 14;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：传送
	function send_TransfMapPoint(
		$qwInstID,  //(UINT64)道具ID
		$wIndex,  //(UINT16)存储序号
		$wMapID //(UINT16)地图ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 14);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 15;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT16($data, $wIndex);
		ByteUtil::writeUINT16($data, $wMapID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求装备心法
	function send_WearCitta(
		$qwInstID,  //(UINT64)装备的实例ID
		$eSlotType //(枚举类型：ECittaSlotType)装备位的类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 15);
		$origParam = new SOrigParam_WearCitta;
		$origParam->qwInstID = $qwInstID;
		$origParam->eSlotType = $eSlotType;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 16;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeINT8($data, $eSlotType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求卸下心法
	function send_TakeoffCitta(
		$eSlotType,  //(枚举类型：ECittaSlotType)装备位的类型
		$wIndex //(INT16)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 16);
		$origParam = new SOrigParam_TakeoffCitta;
		$origParam->eSlotType = $eSlotType;
		$origParam->wIndex = $wIndex;
		$this->_sessionMgr->storeData($sessionID, $origParam);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 17;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeINT8($data, $eSlotType);
		ByteUtil::writeINT16($data, $wIndex);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求合成心法
	function send_MergeCitta(
		$eBindType,  //(枚举类型：EBindUseType)绑定使用方式
		$wItemID,  //(UINT16)制作心法模版ID
		$wCount //(UINT16)制作数量
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 17);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 18;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eBindType);
		ByteUtil::writeUINT16($data, $wItemID);
		ByteUtil::writeUINT16($data, $wCount);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求分解心法
	function send_BreakCitta(
		$vecInstID //(UINT64数组)物品唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 18);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 19;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeVecUINT64($data, $vecInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：激活法宝
	function send_ActiveTrump(
		$wItemID //(UINT16)法宝道具ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 19);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 20;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wItemID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：出战法宝
	function send_EquipTrump(
		$qwInstID //(UINT64)法宝的实例ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 20);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 21;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：卸下法宝
	function send_UnEquipTrump(
		$qwInstID //(UINT64)法宝的实例ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 21);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 22;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：祭炼法宝
	function send_UpgradeTrump(
		$qwInstID,  //(UINT64)法宝的实例ID
		$byOneKey //(UINT8)是否一键
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 22);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 23;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT8($data, $byOneKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：提升法宝品级
	function send_EvolveTrump(
		$qwInstID //(UINT64)法宝的实例ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 23);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 24;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：激活时装
	function send_FashionActive(
		$wItemID //(UINT16)时装物品ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 24);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 25;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wItemID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：隐藏所选时装
	function send_FashionHide(
		$byType,  //(UINT8)0-神器时装 1-神依时装
		$byHide //(UINT8)0-显示 1-隐藏
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 25);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 26;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byType);
		ByteUtil::writeUINT8($data, $byHide);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：选择时装
	function send_FashionChange(
		$qwInstID //(UINT64)时装唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 26);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 27;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：时装炼化
	function send_FashionUpgrade(
		$qwInstID,  //(UINT64)时装物品ID
		$byOneKey //(UINT8)是否一键
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 27);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 28;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT8($data, $byOneKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：穿戴宝石
	function send_WareGemStone(
		$wItemID,  //(UINT16)宝石模板ID
		$qwFighterID,  //(UINT64)将ID
		$byPos //(UINT8)穿戴位置
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 28);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 29;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wItemID);
		ByteUtil::writeUINT64($data, $qwFighterID);
		ByteUtil::writeUINT8($data, $byPos);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：取下宝石
	function send_TakeOffGemStone(
		$qwFighterID,  //(UINT64)将ID
		$byPos //(UINT8)穿戴位置0~5,6表示全部卸下
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 29);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 30;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwFighterID);
		ByteUtil::writeUINT8($data, $byPos);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：合成宝石
	function send_ComposeGemStone(
		$wItemID,  //(UINT16)宝石模板ID
		$dwNum //(UINT32)合成数量
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 30);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 31;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wItemID);
		ByteUtil::writeUINT32($data, $dwNum);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：一键合成宝石
	function send_ComposeGemStoneOneKey(
		$vecStone //(SGMMailItem的数组)合成宝石列表
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 31);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 32;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		SGMMailItem::vectorToStream($data, $vecStone);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：包裹或仓库道具通知
	abstract function onRecv_StoreNotify(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$wStoreSize, //(UINT16)包裹或仓库的容量
		$vecStoreItem //(SItem的数组)包裹或仓库中道具的列表
	);

	//接收：解锁格子还需要多少时间
	abstract function onRecv_PackNextUnlockTime(
		$dwTime //(UINT32)时间，单位秒
	);

	//接收：包裹或仓库容量改变通知
	abstract function onRecv_StoreSizeChangeNotify(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$wStoreSize //(UINT16)包裹或仓库的容量
	);

	//接收：当前玩家的包裹或仓库中道具增加通知
	abstract function onRecv_StoreItemAddNtf(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$vecStoreItem, //(SItem的数组)包裹或仓库中道具的列表
		$bNew //(bool)是否新获得道具
	);

	//接收：当前玩家的包裹或仓库中道具删除通知
	abstract function onRecv_StoreItemDelNtf(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$vecInstID //(UINT64数组)道具的实例ID列表
	);

	//接收：堆叠道具数量刷新通知
	abstract function onRecv_StackItemUpdate(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$qwRoleID, //(UINT64)角色ID
		$qwInstID, //(UINT64)堆叠道具的实例ID
		$wStack //(UINT16)当前堆叠数
	);

	//接收：打开包裹或仓库
	abstract function onRecv_OpenDepot(
		$eStoreType //(枚举类型：EStoreType)存储类型
	);

	//接收：道具绑定改变通知
	abstract function onRecv_ItemBindChangeNtf(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$qwInstID, //(UINT64)道具的实例ID
		$eBindType, //(枚举类型：EBindType)道具的绑定类型
		$bBind //(bool)道具是否绑定
	);

	//接收：道具CD时间通知
	abstract function onRecv_ItemCDNtf(
		$byType, //(UINT8)冷却类型0:ItemID 1:GroupID
		$rItemCD //(类类型：SItemColdTime)道具CD
	);

	//接收：道具的到期时间通知
	abstract function onRecv_ItemExpireTimeNtf(
		$qwInstID, //(UINT64)道具的实例ID
		$dwExpireTime //(UINT32)到期时间(1970年1月1日0时开始的秒数)
	);

	//接收：道具(装备)属性变化通知
	abstract function onRecv_ItemChangeNotify(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$qwOwnerID, //(UINT64)所有者ID(可能是主将，副将，宠物...)
		$rStoreItem //(类类型：SItem)装备更新后信息
	);

	//接收：清除道具使用冷却CD
	abstract function onRecv_ClearAllItemCDNtf(
	);

	//接收：角色道具冷却通知
	abstract function onRecv_SlotItemCDNotify(
		$vecItemCold, //(SItemColdTime的数组)道具使用冷却时间
		$vecGroupCold //(SItemColdTime的数组)道具公共冷却时间
	);

	//接收：角色获得道具提示
	abstract function onRecv_AddItemSystemMsg(
		$vecAddItemMsg //(SAddItemMsg的数组)道具获得提示
	);

	//接收：错误提示
	abstract function onRecv_ItemErrNfg(
		$eResult //(枚举类型：EItemResult)提示
	);

	//接收：再一次增加记录道具通知
	abstract function onRecv_AgainAddloggedItemNotify(
		$rVecLoggedItem //(SLoggedItem的数组)道具列表
	);

	//接收：增加记录道具通知
	abstract function onRecv_AddLoggedItemNotify(
		$rVecLoggedItem //(SLoggedItem的数组)道具列表
	);

	//接收：更新记录的堆叠道具通知
	abstract function onRecv_UpdateLoggedStackItemNotify(
		$wItemID, //(UINT16)ID
		$byQuality, //(UINT8)品质
		$dwCount //(UINT32)数目
	);

	//接收：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
	abstract function onRecv_CittaAddNtf(
		$eStoreType, //(枚举类型：EStoreType)存储类型
		$vecStoreItem, //(SItem的数组)包裹或仓库中道具的列表
		$bNew //(bool)是否新获得道具
	);

	//接收：更新记录的堆叠道具通知
	abstract function onRecv_NoticeUseItemNotify(
		$wItemID, //(UINT16)ID
		$dwNum, //(UINT32)使用物品数量
		$vecRes, //(SResource的数组)资源
		$vecItem //(SItemGenInfo的数组)物品
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：请求包裹信息(整个包裹)
	abstract function onReturn_GetStore(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_GetStore)原来的参数
		$retParam //(类类型：SRetParam_GetStore)返回的参数
	);

	//返回：请求使用包裹中的道具
	abstract function onReturn_UseItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_UseItem)原来的参数
		$retParam //(类类型：SRetParam_UseItem)返回的参数
	);

	//返回：扩充包裹或仓库
	abstract function onReturn_ExpandStore(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ExpandStore)返回的参数
	);

	//返回：包裹或仓库中道具换位置
	abstract function onReturn_RelocateStoreItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_RelocateStoreItem)原来的参数
		$retParam //(类类型：SRetParam_RelocateStoreItem)返回的参数
	);

	//返回：整理包裹或仓库
	abstract function onReturn_TidyupStore(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_TidyupStore)原来的参数
		$retParam //(类类型：SRetParam_TidyupStore)返回的参数
	);

	//返回：拆分包裹或仓库中的堆叠类道具
	abstract function onReturn_SplitStackItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_SplitStackItem)原来的参数
		$retParam //(类类型：SRetParam_SplitStackItem)返回的参数
	);

	//返回：合并包裹或仓库中的堆叠类道具
	abstract function onReturn_MergeStackItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_MergeStackItem)原来的参数
		$retParam //(类类型：SRetParam_MergeStackItem)返回的参数
	);

	//返回：销毁包裹或仓库中的道具
	abstract function onReturn_DestroyStoreItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_DestroyStoreItem)原来的参数
		$retParam //(类类型：SRetParam_DestroyStoreItem)返回的参数
	);

	//返回：在包裹和仓库之间移动道具
	abstract function onReturn_TransferItem(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TransferItem)返回的参数
	);

	//返回：请求出售包裹中的道具-出售给系统
	abstract function onReturn_SellItem(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_SellItem)原来的参数
		$retParam //(类类型：SRetParam_SellItem)返回的参数
	);

	//返回：请求按个数出售包裹中的道具-出售给系统
	abstract function onReturn_SellItemWithCount(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_SellItemWithCount)原来的参数
		$retParam //(类类型：SRetParam_SellItemWithCount)返回的参数
	);

	//返回：解锁背包格子
	abstract function onReturn_UnlockPack(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UnlockPack)返回的参数
	);

	//返回：记录传送点
	abstract function onReturn_RecordTransfPoint(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_RecordTransfPoint)返回的参数
	);

	//返回：传送
	abstract function onReturn_TransfMapPoint(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TransfMapPoint)返回的参数
	);

	//返回：请求装备心法
	abstract function onReturn_WearCitta(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_WearCitta)原来的参数
		$retParam //(类类型：SRetParam_WearCitta)返回的参数
	);

	//返回：请求卸下心法
	abstract function onReturn_TakeoffCitta(
		$ret, //0为成功，1为失败，2为超时
		$origParam, //(类类型：SOrigParam_TakeoffCitta)原来的参数
		$retParam //(类类型：SRetParam_TakeoffCitta)返回的参数
	);

	//返回：请求合成心法
	abstract function onReturn_MergeCitta(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_MergeCitta)返回的参数
	);

	//返回：请求分解心法
	abstract function onReturn_BreakCitta(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_BreakCitta)返回的参数
	);

	//返回：激活法宝
	abstract function onReturn_ActiveTrump(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ActiveTrump)返回的参数
	);

	//返回：出战法宝
	abstract function onReturn_EquipTrump(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_EquipTrump)返回的参数
	);

	//返回：卸下法宝
	abstract function onReturn_UnEquipTrump(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UnEquipTrump)返回的参数
	);

	//返回：祭炼法宝
	abstract function onReturn_UpgradeTrump(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UpgradeTrump)返回的参数
	);

	//返回：提升法宝品级
	abstract function onReturn_EvolveTrump(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_EvolveTrump)返回的参数
	);

	//返回：激活时装
	abstract function onReturn_FashionActive(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FashionActive)返回的参数
	);

	//返回：隐藏所选时装
	abstract function onReturn_FashionHide(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FashionHide)返回的参数
	);

	//返回：选择时装
	abstract function onReturn_FashionChange(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FashionChange)返回的参数
	);

	//返回：时装炼化
	abstract function onReturn_FashionUpgrade(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FashionUpgrade)返回的参数
	);

	//返回：穿戴宝石
	abstract function onReturn_WareGemStone(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_WareGemStone)返回的参数
	);

	//返回：取下宝石
	abstract function onReturn_TakeOffGemStone(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_TakeOffGemStone)返回的参数
	);

	//返回：合成宝石
	abstract function onReturn_ComposeGemStone(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ComposeGemStone)返回的参数
	);

	//返回：一键合成宝石
	abstract function onReturn_ComposeGemStoneOneKey(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ComposeGemStoneOneKey)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：包裹或仓库道具通知
	private function _doRecv_StoreNotify($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$wStoreSize = ByteUtil::readUINT16($data);
		$vecStoreItem = SItem::superVectorFromStream($data);
		return $this->onRecv_StoreNotify($eStoreType, $wStoreSize, $vecStoreItem);
	}

	//接收处理：解锁格子还需要多少时间
	private function _doRecv_PackNextUnlockTime($data)
	{
		$dwTime = ByteUtil::readUINT32($data);
		return $this->onRecv_PackNextUnlockTime($dwTime);
	}

	//接收处理：包裹或仓库容量改变通知
	private function _doRecv_StoreSizeChangeNotify($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$wStoreSize = ByteUtil::readUINT16($data);
		return $this->onRecv_StoreSizeChangeNotify($eStoreType, $wStoreSize);
	}

	//接收处理：当前玩家的包裹或仓库中道具增加通知
	private function _doRecv_StoreItemAddNtf($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$vecStoreItem = SItem::superVectorFromStream($data);
		$bNew = ByteUtil::readBool($data);
		return $this->onRecv_StoreItemAddNtf($eStoreType, $vecStoreItem, $bNew);
	}

	//接收处理：当前玩家的包裹或仓库中道具删除通知
	private function _doRecv_StoreItemDelNtf($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$vecInstID = ByteUtil::readVecUINT64($data);
		return $this->onRecv_StoreItemDelNtf($eStoreType, $vecInstID);
	}

	//接收处理：堆叠道具数量刷新通知
	private function _doRecv_StackItemUpdate($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$qwRoleID = ByteUtil::readUINT64($data);
		$qwInstID = ByteUtil::readUINT64($data);
		$wStack = ByteUtil::readUINT16($data);
		return $this->onRecv_StackItemUpdate($eStoreType, $qwRoleID, $qwInstID, $wStack);
	}

	//接收处理：打开包裹或仓库
	private function _doRecv_OpenDepot($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		return $this->onRecv_OpenDepot($eStoreType);
	}

	//接收处理：道具绑定改变通知
	private function _doRecv_ItemBindChangeNtf($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$qwInstID = ByteUtil::readUINT64($data);
		$eBindType = ByteUtil::readUINT8($data);
		$bBind = ByteUtil::readBool($data);
		return $this->onRecv_ItemBindChangeNtf($eStoreType, $qwInstID, $eBindType, $bBind);
	}

	//接收处理：道具CD时间通知
	private function _doRecv_ItemCDNtf($data)
	{
		$byType = ByteUtil::readUINT8($data);
		$rItemCD = SItemColdTime::fromStream($data);
		return $this->onRecv_ItemCDNtf($byType, $rItemCD);
	}

	//接收处理：道具的到期时间通知
	private function _doRecv_ItemExpireTimeNtf($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$dwExpireTime = ByteUtil::readUINT32($data);
		return $this->onRecv_ItemExpireTimeNtf($qwInstID, $dwExpireTime);
	}

	//接收处理：道具(装备)属性变化通知
	private function _doRecv_ItemChangeNotify($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$qwOwnerID = ByteUtil::readUINT64($data);
		$rStoreItem = SItem::superFromStream($data);
		return $this->onRecv_ItemChangeNotify($eStoreType, $qwOwnerID, $rStoreItem);
	}

	//接收处理：清除道具使用冷却CD
	private function _doRecv_ClearAllItemCDNtf($data)
	{
		return $this->onRecv_ClearAllItemCDNtf();
	}

	//接收处理：角色道具冷却通知
	private function _doRecv_SlotItemCDNotify($data)
	{
		$vecItemCold = SItemColdTime::vectorFromStream($data);
		$vecGroupCold = SItemColdTime::vectorFromStream($data);
		return $this->onRecv_SlotItemCDNotify($vecItemCold, $vecGroupCold);
	}

	//接收处理：角色获得道具提示
	private function _doRecv_AddItemSystemMsg($data)
	{
		$vecAddItemMsg = SAddItemMsg::vectorFromStream($data);
		return $this->onRecv_AddItemSystemMsg($vecAddItemMsg);
	}

	//接收处理：错误提示
	private function _doRecv_ItemErrNfg($data)
	{
		$eResult = ByteUtil::readUINT8($data);
		return $this->onRecv_ItemErrNfg($eResult);
	}

	//接收处理：再一次增加记录道具通知
	private function _doRecv_AgainAddloggedItemNotify($data)
	{
		$rVecLoggedItem = SLoggedItem::vectorFromStream($data);
		return $this->onRecv_AgainAddloggedItemNotify($rVecLoggedItem);
	}

	//接收处理：增加记录道具通知
	private function _doRecv_AddLoggedItemNotify($data)
	{
		$rVecLoggedItem = SLoggedItem::vectorFromStream($data);
		return $this->onRecv_AddLoggedItemNotify($rVecLoggedItem);
	}

	//接收处理：更新记录的堆叠道具通知
	private function _doRecv_UpdateLoggedStackItemNotify($data)
	{
		$wItemID = ByteUtil::readUINT16($data);
		$byQuality = ByteUtil::readUINT8($data);
		$dwCount = ByteUtil::readUINT32($data);
		return $this->onRecv_UpdateLoggedStackItemNotify($wItemID, $byQuality, $dwCount);
	}

	//接收处理：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
	private function _doRecv_CittaAddNtf($data)
	{
		$eStoreType = ByteUtil::readUINT8($data);
		$vecStoreItem = SItem::superVectorFromStream($data);
		$bNew = ByteUtil::readBool($data);
		return $this->onRecv_CittaAddNtf($eStoreType, $vecStoreItem, $bNew);
	}

	//接收处理：更新记录的堆叠道具通知
	private function _doRecv_NoticeUseItemNotify($data)
	{
		$wItemID = ByteUtil::readUINT16($data);
		$dwNum = ByteUtil::readUINT32($data);
		$vecRes = SResource::vectorFromStream($data);
		$vecItem = SItemGenInfo::vectorFromStream($data);
		return $this->onRecv_NoticeUseItemNotify($wItemID, $dwNum, $vecRes, $vecItem);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：请求包裹信息(整个包裹)
	private function _doReturn_GetStore($data)
	{
		$retParam = new SRetParam_GetStore;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$stStoreStream = SStoreStream::fromStream($data); //背包信息
		$dwNextUnlockTime = ByteUtil::readUINT32($data); //(无符号32位整数)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒
		$retParam->stStoreStream = $stStoreStream;
		$retParam->dwNextUnlockTime = $dwNextUnlockTime;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetStore($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求包裹信息(整个包裹)
	private function _onTimeOut_GetStore($sessionID)
	{
		$retParam = new SRetParam_GetStore;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_GetStore(2, $origParam, $retParam);
	}

	//返回处理：请求使用包裹中的道具
	private function _doReturn_UseItem($data)
	{
		$retParam = new SRetParam_UseItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)使用道具结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UseItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求使用包裹中的道具
	private function _onTimeOut_UseItem($sessionID)
	{
		$retParam = new SRetParam_UseItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_UseItem(2, $origParam, $retParam);
	}

	//返回处理：扩充包裹或仓库
	private function _doReturn_ExpandStore($data)
	{
		$retParam = new SRetParam_ExpandStore;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)扩充结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ExpandStore($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：扩充包裹或仓库
	private function _onTimeOut_ExpandStore($sessionID)
	{
		$retParam = new SRetParam_ExpandStore;
		$this->onReturn_ExpandStore(2, $retParam);
	}

	//返回处理：包裹或仓库中道具换位置
	private function _doReturn_RelocateStoreItem($data)
	{
		$retParam = new SRetParam_RelocateStoreItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)换位置的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_RelocateStoreItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：包裹或仓库中道具换位置
	private function _onTimeOut_RelocateStoreItem($sessionID)
	{
		$retParam = new SRetParam_RelocateStoreItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_RelocateStoreItem(2, $origParam, $retParam);
	}

	//返回处理：整理包裹或仓库
	private function _doReturn_TidyupStore($data)
	{
		$retParam = new SRetParam_TidyupStore;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)整理的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TidyupStore($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：整理包裹或仓库
	private function _onTimeOut_TidyupStore($sessionID)
	{
		$retParam = new SRetParam_TidyupStore;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_TidyupStore(2, $origParam, $retParam);
	}

	//返回处理：拆分包裹或仓库中的堆叠类道具
	private function _doReturn_SplitStackItem($data)
	{
		$retParam = new SRetParam_SplitStackItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)拆分的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SplitStackItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：拆分包裹或仓库中的堆叠类道具
	private function _onTimeOut_SplitStackItem($sessionID)
	{
		$retParam = new SRetParam_SplitStackItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_SplitStackItem(2, $origParam, $retParam);
	}

	//返回处理：合并包裹或仓库中的堆叠类道具
	private function _doReturn_MergeStackItem($data)
	{
		$retParam = new SRetParam_MergeStackItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)合并的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MergeStackItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：合并包裹或仓库中的堆叠类道具
	private function _onTimeOut_MergeStackItem($sessionID)
	{
		$retParam = new SRetParam_MergeStackItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_MergeStackItem(2, $origParam, $retParam);
	}

	//返回处理：销毁包裹或仓库中的道具
	private function _doReturn_DestroyStoreItem($data)
	{
		$retParam = new SRetParam_DestroyStoreItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)销毁的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_DestroyStoreItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：销毁包裹或仓库中的道具
	private function _onTimeOut_DestroyStoreItem($sessionID)
	{
		$retParam = new SRetParam_DestroyStoreItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_DestroyStoreItem(2, $origParam, $retParam);
	}

	//返回处理：在包裹和仓库之间移动道具
	private function _doReturn_TransferItem($data)
	{
		$retParam = new SRetParam_TransferItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)移动的结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TransferItem($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：在包裹和仓库之间移动道具
	private function _onTimeOut_TransferItem($sessionID)
	{
		$retParam = new SRetParam_TransferItem;
		$this->onReturn_TransferItem(2, $retParam);
	}

	//返回处理：请求出售包裹中的道具-出售给系统
	private function _doReturn_SellItem($data)
	{
		$retParam = new SRetParam_SellItem;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)使用道具结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SellItem($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求出售包裹中的道具-出售给系统
	private function _onTimeOut_SellItem($sessionID)
	{
		$retParam = new SRetParam_SellItem;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_SellItem(2, $origParam, $retParam);
	}

	//返回处理：请求按个数出售包裹中的道具-出售给系统
	private function _doReturn_SellItemWithCount($data)
	{
		$retParam = new SRetParam_SellItemWithCount;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)卖出道具结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_SellItemWithCount($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求按个数出售包裹中的道具-出售给系统
	private function _onTimeOut_SellItemWithCount($sessionID)
	{
		$retParam = new SRetParam_SellItemWithCount;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_SellItemWithCount(2, $origParam, $retParam);
	}

	//返回处理：解锁背包格子
	private function _doReturn_UnlockPack($data)
	{
		$retParam = new SRetParam_UnlockPack;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UnlockPack($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：解锁背包格子
	private function _onTimeOut_UnlockPack($sessionID)
	{
		$retParam = new SRetParam_UnlockPack;
		$this->onReturn_UnlockPack(2, $retParam);
	}

	//返回处理：记录传送点
	private function _doReturn_RecordTransfPoint($data)
	{
		$retParam = new SRetParam_RecordTransfPoint;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_RecordTransfPoint($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：记录传送点
	private function _onTimeOut_RecordTransfPoint($sessionID)
	{
		$retParam = new SRetParam_RecordTransfPoint;
		$this->onReturn_RecordTransfPoint(2, $retParam);
	}

	//返回处理：传送
	private function _doReturn_TransfMapPoint($data)
	{
		$retParam = new SRetParam_TransfMapPoint;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EItemResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TransfMapPoint($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：传送
	private function _onTimeOut_TransfMapPoint($sessionID)
	{
		$retParam = new SRetParam_TransfMapPoint;
		$this->onReturn_TransfMapPoint(2, $retParam);
	}

	//返回处理：请求装备心法
	private function _doReturn_WearCitta($data)
	{
		$retParam = new SRetParam_WearCitta;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECittaResult)穿上装备的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_WearCitta($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求装备心法
	private function _onTimeOut_WearCitta($sessionID)
	{
		$retParam = new SRetParam_WearCitta;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_WearCitta(2, $origParam, $retParam);
	}

	//返回处理：请求卸下心法
	private function _doReturn_TakeoffCitta($data)
	{
		$retParam = new SRetParam_TakeoffCitta;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECittaResult)脱下装备的结果
		$retParam->eResult = $eResult;
		$origParam = $this->_sessionMgr->getData($sessionID);
		$ret = 0;
		if($origParam == null)
			$ret = 3; //确认已超时但又收到返回
		else if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakeoffCitta($ret, $origParam, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求卸下心法
	private function _onTimeOut_TakeoffCitta($sessionID)
	{
		$retParam = new SRetParam_TakeoffCitta;
		$origParam = $this->_sessionMgr->getData(sessionID);
		$this->onReturn_TakeoffCitta(2, $origParam, $retParam);
	}

	//返回处理：请求合成心法
	private function _doReturn_MergeCitta($data)
	{
		$retParam = new SRetParam_MergeCitta;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECittaResult)结果
		$vecItemCitta = SItem::superVectorFromStream($data); //新增的道具
		$retParam->eResult = $eResult;
		$retParam->vecItemCitta = $vecItemCitta;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_MergeCitta($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求合成心法
	private function _onTimeOut_MergeCitta($sessionID)
	{
		$retParam = new SRetParam_MergeCitta;
		$this->onReturn_MergeCitta(2, $retParam);
	}

	//返回处理：请求分解心法
	private function _doReturn_BreakCitta($data)
	{
		$retParam = new SRetParam_BreakCitta;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECittaResult)结果
		$vecItemInfo = SItemGenInfo::vectorFromStream($data); //分解产生的道具
		$retParam->eResult = $eResult;
		$retParam->vecItemInfo = $vecItemInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_BreakCitta($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求分解心法
	private function _onTimeOut_BreakCitta($sessionID)
	{
		$retParam = new SRetParam_BreakCitta;
		$this->onReturn_BreakCitta(2, $retParam);
	}

	//返回处理：激活法宝
	private function _doReturn_ActiveTrump($data)
	{
		$retParam = new SRetParam_ActiveTrump;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETrumpResult)结果
		$vecTrump = STrump::vectorFromStream($data); //新法宝
		$retParam->eResult = $eResult;
		$retParam->vecTrump = $vecTrump;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ActiveTrump($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：激活法宝
	private function _onTimeOut_ActiveTrump($sessionID)
	{
		$retParam = new SRetParam_ActiveTrump;
		$this->onReturn_ActiveTrump(2, $retParam);
	}

	//返回处理：出战法宝
	private function _doReturn_EquipTrump($data)
	{
		$retParam = new SRetParam_EquipTrump;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETrumpResult)结果
		$vecTrump = STrump::vectorFromStream($data); //新法宝
		$retParam->eResult = $eResult;
		$retParam->vecTrump = $vecTrump;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_EquipTrump($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：出战法宝
	private function _onTimeOut_EquipTrump($sessionID)
	{
		$retParam = new SRetParam_EquipTrump;
		$this->onReturn_EquipTrump(2, $retParam);
	}

	//返回处理：卸下法宝
	private function _doReturn_UnEquipTrump($data)
	{
		$retParam = new SRetParam_UnEquipTrump;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETrumpResult)结果
		$vecTrump = STrump::vectorFromStream($data); //新法宝
		$retParam->eResult = $eResult;
		$retParam->vecTrump = $vecTrump;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UnEquipTrump($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：卸下法宝
	private function _onTimeOut_UnEquipTrump($sessionID)
	{
		$retParam = new SRetParam_UnEquipTrump;
		$this->onReturn_UnEquipTrump(2, $retParam);
	}

	//返回处理：祭炼法宝
	private function _doReturn_UpgradeTrump($data)
	{
		$retParam = new SRetParam_UpgradeTrump;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETrumpResult)结果
		$vecTrump = STrump::vectorFromStream($data); //新法宝
		$retParam->eResult = $eResult;
		$retParam->vecTrump = $vecTrump;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UpgradeTrump($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：祭炼法宝
	private function _onTimeOut_UpgradeTrump($sessionID)
	{
		$retParam = new SRetParam_UpgradeTrump;
		$this->onReturn_UpgradeTrump(2, $retParam);
	}

	//返回处理：提升法宝品级
	private function _doReturn_EvolveTrump($data)
	{
		$retParam = new SRetParam_EvolveTrump;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ETrumpResult)结果
		$vecTrump = STrump::vectorFromStream($data); //新法宝
		$retParam->eResult = $eResult;
		$retParam->vecTrump = $vecTrump;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_EvolveTrump($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：提升法宝品级
	private function _onTimeOut_EvolveTrump($sessionID)
	{
		$retParam = new SRetParam_EvolveTrump;
		$this->onReturn_EvolveTrump(2, $retParam);
	}

	//返回处理：激活时装
	private function _doReturn_FashionActive($data)
	{
		$retParam = new SRetParam_FashionActive;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFashionResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FashionActive($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：激活时装
	private function _onTimeOut_FashionActive($sessionID)
	{
		$retParam = new SRetParam_FashionActive;
		$this->onReturn_FashionActive(2, $retParam);
	}

	//返回处理：隐藏所选时装
	private function _doReturn_FashionHide($data)
	{
		$retParam = new SRetParam_FashionHide;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFashionResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FashionHide($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：隐藏所选时装
	private function _onTimeOut_FashionHide($sessionID)
	{
		$retParam = new SRetParam_FashionHide;
		$this->onReturn_FashionHide(2, $retParam);
	}

	//返回处理：选择时装
	private function _doReturn_FashionChange($data)
	{
		$retParam = new SRetParam_FashionChange;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFashionResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FashionChange($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：选择时装
	private function _onTimeOut_FashionChange($sessionID)
	{
		$retParam = new SRetParam_FashionChange;
		$this->onReturn_FashionChange(2, $retParam);
	}

	//返回处理：时装炼化
	private function _doReturn_FashionUpgrade($data)
	{
		$retParam = new SRetParam_FashionUpgrade;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFashionResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FashionUpgrade($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：时装炼化
	private function _onTimeOut_FashionUpgrade($sessionID)
	{
		$retParam = new SRetParam_FashionUpgrade;
		$this->onReturn_FashionUpgrade(2, $retParam);
	}

	//返回处理：穿戴宝石
	private function _doReturn_WareGemStone($data)
	{
		$retParam = new SRetParam_WareGemStone;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EGemstoneResult)结果
		$qwFighterID = ByteUtil::readUINT64($data); //(无符号64位整数)将ID
		$byPos = ByteUtil::readUINT8($data); //(无符号8位整数)穿戴位置
		$Item = SGemstone::fromStream($data); //宝石
		$retParam->eResult = $eResult;
		$retParam->qwFighterID = $qwFighterID;
		$retParam->byPos = $byPos;
		$retParam->Item = $Item;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_WareGemStone($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：穿戴宝石
	private function _onTimeOut_WareGemStone($sessionID)
	{
		$retParam = new SRetParam_WareGemStone;
		$this->onReturn_WareGemStone(2, $retParam);
	}

	//返回处理：取下宝石
	private function _doReturn_TakeOffGemStone($data)
	{
		$retParam = new SRetParam_TakeOffGemStone;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EGemstoneResult)结果
		$qwFighterID = ByteUtil::readUINT64($data); //(无符号64位整数)将ID
		$byPos = ByteUtil::readUINT8($data); //(无符号8位整数)穿戴位置
		$retParam->eResult = $eResult;
		$retParam->qwFighterID = $qwFighterID;
		$retParam->byPos = $byPos;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_TakeOffGemStone($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：取下宝石
	private function _onTimeOut_TakeOffGemStone($sessionID)
	{
		$retParam = new SRetParam_TakeOffGemStone;
		$this->onReturn_TakeOffGemStone(2, $retParam);
	}

	//返回处理：合成宝石
	private function _doReturn_ComposeGemStone($data)
	{
		$retParam = new SRetParam_ComposeGemStone;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EGemstoneResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ComposeGemStone($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：合成宝石
	private function _onTimeOut_ComposeGemStone($sessionID)
	{
		$retParam = new SRetParam_ComposeGemStone;
		$this->onReturn_ComposeGemStone(2, $retParam);
	}

	//返回处理：一键合成宝石
	private function _doReturn_ComposeGemStoneOneKey($data)
	{
		$retParam = new SRetParam_ComposeGemStoneOneKey;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EGemstoneResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ComposeGemStoneOneKey($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：一键合成宝石
	private function _onTimeOut_ComposeGemStoneOneKey($sessionID)
	{
		$retParam = new SRetParam_ComposeGemStoneOneKey;
		$this->onReturn_ComposeGemStoneOneKey(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 18;
		$this->_recvFuncList[0] = '_doRecv_StoreNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_PackNextUnlockTime'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_StoreSizeChangeNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_StoreItemAddNtf'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_StoreItemDelNtf'; //FuncID: 5
		$this->_recvFuncList[5] = '_doRecv_StackItemUpdate'; //FuncID: 6
		$this->_recvFuncList[6] = '_doRecv_OpenDepot'; //FuncID: 7
		$this->_recvFuncList[7] = '_doRecv_ItemBindChangeNtf'; //FuncID: 8
		$this->_recvFuncList[8] = '_doRecv_ItemCDNtf'; //FuncID: 9
		$this->_recvFuncList[9] = '_doRecv_ItemExpireTimeNtf'; //FuncID: 10
		$this->_recvFuncList[10] = '_doRecv_ItemChangeNotify'; //FuncID: 11
		$this->_recvFuncList[11] = '_doRecv_ClearAllItemCDNtf'; //FuncID: 12
		$this->_recvFuncList[12] = '_doRecv_SlotItemCDNotify'; //FuncID: 13
		$this->_recvFuncList[13] = '_doRecv_AddItemSystemMsg'; //FuncID: 14
		$this->_recvFuncList[14] = '_doRecv_ItemErrNfg'; //FuncID: 15
		$this->_recvFuncList[15] = '_doRecv_AgainAddloggedItemNotify'; //FuncID: 16
		$this->_recvFuncList[16] = '_doRecv_AddLoggedItemNotify'; //FuncID: 17
		$this->_recvFuncList[17] = '_doRecv_UpdateLoggedStackItemNotify'; //FuncID: 18
		$this->_recvFuncList[18] = '_doRecv_CittaAddNtf'; //FuncID: 19
		$this->_recvFuncList[19] = '_doRecv_NoticeUseItemNotify'; //FuncID: 20

		$this->_retFuncList[0] = '_doReturn_GetStore'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_UseItem'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_ExpandStore'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_RelocateStoreItem'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_TidyupStore'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_SplitStackItem'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_MergeStackItem'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_DestroyStoreItem'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_TransferItem'; //FuncID: 9
		$this->_retFuncList[9] = '_doReturn_SellItem'; //FuncID: 10
		$this->_retFuncList[10] = '_doReturn_SellItemWithCount'; //FuncID: 11
		$this->_retFuncList[11] = '_doReturn_UnlockPack'; //FuncID: 12
		$this->_retFuncList[12] = '_doReturn_RecordTransfPoint'; //FuncID: 13
		$this->_retFuncList[13] = '_doReturn_TransfMapPoint'; //FuncID: 14
		$this->_retFuncList[14] = '_doReturn_WearCitta'; //FuncID: 15
		$this->_retFuncList[15] = '_doReturn_TakeoffCitta'; //FuncID: 16
		$this->_retFuncList[16] = '_doReturn_MergeCitta'; //FuncID: 17
		$this->_retFuncList[17] = '_doReturn_BreakCitta'; //FuncID: 18
		$this->_retFuncList[18] = '_doReturn_ActiveTrump'; //FuncID: 19
		$this->_retFuncList[19] = '_doReturn_EquipTrump'; //FuncID: 20
		$this->_retFuncList[20] = '_doReturn_UnEquipTrump'; //FuncID: 21
		$this->_retFuncList[21] = '_doReturn_UpgradeTrump'; //FuncID: 22
		$this->_retFuncList[22] = '_doReturn_EvolveTrump'; //FuncID: 23
		$this->_retFuncList[23] = '_doReturn_FashionActive'; //FuncID: 24
		$this->_retFuncList[24] = '_doReturn_FashionHide'; //FuncID: 25
		$this->_retFuncList[25] = '_doReturn_FashionChange'; //FuncID: 26
		$this->_retFuncList[26] = '_doReturn_FashionUpgrade'; //FuncID: 27
		$this->_retFuncList[27] = '_doReturn_WareGemStone'; //FuncID: 28
		$this->_retFuncList[28] = '_doReturn_TakeOffGemStone'; //FuncID: 29
		$this->_retFuncList[29] = '_doReturn_ComposeGemStone'; //FuncID: 30
		$this->_retFuncList[30] = '_doReturn_ComposeGemStoneOneKey'; //FuncID: 31

		$this->_timeFuncList[0] = '_onTimeOut_GetStore'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_UseItem'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_ExpandStore'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_RelocateStoreItem'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_TidyupStore'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_SplitStackItem'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_MergeStackItem'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_DestroyStoreItem'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_TransferItem'; //FuncID: 9
		$this->_timeFuncList[9] = '_onTimeOut_SellItem'; //FuncID: 10
		$this->_timeFuncList[10] = '_onTimeOut_SellItemWithCount'; //FuncID: 11
		$this->_timeFuncList[11] = '_onTimeOut_UnlockPack'; //FuncID: 12
		$this->_timeFuncList[12] = '_onTimeOut_RecordTransfPoint'; //FuncID: 13
		$this->_timeFuncList[13] = '_onTimeOut_TransfMapPoint'; //FuncID: 14
		$this->_timeFuncList[14] = '_onTimeOut_WearCitta'; //FuncID: 15
		$this->_timeFuncList[15] = '_onTimeOut_TakeoffCitta'; //FuncID: 16
		$this->_timeFuncList[16] = '_onTimeOut_MergeCitta'; //FuncID: 17
		$this->_timeFuncList[17] = '_onTimeOut_BreakCitta'; //FuncID: 18
		$this->_timeFuncList[18] = '_onTimeOut_ActiveTrump'; //FuncID: 19
		$this->_timeFuncList[19] = '_onTimeOut_EquipTrump'; //FuncID: 20
		$this->_timeFuncList[20] = '_onTimeOut_UnEquipTrump'; //FuncID: 21
		$this->_timeFuncList[21] = '_onTimeOut_UpgradeTrump'; //FuncID: 22
		$this->_timeFuncList[22] = '_onTimeOut_EvolveTrump'; //FuncID: 23
		$this->_timeFuncList[23] = '_onTimeOut_FashionActive'; //FuncID: 24
		$this->_timeFuncList[24] = '_onTimeOut_FashionHide'; //FuncID: 25
		$this->_timeFuncList[25] = '_onTimeOut_FashionChange'; //FuncID: 26
		$this->_timeFuncList[26] = '_onTimeOut_FashionUpgrade'; //FuncID: 27
		$this->_timeFuncList[27] = '_onTimeOut_WareGemStone'; //FuncID: 28
		$this->_timeFuncList[28] = '_onTimeOut_TakeOffGemStone'; //FuncID: 29
		$this->_timeFuncList[29] = '_onTimeOut_ComposeGemStone'; //FuncID: 30
		$this->_timeFuncList[30] = '_onTimeOut_ComposeGemStoneOneKey'; //FuncID: 31
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