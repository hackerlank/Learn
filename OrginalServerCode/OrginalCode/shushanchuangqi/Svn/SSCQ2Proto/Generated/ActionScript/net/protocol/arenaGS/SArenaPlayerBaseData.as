/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaPlayerBaseData.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 竞技场玩家基本信息
	 */
	public final class SArenaPlayerBaseData
	{
		public var dwRanking:uint; //(无符号32位整数)同积分序号
		public var dwScore:uint; //(无符号32位整数)积分
		public var dwLadderRank:uint; //(无符号32位整数)天梯排名0表示天梯功未开启，10000表示天梯功能已开启未挑机器人，9999表示已挑战机器人
		public var eLevel:uint; //(枚举类型：EArenaLevel)竞技等级
		public var dwLastFlushTime:uint; //(无符号32位整数)最近客户端刷新时间
		public var dwLastRank:uint; //(无符号32位整数)最近结算排名
		public var eLastLevel:uint; //(枚举类型：EArenaLevel)最近结算之前段位
		public var dwFighterPower:uint; //(无符号32位整数)战斗力
		public var byQuality:uint; //(无符号8位整数)品质
		public var byVIPLevel:uint; //(无符号8位整数)VIP等级
		public var dwLastLadderRank:uint; //(无符号32位整数)最近结算排名

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRanking:uint, dwScore:uint, dwLadderRank:uint, eLevel:uint, dwLastFlushTime:uint, 
			dwLastRank:uint, eLastLevel:uint, dwFighterPower:uint, byQuality:uint, byVIPLevel:uint, 
			dwLastLadderRank:uint):SArenaPlayerBaseData
		{
			var s_:SArenaPlayerBaseData = new SArenaPlayerBaseData();
			s_.dwRanking = dwRanking;
			s_.dwScore = dwScore;
			s_.dwLadderRank = dwLadderRank;
			s_.eLevel = eLevel;
			s_.dwLastFlushTime = dwLastFlushTime;
			s_.dwLastRank = dwLastRank;
			s_.eLastLevel = eLastLevel;
			s_.dwFighterPower = dwFighterPower;
			s_.byQuality = byQuality;
			s_.byVIPLevel = byVIPLevel;
			s_.dwLastLadderRank = dwLastLadderRank;
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
				topXml = <SArenaPlayerBaseData _name_={name_} dwRanking={dwRanking} dwScore={dwScore} dwLadderRank={dwLadderRank} eLevel={eLevel} dwLastFlushTime={dwLastFlushTime}
				 dwLastRank={dwLastRank} eLastLevel={eLastLevel} dwFighterPower={dwFighterPower} byQuality={byQuality} byVIPLevel={byVIPLevel}
				 dwLastLadderRank={dwLastLadderRank}/>;
			else
				topXml = <SArenaPlayerBaseData dwRanking={dwRanking} dwScore={dwScore} dwLadderRank={dwLadderRank} eLevel={eLevel} dwLastFlushTime={dwLastFlushTime}
				 dwLastRank={dwLastRank} eLastLevel={eLastLevel} dwFighterPower={dwFighterPower} byQuality={byQuality} byVIPLevel={byVIPLevel}
				 dwLastLadderRank={dwLastLadderRank}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwRanking = dwRanking;
			obj_.dwScore = dwScore;
			obj_.dwLadderRank = dwLadderRank;
			obj_.eLevel = eLevel;
			obj_.dwLastFlushTime = dwLastFlushTime;
			obj_.dwLastRank = dwLastRank;
			obj_.eLastLevel = eLastLevel;
			obj_.dwFighterPower = dwFighterPower;
			obj_.byQuality = byQuality;
			obj_.byVIPLevel = byVIPLevel;
			obj_.dwLastLadderRank = dwLastLadderRank;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaPlayerBaseData
		{
			var s_:SArenaPlayerBaseData = new SArenaPlayerBaseData();
			var dwRanking:uint = bytes.readUnsignedInt();
			s_.dwRanking = dwRanking;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var dwLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLadderRank = dwLadderRank;
			var eLevel:uint = bytes.readUnsignedByte();
			s_.eLevel = eLevel;
			var dwLastFlushTime:uint = bytes.readUnsignedInt();
			s_.dwLastFlushTime = dwLastFlushTime;
			var dwLastRank:uint = bytes.readUnsignedInt();
			s_.dwLastRank = dwLastRank;
			var eLastLevel:uint = bytes.readUnsignedByte();
			s_.eLastLevel = eLastLevel;
			var dwFighterPower:uint = bytes.readUnsignedInt();
			s_.dwFighterPower = dwFighterPower;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var dwLastLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLastLadderRank = dwLastLadderRank;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaPlayerBaseData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaPlayerBaseData> = new Vector.<SArenaPlayerBaseData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaPlayerBaseData = SArenaPlayerBaseData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRanking);
			bytes.writeUnsignedInt(dwScore);
			bytes.writeUnsignedInt(dwLadderRank);
			bytes.writeByte(eLevel);
			bytes.writeUnsignedInt(dwLastFlushTime);
			bytes.writeUnsignedInt(dwLastRank);
			bytes.writeByte(eLastLevel);
			bytes.writeUnsignedInt(dwFighterPower);
			bytes.writeByte(byQuality);
			bytes.writeByte(byVIPLevel);
			bytes.writeUnsignedInt(dwLastLadderRank);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaPlayerBaseData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaPlayerBaseData in vec)
				s.toByteArray(bytes);
		}
	}
}
