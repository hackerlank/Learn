/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPassiveSkillDBInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库同步到游戏服务器的技能信息
	 */
	public final class SPassiveSkillDBInfo
	{
		public var qwOwnerID:BigInteger; //(无符号64位整数)将唯一ID
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家一ID
		public var dwSkillID:uint; //(无符号32位整数)技能ID
		public var dwSkillQuality:uint; //(无符号32位整数)技能品质
		public var dwSkillLevel:uint; //(无符号32位整数)技能等级

		/**
		 * 辅助创建函数
		 */
		public static function create(qwOwnerID:BigInteger, qwRoleID:BigInteger, dwSkillID:uint, dwSkillQuality:uint, dwSkillLevel:uint):SPassiveSkillDBInfo
		{
			var s_:SPassiveSkillDBInfo = new SPassiveSkillDBInfo();
			s_.qwOwnerID = qwOwnerID;
			s_.qwRoleID = qwRoleID;
			s_.dwSkillID = dwSkillID;
			s_.dwSkillQuality = dwSkillQuality;
			s_.dwSkillLevel = dwSkillLevel;
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
				topXml = <SPassiveSkillDBInfo _name_={name_} qwOwnerID={qwOwnerID} qwRoleID={qwRoleID} dwSkillID={dwSkillID} dwSkillQuality={dwSkillQuality} dwSkillLevel={dwSkillLevel}/>;
			else
				topXml = <SPassiveSkillDBInfo qwOwnerID={qwOwnerID} qwRoleID={qwRoleID} dwSkillID={dwSkillID} dwSkillQuality={dwSkillQuality} dwSkillLevel={dwSkillLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwOwnerID = qwOwnerID;
			obj_.qwRoleID = qwRoleID;
			obj_.dwSkillID = dwSkillID;
			obj_.dwSkillQuality = dwSkillQuality;
			obj_.dwSkillLevel = dwSkillLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPassiveSkillDBInfo
		{
			var s_:SPassiveSkillDBInfo = new SPassiveSkillDBInfo();
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var dwSkillQuality:uint = bytes.readUnsignedInt();
			s_.dwSkillQuality = dwSkillQuality;
			var dwSkillLevel:uint = bytes.readUnsignedInt();
			s_.dwSkillLevel = dwSkillLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPassiveSkillDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPassiveSkillDBInfo> = new Vector.<SPassiveSkillDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPassiveSkillDBInfo = SPassiveSkillDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeUnsignedInt(dwSkillQuality);
			bytes.writeUnsignedInt(dwSkillLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SPassiveSkillDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPassiveSkillDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
