/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildUserInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派成员信息
	 */
	public final class SGuildUserInfo extends SGuildInfoBase
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var wLevel:uint; //(无符号16位整数)玩家等级
		public var dwContribution:uint; //(无符号32位整数)贡献值
		public var dwLastOnlineTime:uint; //(无符号32位整数)最后在线时间
		public var dwJoinTime:uint; //(无符号32位整数)入帮时间
		public var eMemberRank:uint; //(枚举类型：EMemberRank)帮派职位
		public var eMemberLastRank:uint; //(枚举类型：EMemberRank)帮派上一次职位
		public var dwAuthority:uint; //(无符号32位整数)帮派权限
		public var byVIPLevel:uint; //(无符号8位整数)御剑等级
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildUserInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildUserInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} dwContribution={dwContribution} dwLastOnlineTime={dwLastOnlineTime}
				 dwJoinTime={dwJoinTime} eMemberRank={eMemberRank} eMemberLastRank={eMemberLastRank} dwAuthority={dwAuthority} byVIPLevel={byVIPLevel}/>;
			else
				topXml = <SGuildUserInfo qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} dwContribution={dwContribution} dwLastOnlineTime={dwLastOnlineTime}
				 dwJoinTime={dwJoinTime} eMemberRank={eMemberRank} eMemberLastRank={eMemberLastRank} dwAuthority={dwAuthority} byVIPLevel={byVIPLevel}/>;
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
			obj_.wLevel = wLevel;
			obj_.dwContribution = dwContribution;
			obj_.dwLastOnlineTime = dwLastOnlineTime;
			obj_.dwJoinTime = dwJoinTime;
			obj_.eMemberRank = eMemberRank;
			obj_.eMemberLastRank = eMemberLastRank;
			obj_.dwAuthority = dwAuthority;
			obj_.byVIPLevel = byVIPLevel;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildUserInfo
		{
			var s_:SGuildUserInfo = new SGuildUserInfo();
			var base_:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var dwContribution:uint = bytes.readUnsignedInt();
			s_.dwContribution = dwContribution;
			var dwLastOnlineTime:uint = bytes.readUnsignedInt();
			s_.dwLastOnlineTime = dwLastOnlineTime;
			var dwJoinTime:uint = bytes.readUnsignedInt();
			s_.dwJoinTime = dwJoinTime;
			var eMemberRank:uint = bytes.readUnsignedByte();
			s_.eMemberRank = eMemberRank;
			var eMemberLastRank:uint = bytes.readUnsignedByte();
			s_.eMemberLastRank = eMemberLastRank;
			var dwAuthority:uint = bytes.readUnsignedInt();
			s_.dwAuthority = dwAuthority;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildUserInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildUserInfo> = new Vector.<SGuildUserInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildUserInfo = SGuildUserInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wLevel);
			bytes.writeUnsignedInt(dwContribution);
			bytes.writeUnsignedInt(dwLastOnlineTime);
			bytes.writeUnsignedInt(dwJoinTime);
			bytes.writeByte(eMemberRank);
			bytes.writeByte(eMemberLastRank);
			bytes.writeUnsignedInt(dwAuthority);
			bytes.writeByte(byVIPLevel);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildUserInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildUserInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
