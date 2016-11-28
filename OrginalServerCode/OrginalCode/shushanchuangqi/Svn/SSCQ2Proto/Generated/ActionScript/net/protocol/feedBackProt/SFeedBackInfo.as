/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFeedBackInfo.as
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 回馈信息
	 */
	public final class SFeedBackInfo
	{
		public var dwActID:uint; //(无符号32位整数)活动id
		public var dwBeginTime:uint; //(无符号32位整数)开始时间
		public var dwEndTime:uint; //(无符号32位整数)结束时间
		public var dwTakePrizeMax:uint; //(无符号32位整数)可领奖次数
		public var dwTakePrizedCnt:uint; //(无符号32位整数)已领奖次数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwActID:uint, dwBeginTime:uint, dwEndTime:uint, dwTakePrizeMax:uint, dwTakePrizedCnt:uint):SFeedBackInfo
		{
			var s_:SFeedBackInfo = new SFeedBackInfo();
			s_.dwActID = dwActID;
			s_.dwBeginTime = dwBeginTime;
			s_.dwEndTime = dwEndTime;
			s_.dwTakePrizeMax = dwTakePrizeMax;
			s_.dwTakePrizedCnt = dwTakePrizedCnt;
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
				topXml = <SFeedBackInfo _name_={name_} dwActID={dwActID} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwTakePrizeMax={dwTakePrizeMax} dwTakePrizedCnt={dwTakePrizedCnt}/>;
			else
				topXml = <SFeedBackInfo dwActID={dwActID} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwTakePrizeMax={dwTakePrizeMax} dwTakePrizedCnt={dwTakePrizedCnt}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwActID = dwActID;
			obj_.dwBeginTime = dwBeginTime;
			obj_.dwEndTime = dwEndTime;
			obj_.dwTakePrizeMax = dwTakePrizeMax;
			obj_.dwTakePrizedCnt = dwTakePrizedCnt;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFeedBackInfo
		{
			var s_:SFeedBackInfo = new SFeedBackInfo();
			var dwActID:uint = bytes.readUnsignedInt();
			s_.dwActID = dwActID;
			var dwBeginTime:uint = bytes.readUnsignedInt();
			s_.dwBeginTime = dwBeginTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			var dwTakePrizeMax:uint = bytes.readUnsignedInt();
			s_.dwTakePrizeMax = dwTakePrizeMax;
			var dwTakePrizedCnt:uint = bytes.readUnsignedInt();
			s_.dwTakePrizedCnt = dwTakePrizedCnt;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFeedBackInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFeedBackInfo> = new Vector.<SFeedBackInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFeedBackInfo = SFeedBackInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwActID);
			bytes.writeUnsignedInt(dwBeginTime);
			bytes.writeUnsignedInt(dwEndTime);
			bytes.writeUnsignedInt(dwTakePrizeMax);
			bytes.writeUnsignedInt(dwTakePrizedCnt);
		}

		public static function vectorToByteArray(vec:Vector.<SFeedBackInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFeedBackInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
