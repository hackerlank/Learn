/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleArenaInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import net.protocol.arenaGS.SArenaAward;
	import net.protocol.arenaGS.SFlushFighter;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eTypeArena:玩家斗剑信息
	 */
	public final class SRoleArenaInfo
	{
		public var dwLastAwardTimer:uint; //(无符号32位整数)上次刷的那次奖励，记录系统计算时间
		public var vecAwards:Vector.<SArenaAward>; //奖励包状态
		public var dwCDTime:uint; //(无符号32位整数)战斗冷却到期时间戳
		public var dwLadderCDTime:uint; //(无符号32位整数)天梯战斗冷却到期时间戳
		public var vecFlushFigter:Vector.<SFlushFighter>; //最近刷的对手

		/**
		 * 辅助创建函数
		 */
		public static function create(dwLastAwardTimer:uint, vecAwards:Vector.<SArenaAward>, dwCDTime:uint, dwLadderCDTime:uint, vecFlushFigter:Vector.<SFlushFighter>):SRoleArenaInfo
		{
			var s_:SRoleArenaInfo = new SRoleArenaInfo();
			s_.dwLastAwardTimer = dwLastAwardTimer;
			s_.vecAwards = vecAwards;
			s_.dwCDTime = dwCDTime;
			s_.dwLadderCDTime = dwLadderCDTime;
			s_.vecFlushFigter = vecFlushFigter;
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
				topXml = <SRoleArenaInfo _name_={name_} dwLastAwardTimer={dwLastAwardTimer} dwCDTime={dwCDTime} dwLadderCDTime={dwLadderCDTime}/>;
			else
				topXml = <SRoleArenaInfo dwLastAwardTimer={dwLastAwardTimer} dwCDTime={dwCDTime} dwLadderCDTime={dwLadderCDTime}/>;
			if(vecAwards != null)
			{
				var vecAwardsXml:XML = <Vec_SArenaAward _name_="vecAwards"/>;
				for each(var s1:SArenaAward in vecAwards)
					vecAwardsXml.appendChild(s1.toXML());
				topXml.appendChild(vecAwardsXml);
			}
			if(vecFlushFigter != null)
			{
				var vecFlushFigterXml:XML = <Vec_SFlushFighter _name_="vecFlushFigter"/>;
				for each(var s2:SFlushFighter in vecFlushFigter)
					vecFlushFigterXml.appendChild(s2.toXML());
				topXml.appendChild(vecFlushFigterXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwLastAwardTimer = dwLastAwardTimer;
			obj_.vecAwards = vecAwards;
			obj_.dwCDTime = dwCDTime;
			obj_.dwLadderCDTime = dwLadderCDTime;
			obj_.vecFlushFigter = vecFlushFigter;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleArenaInfo
		{
			var s_:SRoleArenaInfo = new SRoleArenaInfo();
			var dwLastAwardTimer:uint = bytes.readUnsignedInt();
			s_.dwLastAwardTimer = dwLastAwardTimer;
			var vecAwards:Vector.<SArenaAward> = SArenaAward.vectorFromByteArray(bytes);
			s_.vecAwards = vecAwards;
			var dwCDTime:uint = bytes.readUnsignedInt();
			s_.dwCDTime = dwCDTime;
			var dwLadderCDTime:uint = bytes.readUnsignedInt();
			s_.dwLadderCDTime = dwLadderCDTime;
			var vecFlushFigter:Vector.<SFlushFighter> = SFlushFighter.vectorFromByteArray(bytes);
			s_.vecFlushFigter = vecFlushFigter;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleArenaInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleArenaInfo> = new Vector.<SRoleArenaInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleArenaInfo = SRoleArenaInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwLastAwardTimer);
			SArenaAward.vectorToByteArray(vecAwards, bytes);
			bytes.writeUnsignedInt(dwCDTime);
			bytes.writeUnsignedInt(dwLadderCDTime);
			SFlushFighter.vectorToByteArray(vecFlushFigter, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleArenaInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleArenaInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
