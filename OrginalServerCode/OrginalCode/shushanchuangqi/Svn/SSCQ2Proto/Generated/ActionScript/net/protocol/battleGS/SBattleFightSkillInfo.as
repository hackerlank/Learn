/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleFightSkillInfo.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 参与战斗的技能信息
	 */
	public final class SBattleFightSkillInfo
	{
		public var dwSkillID:uint; //(无符号32位整数)技能ID
		public var dwSymboleID:uint; //(无符号32位整数)符文ID

		/**
		 * 辅助创建函数
		 */
		public static function create(dwSkillID:uint, dwSymboleID:uint):SBattleFightSkillInfo
		{
			var s_:SBattleFightSkillInfo = new SBattleFightSkillInfo();
			s_.dwSkillID = dwSkillID;
			s_.dwSymboleID = dwSymboleID;
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
				topXml = <SBattleFightSkillInfo _name_={name_} dwSkillID={dwSkillID} dwSymboleID={dwSymboleID}/>;
			else
				topXml = <SBattleFightSkillInfo dwSkillID={dwSkillID} dwSymboleID={dwSymboleID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwSkillID = dwSkillID;
			obj_.dwSymboleID = dwSymboleID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleFightSkillInfo
		{
			var s_:SBattleFightSkillInfo = new SBattleFightSkillInfo();
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var dwSymboleID:uint = bytes.readUnsignedInt();
			s_.dwSymboleID = dwSymboleID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleFightSkillInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleFightSkillInfo> = new Vector.<SBattleFightSkillInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleFightSkillInfo = SBattleFightSkillInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeUnsignedInt(dwSymboleID);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleFightSkillInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleFightSkillInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
