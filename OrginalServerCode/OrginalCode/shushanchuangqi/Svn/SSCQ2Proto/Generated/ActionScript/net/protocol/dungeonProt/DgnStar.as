/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    DgnStar.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 副本星级信息
	 */
	public final class DgnStar
	{
		public var wDgnId:uint; //(无符号16位整数)副本ID
		public var byStar:uint; //(无符号8位整数)星级
		public var dwFinishTimesToday:uint; //(无符号32位整数)今日完成次数
		public var dwBuyTimesToday:uint; //(无符号32位整数)今日购买次数
		public var dwBuyTimes:uint; //(无符号32位整数)购买的总次数
		public var dwCompleteTimes:uint; //(无符号32位整数)总通关次数

		/**
		 * 辅助创建函数
		 */
		public static function create(wDgnId:uint, byStar:uint, dwFinishTimesToday:uint, dwBuyTimesToday:uint, dwBuyTimes:uint, 
			dwCompleteTimes:uint):DgnStar
		{
			var s_:DgnStar = new DgnStar();
			s_.wDgnId = wDgnId;
			s_.byStar = byStar;
			s_.dwFinishTimesToday = dwFinishTimesToday;
			s_.dwBuyTimesToday = dwBuyTimesToday;
			s_.dwBuyTimes = dwBuyTimes;
			s_.dwCompleteTimes = dwCompleteTimes;
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
				topXml = <DgnStar _name_={name_} wDgnId={wDgnId} byStar={byStar} dwFinishTimesToday={dwFinishTimesToday} dwBuyTimesToday={dwBuyTimesToday} dwBuyTimes={dwBuyTimes}
				 dwCompleteTimes={dwCompleteTimes}/>;
			else
				topXml = <DgnStar wDgnId={wDgnId} byStar={byStar} dwFinishTimesToday={dwFinishTimesToday} dwBuyTimesToday={dwBuyTimesToday} dwBuyTimes={dwBuyTimes}
				 dwCompleteTimes={dwCompleteTimes}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wDgnId = wDgnId;
			obj_.byStar = byStar;
			obj_.dwFinishTimesToday = dwFinishTimesToday;
			obj_.dwBuyTimesToday = dwBuyTimesToday;
			obj_.dwBuyTimes = dwBuyTimes;
			obj_.dwCompleteTimes = dwCompleteTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):DgnStar
		{
			var s_:DgnStar = new DgnStar();
			var wDgnId:uint = bytes.readUnsignedShort();
			s_.wDgnId = wDgnId;
			var byStar:uint = bytes.readUnsignedByte();
			s_.byStar = byStar;
			var dwFinishTimesToday:uint = bytes.readUnsignedInt();
			s_.dwFinishTimesToday = dwFinishTimesToday;
			var dwBuyTimesToday:uint = bytes.readUnsignedInt();
			s_.dwBuyTimesToday = dwBuyTimesToday;
			var dwBuyTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyTimes = dwBuyTimes;
			var dwCompleteTimes:uint = bytes.readUnsignedInt();
			s_.dwCompleteTimes = dwCompleteTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<DgnStar>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<DgnStar> = new Vector.<DgnStar>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:DgnStar = DgnStar.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wDgnId);
			bytes.writeByte(byStar);
			bytes.writeUnsignedInt(dwFinishTimesToday);
			bytes.writeUnsignedInt(dwBuyTimesToday);
			bytes.writeUnsignedInt(dwBuyTimes);
			bytes.writeUnsignedInt(dwCompleteTimes);
		}

		public static function vectorToByteArray(vec:Vector.<DgnStar>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:DgnStar in vec)
				s.toByteArray(bytes);
		}
	}
}
