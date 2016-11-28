/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SVIPData.as
//  Purpose:      VIP特权相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 开启VIP特权数据结构
	 */
	public final class SVIPData
	{
		public var dwMonthCardEndTime:uint; //(无符号32位整数)月卡结束时间
		public var dwDayPack:uint; //(无符号32位整数)VIP特权每日礼包领取状态
		public var dwLvlAward:uint; //(无符号32位整数)VIP特权等级奖励领取状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwMonthCardEndTime:uint, dwDayPack:uint, dwLvlAward:uint):SVIPData
		{
			var s_:SVIPData = new SVIPData();
			s_.dwMonthCardEndTime = dwMonthCardEndTime;
			s_.dwDayPack = dwDayPack;
			s_.dwLvlAward = dwLvlAward;
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
				topXml = <SVIPData _name_={name_} dwMonthCardEndTime={dwMonthCardEndTime} dwDayPack={dwDayPack} dwLvlAward={dwLvlAward}/>;
			else
				topXml = <SVIPData dwMonthCardEndTime={dwMonthCardEndTime} dwDayPack={dwDayPack} dwLvlAward={dwLvlAward}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwMonthCardEndTime = dwMonthCardEndTime;
			obj_.dwDayPack = dwDayPack;
			obj_.dwLvlAward = dwLvlAward;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SVIPData
		{
			var s_:SVIPData = new SVIPData();
			var dwMonthCardEndTime:uint = bytes.readUnsignedInt();
			s_.dwMonthCardEndTime = dwMonthCardEndTime;
			var dwDayPack:uint = bytes.readUnsignedInt();
			s_.dwDayPack = dwDayPack;
			var dwLvlAward:uint = bytes.readUnsignedInt();
			s_.dwLvlAward = dwLvlAward;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SVIPData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SVIPData> = new Vector.<SVIPData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SVIPData = SVIPData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwMonthCardEndTime);
			bytes.writeUnsignedInt(dwDayPack);
			bytes.writeUnsignedInt(dwLvlAward);
		}

		public static function vectorToByteArray(vec:Vector.<SVIPData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SVIPData in vec)
				s.toByteArray(bytes);
		}
	}
}
