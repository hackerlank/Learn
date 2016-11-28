/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SResource.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 资源列表
	 */
	public final class SResource
	{
		public var _eRes:uint; //(枚举类型：protoCommon.EMoneyType)资源(货币)类型
		public var _dwValue:uint; //(无符号32位整数)资源(货币)数量

		/**
		 * 辅助创建函数
		 */
		public static function create(_eRes:uint, _dwValue:uint):SResource
		{
			var s_:SResource = new SResource();
			s_._eRes = _eRes;
			s_._dwValue = _dwValue;
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
				topXml = <SResource _name_={name_} _eRes={_eRes} _dwValue={_dwValue}/>;
			else
				topXml = <SResource _eRes={_eRes} _dwValue={_dwValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_._eRes = _eRes;
			obj_._dwValue = _dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SResource
		{
			var s_:SResource = new SResource();
			var _eRes:uint = bytes.readUnsignedByte();
			s_._eRes = _eRes;
			var _dwValue:uint = bytes.readUnsignedInt();
			s_._dwValue = _dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SResource>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SResource> = new Vector.<SResource>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SResource = SResource.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(_eRes);
			bytes.writeUnsignedInt(_dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SResource>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SResource in vec)
				s.toByteArray(bytes);
		}
	}
}
