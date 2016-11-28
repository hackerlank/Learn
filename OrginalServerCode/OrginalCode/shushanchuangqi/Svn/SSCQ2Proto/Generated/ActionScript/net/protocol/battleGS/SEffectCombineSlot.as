/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectCombineSlot.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 连携槽相关操作效果
	 */
	public final class SEffectCombineSlot extends SEffectBase
	{
		public var eType:uint; //(枚举类型：ECombineSlotOPType)操作方式

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectCombineSlot;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectCombineSlot _name_={name_} eType={eType}/>;
			else
				topXml = <SEffectCombineSlot eType={eType}/>;
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
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectCombineSlot
		{
			var s_:SEffectCombineSlot = new SEffectCombineSlot();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectCombineSlot>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectCombineSlot> = new Vector.<SEffectCombineSlot>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectCombineSlot = SEffectCombineSlot.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eType);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectCombineSlot>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectCombineSlot in vec)
				s.toByteArray(bytes);
		}
	}
}
