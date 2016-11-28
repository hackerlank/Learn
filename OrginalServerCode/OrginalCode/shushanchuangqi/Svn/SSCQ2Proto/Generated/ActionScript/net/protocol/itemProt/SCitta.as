/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCitta.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 心法的信息
	 */
	public final class SCitta extends SItem
	{
		public var qwOwnerID:BigInteger; //(无符号64位整数)散仙唯一ID，属于散仙的物品时有效
		public var eCittaNameType:uint; //(枚举类型：ECittaNameType)心法姓名前缀
		public var oAttrVec:Vector.<SFtAttrMod>; //增加属性
		public var dwSkillID:uint; //(无符号32位整数)附加技能ID
		public var dwSignetID:uint; //(无符号32位整数)印记ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_SCitta;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SCitta _name_={name_} qwOwnerID={qwOwnerID} eCittaNameType={eCittaNameType} dwSkillID={dwSkillID} dwSignetID={dwSignetID}/>;
			else
				topXml = <SCitta qwOwnerID={qwOwnerID} eCittaNameType={eCittaNameType} dwSkillID={dwSkillID} dwSignetID={dwSignetID}/>;
			if(oAttrVec != null)
			{
				var oAttrVecXml:XML = <Vec_SFtAttrMod _name_="oAttrVec"/>;
				for each(var s1:SFtAttrMod in oAttrVec)
					oAttrVecXml.appendChild(s1.toXML());
				topXml.appendChild(oAttrVecXml);
			}
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.qwOwnerID = qwOwnerID;
			obj_.eCittaNameType = eCittaNameType;
			obj_.oAttrVec = oAttrVec;
			obj_.dwSkillID = dwSkillID;
			obj_.dwSignetID = dwSignetID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCitta
		{
			var s_:SCitta = new SCitta();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var eCittaNameType:uint = bytes.readUnsignedByte();
			s_.eCittaNameType = eCittaNameType;
			var oAttrVec:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes);
			s_.oAttrVec = oAttrVec;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var dwSignetID:uint = bytes.readUnsignedInt();
			s_.dwSignetID = dwSignetID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCitta>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCitta> = new Vector.<SCitta>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCitta = SCitta.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeByte(eCittaNameType);
			SFtAttrMod.vectorToByteArray(oAttrVec, bytes);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeUnsignedInt(dwSignetID);
		}

		public static function vectorToByteArray(vec:Vector.<SCitta>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCitta in vec)
				s.toByteArray(bytes);
		}
	}
}
