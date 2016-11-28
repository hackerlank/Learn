/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucInTimer.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 时间判定
	 */
	public final class SucInTimer extends DgnSucCond
	{
		public var dwTotalTimer:uint; //(无符号32位整数)总计时间
		public var dwBeginTimer:uint; //(无符号32位整数)起始时间

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucInTimer;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucInTimer _name_={name_} dwTotalTimer={dwTotalTimer} dwBeginTimer={dwBeginTimer}/>;
			else
				topXml = <SucInTimer dwTotalTimer={dwTotalTimer} dwBeginTimer={dwBeginTimer}/>;
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
			obj_.dwTotalTimer = dwTotalTimer;
			obj_.dwBeginTimer = dwBeginTimer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucInTimer
		{
			var s_:SucInTimer = new SucInTimer();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwTotalTimer:uint = bytes.readUnsignedInt();
			s_.dwTotalTimer = dwTotalTimer;
			var dwBeginTimer:uint = bytes.readUnsignedInt();
			s_.dwBeginTimer = dwBeginTimer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucInTimer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucInTimer> = new Vector.<SucInTimer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucInTimer = SucInTimer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwTotalTimer);
			bytes.writeUnsignedInt(dwBeginTimer);
		}

		public static function vectorToByteArray(vec:Vector.<SucInTimer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucInTimer in vec)
				s.toByteArray(bytes);
		}
	}
}
