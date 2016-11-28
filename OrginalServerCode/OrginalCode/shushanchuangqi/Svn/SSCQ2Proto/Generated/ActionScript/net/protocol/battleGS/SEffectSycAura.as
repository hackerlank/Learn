/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectSycAura.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 同步灵气
	 */
	public final class SEffectSycAura extends SEffectBase
	{
		public var iAura:int; //(有符号32位整数)当前怒气值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectSycAura;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectSycAura _name_={name_} iAura={iAura}/>;
			else
				topXml = <SEffectSycAura iAura={iAura}/>;
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
			obj_.iAura = iAura;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectSycAura
		{
			var s_:SEffectSycAura = new SEffectSycAura();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var iAura:int = bytes.readInt();
			s_.iAura = iAura;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectSycAura>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectSycAura> = new Vector.<SEffectSycAura>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectSycAura = SEffectSycAura.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeInt(iAura);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectSycAura>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectSycAura in vec)
				s.toByteArray(bytes);
		}
	}
}
