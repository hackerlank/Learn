/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SWhisperInfo.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 私聊对方信息
	 */
	public final class SWhisperInfo
	{
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strName:String; //名字 XXX: 如果主将改名需要修改此处
		public var byVIPType:uint; //(无符号8位整数)VIP特权类型
		public var strGuildName:String; //帮派名称
		public var vecPlatforms:Vector.<SPlatformParam>; //平台相关参数
		public var wFighterID:uint; //(无符号16位整数)主将ID
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byLevel:uint; //(无符号8位整数)等级
		public var wMood:uint; //(无符号16位整数)心情表情
		public var strSign:String; //签名
		public var byQuality:uint; //(无符号8位整数)品质

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, strName:String, byVIPType:uint, strGuildName:String, vecPlatforms:Vector.<SPlatformParam>, 
			wFighterID:uint, eSex:uint, byLevel:uint, wMood:uint, strSign:String, 
			byQuality:uint):SWhisperInfo
		{
			var s_:SWhisperInfo = new SWhisperInfo();
			s_.qwUserID = qwUserID;
			s_.strName = strName;
			s_.byVIPType = byVIPType;
			s_.strGuildName = strGuildName;
			s_.vecPlatforms = vecPlatforms;
			s_.wFighterID = wFighterID;
			s_.eSex = eSex;
			s_.byLevel = byLevel;
			s_.wMood = wMood;
			s_.strSign = strSign;
			s_.byQuality = byQuality;
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
				topXml = <SWhisperInfo _name_={name_} qwUserID={qwUserID} strName={strName} byVIPType={byVIPType} strGuildName={strGuildName}
				 wFighterID={wFighterID} eSex={eSex} byLevel={byLevel} wMood={wMood} strSign={strSign}
				 byQuality={byQuality}/>;
			else
				topXml = <SWhisperInfo qwUserID={qwUserID} strName={strName} byVIPType={byVIPType} strGuildName={strGuildName}
				 wFighterID={wFighterID} eSex={eSex} byLevel={byLevel} wMood={wMood} strSign={strSign}
				 byQuality={byQuality}/>;
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
			obj_.qwUserID = qwUserID;
			obj_.strName = strName;
			obj_.byVIPType = byVIPType;
			obj_.strGuildName = strGuildName;
			obj_.vecPlatforms = vecPlatforms;
			obj_.wFighterID = wFighterID;
			obj_.eSex = eSex;
			obj_.byLevel = byLevel;
			obj_.wMood = wMood;
			obj_.strSign = strSign;
			obj_.byQuality = byQuality;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SWhisperInfo
		{
			var s_:SWhisperInfo = new SWhisperInfo();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byVIPType:uint = bytes.readUnsignedByte();
			s_.byVIPType = byVIPType;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var wMood:uint = bytes.readUnsignedShort();
			s_.wMood = wMood;
			var strSign:String = BytesUtil.readString(bytes);
			s_.strSign = strSign;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SWhisperInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SWhisperInfo> = new Vector.<SWhisperInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SWhisperInfo = SWhisperInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byVIPType);
			BytesUtil.writeString(bytes, strGuildName);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
			bytes.writeShort(wFighterID);
			bytes.writeByte(eSex);
			bytes.writeByte(byLevel);
			bytes.writeShort(wMood);
			BytesUtil.writeString(bytes, strSign);
			bytes.writeByte(byQuality);
		}

		public static function vectorToByteArray(vec:Vector.<SWhisperInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SWhisperInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
