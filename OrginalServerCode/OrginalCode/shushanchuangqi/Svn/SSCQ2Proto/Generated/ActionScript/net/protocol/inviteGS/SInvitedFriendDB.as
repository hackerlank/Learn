/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SInvitedFriendDB.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 被邀请好友db信息
	 */
	public final class SInvitedFriendDB
	{
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var qwInviteID:BigInteger; //(无符号64位整数)邀请账号ID
		public var strName:String; //名字
		public var byColor:uint; //(无符号8位整数)职业
		public var byJob:uint; //(无符号8位整数)职业
		public var bySex:uint; //(无符号8位整数)性别
		public var byLevel:uint; //(无符号8位整数)等级
		public var byVIPLevel:uint; //(无符号8位整数)VIP等级
		public var dwTotalRecharge:uint; //(无符号32位整数)总充值

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, qwInviteID:BigInteger, strName:String, byColor:uint, byJob:uint, 
			bySex:uint, byLevel:uint, byVIPLevel:uint, dwTotalRecharge:uint):SInvitedFriendDB
		{
			var s_:SInvitedFriendDB = new SInvitedFriendDB();
			s_.qwUserID = qwUserID;
			s_.qwInviteID = qwInviteID;
			s_.strName = strName;
			s_.byColor = byColor;
			s_.byJob = byJob;
			s_.bySex = bySex;
			s_.byLevel = byLevel;
			s_.byVIPLevel = byVIPLevel;
			s_.dwTotalRecharge = dwTotalRecharge;
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
				topXml = <SInvitedFriendDB _name_={name_} qwUserID={qwUserID} qwInviteID={qwInviteID} strName={strName} byColor={byColor} byJob={byJob}
				 bySex={bySex} byLevel={byLevel} byVIPLevel={byVIPLevel} dwTotalRecharge={dwTotalRecharge}/>;
			else
				topXml = <SInvitedFriendDB qwUserID={qwUserID} qwInviteID={qwInviteID} strName={strName} byColor={byColor} byJob={byJob}
				 bySex={bySex} byLevel={byLevel} byVIPLevel={byVIPLevel} dwTotalRecharge={dwTotalRecharge}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.qwInviteID = qwInviteID;
			obj_.strName = strName;
			obj_.byColor = byColor;
			obj_.byJob = byJob;
			obj_.bySex = bySex;
			obj_.byLevel = byLevel;
			obj_.byVIPLevel = byVIPLevel;
			obj_.dwTotalRecharge = dwTotalRecharge;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SInvitedFriendDB
		{
			var s_:SInvitedFriendDB = new SInvitedFriendDB();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var qwInviteID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInviteID = qwInviteID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
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
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SInvitedFriendDB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SInvitedFriendDB> = new Vector.<SInvitedFriendDB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SInvitedFriendDB = SInvitedFriendDB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeUInt64(bytes, qwInviteID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byColor);
			bytes.writeByte(byJob);
			bytes.writeByte(bySex);
			bytes.writeByte(byLevel);
			bytes.writeByte(byVIPLevel);
			bytes.writeUnsignedInt(dwTotalRecharge);
		}

		public static function vectorToByteArray(vec:Vector.<SInvitedFriendDB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SInvitedFriendDB in vec)
				s.toByteArray(bytes);
		}
	}
}
