/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SExDescend3.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 结构体子类型3示例
	 */
	public final class SExDescend3 extends SExDerived1
	{
		public var base:SExBase; //成员5
		public var s:SExDerived1; //成员6
		public var vecExDerive:Vector.<SExDerived1>; //成员7
		public var vecExBase:Vector.<SExBase>; //成员8

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SExBase.eType_SExDescend3;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SExDescend3 _name_={name_}/>;
			else
				topXml = <SExDescend3/>;
			if(base != null)
				topXml.appendChild(base.toXML("base"));
			if(s != null)
				topXml.appendChild(s.toXML("s"));
			if(vecExDerive != null)
			{
				var vecExDeriveXml:XML = <Vec_SExDerived1 _name_="vecExDerive"/>;
				for each(var s3:SExDerived1 in vecExDerive)
					vecExDeriveXml.appendChild(s3.toXML());
				topXml.appendChild(vecExDeriveXml);
			}
			if(vecExBase != null)
			{
				var vecExBaseXml:XML = <Vec_SExBase _name_="vecExBase"/>;
				for each(var s4:SExBase in vecExBase)
					vecExBaseXml.appendChild(s4.toXML());
				topXml.appendChild(vecExBaseXml);
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
			obj_.base = base;
			obj_.s = s;
			obj_.vecExDerive = vecExDerive;
			obj_.vecExBase = vecExBase;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SExDescend3
		{
			var s_:SExDescend3 = new SExDescend3();
			var base_:SExDerived1 = SExDerived1.fromByteArray(bytes);
			base_.copyTo(s_);
			var base:SExBase = SExBase.superFromByteArray(bytes);
			s_.base = base;
			var s:SExDerived1 = SExDerived1.superFromByteArray(bytes);
			s_.s = s;
			var vecExDerive:Vector.<SExDerived1> = SExDerived1.superVectorFromByteArray(bytes);
			s_.vecExDerive = vecExDerive;
			var vecExBase:Vector.<SExBase> = SExBase.superVectorFromByteArray(bytes);
			s_.vecExBase = vecExBase;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SExDescend3>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExDescend3> = new Vector.<SExDescend3>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExDescend3 = SExDescend3.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			base.superToByteArray(bytes);
			s.superToByteArray(bytes);
			SExDerived1.superVectorToByteArray(vecExDerive, bytes);
			SExBase.superVectorToByteArray(vecExBase, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SExDescend3>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExDescend3 in vec)
				s.toByteArray(bytes);
		}
	}
}
