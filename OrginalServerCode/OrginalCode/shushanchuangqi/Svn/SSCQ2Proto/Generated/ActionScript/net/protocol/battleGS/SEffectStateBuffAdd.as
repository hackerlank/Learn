/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectStateBuffAdd.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 加状态Buff
	 */
	public final class SEffectStateBuffAdd extends SEffectBase
	{
		public var dwBuffKey:uint; //(无符号32位整数)查找这个buff的唯一ID
		public var eStateBuffType:uint; //(枚举类型：EBStateBuffType)状态枚举
		public var dwSkillID:uint; //(无符号32位整数)该Buff的技能来源
		public var dwBaseSkillID:uint; //(无符号32位整数)初始技能ID（SkillBase表的ID）
		public var byLast:uint; //(无符号8位整数)持续时间
		public var dwValue:int; //(有符号32位整数)该Buff的效果值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectStateBuffAdd;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectStateBuffAdd _name_={name_} dwBuffKey={dwBuffKey} eStateBuffType={eStateBuffType} dwSkillID={dwSkillID} dwBaseSkillID={dwBaseSkillID} byLast={byLast}
				 dwValue={dwValue}/>;
			else
				topXml = <SEffectStateBuffAdd dwBuffKey={dwBuffKey} eStateBuffType={eStateBuffType} dwSkillID={dwSkillID} dwBaseSkillID={dwBaseSkillID} byLast={byLast}
				 dwValue={dwValue}/>;
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
			obj_.dwBuffKey = dwBuffKey;
			obj_.eStateBuffType = eStateBuffType;
			obj_.dwSkillID = dwSkillID;
			obj_.dwBaseSkillID = dwBaseSkillID;
			obj_.byLast = byLast;
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectStateBuffAdd
		{
			var s_:SEffectStateBuffAdd = new SEffectStateBuffAdd();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwBuffKey:uint = bytes.readUnsignedInt();
			s_.dwBuffKey = dwBuffKey;
			var eStateBuffType:uint = bytes.readUnsignedShort();
			s_.eStateBuffType = eStateBuffType;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var dwBaseSkillID:uint = bytes.readUnsignedInt();
			s_.dwBaseSkillID = dwBaseSkillID;
			var byLast:uint = bytes.readUnsignedByte();
			s_.byLast = byLast;
			var dwValue:int = bytes.readInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectStateBuffAdd>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectStateBuffAdd> = new Vector.<SEffectStateBuffAdd>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectStateBuffAdd = SEffectStateBuffAdd.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwBuffKey);
			bytes.writeShort(eStateBuffType);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeUnsignedInt(dwBaseSkillID);
			bytes.writeByte(byLast);
			bytes.writeInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectStateBuffAdd>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectStateBuffAdd in vec)
				s.toByteArray(bytes);
		}
	}
}
