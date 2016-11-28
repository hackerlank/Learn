/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSSBattleUseSkill.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 蜀山论剑场玩家使用技能返回的数据结构
	 */
	public final class SSSBattleUseSkill
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wHonor:uint; //(无符号16位整数)总荣誉值
		public var wSkillFlags:uint; //(无符号16位整数)技能使用位域,对应位表示技能是否已使用(低8位)
		public var dwCurHp:uint; //(无符号32位整数)当前血量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wHonor:uint, wSkillFlags:uint, dwCurHp:uint):SSSBattleUseSkill
		{
			var s_:SSSBattleUseSkill = new SSSBattleUseSkill();
			s_.qwRoleID = qwRoleID;
			s_.wHonor = wHonor;
			s_.wSkillFlags = wSkillFlags;
			s_.dwCurHp = dwCurHp;
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
				topXml = <SSSBattleUseSkill _name_={name_} qwRoleID={qwRoleID} wHonor={wHonor} wSkillFlags={wSkillFlags} dwCurHp={dwCurHp}/>;
			else
				topXml = <SSSBattleUseSkill qwRoleID={qwRoleID} wHonor={wHonor} wSkillFlags={wSkillFlags} dwCurHp={dwCurHp}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wHonor = wHonor;
			obj_.wSkillFlags = wSkillFlags;
			obj_.dwCurHp = dwCurHp;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSSBattleUseSkill
		{
			var s_:SSSBattleUseSkill = new SSSBattleUseSkill();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wHonor:uint = bytes.readUnsignedShort();
			s_.wHonor = wHonor;
			var wSkillFlags:uint = bytes.readUnsignedShort();
			s_.wSkillFlags = wSkillFlags;
			var dwCurHp:uint = bytes.readUnsignedInt();
			s_.dwCurHp = dwCurHp;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSSBattleUseSkill>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSSBattleUseSkill> = new Vector.<SSSBattleUseSkill>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSSBattleUseSkill = SSSBattleUseSkill.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wHonor);
			bytes.writeShort(wSkillFlags);
			bytes.writeUnsignedInt(dwCurHp);
		}

		public static function vectorToByteArray(vec:Vector.<SSSBattleUseSkill>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSSBattleUseSkill in vec)
				s.toByteArray(bytes);
		}
	}
}
