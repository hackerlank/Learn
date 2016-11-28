/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SStoreStream.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 背包信息
	 */
	public final class SStoreStream
	{
		public var wCapacity:uint; //(无符号16位整数)背包大小(不发最大值，最大值由两端的配置决定)
		public var vecItem:Vector.<SItem>; //物品信息

		/**
		 * 辅助创建函数
		 */
		public static function create(wCapacity:uint, vecItem:Vector.<SItem>):SStoreStream
		{
			var s_:SStoreStream = new SStoreStream();
			s_.wCapacity = wCapacity;
			s_.vecItem = vecItem;
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
				topXml = <SStoreStream _name_={name_} wCapacity={wCapacity}/>;
			else
				topXml = <SStoreStream wCapacity={wCapacity}/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItem _name_="vecItem"/>;
				for each(var s1:SItem in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wCapacity = wCapacity;
			obj_.vecItem = vecItem;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SStoreStream
		{
			var s_:SStoreStream = new SStoreStream();
			var wCapacity:uint = bytes.readUnsignedShort();
			s_.wCapacity = wCapacity;
			var vecItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes);
			s_.vecItem = vecItem;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SStoreStream>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SStoreStream> = new Vector.<SStoreStream>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SStoreStream = SStoreStream.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wCapacity);
			SItem.superVectorToByteArray(vecItem, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SStoreStream>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SStoreStream in vec)
				s.toByteArray(bytes);
		}
	}
}
