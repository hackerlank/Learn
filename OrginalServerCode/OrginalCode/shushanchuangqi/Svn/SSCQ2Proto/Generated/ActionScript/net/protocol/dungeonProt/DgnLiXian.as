/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    DgnLiXian.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 历险副本信息
	 */
	public final class DgnLiXian
	{
		public var dwFinishTimesToday:uint; //(无符号32位整数)今日完成次数
		public var dwBuyTimesToday:uint; //(无符号32位整数)今日购买次数
		public var dwBuyTimes:uint; //(无符号32位整数)购买的总次数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwFinishTimesToday:uint, dwBuyTimesToday:uint, dwBuyTimes:uint):DgnLiXian
		{
			var s_:DgnLiXian = new DgnLiXian();
			s_.dwFinishTimesToday = dwFinishTimesToday;
			s_.dwBuyTimesToday = dwBuyTimesToday;
			s_.dwBuyTimes = dwBuyTimes;
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
				topXml = <DgnLiXian _name_={name_} dwFinishTimesToday={dwFinishTimesToday} dwBuyTimesToday={dwBuyTimesToday} dwBuyTimes={dwBuyTimes}/>;
			else
				topXml = <DgnLiXian dwFinishTimesToday={dwFinishTimesToday} dwBuyTimesToday={dwBuyTimesToday} dwBuyTimes={dwBuyTimes}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwFinishTimesToday = dwFinishTimesToday;
			obj_.dwBuyTimesToday = dwBuyTimesToday;
			obj_.dwBuyTimes = dwBuyTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):DgnLiXian
		{
			var s_:DgnLiXian = new DgnLiXian();
			var dwFinishTimesToday:uint = bytes.readUnsignedInt();
			s_.dwFinishTimesToday = dwFinishTimesToday;
			var dwBuyTimesToday:uint = bytes.readUnsignedInt();
			s_.dwBuyTimesToday = dwBuyTimesToday;
			var dwBuyTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyTimes = dwBuyTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<DgnLiXian>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<DgnLiXian> = new Vector.<DgnLiXian>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:DgnLiXian = DgnLiXian.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwFinishTimesToday);
			bytes.writeUnsignedInt(dwBuyTimesToday);
			bytes.writeUnsignedInt(dwBuyTimes);
		}

		public static function vectorToByteArray(vec:Vector.<DgnLiXian>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:DgnLiXian in vec)
				s.toByteArray(bytes);
		}
	}
}
