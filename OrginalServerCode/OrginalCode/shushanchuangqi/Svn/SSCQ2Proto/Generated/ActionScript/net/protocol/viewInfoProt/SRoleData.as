/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.itemProt.SEquipTrump;
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 主角信息
	 */
	public final class SRoleData
	{
		public var strName:String; //玩家名字
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var byLevel:uint; //(无符号8位整数)玩家等级
		public var dwBTPoint:uint; //(无符号32位整数)战斗力
		public var vecAttr:Vector.<SFtAttrMod>; //总属性
		public var vecBattleFighter:Vector.<SBattleFighterData>; //出战的散仙
		public var sDujie:SDujieData; //渡劫
		public var sCuiTi:SCTData; //淬体(装备)
		public var vecBaoshi:Vector.<uint>; //(无符号32位整数)宝石
		public var vecCitta:Vector.<SCittaData>; //心法
		public var vecTrump:Vector.<SEquipTrump>; //法宝
		public var vecRareTrump:Vector.<SRareTrumpData>; //稀有(被动）法宝
		public var sBeauty:SBeautyData; //美女
		public var sBeastSoul:SBeastSoulData; //魂魄
		public var vecComb:Vector.<SCombData>; //组合
		public var vecSkill:Vector.<SSkillData>; //技能
		public var vecHorse:Vector.<SHorseData>; //坐骑
		public var vecFashion:Vector.<SFashionData>; //已激活的时装
		public var vecTitle:Vector.<STitleData>; //已激活的称号
		public var vecGuild:Vector.<SGuildData>; //帮派
		public var vecTianBookAttr:Vector.<SFtAttrMod>; //天书属性

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, eCareer:uint, byLevel:uint, dwBTPoint:uint, vecAttr:Vector.<SFtAttrMod>, 
			vecBattleFighter:Vector.<SBattleFighterData>, sDujie:SDujieData, sCuiTi:SCTData, vecBaoshi:Vector.<uint>, vecCitta:Vector.<SCittaData>, 
			vecTrump:Vector.<SEquipTrump>, vecRareTrump:Vector.<SRareTrumpData>, sBeauty:SBeautyData, sBeastSoul:SBeastSoulData, vecComb:Vector.<SCombData>, 
			vecSkill:Vector.<SSkillData>, vecHorse:Vector.<SHorseData>, vecFashion:Vector.<SFashionData>, vecTitle:Vector.<STitleData>, vecGuild:Vector.<SGuildData>, 
			vecTianBookAttr:Vector.<SFtAttrMod>):SRoleData
		{
			var s_:SRoleData = new SRoleData();
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.byLevel = byLevel;
			s_.dwBTPoint = dwBTPoint;
			s_.vecAttr = vecAttr;
			s_.vecBattleFighter = vecBattleFighter;
			s_.sDujie = sDujie;
			s_.sCuiTi = sCuiTi;
			s_.vecBaoshi = vecBaoshi;
			s_.vecCitta = vecCitta;
			s_.vecTrump = vecTrump;
			s_.vecRareTrump = vecRareTrump;
			s_.sBeauty = sBeauty;
			s_.sBeastSoul = sBeastSoul;
			s_.vecComb = vecComb;
			s_.vecSkill = vecSkill;
			s_.vecHorse = vecHorse;
			s_.vecFashion = vecFashion;
			s_.vecTitle = vecTitle;
			s_.vecGuild = vecGuild;
			s_.vecTianBookAttr = vecTianBookAttr;
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
				topXml = <SRoleData _name_={name_} strName={strName} eCareer={eCareer} byLevel={byLevel} dwBTPoint={dwBTPoint}/>;
			else
				topXml = <SRoleData strName={strName} eCareer={eCareer} byLevel={byLevel} dwBTPoint={dwBTPoint}/>;
			if(vecAttr != null)
			{
				var vecAttrXml:XML = <Vec_SFtAttrMod _name_="vecAttr"/>;
				for each(var s1:SFtAttrMod in vecAttr)
					vecAttrXml.appendChild(s1.toXML());
				topXml.appendChild(vecAttrXml);
			}
			if(vecBattleFighter != null)
			{
				var vecBattleFighterXml:XML = <Vec_SBattleFighterData _name_="vecBattleFighter"/>;
				for each(var s2:SBattleFighterData in vecBattleFighter)
					vecBattleFighterXml.appendChild(s2.toXML());
				topXml.appendChild(vecBattleFighterXml);
			}
			if(sDujie != null)
				topXml.appendChild(sDujie.toXML("sDujie"));
			if(sCuiTi != null)
				topXml.appendChild(sCuiTi.toXML("sCuiTi"));
			if(vecBaoshi != null)
			{
				var vecBaoshiXml:XML = <Vec_UINT32 _name_="vecBaoshi"/>;
				var text5:String = "";
				for each(var value5:uint in vecBaoshi)
					text5 += "[" + value5 + "]";
				vecBaoshiXml.appendChild(text5);
				topXml.appendChild(vecBaoshiXml);
			}
			if(vecCitta != null)
			{
				var vecCittaXml:XML = <Vec_SCittaData _name_="vecCitta"/>;
				for each(var s6:SCittaData in vecCitta)
					vecCittaXml.appendChild(s6.toXML());
				topXml.appendChild(vecCittaXml);
			}
			if(vecTrump != null)
			{
				var vecTrumpXml:XML = <Vec_SEquipTrump _name_="vecTrump"/>;
				for each(var s7:SEquipTrump in vecTrump)
					vecTrumpXml.appendChild(s7.toXML());
				topXml.appendChild(vecTrumpXml);
			}
			if(vecRareTrump != null)
			{
				var vecRareTrumpXml:XML = <Vec_SRareTrumpData _name_="vecRareTrump"/>;
				for each(var s8:SRareTrumpData in vecRareTrump)
					vecRareTrumpXml.appendChild(s8.toXML());
				topXml.appendChild(vecRareTrumpXml);
			}
			if(sBeauty != null)
				topXml.appendChild(sBeauty.toXML("sBeauty"));
			if(sBeastSoul != null)
				topXml.appendChild(sBeastSoul.toXML("sBeastSoul"));
			if(vecComb != null)
			{
				var vecCombXml:XML = <Vec_SCombData _name_="vecComb"/>;
				for each(var s11:SCombData in vecComb)
					vecCombXml.appendChild(s11.toXML());
				topXml.appendChild(vecCombXml);
			}
			if(vecSkill != null)
			{
				var vecSkillXml:XML = <Vec_SSkillData _name_="vecSkill"/>;
				for each(var s12:SSkillData in vecSkill)
					vecSkillXml.appendChild(s12.toXML());
				topXml.appendChild(vecSkillXml);
			}
			if(vecHorse != null)
			{
				var vecHorseXml:XML = <Vec_SHorseData _name_="vecHorse"/>;
				for each(var s13:SHorseData in vecHorse)
					vecHorseXml.appendChild(s13.toXML());
				topXml.appendChild(vecHorseXml);
			}
			if(vecFashion != null)
			{
				var vecFashionXml:XML = <Vec_SFashionData _name_="vecFashion"/>;
				for each(var s14:SFashionData in vecFashion)
					vecFashionXml.appendChild(s14.toXML());
				topXml.appendChild(vecFashionXml);
			}
			if(vecTitle != null)
			{
				var vecTitleXml:XML = <Vec_STitleData _name_="vecTitle"/>;
				for each(var s15:STitleData in vecTitle)
					vecTitleXml.appendChild(s15.toXML());
				topXml.appendChild(vecTitleXml);
			}
			if(vecGuild != null)
			{
				var vecGuildXml:XML = <Vec_SGuildData _name_="vecGuild"/>;
				for each(var s16:SGuildData in vecGuild)
					vecGuildXml.appendChild(s16.toXML());
				topXml.appendChild(vecGuildXml);
			}
			if(vecTianBookAttr != null)
			{
				var vecTianBookAttrXml:XML = <Vec_SFtAttrMod _name_="vecTianBookAttr"/>;
				for each(var s17:SFtAttrMod in vecTianBookAttr)
					vecTianBookAttrXml.appendChild(s17.toXML());
				topXml.appendChild(vecTianBookAttrXml);
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
			obj_.byLevel = byLevel;
			obj_.dwBTPoint = dwBTPoint;
			obj_.vecAttr = vecAttr;
			obj_.vecBattleFighter = vecBattleFighter;
			obj_.sDujie = sDujie;
			obj_.sCuiTi = sCuiTi;
			obj_.vecBaoshi = vecBaoshi;
			obj_.vecCitta = vecCitta;
			obj_.vecTrump = vecTrump;
			obj_.vecRareTrump = vecRareTrump;
			obj_.sBeauty = sBeauty;
			obj_.sBeastSoul = sBeastSoul;
			obj_.vecComb = vecComb;
			obj_.vecSkill = vecSkill;
			obj_.vecHorse = vecHorse;
			obj_.vecFashion = vecFashion;
			obj_.vecTitle = vecTitle;
			obj_.vecGuild = vecGuild;
			obj_.vecTianBookAttr = vecTianBookAttr;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleData
		{
			var s_:SRoleData = new SRoleData();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwBTPoint:uint = bytes.readUnsignedInt();
			s_.dwBTPoint = dwBTPoint;
			var vecAttr:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecAttr = vecAttr;
			var vecBattleFighter:Vector.<SBattleFighterData> = SBattleFighterData.vectorFromByteArray(bytes);
			s_.vecBattleFighter = vecBattleFighter;
			var sDujie:SDujieData = SDujieData.fromByteArray(bytes);
			s_.sDujie = sDujie;
			var sCuiTi:SCTData = SCTData.fromByteArray(bytes);
			s_.sCuiTi = sCuiTi;
			var vecBaoshi:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecBaoshi = vecBaoshi;
			var vecCitta:Vector.<SCittaData> = SCittaData.vectorFromByteArray(bytes);
			s_.vecCitta = vecCitta;
			var vecTrump:Vector.<SEquipTrump> = SEquipTrump.vectorFromByteArray(bytes);
			s_.vecTrump = vecTrump;
			var vecRareTrump:Vector.<SRareTrumpData> = SRareTrumpData.vectorFromByteArray(bytes);
			s_.vecRareTrump = vecRareTrump;
			var sBeauty:SBeautyData = SBeautyData.fromByteArray(bytes);
			s_.sBeauty = sBeauty;
			var sBeastSoul:SBeastSoulData = SBeastSoulData.fromByteArray(bytes);
			s_.sBeastSoul = sBeastSoul;
			var vecComb:Vector.<SCombData> = SCombData.vectorFromByteArray(bytes);
			s_.vecComb = vecComb;
			var vecSkill:Vector.<SSkillData> = SSkillData.vectorFromByteArray(bytes);
			s_.vecSkill = vecSkill;
			var vecHorse:Vector.<SHorseData> = SHorseData.vectorFromByteArray(bytes);
			s_.vecHorse = vecHorse;
			var vecFashion:Vector.<SFashionData> = SFashionData.vectorFromByteArray(bytes);
			s_.vecFashion = vecFashion;
			var vecTitle:Vector.<STitleData> = STitleData.vectorFromByteArray(bytes);
			s_.vecTitle = vecTitle;
			var vecGuild:Vector.<SGuildData> = SGuildData.vectorFromByteArray(bytes);
			s_.vecGuild = vecGuild;
			var vecTianBookAttr:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecTianBookAttr = vecTianBookAttr;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleData> = new Vector.<SRoleData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleData = SRoleData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwBTPoint);
			SFtAttrMod.vectorToByteArray(vecAttr, bytes);
			SBattleFighterData.vectorToByteArray(vecBattleFighter, bytes);
			sDujie.toByteArray(bytes);
			sCuiTi.toByteArray(bytes);
			BytesUtil.writeVecUInt(bytes, vecBaoshi);
			SCittaData.vectorToByteArray(vecCitta, bytes);
			SEquipTrump.vectorToByteArray(vecTrump, bytes);
			SRareTrumpData.vectorToByteArray(vecRareTrump, bytes);
			sBeauty.toByteArray(bytes);
			sBeastSoul.toByteArray(bytes);
			SCombData.vectorToByteArray(vecComb, bytes);
			SSkillData.vectorToByteArray(vecSkill, bytes);
			SHorseData.vectorToByteArray(vecHorse, bytes);
			SFashionData.vectorToByteArray(vecFashion, bytes);
			STitleData.vectorToByteArray(vecTitle, bytes);
			SGuildData.vectorToByteArray(vecGuild, bytes);
			SFtAttrMod.vectorToByteArray(vecTianBookAttr, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleData in vec)
				s.toByteArray(bytes);
		}
	}
}
