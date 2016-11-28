/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlushFitherForClient.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 客户端竞技场的对手
	 */
	public final class SFlushFitherForClient
	{
		public var stFlushFighter:SFlushFighter; //id，小于65535为机器人，读怪物列表
		public var wGroup:uint; //(无符号32位整数)
		public var eLevel:uint; //(枚举类型：EArenaLevel)段位,无段位表示没有加入竞技场
		public var stFighter:SArenaFighter; //其他属性
		public var dwFighterPower:uint; //(无符号32位整数)战斗力
		public var dwLadderRank:uint; //(无符号32位整数)天梯排名
		public var dwArenaRank:uint; //(无符号32位整数)历练排名

		/**
		 * 辅助创建函数
		 */
		public static function create(stFlushFighter:SFlushFighter, wGroup:uint, eLevel:uint, stFighter:SArenaFighter, dwFighterPower:uint, 
			dwLadderRank:uint, dwArenaRank:uint):SFlushFitherForClient
		{
			var s_:SFlushFitherForClient = new SFlushFitherForClient();
			s_.stFlushFighter = stFlushFighter;
			s_.wGroup = wGroup;
			s_.eLevel = eLevel;
			s_.stFighter = stFighter;
			s_.dwFighterPower = dwFighterPower;
			s_.dwLadderRank = dwLadderRank;
			s_.dwArenaRank = dwArenaRank;
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
				topXml = <SFlushFitherForClient _name_={name_} wGroup={wGroup} eLevel={eLevel} dwFighterPower={dwFighterPower}
				 dwLadderRank={dwLadderRank} dwArenaRank={dwArenaRank}/>;
			else
				topXml = <SFlushFitherForClient wGroup={wGroup} eLevel={eLevel} dwFighterPower={dwFighterPower}
				 dwLadderRank={dwLadderRank} dwArenaRank={dwArenaRank}/>;
			if(stFlushFighter != null)
				topXml.appendChild(stFlushFighter.toXML("stFlushFighter"));
			if(stFighter != null)
				topXml.appendChild(stFighter.toXML("stFighter"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.stFlushFighter = stFlushFighter;
			obj_.wGroup = wGroup;
			obj_.eLevel = eLevel;
			obj_.stFighter = stFighter;
			obj_.dwFighterPower = dwFighterPower;
			obj_.dwLadderRank = dwLadderRank;
			obj_.dwArenaRank = dwArenaRank;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlushFitherForClient
		{
			var s_:SFlushFitherForClient = new SFlushFitherForClient();
			var stFlushFighter:SFlushFighter = SFlushFighter.fromByteArray(bytes);
			s_.stFlushFighter = stFlushFighter;
			var wGroup:uint = bytes.readUnsignedInt();
			s_.wGroup = wGroup;
			var eLevel:uint = bytes.readUnsignedByte();
			s_.eLevel = eLevel;
			var stFighter:SArenaFighter = SArenaFighter.fromByteArray(bytes);
			s_.stFighter = stFighter;
			var dwFighterPower:uint = bytes.readUnsignedInt();
			s_.dwFighterPower = dwFighterPower;
			var dwLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLadderRank = dwLadderRank;
			var dwArenaRank:uint = bytes.readUnsignedInt();
			s_.dwArenaRank = dwArenaRank;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlushFitherForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlushFitherForClient> = new Vector.<SFlushFitherForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlushFitherForClient = SFlushFitherForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			stFlushFighter.toByteArray(bytes);
			bytes.writeUnsignedInt(wGroup);
			bytes.writeByte(eLevel);
			stFighter.toByteArray(bytes);
			bytes.writeUnsignedInt(dwFighterPower);
			bytes.writeUnsignedInt(dwLadderRank);
			bytes.writeUnsignedInt(dwArenaRank);
		}

		public static function vectorToByteArray(vec:Vector.<SFlushFitherForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlushFitherForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
