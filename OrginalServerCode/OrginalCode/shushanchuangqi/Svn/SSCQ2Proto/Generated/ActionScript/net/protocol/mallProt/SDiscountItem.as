/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDiscountItem.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 商城折扣物品
	 */
	public final class SDiscountItem
	{
		public var wItemID:uint; //(无符号16位整数)物品ID
		public var wOriginalPrice:uint; //(无符号16位整数)原价
		public var wDiscountPrice:uint; //(无符号16位整数)折扣价

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, wOriginalPrice:uint, wDiscountPrice:uint):SDiscountItem
		{
			var s_:SDiscountItem = new SDiscountItem();
			s_.wItemID = wItemID;
			s_.wOriginalPrice = wOriginalPrice;
			s_.wDiscountPrice = wDiscountPrice;
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
				topXml = <SDiscountItem _name_={name_} wItemID={wItemID} wOriginalPrice={wOriginalPrice} wDiscountPrice={wDiscountPrice}/>;
			else
				topXml = <SDiscountItem wItemID={wItemID} wOriginalPrice={wOriginalPrice} wDiscountPrice={wDiscountPrice}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.wOriginalPrice = wOriginalPrice;
			obj_.wDiscountPrice = wDiscountPrice;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDiscountItem
		{
			var s_:SDiscountItem = new SDiscountItem();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wOriginalPrice:uint = bytes.readUnsignedShort();
			s_.wOriginalPrice = wOriginalPrice;
			var wDiscountPrice:uint = bytes.readUnsignedShort();
			s_.wDiscountPrice = wDiscountPrice;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDiscountItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDiscountItem> = new Vector.<SDiscountItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDiscountItem = SDiscountItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeShort(wOriginalPrice);
			bytes.writeShort(wDiscountPrice);
		}

		public static function vectorToByteArray(vec:Vector.<SDiscountItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDiscountItem in vec)
				s.toByteArray(bytes);
		}
	}
}
