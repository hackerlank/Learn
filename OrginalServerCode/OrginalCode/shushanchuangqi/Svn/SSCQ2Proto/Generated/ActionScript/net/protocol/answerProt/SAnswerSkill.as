/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAnswerSkill.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 答题技能信息
	 */
	public final class SAnswerSkill
	{
		public var eSkillType:uint; //(枚举类型：EAnswerSkill)技能ID
		public var byRemain:uint; //(无符号8位整数)剩余次数

		/**
		 * 辅助创建函数
		 */
		public static function create(eSkillType:uint, byRemain:uint):SAnswerSkill
		{
			var s_:SAnswerSkill = new SAnswerSkill();
			s_.eSkillType = eSkillType;
			s_.byRemain = byRemain;
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
				topXml = <SAnswerSkill _name_={name_} eSkillType={eSkillType} byRemain={byRemain}/>;
			else
				topXml = <SAnswerSkill eSkillType={eSkillType} byRemain={byRemain}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eSkillType = eSkillType;
			obj_.byRemain = byRemain;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAnswerSkill
		{
			var s_:SAnswerSkill = new SAnswerSkill();
			var eSkillType:uint = bytes.readUnsignedByte();
			s_.eSkillType = eSkillType;
			var byRemain:uint = bytes.readUnsignedByte();
			s_.byRemain = byRemain;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAnswerSkill>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAnswerSkill> = new Vector.<SAnswerSkill>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAnswerSkill = SAnswerSkill.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eSkillType);
			bytes.writeByte(byRemain);
		}

		public static function vectorToByteArray(vec:Vector.<SAnswerSkill>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAnswerSkill in vec)
				s.toByteArray(bytes);
		}
	}
}
