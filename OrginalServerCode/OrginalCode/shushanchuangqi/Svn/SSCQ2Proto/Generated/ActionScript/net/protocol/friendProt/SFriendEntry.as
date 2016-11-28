/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFriendEntry.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 好友条目
	 */
	public final class SFriendEntry
	{
		public var eGroupType:uint; //(枚举类型：EFriendGroupType)分组ID
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strName:String; //名字 XXX: 如果主将改名需要修改此处
		public var wFighterID:uint; //(无符号16位整数)主将ID
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byLevel:uint; //(无符号8位整数)等级
		public var byVIPLevel:uint; //(无符号8位整数)VIP等级
		public var byColor:uint; //(无符号8位整数)好友颜色
		public var wMood:uint; //(无符号16位整数)心情表情
		public var strSign:String; //签名
		public var dwTotalRecharge:uint; //(无符号32位整数)总充值
		public var bOnlineStatus:Boolean; //在线状态
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 辅助创建函数
		 */
		public static function create(eGroupType:uint, qwUserID:BigInteger, strName:String, wFighterID:uint, eSex:uint, 
			byLevel:uint, byVIPLevel:uint, byColor:uint, wMood:uint, strSign:String, 
			dwTotalRecharge:uint, bOnlineStatus:Boolean, vecPlatforms:Vector.<SPlatformParam>):SFriendEntry
		{
			var s_:SFriendEntry = new SFriendEntry();
			s_.eGroupType = eGroupType;
			s_.qwUserID = qwUserID;
			s_.strName = strName;
			s_.wFighterID = wFighterID;
			s_.eSex = eSex;
			s_.byLevel = byLevel;
			s_.byVIPLevel = byVIPLevel;
			s_.byColor = byColor;
			s_.wMood = wMood;
			s_.strSign = strSign;
			s_.dwTotalRecharge = dwTotalRecharge;
			s_.bOnlineStatus = bOnlineStatus;
			s_.vecPlatforms = vecPlatforms;
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
				topXml = <SFriendEntry _name_={name_} eGroupType={eGroupType} qwUserID={qwUserID} strName={strName} wFighterID={wFighterID} eSex={eSex}
				 byLevel={byLevel} byVIPLevel={byVIPLevel} byColor={byColor} wMood={wMood} strSign={strSign}
				 dwTotalRecharge={dwTotalRecharge} bOnlineStatus={bOnlineStatus}/>;
			else
				topXml = <SFriendEntry eGroupType={eGroupType} qwUserID={qwUserID} strName={strName} wFighterID={wFighterID} eSex={eSex}
				 byLevel={byLevel} byVIPLevel={byVIPLevel} byColor={byColor} wMood={wMood} strSign={strSign}
				 dwTotalRecharge={dwTotalRecharge} bOnlineStatus={bOnlineStatus}/>;
			if(vecPlatforms != null)
			{
				var vecPlatformsXml:XML = <Vec_SPlatformParam _name_="vecPlatforms"/>;
				for each(var s1:SPlatformParam in vecPlatforms)
					vecPlatformsXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlatformsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eGroupType = eGroupType;
			obj_.qwUserID = qwUserID;
			obj_.strName = strName;
			obj_.wFighterID = wFighterID;
			obj_.eSex = eSex;
			obj_.byLevel = byLevel;
			obj_.byVIPLevel = byVIPLevel;
			obj_.byColor = byColor;
			obj_.wMood = wMood;
			obj_.strSign = strSign;
			obj_.dwTotalRecharge = dwTotalRecharge;
			obj_.bOnlineStatus = bOnlineStatus;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFriendEntry
		{
			var s_:SFriendEntry = new SFriendEntry();
			var eGroupType:uint = bytes.readUnsignedByte();
			s_.eGroupType = eGroupType;
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			var wMood:uint = bytes.readUnsignedShort();
			s_.wMood = wMood;
			var strSign:String = BytesUtil.readString(bytes);
			s_.strSign = strSign;
			var dwTotalRecharge:uint = bytes.readUnsignedInt();
			s_.dwTotalRecharge = dwTotalRecharge;
			var bOnlineStatus:Boolean = bytes.readBoolean();
			s_.bOnlineStatus = bOnlineStatus;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFriendEntry>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFriendEntry> = new Vector.<SFriendEntry>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFriendEntry = SFriendEntry.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eGroupType);
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wFighterID);
			bytes.writeByte(eSex);
			bytes.writeByte(byLevel);
			bytes.writeByte(byVIPLevel);
			bytes.writeByte(byColor);
			bytes.writeShort(wMood);
			BytesUtil.writeString(bytes, strSign);
			bytes.writeUnsignedInt(dwTotalRecharge);
			bytes.writeBoolean(bOnlineStatus);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFriendEntry>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFriendEntry in vec)
				s.toByteArray(bytes);
		}
	}
}
