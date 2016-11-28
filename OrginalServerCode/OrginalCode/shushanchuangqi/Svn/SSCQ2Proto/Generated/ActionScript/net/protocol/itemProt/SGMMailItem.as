/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGMMailItem.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 道具信息
	 */
	public final class SGMMailItem
	{
		public var wItemID:uint; //(无符号16位整数)道具配置ID
		public var wItemCount:uint; //(无符号32位整数)道具数量

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, wItemCount:uint):SGMMailItem
		{
			var s_:SGMMailItem = new SGMMailItem();
			s_.wItemID = wItemID;
			s_.wItemCount = wItemCount;
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
				topXml = <SGMMailItem _name_={name_} wItemID={wItemID} wItemCount={wItemCount}/>;
			else
				topXml = <SGMMailItem wItemID={wItemID} wItemCount={wItemCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.wItemCount = wItemCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGMMailItem
		{
			var s_:SGMMailItem = new SGMMailItem();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wItemCount:uint = bytes.readUnsignedInt();
			s_.wItemCount = wItemCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGMMailItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGMMailItem> = new Vector.<SGMMailItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGMMailItem = SGMMailItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(wItemCount);
		}

		public static function vectorToByteArray(vec:Vector.<SGMMailItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGMMailItem in vec)
				s.toByteArray(bytes);
		}
	}
}
