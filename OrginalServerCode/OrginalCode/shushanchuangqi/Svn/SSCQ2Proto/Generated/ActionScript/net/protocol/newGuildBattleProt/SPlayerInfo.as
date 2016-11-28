/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家信息
	 */
	public final class SPlayerInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var eJob:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byQuality:uint; //(无符号8位整数)品质
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var eSide:uint; //(枚举类型：ENGBSide)自己所在方向
		public var dwMaxHP:uint; //(无符号32位整数)最大血量
		public var dwHP:uint; //(无符号32位整数)当前血量
		public var dwDeadTime:uint; //(无符号32位整数)死亡时间（复活所需时间）

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, eJob:uint, eSex:uint, byQuality:uint, 
			qwGuildID:BigInteger, eSide:uint, dwMaxHP:uint, dwHP:uint, dwDeadTime:uint):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.eJob = eJob;
			s_.eSex = eSex;
			s_.byQuality = byQuality;
			s_.qwGuildID = qwGuildID;
			s_.eSide = eSide;
			s_.dwMaxHP = dwMaxHP;
			s_.dwHP = dwHP;
			s_.dwDeadTime = dwDeadTime;
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
				topXml = <SPlayerInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} eJob={eJob} eSex={eSex} byQuality={byQuality}
				 qwGuildID={qwGuildID} eSide={eSide} dwMaxHP={dwMaxHP} dwHP={dwHP} dwDeadTime={dwDeadTime}/>;
			else
				topXml = <SPlayerInfo qwRoleID={qwRoleID} strName={strName} eJob={eJob} eSex={eSex} byQuality={byQuality}
				 qwGuildID={qwGuildID} eSide={eSide} dwMaxHP={dwMaxHP} dwHP={dwHP} dwDeadTime={dwDeadTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.eJob = eJob;
			obj_.eSex = eSex;
			obj_.byQuality = byQuality;
			obj_.qwGuildID = qwGuildID;
			obj_.eSide = eSide;
			obj_.dwMaxHP = dwMaxHP;
			obj_.dwHP = dwHP;
			obj_.dwDeadTime = dwDeadTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eJob:uint = bytes.readUnsignedByte();
			s_.eJob = eJob;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var eSide:uint = bytes.readUnsignedByte();
			s_.eSide = eSide;
			var dwMaxHP:uint = bytes.readUnsignedInt();
			s_.dwMaxHP = dwMaxHP;
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			var dwDeadTime:uint = bytes.readUnsignedInt();
			s_.dwDeadTime = dwDeadTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerInfo> = new Vector.<SPlayerInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerInfo = SPlayerInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eJob);
			bytes.writeByte(eSex);
			bytes.writeByte(byQuality);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			bytes.writeByte(eSide);
			bytes.writeUnsignedInt(dwMaxHP);
			bytes.writeUnsignedInt(dwHP);
			bytes.writeUnsignedInt(dwDeadTime);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
