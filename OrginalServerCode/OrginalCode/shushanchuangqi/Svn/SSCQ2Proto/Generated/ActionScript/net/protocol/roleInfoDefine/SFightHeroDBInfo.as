/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFightHeroDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗散仙数据
	 */
	public final class SFightHeroDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wBattleType:uint; //(无符号16位整数)战斗类型
		public var qwInstID:BigInteger; //(无符号64位整数)散仙instID
		public var dwHP:uint; //(无符号32位整数)当前生命值
		public var dwMaxHP:uint; //(无符号32位整数)最大生命值（可能用到）
		public var dwAura:uint; //(无符号32位整数)灵气值
		public var dwMaxAura:uint; //(无符号32位整数)灵气值

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wBattleType:uint, qwInstID:BigInteger, dwHP:uint, dwMaxHP:uint, 
			dwAura:uint, dwMaxAura:uint):SFightHeroDBInfo
		{
			var s_:SFightHeroDBInfo = new SFightHeroDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wBattleType = wBattleType;
			s_.qwInstID = qwInstID;
			s_.dwHP = dwHP;
			s_.dwMaxHP = dwMaxHP;
			s_.dwAura = dwAura;
			s_.dwMaxAura = dwMaxAura;
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
				topXml = <SFightHeroDBInfo _name_={name_} qwRoleID={qwRoleID} wBattleType={wBattleType} qwInstID={qwInstID} dwHP={dwHP} dwMaxHP={dwMaxHP}
				 dwAura={dwAura} dwMaxAura={dwMaxAura}/>;
			else
				topXml = <SFightHeroDBInfo qwRoleID={qwRoleID} wBattleType={wBattleType} qwInstID={qwInstID} dwHP={dwHP} dwMaxHP={dwMaxHP}
				 dwAura={dwAura} dwMaxAura={dwMaxAura}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wBattleType = wBattleType;
			obj_.qwInstID = qwInstID;
			obj_.dwHP = dwHP;
			obj_.dwMaxHP = dwMaxHP;
			obj_.dwAura = dwAura;
			obj_.dwMaxAura = dwMaxAura;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFightHeroDBInfo
		{
			var s_:SFightHeroDBInfo = new SFightHeroDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wBattleType:uint = bytes.readUnsignedShort();
			s_.wBattleType = wBattleType;
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			var dwMaxHP:uint = bytes.readUnsignedInt();
			s_.dwMaxHP = dwMaxHP;
			var dwAura:uint = bytes.readUnsignedInt();
			s_.dwAura = dwAura;
			var dwMaxAura:uint = bytes.readUnsignedInt();
			s_.dwMaxAura = dwMaxAura;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFightHeroDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFightHeroDBInfo> = new Vector.<SFightHeroDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFightHeroDBInfo = SFightHeroDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wBattleType);
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeUnsignedInt(dwHP);
			bytes.writeUnsignedInt(dwMaxHP);
			bytes.writeUnsignedInt(dwAura);
			bytes.writeUnsignedInt(dwMaxAura);
		}

		public static function vectorToByteArray(vec:Vector.<SFightHeroDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFightHeroDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
