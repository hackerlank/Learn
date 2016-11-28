/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectAddHP.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 加血
	 */
	public final class SEffectAddHP extends SEffectBase
	{
		public var dwSkillID:uint; //(无符号32位整数)加血对应ID
		public var eHPType:uint; //(枚举类型：EBModifyHPType)加血类型
		public var dwAddHP:uint; //(无符号32位整数)增加的血量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectAddHP;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectAddHP _name_={name_} dwSkillID={dwSkillID} eHPType={eHPType} dwAddHP={dwAddHP}/>;
			else
				topXml = <SEffectAddHP dwSkillID={dwSkillID} eHPType={eHPType} dwAddHP={dwAddHP}/>;
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
			obj_.eHPType = eHPType;
			obj_.dwAddHP = dwAddHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectAddHP
		{
			var s_:SEffectAddHP = new SEffectAddHP();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var eHPType:uint = bytes.readUnsignedByte();
			s_.eHPType = eHPType;
			var dwAddHP:uint = bytes.readUnsignedInt();
			s_.dwAddHP = dwAddHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectAddHP>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectAddHP> = new Vector.<SEffectAddHP>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectAddHP = SEffectAddHP.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeByte(eHPType);
			bytes.writeUnsignedInt(dwAddHP);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectAddHP>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectAddHP in vec)
				s.toByteArray(bytes);
		}
	}
}
