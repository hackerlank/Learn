/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    ExchangeInfo.as
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 已兑换信息列表
	 */
	public final class ExchangeInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var dwExchangeID:uint; //(无符号32位整数)兑换ID
		public var dwCount:uint; //(无符号32位整数)已兑换次数
		public var dwFinishTime:uint; //(无符号32位整数)兑换时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwExchangeID:uint, dwCount:uint, dwFinishTime:uint):ExchangeInfo
		{
			var s_:ExchangeInfo = new ExchangeInfo();
			s_.qwRoleID = qwRoleID;
			s_.dwExchangeID = dwExchangeID;
			s_.dwCount = dwCount;
			s_.dwFinishTime = dwFinishTime;
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
				topXml = <ExchangeInfo _name_={name_} qwRoleID={qwRoleID} dwExchangeID={dwExchangeID} dwCount={dwCount} dwFinishTime={dwFinishTime}/>;
			else
				topXml = <ExchangeInfo qwRoleID={qwRoleID} dwExchangeID={dwExchangeID} dwCount={dwCount} dwFinishTime={dwFinishTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwExchangeID = dwExchangeID;
			obj_.dwCount = dwCount;
			obj_.dwFinishTime = dwFinishTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):ExchangeInfo
		{
			var s_:ExchangeInfo = new ExchangeInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwExchangeID:uint = bytes.readUnsignedInt();
			s_.dwExchangeID = dwExchangeID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var dwFinishTime:uint = bytes.readUnsignedInt();
			s_.dwFinishTime = dwFinishTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<ExchangeInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<ExchangeInfo> = new Vector.<ExchangeInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:ExchangeInfo = ExchangeInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwExchangeID);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeUnsignedInt(dwFinishTime);
		}

		public static function vectorToByteArray(vec:Vector.<ExchangeInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:ExchangeInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
