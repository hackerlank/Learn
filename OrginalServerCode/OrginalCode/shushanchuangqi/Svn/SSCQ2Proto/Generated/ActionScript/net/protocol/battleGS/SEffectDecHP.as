/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectDecHP.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 扣血
	 */
	public final class SEffectDecHP extends SEffectBase
	{
		public var dwSkillID:uint; //(无符号32位整数)扣血对应ID
		public var eSubHPType:uint; //(枚举类型：EBSubHPType)扣血伤害类型（物理/法术）
		public var eHPType:uint; //(枚举类型：EBModifyHPType)扣血类型
		public var dwDecHP:uint; //(无符号32位整数)扣掉的血

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectDecHP;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectDecHP _name_={name_} dwSkillID={dwSkillID} eSubHPType={eSubHPType} eHPType={eHPType} dwDecHP={dwDecHP}/>;
			else
				topXml = <SEffectDecHP dwSkillID={dwSkillID} eSubHPType={eSubHPType} eHPType={eHPType} dwDecHP={dwDecHP}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.dwSkillID = dwSkillID;
			obj_.eSubHPType = eSubHPType;
			obj_.eHPType = eHPType;
			obj_.dwDecHP = dwDecHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectDecHP
		{
			var s_:SEffectDecHP = new SEffectDecHP();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var eSubHPType:uint = bytes.readUnsignedByte();
			s_.eSubHPType = eSubHPType;
			var eHPType:uint = bytes.readUnsignedByte();
			s_.eHPType = eHPType;
			var dwDecHP:uint = bytes.readUnsignedInt();
			s_.dwDecHP = dwDecHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectDecHP>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectDecHP> = new Vector.<SEffectDecHP>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectDecHP = SEffectDecHP.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeByte(eSubHPType);
			bytes.writeByte(eHPType);
			bytes.writeUnsignedInt(dwDecHP);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectDecHP>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectDecHP in vec)
				s.toByteArray(bytes);
		}
	}
}
