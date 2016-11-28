/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAnswerTime.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 答题时间控制
	 */
	public final class SAnswerTime
	{
		public var dwReadTime:uint; //(无符号32位整数)玩家阅读时间
		public var dwAnswerTime:uint; //(无符号32位整数)玩家答题时间
		public var dwResultTime:uint; //(无符号32位整数)玩家显示结果时间
		public var dwEndTime:uint; //(无符号32位整数)玩家答题结束时间

		/**
		 * 辅助创建函数
		 */
		public static function create(dwReadTime:uint, dwAnswerTime:uint, dwResultTime:uint, dwEndTime:uint):SAnswerTime
		{
			var s_:SAnswerTime = new SAnswerTime();
			s_.dwReadTime = dwReadTime;
			s_.dwAnswerTime = dwAnswerTime;
			s_.dwResultTime = dwResultTime;
			s_.dwEndTime = dwEndTime;
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
				topXml = <SAnswerTime _name_={name_} dwReadTime={dwReadTime} dwAnswerTime={dwAnswerTime} dwResultTime={dwResultTime} dwEndTime={dwEndTime}/>;
			else
				topXml = <SAnswerTime dwReadTime={dwReadTime} dwAnswerTime={dwAnswerTime} dwResultTime={dwResultTime} dwEndTime={dwEndTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwReadTime = dwReadTime;
			obj_.dwAnswerTime = dwAnswerTime;
			obj_.dwResultTime = dwResultTime;
			obj_.dwEndTime = dwEndTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAnswerTime
		{
			var s_:SAnswerTime = new SAnswerTime();
			var dwReadTime:uint = bytes.readUnsignedInt();
			s_.dwReadTime = dwReadTime;
			var dwAnswerTime:uint = bytes.readUnsignedInt();
			s_.dwAnswerTime = dwAnswerTime;
			var dwResultTime:uint = bytes.readUnsignedInt();
			s_.dwResultTime = dwResultTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAnswerTime>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAnswerTime> = new Vector.<SAnswerTime>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAnswerTime = SAnswerTime.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwReadTime);
			bytes.writeUnsignedInt(dwAnswerTime);
			bytes.writeUnsignedInt(dwResultTime);
			bytes.writeUnsignedInt(dwEndTime);
		}

		public static function vectorToByteArray(vec:Vector.<SAnswerTime>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAnswerTime in vec)
				s.toByteArray(bytes);
		}
	}
}
