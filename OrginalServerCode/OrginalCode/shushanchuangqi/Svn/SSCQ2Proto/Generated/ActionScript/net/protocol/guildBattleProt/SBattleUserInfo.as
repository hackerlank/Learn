/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleUserInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派战玩家信息
	 */
	public class SBattleUserInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)成员角色ID
		public var strName:String; //名字
		public var wLevel:uint; //(无符号16位整数)等级
		public var eState:uint; //(枚举类型：EGBUserState)玩家状态
		public var wFighterID:uint; //(无符号16位整数)玩家主将ID
		public var vecSkillInfo:Vector.<SSkillInfo>; //玩家技能信息

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SBattleUserInfo.eType_SBattleUserInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SBattleUserInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} eState={eState} wFighterID={wFighterID}/>;
			else
				topXml = <SBattleUserInfo qwRoleID={qwRoleID} strName={strName} wLevel={wLevel} eState={eState} wFighterID={wFighterID}/>;
			if(vecSkillInfo != null)
			{
				var vecSkillInfoXml:XML = <Vec_SSkillInfo _name_="vecSkillInfo"/>;
				for each(var s1:SSkillInfo in vecSkillInfo)
					vecSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSkillInfoXml);
			}
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
			obj_.wLevel = wLevel;
			obj_.eState = eState;
			obj_.wFighterID = wFighterID;
			obj_.vecSkillInfo = vecSkillInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleUserInfo
		{
			var s_:SBattleUserInfo = new SBattleUserInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var eState:uint = bytes.readUnsignedByte();
			s_.eState = eState;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var vecSkillInfo:Vector.<SSkillInfo> = SSkillInfo.vectorFromByteArray(bytes);
			s_.vecSkillInfo = vecSkillInfo;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SBattleUserInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SBattleUserInfo;
			switch(eType)
			{
				case EType_SBattleUserInfo.eType_SBattleUserInfo:
					s = SBattleUserInfo.fromByteArray(bytes);
					break;
				case EType_SBattleUserInfo.eType_SBattleUserAllInfo:
					s = SBattleUserAllInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SBattleUserInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleUserInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleUserInfo> = new Vector.<SBattleUserInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleUserInfo = SBattleUserInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SBattleUserInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleUserInfo> = new Vector.<SBattleUserInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleUserInfo = SBattleUserInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeShort(wLevel);
			bytes.writeByte(eState);
			bytes.writeShort(wFighterID);
			SSkillInfo.vectorToByteArray(vecSkillInfo, bytes);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleUserInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleUserInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SBattleUserInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleUserInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
