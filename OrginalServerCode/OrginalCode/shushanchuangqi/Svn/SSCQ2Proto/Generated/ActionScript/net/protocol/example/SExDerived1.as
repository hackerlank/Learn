/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SExDerived1.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 结构体子类型1示例
	 */
	public class SExDerived1 extends SExBase
	{
		public var byMember3:uint; //(无符号16位整数)成员3
		public var qwMember4:BigInteger; //(有符号64位整数)成员4

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SExBase.eType_SExDerived1;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SExDerived1 _name_={name_} byMember3={byMember3} qwMember4={qwMember4}/>;
			else
				topXml = <SExDerived1 byMember3={byMember3} qwMember4={qwMember4}/>;
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
			obj_.byMember3 = byMember3;
			obj_.qwMember4 = qwMember4;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SExDerived1
		{
			var s_:SExDerived1 = new SExDerived1();
			var base_:SExBase = SExBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var byMember3:uint = bytes.readUnsignedShort();
			s_.byMember3 = byMember3;
			var qwMember4:BigInteger = BytesUtil.readInt64(bytes);
			s_.qwMember4 = qwMember4;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SExDerived1
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SExDerived1;
			switch(eType)
			{
				case EType_SExBase.eType_SExDerived1:
					s = SExDerived1.fromByteArray(bytes);
					break;
				case EType_SExBase.eType_SExDescend3:
					s = SExDescend3.fromByteArray(bytes);
					break;
				case EType_SExBase.eType_SExDescend4:
					s = SExDescend4.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SExBase:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SExDerived1>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExDerived1> = new Vector.<SExDerived1>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExDerived1 = SExDerived1.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SExDerived1>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExDerived1> = new Vector.<SExDerived1>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExDerived1 = SExDerived1.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(byMember3);
			BytesUtil.writeInt64(bytes, qwMember4);
		}

		public override function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SExDerived1>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExDerived1 in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SExDerived1>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExDerived1 in vec)
				s.superToByteArray(bytes);
		}
	}
}
