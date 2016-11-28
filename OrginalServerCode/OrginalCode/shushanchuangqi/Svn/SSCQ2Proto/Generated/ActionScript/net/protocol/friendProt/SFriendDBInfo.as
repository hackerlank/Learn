/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFriendDBInfo.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 好友条目
	 */
	public final class SFriendDBInfo
	{
		public var byGroup:uint; //(无符号8位整数)分组ID
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strName:String; //名字 XXX: 如果主将改名需要修改此处
		public var wFighterID:uint; //(无符号16位整数)主将ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var wMood:uint; //(无符号16位整数)心情表情
		public var byVIPLevel:uint; //(无符号8位整数)VIP等级
		public var strSign:String; //签名
		public var byColor:uint; //(无符号8位整数)好友颜色

		/**
		 * 辅助创建函数
		 */
		public static function create(byGroup:uint, qwUserID:BigInteger, strName:String, wFighterID:uint, byLevel:uint, 
			wMood:uint, byVIPLevel:uint, strSign:String, byColor:uint):SFriendDBInfo
		{
			var s_:SFriendDBInfo = new SFriendDBInfo();
			s_.byGroup = byGroup;
			s_.qwUserID = qwUserID;
			s_.strName = strName;
			s_.wFighterID = wFighterID;
			s_.byLevel = byLevel;
			s_.wMood = wMood;
			s_.byVIPLevel = byVIPLevel;
			s_.strSign = strSign;
			s_.byColor = byColor;
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
				topXml = <SFriendDBInfo _name_={name_} byGroup={byGroup} qwUserID={qwUserID} strName={strName} wFighterID={wFighterID} byLevel={byLevel}
				 wMood={wMood} byVIPLevel={byVIPLevel} strSign={strSign} byColor={byColor}/>;
			else
				topXml = <SFriendDBInfo byGroup={byGroup} qwUserID={qwUserID} strName={strName} wFighterID={wFighterID} byLevel={byLevel}
				 wMood={wMood} byVIPLevel={byVIPLevel} strSign={strSign} byColor={byColor}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byGroup = byGroup;
			obj_.qwUserID = qwUserID;
			obj_.strName = strName;
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
			obj_.wMood = wMood;
			obj_.byVIPLevel = byVIPLevel;
			obj_.strSign = strSign;
			obj_.byColor = byColor;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFriendDBInfo
		{
			var s_:SFriendDBInfo = new SFriendDBInfo();
			var byGroup:uint = bytes.readUnsignedByte();
			s_.byGroup = byGroup;
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var wMood:uint = bytes.readUnsignedShort();
			s_.wMood = wMood;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var strSign:String = BytesUtil.readString(bytes);
			s_.strSign = strSign;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFriendDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFriendDBInfo> = new Vector.<SFriendDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFriendDBInfo = SFriendDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byGroup);
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
			bytes.writeShort(wMood);
			bytes.writeByte(byVIPLevel);
			BytesUtil.writeString(bytes, strSign);
			bytes.writeByte(byColor);
		}

		public static function vectorToByteArray(vec:Vector.<SFriendDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFriendDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
