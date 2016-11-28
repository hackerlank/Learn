/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildListInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派列表信息
	 */
	public final class SGuildListInfo
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派唯一ID
		public var strName:String; //帮派名称
		public var strInfo:String; //帮派公告
		public var qwOwnerID:BigInteger; //(无符号64位整数)帮主ID
		public var strOwnerName:String; //帮主名称
		public var byLevel:uint; //(无符号8位整数)帮派等级
		public var wUserCount:uint; //(无符号16位整数)成员数量
		public var wMaxUserCount:uint; //(无符号16位整数)最大成员数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwGuildID:BigInteger, strName:String, strInfo:String, qwOwnerID:BigInteger, strOwnerName:String, 
			byLevel:uint, wUserCount:uint, wMaxUserCount:uint):SGuildListInfo
		{
			var s_:SGuildListInfo = new SGuildListInfo();
			s_.qwGuildID = qwGuildID;
			s_.strName = strName;
			s_.strInfo = strInfo;
			s_.qwOwnerID = qwOwnerID;
			s_.strOwnerName = strOwnerName;
			s_.byLevel = byLevel;
			s_.wUserCount = wUserCount;
			s_.wMaxUserCount = wMaxUserCount;
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
				topXml = <SGuildListInfo _name_={name_} qwGuildID={qwGuildID} strName={strName} strInfo={strInfo} qwOwnerID={qwOwnerID} strOwnerName={strOwnerName}
				 byLevel={byLevel} wUserCount={wUserCount} wMaxUserCount={wMaxUserCount}/>;
			else
				topXml = <SGuildListInfo qwGuildID={qwGuildID} strName={strName} strInfo={strInfo} qwOwnerID={qwOwnerID} strOwnerName={strOwnerName}
				 byLevel={byLevel} wUserCount={wUserCount} wMaxUserCount={wMaxUserCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwGuildID = qwGuildID;
			obj_.strName = strName;
			obj_.strInfo = strInfo;
			obj_.qwOwnerID = qwOwnerID;
			obj_.strOwnerName = strOwnerName;
			obj_.byLevel = byLevel;
			obj_.wUserCount = wUserCount;
			obj_.wMaxUserCount = wMaxUserCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildListInfo
		{
			var s_:SGuildListInfo = new SGuildListInfo();
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var strInfo:String = BytesUtil.readString(bytes);
			s_.strInfo = strInfo;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var strOwnerName:String = BytesUtil.readString(bytes);
			s_.strOwnerName = strOwnerName;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var wUserCount:uint = bytes.readUnsignedShort();
			s_.wUserCount = wUserCount;
			var wMaxUserCount:uint = bytes.readUnsignedShort();
			s_.wMaxUserCount = wMaxUserCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildListInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildListInfo> = new Vector.<SGuildListInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildListInfo = SGuildListInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strName);
			BytesUtil.writeString(bytes, strInfo);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			BytesUtil.writeString(bytes, strOwnerName);
			bytes.writeByte(byLevel);
			bytes.writeShort(wUserCount);
			bytes.writeShort(wMaxUserCount);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildListInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildListInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
