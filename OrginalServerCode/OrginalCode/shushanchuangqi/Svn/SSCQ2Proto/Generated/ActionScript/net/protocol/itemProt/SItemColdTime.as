/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemColdTime.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家道具冷却时间
	 */
	public final class SItemColdTime
	{
		public var wID:uint; //(无符号16位整数)冷却ID
		public var dwTime:uint; //(无符号32位整数)冷却到期时间

		/**
		 * 辅助创建函数
		 */
		public static function create(wID:uint, dwTime:uint):SItemColdTime
		{
			var s_:SItemColdTime = new SItemColdTime();
			s_.wID = wID;
			s_.dwTime = dwTime;
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
				topXml = <SItemColdTime _name_={name_} wID={wID} dwTime={dwTime}/>;
			else
				topXml = <SItemColdTime wID={wID} dwTime={dwTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wID = wID;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemColdTime
		{
			var s_:SItemColdTime = new SItemColdTime();
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemColdTime>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemColdTime> = new Vector.<SItemColdTime>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemColdTime = SItemColdTime.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wID);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<SItemColdTime>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemColdTime in vec)
				s.toByteArray(bytes);
		}
	}
}
