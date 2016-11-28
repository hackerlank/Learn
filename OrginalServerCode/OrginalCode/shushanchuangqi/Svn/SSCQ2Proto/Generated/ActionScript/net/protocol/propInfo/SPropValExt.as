/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPropValExt.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 扩展属性信息
	 */
	public final class SPropValExt
	{
		public var ePropType:uint; //(枚举类型：EPropType)属性类型
		public var value:Number; //(Float)属性值，需要根据类型来转换
		public var ext:int; //(有符号32位整数)扩展值，不同用途作不同的解释

		/**
		 * 辅助创建函数
		 */
		public static function create(ePropType:uint, value:Number, ext:int):SPropValExt
		{
			var s_:SPropValExt = new SPropValExt();
			s_.ePropType = ePropType;
			s_.value = value;
			s_.ext = ext;
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
				topXml = <SPropValExt _name_={name_} ePropType={ePropType} value={value} ext={ext}/>;
			else
				topXml = <SPropValExt ePropType={ePropType} value={value} ext={ext}/>;
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
			obj_.ext = ext;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPropValExt
		{
			var s_:SPropValExt = new SPropValExt();
			var ePropType:uint = bytes.readUnsignedShort();
			s_.ePropType = ePropType;
			var value:Number = bytes.readFloat();
			s_.value = value;
			var ext:int = bytes.readInt();
			s_.ext = ext;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPropValExt>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPropValExt> = new Vector.<SPropValExt>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPropValExt = SPropValExt.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(ePropType);
			bytes.writeFloat(value);
			bytes.writeInt(ext);
		}

		public static function vectorToByteArray(vec:Vector.<SPropValExt>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPropValExt in vec)
				s.toByteArray(bytes);
		}
	}
}
