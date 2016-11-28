/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPropValue.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 属性信息
	 */
	public final class SPropValue
	{
		public var ePropType:uint; //(枚举类型：EPropType)属性类型
		public var value:uint; //(无符号32位整数)属性值，需要根据类型来转换

		/**
		 * 辅助创建函数
		 */
		public static function create(ePropType:uint, value:uint):SPropValue
		{
			var s_:SPropValue = new SPropValue();
			s_.ePropType = ePropType;
			s_.value = value;
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
				topXml = <SPropValue _name_={name_} ePropType={ePropType} value={value}/>;
			else
				topXml = <SPropValue ePropType={ePropType} value={value}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.ePropType = ePropType;
			obj_.value = value;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPropValue
		{
			var s_:SPropValue = new SPropValue();
			var ePropType:uint = bytes.readUnsignedShort();
			s_.ePropType = ePropType;
			var value:uint = bytes.readUnsignedInt();
			s_.value = value;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPropValue>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPropValue> = new Vector.<SPropValue>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPropValue = SPropValue.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(ePropType);
			bytes.writeUnsignedInt(value);
		}

		public static function vectorToByteArray(vec:Vector.<SPropValue>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPropValue in vec)
				s.toByteArray(bytes);
		}
	}
}
