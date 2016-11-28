/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectCounter.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 反击
	 */
	public final class SEffectCounter extends SEffectBase
	{
		public var eSubHPType:uint; //(枚举类型：EBSubHPType)扣血伤害类型（物理/法术）
		public var eHPType:uint; //(枚举类型：EBModifyHPType)扣血类型
		public var dwDecHP:uint; //(无符号32位整数)反击的伤害量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectCounter;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectCounter _name_={name_} eSubHPType={eSubHPType} eHPType={eHPType} dwDecHP={dwDecHP}/>;
			else
				topXml = <SEffectCounter eSubHPType={eSubHPType} eHPType={eHPType} dwDecHP={dwDecHP}/>;
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
			obj_.eSubHPType = eSubHPType;
			obj_.eHPType = eHPType;
			obj_.dwDecHP = dwDecHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectCounter
		{
			var s_:SEffectCounter = new SEffectCounter();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eSubHPType:uint = bytes.readUnsignedByte();
			s_.eSubHPType = eSubHPType;
			var eHPType:uint = bytes.readUnsignedByte();
			s_.eHPType = eHPType;
			var dwDecHP:uint = bytes.readUnsignedInt();
			s_.dwDecHP = dwDecHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectCounter>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectCounter> = new Vector.<SEffectCounter>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectCounter = SEffectCounter.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eSubHPType);
			bytes.writeByte(eHPType);
			bytes.writeUnsignedInt(dwDecHP);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectCounter>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectCounter in vec)
				s.toByteArray(bytes);
		}
	}
}
