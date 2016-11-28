/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SClient.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 只在客户端生成
	 */
	public final class SClient
	{
		public var dwValue:uint; //(无符号32位整数)成员

		/**
		 * 辅助创建函数
		 */
		public static function create(dwValue:uint):SClient
		{
			var s_:SClient = new SClient();
			s_.dwValue = dwValue;
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
				topXml = <SClient _name_={name_} dwValue={dwValue}/>;
			else
				topXml = <SClient dwValue={dwValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SClient
		{
			var s_:SClient = new SClient();
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SClient> = new Vector.<SClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SClient = SClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SClient in vec)
				s.toByteArray(bytes);
		}
	}
}
