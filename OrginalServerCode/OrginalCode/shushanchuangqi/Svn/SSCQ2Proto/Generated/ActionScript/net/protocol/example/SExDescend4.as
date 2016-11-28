/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SExDescend4.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 结构体子类型4示例
	 */
	public final class SExDescend4 extends SExDerived1
	{
		public var wMember5:uint; //(无符号16位整数)成员5
		public var qwMember6:BigInteger; //(有符号64位整数)成员6
		public var vecExDesc:Vector.<SExDescend3>; //成员7

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SExBase.eType_SExDescend4;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SExDescend4 _name_={name_} wMember5={wMember5} qwMember6={qwMember6}/>;
			else
				topXml = <SExDescend4 wMember5={wMember5} qwMember6={qwMember6}/>;
			if(vecExDesc != null)
			{
				var vecExDescXml:XML = <Vec_SExDescend3 _name_="vecExDesc"/>;
				for each(var s1:SExDescend3 in vecExDesc)
					vecExDescXml.appendChild(s1.toXML());
				topXml.appendChild(vecExDescXml);
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
			obj_.wMember5 = wMember5;
			obj_.qwMember6 = qwMember6;
			obj_.vecExDesc = vecExDesc;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SExDescend4
		{
			var s_:SExDescend4 = new SExDescend4();
			var base_:SExDerived1 = SExDerived1.fromByteArray(bytes);
			base_.copyTo(s_);
			var wMember5:uint = bytes.readUnsignedShort();
			s_.wMember5 = wMember5;
			var qwMember6:BigInteger = BytesUtil.readInt64(bytes);
			s_.qwMember6 = qwMember6;
			var vecExDesc:Vector.<SExDescend3> = SExDescend3.vectorFromByteArray(bytes);
			s_.vecExDesc = vecExDesc;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SExDescend4>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExDescend4> = new Vector.<SExDescend4>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExDescend4 = SExDescend4.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wMember5);
			BytesUtil.writeInt64(bytes, qwMember6);
			SExDescend3.vectorToByteArray(vecExDesc, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SExDescend4>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExDescend4 in vec)
				s.toByteArray(bytes);
		}
	}
}
