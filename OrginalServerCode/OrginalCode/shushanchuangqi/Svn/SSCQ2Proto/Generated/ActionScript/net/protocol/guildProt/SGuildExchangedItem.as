/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildExchangedItem.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派兑换物品
	 */
	public final class SGuildExchangedItem
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派唯一ID
		public var dwExchangeID:uint; //(无符号32位整数)兑换ID
		public var dwCount:uint; //(无符号32位整数)兑换数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwGuildID:BigInteger, dwExchangeID:uint, dwCount:uint):SGuildExchangedItem
		{
			var s_:SGuildExchangedItem = new SGuildExchangedItem();
			s_.qwGuildID = qwGuildID;
			s_.dwExchangeID = dwExchangeID;
			s_.dwCount = dwCount;
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
				topXml = <SGuildExchangedItem _name_={name_} qwGuildID={qwGuildID} dwExchangeID={dwExchangeID} dwCount={dwCount}/>;
			else
				topXml = <SGuildExchangedItem qwGuildID={qwGuildID} dwExchangeID={dwExchangeID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwGuildID = qwGuildID;
			obj_.dwExchangeID = dwExchangeID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildExchangedItem
		{
			var s_:SGuildExchangedItem = new SGuildExchangedItem();
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var dwExchangeID:uint = bytes.readUnsignedInt();
			s_.dwExchangeID = dwExchangeID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildExchangedItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildExchangedItem> = new Vector.<SGuildExchangedItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildExchangedItem = SGuildExchangedItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwGuildID);
			bytes.writeUnsignedInt(dwExchangeID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildExchangedItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildExchangedItem in vec)
				s.toByteArray(bytes);
		}
	}
}
