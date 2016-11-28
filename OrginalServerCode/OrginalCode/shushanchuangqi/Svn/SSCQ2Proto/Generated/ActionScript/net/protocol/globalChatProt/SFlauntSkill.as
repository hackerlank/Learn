/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlauntSkill.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 炫耀参与战斗的技能信息
	 */
	public final class SFlauntSkill
	{
		public var byIdx:uint; //(无符号8位整数)技能槽idx
		public var dwSkillID:uint; //(无符号32位整数)技能ID

		/**
		 * 辅助创建函数
		 */
		public static function create(byIdx:uint, dwSkillID:uint):SFlauntSkill
		{
			var s_:SFlauntSkill = new SFlauntSkill();
			s_.byIdx = byIdx;
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
				topXml = <SFlauntSkill _name_={name_} byIdx={byIdx} dwSkillID={dwSkillID}/>;
			else
				topXml = <SFlauntSkill byIdx={byIdx} dwSkillID={dwSkillID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIdx = byIdx;
			obj_.dwSkillID = dwSkillID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlauntSkill
		{
			var s_:SFlauntSkill = new SFlauntSkill();
			var byIdx:uint = bytes.readUnsignedByte();
			s_.byIdx = byIdx;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlauntSkill>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlauntSkill> = new Vector.<SFlauntSkill>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlauntSkill = SFlauntSkill.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIdx);
			bytes.writeUnsignedInt(dwSkillID);
		}

		public static function vectorToByteArray(vec:Vector.<SFlauntSkill>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlauntSkill in vec)
				s.toByteArray(bytes);
		}
	}
}
