/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGetSweepInfo.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 客户段获取的扫荡信息
	 */
	public final class SGetSweepInfo
	{
		public var wDgnId:uint; //(无符号16位整数)扫荡副本实例
		public var dwReserverTimer:uint; //(无符号32位整数)剩余时间
		public var wCount:uint; //(无符号16位整数)剩余次数
		public var wMaxCount:uint; //(无符号16位整数)总的扫荡次数
		public var vecSweepItem:Vector.<SSweepItem>; //扫荡日志

		/**
		 * 辅助创建函数
		 */
		public static function create(wDgnId:uint, dwReserverTimer:uint, wCount:uint, wMaxCount:uint, vecSweepItem:Vector.<SSweepItem>):SGetSweepInfo
		{
			var s_:SGetSweepInfo = new SGetSweepInfo();
			s_.wDgnId = wDgnId;
			s_.dwReserverTimer = dwReserverTimer;
			s_.wCount = wCount;
			s_.wMaxCount = wMaxCount;
			s_.vecSweepItem = vecSweepItem;
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
				topXml = <SGetSweepInfo _name_={name_} wDgnId={wDgnId} dwReserverTimer={dwReserverTimer} wCount={wCount} wMaxCount={wMaxCount}/>;
			else
				topXml = <SGetSweepInfo wDgnId={wDgnId} dwReserverTimer={dwReserverTimer} wCount={wCount} wMaxCount={wMaxCount}/>;
			if(vecSweepItem != null)
			{
				var vecSweepItemXml:XML = <Vec_SSweepItem _name_="vecSweepItem"/>;
				for each(var s1:SSweepItem in vecSweepItem)
					vecSweepItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecSweepItemXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wDgnId = wDgnId;
			obj_.dwReserverTimer = dwReserverTimer;
			obj_.wCount = wCount;
			obj_.wMaxCount = wMaxCount;
			obj_.vecSweepItem = vecSweepItem;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGetSweepInfo
		{
			var s_:SGetSweepInfo = new SGetSweepInfo();
			var wDgnId:uint = bytes.readUnsignedShort();
			s_.wDgnId = wDgnId;
			var dwReserverTimer:uint = bytes.readUnsignedInt();
			s_.dwReserverTimer = dwReserverTimer;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			var wMaxCount:uint = bytes.readUnsignedShort();
			s_.wMaxCount = wMaxCount;
			var vecSweepItem:Vector.<SSweepItem> = SSweepItem.vectorFromByteArray(bytes);
			s_.vecSweepItem = vecSweepItem;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGetSweepInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGetSweepInfo> = new Vector.<SGetSweepInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGetSweepInfo = SGetSweepInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wDgnId);
			bytes.writeUnsignedInt(dwReserverTimer);
			bytes.writeShort(wCount);
			bytes.writeShort(wMaxCount);
			SSweepItem.vectorToByteArray(vecSweepItem, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGetSweepInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGetSweepInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
