/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPropQWValExt.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 扩展属性信息
	 */
	public final class SPropQWValExt
	{
		public var ePropType:uint; //(枚举类型：EPropType)属性类型
		public var value:BigInteger; //(无符号64位整数)属性值，需要根据类型来转换
		public var ext:int; //(有符号32位整数)扩展值，不同用途作不同的解释

		/**
		 * 辅助创建函数
		 */
		public static function create(ePropType:uint, value:BigInteger, ext:int):SPropQWValExt
		{
			var s_:SPropQWValExt = new SPropQWValExt();
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
				topXml = <SPropQWValExt _name_={name_} ePropType={ePropType} value={value} ext={ext}/>;
			else
				topXml = <SPropQWValExt ePropType={ePropType} value={value} ext={ext}/>;
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

		public static function fromByteArray(bytes:ByteArray):SPropQWValExt
		{
			var s_:SPropQWValExt = new SPropQWValExt();
			var ePropType:uint = bytes.readUnsignedShort();
			s_.ePropType = ePropType;
			var value:BigInteger = BytesUtil.readUInt64(bytes);
			s_.value = value;
			var ext:int = bytes.readInt();
			s_.ext = ext;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPropQWValExt>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPropQWValExt> = new Vector.<SPropQWValExt>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPropQWValExt = SPropQWValExt.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(ePropType);
			BytesUtil.writeUInt64(bytes, value);
			bytes.writeInt(ext);
		}

		public static function vectorToByteArray(vec:Vector.<SPropQWValExt>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPropQWValExt in vec)
				s.toByteArray(bytes);
		}
	}
}
