/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlauntHero.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙炫耀信息
	 */
	public final class SFlauntHero
	{
		public var strName:String; //名字
		public var qwInstID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var wFighterID:uint; //(无符号16位整数)散仙ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var byQuilty:uint; //(无符号8位整数)品质 0,1,2,3,4,5,6【黑白绿蓝紫黄橙】
		public var dwPower:uint; //(无符号32位整数)散仙战斗力
		public var oAttrVec:Vector.<SFtAttrMod>; //最终属性
		public var byDujieLevel:uint; //(无符号8位整数)散仙渡劫等级
		public var vActiveSkill:Vector.<SFlauntSkill>; //主动技能
		public var vPassiveSkill:Vector.<SFlauntSkill>; //被动技能
		public var sPeerLessSkill:SFlauntSkill; //无双技能
		public var vecFlauntEquip:Vector.<SFlauntEquip>; //时装
		public var byLianPi:uint; //(无符号8位整数)炼皮
		public var byTongJin:uint; //(无符号8位整数)通筋
		public var byQiangJi:uint; //(无符号8位整数)强肌
		public var byDuanGu:uint; //(无符号8位整数)锻骨
		public var byHuoLuo:uint; //(无符号8位整数)活络
		public var byXiSui:uint; //(无符号8位整数)洗髓

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, qwInstID:BigInteger, wFighterID:uint, byLevel:uint, byQuilty:uint, 
			dwPower:uint, oAttrVec:Vector.<SFtAttrMod>, byDujieLevel:uint, vActiveSkill:Vector.<SFlauntSkill>, vPassiveSkill:Vector.<SFlauntSkill>, 
			sPeerLessSkill:SFlauntSkill, vecFlauntEquip:Vector.<SFlauntEquip>, byLianPi:uint, byTongJin:uint, byQiangJi:uint, 
			byDuanGu:uint, byHuoLuo:uint, byXiSui:uint):SFlauntHero
		{
			var s_:SFlauntHero = new SFlauntHero();
			s_.strName = strName;
			s_.qwInstID = qwInstID;
			s_.wFighterID = wFighterID;
			s_.byLevel = byLevel;
			s_.byQuilty = byQuilty;
			s_.dwPower = dwPower;
			s_.oAttrVec = oAttrVec;
			s_.byDujieLevel = byDujieLevel;
			s_.vActiveSkill = vActiveSkill;
			s_.vPassiveSkill = vPassiveSkill;
			s_.sPeerLessSkill = sPeerLessSkill;
			s_.vecFlauntEquip = vecFlauntEquip;
			s_.byLianPi = byLianPi;
			s_.byTongJin = byTongJin;
			s_.byQiangJi = byQiangJi;
			s_.byDuanGu = byDuanGu;
			s_.byHuoLuo = byHuoLuo;
			s_.byXiSui = byXiSui;
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
				topXml = <SFlauntHero _name_={name_} strName={strName} qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel} byQuilty={byQuilty}
				 dwPower={dwPower} byDujieLevel={byDujieLevel} byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi}
				 byDuanGu={byDuanGu} byHuoLuo={byHuoLuo} byXiSui={byXiSui}/>;
			else
				topXml = <SFlauntHero strName={strName} qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel} byQuilty={byQuilty}
				 dwPower={dwPower} byDujieLevel={byDujieLevel} byLianPi={byLianPi} byTongJin={byTongJin} byQiangJi={byQiangJi}
				 byDuanGu={byDuanGu} byHuoLuo={byHuoLuo} byXiSui={byXiSui}/>;
			if(oAttrVec != null)
			{
				var oAttrVecXml:XML = <Vec_SFtAttrMod _name_="oAttrVec"/>;
				for each(var s1:SFtAttrMod in oAttrVec)
					oAttrVecXml.appendChild(s1.toXML());
				topXml.appendChild(oAttrVecXml);
			}
			if(vActiveSkill != null)
			{
				var vActiveSkillXml:XML = <Vec_SFlauntSkill _name_="vActiveSkill"/>;
				for each(var s2:SFlauntSkill in vActiveSkill)
					vActiveSkillXml.appendChild(s2.toXML());
				topXml.appendChild(vActiveSkillXml);
			}
			if(vPassiveSkill != null)
			{
				var vPassiveSkillXml:XML = <Vec_SFlauntSkill _name_="vPassiveSkill"/>;
				for each(var s3:SFlauntSkill in vPassiveSkill)
					vPassiveSkillXml.appendChild(s3.toXML());
				topXml.appendChild(vPassiveSkillXml);
			}
			if(sPeerLessSkill != null)
				topXml.appendChild(sPeerLessSkill.toXML("sPeerLessSkill"));
			if(vecFlauntEquip != null)
			{
				var vecFlauntEquipXml:XML = <Vec_SFlauntEquip _name_="vecFlauntEquip"/>;
				for each(var s5:SFlauntEquip in vecFlauntEquip)
					vecFlauntEquipXml.appendChild(s5.toXML());
				topXml.appendChild(vecFlauntEquipXml);
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
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
			obj_.byQuilty = byQuilty;
			obj_.dwPower = dwPower;
			obj_.oAttrVec = oAttrVec;
			obj_.byDujieLevel = byDujieLevel;
			obj_.vActiveSkill = vActiveSkill;
			obj_.vPassiveSkill = vPassiveSkill;
			obj_.sPeerLessSkill = sPeerLessSkill;
			obj_.vecFlauntEquip = vecFlauntEquip;
			obj_.byLianPi = byLianPi;
			obj_.byTongJin = byTongJin;
			obj_.byQiangJi = byQiangJi;
			obj_.byDuanGu = byDuanGu;
			obj_.byHuoLuo = byHuoLuo;
			obj_.byXiSui = byXiSui;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlauntHero
		{
			var s_:SFlauntHero = new SFlauntHero();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byQuilty:uint = bytes.readUnsignedByte();
			s_.byQuilty = byQuilty;
			var dwPower:uint = bytes.readUnsignedInt();
			s_.dwPower = dwPower;
			var oAttrVec:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.oAttrVec = oAttrVec;
			var byDujieLevel:uint = bytes.readUnsignedByte();
			s_.byDujieLevel = byDujieLevel;
			var vActiveSkill:Vector.<SFlauntSkill> = SFlauntSkill.vectorFromByteArray(bytes);
			s_.vActiveSkill = vActiveSkill;
			var vPassiveSkill:Vector.<SFlauntSkill> = SFlauntSkill.vectorFromByteArray(bytes);
			s_.vPassiveSkill = vPassiveSkill;
			var sPeerLessSkill:SFlauntSkill = SFlauntSkill.fromByteArray(bytes);
			s_.sPeerLessSkill = sPeerLessSkill;
			var vecFlauntEquip:Vector.<SFlauntEquip> = SFlauntEquip.vectorFromByteArray(bytes);
			s_.vecFlauntEquip = vecFlauntEquip;
			var byLianPi:uint = bytes.readUnsignedByte();
			s_.byLianPi = byLianPi;
			var byTongJin:uint = bytes.readUnsignedByte();
			s_.byTongJin = byTongJin;
			var byQiangJi:uint = bytes.readUnsignedByte();
			s_.byQiangJi = byQiangJi;
			var byDuanGu:uint = bytes.readUnsignedByte();
			s_.byDuanGu = byDuanGu;
			var byHuoLuo:uint = bytes.readUnsignedByte();
			s_.byHuoLuo = byHuoLuo;
			var byXiSui:uint = bytes.readUnsignedByte();
			s_.byXiSui = byXiSui;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlauntHero>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlauntHero> = new Vector.<SFlauntHero>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlauntHero = SFlauntHero.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
			bytes.writeByte(byQuilty);
			bytes.writeUnsignedInt(dwPower);
			SFtAttrMod.vectorToByteArray(oAttrVec, bytes);
			bytes.writeByte(byDujieLevel);
			SFlauntSkill.vectorToByteArray(vActiveSkill, bytes);
			SFlauntSkill.vectorToByteArray(vPassiveSkill, bytes);
			sPeerLessSkill.toByteArray(bytes);
			SFlauntEquip.vectorToByteArray(vecFlauntEquip, bytes);
			bytes.writeByte(byLianPi);
			bytes.writeByte(byTongJin);
			bytes.writeByte(byQiangJi);
			bytes.writeByte(byDuanGu);
			bytes.writeByte(byHuoLuo);
			bytes.writeByte(byXiSui);
		}

		public static function vectorToByteArray(vec:Vector.<SFlauntHero>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlauntHero in vec)
				s.toByteArray(bytes);
		}
	}
}
