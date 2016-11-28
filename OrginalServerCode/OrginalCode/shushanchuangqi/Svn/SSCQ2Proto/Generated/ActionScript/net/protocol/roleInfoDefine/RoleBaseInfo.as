/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleBaseInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eRoleBaseInfo
	 */
	public final class RoleBaseInfo
	{
		public var strName:String; //玩家名字
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var wMapID:uint; //(无符号16位整数)地图ID
		public var fX:Number; //(Float)X坐标
		public var fY:Number; //(Float)Y坐标
		public var qwDgnId:BigInteger; //(无符号64位整数)副本实例ID
		public var dwDgnTypeID:uint; //(无符号16位整数)副本模版ID
		public var wDgnMapId:uint; //(无符号16位整数)副本地图ID
		public var fDgnfX:Number; //(Float)副本X坐标
		public var fDgnfY:Number; //(Float)副本Y坐标
		public var wBagMax:uint; //(无符号16位整数)背包容量
		public var wDepotMax:uint; //(无符号16位整数)仓库容量
		public var dwPendSilver:uint; //(无符号32位整数)延迟发放的银币
		public var dwPendCoupon:uint; //(无符号32位整数)延迟发放的礼券
		public var dwPendExp:uint; //(无符号32位整数)延迟发放的经验
		public var dwPendGold:uint; //(无符号32位整数)延迟发放的仙石
		public var dwDemonTowerFloorID:uint; //(无符号32位整数)通关镇妖塔层数
		public var dwDemonTowerPrizeFloorID:uint; //(无符号32位整数)镇妖塔层数
		public var strGuide:String; //新手引导内容
		public var szIcon:String; //功能开放标签
		public var szIconDel:String; //功能关闭标签
		public var szIconActive:String; //功能关闭标签
		public var dwPackNextUnlockTime:uint; //(无符号32位整数)背包下次解锁时间
		public var dwActivity:uint; //(无符号32位整数)活跃值
		public var qwSittingPlayer:BigInteger; //(无符号64位整数)一起双修的人
		public var szDgnStarAward:String; //副本星级领奖
		public var strCreateIP:String; //玩家创角时IP
		public var strLoginIP:String; //玩家登录时IP
		public var dwLuckyCoupon:uint; //(无符号32位整数)幸运券
		public var byLevel:uint; //(无符号8位整数)玩家等级
		public var qwExp:BigInteger; //(无符号64位整数)玩家经验值
		public var byNation:uint; //(无符号8位整数)国家
		public var byGMLvl:uint; //(无符号8位整数)GM权限
		public var dwTotalRecharge:uint; //(无符号32位整数)充值金额
		public var dwLoginTime:uint; //(无符号32位整数)上次登陆时间
		public var dwOfflineTime:uint; //(无符号32位整数)上次下线时间
		public var dwLockExpireTime:uint; //(无符号32位整数)被封禁结束时间
		public var dwForbExpireTime:uint; //(无符号32位整数)被禁言结束时间
		public var dwGold:uint; //(无符号32位整数)充值仙石
		public var dwFreeGold:uint; //(无符号32位整数)免费仙石
		public var dwSilver:uint; //(无符号32位整数)银币
		public var dwCoupon:uint; //(无符号32位整数)礼券
		public var dwSoul:uint; //(无符号32位整数)魂魄
		public var dwPrestige:uint; //(无符号32位整数)声望
		public var dwHonor:uint; //(无符号32位整数)荣誉
		public var dwPExp:uint; //(无符号32位整数)修为
		public var dwAction:uint; //(无符号32位整数)体力
		public var dwPoten:uint; //(无符号32位整数)渡劫点数
		public var dwReiki:uint; //(无符号32位整数)副本星级
		public var dwDemonSoul:uint; //(无符号32位整数)锁妖塔魂值
		public var dwSoulAttack:uint; //(无符号32位整数)攻击之魂
		public var dwSoulHp:uint; //(无符号32位整数)生命之魂
		public var dwSoulCritical:uint; //(无符号32位整数)暴击之魂
		public var dwSoulCounter:uint; //(无符号32位整数)破击之魂
		public var dwSoulSpeed:uint; //(无符号32位整数)身法之魂
		public var dwSoulDefence:uint; //(无符号32位整数)防御之魂
		public var dwSoulHit:uint; //(无符号32位整数)命中之魂
		public var dwSoulDodge:uint; //(无符号32位整数)闪避之魂
		public var dwStampHuang:uint; //(无符号32位整数)黄阶除魔印
		public var dwStampXuan:uint; //(无符号32位整数)玄阶除魔印
		public var dwStampDi:uint; //(无符号32位整数)地阶除魔印
		public var dwStampTian:uint; //(无符号32位整数)天阶除魔印
		public var dwStampXing:uint; //(无符号32位整数)星阶除魔印
		public var dwStampYue:uint; //(无符号32位整数)月阶除魔印
		public var dwStampDi2:uint; //(无符号32位整数)帝阶除魔印
		public var dwStampXian:uint; //(无符号32位整数)仙阶除魔印
		public var dwStampSheng:uint; //(无符号32位整数)圣阶除魔印
		public var dwStampFo:uint; //(无符号32位整数)佛阶除魔印
		public var dwLoveHeart:uint; //(无符号32位整数)爱心
		public var dwBlueFairyFate:uint; //(无符号32位整数)蓝色仙缘
		public var dwPurpleFairyFate:uint; //(无符号32位整数)紫色仙缘
		public var dwOrangeFairyFate:uint; //(无符号32位整数)橙色仙缘
		public var dwDuJieFu:uint; //(无符号32位整数)散仙渡劫符数量
		public var dwBTPoint:uint; //(无符号32位整数)战斗力
		public var szOwnTitle:String; //拥有的称号
		public var szEquipTitle:String; //装备的称号
		public var byDomain:uint; //(无符号8位整数)渠道
		public var byDomainLvl:uint; //(无符号8位整数)渠道等级
		public var byDisplayLvl:uint; //(无符号8位整数)显示等级
		public var byDomainYear:uint; //(无符号8位整数)年费
		public var szOpenId:String; //szOpenId
		public var szOpenKey:String; //szOpenKey
		public var strSign:String; //签名
		public var wMood:uint; //(无符号16位整数)心情表情
		public var wAchievementLevel:uint; //(无符号16位整数)成就等级
		public var dwAchievementAP:uint; //(无符号32位整数)成就点
		public var wCollectLevel:uint; //(无符号16位整数)收藏等级
		public var dwCollectAP:uint; //(无符号32位整数)收藏点
		public var qwInvitedID:BigInteger; //(无符号64位整数)邀请
		public var byWallow:uint; //(无符号8位整数)防沉迷
		public var dwIndulgeKickTime:uint; //(无符号32位整数)防沉迷t人时间
		public var byYDLevel:uint; //(无符号8位整数)玩家QQ黄钻等级
		public var dwCreateTime:uint; //(无符号32位整数)创角时间
		public var wLastSaveMapID:uint; //(无符号16位整数)保存地图ID
		public var fLastSaveX:Number; //(Float)保存X坐标
		public var fLastSaveY:Number; //(Float)保存Y坐标

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, eCareer:uint, eSex:uint, wMapID:uint, fX:Number, 
			fY:Number, qwDgnId:BigInteger, dwDgnTypeID:uint, wDgnMapId:uint, fDgnfX:Number, 
			fDgnfY:Number, wBagMax:uint, wDepotMax:uint, dwPendSilver:uint, dwPendCoupon:uint, 
			dwPendExp:uint, dwPendGold:uint, dwDemonTowerFloorID:uint, dwDemonTowerPrizeFloorID:uint, strGuide:String, 
			szIcon:String, szIconDel:String, szIconActive:String, dwPackNextUnlockTime:uint, dwActivity:uint, 
			qwSittingPlayer:BigInteger, szDgnStarAward:String, strCreateIP:String, strLoginIP:String, dwLuckyCoupon:uint, 
			byLevel:uint, qwExp:BigInteger, byNation:uint, byGMLvl:uint, dwTotalRecharge:uint, 
			dwLoginTime:uint, dwOfflineTime:uint, dwLockExpireTime:uint, dwForbExpireTime:uint, dwGold:uint, 
			dwFreeGold:uint, dwSilver:uint, dwCoupon:uint, dwSoul:uint, dwPrestige:uint, 
			dwHonor:uint, dwPExp:uint, dwAction:uint, dwPoten:uint, dwReiki:uint, 
			dwDemonSoul:uint, dwSoulAttack:uint, dwSoulHp:uint, dwSoulCritical:uint, dwSoulCounter:uint, 
			dwSoulSpeed:uint, dwSoulDefence:uint, dwSoulHit:uint, dwSoulDodge:uint, dwStampHuang:uint, 
			dwStampXuan:uint, dwStampDi:uint, dwStampTian:uint, dwStampXing:uint, dwStampYue:uint, 
			dwStampDi2:uint, dwStampXian:uint, dwStampSheng:uint, dwStampFo:uint, dwLoveHeart:uint, 
			dwBlueFairyFate:uint, dwPurpleFairyFate:uint, dwOrangeFairyFate:uint, dwDuJieFu:uint, dwBTPoint:uint, 
			szOwnTitle:String, szEquipTitle:String, byDomain:uint, byDomainLvl:uint, byDisplayLvl:uint, 
			byDomainYear:uint, szOpenId:String, szOpenKey:String, strSign:String, wMood:uint, 
			wAchievementLevel:uint, dwAchievementAP:uint, wCollectLevel:uint, dwCollectAP:uint, qwInvitedID:BigInteger, 
			byWallow:uint, dwIndulgeKickTime:uint, byYDLevel:uint, dwCreateTime:uint, wLastSaveMapID:uint, 
			fLastSaveX:Number, fLastSaveY:Number):RoleBaseInfo
		{
			var s_:RoleBaseInfo = new RoleBaseInfo();
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.wMapID = wMapID;
			s_.fX = fX;
			s_.fY = fY;
			s_.qwDgnId = qwDgnId;
			s_.dwDgnTypeID = dwDgnTypeID;
			s_.wDgnMapId = wDgnMapId;
			s_.fDgnfX = fDgnfX;
			s_.fDgnfY = fDgnfY;
			s_.wBagMax = wBagMax;
			s_.wDepotMax = wDepotMax;
			s_.dwPendSilver = dwPendSilver;
			s_.dwPendCoupon = dwPendCoupon;
			s_.dwPendExp = dwPendExp;
			s_.dwPendGold = dwPendGold;
			s_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			s_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			s_.strGuide = strGuide;
			s_.szIcon = szIcon;
			s_.szIconDel = szIconDel;
			s_.szIconActive = szIconActive;
			s_.dwPackNextUnlockTime = dwPackNextUnlockTime;
			s_.dwActivity = dwActivity;
			s_.qwSittingPlayer = qwSittingPlayer;
			s_.szDgnStarAward = szDgnStarAward;
			s_.strCreateIP = strCreateIP;
			s_.strLoginIP = strLoginIP;
			s_.dwLuckyCoupon = dwLuckyCoupon;
			s_.byLevel = byLevel;
			s_.qwExp = qwExp;
			s_.byNation = byNation;
			s_.byGMLvl = byGMLvl;
			s_.dwTotalRecharge = dwTotalRecharge;
			s_.dwLoginTime = dwLoginTime;
			s_.dwOfflineTime = dwOfflineTime;
			s_.dwLockExpireTime = dwLockExpireTime;
			s_.dwForbExpireTime = dwForbExpireTime;
			s_.dwGold = dwGold;
			s_.dwFreeGold = dwFreeGold;
			s_.dwSilver = dwSilver;
			s_.dwCoupon = dwCoupon;
			s_.dwSoul = dwSoul;
			s_.dwPrestige = dwPrestige;
			s_.dwHonor = dwHonor;
			s_.dwPExp = dwPExp;
			s_.dwAction = dwAction;
			s_.dwPoten = dwPoten;
			s_.dwReiki = dwReiki;
			s_.dwDemonSoul = dwDemonSoul;
			s_.dwSoulAttack = dwSoulAttack;
			s_.dwSoulHp = dwSoulHp;
			s_.dwSoulCritical = dwSoulCritical;
			s_.dwSoulCounter = dwSoulCounter;
			s_.dwSoulSpeed = dwSoulSpeed;
			s_.dwSoulDefence = dwSoulDefence;
			s_.dwSoulHit = dwSoulHit;
			s_.dwSoulDodge = dwSoulDodge;
			s_.dwStampHuang = dwStampHuang;
			s_.dwStampXuan = dwStampXuan;
			s_.dwStampDi = dwStampDi;
			s_.dwStampTian = dwStampTian;
			s_.dwStampXing = dwStampXing;
			s_.dwStampYue = dwStampYue;
			s_.dwStampDi2 = dwStampDi2;
			s_.dwStampXian = dwStampXian;
			s_.dwStampSheng = dwStampSheng;
			s_.dwStampFo = dwStampFo;
			s_.dwLoveHeart = dwLoveHeart;
			s_.dwBlueFairyFate = dwBlueFairyFate;
			s_.dwPurpleFairyFate = dwPurpleFairyFate;
			s_.dwOrangeFairyFate = dwOrangeFairyFate;
			s_.dwDuJieFu = dwDuJieFu;
			s_.dwBTPoint = dwBTPoint;
			s_.szOwnTitle = szOwnTitle;
			s_.szEquipTitle = szEquipTitle;
			s_.byDomain = byDomain;
			s_.byDomainLvl = byDomainLvl;
			s_.byDisplayLvl = byDisplayLvl;
			s_.byDomainYear = byDomainYear;
			s_.szOpenId = szOpenId;
			s_.szOpenKey = szOpenKey;
			s_.strSign = strSign;
			s_.wMood = wMood;
			s_.wAchievementLevel = wAchievementLevel;
			s_.dwAchievementAP = dwAchievementAP;
			s_.wCollectLevel = wCollectLevel;
			s_.dwCollectAP = dwCollectAP;
			s_.qwInvitedID = qwInvitedID;
			s_.byWallow = byWallow;
			s_.dwIndulgeKickTime = dwIndulgeKickTime;
			s_.byYDLevel = byYDLevel;
			s_.dwCreateTime = dwCreateTime;
			s_.wLastSaveMapID = wLastSaveMapID;
			s_.fLastSaveX = fLastSaveX;
			s_.fLastSaveY = fLastSaveY;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <RoleBaseInfo _name_={name_} strName={strName} eCareer={eCareer} eSex={eSex} wMapID={wMapID} fX={fX}
				 fY={fY} qwDgnId={qwDgnId} dwDgnTypeID={dwDgnTypeID} wDgnMapId={wDgnMapId} fDgnfX={fDgnfX}
				 fDgnfY={fDgnfY} wBagMax={wBagMax} wDepotMax={wDepotMax} dwPendSilver={dwPendSilver} dwPendCoupon={dwPendCoupon}
				 dwPendExp={dwPendExp} dwPendGold={dwPendGold} dwDemonTowerFloorID={dwDemonTowerFloorID} dwDemonTowerPrizeFloorID={dwDemonTowerPrizeFloorID} strGuide={strGuide}
				 szIcon={szIcon} szIconDel={szIconDel} szIconActive={szIconActive} dwPackNextUnlockTime={dwPackNextUnlockTime} dwActivity={dwActivity}
				 qwSittingPlayer={qwSittingPlayer} szDgnStarAward={szDgnStarAward} strCreateIP={strCreateIP} strLoginIP={strLoginIP} dwLuckyCoupon={dwLuckyCoupon}
				 byLevel={byLevel} qwExp={qwExp} byNation={byNation} byGMLvl={byGMLvl} dwTotalRecharge={dwTotalRecharge}
				 dwLoginTime={dwLoginTime} dwOfflineTime={dwOfflineTime} dwLockExpireTime={dwLockExpireTime} dwForbExpireTime={dwForbExpireTime} dwGold={dwGold}
				 dwFreeGold={dwFreeGold} dwSilver={dwSilver} dwCoupon={dwCoupon} dwSoul={dwSoul} dwPrestige={dwPrestige}
				 dwHonor={dwHonor} dwPExp={dwPExp} dwAction={dwAction} dwPoten={dwPoten} dwReiki={dwReiki}
				 dwDemonSoul={dwDemonSoul} dwSoulAttack={dwSoulAttack} dwSoulHp={dwSoulHp} dwSoulCritical={dwSoulCritical} dwSoulCounter={dwSoulCounter}
				 dwSoulSpeed={dwSoulSpeed} dwSoulDefence={dwSoulDefence} dwSoulHit={dwSoulHit} dwSoulDodge={dwSoulDodge} dwStampHuang={dwStampHuang}
				 dwStampXuan={dwStampXuan} dwStampDi={dwStampDi} dwStampTian={dwStampTian} dwStampXing={dwStampXing} dwStampYue={dwStampYue}
				 dwStampDi2={dwStampDi2} dwStampXian={dwStampXian} dwStampSheng={dwStampSheng} dwStampFo={dwStampFo} dwLoveHeart={dwLoveHeart}
				 dwBlueFairyFate={dwBlueFairyFate} dwPurpleFairyFate={dwPurpleFairyFate} dwOrangeFairyFate={dwOrangeFairyFate} dwDuJieFu={dwDuJieFu} dwBTPoint={dwBTPoint}
				 szOwnTitle={szOwnTitle} szEquipTitle={szEquipTitle} byDomain={byDomain} byDomainLvl={byDomainLvl} byDisplayLvl={byDisplayLvl}
				 byDomainYear={byDomainYear} szOpenId={szOpenId} szOpenKey={szOpenKey} strSign={strSign} wMood={wMood}
				 wAchievementLevel={wAchievementLevel} dwAchievementAP={dwAchievementAP} wCollectLevel={wCollectLevel} dwCollectAP={dwCollectAP} qwInvitedID={qwInvitedID}
				 byWallow={byWallow} dwIndulgeKickTime={dwIndulgeKickTime} byYDLevel={byYDLevel} dwCreateTime={dwCreateTime} wLastSaveMapID={wLastSaveMapID}
				 fLastSaveX={fLastSaveX} fLastSaveY={fLastSaveY}/>;
			else
				topXml = <RoleBaseInfo strName={strName} eCareer={eCareer} eSex={eSex} wMapID={wMapID} fX={fX}
				 fY={fY} qwDgnId={qwDgnId} dwDgnTypeID={dwDgnTypeID} wDgnMapId={wDgnMapId} fDgnfX={fDgnfX}
				 fDgnfY={fDgnfY} wBagMax={wBagMax} wDepotMax={wDepotMax} dwPendSilver={dwPendSilver} dwPendCoupon={dwPendCoupon}
				 dwPendExp={dwPendExp} dwPendGold={dwPendGold} dwDemonTowerFloorID={dwDemonTowerFloorID} dwDemonTowerPrizeFloorID={dwDemonTowerPrizeFloorID} strGuide={strGuide}
				 szIcon={szIcon} szIconDel={szIconDel} szIconActive={szIconActive} dwPackNextUnlockTime={dwPackNextUnlockTime} dwActivity={dwActivity}
				 qwSittingPlayer={qwSittingPlayer} szDgnStarAward={szDgnStarAward} strCreateIP={strCreateIP} strLoginIP={strLoginIP} dwLuckyCoupon={dwLuckyCoupon}
				 byLevel={byLevel} qwExp={qwExp} byNation={byNation} byGMLvl={byGMLvl} dwTotalRecharge={dwTotalRecharge}
				 dwLoginTime={dwLoginTime} dwOfflineTime={dwOfflineTime} dwLockExpireTime={dwLockExpireTime} dwForbExpireTime={dwForbExpireTime} dwGold={dwGold}
				 dwFreeGold={dwFreeGold} dwSilver={dwSilver} dwCoupon={dwCoupon} dwSoul={dwSoul} dwPrestige={dwPrestige}
				 dwHonor={dwHonor} dwPExp={dwPExp} dwAction={dwAction} dwPoten={dwPoten} dwReiki={dwReiki}
				 dwDemonSoul={dwDemonSoul} dwSoulAttack={dwSoulAttack} dwSoulHp={dwSoulHp} dwSoulCritical={dwSoulCritical} dwSoulCounter={dwSoulCounter}
				 dwSoulSpeed={dwSoulSpeed} dwSoulDefence={dwSoulDefence} dwSoulHit={dwSoulHit} dwSoulDodge={dwSoulDodge} dwStampHuang={dwStampHuang}
				 dwStampXuan={dwStampXuan} dwStampDi={dwStampDi} dwStampTian={dwStampTian} dwStampXing={dwStampXing} dwStampYue={dwStampYue}
				 dwStampDi2={dwStampDi2} dwStampXian={dwStampXian} dwStampSheng={dwStampSheng} dwStampFo={dwStampFo} dwLoveHeart={dwLoveHeart}
				 dwBlueFairyFate={dwBlueFairyFate} dwPurpleFairyFate={dwPurpleFairyFate} dwOrangeFairyFate={dwOrangeFairyFate} dwDuJieFu={dwDuJieFu} dwBTPoint={dwBTPoint}
				 szOwnTitle={szOwnTitle} szEquipTitle={szEquipTitle} byDomain={byDomain} byDomainLvl={byDomainLvl} byDisplayLvl={byDisplayLvl}
				 byDomainYear={byDomainYear} szOpenId={szOpenId} szOpenKey={szOpenKey} strSign={strSign} wMood={wMood}
				 wAchievementLevel={wAchievementLevel} dwAchievementAP={dwAchievementAP} wCollectLevel={wCollectLevel} dwCollectAP={dwCollectAP} qwInvitedID={qwInvitedID}
				 byWallow={byWallow} dwIndulgeKickTime={dwIndulgeKickTime} byYDLevel={byYDLevel} dwCreateTime={dwCreateTime} wLastSaveMapID={wLastSaveMapID}
				 fLastSaveX={fLastSaveX} fLastSaveY={fLastSaveY}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.eCareer = eCareer;
			obj_.eSex = eSex;
			obj_.wMapID = wMapID;
			obj_.fX = fX;
			obj_.fY = fY;
			obj_.qwDgnId = qwDgnId;
			obj_.dwDgnTypeID = dwDgnTypeID;
			obj_.wDgnMapId = wDgnMapId;
			obj_.fDgnfX = fDgnfX;
			obj_.fDgnfY = fDgnfY;
			obj_.wBagMax = wBagMax;
			obj_.wDepotMax = wDepotMax;
			obj_.dwPendSilver = dwPendSilver;
			obj_.dwPendCoupon = dwPendCoupon;
			obj_.dwPendExp = dwPendExp;
			obj_.dwPendGold = dwPendGold;
			obj_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			obj_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			obj_.strGuide = strGuide;
			obj_.szIcon = szIcon;
			obj_.szIconDel = szIconDel;
			obj_.szIconActive = szIconActive;
			obj_.dwPackNextUnlockTime = dwPackNextUnlockTime;
			obj_.dwActivity = dwActivity;
			obj_.qwSittingPlayer = qwSittingPlayer;
			obj_.szDgnStarAward = szDgnStarAward;
			obj_.strCreateIP = strCreateIP;
			obj_.strLoginIP = strLoginIP;
			obj_.dwLuckyCoupon = dwLuckyCoupon;
			obj_.byLevel = byLevel;
			obj_.qwExp = qwExp;
			obj_.byNation = byNation;
			obj_.byGMLvl = byGMLvl;
			obj_.dwTotalRecharge = dwTotalRecharge;
			obj_.dwLoginTime = dwLoginTime;
			obj_.dwOfflineTime = dwOfflineTime;
			obj_.dwLockExpireTime = dwLockExpireTime;
			obj_.dwForbExpireTime = dwForbExpireTime;
			obj_.dwGold = dwGold;
			obj_.dwFreeGold = dwFreeGold;
			obj_.dwSilver = dwSilver;
			obj_.dwCoupon = dwCoupon;
			obj_.dwSoul = dwSoul;
			obj_.dwPrestige = dwPrestige;
			obj_.dwHonor = dwHonor;
			obj_.dwPExp = dwPExp;
			obj_.dwAction = dwAction;
			obj_.dwPoten = dwPoten;
			obj_.dwReiki = dwReiki;
			obj_.dwDemonSoul = dwDemonSoul;
			obj_.dwSoulAttack = dwSoulAttack;
			obj_.dwSoulHp = dwSoulHp;
			obj_.dwSoulCritical = dwSoulCritical;
			obj_.dwSoulCounter = dwSoulCounter;
			obj_.dwSoulSpeed = dwSoulSpeed;
			obj_.dwSoulDefence = dwSoulDefence;
			obj_.dwSoulHit = dwSoulHit;
			obj_.dwSoulDodge = dwSoulDodge;
			obj_.dwStampHuang = dwStampHuang;
			obj_.dwStampXuan = dwStampXuan;
			obj_.dwStampDi = dwStampDi;
			obj_.dwStampTian = dwStampTian;
			obj_.dwStampXing = dwStampXing;
			obj_.dwStampYue = dwStampYue;
			obj_.dwStampDi2 = dwStampDi2;
			obj_.dwStampXian = dwStampXian;
			obj_.dwStampSheng = dwStampSheng;
			obj_.dwStampFo = dwStampFo;
			obj_.dwLoveHeart = dwLoveHeart;
			obj_.dwBlueFairyFate = dwBlueFairyFate;
			obj_.dwPurpleFairyFate = dwPurpleFairyFate;
			obj_.dwOrangeFairyFate = dwOrangeFairyFate;
			obj_.dwDuJieFu = dwDuJieFu;
			obj_.dwBTPoint = dwBTPoint;
			obj_.szOwnTitle = szOwnTitle;
			obj_.szEquipTitle = szEquipTitle;
			obj_.byDomain = byDomain;
			obj_.byDomainLvl = byDomainLvl;
			obj_.byDisplayLvl = byDisplayLvl;
			obj_.byDomainYear = byDomainYear;
			obj_.szOpenId = szOpenId;
			obj_.szOpenKey = szOpenKey;
			obj_.strSign = strSign;
			obj_.wMood = wMood;
			obj_.wAchievementLevel = wAchievementLevel;
			obj_.dwAchievementAP = dwAchievementAP;
			obj_.wCollectLevel = wCollectLevel;
			obj_.dwCollectAP = dwCollectAP;
			obj_.qwInvitedID = qwInvitedID;
			obj_.byWallow = byWallow;
			obj_.dwIndulgeKickTime = dwIndulgeKickTime;
			obj_.byYDLevel = byYDLevel;
			obj_.dwCreateTime = dwCreateTime;
			obj_.wLastSaveMapID = wLastSaveMapID;
			obj_.fLastSaveX = fLastSaveX;
			obj_.fLastSaveY = fLastSaveY;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleBaseInfo
		{
			var s_:RoleBaseInfo = new RoleBaseInfo();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var wMapID:uint = bytes.readUnsignedShort();
			s_.wMapID = wMapID;
			var fX:Number = bytes.readFloat();
			s_.fX = fX;
			var fY:Number = bytes.readFloat();
			s_.fY = fY;
			var qwDgnId:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwDgnId = qwDgnId;
			var dwDgnTypeID:uint = bytes.readUnsignedShort();
			s_.dwDgnTypeID = dwDgnTypeID;
			var wDgnMapId:uint = bytes.readUnsignedShort();
			s_.wDgnMapId = wDgnMapId;
			var fDgnfX:Number = bytes.readFloat();
			s_.fDgnfX = fDgnfX;
			var fDgnfY:Number = bytes.readFloat();
			s_.fDgnfY = fDgnfY;
			var wBagMax:uint = bytes.readUnsignedShort();
			s_.wBagMax = wBagMax;
			var wDepotMax:uint = bytes.readUnsignedShort();
			s_.wDepotMax = wDepotMax;
			var dwPendSilver:uint = bytes.readUnsignedInt();
			s_.dwPendSilver = dwPendSilver;
			var dwPendCoupon:uint = bytes.readUnsignedInt();
			s_.dwPendCoupon = dwPendCoupon;
			var dwPendExp:uint = bytes.readUnsignedInt();
			s_.dwPendExp = dwPendExp;
			var dwPendGold:uint = bytes.readUnsignedInt();
			s_.dwPendGold = dwPendGold;
			var dwDemonTowerFloorID:uint = bytes.readUnsignedInt();
			s_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			var dwDemonTowerPrizeFloorID:uint = bytes.readUnsignedInt();
			s_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			var strGuide:String = BytesUtil.readString(bytes);
			s_.strGuide = strGuide;
			var szIcon:String = BytesUtil.readString(bytes);
			s_.szIcon = szIcon;
			var szIconDel:String = BytesUtil.readString(bytes);
			s_.szIconDel = szIconDel;
			var szIconActive:String = BytesUtil.readString(bytes);
			s_.szIconActive = szIconActive;
			var dwPackNextUnlockTime:uint = bytes.readUnsignedInt();
			s_.dwPackNextUnlockTime = dwPackNextUnlockTime;
			var dwActivity:uint = bytes.readUnsignedInt();
			s_.dwActivity = dwActivity;
			var qwSittingPlayer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwSittingPlayer = qwSittingPlayer;
			var szDgnStarAward:String = BytesUtil.readString(bytes);
			s_.szDgnStarAward = szDgnStarAward;
			var strCreateIP:String = BytesUtil.readString(bytes);
			s_.strCreateIP = strCreateIP;
			var strLoginIP:String = BytesUtil.readString(bytes);
			s_.strLoginIP = strLoginIP;
			var dwLuckyCoupon:uint = bytes.readUnsignedInt();
			s_.dwLuckyCoupon = dwLuckyCoupon;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var qwExp:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwExp = qwExp;
			var byNation:uint = bytes.readUnsignedByte();
			s_.byNation = byNation;
			var byGMLvl:uint = bytes.readUnsignedByte();
			s_.byGMLvl = byGMLvl;
			var dwTotalRecharge:uint = bytes.readUnsignedInt();
			s_.dwTotalRecharge = dwTotalRecharge;
			var dwLoginTime:uint = bytes.readUnsignedInt();
			s_.dwLoginTime = dwLoginTime;
			var dwOfflineTime:uint = bytes.readUnsignedInt();
			s_.dwOfflineTime = dwOfflineTime;
			var dwLockExpireTime:uint = bytes.readUnsignedInt();
			s_.dwLockExpireTime = dwLockExpireTime;
			var dwForbExpireTime:uint = bytes.readUnsignedInt();
			s_.dwForbExpireTime = dwForbExpireTime;
			var dwGold:uint = bytes.readUnsignedInt();
			s_.dwGold = dwGold;
			var dwFreeGold:uint = bytes.readUnsignedInt();
			s_.dwFreeGold = dwFreeGold;
			var dwSilver:uint = bytes.readUnsignedInt();
			s_.dwSilver = dwSilver;
			var dwCoupon:uint = bytes.readUnsignedInt();
			s_.dwCoupon = dwCoupon;
			var dwSoul:uint = bytes.readUnsignedInt();
			s_.dwSoul = dwSoul;
			var dwPrestige:uint = bytes.readUnsignedInt();
			s_.dwPrestige = dwPrestige;
			var dwHonor:uint = bytes.readUnsignedInt();
			s_.dwHonor = dwHonor;
			var dwPExp:uint = bytes.readUnsignedInt();
			s_.dwPExp = dwPExp;
			var dwAction:uint = bytes.readUnsignedInt();
			s_.dwAction = dwAction;
			var dwPoten:uint = bytes.readUnsignedInt();
			s_.dwPoten = dwPoten;
			var dwReiki:uint = bytes.readUnsignedInt();
			s_.dwReiki = dwReiki;
			var dwDemonSoul:uint = bytes.readUnsignedInt();
			s_.dwDemonSoul = dwDemonSoul;
			var dwSoulAttack:uint = bytes.readUnsignedInt();
			s_.dwSoulAttack = dwSoulAttack;
			var dwSoulHp:uint = bytes.readUnsignedInt();
			s_.dwSoulHp = dwSoulHp;
			var dwSoulCritical:uint = bytes.readUnsignedInt();
			s_.dwSoulCritical = dwSoulCritical;
			var dwSoulCounter:uint = bytes.readUnsignedInt();
			s_.dwSoulCounter = dwSoulCounter;
			var dwSoulSpeed:uint = bytes.readUnsignedInt();
			s_.dwSoulSpeed = dwSoulSpeed;
			var dwSoulDefence:uint = bytes.readUnsignedInt();
			s_.dwSoulDefence = dwSoulDefence;
			var dwSoulHit:uint = bytes.readUnsignedInt();
			s_.dwSoulHit = dwSoulHit;
			var dwSoulDodge:uint = bytes.readUnsignedInt();
			s_.dwSoulDodge = dwSoulDodge;
			var dwStampHuang:uint = bytes.readUnsignedInt();
			s_.dwStampHuang = dwStampHuang;
			var dwStampXuan:uint = bytes.readUnsignedInt();
			s_.dwStampXuan = dwStampXuan;
			var dwStampDi:uint = bytes.readUnsignedInt();
			s_.dwStampDi = dwStampDi;
			var dwStampTian:uint = bytes.readUnsignedInt();
			s_.dwStampTian = dwStampTian;
			var dwStampXing:uint = bytes.readUnsignedInt();
			s_.dwStampXing = dwStampXing;
			var dwStampYue:uint = bytes.readUnsignedInt();
			s_.dwStampYue = dwStampYue;
			var dwStampDi2:uint = bytes.readUnsignedInt();
			s_.dwStampDi2 = dwStampDi2;
			var dwStampXian:uint = bytes.readUnsignedInt();
			s_.dwStampXian = dwStampXian;
			var dwStampSheng:uint = bytes.readUnsignedInt();
			s_.dwStampSheng = dwStampSheng;
			var dwStampFo:uint = bytes.readUnsignedInt();
			s_.dwStampFo = dwStampFo;
			var dwLoveHeart:uint = bytes.readUnsignedInt();
			s_.dwLoveHeart = dwLoveHeart;
			var dwBlueFairyFate:uint = bytes.readUnsignedInt();
			s_.dwBlueFairyFate = dwBlueFairyFate;
			var dwPurpleFairyFate:uint = bytes.readUnsignedInt();
			s_.dwPurpleFairyFate = dwPurpleFairyFate;
			var dwOrangeFairyFate:uint = bytes.readUnsignedInt();
			s_.dwOrangeFairyFate = dwOrangeFairyFate;
			var dwDuJieFu:uint = bytes.readUnsignedInt();
			s_.dwDuJieFu = dwDuJieFu;
			var dwBTPoint:uint = bytes.readUnsignedInt();
			s_.dwBTPoint = dwBTPoint;
			var szOwnTitle:String = BytesUtil.readString(bytes);
			s_.szOwnTitle = szOwnTitle;
			var szEquipTitle:String = BytesUtil.readString(bytes);
			s_.szEquipTitle = szEquipTitle;
			var byDomain:uint = bytes.readUnsignedByte();
			s_.byDomain = byDomain;
			var byDomainLvl:uint = bytes.readUnsignedByte();
			s_.byDomainLvl = byDomainLvl;
			var byDisplayLvl:uint = bytes.readUnsignedByte();
			s_.byDisplayLvl = byDisplayLvl;
			var byDomainYear:uint = bytes.readUnsignedByte();
			s_.byDomainYear = byDomainYear;
			var szOpenId:String = BytesUtil.readString(bytes);
			s_.szOpenId = szOpenId;
			var szOpenKey:String = BytesUtil.readString(bytes);
			s_.szOpenKey = szOpenKey;
			var strSign:String = BytesUtil.readString(bytes);
			s_.strSign = strSign;
			var wMood:uint = bytes.readUnsignedShort();
			s_.wMood = wMood;
			var wAchievementLevel:uint = bytes.readUnsignedShort();
			s_.wAchievementLevel = wAchievementLevel;
			var dwAchievementAP:uint = bytes.readUnsignedInt();
			s_.dwAchievementAP = dwAchievementAP;
			var wCollectLevel:uint = bytes.readUnsignedShort();
			s_.wCollectLevel = wCollectLevel;
			var dwCollectAP:uint = bytes.readUnsignedInt();
			s_.dwCollectAP = dwCollectAP;
			var qwInvitedID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInvitedID = qwInvitedID;
			var byWallow:uint = bytes.readUnsignedByte();
			s_.byWallow = byWallow;
			var dwIndulgeKickTime:uint = bytes.readUnsignedInt();
			s_.dwIndulgeKickTime = dwIndulgeKickTime;
			var byYDLevel:uint = bytes.readUnsignedByte();
			s_.byYDLevel = byYDLevel;
			var dwCreateTime:uint = bytes.readUnsignedInt();
			s_.dwCreateTime = dwCreateTime;
			var wLastSaveMapID:uint = bytes.readUnsignedShort();
			s_.wLastSaveMapID = wLastSaveMapID;
			var fLastSaveX:Number = bytes.readFloat();
			s_.fLastSaveX = fLastSaveX;
			var fLastSaveY:Number = bytes.readFloat();
			s_.fLastSaveY = fLastSaveY;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleBaseInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleBaseInfo> = new Vector.<RoleBaseInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleBaseInfo = RoleBaseInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			bytes.writeShort(wMapID);
			bytes.writeFloat(fX);
			bytes.writeFloat(fY);
			BytesUtil.writeUInt64(bytes, qwDgnId);
			bytes.writeShort(dwDgnTypeID);
			bytes.writeShort(wDgnMapId);
			bytes.writeFloat(fDgnfX);
			bytes.writeFloat(fDgnfY);
			bytes.writeShort(wBagMax);
			bytes.writeShort(wDepotMax);
			bytes.writeUnsignedInt(dwPendSilver);
			bytes.writeUnsignedInt(dwPendCoupon);
			bytes.writeUnsignedInt(dwPendExp);
			bytes.writeUnsignedInt(dwPendGold);
			bytes.writeUnsignedInt(dwDemonTowerFloorID);
			bytes.writeUnsignedInt(dwDemonTowerPrizeFloorID);
			BytesUtil.writeString(bytes, strGuide);
			BytesUtil.writeString(bytes, szIcon);
			BytesUtil.writeString(bytes, szIconDel);
			BytesUtil.writeString(bytes, szIconActive);
			bytes.writeUnsignedInt(dwPackNextUnlockTime);
			bytes.writeUnsignedInt(dwActivity);
			BytesUtil.writeUInt64(bytes, qwSittingPlayer);
			BytesUtil.writeString(bytes, szDgnStarAward);
			BytesUtil.writeString(bytes, strCreateIP);
			BytesUtil.writeString(bytes, strLoginIP);
			bytes.writeUnsignedInt(dwLuckyCoupon);
			bytes.writeByte(byLevel);
			BytesUtil.writeUInt64(bytes, qwExp);
			bytes.writeByte(byNation);
			bytes.writeByte(byGMLvl);
			bytes.writeUnsignedInt(dwTotalRecharge);
			bytes.writeUnsignedInt(dwLoginTime);
			bytes.writeUnsignedInt(dwOfflineTime);
			bytes.writeUnsignedInt(dwLockExpireTime);
			bytes.writeUnsignedInt(dwForbExpireTime);
			bytes.writeUnsignedInt(dwGold);
			bytes.writeUnsignedInt(dwFreeGold);
			bytes.writeUnsignedInt(dwSilver);
			bytes.writeUnsignedInt(dwCoupon);
			bytes.writeUnsignedInt(dwSoul);
			bytes.writeUnsignedInt(dwPrestige);
			bytes.writeUnsignedInt(dwHonor);
			bytes.writeUnsignedInt(dwPExp);
			bytes.writeUnsignedInt(dwAction);
			bytes.writeUnsignedInt(dwPoten);
			bytes.writeUnsignedInt(dwReiki);
			bytes.writeUnsignedInt(dwDemonSoul);
			bytes.writeUnsignedInt(dwSoulAttack);
			bytes.writeUnsignedInt(dwSoulHp);
			bytes.writeUnsignedInt(dwSoulCritical);
			bytes.writeUnsignedInt(dwSoulCounter);
			bytes.writeUnsignedInt(dwSoulSpeed);
			bytes.writeUnsignedInt(dwSoulDefence);
			bytes.writeUnsignedInt(dwSoulHit);
			bytes.writeUnsignedInt(dwSoulDodge);
			bytes.writeUnsignedInt(dwStampHuang);
			bytes.writeUnsignedInt(dwStampXuan);
			bytes.writeUnsignedInt(dwStampDi);
			bytes.writeUnsignedInt(dwStampTian);
			bytes.writeUnsignedInt(dwStampXing);
			bytes.writeUnsignedInt(dwStampYue);
			bytes.writeUnsignedInt(dwStampDi2);
			bytes.writeUnsignedInt(dwStampXian);
			bytes.writeUnsignedInt(dwStampSheng);
			bytes.writeUnsignedInt(dwStampFo);
			bytes.writeUnsignedInt(dwLoveHeart);
			bytes.writeUnsignedInt(dwBlueFairyFate);
			bytes.writeUnsignedInt(dwPurpleFairyFate);
			bytes.writeUnsignedInt(dwOrangeFairyFate);
			bytes.writeUnsignedInt(dwDuJieFu);
			bytes.writeUnsignedInt(dwBTPoint);
			BytesUtil.writeString(bytes, szOwnTitle);
			BytesUtil.writeString(bytes, szEquipTitle);
			bytes.writeByte(byDomain);
			bytes.writeByte(byDomainLvl);
			bytes.writeByte(byDisplayLvl);
			bytes.writeByte(byDomainYear);
			BytesUtil.writeString(bytes, szOpenId);
			BytesUtil.writeString(bytes, szOpenKey);
			BytesUtil.writeString(bytes, strSign);
			bytes.writeShort(wMood);
			bytes.writeShort(wAchievementLevel);
			bytes.writeUnsignedInt(dwAchievementAP);
			bytes.writeShort(wCollectLevel);
			bytes.writeUnsignedInt(dwCollectAP);
			BytesUtil.writeUInt64(bytes, qwInvitedID);
			bytes.writeByte(byWallow);
			bytes.writeUnsignedInt(dwIndulgeKickTime);
			bytes.writeByte(byYDLevel);
			bytes.writeUnsignedInt(dwCreateTime);
			bytes.writeShort(wLastSaveMapID);
			bytes.writeFloat(fLastSaveX);
			bytes.writeFloat(fLastSaveY);
		}

		public static function vectorToByteArray(vec:Vector.<RoleBaseInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleBaseInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
