/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STrump.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 法宝信息
	 */
	public final class STrump extends SItem
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)拥有者RoleID
		public var byActived:uint; //(无符号8位整数)
		public var byUsed:uint; //(无符号8位整数)法宝是否出战
		public var dwExp:uint; //(无符号32位整数)法宝祭炼值
		public var wLevel:uint; //(无符号16位整数)法宝祭炼等级
		public var wRank:uint; //(无符号16位整数)法宝祭炼阶数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SItem.eType_STrump;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STrump _name_={name_} qwRoleID={qwRoleID} byActived={byActived} byUsed={byUsed} dwExp={dwExp} wLevel={wLevel}
				 wRank={wRank}/>;
			else
				topXml = <STrump qwRoleID={qwRoleID} byActived={byActived} byUsed={byUsed} dwExp={dwExp} wLevel={wLevel}
				 wRank={wRank}/>;
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
			obj_.qwRoleID = qwRoleID;
			obj_.byActived = byActived;
			obj_.byUsed = byUsed;
			obj_.dwExp = dwExp;
			obj_.wLevel = wLevel;
			obj_.wRank = wRank;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STrump
		{
			var s_:STrump = new STrump();
			var base_:SItem = SItem.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byActived:uint = bytes.readUnsignedByte();
			s_.byActived = byActived;
			var byUsed:uint = bytes.readUnsignedByte();
			s_.byUsed = byUsed;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var wRank:uint = bytes.readUnsignedShort();
			s_.wRank = wRank;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STrump>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STrump> = new Vector.<STrump>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STrump = STrump.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byActived);
			bytes.writeByte(byUsed);
			bytes.writeUnsignedInt(dwExp);
			bytes.writeShort(wLevel);
			bytes.writeShort(wRank);
		}

		public static function vectorToByteArray(vec:Vector.<STrump>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STrump in vec)
				s.toByteArray(bytes);
		}
	}
}
