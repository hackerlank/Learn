/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SInvitedFriend.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 被邀请好友信息
	 */
	public final class SInvitedFriend
	{
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strName:String; //名字
		public var byJob:uint; //(无符号8位整数)职业
		public var bySex:uint; //(无符号8位整数)性别
		public var byLevel:uint; //(无符号8位整数)等级
		public var byVIPLevel:uint; //(无符号8位整数)VIP等级
		public var dwTotalRecharge:uint; //(无符号32位整数)总充值
		public var vecPlatforms:Vector.<SPlatformParam>; //平台信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, strName:String, byJob:uint, bySex:uint, byLevel:uint, 
			byVIPLevel:uint, dwTotalRecharge:uint, vecPlatforms:Vector.<SPlatformParam>):SInvitedFriend
		{
			var s_:SInvitedFriend = new SInvitedFriend();
			s_.qwUserID = qwUserID;
			s_.strName = strName;
			s_.byJob = byJob;
			s_.bySex = bySex;
			s_.byLevel = byLevel;
			s_.byVIPLevel = byVIPLevel;
			s_.dwTotalRecharge = dwTotalRecharge;
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
				topXml = <SInvitedFriend _name_={name_} qwUserID={qwUserID} strName={strName} byJob={byJob} bySex={bySex} byLevel={byLevel}
				 byVIPLevel={byVIPLevel} dwTotalRecharge={dwTotalRecharge}/>;
			else
				topXml = <SInvitedFriend qwUserID={qwUserID} strName={strName} byJob={byJob} bySex={bySex} byLevel={byLevel}
				 byVIPLevel={byVIPLevel} dwTotalRecharge={dwTotalRecharge}/>;
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
			obj_.byJob = byJob;
			obj_.bySex = bySex;
			obj_.byLevel = byLevel;
			obj_.byVIPLevel = byVIPLevel;
			obj_.dwTotalRecharge = dwTotalRecharge;
			obj_.vecPlatforms = vecPlatforms;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SInvitedFriend
		{
			var s_:SInvitedFriend = new SInvitedFriend();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byJob:uint = bytes.readUnsignedByte();
			s_.byJob = byJob;
			var bySex:uint = bytes.readUnsignedByte();
			s_.bySex = bySex;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var dwTotalRecharge:uint = bytes.readUnsignedInt();
			s_.dwTotalRecharge = dwTotalRecharge;
			var vecPlatforms:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatforms = vecPlatforms;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SInvitedFriend>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SInvitedFriend> = new Vector.<SInvitedFriend>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SInvitedFriend = SInvitedFriend.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byJob);
			bytes.writeByte(bySex);
			bytes.writeByte(byLevel);
			bytes.writeByte(byVIPLevel);
			bytes.writeUnsignedInt(dwTotalRecharge);
			SPlatformParam.vectorToByteArray(vecPlatforms, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SInvitedFriend>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SInvitedFriend in vec)
				s.toByteArray(bytes);
		}
	}
}
