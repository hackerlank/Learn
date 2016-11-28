/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectShieldAbsorb.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 盾牌吸收伤害
	 */
	public final class SEffectShieldAbsorb extends SEffectBase
	{
		public var eType:uint; //(枚举类型：EBSheildAbsorbType)吸收类型
		public var dwHP:uint; //(无符号32位整数)吸收的数值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectShieldAbsorb;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectShieldAbsorb _name_={name_} eType={eType} dwHP={dwHP}/>;
			else
				topXml = <SEffectShieldAbsorb eType={eType} dwHP={dwHP}/>;
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
			obj_.eType = eType;
			obj_.dwHP = dwHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectShieldAbsorb
		{
			var s_:SEffectShieldAbsorb = new SEffectShieldAbsorb();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectShieldAbsorb>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectShieldAbsorb> = new Vector.<SEffectShieldAbsorb>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectShieldAbsorb = SEffectShieldAbsorb.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eType);
			bytes.writeUnsignedInt(dwHP);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectShieldAbsorb>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectShieldAbsorb in vec)
				s.toByteArray(bytes);
		}
	}
}
