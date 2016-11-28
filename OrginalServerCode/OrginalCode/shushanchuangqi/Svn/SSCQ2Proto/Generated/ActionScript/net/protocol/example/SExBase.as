/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SExBase.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 结构体父类型示例
	 */
	public class SExBase
	{
		public var member1:uint = 1; //(无符号32位整数)成员1
		public var vecMember2:Vector.<String>; //成员2

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SExBase.eType_SExBase;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SExBase _name_={name_} member1={member1}/>;
			else
				topXml = <SExBase member1={member1}/>;
			if(vecMember2 != null)
			{
				var vecMember2Xml:XML = <Vec_string _name_="vecMember2"/>;
				var text1:String = "";
				for each(var value1:String in vecMember2)
					text1 += "[" + value1 + "]";
				vecMember2Xml.appendChild(text1);
				topXml.appendChild(vecMember2Xml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.member1 = member1;
			obj_.vecMember2 = vecMember2;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SExBase
		{
			var s_:SExBase = new SExBase();
			var member1:uint = bytes.readUnsignedInt();
			s_.member1 = member1;
			var vecMember2:Vector.<String> = BytesUtil.readVecString(bytes);
			s_.vecMember2 = vecMember2;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SExBase
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SExBase;
			switch(eType)
			{
				case EType_SExBase.eType_SExBase:
					s = SExBase.fromByteArray(bytes);
					break;
				case EType_SExBase.eType_SExDerived1:
					s = SExDerived1.fromByteArray(bytes);
					break;
				case EType_SExBase.eType_SExDerived2:
					s = SExDerived2.fromByteArray(bytes);
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

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SExBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExBase> = new Vector.<SExBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExBase = SExBase.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SExBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SExBase> = new Vector.<SExBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SExBase = SExBase.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(member1);
			BytesUtil.writeVecString(bytes, vecMember2);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SExBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExBase in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SExBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SExBase in vec)
				s.superToByteArray(bytes);
		}
	}
}
