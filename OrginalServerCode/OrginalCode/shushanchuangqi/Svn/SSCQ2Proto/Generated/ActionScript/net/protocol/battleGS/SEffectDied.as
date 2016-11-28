/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectDied.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 我死了
	 */
	public final class SEffectDied extends SEffectBase
	{
		public var dwSkillID:uint; //(无符号32位整数)死亡时动画技能ID

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectDied;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectDied _name_={name_} dwSkillID={dwSkillID}/>;
			else
				topXml = <SEffectDied dwSkillID={dwSkillID}/>;
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
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectDied
		{
			var s_:SEffectDied = new SEffectDied();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectDied>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectDied> = new Vector.<SEffectDied>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectDied = SEffectDied.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwSkillID);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectDied>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectDied in vec)
				s.toByteArray(bytes);
		}
	}
}
