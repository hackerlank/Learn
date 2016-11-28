/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMaxShuffleInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 最大洗练属性
	 */
	public final class SMaxShuffleInfo
	{
		public var dwType:uint; //(无符号32位整数)洗炼类型
		public var dwValue:uint; //(无符号32位整数)洗炼数值

		/**
		 * 辅助创建函数
		 */
		public static function create(dwType:uint, dwValue:uint):SMaxShuffleInfo
		{
			var s_:SMaxShuffleInfo = new SMaxShuffleInfo();
			s_.dwType = dwType;
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
				topXml = <SMaxShuffleInfo _name_={name_} dwType={dwType} dwValue={dwValue}/>;
			else
				topXml = <SMaxShuffleInfo dwType={dwType} dwValue={dwValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwType = dwType;
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMaxShuffleInfo
		{
			var s_:SMaxShuffleInfo = new SMaxShuffleInfo();
			var dwType:uint = bytes.readUnsignedInt();
			s_.dwType = dwType;
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMaxShuffleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMaxShuffleInfo> = new Vector.<SMaxShuffleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMaxShuffleInfo = SMaxShuffleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwType);
			bytes.writeUnsignedInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SMaxShuffleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMaxShuffleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
