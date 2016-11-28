/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLHBSkillInfo.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 技能信息
	 */
	public final class SLHBSkillInfo
	{
		public var eLHBSkillType:uint; //(枚举类型：ELHBSkillType)技能类型
		public var byCD:uint; //(无符号8位整数)技能CD
		public var wScore:uint; //(无符号32位整数)修为值
		public var byTimes:uint; //(无符号8位整数)使用次数

		/**
		 * 辅助创建函数
		 */
		public static function create(eLHBSkillType:uint, byCD:uint, wScore:uint, byTimes:uint):SLHBSkillInfo
		{
			var s_:SLHBSkillInfo = new SLHBSkillInfo();
			s_.eLHBSkillType = eLHBSkillType;
			s_.byCD = byCD;
			s_.wScore = wScore;
			s_.byTimes = byTimes;
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
				topXml = <SLHBSkillInfo _name_={name_} eLHBSkillType={eLHBSkillType} byCD={byCD} wScore={wScore} byTimes={byTimes}/>;
			else
				topXml = <SLHBSkillInfo eLHBSkillType={eLHBSkillType} byCD={byCD} wScore={wScore} byTimes={byTimes}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eLHBSkillType = eLHBSkillType;
			obj_.byCD = byCD;
			obj_.wScore = wScore;
			obj_.byTimes = byTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLHBSkillInfo
		{
			var s_:SLHBSkillInfo = new SLHBSkillInfo();
			var eLHBSkillType:uint = bytes.readUnsignedByte();
			s_.eLHBSkillType = eLHBSkillType;
			var byCD:uint = bytes.readUnsignedByte();
			s_.byCD = byCD;
			var wScore:uint = bytes.readUnsignedInt();
			s_.wScore = wScore;
			var byTimes:uint = bytes.readUnsignedByte();
			s_.byTimes = byTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLHBSkillInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLHBSkillInfo> = new Vector.<SLHBSkillInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLHBSkillInfo = SLHBSkillInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eLHBSkillType);
			bytes.writeByte(byCD);
			bytes.writeUnsignedInt(wScore);
			bytes.writeByte(byTimes);
		}

		public static function vectorToByteArray(vec:Vector.<SLHBSkillInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLHBSkillInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
