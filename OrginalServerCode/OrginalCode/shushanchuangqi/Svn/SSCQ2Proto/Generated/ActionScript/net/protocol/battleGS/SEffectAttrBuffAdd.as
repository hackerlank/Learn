/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectAttrBuffAdd.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 加修改人物属性buff
	 */
	public final class SEffectAttrBuffAdd extends SEffectBase
	{
		public var eBuffType:uint; //(枚举类型：protoCommon.EFighterAttr)修改的属性枚举
		public var dwBuffKey:uint; //(无符号32位整数)查找这个buff的唯一ID
		public var dwSkillID:uint; //(无符号32位整数)该Buff的技能来源
		public var byLast:uint; //(无符号8位整数)持续时间
		public var dwValue:int; //(有符号32位整数)该Buff的效果值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectAttrBuffAdd;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectAttrBuffAdd _name_={name_} eBuffType={eBuffType} dwBuffKey={dwBuffKey} dwSkillID={dwSkillID} byLast={byLast} dwValue={dwValue}/>;
			else
				topXml = <SEffectAttrBuffAdd eBuffType={eBuffType} dwBuffKey={dwBuffKey} dwSkillID={dwSkillID} byLast={byLast} dwValue={dwValue}/>;
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
			obj_.eBuffType = eBuffType;
			obj_.dwBuffKey = dwBuffKey;
			obj_.dwSkillID = dwSkillID;
			obj_.byLast = byLast;
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectAttrBuffAdd
		{
			var s_:SEffectAttrBuffAdd = new SEffectAttrBuffAdd();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eBuffType:uint = bytes.readUnsignedByte();
			s_.eBuffType = eBuffType;
			var dwBuffKey:uint = bytes.readUnsignedInt();
			s_.dwBuffKey = dwBuffKey;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var byLast:uint = bytes.readUnsignedByte();
			s_.byLast = byLast;
			var dwValue:int = bytes.readInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectAttrBuffAdd>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectAttrBuffAdd> = new Vector.<SEffectAttrBuffAdd>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectAttrBuffAdd = SEffectAttrBuffAdd.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eBuffType);
			bytes.writeUnsignedInt(dwBuffKey);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeByte(byLast);
			bytes.writeInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectAttrBuffAdd>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectAttrBuffAdd in vec)
				s.toByteArray(bytes);
		}
	}
}
