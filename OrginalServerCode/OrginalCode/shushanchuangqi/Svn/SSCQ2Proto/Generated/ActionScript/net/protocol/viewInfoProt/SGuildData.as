/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildData.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派信息
	 */
	public final class SGuildData
	{
		public var strName:String; //帮派名称
		public var byGuildLvl:uint; //(无符号8位整数)帮派等级
		public var vecGuildSkill:Vector.<SGuildSkillData>; //帮派技能

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, byGuildLvl:uint, vecGuildSkill:Vector.<SGuildSkillData>):SGuildData
		{
			var s_:SGuildData = new SGuildData();
			s_.strName = strName;
			s_.byGuildLvl = byGuildLvl;
			s_.vecGuildSkill = vecGuildSkill;
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
				topXml = <SGuildData _name_={name_} strName={strName} byGuildLvl={byGuildLvl}/>;
			else
				topXml = <SGuildData strName={strName} byGuildLvl={byGuildLvl}/>;
			if(vecGuildSkill != null)
			{
				var vecGuildSkillXml:XML = <Vec_SGuildSkillData _name_="vecGuildSkill"/>;
				for each(var s1:SGuildSkillData in vecGuildSkill)
					vecGuildSkillXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildSkillXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.byGuildLvl = byGuildLvl;
			obj_.vecGuildSkill = vecGuildSkill;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildData
		{
			var s_:SGuildData = new SGuildData();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byGuildLvl:uint = bytes.readUnsignedByte();
			s_.byGuildLvl = byGuildLvl;
			var vecGuildSkill:Vector.<SGuildSkillData> = SGuildSkillData.vectorFromByteArray(bytes);
			s_.vecGuildSkill = vecGuildSkill;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildData> = new Vector.<SGuildData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildData = SGuildData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byGuildLvl);
			SGuildSkillData.vectorToByteArray(vecGuildSkill, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildData in vec)
				s.toByteArray(bytes);
		}
	}
}
