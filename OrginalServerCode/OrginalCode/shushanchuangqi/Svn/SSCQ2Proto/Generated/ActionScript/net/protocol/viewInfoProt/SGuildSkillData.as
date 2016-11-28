/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildSkillData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派技能信息
	 */
	public final class SGuildSkillData
	{
		public var dwGuildSkillID:uint; //(无符号32位整数)技能id
		public var byGuildSkillLvl:uint; //(无符号8位整数)技能等级

		/**
		 * 辅助创建函数
		 */
		public static function create(dwGuildSkillID:uint, byGuildSkillLvl:uint):SGuildSkillData
		{
			var s_:SGuildSkillData = new SGuildSkillData();
			s_.dwGuildSkillID = dwGuildSkillID;
			s_.byGuildSkillLvl = byGuildSkillLvl;
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
				topXml = <SGuildSkillData _name_={name_} dwGuildSkillID={dwGuildSkillID} byGuildSkillLvl={byGuildSkillLvl}/>;
			else
				topXml = <SGuildSkillData dwGuildSkillID={dwGuildSkillID} byGuildSkillLvl={byGuildSkillLvl}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwGuildSkillID = dwGuildSkillID;
			obj_.byGuildSkillLvl = byGuildSkillLvl;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildSkillData
		{
			var s_:SGuildSkillData = new SGuildSkillData();
			var dwGuildSkillID:uint = bytes.readUnsignedInt();
			s_.dwGuildSkillID = dwGuildSkillID;
			var byGuildSkillLvl:uint = bytes.readUnsignedByte();
			s_.byGuildSkillLvl = byGuildSkillLvl;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildSkillData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildSkillData> = new Vector.<SGuildSkillData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildSkillData = SGuildSkillData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwGuildSkillID);
			bytes.writeByte(byGuildSkillLvl);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildSkillData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildSkillData in vec)
				s.toByteArray(bytes);
		}
	}
}
