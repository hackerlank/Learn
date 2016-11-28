/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSkillData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 参与战斗的技能信息
	 */
	public final class SSkillData
	{
		public var dwSkillID:uint; //(无符号32位整数)技能id
		public var bySkillLvl:uint; //(无符号8位整数)技能等级
		public var bySkillQuality:uint; //(无符号8位整数)技能品质

		/**
		 * 辅助创建函数
		 */
		public static function create(dwSkillID:uint, bySkillLvl:uint, bySkillQuality:uint):SSkillData
		{
			var s_:SSkillData = new SSkillData();
			s_.dwSkillID = dwSkillID;
			s_.bySkillLvl = bySkillLvl;
			s_.bySkillQuality = bySkillQuality;
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
				topXml = <SSkillData _name_={name_} dwSkillID={dwSkillID} bySkillLvl={bySkillLvl} bySkillQuality={bySkillQuality}/>;
			else
				topXml = <SSkillData dwSkillID={dwSkillID} bySkillLvl={bySkillLvl} bySkillQuality={bySkillQuality}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwSkillID = dwSkillID;
			obj_.bySkillLvl = bySkillLvl;
			obj_.bySkillQuality = bySkillQuality;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSkillData
		{
			var s_:SSkillData = new SSkillData();
			var dwSkillID:uint = bytes.readUnsignedInt();
			s_.dwSkillID = dwSkillID;
			var bySkillLvl:uint = bytes.readUnsignedByte();
			s_.bySkillLvl = bySkillLvl;
			var bySkillQuality:uint = bytes.readUnsignedByte();
			s_.bySkillQuality = bySkillQuality;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSkillData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSkillData> = new Vector.<SSkillData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSkillData = SSkillData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwSkillID);
			bytes.writeByte(bySkillLvl);
			bytes.writeByte(bySkillQuality);
		}

		public static function vectorToByteArray(vec:Vector.<SSkillData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSkillData in vec)
				s.toByteArray(bytes);
		}
	}
}
