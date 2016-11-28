/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectAddStatus.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 一个UINT32参数的效果
	 */
	public final class SEffectAddStatus extends SEffectBase
	{
		public var eStatus:uint; //(枚举类型：EBStatusType)状态类型

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectAddStatus;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectAddStatus _name_={name_} eStatus={eStatus}/>;
			else
				topXml = <SEffectAddStatus eStatus={eStatus}/>;
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
			obj_.eStatus = eStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectAddStatus
		{
			var s_:SEffectAddStatus = new SEffectAddStatus();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var eStatus:uint = bytes.readUnsignedByte();
			s_.eStatus = eStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectAddStatus>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectAddStatus> = new Vector.<SEffectAddStatus>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectAddStatus = SEffectAddStatus.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(eStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectAddStatus>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectAddStatus in vec)
				s.toByteArray(bytes);
		}
	}
}
