<?php
/************************************************************************
//  工具自动生成的PHP客户端协议代码
//  File Name:    FighterProt.php
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

require_once('ByteUtil.php');
require_once('ProtocolBase.php');
require_once('ItemProtBase.php');
require_once('PropInfoBase.php');
require_once('ProtoCommonBase.php');

/////////////////////以下为类型定义/////////////////////
//将类型
class EFighterType
{
	const eFighter = 0; //将
	const eFighterPlayer = 1; //主将
	const eFighterHero = 2; //散仙
	const eFighterMonster = 3; //怪
	const eFighterMax = 4; //将类型结束
}

//技能操作结果
class ESkillResult
{
	const eSkillSucc = 0; //成功
	const eSkillFailed = 1; //失败
	const eSkillNotExist = 2; //没有此技能
	const eSkillLevelMax = 3; //已达最高等级
	const eSkillLevelErr = 4; //玩家等级不足
	const eSkillNotUp = 5; //未装备此技能
	const eSkillPExpErr = 6; //修为不足
	const eSkillSopErr = 7; //阅历不足
	const eSkillSigilErr = 8; //符印不足
	const eSkillCentsYErr = 9; //仙元不足
	const eSkillPotenErr = 10; //潜力不足
	const eRuneNotExist = 11; //符文不存在
	const eRuneLevelMax = 12; //符文已达最高等级
	const eRuneLevelErr = 13; //玩家等级不足
	const eAdvNotExist = 14; //进阶不存在
	const eAdvLevelGTSkillLevelErr = 15; //进阶等级大于技能等级
	const eItemNotEnough = 16; //物品不足
}

//求签类型
class EDrawType
{
	const eDrawTypeNone = 0; //无效类型
	const eDrawTypeNormal = 1; //普通求签(银币)
	const eDrawTypeAdvance = 2; //高级求签(仙石)
	const eDrawTypeMax = 3; //最大类型
}

//求签类型
class EDrawRewardType
{
	const eDrawRewardTypeNone = 0; //无效类型
	const eDrawRewardTypeBlue = 1; //蓝色仙缘
	const eDrawRewardTypePurple = 2; //紫色仙缘
	const eDrawRewardTypeOrange = 3; //橙色仙缘
	const eDrawRewardTypeMax = 4; //最大类型
}

//求签结果
class EDrawResult
{
	const eDrawResultSuccess = 0; //求签成功
	const eDrawResultFailed = 1; //求签失败
	const eDrawResultLackOfCount = 2; //次数不足
	const eDrawResultLackOfMoney = 3; //金钱不足
	const eDrawResultMax = 4; //求签结果最大值
}

//招募返回
class ERecruitResult
{
	const eRecruitSucc = 0; //成功
	const eRecruitFailed = 1; //失败
	const eRecruitAlready = 2; //已招募
	const eRecruitLackOfMoney = 3; //货币不足
	const eRecruitLevelLimited = 4; //等级不足
}

//淬体
class ECuiTiType
{
	const eCuiTiLianPi = 0; //炼皮-武器
	const eCuiTiTongJin = 1; //通筋-头盔
	const eCuiTiQiangJi = 2; //强肌-戒指
	const eCuiTiDuanGu = 3; //锻骨-衣服
	const eCuiTiHuoLuo = 4; //活络-鞋子
	const eCuiTiXiSui = 5; //洗髓-项链
	const eCuiTiMax = 6; //淬体上限
}

//淬体
class ECuiTiResult
{
	const eCuiTiResultSucc = 0; //成功
	const eCuiTiResultFailed = 1; //失败
	const eCuiTiResultSilverErr = 2; //银币不足
	const eCuiTiResultLvlMaxErr = 3; //已达最高等级
	const eCuiTiResultPlayerLvlErr = 4; //已达将最高等级
	const eCuiTiResultUnlock = 5; //未解锁
}

//转移
class EShiftResult
{
	const eShiftSucc = 0; //成功
	const eShiftFailed = 1; //失败
	const eShiftGoldErr = 2; //仙石不足
}

//散仙等级同步
class ESyncLevelResult
{
	const eSyncLevelSucc = 0; //成功
	const eSyncLevelFailed = 1; //失败
	const eSyncLevelAlready = 2; //已是最高等级
	const eSyncLevelMoney = 3; //同步等级所需银币不足
	const eSyncLevelMoneyMore = 4; //同步等级成功但所需银币不足无法继续升级
}

//散仙渡劫
class EDujieResult
{
	const eDujieSucc = 0; //成功
	const eDujieFailed = 1; //失败
	const eDujieItemErr = 2; //渡劫符不足
	const eDujieLevelMaxErr = 3; //渡劫等级已是最高级
}

//心法返回
class EXinFaResult
{
	const eXinFaSucc = 0; //成功
	const eXinFaFailed = 1; //失败
}

//散仙组合返回
class ECombinationResult
{
	const eCombinationSucc = 0; //成功
	const eCombinationFailed = 1; //失败
	const eCombinationMaxLevel = 2; //散仙组合已达最高等级
	const eCombinationHaved = 3; //该散仙组合已激活
	const eCombinationNotHaved = 4; //该散仙组合未激活
	const eCombinationFighterErr = 5; //散仙未招募满
	const eCombinationItemErr = 6; //道具不足
	const eCombinationMainLevelErr = 7; //玩家主将等级不足
}

//散功返回
class EDismissResult
{
	const eDismissSucc = 0; //成功
	const eDismissFailed = 1; //失败
	const eNeedTakeOffStone = 2; //需要卸下宝石
}

//购买散仙返回
class EFighterBuyResult
{
	const eFighterBuySucc = 0; //成功
	const eFighterBuyFailed = 1; //失败
	const eFighterBuyAlready = 2; //已购买
	const eFighterBuyLackOfMoney = 3; //货币不足
}

//玩家购买散仙信息
final class SFighterBuyInfo
{
	public $wFighterID; //(UINT16)将类型ID
	public $byFighterBuyStatus; //(UINT8)购买状态（0：未购买；1：已购买）

	//构造函数
	function __construct()
	{
		$this->wFighterID = 0;
		$this->byFighterBuyStatus = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wFighterID = $this->wFighterID;
		$obj->byFighterBuyStatus = $this->byFighterBuyStatus;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterBuyInfo;
		$s->wFighterID = ByteUtil::readUINT16($data);
		$s->byFighterBuyStatus = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterBuyInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wFighterID);
		ByteUtil::writeUINT8($data, $this->byFighterBuyStatus);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//玩家的散仙组合信息
final class SFighterCombination
{
	public $byGroupID; //(UINT8)散仙组合ID
	public $byGroupLvl; //(UINT8)散仙组合等级
	public $dwGroupExp; //(UINT32)散仙组合当前经验值
	public $byInLineUp; //(UINT8)是否出战在阵型(0未出战 1已出战)
	public $byInEMei; //(UINT8)是否出战在守卫峨眉(0未出战 1已出战)

	//构造函数
	function __construct()
	{
		$this->byGroupID = 0;
		$this->byGroupLvl = 0;
		$this->dwGroupExp = 0;
		$this->byInLineUp = 0;
		$this->byInEMei = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->byGroupID = $this->byGroupID;
		$obj->byGroupLvl = $this->byGroupLvl;
		$obj->dwGroupExp = $this->dwGroupExp;
		$obj->byInLineUp = $this->byInLineUp;
		$obj->byInEMei = $this->byInEMei;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterCombination;
		$s->byGroupID = ByteUtil::readUINT8($data);
		$s->byGroupLvl = ByteUtil::readUINT8($data);
		$s->dwGroupExp = ByteUtil::readUINT32($data);
		$s->byInLineUp = ByteUtil::readUINT8($data);
		$s->byInEMei = ByteUtil::readUINT8($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterCombination::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->byGroupID);
		ByteUtil::writeUINT8($data, $this->byGroupLvl);
		ByteUtil::writeUINT32($data, $this->dwGroupExp);
		ByteUtil::writeUINT8($data, $this->byInLineUp);
		ByteUtil::writeUINT8($data, $this->byInEMei);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//数据库同步到游戏服务器的将信息
final class SFighterDBInfo
{
	public $qwInstID; //(UINT64)将唯一ID
	public $qwRoleID; //(UINT64)所属玩家ID
	public $wFighterID; //(UINT16)将类型ID
	public $byRecruited; //(UINT8)是否已招募
	public $byStar; //(UINT8)当前星级
	public $iSlot; //(INT32)将位置
	public $iPos; //(INT32)阵型中的位置
	public $fPotential; //(float)潜力
	public $fCapacity; //(float)资质
	public $byLevel; //(UINT8)等级
	public $qwExp; //(UINT64)经验
	public $byLianPi; //(UINT8)炼皮
	public $byTongJin; //(UINT8)通筋
	public $byQiangJi; //(UINT8)强肌
	public $byDuanGu; //(UINT8)锻骨
	public $byHuoLuo; //(UINT8)活络
	public $byXiSui; //(UINT8)洗髓
	public $dwDujieExp; //(UINT32)散仙渡劫经验
	public $dwSpiritPower; //(UINT32)元神力

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->qwRoleID = new Math_BigInteger;
		$this->wFighterID = 0;
		$this->byRecruited = 0;
		$this->byStar = 0;
		$this->iSlot = 0;
		$this->iPos = 0;
		$this->fPotential = 0;
		$this->fCapacity = 0;
		$this->byLevel = 0;
		$this->qwExp = new Math_BigInteger;
		$this->byLianPi = 0;
		$this->byTongJin = 0;
		$this->byQiangJi = 0;
		$this->byDuanGu = 0;
		$this->byHuoLuo = 0;
		$this->byXiSui = 0;
		$this->dwDujieExp = 0;
		$this->dwSpiritPower = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->qwRoleID = $this->qwRoleID;
		$obj->wFighterID = $this->wFighterID;
		$obj->byRecruited = $this->byRecruited;
		$obj->byStar = $this->byStar;
		$obj->iSlot = $this->iSlot;
		$obj->iPos = $this->iPos;
		$obj->fPotential = $this->fPotential;
		$obj->fCapacity = $this->fCapacity;
		$obj->byLevel = $this->byLevel;
		$obj->qwExp = $this->qwExp;
		$obj->byLianPi = $this->byLianPi;
		$obj->byTongJin = $this->byTongJin;
		$obj->byQiangJi = $this->byQiangJi;
		$obj->byDuanGu = $this->byDuanGu;
		$obj->byHuoLuo = $this->byHuoLuo;
		$obj->byXiSui = $this->byXiSui;
		$obj->dwDujieExp = $this->dwDujieExp;
		$obj->dwSpiritPower = $this->dwSpiritPower;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterDBInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->wFighterID = ByteUtil::readUINT16($data);
		$s->byRecruited = ByteUtil::readUINT8($data);
		$s->byStar = ByteUtil::readUINT8($data);
		$s->iSlot = ByteUtil::readINT32($data);
		$s->iPos = ByteUtil::readINT32($data);
		$s->fPotential = ByteUtil::readFloat($data);
		$s->fCapacity = ByteUtil::readFloat($data);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->qwExp = ByteUtil::readUINT64($data);
		$s->byLianPi = ByteUtil::readUINT8($data);
		$s->byTongJin = ByteUtil::readUINT8($data);
		$s->byQiangJi = ByteUtil::readUINT8($data);
		$s->byDuanGu = ByteUtil::readUINT8($data);
		$s->byHuoLuo = ByteUtil::readUINT8($data);
		$s->byXiSui = ByteUtil::readUINT8($data);
		$s->dwDujieExp = ByteUtil::readUINT32($data);
		$s->dwSpiritPower = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterDBInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT16($data, $this->wFighterID);
		ByteUtil::writeUINT8($data, $this->byRecruited);
		ByteUtil::writeUINT8($data, $this->byStar);
		ByteUtil::writeINT32($data, $this->iSlot);
		ByteUtil::writeINT32($data, $this->iPos);
		ByteUtil::writeFloat($data, $this->fPotential);
		ByteUtil::writeFloat($data, $this->fCapacity);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT64($data, $this->qwExp);
		ByteUtil::writeUINT8($data, $this->byLianPi);
		ByteUtil::writeUINT8($data, $this->byTongJin);
		ByteUtil::writeUINT8($data, $this->byQiangJi);
		ByteUtil::writeUINT8($data, $this->byDuanGu);
		ByteUtil::writeUINT8($data, $this->byHuoLuo);
		ByteUtil::writeUINT8($data, $this->byXiSui);
		ByteUtil::writeUINT32($data, $this->dwDujieExp);
		ByteUtil::writeUINT32($data, $this->dwSpiritPower);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//数据库同步到游戏服务器的技能信息
final class SSkillDBInfo
{
	public $qwOwnerID; //(UINT64)将唯一ID
	public $dwUpSkill1; //(UINT32)使用中的技能1
	public $dwUpSkill2; //(UINT32)使用中的技能2
	public $dwUpSkill3; //(UINT32)使用中的技能3
	public $dwUpSkill4; //(UINT32)使用中的技能4
	public $dwUpSkill5; //(UINT32)使用中的技能5
	public $dwUpSkill6; //(UINT32)使用中的技能6
	public $dwSkill1; //(UINT32)技能1
	public $dwSkill2; //(UINT32)技能2
	public $dwSkill3; //(UINT32)技能3
	public $dwSkill4; //(UINT32)技能4
	public $dwSkill5; //(UINT32)技能5
	public $dwSkill6; //(UINT32)技能6
	public $dwSkill7; //(UINT32)技能7
	public $dwSkill8; //(UINT32)技能8
	public $dwSkill9; //(UINT32)技能9
	public $dwRune1; //(UINT32)符文1
	public $dwRune2; //(UINT32)符文2
	public $dwRune3; //(UINT32)符文3
	public $dwRune4; //(UINT32)符文4
	public $dwRune5; //(UINT32)符文5
	public $dwRune6; //(UINT32)符文6
	public $dwRune7; //(UINT32)符文7
	public $dwRune8; //(UINT32)符文8
	public $dwRune9; //(UINT32)符文9
	public $dwSkillAdv1; //(UINT32)技能进阶1
	public $dwSkillAdv2; //(UINT32)技能进阶2
	public $dwSkillAdv3; //(UINT32)技能进阶3
	public $dwSkillAdv4; //(UINT32)技能进阶4
	public $dwSkillAdv5; //(UINT32)技能进阶5
	public $dwSkillAdv6; //(UINT32)技能进阶6
	public $dwSkillAdv7; //(UINT32)技能进阶7
	public $dwSkillAdv8; //(UINT32)技能进阶8
	public $dwSkillAdv9; //(UINT32)技能进阶9

	//构造函数
	function __construct()
	{
		$this->qwOwnerID = new Math_BigInteger;
		$this->dwUpSkill1 = 0;
		$this->dwUpSkill2 = 0;
		$this->dwUpSkill3 = 0;
		$this->dwUpSkill4 = 0;
		$this->dwUpSkill5 = 0;
		$this->dwUpSkill6 = 0;
		$this->dwSkill1 = 0;
		$this->dwSkill2 = 0;
		$this->dwSkill3 = 0;
		$this->dwSkill4 = 0;
		$this->dwSkill5 = 0;
		$this->dwSkill6 = 0;
		$this->dwSkill7 = 0;
		$this->dwSkill8 = 0;
		$this->dwSkill9 = 0;
		$this->dwRune1 = 0;
		$this->dwRune2 = 0;
		$this->dwRune3 = 0;
		$this->dwRune4 = 0;
		$this->dwRune5 = 0;
		$this->dwRune6 = 0;
		$this->dwRune7 = 0;
		$this->dwRune8 = 0;
		$this->dwRune9 = 0;
		$this->dwSkillAdv1 = 0;
		$this->dwSkillAdv2 = 0;
		$this->dwSkillAdv3 = 0;
		$this->dwSkillAdv4 = 0;
		$this->dwSkillAdv5 = 0;
		$this->dwSkillAdv6 = 0;
		$this->dwSkillAdv7 = 0;
		$this->dwSkillAdv8 = 0;
		$this->dwSkillAdv9 = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwOwnerID = $this->qwOwnerID;
		$obj->dwUpSkill1 = $this->dwUpSkill1;
		$obj->dwUpSkill2 = $this->dwUpSkill2;
		$obj->dwUpSkill3 = $this->dwUpSkill3;
		$obj->dwUpSkill4 = $this->dwUpSkill4;
		$obj->dwUpSkill5 = $this->dwUpSkill5;
		$obj->dwUpSkill6 = $this->dwUpSkill6;
		$obj->dwSkill1 = $this->dwSkill1;
		$obj->dwSkill2 = $this->dwSkill2;
		$obj->dwSkill3 = $this->dwSkill3;
		$obj->dwSkill4 = $this->dwSkill4;
		$obj->dwSkill5 = $this->dwSkill5;
		$obj->dwSkill6 = $this->dwSkill6;
		$obj->dwSkill7 = $this->dwSkill7;
		$obj->dwSkill8 = $this->dwSkill8;
		$obj->dwSkill9 = $this->dwSkill9;
		$obj->dwRune1 = $this->dwRune1;
		$obj->dwRune2 = $this->dwRune2;
		$obj->dwRune3 = $this->dwRune3;
		$obj->dwRune4 = $this->dwRune4;
		$obj->dwRune5 = $this->dwRune5;
		$obj->dwRune6 = $this->dwRune6;
		$obj->dwRune7 = $this->dwRune7;
		$obj->dwRune8 = $this->dwRune8;
		$obj->dwRune9 = $this->dwRune9;
		$obj->dwSkillAdv1 = $this->dwSkillAdv1;
		$obj->dwSkillAdv2 = $this->dwSkillAdv2;
		$obj->dwSkillAdv3 = $this->dwSkillAdv3;
		$obj->dwSkillAdv4 = $this->dwSkillAdv4;
		$obj->dwSkillAdv5 = $this->dwSkillAdv5;
		$obj->dwSkillAdv6 = $this->dwSkillAdv6;
		$obj->dwSkillAdv7 = $this->dwSkillAdv7;
		$obj->dwSkillAdv8 = $this->dwSkillAdv8;
		$obj->dwSkillAdv9 = $this->dwSkillAdv9;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SSkillDBInfo;
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		$s->dwUpSkill1 = ByteUtil::readUINT32($data);
		$s->dwUpSkill2 = ByteUtil::readUINT32($data);
		$s->dwUpSkill3 = ByteUtil::readUINT32($data);
		$s->dwUpSkill4 = ByteUtil::readUINT32($data);
		$s->dwUpSkill5 = ByteUtil::readUINT32($data);
		$s->dwUpSkill6 = ByteUtil::readUINT32($data);
		$s->dwSkill1 = ByteUtil::readUINT32($data);
		$s->dwSkill2 = ByteUtil::readUINT32($data);
		$s->dwSkill3 = ByteUtil::readUINT32($data);
		$s->dwSkill4 = ByteUtil::readUINT32($data);
		$s->dwSkill5 = ByteUtil::readUINT32($data);
		$s->dwSkill6 = ByteUtil::readUINT32($data);
		$s->dwSkill7 = ByteUtil::readUINT32($data);
		$s->dwSkill8 = ByteUtil::readUINT32($data);
		$s->dwSkill9 = ByteUtil::readUINT32($data);
		$s->dwRune1 = ByteUtil::readUINT32($data);
		$s->dwRune2 = ByteUtil::readUINT32($data);
		$s->dwRune3 = ByteUtil::readUINT32($data);
		$s->dwRune4 = ByteUtil::readUINT32($data);
		$s->dwRune5 = ByteUtil::readUINT32($data);
		$s->dwRune6 = ByteUtil::readUINT32($data);
		$s->dwRune7 = ByteUtil::readUINT32($data);
		$s->dwRune8 = ByteUtil::readUINT32($data);
		$s->dwRune9 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv1 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv2 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv3 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv4 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv5 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv6 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv7 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv8 = ByteUtil::readUINT32($data);
		$s->dwSkillAdv9 = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SSkillDBInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
		ByteUtil::writeUINT32($data, $this->dwUpSkill1);
		ByteUtil::writeUINT32($data, $this->dwUpSkill2);
		ByteUtil::writeUINT32($data, $this->dwUpSkill3);
		ByteUtil::writeUINT32($data, $this->dwUpSkill4);
		ByteUtil::writeUINT32($data, $this->dwUpSkill5);
		ByteUtil::writeUINT32($data, $this->dwUpSkill6);
		ByteUtil::writeUINT32($data, $this->dwSkill1);
		ByteUtil::writeUINT32($data, $this->dwSkill2);
		ByteUtil::writeUINT32($data, $this->dwSkill3);
		ByteUtil::writeUINT32($data, $this->dwSkill4);
		ByteUtil::writeUINT32($data, $this->dwSkill5);
		ByteUtil::writeUINT32($data, $this->dwSkill6);
		ByteUtil::writeUINT32($data, $this->dwSkill7);
		ByteUtil::writeUINT32($data, $this->dwSkill8);
		ByteUtil::writeUINT32($data, $this->dwSkill9);
		ByteUtil::writeUINT32($data, $this->dwRune1);
		ByteUtil::writeUINT32($data, $this->dwRune2);
		ByteUtil::writeUINT32($data, $this->dwRune3);
		ByteUtil::writeUINT32($data, $this->dwRune4);
		ByteUtil::writeUINT32($data, $this->dwRune5);
		ByteUtil::writeUINT32($data, $this->dwRune6);
		ByteUtil::writeUINT32($data, $this->dwRune7);
		ByteUtil::writeUINT32($data, $this->dwRune8);
		ByteUtil::writeUINT32($data, $this->dwRune9);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv1);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv2);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv3);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv4);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv5);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv6);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv7);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv8);
		ByteUtil::writeUINT32($data, $this->dwSkillAdv9);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//数据库同步到游戏服务器的技能信息
final class SPassiveSkillDBInfo
{
	public $qwOwnerID; //(UINT64)将唯一ID
	public $qwRoleID; //(UINT64)玩家一ID
	public $dwSkillID; //(UINT32)技能ID
	public $dwSkillQuality; //(UINT32)技能品质
	public $dwSkillLevel; //(UINT32)技能等级

	//构造函数
	function __construct()
	{
		$this->qwOwnerID = new Math_BigInteger;
		$this->qwRoleID = new Math_BigInteger;
		$this->dwSkillID = 0;
		$this->dwSkillQuality = 0;
		$this->dwSkillLevel = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwOwnerID = $this->qwOwnerID;
		$obj->qwRoleID = $this->qwRoleID;
		$obj->dwSkillID = $this->dwSkillID;
		$obj->dwSkillQuality = $this->dwSkillQuality;
		$obj->dwSkillLevel = $this->dwSkillLevel;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SPassiveSkillDBInfo;
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->dwSkillID = ByteUtil::readUINT32($data);
		$s->dwSkillQuality = ByteUtil::readUINT32($data);
		$s->dwSkillLevel = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SPassiveSkillDBInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT32($data, $this->dwSkillID);
		ByteUtil::writeUINT32($data, $this->dwSkillQuality);
		ByteUtil::writeUINT32($data, $this->dwSkillLevel);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//客栈散仙信息
final class SHeroFighterInTavernInfo
{
	public $wID; //(UINT16)散仙ID
	public $bHired; //(bool)是否已招募

	//构造函数
	function __construct()
	{
		$this->wID = 0;
		$this->bHired = false;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wID = $this->wID;
		$obj->bHired = $this->bHired;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SHeroFighterInTavernInfo;
		$s->wID = ByteUtil::readUINT16($data);
		$s->bHired = ByteUtil::readBool($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SHeroFighterInTavernInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wID);
		ByteUtil::writeBool($data, $this->bHired);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//客栈信息
final class STavernInfo
{
	public $wID; //(UINT16)客栈ID
	public $vecFighterInfo; //(SHeroFighterInTavernInfo的数组)客栈中散仙信息

	//构造函数
	function __construct()
	{
		$this->wID = 0;
		$this->vecFighterInfo = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->wID = $this->wID;
		$obj->vecFighterInfo = $this->vecFighterInfo;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new STavernInfo;
		$s->wID = ByteUtil::readUINT16($data);
		$s->vecFighterInfo = SHeroFighterInTavernInfo::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = STavernInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT16($data, $this->wID);
		SHeroFighterInTavernInfo::vectorToStream($data, $this->vecFighterInfo);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//战斗者除了外观之外的杂七杂八的基本信息
final class SFighterBaseInfo
{
	public $qwInstID; //(UINT64)将唯一ID
	public $wFighterID; //(UINT16)将类型ID
	public $byRecruited; //(UINT8)是否已招募
	public $byStar; //(UINT8)当前星级
	public $iSlot; //(INT32)将位置
	public $iPos; //(INT32)阵型中的位置
	public $byLevel; //(UINT8)等级
	public $qwExp; //(UINT64)总经验
	public $strName; //(string)将名字
	public $dwHpMax; //(UINT32)最大血量
	public $dwHp; //(UINT32)当前血量
	public $dwAura; //(UINT32)当前灵气
	public $dwAuraMax; //(UINT32)最大灵气
	public $byLianPi; //(UINT8)炼皮
	public $byTongJin; //(UINT8)通筋
	public $byQiangJi; //(UINT8)强肌
	public $byDuanGu; //(UINT8)锻骨
	public $byHuoLuo; //(UINT8)活络
	public $byXiSui; //(UINT8)洗髓
	public $byDujieLevel; //(UINT8)散仙渡劫等级
	public $dwDujieExp; //(UINT32)散仙渡劫经验
	public $byQuality; //(UINT8)散仙品质(颜色)
	public $dwSpiritPower; //(UINT32)元神力

	//构造函数
	function __construct()
	{
		$this->qwInstID = new Math_BigInteger;
		$this->wFighterID = 0;
		$this->byRecruited = 0;
		$this->byStar = 0;
		$this->iSlot = 0;
		$this->iPos = 0;
		$this->byLevel = 0;
		$this->qwExp = new Math_BigInteger;
		$this->strName = '';
		$this->dwHpMax = 0;
		$this->dwHp = 0;
		$this->dwAura = 0;
		$this->dwAuraMax = 0;
		$this->byLianPi = 0;
		$this->byTongJin = 0;
		$this->byQiangJi = 0;
		$this->byDuanGu = 0;
		$this->byHuoLuo = 0;
		$this->byXiSui = 0;
		$this->byDujieLevel = 0;
		$this->dwDujieExp = 0;
		$this->byQuality = 0;
		$this->dwSpiritPower = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwInstID = $this->qwInstID;
		$obj->wFighterID = $this->wFighterID;
		$obj->byRecruited = $this->byRecruited;
		$obj->byStar = $this->byStar;
		$obj->iSlot = $this->iSlot;
		$obj->iPos = $this->iPos;
		$obj->byLevel = $this->byLevel;
		$obj->qwExp = $this->qwExp;
		$obj->strName = $this->strName;
		$obj->dwHpMax = $this->dwHpMax;
		$obj->dwHp = $this->dwHp;
		$obj->dwAura = $this->dwAura;
		$obj->dwAuraMax = $this->dwAuraMax;
		$obj->byLianPi = $this->byLianPi;
		$obj->byTongJin = $this->byTongJin;
		$obj->byQiangJi = $this->byQiangJi;
		$obj->byDuanGu = $this->byDuanGu;
		$obj->byHuoLuo = $this->byHuoLuo;
		$obj->byXiSui = $this->byXiSui;
		$obj->byDujieLevel = $this->byDujieLevel;
		$obj->dwDujieExp = $this->dwDujieExp;
		$obj->byQuality = $this->byQuality;
		$obj->dwSpiritPower = $this->dwSpiritPower;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterBaseInfo;
		$s->qwInstID = ByteUtil::readUINT64($data);
		$s->wFighterID = ByteUtil::readUINT16($data);
		$s->byRecruited = ByteUtil::readUINT8($data);
		$s->byStar = ByteUtil::readUINT8($data);
		$s->iSlot = ByteUtil::readINT32($data);
		$s->iPos = ByteUtil::readINT32($data);
		$s->byLevel = ByteUtil::readUINT8($data);
		$s->qwExp = ByteUtil::readUINT64($data);
		$s->strName = ByteUtil::readString($data);
		$s->dwHpMax = ByteUtil::readUINT32($data);
		$s->dwHp = ByteUtil::readUINT32($data);
		$s->dwAura = ByteUtil::readUINT32($data);
		$s->dwAuraMax = ByteUtil::readUINT32($data);
		$s->byLianPi = ByteUtil::readUINT8($data);
		$s->byTongJin = ByteUtil::readUINT8($data);
		$s->byQiangJi = ByteUtil::readUINT8($data);
		$s->byDuanGu = ByteUtil::readUINT8($data);
		$s->byHuoLuo = ByteUtil::readUINT8($data);
		$s->byXiSui = ByteUtil::readUINT8($data);
		$s->byDujieLevel = ByteUtil::readUINT8($data);
		$s->dwDujieExp = ByteUtil::readUINT32($data);
		$s->byQuality = ByteUtil::readUINT8($data);
		$s->dwSpiritPower = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterBaseInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwInstID);
		ByteUtil::writeUINT16($data, $this->wFighterID);
		ByteUtil::writeUINT8($data, $this->byRecruited);
		ByteUtil::writeUINT8($data, $this->byStar);
		ByteUtil::writeINT32($data, $this->iSlot);
		ByteUtil::writeINT32($data, $this->iPos);
		ByteUtil::writeUINT8($data, $this->byLevel);
		ByteUtil::writeUINT64($data, $this->qwExp);
		ByteUtil::writeString($data, $this->strName);
		ByteUtil::writeUINT32($data, $this->dwHpMax);
		ByteUtil::writeUINT32($data, $this->dwHp);
		ByteUtil::writeUINT32($data, $this->dwAura);
		ByteUtil::writeUINT32($data, $this->dwAuraMax);
		ByteUtil::writeUINT8($data, $this->byLianPi);
		ByteUtil::writeUINT8($data, $this->byTongJin);
		ByteUtil::writeUINT8($data, $this->byQiangJi);
		ByteUtil::writeUINT8($data, $this->byDuanGu);
		ByteUtil::writeUINT8($data, $this->byHuoLuo);
		ByteUtil::writeUINT8($data, $this->byXiSui);
		ByteUtil::writeUINT8($data, $this->byDujieLevel);
		ByteUtil::writeUINT32($data, $this->dwDujieExp);
		ByteUtil::writeUINT8($data, $this->byQuality);
		ByteUtil::writeUINT32($data, $this->dwSpiritPower);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//参与战斗的技能信息
final class SFightSkillInfo
{
	public $byIdx; //(UINT8)技能槽idx
	public $dwSkillID; //(UINT32)技能ID

	//构造函数
	function __construct()
	{
		$this->byIdx = 0;
		$this->dwSkillID = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->byIdx = $this->byIdx;
		$obj->dwSkillID = $this->dwSkillID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFightSkillInfo;
		$s->byIdx = ByteUtil::readUINT8($data);
		$s->dwSkillID = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFightSkillInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT8($data, $this->byIdx);
		ByteUtil::writeUINT32($data, $this->dwSkillID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//心法信息
final class SXinFaInfo
{
	public $dwXinFaID; //(UINT32)心法ID
	public $byXinFaLvl; //(UINT8)心法等级
	public $iSlot; //(INT32)心法槽 -1表示心法没装备

	//构造函数
	function __construct()
	{
		$this->dwXinFaID = 0;
		$this->byXinFaLvl = 0;
		$this->iSlot = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwXinFaID = $this->dwXinFaID;
		$obj->byXinFaLvl = $this->byXinFaLvl;
		$obj->iSlot = $this->iSlot;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SXinFaInfo;
		$s->dwXinFaID = ByteUtil::readUINT32($data);
		$s->byXinFaLvl = ByteUtil::readUINT8($data);
		$s->iSlot = ByteUtil::readINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SXinFaInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwXinFaID);
		ByteUtil::writeUINT8($data, $this->byXinFaLvl);
		ByteUtil::writeINT32($data, $this->iSlot);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//数据库同步到游戏服务器的心法信息
final class SXinFaDBInfo
{
	public $qwRoleID; //(UINT64)所属角色唯一ID
	public $qwOwnerID; //(UINT64)所属散仙ID
	public $dwXinFaID; //(UINT32)心法ID
	public $byXinFaLvl; //(UINT8)心法等级
	public $iSlot; //(INT32)心法槽 -1表示心法没装备

	//构造函数
	function __construct()
	{
		$this->qwRoleID = new Math_BigInteger;
		$this->qwOwnerID = new Math_BigInteger;
		$this->dwXinFaID = 0;
		$this->byXinFaLvl = 0;
		$this->iSlot = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->qwRoleID = $this->qwRoleID;
		$obj->qwOwnerID = $this->qwOwnerID;
		$obj->dwXinFaID = $this->dwXinFaID;
		$obj->byXinFaLvl = $this->byXinFaLvl;
		$obj->iSlot = $this->iSlot;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SXinFaDBInfo;
		$s->qwRoleID = ByteUtil::readUINT64($data);
		$s->qwOwnerID = ByteUtil::readUINT64($data);
		$s->dwXinFaID = ByteUtil::readUINT32($data);
		$s->byXinFaLvl = ByteUtil::readUINT8($data);
		$s->iSlot = ByteUtil::readINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SXinFaDBInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT64($data, $this->qwRoleID);
		ByteUtil::writeUINT64($data, $this->qwOwnerID);
		ByteUtil::writeUINT32($data, $this->dwXinFaID);
		ByteUtil::writeUINT8($data, $this->byXinFaLvl);
		ByteUtil::writeINT32($data, $this->iSlot);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//战斗者信息
final class SFighterInfo
{
	public $oBaseInfo; //(类类型：SFighterBaseInfo)基本信息
	public $oAttrVec; //(SFtAttrMod的数组)将属性
	public $vActiveSkill; //(SFightSkillInfo的数组)装备的主动技能
	public $vPassiveSkill; //(SFightSkillInfo的数组)被动技能
	public $oPeerLees; //(类类型：SFightSkillInfo)无双技能
	public $vecXinFa; //(SXinFaInfo的数组)散仙已经学会的心法信息(注：供客户端计算属性百分比加成)
	public $vecStoneItem; //(SItem的数组)宝石信息
	public $vecEquipTrump; //(SEquipTrump的数组)装备法宝信息

	//构造函数
	function __construct()
	{
		$this->oBaseInfo = new SFighterBaseInfo;
		$this->oAttrVec = array();
		$this->vActiveSkill = array();
		$this->vPassiveSkill = array();
		$this->oPeerLees = new SFightSkillInfo;
		$this->vecXinFa = array();
		$this->vecStoneItem = array();
		$this->vecEquipTrump = array();
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->oBaseInfo = $this->oBaseInfo;
		$obj->oAttrVec = $this->oAttrVec;
		$obj->vActiveSkill = $this->vActiveSkill;
		$obj->vPassiveSkill = $this->vPassiveSkill;
		$obj->oPeerLees = $this->oPeerLees;
		$obj->vecXinFa = $this->vecXinFa;
		$obj->vecStoneItem = $this->vecStoneItem;
		$obj->vecEquipTrump = $this->vecEquipTrump;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterInfo;
		$s->oBaseInfo = SFighterBaseInfo::fromStream($data);
		$s->oAttrVec = SFtAttrMod::vectorFromStream($data);
		$s->vActiveSkill = SFightSkillInfo::vectorFromStream($data);
		$s->vPassiveSkill = SFightSkillInfo::vectorFromStream($data);
		$s->oPeerLees = SFightSkillInfo::fromStream($data);
		$s->vecXinFa = SXinFaInfo::vectorFromStream($data);
		$s->vecStoneItem = SItem::superVectorFromStream($data);
		$s->vecEquipTrump = SEquipTrump::vectorFromStream($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterInfo::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		$this->oBaseInfo->toStream($data);
		SFtAttrMod::vectorToStream($data, $this->oAttrVec);
		SFightSkillInfo::vectorToStream($data, $this->vActiveSkill);
		SFightSkillInfo::vectorToStream($data, $this->vPassiveSkill);
		$this->oPeerLees->toStream($data);
		SXinFaInfo::vectorToStream($data, $this->vecXinFa);
		SItem::superVectorToStream($data, $this->vecStoneItem);
		SEquipTrump::vectorToStream($data, $this->vecEquipTrump);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//阵型位置信息
final class SFighterPos
{
	public $qwInstID; //(UINT64)将唯一ID
	public $iPos; //(INT32)将在阵型中的位置：-1表示下阵型

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
		$s = new SFighterPos;
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
			$s = SFighterPos::fromStream($data);
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

//散仙技能信息
final class SFighterSkill
{
	public $dwSkillID; //(UINT32)技能ID

	//构造函数
	function __construct()
	{
		$this->dwSkillID = 0;
	}

	//拷贝到另一个对象
	function copyTo($obj)
	{
		$obj->dwSkillID = $this->dwSkillID;
	}

	/////////////////////以下为序列化函数/////////////////////

	static function fromStream(&$data)
	{
		$s = new SFighterSkill;
		$s->dwSkillID = ByteUtil::readUINT32($data);
		return $s;
	}

	static function vectorFromStream(&$data)
	{
		$length = ByteUtil::readVectorLength($data);
		$arr = array();
		for($i = 0; $i < $length; ++$i)
		{
			$s = SFighterSkill::fromStream($data);
			$arr[$i] = $s;
		}
		return $arr;
	}

	function toStream(&$data)
	{
		ByteUtil::writeUINT32($data, $this->dwSkillID);
	}

	static function vectorToStream(&$data, $arr)
	{
		ByteUtil::writeVectorLength($data, count($arr));
		foreach($arr as $s)
			$s->toStream($data);
	}
}

//函数[FighterSkillEquipTo:散仙装备主动技能]的返回的参数组成的结构体
class SRetParam_FighterSkillEquipTo
{
	public $eResult; //(枚举类型：ESkillResult)结果
	public $vActiveSkill; //(SFightSkillInfo的数组)装备的主动技能

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vActiveSkill = array();
	}
};

//函数[FighterSkillLevelUp:散仙技能升级]的返回的参数组成的结构体
class SRetParam_FighterSkillLevelUp
{
	public $eResult; //(枚举类型：ESkillResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FighterPassiveSkillLevelUp:散仙被动技能升级]的返回的参数组成的结构体
class SRetParam_FighterPassiveSkillLevelUp
{
	public $eResult; //(枚举类型：ESkillResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[GetTavernInfo:获取客栈信息]的返回的参数组成的结构体
class SRetParam_GetTavernInfo
{
	public $dwDrawCount; //(UINT32)免费求签次数
	public $vecTavernInfo; //(STavernInfo的数组)具体客栈信息

	//构造函数
	function __construct()
	{
		$this->dwDrawCount = 0;
		$this->vecTavernInfo = array();
	}
};

//函数[Draw:求签]的返回的参数组成的结构体
class SRetParam_Draw
{
	public $eResult; //(枚举类型：EDrawResult)返回结果
	public $vecItemGet; //(SItemCount的数组)求签获得物品

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecItemGet = array();
	}
};

//函数[FighterRecruit:招募]的返回的参数组成的结构体
class SRetParam_FighterRecruit
{
	public $eResult; //(枚举类型：ERecruitResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[CuiTiUpgrade:淬体升级]的返回的参数组成的结构体
class SRetParam_CuiTiUpgrade
{
	public $eResult; //(枚举类型：ECuiTiResult)结果
	public $byLevel; //(UINT8)当前淬体等级

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->byLevel = 0;
	}
};

//函数[CuiTiAllUpgrade:散仙淬体全体(六种)升级一次]的返回的参数组成的结构体
class SRetParam_CuiTiAllUpgrade
{
	public $eResult; //(枚举类型：ECuiTiResult)结果
	public $vecLevel; //(UINT8数组)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->vecLevel = array();
	}
};

//函数[FighterShift:转移]的返回的参数组成的结构体
class SRetParam_FighterShift
{
	public $eResult; //(枚举类型：EShiftResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FighterSyncLevel:同步等级]的返回的参数组成的结构体
class SRetParam_FighterSyncLevel
{
	public $eResult; //(枚举类型：ESyncLevelResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[UpgradeDujie:渡劫升级]的返回的参数组成的结构体
class SRetParam_UpgradeDujie
{
	public $eResult; //(枚举类型：EDujieResult)结果
	public $qwInstID; //(UINT64)将唯一ID

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
		$this->qwInstID = new Math_BigInteger;
	}
};

//函数[ReqFighterXinFaInfo:请求散仙心法]的返回的参数组成的结构体
class SRetParam_ReqFighterXinFaInfo
{
	public $vecFighterXinFa; //(SXinFaInfo的数组)散仙已经学会的心法信息

	//构造函数
	function __construct()
	{
		$this->vecFighterXinFa = array();
	}
};

//函数[FighterActiveXinFa:散仙学习心法]的返回的参数组成的结构体
class SRetParam_FighterActiveXinFa
{
	public $eResult; //(枚举类型：EXinFaResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FighterXinFaLevelUp:散仙心法升级]的返回的参数组成的结构体
class SRetParam_FighterXinFaLevelUp
{
	public $eResult; //(枚举类型：EXinFaResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FighterXinFaDisperse:散仙心法散功]的返回的参数组成的结构体
class SRetParam_FighterXinFaDisperse
{
	public $eResult; //(枚举类型：EXinFaResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[GetAllFighterCombination:获取玩家的所有散仙组合]的返回的参数组成的结构体
class SRetParam_GetAllFighterCombination
{
	public $vecCombinationInfo; //(SFighterCombination的数组)玩家的散仙组合信息

	//构造函数
	function __construct()
	{
		$this->vecCombinationInfo = array();
	}
};

//函数[ActiveCombination:激活散仙组合]的返回的参数组成的结构体
class SRetParam_ActiveCombination
{
	public $eResult; //(枚举类型：ECombinationResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[UpgradeCombination:升级散仙组合]的返回的参数组成的结构体
class SRetParam_UpgradeCombination
{
	public $oCombinationInfo; //(类类型：SFighterCombination)当前升级的散仙组合信息
	public $eResult; //(枚举类型：ECombinationResult)结果

	//构造函数
	function __construct()
	{
		$this->oCombinationInfo = new SFighterCombination;
		$this->eResult = 0;
	}
};

//函数[EquipToCombinationSkill:装备散仙组合技能(连携技)]的返回的参数组成的结构体
class SRetParam_EquipToCombinationSkill
{
	public $eResult; //(枚举类型：ECombinationResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[FighterDismiss:散仙散功]的返回的参数组成的结构体
class SRetParam_FighterDismiss
{
	public $eResult; //(枚举类型：EDismissResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

//函数[GetFighterBuyInfo:获取购买散仙信息]的返回的参数组成的结构体
class SRetParam_GetFighterBuyInfo
{
	public $vecFighterBuyInfo; //(SFighterBuyInfo的数组)购买散仙信息

	//构造函数
	function __construct()
	{
		$this->vecFighterBuyInfo = array();
	}
};

//函数[FighterBuy:散仙购买]的返回的参数组成的结构体
class SRetParam_FighterBuy
{
	public $eResult; //(枚举类型：EFighterBuyResult)结果

	//构造函数
	function __construct()
	{
		$this->eResult = 0;
	}
};

////////////////////////////////////////////////////////////
//协议类：道具相关协议
abstract class FighterProtBase extends ProtocolBase
{
	/////////////////////以下为发送函数/////////////////////
	//发送：散仙装备主动技能
	function send_FighterSkillEquipTo(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwSkillID,  //(UINT32)技能ID
		$iSlot //(INT32)技能槽 -1表示卸下技能
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 1);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 1;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwSkillID);
		ByteUtil::writeINT32($data, $iSlot);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙技能升级
	function send_FighterSkillLevelUp(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwSkillID //(UINT32)技能ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 2);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 2;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwSkillID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙被动技能升级
	function send_FighterPassiveSkillLevelUp(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwSkillID //(UINT32)技能ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 3);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 3;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwSkillID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取客栈信息
	function send_GetTavernInfo(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 4);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 4;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：求签
	function send_Draw(
		$eType //(枚举类型：EDrawType)求签类型
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 5);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 5;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $eType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：招募
	function send_FighterRecruit(
		$wFighterID //(UINT16)将ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 6);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 6;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wFighterID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：淬体升级
	function send_CuiTiUpgrade(
		$qwInstID,  //(UINT64)将唯一ID
		$eCuiTiType,  //(枚举类型：ECuiTiType)淬体类型
		$byTimes //(UINT8)次数
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 7);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 7;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT8($data, $eCuiTiType);
		ByteUtil::writeUINT8($data, $byTimes);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙淬体全体(六种)升级一次
	function send_CuiTiAllUpgrade(
		$qwInstID //(UINT64)将唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 8);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 8;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：转移
	function send_FighterShift(
		$qwInstIDSrc,  //(UINT64)将唯一ID
		$qwInstIDDst //(UINT64)将唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 9);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 9;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstIDSrc);
		ByteUtil::writeUINT64($data, $qwInstIDDst);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：同步等级
	function send_FighterSyncLevel(
		$qwInstID,  //(UINT64)将唯一ID
		$byGoalLvl //(UINT8)同步的目标等级
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 10);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 10;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT8($data, $byGoalLvl);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：渡劫升级
	function send_UpgradeDujie(
		$qwInstID,  //(UINT64)将唯一ID
		$byOneKey //(UINT8)是否一键(是>0 否=0)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 11);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 11;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT8($data, $byOneKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：请求散仙心法
	function send_ReqFighterXinFaInfo(
		$qwInstID //(UINT64)散仙唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 12);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 12;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙学习心法
	function send_FighterActiveXinFa(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwXinFaID //(UINT32)心法ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 13);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 13;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwXinFaID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙心法升级
	function send_FighterXinFaLevelUp(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwXinFaID //(UINT32)心法ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 14);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 14;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwXinFaID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙心法散功
	function send_FighterXinFaDisperse(
		$qwInstID,  //(UINT64)散仙唯一ID
		$dwXinFaID //(UINT32)心法ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 15);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 15;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		ByteUtil::writeUINT32($data, $dwXinFaID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取玩家的所有散仙组合
	function send_GetAllFighterCombination(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 16);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 16;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：激活散仙组合
	function send_ActiveCombination(
		$byGroupID //(UINT8)散仙组合ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 17);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 17;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byGroupID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：升级散仙组合
	function send_UpgradeCombination(
		$byGroupID,  //(UINT8)散仙组合ID
		$byOneKey //(UINT8)是否一键(是>0 否=0)
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 18);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 18;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byGroupID);
		ByteUtil::writeUINT8($data, $byOneKey);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：装备散仙组合技能(连携技)
	function send_EquipToCombinationSkill(
		$byGroupID,  //(UINT8)散仙组合ID
		$byType //(UINT8)1出战在阵型 2出战在守卫峨眉
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 19);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 19;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT8($data, $byGroupID);
		ByteUtil::writeUINT8($data, $byType);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙散功
	function send_FighterDismiss(
		$qwInstID //(UINT64)散仙唯一ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 20);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 20;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT64($data, $qwInstID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：获取购买散仙信息
	function send_GetFighterBuyInfo(
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 21);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 21;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		return $this->_svrHandler->sendPacket($data);
	}

	//发送：散仙购买
	function send_FighterBuy(
		$wFighterID //(UINT16)将ID
	)
	{
		$sessionID = $this->_sessionMgr->getNewSession($this, 22);
		$data = '';
		ByteUtil::writeINT8($data, $this->_protID);
		$funcID = 22;
		ByteUtil::writeINT8($data, $funcID);
		ByteUtil::writeUINT32($data, $sessionID);
		ByteUtil::writeUINT16($data, $wFighterID);
		return $this->_svrHandler->sendPacket($data);
	}

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：装备技能返回
	abstract function onRecv_SkillUpNotify(
		$dwSkillID, //(UINT32)技能ID
		$iSlot //(INT32)技能槽 -1表示卸下技能
	);

	//接收：增加新技能
	abstract function onRecv_SkillAddNotify(
		$dwSkillID //(UINT32)技能ID
	);

	//接收：散仙血脉激活
	abstract function onRecv_InstinctActiveNotify(
		$qwInstID, //(UINT64)散仙唯一ID
		$vecInstinctIDRandom, //(UINT16数组)血脉随机结果
		$vecInstinctIDRet //(UINT16数组)血脉最终结果
	);

	//接收：招募散仙成功的弹框通知
	abstract function onRecv_RecruitSuccNotify(
		$wFighterID //(UINT16)散仙ID
	);

	//接收：阵型位置变更
	abstract function onRecv_FighterPosNotify(
		$vecPos //(SFighterPos的数组)阵型位置
	);

	//接收：更新散仙的渡劫数据
	abstract function onRecv_UpdateDujieValue(
		$qwInstID, //(UINT64)将唯一ID
		$byDujieLevel, //(UINT8)当前渡劫等级
		$dwDujieExp, //(UINT32)当前渡劫经验
		$dwSpiritPower //(UINT32)元神力
	);

	//接收：心法数据更新通知
	abstract function onRecv_XinFaNotify(
		$qwInstID, //(UINT64)将唯一ID
		$dwXinFaID, //(UINT32)心法ID
		$byXinFaLvl, //(UINT8)心法等级
		$iSlot //(INT32)心法槽 -1表示心法没装备
	);

	//接收：散仙心法主卷等级满了添加一个天赋技能更新通知
	abstract function onRecv_AddTalentSkillNotify(
		$qwInstID, //(UINT64)将唯一ID
		$byIdx, //(UINT8)技能槽idx
		$dwSkillID //(UINT32)技能ID
	);

	//接收：散仙技能列表返回
	abstract function onRecv_SkillListNotify(
		$qwInstID, //(UINT64)将唯一ID
		$VecFighterSkill //(SFighterSkill的数组)技能ID
	);

	//接收：玩家的散仙组合列表返回
	abstract function onRecv_FighterCombinationNotify(
		$VecCombination //(SFighterCombination的数组)散仙组合列表
	);

	/////////////////////以下的返回函数需要重载/////////////////////
	//返回：散仙装备主动技能
	abstract function onReturn_FighterSkillEquipTo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterSkillEquipTo)返回的参数
	);

	//返回：散仙技能升级
	abstract function onReturn_FighterSkillLevelUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterSkillLevelUp)返回的参数
	);

	//返回：散仙被动技能升级
	abstract function onReturn_FighterPassiveSkillLevelUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterPassiveSkillLevelUp)返回的参数
	);

	//返回：获取客栈信息
	abstract function onReturn_GetTavernInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetTavernInfo)返回的参数
	);

	//返回：求签
	abstract function onReturn_Draw(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_Draw)返回的参数
	);

	//返回：招募
	abstract function onReturn_FighterRecruit(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterRecruit)返回的参数
	);

	//返回：淬体升级
	abstract function onReturn_CuiTiUpgrade(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_CuiTiUpgrade)返回的参数
	);

	//返回：散仙淬体全体(六种)升级一次
	abstract function onReturn_CuiTiAllUpgrade(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_CuiTiAllUpgrade)返回的参数
	);

	//返回：转移
	abstract function onReturn_FighterShift(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterShift)返回的参数
	);

	//返回：同步等级
	abstract function onReturn_FighterSyncLevel(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterSyncLevel)返回的参数
	);

	//返回：渡劫升级
	abstract function onReturn_UpgradeDujie(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UpgradeDujie)返回的参数
	);

	//返回：请求散仙心法
	abstract function onReturn_ReqFighterXinFaInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ReqFighterXinFaInfo)返回的参数
	);

	//返回：散仙学习心法
	abstract function onReturn_FighterActiveXinFa(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterActiveXinFa)返回的参数
	);

	//返回：散仙心法升级
	abstract function onReturn_FighterXinFaLevelUp(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterXinFaLevelUp)返回的参数
	);

	//返回：散仙心法散功
	abstract function onReturn_FighterXinFaDisperse(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterXinFaDisperse)返回的参数
	);

	//返回：获取玩家的所有散仙组合
	abstract function onReturn_GetAllFighterCombination(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetAllFighterCombination)返回的参数
	);

	//返回：激活散仙组合
	abstract function onReturn_ActiveCombination(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_ActiveCombination)返回的参数
	);

	//返回：升级散仙组合
	abstract function onReturn_UpgradeCombination(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_UpgradeCombination)返回的参数
	);

	//返回：装备散仙组合技能(连携技)
	abstract function onReturn_EquipToCombinationSkill(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_EquipToCombinationSkill)返回的参数
	);

	//返回：散仙散功
	abstract function onReturn_FighterDismiss(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterDismiss)返回的参数
	);

	//返回：获取购买散仙信息
	abstract function onReturn_GetFighterBuyInfo(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_GetFighterBuyInfo)返回的参数
	);

	//返回：散仙购买
	abstract function onReturn_FighterBuy(
		$ret, //0为成功，1为失败，2为超时
		$retParam //(类类型：SRetParam_FighterBuy)返回的参数
	);

	/////////////////////以下为接收处理函数/////////////////////
	//接收处理：装备技能返回
	private function _doRecv_SkillUpNotify($data)
	{
		$dwSkillID = ByteUtil::readUINT32($data);
		$iSlot = ByteUtil::readINT32($data);
		return $this->onRecv_SkillUpNotify($dwSkillID, $iSlot);
	}

	//接收处理：增加新技能
	private function _doRecv_SkillAddNotify($data)
	{
		$dwSkillID = ByteUtil::readUINT32($data);
		return $this->onRecv_SkillAddNotify($dwSkillID);
	}

	//接收处理：散仙血脉激活
	private function _doRecv_InstinctActiveNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$vecInstinctIDRandom = ByteUtil::readVecUINT16($data);
		$vecInstinctIDRet = ByteUtil::readVecUINT16($data);
		return $this->onRecv_InstinctActiveNotify($qwInstID, $vecInstinctIDRandom, $vecInstinctIDRet);
	}

	//接收处理：招募散仙成功的弹框通知
	private function _doRecv_RecruitSuccNotify($data)
	{
		$wFighterID = ByteUtil::readUINT16($data);
		return $this->onRecv_RecruitSuccNotify($wFighterID);
	}

	//接收处理：阵型位置变更
	private function _doRecv_FighterPosNotify($data)
	{
		$vecPos = SFighterPos::vectorFromStream($data);
		return $this->onRecv_FighterPosNotify($vecPos);
	}

	//接收处理：更新散仙的渡劫数据
	private function _doRecv_UpdateDujieValue($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$byDujieLevel = ByteUtil::readUINT8($data);
		$dwDujieExp = ByteUtil::readUINT32($data);
		$dwSpiritPower = ByteUtil::readUINT32($data);
		return $this->onRecv_UpdateDujieValue($qwInstID, $byDujieLevel, $dwDujieExp, $dwSpiritPower);
	}

	//接收处理：心法数据更新通知
	private function _doRecv_XinFaNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$dwXinFaID = ByteUtil::readUINT32($data);
		$byXinFaLvl = ByteUtil::readUINT8($data);
		$iSlot = ByteUtil::readINT32($data);
		return $this->onRecv_XinFaNotify($qwInstID, $dwXinFaID, $byXinFaLvl, $iSlot);
	}

	//接收处理：散仙心法主卷等级满了添加一个天赋技能更新通知
	private function _doRecv_AddTalentSkillNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$byIdx = ByteUtil::readUINT8($data);
		$dwSkillID = ByteUtil::readUINT32($data);
		return $this->onRecv_AddTalentSkillNotify($qwInstID, $byIdx, $dwSkillID);
	}

	//接收处理：散仙技能列表返回
	private function _doRecv_SkillListNotify($data)
	{
		$qwInstID = ByteUtil::readUINT64($data);
		$VecFighterSkill = SFighterSkill::vectorFromStream($data);
		return $this->onRecv_SkillListNotify($qwInstID, $VecFighterSkill);
	}

	//接收处理：玩家的散仙组合列表返回
	private function _doRecv_FighterCombinationNotify($data)
	{
		$VecCombination = SFighterCombination::vectorFromStream($data);
		return $this->onRecv_FighterCombinationNotify($VecCombination);
	}

	/////////////////////以下为返回处理函数/////////////////////
	//返回处理：散仙装备主动技能
	private function _doReturn_FighterSkillEquipTo($data)
	{
		$retParam = new SRetParam_FighterSkillEquipTo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ESkillResult)结果
		$vActiveSkill = SFightSkillInfo::vectorFromStream($data); //装备的主动技能
		$retParam->eResult = $eResult;
		$retParam->vActiveSkill = $vActiveSkill;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterSkillEquipTo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙装备主动技能
	private function _onTimeOut_FighterSkillEquipTo($sessionID)
	{
		$retParam = new SRetParam_FighterSkillEquipTo;
		$this->onReturn_FighterSkillEquipTo(2, $retParam);
	}

	//返回处理：散仙技能升级
	private function _doReturn_FighterSkillLevelUp($data)
	{
		$retParam = new SRetParam_FighterSkillLevelUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ESkillResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterSkillLevelUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙技能升级
	private function _onTimeOut_FighterSkillLevelUp($sessionID)
	{
		$retParam = new SRetParam_FighterSkillLevelUp;
		$this->onReturn_FighterSkillLevelUp(2, $retParam);
	}

	//返回处理：散仙被动技能升级
	private function _doReturn_FighterPassiveSkillLevelUp($data)
	{
		$retParam = new SRetParam_FighterPassiveSkillLevelUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ESkillResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterPassiveSkillLevelUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙被动技能升级
	private function _onTimeOut_FighterPassiveSkillLevelUp($sessionID)
	{
		$retParam = new SRetParam_FighterPassiveSkillLevelUp;
		$this->onReturn_FighterPassiveSkillLevelUp(2, $retParam);
	}

	//返回处理：获取客栈信息
	private function _doReturn_GetTavernInfo($data)
	{
		$retParam = new SRetParam_GetTavernInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$dwDrawCount = ByteUtil::readUINT32($data); //(无符号32位整数)免费求签次数
		$vecTavernInfo = STavernInfo::vectorFromStream($data); //具体客栈信息
		$retParam->dwDrawCount = $dwDrawCount;
		$retParam->vecTavernInfo = $vecTavernInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetTavernInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取客栈信息
	private function _onTimeOut_GetTavernInfo($sessionID)
	{
		$retParam = new SRetParam_GetTavernInfo;
		$this->onReturn_GetTavernInfo(2, $retParam);
	}

	//返回处理：求签
	private function _doReturn_Draw($data)
	{
		$retParam = new SRetParam_Draw;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EDrawResult)返回结果
		$vecItemGet = SItemCount::vectorFromStream($data); //求签获得物品
		$retParam->eResult = $eResult;
		$retParam->vecItemGet = $vecItemGet;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_Draw($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：求签
	private function _onTimeOut_Draw($sessionID)
	{
		$retParam = new SRetParam_Draw;
		$this->onReturn_Draw(2, $retParam);
	}

	//返回处理：招募
	private function _doReturn_FighterRecruit($data)
	{
		$retParam = new SRetParam_FighterRecruit;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ERecruitResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterRecruit($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：招募
	private function _onTimeOut_FighterRecruit($sessionID)
	{
		$retParam = new SRetParam_FighterRecruit;
		$this->onReturn_FighterRecruit(2, $retParam);
	}

	//返回处理：淬体升级
	private function _doReturn_CuiTiUpgrade($data)
	{
		$retParam = new SRetParam_CuiTiUpgrade;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECuiTiResult)结果
		$byLevel = ByteUtil::readUINT8($data); //(无符号8位整数)当前淬体等级
		$retParam->eResult = $eResult;
		$retParam->byLevel = $byLevel;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_CuiTiUpgrade($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：淬体升级
	private function _onTimeOut_CuiTiUpgrade($sessionID)
	{
		$retParam = new SRetParam_CuiTiUpgrade;
		$this->onReturn_CuiTiUpgrade(2, $retParam);
	}

	//返回处理：散仙淬体全体(六种)升级一次
	private function _doReturn_CuiTiAllUpgrade($data)
	{
		$retParam = new SRetParam_CuiTiAllUpgrade;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECuiTiResult)结果
		$vecLevel = ByteUtil::readVecUINT8($data); //(无符号8位整数)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)
		$retParam->eResult = $eResult;
		$retParam->vecLevel = $vecLevel;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_CuiTiAllUpgrade($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙淬体全体(六种)升级一次
	private function _onTimeOut_CuiTiAllUpgrade($sessionID)
	{
		$retParam = new SRetParam_CuiTiAllUpgrade;
		$this->onReturn_CuiTiAllUpgrade(2, $retParam);
	}

	//返回处理：转移
	private function _doReturn_FighterShift($data)
	{
		$retParam = new SRetParam_FighterShift;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EShiftResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterShift($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：转移
	private function _onTimeOut_FighterShift($sessionID)
	{
		$retParam = new SRetParam_FighterShift;
		$this->onReturn_FighterShift(2, $retParam);
	}

	//返回处理：同步等级
	private function _doReturn_FighterSyncLevel($data)
	{
		$retParam = new SRetParam_FighterSyncLevel;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ESyncLevelResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterSyncLevel($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：同步等级
	private function _onTimeOut_FighterSyncLevel($sessionID)
	{
		$retParam = new SRetParam_FighterSyncLevel;
		$this->onReturn_FighterSyncLevel(2, $retParam);
	}

	//返回处理：渡劫升级
	private function _doReturn_UpgradeDujie($data)
	{
		$retParam = new SRetParam_UpgradeDujie;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EDujieResult)结果
		$qwInstID = ByteUtil::readUINT64($data); //(无符号64位整数)将唯一ID
		$retParam->eResult = $eResult;
		$retParam->qwInstID = $qwInstID;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UpgradeDujie($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：渡劫升级
	private function _onTimeOut_UpgradeDujie($sessionID)
	{
		$retParam = new SRetParam_UpgradeDujie;
		$this->onReturn_UpgradeDujie(2, $retParam);
	}

	//返回处理：请求散仙心法
	private function _doReturn_ReqFighterXinFaInfo($data)
	{
		$retParam = new SRetParam_ReqFighterXinFaInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecFighterXinFa = SXinFaInfo::vectorFromStream($data); //散仙已经学会的心法信息
		$retParam->vecFighterXinFa = $vecFighterXinFa;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ReqFighterXinFaInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：请求散仙心法
	private function _onTimeOut_ReqFighterXinFaInfo($sessionID)
	{
		$retParam = new SRetParam_ReqFighterXinFaInfo;
		$this->onReturn_ReqFighterXinFaInfo(2, $retParam);
	}

	//返回处理：散仙学习心法
	private function _doReturn_FighterActiveXinFa($data)
	{
		$retParam = new SRetParam_FighterActiveXinFa;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EXinFaResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterActiveXinFa($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙学习心法
	private function _onTimeOut_FighterActiveXinFa($sessionID)
	{
		$retParam = new SRetParam_FighterActiveXinFa;
		$this->onReturn_FighterActiveXinFa(2, $retParam);
	}

	//返回处理：散仙心法升级
	private function _doReturn_FighterXinFaLevelUp($data)
	{
		$retParam = new SRetParam_FighterXinFaLevelUp;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EXinFaResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterXinFaLevelUp($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙心法升级
	private function _onTimeOut_FighterXinFaLevelUp($sessionID)
	{
		$retParam = new SRetParam_FighterXinFaLevelUp;
		$this->onReturn_FighterXinFaLevelUp(2, $retParam);
	}

	//返回处理：散仙心法散功
	private function _doReturn_FighterXinFaDisperse($data)
	{
		$retParam = new SRetParam_FighterXinFaDisperse;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EXinFaResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterXinFaDisperse($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙心法散功
	private function _onTimeOut_FighterXinFaDisperse($sessionID)
	{
		$retParam = new SRetParam_FighterXinFaDisperse;
		$this->onReturn_FighterXinFaDisperse(2, $retParam);
	}

	//返回处理：获取玩家的所有散仙组合
	private function _doReturn_GetAllFighterCombination($data)
	{
		$retParam = new SRetParam_GetAllFighterCombination;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecCombinationInfo = SFighterCombination::vectorFromStream($data); //玩家的散仙组合信息
		$retParam->vecCombinationInfo = $vecCombinationInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetAllFighterCombination($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取玩家的所有散仙组合
	private function _onTimeOut_GetAllFighterCombination($sessionID)
	{
		$retParam = new SRetParam_GetAllFighterCombination;
		$this->onReturn_GetAllFighterCombination(2, $retParam);
	}

	//返回处理：激活散仙组合
	private function _doReturn_ActiveCombination($data)
	{
		$retParam = new SRetParam_ActiveCombination;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECombinationResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_ActiveCombination($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：激活散仙组合
	private function _onTimeOut_ActiveCombination($sessionID)
	{
		$retParam = new SRetParam_ActiveCombination;
		$this->onReturn_ActiveCombination(2, $retParam);
	}

	//返回处理：升级散仙组合
	private function _doReturn_UpgradeCombination($data)
	{
		$retParam = new SRetParam_UpgradeCombination;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$oCombinationInfo = SFighterCombination::fromStream($data); //当前升级的散仙组合信息
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECombinationResult)结果
		$retParam->oCombinationInfo = $oCombinationInfo;
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_UpgradeCombination($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：升级散仙组合
	private function _onTimeOut_UpgradeCombination($sessionID)
	{
		$retParam = new SRetParam_UpgradeCombination;
		$this->onReturn_UpgradeCombination(2, $retParam);
	}

	//返回处理：装备散仙组合技能(连携技)
	private function _doReturn_EquipToCombinationSkill($data)
	{
		$retParam = new SRetParam_EquipToCombinationSkill;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：ECombinationResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_EquipToCombinationSkill($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：装备散仙组合技能(连携技)
	private function _onTimeOut_EquipToCombinationSkill($sessionID)
	{
		$retParam = new SRetParam_EquipToCombinationSkill;
		$this->onReturn_EquipToCombinationSkill(2, $retParam);
	}

	//返回处理：散仙散功
	private function _doReturn_FighterDismiss($data)
	{
		$retParam = new SRetParam_FighterDismiss;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EDismissResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterDismiss($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙散功
	private function _onTimeOut_FighterDismiss($sessionID)
	{
		$retParam = new SRetParam_FighterDismiss;
		$this->onReturn_FighterDismiss(2, $retParam);
	}

	//返回处理：获取购买散仙信息
	private function _doReturn_GetFighterBuyInfo($data)
	{
		$retParam = new SRetParam_GetFighterBuyInfo;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$vecFighterBuyInfo = SFighterBuyInfo::vectorFromStream($data); //购买散仙信息
		$retParam->vecFighterBuyInfo = $vecFighterBuyInfo;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_GetFighterBuyInfo($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：获取购买散仙信息
	private function _onTimeOut_GetFighterBuyInfo($sessionID)
	{
		$retParam = new SRetParam_GetFighterBuyInfo;
		$this->onReturn_GetFighterBuyInfo(2, $retParam);
	}

	//返回处理：散仙购买
	private function _doReturn_FighterBuy($data)
	{
		$retParam = new SRetParam_FighterBuy;
		$sessionID = ByteUtil::readUINT32($data);
		$retVal = ByteUtil::readBool($data);
		$eResult = ByteUtil::readUINT8($data); //(枚举类型：EFighterBuyResult)结果
		$retParam->eResult = $eResult;
		$ret = 0;
		if(!$retVal)
			$ret = 1;
		$result = $this->onReturn_FighterBuy($ret, $retParam);
		$this->_sessionMgr->delSession($sessionID);
		return $result;
	}

	//超时处理：散仙购买
	private function _onTimeOut_FighterBuy($sessionID)
	{
		$retParam = new SRetParam_FighterBuy;
		$this->onReturn_FighterBuy(2, $retParam);
	}

	/////////////////////以下为协议接口/////////////////////
	private $_recvFuncList;
	private $_retFuncList;
	private $_timeFuncList;

	function __construct()
	{
		$this->_protID = 20;
		$this->_recvFuncList[0] = '_doRecv_SkillUpNotify'; //FuncID: 1
		$this->_recvFuncList[1] = '_doRecv_SkillAddNotify'; //FuncID: 2
		$this->_recvFuncList[2] = '_doRecv_InstinctActiveNotify'; //FuncID: 3
		$this->_recvFuncList[3] = '_doRecv_RecruitSuccNotify'; //FuncID: 4
		$this->_recvFuncList[4] = '_doRecv_FighterPosNotify'; //FuncID: 5
		$this->_recvFuncList[5] = '_doRecv_UpdateDujieValue'; //FuncID: 6
		$this->_recvFuncList[6] = '_doRecv_XinFaNotify'; //FuncID: 7
		$this->_recvFuncList[7] = '_doRecv_AddTalentSkillNotify'; //FuncID: 8
		$this->_recvFuncList[8] = '_doRecv_SkillListNotify'; //FuncID: 9
		$this->_recvFuncList[9] = '_doRecv_FighterCombinationNotify'; //FuncID: 10

		$this->_retFuncList[0] = '_doReturn_FighterSkillEquipTo'; //FuncID: 1
		$this->_retFuncList[1] = '_doReturn_FighterSkillLevelUp'; //FuncID: 2
		$this->_retFuncList[2] = '_doReturn_FighterPassiveSkillLevelUp'; //FuncID: 3
		$this->_retFuncList[3] = '_doReturn_GetTavernInfo'; //FuncID: 4
		$this->_retFuncList[4] = '_doReturn_Draw'; //FuncID: 5
		$this->_retFuncList[5] = '_doReturn_FighterRecruit'; //FuncID: 6
		$this->_retFuncList[6] = '_doReturn_CuiTiUpgrade'; //FuncID: 7
		$this->_retFuncList[7] = '_doReturn_CuiTiAllUpgrade'; //FuncID: 8
		$this->_retFuncList[8] = '_doReturn_FighterShift'; //FuncID: 9
		$this->_retFuncList[9] = '_doReturn_FighterSyncLevel'; //FuncID: 10
		$this->_retFuncList[10] = '_doReturn_UpgradeDujie'; //FuncID: 11
		$this->_retFuncList[11] = '_doReturn_ReqFighterXinFaInfo'; //FuncID: 12
		$this->_retFuncList[12] = '_doReturn_FighterActiveXinFa'; //FuncID: 13
		$this->_retFuncList[13] = '_doReturn_FighterXinFaLevelUp'; //FuncID: 14
		$this->_retFuncList[14] = '_doReturn_FighterXinFaDisperse'; //FuncID: 15
		$this->_retFuncList[15] = '_doReturn_GetAllFighterCombination'; //FuncID: 16
		$this->_retFuncList[16] = '_doReturn_ActiveCombination'; //FuncID: 17
		$this->_retFuncList[17] = '_doReturn_UpgradeCombination'; //FuncID: 18
		$this->_retFuncList[18] = '_doReturn_EquipToCombinationSkill'; //FuncID: 19
		$this->_retFuncList[19] = '_doReturn_FighterDismiss'; //FuncID: 20
		$this->_retFuncList[20] = '_doReturn_GetFighterBuyInfo'; //FuncID: 21
		$this->_retFuncList[21] = '_doReturn_FighterBuy'; //FuncID: 22

		$this->_timeFuncList[0] = '_onTimeOut_FighterSkillEquipTo'; //FuncID: 1
		$this->_timeFuncList[1] = '_onTimeOut_FighterSkillLevelUp'; //FuncID: 2
		$this->_timeFuncList[2] = '_onTimeOut_FighterPassiveSkillLevelUp'; //FuncID: 3
		$this->_timeFuncList[3] = '_onTimeOut_GetTavernInfo'; //FuncID: 4
		$this->_timeFuncList[4] = '_onTimeOut_Draw'; //FuncID: 5
		$this->_timeFuncList[5] = '_onTimeOut_FighterRecruit'; //FuncID: 6
		$this->_timeFuncList[6] = '_onTimeOut_CuiTiUpgrade'; //FuncID: 7
		$this->_timeFuncList[7] = '_onTimeOut_CuiTiAllUpgrade'; //FuncID: 8
		$this->_timeFuncList[8] = '_onTimeOut_FighterShift'; //FuncID: 9
		$this->_timeFuncList[9] = '_onTimeOut_FighterSyncLevel'; //FuncID: 10
		$this->_timeFuncList[10] = '_onTimeOut_UpgradeDujie'; //FuncID: 11
		$this->_timeFuncList[11] = '_onTimeOut_ReqFighterXinFaInfo'; //FuncID: 12
		$this->_timeFuncList[12] = '_onTimeOut_FighterActiveXinFa'; //FuncID: 13
		$this->_timeFuncList[13] = '_onTimeOut_FighterXinFaLevelUp'; //FuncID: 14
		$this->_timeFuncList[14] = '_onTimeOut_FighterXinFaDisperse'; //FuncID: 15
		$this->_timeFuncList[15] = '_onTimeOut_GetAllFighterCombination'; //FuncID: 16
		$this->_timeFuncList[16] = '_onTimeOut_ActiveCombination'; //FuncID: 17
		$this->_timeFuncList[17] = '_onTimeOut_UpgradeCombination'; //FuncID: 18
		$this->_timeFuncList[18] = '_onTimeOut_EquipToCombinationSkill'; //FuncID: 19
		$this->_timeFuncList[19] = '_onTimeOut_FighterDismiss'; //FuncID: 20
		$this->_timeFuncList[20] = '_onTimeOut_GetFighterBuyInfo'; //FuncID: 21
		$this->_timeFuncList[21] = '_onTimeOut_FighterBuy'; //FuncID: 22
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