/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAddItemMsg.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家获得道具
	 */
	public final class SAddItemMsg
	{
		public var wItemID:uint; //(无符号16位整数)道具的ID
		public var wCount:uint; //(无符号16位整数)道具个数
		public var byQuality:uint; //(无符号8位整数)道具品质

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, wCount:uint, byQuality:uint):SAddItemMsg
		{
			var s_:SAddItemMsg = new SAddItemMsg();
			s_.wItemID = wItemID;
			s_.wCount = wCount;
			s_.byQuality = byQuality;
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
				topXml = <SAddItemMsg _name_={name_} wItemID={wItemID} wCount={wCount} byQuality={byQuality}/>;
			else
				topXml = <SAddItemMsg wItemID={wItemID} wCount={wCount} byQuality={byQuality}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.wCount = wCount;
			obj_.byQuality = byQuality;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAddItemMsg
		{
			var s_:SAddItemMsg = new SAddItemMsg();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAddItemMsg>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAddItemMsg> = new Vector.<SAddItemMsg>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAddItemMsg = SAddItemMsg.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeShort(wCount);
			bytes.writeByte(byQuality);
		}

		public static function vectorToByteArray(vec:Vector.<SAddItemMsg>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAddItemMsg in vec)
				s.toByteArray(bytes);
		}
	}
}
