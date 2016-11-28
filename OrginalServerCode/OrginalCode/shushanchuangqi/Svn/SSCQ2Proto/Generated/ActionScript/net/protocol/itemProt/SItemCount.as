/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemCount.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品列表
	 */
	public final class SItemCount
	{
		public var wItemID:uint; //(无符号16位整数)道具ID
		public var wCount:uint; //(无符号32位整数)道具个数

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, wCount:uint):SItemCount
		{
			var s_:SItemCount = new SItemCount();
			s_.wItemID = wItemID;
			s_.wCount = wCount;
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
				topXml = <SItemCount _name_={name_} wItemID={wItemID} wCount={wCount}/>;
			else
				topXml = <SItemCount wItemID={wItemID} wCount={wCount}/>;
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
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemCount
		{
			var s_:SItemCount = new SItemCount();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wCount:uint = bytes.readUnsignedInt();
			s_.wCount = wCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemCount>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemCount> = new Vector.<SItemCount>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemCount = SItemCount.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(wCount);
		}

		public static function vectorToByteArray(vec:Vector.<SItemCount>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemCount in vec)
				s.toByteArray(bytes);
		}
	}
}
