/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAttrInfo.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 属性信息表
	 */
	public final class SAttrInfo
	{
		public var dwAttrType:uint; //(无符号32位整数)属性类型id
		public var fAttrValue:Number; //(Float)属性值

		/**
		 * 辅助创建函数
		 */
		public static function create(dwAttrType:uint, fAttrValue:Number):SAttrInfo
		{
			var s_:SAttrInfo = new SAttrInfo();
			s_.dwAttrType = dwAttrType;
			s_.fAttrValue = fAttrValue;
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
				topXml = <SAttrInfo _name_={name_} dwAttrType={dwAttrType} fAttrValue={fAttrValue}/>;
			else
				topXml = <SAttrInfo dwAttrType={dwAttrType} fAttrValue={fAttrValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwAttrType = dwAttrType;
			obj_.fAttrValue = fAttrValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAttrInfo
		{
			var s_:SAttrInfo = new SAttrInfo();
			var dwAttrType:uint = bytes.readUnsignedInt();
			s_.dwAttrType = dwAttrType;
			var fAttrValue:Number = bytes.readFloat();
			s_.fAttrValue = fAttrValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAttrInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAttrInfo> = new Vector.<SAttrInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAttrInfo = SAttrInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwAttrType);
			bytes.writeFloat(fAttrValue);
		}

		public static function vectorToByteArray(vec:Vector.<SAttrInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAttrInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
