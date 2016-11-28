/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleItemInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eRoleItemInfo
	 */
	public final class RoleItemInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)物品唯一ID
		public var wItemID:uint; //(无符号16位整数)物品模板
		public var byStoreType:uint; //(无符号8位整数)背包类型-数据来源：EStoreType
		public var wIndex:int; //(有符号16位整数)所属背包的位置
		public var wCount:uint; //(无符号16位整数)具的堆叠数
		public var byBind:uint; //(无符号8位整数)绑定类型0非绑定，1绑定
		public var byExpired:uint; //(无符号8位整数)是否时效，>0 时效物品
		public var dwExpireTime:uint; //(无符号32位整数)时效过期时间
		public var dwMark:uint; //(无符号32位整数)标记为错误物品,存下标记时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wItemID:uint, byStoreType:uint, wIndex:int, wCount:uint, 
			byBind:uint, byExpired:uint, dwExpireTime:uint, dwMark:uint):RoleItemInfo
		{
			var s_:RoleItemInfo = new RoleItemInfo();
			s_.qwInstID = qwInstID;
			s_.wItemID = wItemID;
			s_.byStoreType = byStoreType;
			s_.wIndex = wIndex;
			s_.wCount = wCount;
			s_.byBind = byBind;
			s_.byExpired = byExpired;
			s_.dwExpireTime = dwExpireTime;
			s_.dwMark = dwMark;
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
				topXml = <RoleItemInfo _name_={name_} qwInstID={qwInstID} wItemID={wItemID} byStoreType={byStoreType} wIndex={wIndex} wCount={wCount}
				 byBind={byBind} byExpired={byExpired} dwExpireTime={dwExpireTime} dwMark={dwMark}/>;
			else
				topXml = <RoleItemInfo qwInstID={qwInstID} wItemID={wItemID} byStoreType={byStoreType} wIndex={wIndex} wCount={wCount}
				 byBind={byBind} byExpired={byExpired} dwExpireTime={dwExpireTime} dwMark={dwMark}/>;
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
			obj_.byStoreType = byStoreType;
			obj_.wIndex = wIndex;
			obj_.wCount = wCount;
			obj_.byBind = byBind;
			obj_.byExpired = byExpired;
			obj_.dwExpireTime = dwExpireTime;
			obj_.dwMark = dwMark;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleItemInfo
		{
			var s_:RoleItemInfo = new RoleItemInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var byStoreType:uint = bytes.readUnsignedByte();
			s_.byStoreType = byStoreType;
			var wIndex:int = bytes.readShort();
			s_.wIndex = wIndex;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			var byBind:uint = bytes.readUnsignedByte();
			s_.byBind = byBind;
			var byExpired:uint = bytes.readUnsignedByte();
			s_.byExpired = byExpired;
			var dwExpireTime:uint = bytes.readUnsignedInt();
			s_.dwExpireTime = dwExpireTime;
			var dwMark:uint = bytes.readUnsignedInt();
			s_.dwMark = dwMark;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleItemInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleItemInfo> = new Vector.<RoleItemInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleItemInfo = RoleItemInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wItemID);
			bytes.writeByte(byStoreType);
			bytes.writeShort(wIndex);
			bytes.writeShort(wCount);
			bytes.writeByte(byBind);
			bytes.writeByte(byExpired);
			bytes.writeUnsignedInt(dwExpireTime);
			bytes.writeUnsignedInt(dwMark);
		}

		public static function vectorToByteArray(vec:Vector.<RoleItemInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleItemInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
