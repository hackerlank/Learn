/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectPartBroken.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 部位破坏
	 */
	public final class SEffectPartBroken extends SEffectBase
	{
		public var wPartID:uint; //(无符号16位整数)部位ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectPartBroken;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectPartBroken _name_={name_} wPartID={wPartID}/>;
			else
				topXml = <SEffectPartBroken wPartID={wPartID}/>;
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
			obj_.wPartID = wPartID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectPartBroken
		{
			var s_:SEffectPartBroken = new SEffectPartBroken();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var wPartID:uint = bytes.readUnsignedShort();
			s_.wPartID = wPartID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectPartBroken>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectPartBroken> = new Vector.<SEffectPartBroken>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectPartBroken = SEffectPartBroken.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wPartID);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectPartBroken>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectPartBroken in vec)
				s.toByteArray(bytes);
		}
	}
}
