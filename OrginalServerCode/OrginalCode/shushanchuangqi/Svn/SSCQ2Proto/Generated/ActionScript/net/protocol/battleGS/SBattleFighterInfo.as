/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleFighterInfo.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗者信息
	 */
	public final class SBattleFighterInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var wFighterID:uint; //(无符号16位整数)将类型ID
		public var iPos:int; //(有符号32位整数)将位置
		public var byTeamID:uint; //(无符号8位整数)所属队伍ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var strName:String; //将名字
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)将性别
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)将职业
		public var dwHpMax:uint; //(无符号32位整数)最大血量
		public var dwHp:uint; //(无符号32位整数)当前血量
		public var dwAura:uint; //(无符号32位整数)当前灵气
		public var dwAuraMax:uint; //(无符号32位整数)最大灵气
		public var oAttrVec:Vector.<SFtAttrMod>; //最终属性
		public var vActiveSkill:Vector.<SBattleFightSkillInfo>; //装备的主动技能
		public var vPassiveSkill:Vector.<SBattleFightSkillInfo>; //被动技能
		public var oPeerLees:SBattleFightSkillInfo; //无双技能
		public var oPeerLeesEx:SBattleFightSkillInfo; //变身后无双技能
		public var pFeature:SFeatureBase; //外观信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wFighterID:uint, iPos:int, byTeamID:uint, byLevel:uint, 
			strName:String, eSex:uint, eCareer:uint, dwHpMax:uint, dwHp:uint, 
			dwAura:uint, dwAuraMax:uint, oAttrVec:Vector.<SFtAttrMod>, vActiveSkill:Vector.<SBattleFightSkillInfo>, vPassiveSkill:Vector.<SBattleFightSkillInfo>, 
			oPeerLees:SBattleFightSkillInfo, oPeerLeesEx:SBattleFightSkillInfo, pFeature:SFeatureBase):SBattleFighterInfo
		{
			var s_:SBattleFighterInfo = new SBattleFighterInfo();
			s_.qwInstID = qwInstID;
			s_.wFighterID = wFighterID;
			s_.iPos = iPos;
			s_.byTeamID = byTeamID;
			s_.byLevel = byLevel;
			s_.strName = strName;
			s_.eSex = eSex;
			s_.eCareer = eCareer;
			s_.dwHpMax = dwHpMax;
			s_.dwHp = dwHp;
			s_.dwAura = dwAura;
			s_.dwAuraMax = dwAuraMax;
			s_.oAttrVec = oAttrVec;
			s_.vActiveSkill = vActiveSkill;
			s_.vPassiveSkill = vPassiveSkill;
			s_.oPeerLees = oPeerLees;
			s_.oPeerLeesEx = oPeerLeesEx;
			s_.pFeature = pFeature;
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
				topXml = <SBattleFighterInfo _name_={name_} qwInstID={qwInstID} wFighterID={wFighterID} iPos={iPos} byTeamID={byTeamID} byLevel={byLevel}
				 strName={strName} eSex={eSex} eCareer={eCareer} dwHpMax={dwHpMax} dwHp={dwHp}
				 dwAura={dwAura} dwAuraMax={dwAuraMax}/>;
			else
				topXml = <SBattleFighterInfo qwInstID={qwInstID} wFighterID={wFighterID} iPos={iPos} byTeamID={byTeamID} byLevel={byLevel}
				 strName={strName} eSex={eSex} eCareer={eCareer} dwHpMax={dwHpMax} dwHp={dwHp}
				 dwAura={dwAura} dwAuraMax={dwAuraMax}/>;
			if(oAttrVec != null)
			{
				var oAttrVecXml:XML = <Vec_SFtAttrMod _name_="oAttrVec"/>;
				for each(var s1:SFtAttrMod in oAttrVec)
					oAttrVecXml.appendChild(s1.toXML());
				topXml.appendChild(oAttrVecXml);
			}
			if(vActiveSkill != null)
			{
				var vActiveSkillXml:XML = <Vec_SBattleFightSkillInfo _name_="vActiveSkill"/>;
				for each(var s2:SBattleFightSkillInfo in vActiveSkill)
					vActiveSkillXml.appendChild(s2.toXML());
				topXml.appendChild(vActiveSkillXml);
			}
			if(vPassiveSkill != null)
			{
				var vPassiveSkillXml:XML = <Vec_SBattleFightSkillInfo _name_="vPassiveSkill"/>;
				for each(var s3:SBattleFightSkillInfo in vPassiveSkill)
					vPassiveSkillXml.appendChild(s3.toXML());
				topXml.appendChild(vPassiveSkillXml);
			}
			if(oPeerLees != null)
				topXml.appendChild(oPeerLees.toXML("oPeerLees"));
			if(oPeerLeesEx != null)
				topXml.appendChild(oPeerLeesEx.toXML("oPeerLeesEx"));
			if(pFeature != null)
				topXml.appendChild(pFeature.toXML("pFeature"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.iPos = iPos;
			obj_.byTeamID = byTeamID;
			obj_.byLevel = byLevel;
			obj_.strName = strName;
			obj_.eSex = eSex;
			obj_.eCareer = eCareer;
			obj_.dwHpMax = dwHpMax;
			obj_.dwHp = dwHp;
			obj_.dwAura = dwAura;
			obj_.dwAuraMax = dwAuraMax;
			obj_.oAttrVec = oAttrVec;
			obj_.vActiveSkill = vActiveSkill;
			obj_.vPassiveSkill = vPassiveSkill;
			obj_.oPeerLees = oPeerLees;
			obj_.oPeerLeesEx = oPeerLeesEx;
			obj_.pFeature = pFeature;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleFighterInfo
		{
			var s_:SBattleFighterInfo = new SBattleFighterInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var iPos:int = bytes.readInt();
			s_.iPos = iPos;
			var byTeamID:uint = bytes.readUnsignedByte();
			s_.byTeamID = byTeamID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var dwHpMax:uint = bytes.readUnsignedInt();
			s_.dwHpMax = dwHpMax;
			var dwHp:uint = bytes.readUnsignedInt();
			s_.dwHp = dwHp;
			var dwAura:uint = bytes.readUnsignedInt();
			s_.dwAura = dwAura;
			var dwAuraMax:uint = bytes.readUnsignedInt();
			s_.dwAuraMax = dwAuraMax;
			var oAttrVec:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.oAttrVec = oAttrVec;
			var vActiveSkill:Vector.<SBattleFightSkillInfo> = SBattleFightSkillInfo.vectorFromByteArray(bytes);
			s_.vActiveSkill = vActiveSkill;
			var vPassiveSkill:Vector.<SBattleFightSkillInfo> = SBattleFightSkillInfo.vectorFromByteArray(bytes);
			s_.vPassiveSkill = vPassiveSkill;
			var oPeerLees:SBattleFightSkillInfo = SBattleFightSkillInfo.fromByteArray(bytes);
			s_.oPeerLees = oPeerLees;
			var oPeerLeesEx:SBattleFightSkillInfo = SBattleFightSkillInfo.fromByteArray(bytes);
			s_.oPeerLeesEx = oPeerLeesEx;
			var pFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
			s_.pFeature = pFeature;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleFighterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleFighterInfo> = new Vector.<SBattleFighterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleFighterInfo = SBattleFighterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeInt(iPos);
			bytes.writeByte(byTeamID);
			bytes.writeByte(byLevel);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eSex);
			bytes.writeByte(eCareer);
			bytes.writeUnsignedInt(dwHpMax);
			bytes.writeUnsignedInt(dwHp);
			bytes.writeUnsignedInt(dwAura);
			bytes.writeUnsignedInt(dwAuraMax);
			SFtAttrMod.vectorToByteArray(oAttrVec, bytes);
			SBattleFightSkillInfo.vectorToByteArray(vActiveSkill, bytes);
			SBattleFightSkillInfo.vectorToByteArray(vPassiveSkill, bytes);
			oPeerLees.toByteArray(bytes);
			oPeerLeesEx.toByteArray(bytes);
			pFeature.superToByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleFighterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleFighterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
