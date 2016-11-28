/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterSkill.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙技能信息
	 */
	public final class SFighterSkill
	{
		public var dwSkillID:uint; //(无符号32位整数)技能ID

		/**
		 * 辅助创建函数
		 */
		public static function create(dwSkillID:uint):SFighterSkill
		{
			var s_:SFighterSkill = new SFighterSkill();
			s_.dwSkillID = dwSkillID;
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
				topXml = <SFighterSkill _name_={name_} dwSkillID={dwSkillID}/>;
			else
				topXml = <SFighterSkill dwSkillID={dwSkillID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwSkillID = dwSkillID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterSkill
		{
			var s_:SFighterSkill = new SFighterSkill();
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterSkill>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterSkill> = new Vector.<SFighterSkill>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterSkill = SFighterSkill.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwSkillID);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterSkill>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterSkill in vec)
				s.toByteArray(bytes);
		}
	}
}
