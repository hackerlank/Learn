/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectBrokenShield.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 破盾效果
	 */
	public final class SEffectBrokenShield extends SEffectBase
	{
		public var iPoint:int; //(有符号32位整数)盾牌耐久扣减值

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectBrokenShield;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectBrokenShield _name_={name_} iPoint={iPoint}/>;
			else
				topXml = <SEffectBrokenShield iPoint={iPoint}/>;
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
			obj_.iPoint = iPoint;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectBrokenShield
		{
			var s_:SEffectBrokenShield = new SEffectBrokenShield();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var iPoint:int = bytes.readInt();
			s_.iPoint = iPoint;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectBrokenShield>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectBrokenShield> = new Vector.<SEffectBrokenShield>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectBrokenShield = SEffectBrokenShield.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeInt(iPoint);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectBrokenShield>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectBrokenShield in vec)
				s.toByteArray(bytes);
		}
	}
}
