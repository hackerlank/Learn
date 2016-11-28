/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleRankInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家相关排名信息
	 */
	public class SRoleRankInfo extends SRankInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var wPlayerFighterID:uint; //(无符号16位整数)主将ID
		public var byQuality:uint; //(无符号8位整数)散仙品质(颜色)
		public var byVIPLevel:uint; //(无符号8位整数)玩家VIP等级
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SRoleRankInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRoleRankInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality} byVIPLevel={byVIPLevel}/>;
			else
				topXml = <SRoleRankInfo qwRoleID={qwRoleID} strName={strName} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality} byVIPLevel={byVIPLevel}/>;
			if(vecPlatforms != null)
			{
				var vecPlatformsXml:XML = <Vec_SPlatformParam _name_="vecPlatforms"/>;
				for each(var s1:SPlatformParam in vecPlatforms)
					vecPlatformsXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlatformsXml);
			}
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.wPlayerFighterID = wPlayerFighterID;
			obj_.byQuality = byQuality;
			obj_.byVIPLevel = byVIPLevel;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleRankInfo
		{
			var s_:SRoleRankInfo = new SRoleRankInfo();
			var base_:SRankInfo = SRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wPlayerFighterID:uint = bytes.readUnsignedShort();
			s_.wPlayerFighterID = wPlayerFighterID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SRoleRankInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SRoleRankInfo;
			switch(eType)
			{
				case EType_SRankInfo.eType_SRoleRankInfo:
					s = SRoleRankInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRBattlePointInfo:
					s = SRRBattlePointInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRLevelInfo:
					s = SRRLevelInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRFormationInfo:
					s = SRRFormationInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRHeroFighterInfo:
					s = SRRHeroFighterInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRTrumpInfo:
					s = SRRTrumpInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SRRArenaInfo:
					s = SRRArenaInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SRankInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleRankInfo> = new Vector.<SRoleRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleRankInfo = SRoleRankInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SRoleRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleRankInfo> = new Vector.<SRoleRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleRankInfo = SRoleRankInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wPlayerFighterID);
			bytes.writeByte(byQuality);
			bytes.writeByte(byVIPLevel);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public override function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleRankInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SRoleRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleRankInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
