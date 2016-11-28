/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSkillInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 技能信息
	 */
	public final class SSkillInfo
	{
		public var eType:uint; //(枚举类型：EGBSkill)技能类型

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint):SSkillInfo
		{
			var s_:SSkillInfo = new SSkillInfo();
			s_.eType = eType;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSkillInfo _name_={name_} eType={eType}/>;
			else
				topXml = <SSkillInfo eType={eType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSkillInfo
		{
			var s_:SSkillInfo = new SSkillInfo();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSkillInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSkillInfo> = new Vector.<SSkillInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSkillInfo = SSkillInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
		}

		public static function vectorToByteArray(vec:Vector.<SSkillInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSkillInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
