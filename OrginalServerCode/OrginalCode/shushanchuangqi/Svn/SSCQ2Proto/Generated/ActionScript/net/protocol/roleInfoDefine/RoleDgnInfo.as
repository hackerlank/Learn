/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleDgnInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eTypePlayerDgn：剧情副本，特定日期副本可以考虑删除
	 */
	public final class RoleDgnInfo
	{
		public var dwDgnType:uint; //(无符号32位整数)副本类型
		public var dwLastEnterTimer:uint; //(无符号32位整数)最近副本支付代价时间
		public var byCost:uint; //(无符号8位整数)副本支付代价,是否没有消费,0表示已经消费
		public var dwEnterTimesAppend:uint; //(无符号32位整数)额外增加的副本进入次数
		public var dwAppendEndTimer:uint; //(无符号32位整数)额外增加的副本进入次数的到期时间
		public var dwEnterTimes:uint; //(无符号32位整数)当前副本进入次数
		public var dwLastCompleteTimer:uint; //(无符号32位整数)最近副本通过时间
		public var dwCompleteTimes:uint; //(无符号32位整数)副本通过次数，通过就记录下
		public var wMinTurns:uint; //(无符号16位整数)通过的最少回合数
		public var dwBuyTimer:uint; //(无符号32位整数)最近购买的时间
		public var dwBuyTimesToday:uint; //(无符号32位整数)当天购买的次数
		public var dwFinishTimesToday:uint; //(无符号32位整数)今日完成副本次数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwDgnType:uint, dwLastEnterTimer:uint, byCost:uint, dwEnterTimesAppend:uint, dwAppendEndTimer:uint, 
			dwEnterTimes:uint, dwLastCompleteTimer:uint, dwCompleteTimes:uint, wMinTurns:uint, dwBuyTimer:uint, 
			dwBuyTimesToday:uint, dwFinishTimesToday:uint):RoleDgnInfo
		{
			var s_:RoleDgnInfo = new RoleDgnInfo();
			s_.dwDgnType = dwDgnType;
			s_.dwLastEnterTimer = dwLastEnterTimer;
			s_.byCost = byCost;
			s_.dwEnterTimesAppend = dwEnterTimesAppend;
			s_.dwAppendEndTimer = dwAppendEndTimer;
			s_.dwEnterTimes = dwEnterTimes;
			s_.dwLastCompleteTimer = dwLastCompleteTimer;
			s_.dwCompleteTimes = dwCompleteTimes;
			s_.wMinTurns = wMinTurns;
			s_.dwBuyTimer = dwBuyTimer;
			s_.dwBuyTimesToday = dwBuyTimesToday;
			s_.dwFinishTimesToday = dwFinishTimesToday;
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
				topXml = <RoleDgnInfo _name_={name_} dwDgnType={dwDgnType} dwLastEnterTimer={dwLastEnterTimer} byCost={byCost} dwEnterTimesAppend={dwEnterTimesAppend} dwAppendEndTimer={dwAppendEndTimer}
				 dwEnterTimes={dwEnterTimes} dwLastCompleteTimer={dwLastCompleteTimer} dwCompleteTimes={dwCompleteTimes} wMinTurns={wMinTurns} dwBuyTimer={dwBuyTimer}
				 dwBuyTimesToday={dwBuyTimesToday} dwFinishTimesToday={dwFinishTimesToday}/>;
			else
				topXml = <RoleDgnInfo dwDgnType={dwDgnType} dwLastEnterTimer={dwLastEnterTimer} byCost={byCost} dwEnterTimesAppend={dwEnterTimesAppend} dwAppendEndTimer={dwAppendEndTimer}
				 dwEnterTimes={dwEnterTimes} dwLastCompleteTimer={dwLastCompleteTimer} dwCompleteTimes={dwCompleteTimes} wMinTurns={wMinTurns} dwBuyTimer={dwBuyTimer}
				 dwBuyTimesToday={dwBuyTimesToday} dwFinishTimesToday={dwFinishTimesToday}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwDgnType = dwDgnType;
			obj_.dwLastEnterTimer = dwLastEnterTimer;
			obj_.byCost = byCost;
			obj_.dwEnterTimesAppend = dwEnterTimesAppend;
			obj_.dwAppendEndTimer = dwAppendEndTimer;
			obj_.dwEnterTimes = dwEnterTimes;
			obj_.dwLastCompleteTimer = dwLastCompleteTimer;
			obj_.dwCompleteTimes = dwCompleteTimes;
			obj_.wMinTurns = wMinTurns;
			obj_.dwBuyTimer = dwBuyTimer;
			obj_.dwBuyTimesToday = dwBuyTimesToday;
			obj_.dwFinishTimesToday = dwFinishTimesToday;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleDgnInfo
		{
			var s_:RoleDgnInfo = new RoleDgnInfo();
			var dwDgnType:uint = bytes.readUnsignedInt();
			s_.dwDgnType = dwDgnType;
			var dwLastEnterTimer:uint = bytes.readUnsignedInt();
			s_.dwLastEnterTimer = dwLastEnterTimer;
			var byCost:uint = bytes.readUnsignedByte();
			s_.byCost = byCost;
			var dwEnterTimesAppend:uint = bytes.readUnsignedInt();
			s_.dwEnterTimesAppend = dwEnterTimesAppend;
			var dwAppendEndTimer:uint = bytes.readUnsignedInt();
			s_.dwAppendEndTimer = dwAppendEndTimer;
			var dwEnterTimes:uint = bytes.readUnsignedInt();
			s_.dwEnterTimes = dwEnterTimes;
			var dwLastCompleteTimer:uint = bytes.readUnsignedInt();
			s_.dwLastCompleteTimer = dwLastCompleteTimer;
			var dwCompleteTimes:uint = bytes.readUnsignedInt();
			s_.dwCompleteTimes = dwCompleteTimes;
			var wMinTurns:uint = bytes.readUnsignedShort();
			s_.wMinTurns = wMinTurns;
			var dwBuyTimer:uint = bytes.readUnsignedInt();
			s_.dwBuyTimer = dwBuyTimer;
			var dwBuyTimesToday:uint = bytes.readUnsignedInt();
			s_.dwBuyTimesToday = dwBuyTimesToday;
			var dwFinishTimesToday:uint = bytes.readUnsignedInt();
			s_.dwFinishTimesToday = dwFinishTimesToday;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleDgnInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleDgnInfo> = new Vector.<RoleDgnInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleDgnInfo = RoleDgnInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwDgnType);
			bytes.writeUnsignedInt(dwLastEnterTimer);
			bytes.writeByte(byCost);
			bytes.writeUnsignedInt(dwEnterTimesAppend);
			bytes.writeUnsignedInt(dwAppendEndTimer);
			bytes.writeUnsignedInt(dwEnterTimes);
			bytes.writeUnsignedInt(dwLastCompleteTimer);
			bytes.writeUnsignedInt(dwCompleteTimes);
			bytes.writeShort(wMinTurns);
			bytes.writeUnsignedInt(dwBuyTimer);
			bytes.writeUnsignedInt(dwBuyTimesToday);
			bytes.writeUnsignedInt(dwFinishTimesToday);
		}

		public static function vectorToByteArray(vec:Vector.<RoleDgnInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleDgnInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
