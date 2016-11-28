/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.itemProt.SItem;
	import net.protocol.itemProt.SEquipTrump;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗者信息
	 */
	public final class SFighterInfo
	{
		public var oBaseInfo:SFighterBaseInfo; //基本信息
		public var oAttrVec:Vector.<SFtAttrMod>; //将属性
		public var vActiveSkill:Vector.<SFightSkillInfo>; //装备的主动技能
		public var vPassiveSkill:Vector.<SFightSkillInfo>; //被动技能
		public var oPeerLees:SFightSkillInfo; //无双技能
		public var vecXinFa:Vector.<SXinFaInfo>; //散仙已经学会的心法信息(注：供客户端计算属性百分比加成)
		public var vecStoneItem:Vector.<SItem>; //宝石信息
		public var vecEquipTrump:Vector.<SEquipTrump>; //装备法宝信息

		/**
		 * 辅助创建函数
		 */
		public static function create(oBaseInfo:SFighterBaseInfo, oAttrVec:Vector.<SFtAttrMod>, vActiveSkill:Vector.<SFightSkillInfo>, vPassiveSkill:Vector.<SFightSkillInfo>, oPeerLees:SFightSkillInfo, 
			vecXinFa:Vector.<SXinFaInfo>, vecStoneItem:Vector.<SItem>, vecEquipTrump:Vector.<SEquipTrump>):SFighterInfo
		{
			var s_:SFighterInfo = new SFighterInfo();
			s_.oBaseInfo = oBaseInfo;
			s_.oAttrVec = oAttrVec;
			s_.vActiveSkill = vActiveSkill;
			s_.vPassiveSkill = vPassiveSkill;
			s_.oPeerLees = oPeerLees;
			s_.vecXinFa = vecXinFa;
			s_.vecStoneItem = vecStoneItem;
			s_.vecEquipTrump = vecEquipTrump;
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
				topXml = <SFighterInfo _name_={name_}/>;
			else
				topXml = <SFighterInfo/>;
			if(oBaseInfo != null)
				topXml.appendChild(oBaseInfo.toXML("oBaseInfo"));
			if(oAttrVec != null)
			{
				var oAttrVecXml:XML = <Vec_SFtAttrMod _name_="oAttrVec"/>;
				for each(var s2:SFtAttrMod in oAttrVec)
					oAttrVecXml.appendChild(s2.toXML());
				topXml.appendChild(oAttrVecXml);
			}
			if(vActiveSkill != null)
			{
				var vActiveSkillXml:XML = <Vec_SFightSkillInfo _name_="vActiveSkill"/>;
				for each(var s3:SFightSkillInfo in vActiveSkill)
					vActiveSkillXml.appendChild(s3.toXML());
				topXml.appendChild(vActiveSkillXml);
			}
			if(vPassiveSkill != null)
			{
				var vPassiveSkillXml:XML = <Vec_SFightSkillInfo _name_="vPassiveSkill"/>;
				for each(var s4:SFightSkillInfo in vPassiveSkill)
					vPassiveSkillXml.appendChild(s4.toXML());
				topXml.appendChild(vPassiveSkillXml);
			}
			if(oPeerLees != null)
				topXml.appendChild(oPeerLees.toXML("oPeerLees"));
			if(vecXinFa != null)
			{
				var vecXinFaXml:XML = <Vec_SXinFaInfo _name_="vecXinFa"/>;
				for each(var s6:SXinFaInfo in vecXinFa)
					vecXinFaXml.appendChild(s6.toXML());
				topXml.appendChild(vecXinFaXml);
			}
			if(vecStoneItem != null)
			{
				var vecStoneItemXml:XML = <Vec_SItem _name_="vecStoneItem"/>;
				for each(var s7:SItem in vecStoneItem)
					vecStoneItemXml.appendChild(s7.toXML());
				topXml.appendChild(vecStoneItemXml);
			}
			if(vecEquipTrump != null)
			{
				var vecEquipTrumpXml:XML = <Vec_SEquipTrump _name_="vecEquipTrump"/>;
				for each(var s8:SEquipTrump in vecEquipTrump)
					vecEquipTrumpXml.appendChild(s8.toXML());
				topXml.appendChild(vecEquipTrumpXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.oBaseInfo = oBaseInfo;
			obj_.oAttrVec = oAttrVec;
			obj_.vActiveSkill = vActiveSkill;
			obj_.vPassiveSkill = vPassiveSkill;
			obj_.oPeerLees = oPeerLees;
			obj_.vecXinFa = vecXinFa;
			obj_.vecStoneItem = vecStoneItem;
			obj_.vecEquipTrump = vecEquipTrump;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterInfo
		{
			var s_:SFighterInfo = new SFighterInfo();
			var oBaseInfo:SFighterBaseInfo = SFighterBaseInfo.fromByteArray(bytes);
			s_.oBaseInfo = oBaseInfo;
			var oAttrVec:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.oAttrVec = oAttrVec;
			var vActiveSkill:Vector.<SFightSkillInfo> = SFightSkillInfo.vectorFromByteArray(bytes);
			s_.vActiveSkill = vActiveSkill;
			var vPassiveSkill:Vector.<SFightSkillInfo> = SFightSkillInfo.vectorFromByteArray(bytes);
			s_.vPassiveSkill = vPassiveSkill;
			var oPeerLees:SFightSkillInfo = SFightSkillInfo.fromByteArray(bytes);
			s_.oPeerLees = oPeerLees;
			var vecXinFa:Vector.<SXinFaInfo> = SXinFaInfo.vectorFromByteArray(bytes);
			s_.vecXinFa = vecXinFa;
			var vecStoneItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes);
			s_.vecStoneItem = vecStoneItem;
			var vecEquipTrump:Vector.<SEquipTrump> = SEquipTrump.vectorFromByteArray(bytes);
			s_.vecEquipTrump = vecEquipTrump;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterInfo> = new Vector.<SFighterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterInfo = SFighterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			oBaseInfo.toByteArray(bytes);
			SFtAttrMod.vectorToByteArray(oAttrVec, bytes);
			SFightSkillInfo.vectorToByteArray(vActiveSkill, bytes);
			SFightSkillInfo.vectorToByteArray(vPassiveSkill, bytes);
			oPeerLees.toByteArray(bytes);
			SXinFaInfo.vectorToByteArray(vecXinFa, bytes);
			SItem.superVectorToByteArray(vecStoneItem, bytes);
			SEquipTrump.vectorToByteArray(vecEquipTrump, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
