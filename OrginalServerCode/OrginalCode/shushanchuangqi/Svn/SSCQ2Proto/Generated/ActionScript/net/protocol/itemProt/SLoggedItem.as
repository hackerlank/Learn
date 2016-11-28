/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLoggedItem.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 记录的道具
	 */
	public final class SLoggedItem
	{
		public var wItemID:uint; //(无符号16位整数)道具ID
		public var byQuality:uint; //(无符号8位整数)品质
		public var dwCount:uint; //(无符号32位整数)道具个数
		public var bBind:Boolean; //是否绑定

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, byQuality:uint, dwCount:uint, bBind:Boolean):SLoggedItem
		{
			var s_:SLoggedItem = new SLoggedItem();
			s_.wItemID = wItemID;
			s_.byQuality = byQuality;
			s_.dwCount = dwCount;
			s_.bBind = bBind;
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
				topXml = <SLoggedItem _name_={name_} wItemID={wItemID} byQuality={byQuality} dwCount={dwCount} bBind={bBind}/>;
			else
				topXml = <SLoggedItem wItemID={wItemID} byQuality={byQuality} dwCount={dwCount} bBind={bBind}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.byQuality = byQuality;
			obj_.dwCount = dwCount;
			obj_.bBind = bBind;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLoggedItem
		{
			var s_:SLoggedItem = new SLoggedItem();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var bBind:Boolean = bytes.readBoolean();
			s_.bBind = bBind;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLoggedItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLoggedItem> = new Vector.<SLoggedItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLoggedItem = SLoggedItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeByte(byQuality);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeBoolean(bBind);
		}

		public static function vectorToByteArray(vec:Vector.<SLoggedItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLoggedItem in vec)
				s.toByteArray(bytes);
		}
	}
}
