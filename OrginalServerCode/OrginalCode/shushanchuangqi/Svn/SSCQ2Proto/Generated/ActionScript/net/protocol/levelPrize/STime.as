/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STime.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活动配置时间
	 */
	public final class STime
	{
		public var dwAdvTime:uint; //(无符号32位整数)活动预告时间
		public var dwBeginTime:uint; //(无符号32位整数)活动开始时间
		public var dwEndTime:uint; //(无符号32位整数)活动结束时间
		public var dwRetainTime:uint; //(无符号32位整数)活动预留时间

		/**
		 * 辅助创建函数
		 */
		public static function create(dwAdvTime:uint, dwBeginTime:uint, dwEndTime:uint, dwRetainTime:uint):STime
		{
			var s_:STime = new STime();
			s_.dwAdvTime = dwAdvTime;
			s_.dwBeginTime = dwBeginTime;
			s_.dwEndTime = dwEndTime;
			s_.dwRetainTime = dwRetainTime;
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
				topXml = <STime _name_={name_} dwAdvTime={dwAdvTime} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwRetainTime={dwRetainTime}/>;
			else
				topXml = <STime dwAdvTime={dwAdvTime} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwRetainTime={dwRetainTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwAdvTime = dwAdvTime;
			obj_.dwBeginTime = dwBeginTime;
			obj_.dwEndTime = dwEndTime;
			obj_.dwRetainTime = dwRetainTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STime
		{
			var s_:STime = new STime();
			var dwAdvTime:uint = bytes.readUnsignedInt();
			s_.dwAdvTime = dwAdvTime;
			var dwBeginTime:uint = bytes.readUnsignedInt();
			s_.dwBeginTime = dwBeginTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			var dwRetainTime:uint = bytes.readUnsignedInt();
			s_.dwRetainTime = dwRetainTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STime>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STime> = new Vector.<STime>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STime = STime.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwAdvTime);
			bytes.writeUnsignedInt(dwBeginTime);
			bytes.writeUnsignedInt(dwEndTime);
			bytes.writeUnsignedInt(dwRetainTime);
		}

		public static function vectorToByteArray(vec:Vector.<STime>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STime in vec)
				s.toByteArray(bytes);
		}
	}
}
