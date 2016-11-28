/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerBaseData.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 查询基础消息
	 */
	public final class PlayerBaseData
	{
		public var strName:String; //玩家名字
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byLevel:uint; //(无符号8位整数)玩家等级
		public var qwExp:BigInteger; //(无符号64位整数)玩家经验值
		public var wBagMax:uint; //(无符号16位整数)背包容量
		public var wDepotMax:uint; //(无符号16位整数)仓库容量
		public var byNation:uint; //(无符号8位整数)国家
		public var dwGold:uint; //(无符号32位整数)仙石
		public var dwSilver:uint; //(无符号32位整数)银币
		public var dwCoupon:uint; //(无符号32位整数)礼券
		public var dwSoul:uint; //(无符号32位整数)魂魄
		public var dwPrestige:uint; //(无符号32位整数)声望
		public var dwHonor:uint; //(无符号32位整数)荣誉
		public var dwPExp:uint; //(无符号32位整数)修为
		public var dwSigil:uint; //(无符号32位整数)符印
		public var dwCentsY:uint; //(无符号32位整数)仙元
		public var dwAction:uint; //(无符号32位整数)体力
		public var dwSop:uint; //(无符号32位整数)阅历
		public var dwPoten:uint; //(无符号32位整数)潜能
		public var dwReiki:uint; //(无符号32位整数)灵力
		public var dwDemonSoul:uint; //(无符号32位整数)锁妖塔魂值
		public var dwSoulAttack:uint; //(无符号32位整数)攻击之魂
		public var dwSoulHp:uint; //(无符号32位整数)生命之魂
		public var dwSoulCritical:uint; //(无符号32位整数)暴击之魂
		public var dwSoulCounter:uint; //(无符号32位整数)反击之魂
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
		public var dwBTPoint:uint; //(无符号32位整数)战斗力
		public var dwBlueFairyFate:uint; //(无符号32位整数)蓝色仙缘
		public var dwPurpleFairyFate:uint; //(无符号32位整数)紫色仙缘
		public var dwOrangeFairyFate:uint; //(无符号32位整数)橙色仙缘
		public var dwTotalRecharge:uint; //(无符号32位整数)总充值数
		public var vecOwnTitle:Vector.<uint>; //(无符号16位整数)拥有称号
		public var vecEquipTitle:Vector.<uint>; //(无符号16位整数)装备称号
		public var strGuide:String; //新手引导信息
		public var byWallow:uint; //(无符号8位整数)防沉迷
		public var vecIconAppear:Vector.<uint>; //(无符号16位整数)Icon开启
		public var vecIconDel:Vector.<uint>; //(无符号16位整数)Icon关闭
		public var dwDemonTowerFloorID:uint; //(无符号32位整数)通关镇妖塔层数
		public var dwDemonTowerPrizeFloorID:uint; //(无符号32位整数)镇妖塔领奖层数
		public var dwCreateTime:uint; //(无符号32位整数)玩家创角时间

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, eCareer:uint, eSex:uint, byLevel:uint, qwExp:BigInteger, 
			wBagMax:uint, wDepotMax:uint, byNation:uint, dwGold:uint, dwSilver:uint, 
			dwCoupon:uint, dwSoul:uint, dwPrestige:uint, dwHonor:uint, dwPExp:uint, 
			dwSigil:uint, dwCentsY:uint, dwAction:uint, dwSop:uint, dwPoten:uint, 
			dwReiki:uint, dwDemonSoul:uint, dwSoulAttack:uint, dwSoulHp:uint, dwSoulCritical:uint, 
			dwSoulCounter:uint, dwSoulSpeed:uint, dwSoulDefence:uint, dwSoulHit:uint, dwSoulDodge:uint, 
			dwStampHuang:uint, dwStampXuan:uint, dwStampDi:uint, dwStampTian:uint, dwStampXing:uint, 
			dwStampYue:uint, dwStampDi2:uint, dwStampXian:uint, dwStampSheng:uint, dwStampFo:uint, 
			dwBTPoint:uint, dwBlueFairyFate:uint, dwPurpleFairyFate:uint, dwOrangeFairyFate:uint, dwTotalRecharge:uint, 
			vecOwnTitle:Vector.<uint>, vecEquipTitle:Vector.<uint>, strGuide:String, byWallow:uint, vecIconAppear:Vector.<uint>, 
			vecIconDel:Vector.<uint>, dwDemonTowerFloorID:uint, dwDemonTowerPrizeFloorID:uint, dwCreateTime:uint):PlayerBaseData
		{
			var s_:PlayerBaseData = new PlayerBaseData();
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.byLevel = byLevel;
			s_.qwExp = qwExp;
			s_.wBagMax = wBagMax;
			s_.wDepotMax = wDepotMax;
			s_.byNation = byNation;
			s_.dwGold = dwGold;
			s_.dwSilver = dwSilver;
			s_.dwCoupon = dwCoupon;
			s_.dwSoul = dwSoul;
			s_.dwPrestige = dwPrestige;
			s_.dwHonor = dwHonor;
			s_.dwPExp = dwPExp;
			s_.dwSigil = dwSigil;
			s_.dwCentsY = dwCentsY;
			s_.dwAction = dwAction;
			s_.dwSop = dwSop;
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
			s_.dwBTPoint = dwBTPoint;
			s_.dwBlueFairyFate = dwBlueFairyFate;
			s_.dwPurpleFairyFate = dwPurpleFairyFate;
			s_.dwOrangeFairyFate = dwOrangeFairyFate;
			s_.dwTotalRecharge = dwTotalRecharge;
			s_.vecOwnTitle = vecOwnTitle;
			s_.vecEquipTitle = vecEquipTitle;
			s_.strGuide = strGuide;
			s_.byWallow = byWallow;
			s_.vecIconAppear = vecIconAppear;
			s_.vecIconDel = vecIconDel;
			s_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			s_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			s_.dwCreateTime = dwCreateTime;
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
				topXml = <PlayerBaseData _name_={name_} strName={strName} eCareer={eCareer} eSex={eSex} byLevel={byLevel} qwExp={qwExp}
				 wBagMax={wBagMax} wDepotMax={wDepotMax} byNation={byNation} dwGold={dwGold} dwSilver={dwSilver}
				 dwCoupon={dwCoupon} dwSoul={dwSoul} dwPrestige={dwPrestige} dwHonor={dwHonor} dwPExp={dwPExp}
				 dwSigil={dwSigil} dwCentsY={dwCentsY} dwAction={dwAction} dwSop={dwSop} dwPoten={dwPoten}
				 dwReiki={dwReiki} dwDemonSoul={dwDemonSoul} dwSoulAttack={dwSoulAttack} dwSoulHp={dwSoulHp} dwSoulCritical={dwSoulCritical}
				 dwSoulCounter={dwSoulCounter} dwSoulSpeed={dwSoulSpeed} dwSoulDefence={dwSoulDefence} dwSoulHit={dwSoulHit} dwSoulDodge={dwSoulDodge}
				 dwStampHuang={dwStampHuang} dwStampXuan={dwStampXuan} dwStampDi={dwStampDi} dwStampTian={dwStampTian} dwStampXing={dwStampXing}
				 dwStampYue={dwStampYue} dwStampDi2={dwStampDi2} dwStampXian={dwStampXian} dwStampSheng={dwStampSheng} dwStampFo={dwStampFo}
				 dwBTPoint={dwBTPoint} dwBlueFairyFate={dwBlueFairyFate} dwPurpleFairyFate={dwPurpleFairyFate} dwOrangeFairyFate={dwOrangeFairyFate} dwTotalRecharge={dwTotalRecharge} strGuide={strGuide} byWallow={byWallow} dwDemonTowerFloorID={dwDemonTowerFloorID} dwDemonTowerPrizeFloorID={dwDemonTowerPrizeFloorID} dwCreateTime={dwCreateTime}/>;
			else
				topXml = <PlayerBaseData strName={strName} eCareer={eCareer} eSex={eSex} byLevel={byLevel} qwExp={qwExp}
				 wBagMax={wBagMax} wDepotMax={wDepotMax} byNation={byNation} dwGold={dwGold} dwSilver={dwSilver}
				 dwCoupon={dwCoupon} dwSoul={dwSoul} dwPrestige={dwPrestige} dwHonor={dwHonor} dwPExp={dwPExp}
				 dwSigil={dwSigil} dwCentsY={dwCentsY} dwAction={dwAction} dwSop={dwSop} dwPoten={dwPoten}
				 dwReiki={dwReiki} dwDemonSoul={dwDemonSoul} dwSoulAttack={dwSoulAttack} dwSoulHp={dwSoulHp} dwSoulCritical={dwSoulCritical}
				 dwSoulCounter={dwSoulCounter} dwSoulSpeed={dwSoulSpeed} dwSoulDefence={dwSoulDefence} dwSoulHit={dwSoulHit} dwSoulDodge={dwSoulDodge}
				 dwStampHuang={dwStampHuang} dwStampXuan={dwStampXuan} dwStampDi={dwStampDi} dwStampTian={dwStampTian} dwStampXing={dwStampXing}
				 dwStampYue={dwStampYue} dwStampDi2={dwStampDi2} dwStampXian={dwStampXian} dwStampSheng={dwStampSheng} dwStampFo={dwStampFo}
				 dwBTPoint={dwBTPoint} dwBlueFairyFate={dwBlueFairyFate} dwPurpleFairyFate={dwPurpleFairyFate} dwOrangeFairyFate={dwOrangeFairyFate} dwTotalRecharge={dwTotalRecharge} strGuide={strGuide} byWallow={byWallow} dwDemonTowerFloorID={dwDemonTowerFloorID} dwDemonTowerPrizeFloorID={dwDemonTowerPrizeFloorID} dwCreateTime={dwCreateTime}/>;
			if(vecOwnTitle != null)
			{
				var vecOwnTitleXml:XML = <Vec_UINT16 _name_="vecOwnTitle"/>;
				var text1:String = "";
				for each(var value1:uint in vecOwnTitle)
					text1 += "[" + value1 + "]";
				vecOwnTitleXml.appendChild(text1);
				topXml.appendChild(vecOwnTitleXml);
			}
			if(vecEquipTitle != null)
			{
				var vecEquipTitleXml:XML = <Vec_UINT16 _name_="vecEquipTitle"/>;
				var text2:String = "";
				for each(var value2:uint in vecEquipTitle)
					text2 += "[" + value2 + "]";
				vecEquipTitleXml.appendChild(text2);
				topXml.appendChild(vecEquipTitleXml);
			}
			if(vecIconAppear != null)
			{
				var vecIconAppearXml:XML = <Vec_UINT16 _name_="vecIconAppear"/>;
				var text3:String = "";
				for each(var value3:uint in vecIconAppear)
					text3 += "[" + value3 + "]";
				vecIconAppearXml.appendChild(text3);
				topXml.appendChild(vecIconAppearXml);
			}
			if(vecIconDel != null)
			{
				var vecIconDelXml:XML = <Vec_UINT16 _name_="vecIconDel"/>;
				var text4:String = "";
				for each(var value4:uint in vecIconDel)
					text4 += "[" + value4 + "]";
				vecIconDelXml.appendChild(text4);
				topXml.appendChild(vecIconDelXml);
			}
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
			obj_.byLevel = byLevel;
			obj_.qwExp = qwExp;
			obj_.wBagMax = wBagMax;
			obj_.wDepotMax = wDepotMax;
			obj_.byNation = byNation;
			obj_.dwGold = dwGold;
			obj_.dwSilver = dwSilver;
			obj_.dwCoupon = dwCoupon;
			obj_.dwSoul = dwSoul;
			obj_.dwPrestige = dwPrestige;
			obj_.dwHonor = dwHonor;
			obj_.dwPExp = dwPExp;
			obj_.dwSigil = dwSigil;
			obj_.dwCentsY = dwCentsY;
			obj_.dwAction = dwAction;
			obj_.dwSop = dwSop;
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
			obj_.dwBTPoint = dwBTPoint;
			obj_.dwBlueFairyFate = dwBlueFairyFate;
			obj_.dwPurpleFairyFate = dwPurpleFairyFate;
			obj_.dwOrangeFairyFate = dwOrangeFairyFate;
			obj_.dwTotalRecharge = dwTotalRecharge;
			obj_.vecOwnTitle = vecOwnTitle;
			obj_.vecEquipTitle = vecEquipTitle;
			obj_.strGuide = strGuide;
			obj_.byWallow = byWallow;
			obj_.vecIconAppear = vecIconAppear;
			obj_.vecIconDel = vecIconDel;
			obj_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			obj_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			obj_.dwCreateTime = dwCreateTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerBaseData
		{
			var s_:PlayerBaseData = new PlayerBaseData();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var qwExp:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwExp = qwExp;
			var wBagMax:uint = bytes.readUnsignedShort();
			s_.wBagMax = wBagMax;
			var wDepotMax:uint = bytes.readUnsignedShort();
			s_.wDepotMax = wDepotMax;
			var byNation:uint = bytes.readUnsignedByte();
			s_.byNation = byNation;
			var dwGold:uint = bytes.readUnsignedInt();
			s_.dwGold = dwGold;
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
			var dwSigil:uint = bytes.readUnsignedInt();
			s_.dwSigil = dwSigil;
			var dwCentsY:uint = bytes.readUnsignedInt();
			s_.dwCentsY = dwCentsY;
			var dwAction:uint = bytes.readUnsignedInt();
			s_.dwAction = dwAction;
			var dwSop:uint = bytes.readUnsignedInt();
			s_.dwSop = dwSop;
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
			var dwBTPoint:uint = bytes.readUnsignedInt();
			s_.dwBTPoint = dwBTPoint;
			var dwBlueFairyFate:uint = bytes.readUnsignedInt();
			s_.dwBlueFairyFate = dwBlueFairyFate;
			var dwPurpleFairyFate:uint = bytes.readUnsignedInt();
			s_.dwPurpleFairyFate = dwPurpleFairyFate;
			var dwOrangeFairyFate:uint = bytes.readUnsignedInt();
			s_.dwOrangeFairyFate = dwOrangeFairyFate;
			var dwTotalRecharge:uint = bytes.readUnsignedInt();
			s_.dwTotalRecharge = dwTotalRecharge;
			var vecOwnTitle:Vector.<uint> = BytesUtil.readVecUShort(bytes);
			s_.vecOwnTitle = vecOwnTitle;
			var vecEquipTitle:Vector.<uint> = BytesUtil.readVecUShort(bytes);
			s_.vecEquipTitle = vecEquipTitle;
			var strGuide:String = BytesUtil.readString(bytes);
			s_.strGuide = strGuide;
			var byWallow:uint = bytes.readUnsignedByte();
			s_.byWallow = byWallow;
			var vecIconAppear:Vector.<uint> = BytesUtil.readVecUShort(bytes);
			s_.vecIconAppear = vecIconAppear;
			var vecIconDel:Vector.<uint> = BytesUtil.readVecUShort(bytes);
			s_.vecIconDel = vecIconDel;
			var dwDemonTowerFloorID:uint = bytes.readUnsignedInt();
			s_.dwDemonTowerFloorID = dwDemonTowerFloorID;
			var dwDemonTowerPrizeFloorID:uint = bytes.readUnsignedInt();
			s_.dwDemonTowerPrizeFloorID = dwDemonTowerPrizeFloorID;
			var dwCreateTime:uint = bytes.readUnsignedInt();
			s_.dwCreateTime = dwCreateTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerBaseData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerBaseData> = new Vector.<PlayerBaseData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerBaseData = PlayerBaseData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			bytes.writeByte(byLevel);
			BytesUtil.writeUInt64(bytes, qwExp);
			bytes.writeShort(wBagMax);
			bytes.writeShort(wDepotMax);
			bytes.writeByte(byNation);
			bytes.writeUnsignedInt(dwGold);
			bytes.writeUnsignedInt(dwSilver);
			bytes.writeUnsignedInt(dwCoupon);
			bytes.writeUnsignedInt(dwSoul);
			bytes.writeUnsignedInt(dwPrestige);
			bytes.writeUnsignedInt(dwHonor);
			bytes.writeUnsignedInt(dwPExp);
			bytes.writeUnsignedInt(dwSigil);
			bytes.writeUnsignedInt(dwCentsY);
			bytes.writeUnsignedInt(dwAction);
			bytes.writeUnsignedInt(dwSop);
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
			bytes.writeUnsignedInt(dwBTPoint);
			bytes.writeUnsignedInt(dwBlueFairyFate);
			bytes.writeUnsignedInt(dwPurpleFairyFate);
			bytes.writeUnsignedInt(dwOrangeFairyFate);
			bytes.writeUnsignedInt(dwTotalRecharge);
			BytesUtil.writeVecUShort(bytes, vecOwnTitle);
			BytesUtil.writeVecUShort(bytes, vecEquipTitle);
			BytesUtil.writeString(bytes, strGuide);
			bytes.writeByte(byWallow);
			BytesUtil.writeVecUShort(bytes, vecIconAppear);
			BytesUtil.writeVecUShort(bytes, vecIconDel);
			bytes.writeUnsignedInt(dwDemonTowerFloorID);
			bytes.writeUnsignedInt(dwDemonTowerPrizeFloorID);
			bytes.writeUnsignedInt(dwCreateTime);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerBaseData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerBaseData in vec)
				s.toByteArray(bytes);
		}
	}
}
