/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SExDerived2.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 结构体子类型2示例
	 */
	public final class SExDerived2 extends SExBase
	{
		public var dMember3:Number; //(Double)成员3
		public var bMember4:Boolean; //成员4

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SExBase.eType_SExDerived2;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SExDerived2 _name_={name_} dMember3={dMember3} bMember4={bMember4}/>;
			else
				topXml = <SExDerived2 dMember3={dMember3} bMember4={bMember4}/>;
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
			obj_.dMember3 = dMember3;
			obj_.bMember4 = bMember4;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SExDerived2
		{
			var s_:SExDerived2 = new SExDerived2();
			var base_:SExBase = SExBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dMember3:Number = bytes.readDouble();
			s_.dMember3 = dMember3;
			var bMember4:Boolean = bytes.readBoolean();
			s_.bMember4 = bMember4;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SExDerived2>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExDerived2> = new Vector.<SExDerived2>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExDerived2 = SExDerived2.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeDouble(dMember3);
			bytes.writeBoolean(bMember4);
		}

		public static function vectorToByteArray(vec:Vector.<SExDerived2>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExDerived2 in vec)
				s.toByteArray(bytes);
		}
	}
}
