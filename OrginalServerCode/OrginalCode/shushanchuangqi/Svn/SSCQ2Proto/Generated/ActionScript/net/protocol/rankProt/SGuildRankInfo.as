/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildRankInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派相关排名信息
	 */
	public class SGuildRankInfo extends SRankInfo
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var strName:String; //帮主姓名
		public var wLevel:uint; //(无符号16位整数)帮派等级
		public var strGuildName:String; //帮派姓名
		public var qwRoleID:BigInteger; //(无符号64位整数)帮主ID
		public var byQuality:uint; //(无符号8位整数)主将品质(颜色)
		public var wPlayerFighterID:uint; //(无符号16位整数)主将ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SGuildRankInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildRankInfo _name_={name_} qwGuildID={qwGuildID} strName={strName} wLevel={wLevel} strGuildName={strGuildName} qwRoleID={qwRoleID}
				 byQuality={byQuality} wPlayerFighterID={wPlayerFighterID}/>;
			else
				topXml = <SGuildRankInfo qwGuildID={qwGuildID} strName={strName} wLevel={wLevel} strGuildName={strGuildName} qwRoleID={qwRoleID}
				 byQuality={byQuality} wPlayerFighterID={wPlayerFighterID}/>;
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
			obj_.qwGuildID = qwGuildID;
			obj_.strName = strName;
			obj_.wLevel = wLevel;
			obj_.strGuildName = strGuildName;
			obj_.qwRoleID = qwRoleID;
			obj_.byQuality = byQuality;
			obj_.wPlayerFighterID = wPlayerFighterID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildRankInfo
		{
			var s_:SGuildRankInfo = new SGuildRankInfo();
			var base_:SRankInfo = SRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var wPlayerFighterID:uint = bytes.readUnsignedShort();
			s_.wPlayerFighterID = wPlayerFighterID;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SGuildRankInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SGuildRankInfo;
			switch(eType)
			{
				case EType_SRankInfo.eType_SGuildRankInfo:
					s = SGuildRankInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SGRBattleInfo:
					s = SGRBattleInfo.fromByteArray(bytes);
					break;
				case EType_SRankInfo.eType_SGRLevelInfo:
					s = SGRLevelInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SRankInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildRankInfo> = new Vector.<SGuildRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildRankInfo = SGuildRankInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SGuildRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildRankInfo> = new Vector.<SGuildRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildRankInfo = SGuildRankInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wLevel);
			BytesUtil.writeString(bytes, strGuildName);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byQuality);
			bytes.writeShort(wPlayerFighterID);
		}

		public override function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildRankInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SGuildRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildRankInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
