/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityTime.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * Center2Game 活动时间同步
	 */
	public final class SActivityTime
	{
		public var dwActID:uint; //(无符号32位整数)活动ID
		public var dwAlarm:uint; //(无符号32位整数)公告
		public var dwReady:uint; //(无符号32位整数)准备
		public var dwBegin:uint; //(无符号32位整数)开始
		public var dwEnd:uint; //(无符号32位整数)结束

		/**
		 * 辅助创建函数
		 */
		public static function create(dwActID:uint, dwAlarm:uint, dwReady:uint, dwBegin:uint, dwEnd:uint):SActivityTime
		{
			var s_:SActivityTime = new SActivityTime();
			s_.dwActID = dwActID;
			s_.dwAlarm = dwAlarm;
			s_.dwReady = dwReady;
			s_.dwBegin = dwBegin;
			s_.dwEnd = dwEnd;
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
				topXml = <SActivityTime _name_={name_} dwActID={dwActID} dwAlarm={dwAlarm} dwReady={dwReady} dwBegin={dwBegin} dwEnd={dwEnd}/>;
			else
				topXml = <SActivityTime dwActID={dwActID} dwAlarm={dwAlarm} dwReady={dwReady} dwBegin={dwBegin} dwEnd={dwEnd}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwActID = dwActID;
			obj_.dwAlarm = dwAlarm;
			obj_.dwReady = dwReady;
			obj_.dwBegin = dwBegin;
			obj_.dwEnd = dwEnd;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityTime
		{
			var s_:SActivityTime = new SActivityTime();
			var dwActID:uint = bytes.readUnsignedInt();
			s_.dwActID = dwActID;
			var dwAlarm:uint = bytes.readUnsignedInt();
			s_.dwAlarm = dwAlarm;
			var dwReady:uint = bytes.readUnsignedInt();
			s_.dwReady = dwReady;
			var dwBegin:uint = bytes.readUnsignedInt();
			s_.dwBegin = dwBegin;
			var dwEnd:uint = bytes.readUnsignedInt();
			s_.dwEnd = dwEnd;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityTime>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityTime> = new Vector.<SActivityTime>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityTime = SActivityTime.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwActID);
			bytes.writeUnsignedInt(dwAlarm);
			bytes.writeUnsignedInt(dwReady);
			bytes.writeUnsignedInt(dwBegin);
			bytes.writeUnsignedInt(dwEnd);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityTime>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityTime in vec)
				s.toByteArray(bytes);
		}
	}
}
