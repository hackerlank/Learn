/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSevenConsumeAct.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 七日消费活动信息
	 */
	public final class SSevenConsumeAct
	{
		public var dwBeginTime:uint; //(无符号32位整数)活动开始时间
		public var dwEndTime:uint; //(无符号32位整数)活动结束时间
		public var dwConsume:uint; //(无符号32位整数)七日总消费仙石数
		public var byInfo:uint; //(无符号8位整数)奖励领取状态信息(从低到高按位取,1已领取 0未领取)

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBeginTime:uint, dwEndTime:uint, dwConsume:uint, byInfo:uint):SSevenConsumeAct
		{
			var s_:SSevenConsumeAct = new SSevenConsumeAct();
			s_.dwBeginTime = dwBeginTime;
			s_.dwEndTime = dwEndTime;
			s_.dwConsume = dwConsume;
			s_.byInfo = byInfo;
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
				topXml = <SSevenConsumeAct _name_={name_} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwConsume={dwConsume} byInfo={byInfo}/>;
			else
				topXml = <SSevenConsumeAct dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwConsume={dwConsume} byInfo={byInfo}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBeginTime = dwBeginTime;
			obj_.dwEndTime = dwEndTime;
			obj_.dwConsume = dwConsume;
			obj_.byInfo = byInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSevenConsumeAct
		{
			var s_:SSevenConsumeAct = new SSevenConsumeAct();
			var dwBeginTime:uint = bytes.readUnsignedInt();
			s_.dwBeginTime = dwBeginTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			var dwConsume:uint = bytes.readUnsignedInt();
			s_.dwConsume = dwConsume;
			var byInfo:uint = bytes.readUnsignedByte();
			s_.byInfo = byInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSevenConsumeAct>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSevenConsumeAct> = new Vector.<SSevenConsumeAct>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSevenConsumeAct = SSevenConsumeAct.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBeginTime);
			bytes.writeUnsignedInt(dwEndTime);
			bytes.writeUnsignedInt(dwConsume);
			bytes.writeByte(byInfo);
		}

		public static function vectorToByteArray(vec:Vector.<SSevenConsumeAct>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSevenConsumeAct in vec)
				s.toByteArray(bytes);
		}
	}
}
