/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectSycHP.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 同步血量和血上限
	 */
	public final class SEffectSycHP extends SEffectBase
	{
		public var dwHP:uint; //(无符号32位整数)当前血量
		public var dwHPMax:uint; //(无符号32位整数)当前血上限

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectSycHP;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectSycHP _name_={name_} dwHP={dwHP} dwHPMax={dwHPMax}/>;
			else
				topXml = <SEffectSycHP dwHP={dwHP} dwHPMax={dwHPMax}/>;
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
			obj_.dwHP = dwHP;
			obj_.dwHPMax = dwHPMax;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectSycHP
		{
			var s_:SEffectSycHP = new SEffectSycHP();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			var dwHPMax:uint = bytes.readUnsignedInt();
			s_.dwHPMax = dwHPMax;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectSycHP>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectSycHP> = new Vector.<SEffectSycHP>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectSycHP = SEffectSycHP.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwHP);
			bytes.writeUnsignedInt(dwHPMax);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectSycHP>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectSycHP in vec)
				s.toByteArray(bytes);
		}
	}
}