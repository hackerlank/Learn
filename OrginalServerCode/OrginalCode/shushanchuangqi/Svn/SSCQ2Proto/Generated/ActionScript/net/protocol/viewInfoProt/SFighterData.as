/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.itemProt.SEquipTrump;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙信息
	 */
	public final class SFighterData
	{
		public var wFighterID:uint; //(无符号16位整数)散仙模版
		public var byLevel:uint; //(无符号8位整数)散仙等级
		public var dwBTPoint:uint; //(无符号32位整数)战斗力
		public var vecAttr:Vector.<SFtAttrMod>; //将属性
		public var sDujie:SDujieData; //渡劫
		public var vecSkill:Vector.<SSkillData>; //技能
		public var sCuiTi:SCTData; //淬体
		public var vecBaoshi:Vector.<uint>; //(无符号32位整数)宝石
		public var vecCitta:Vector.<SCittaData>; //心法
		public var vecTrump:Vector.<SEquipTrump>; //法宝

		/**
		 * 辅助创建函数
		 */
		public static function create(wFighterID:uint, byLevel:uint, dwBTPoint:uint, vecAttr:Vector.<SFtAttrMod>, sDujie:SDujieData, 
			vecSkill:Vector.<SSkillData>, sCuiTi:SCTData, vecBaoshi:Vector.<uint>, vecCitta:Vector.<SCittaData>, vecTrump:Vector.<SEquipTrump>):SFighterData
		{
			var s_:SFighterData = new SFighterData();
			s_.wFighterID = wFighterID;
			s_.byLevel = byLevel;
			s_.dwBTPoint = dwBTPoint;
			s_.vecAttr = vecAttr;
			s_.sDujie = sDujie;
			s_.vecSkill = vecSkill;
			s_.sCuiTi = sCuiTi;
			s_.vecBaoshi = vecBaoshi;
			s_.vecCitta = vecCitta;
			s_.vecTrump = vecTrump;
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
				topXml = <SFighterData _name_={name_} wFighterID={wFighterID} byLevel={byLevel} dwBTPoint={dwBTPoint}/>;
			else
				topXml = <SFighterData wFighterID={wFighterID} byLevel={byLevel} dwBTPoint={dwBTPoint}/>;
			if(vecAttr != null)
			{
				var vecAttrXml:XML = <Vec_SFtAttrMod _name_="vecAttr"/>;
				for each(var s1:SFtAttrMod in vecAttr)
					vecAttrXml.appendChild(s1.toXML());
				topXml.appendChild(vecAttrXml);
			}
			if(sDujie != null)
				topXml.appendChild(sDujie.toXML("sDujie"));
			if(vecSkill != null)
			{
				var vecSkillXml:XML = <Vec_SSkillData _name_="vecSkill"/>;
				for each(var s3:SSkillData in vecSkill)
					vecSkillXml.appendChild(s3.toXML());
				topXml.appendChild(vecSkillXml);
			}
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
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
			obj_.dwBTPoint = dwBTPoint;
			obj_.vecAttr = vecAttr;
			obj_.sDujie = sDujie;
			obj_.vecSkill = vecSkill;
			obj_.sCuiTi = sCuiTi;
			obj_.vecBaoshi = vecBaoshi;
			obj_.vecCitta = vecCitta;
			obj_.vecTrump = vecTrump;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterData
		{
			var s_:SFighterData = new SFighterData();
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwBTPoint:uint = bytes.readUnsignedInt();
			s_.dwBTPoint = dwBTPoint;
			var vecAttr:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.vecAttr = vecAttr;
			var sDujie:SDujieData = SDujieData.fromByteArray(bytes);
			s_.sDujie = sDujie;
			var vecSkill:Vector.<SSkillData> = SSkillData.vectorFromByteArray(bytes);
			s_.vecSkill = vecSkill;
			var sCuiTi:SCTData = SCTData.fromByteArray(bytes);
			s_.sCuiTi = sCuiTi;
			var vecBaoshi:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecBaoshi = vecBaoshi;
			var vecCitta:Vector.<SCittaData> = SCittaData.vectorFromByteArray(bytes);
			s_.vecCitta = vecCitta;
			var vecTrump:Vector.<SEquipTrump> = SEquipTrump.vectorFromByteArray(bytes);
			s_.vecTrump = vecTrump;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterData> = new Vector.<SFighterData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterData = SFighterData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwBTPoint);
			SFtAttrMod.vectorToByteArray(vecAttr, bytes);
			sDujie.toByteArray(bytes);
			SSkillData.vectorToByteArray(vecSkill, bytes);
			sCuiTi.toByteArray(bytes);
			BytesUtil.writeVecUInt(bytes, vecBaoshi);
			SCittaData.vectorToByteArray(vecCitta, bytes);
			SEquipTrump.vectorToByteArray(vecTrump, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterData in vec)
				s.toByteArray(bytes);
		}
	}
}
