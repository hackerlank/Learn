/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMailItemInfo.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 道具格式
	 */
	public final class SMailItemInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)道具类型ID
		public var wItemID:uint; //(无符号32位整数)物品模板
		public var eItemQuelity:uint; //(枚举类型：itemProt.EItemQuality)物品品质
		public var wCount:uint; //(无符号32位整数)道具数量
		public var eBindType:uint; //(枚举类型：itemProt.EBindType)绑定类型
		public var byExpired:uint; //(无符号8位整数)是否时效，>0 时效物品
		public var dwExpireTime:uint; //(无符号32位整数)过期时间
		public var qwOPID:BigInteger; //(无符号64位整数)操作ID

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wItemID:uint, eItemQuelity:uint, wCount:uint, eBindType:uint, 
			byExpired:uint, dwExpireTime:uint, qwOPID:BigInteger):SMailItemInfo
		{
			var s_:SMailItemInfo = new SMailItemInfo();
			s_.qwInstID = qwInstID;
			s_.wItemID = wItemID;
			s_.eItemQuelity = eItemQuelity;
			s_.wCount = wCount;
			s_.eBindType = eBindType;
			s_.byExpired = byExpired;
			s_.dwExpireTime = dwExpireTime;
			s_.qwOPID = qwOPID;
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
				topXml = <SMailItemInfo _name_={name_} qwInstID={qwInstID} wItemID={wItemID} eItemQuelity={eItemQuelity} wCount={wCount} eBindType={eBindType}
				 byExpired={byExpired} dwExpireTime={dwExpireTime} qwOPID={qwOPID}/>;
			else
				topXml = <SMailItemInfo qwInstID={qwInstID} wItemID={wItemID} eItemQuelity={eItemQuelity} wCount={wCount} eBindType={eBindType}
				 byExpired={byExpired} dwExpireTime={dwExpireTime} qwOPID={qwOPID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wItemID = wItemID;
			obj_.eItemQuelity = eItemQuelity;
			obj_.wCount = wCount;
			obj_.eBindType = eBindType;
			obj_.byExpired = byExpired;
			obj_.dwExpireTime = dwExpireTime;
			obj_.qwOPID = qwOPID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMailItemInfo
		{
			var s_:SMailItemInfo = new SMailItemInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wItemID:uint = bytes.readUnsignedInt();
			s_.wItemID = wItemID;
			var eItemQuelity:uint = bytes.readUnsignedByte();
			s_.eItemQuelity = eItemQuelity;
			var wCount:uint = bytes.readUnsignedInt();
			s_.wCount = wCount;
			var eBindType:uint = bytes.readUnsignedByte();
			s_.eBindType = eBindType;
			var byExpired:uint = bytes.readUnsignedByte();
			s_.byExpired = byExpired;
			var dwExpireTime:uint = bytes.readUnsignedInt();
			s_.dwExpireTime = dwExpireTime;
			var qwOPID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOPID = qwOPID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMailItemInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMailItemInfo> = new Vector.<SMailItemInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMailItemInfo = SMailItemInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeUnsignedInt(wItemID);
			bytes.writeByte(eItemQuelity);
			bytes.writeUnsignedInt(wCount);
			bytes.writeByte(eBindType);
			bytes.writeByte(byExpired);
			bytes.writeUnsignedInt(dwExpireTime);
			BytesUtil.writeUInt64(bytes, qwOPID);
		}

		public static function vectorToByteArray(vec:Vector.<SMailItemInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMailItemInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
