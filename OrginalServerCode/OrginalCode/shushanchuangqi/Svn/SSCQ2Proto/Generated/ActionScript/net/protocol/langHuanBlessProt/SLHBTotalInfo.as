/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLHBTotalInfo.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 总的信息
	 */
	public final class SLHBTotalInfo
	{
		public var byState:uint; //(枚举类型：ELHBState)活动状态
		public var dwTime:uint; //(无符号32位整数)玩家持续时间
		public var dwXiuwei:uint; //(无符号32位整数)获得的修为值
		public var dwExp:uint; //(无符号32位整数)获得的经验值
		public var vecLHBSkillInfo:Vector.<SLHBSkillInfo>; //技能使用信息

		/**
		 * 辅助创建函数
		 */
		public static function create(byState:uint, dwTime:uint, dwXiuwei:uint, dwExp:uint, vecLHBSkillInfo:Vector.<SLHBSkillInfo>):SLHBTotalInfo
		{
			var s_:SLHBTotalInfo = new SLHBTotalInfo();
			s_.byState = byState;
			s_.dwTime = dwTime;
			s_.dwXiuwei = dwXiuwei;
			s_.dwExp = dwExp;
			s_.vecLHBSkillInfo = vecLHBSkillInfo;
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
				topXml = <SLHBTotalInfo _name_={name_} byState={byState} dwTime={dwTime} dwXiuwei={dwXiuwei} dwExp={dwExp}/>;
			else
				topXml = <SLHBTotalInfo byState={byState} dwTime={dwTime} dwXiuwei={dwXiuwei} dwExp={dwExp}/>;
			if(vecLHBSkillInfo != null)
			{
				var vecLHBSkillInfoXml:XML = <Vec_SLHBSkillInfo _name_="vecLHBSkillInfo"/>;
				for each(var s1:SLHBSkillInfo in vecLHBSkillInfo)
					vecLHBSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecLHBSkillInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byState = byState;
			obj_.dwTime = dwTime;
			obj_.dwXiuwei = dwXiuwei;
			obj_.dwExp = dwExp;
			obj_.vecLHBSkillInfo = vecLHBSkillInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLHBTotalInfo
		{
			var s_:SLHBTotalInfo = new SLHBTotalInfo();
			var byState:uint = bytes.readUnsignedByte();
			s_.byState = byState;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var dwXiuwei:uint = bytes.readUnsignedInt();
			s_.dwXiuwei = dwXiuwei;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var vecLHBSkillInfo:Vector.<SLHBSkillInfo> = SLHBSkillInfo.vectorFromByteArray(bytes);
			s_.vecLHBSkillInfo = vecLHBSkillInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLHBTotalInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLHBTotalInfo> = new Vector.<SLHBTotalInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLHBTotalInfo = SLHBTotalInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byState);
			bytes.writeUnsignedInt(dwTime);
			bytes.writeUnsignedInt(dwXiuwei);
			bytes.writeUnsignedInt(dwExp);
			SLHBSkillInfo.vectorToByteArray(vecLHBSkillInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SLHBTotalInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLHBTotalInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
