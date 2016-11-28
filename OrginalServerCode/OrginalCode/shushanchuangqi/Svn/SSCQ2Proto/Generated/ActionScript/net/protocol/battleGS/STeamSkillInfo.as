/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STeamSkillInfo.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 队伍技能
	 */
	public final class STeamSkillInfo
	{
		public var byIndex:uint; //(无符号8位整数)队伍技能唯一编号
		public var byTeamID:uint; //(无符号8位整数)队伍ID
		public var dwSkillID:uint; //(无符号32位整数)技能ID

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, byTeamID:uint, dwSkillID:uint):STeamSkillInfo
		{
			var s_:STeamSkillInfo = new STeamSkillInfo();
			s_.byIndex = byIndex;
			s_.byTeamID = byTeamID;
			s_.dwSkillID = dwSkillID;
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
				topXml = <STeamSkillInfo _name_={name_} byIndex={byIndex} byTeamID={byTeamID} dwSkillID={dwSkillID}/>;
			else
				topXml = <STeamSkillInfo byIndex={byIndex} byTeamID={byTeamID} dwSkillID={dwSkillID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.byTeamID = byTeamID;
			obj_.dwSkillID = dwSkillID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STeamSkillInfo
		{
			var s_:STeamSkillInfo = new STeamSkillInfo();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var byTeamID:uint = bytes.readUnsignedByte();
			s_.byTeamID = byTeamID;
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STeamSkillInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STeamSkillInfo> = new Vector.<STeamSkillInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STeamSkillInfo = STeamSkillInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			bytes.writeByte(byTeamID);
			bytes.writeUnsignedInt(dwSkillID);
		}

		public static function vectorToByteArray(vec:Vector.<STeamSkillInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STeamSkillInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
