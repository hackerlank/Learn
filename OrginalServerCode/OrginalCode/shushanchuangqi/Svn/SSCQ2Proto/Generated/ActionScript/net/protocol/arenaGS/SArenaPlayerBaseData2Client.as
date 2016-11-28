/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaPlayerBaseData2Client.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 竞技场玩家基本信息，也是发给前端用的信息
	 */
	public final class SArenaPlayerBaseData2Client
	{
		public var dwRanking:uint; //(无符号32位整数)本段位排名
		public var dwScore:uint; //(无符号32位整数)积分
		public var eLevel:uint; //(枚举类型：EArenaLevel)段位
		public var dwTotalSize:uint; //(无符号32位整数)本段位总人数
		public var ePreLevel:uint; //(枚举类型：EArenaLevel)前次结算段位
		public var dwPreRank:uint; //(无符号32位整数)前次结算排名
		public var vecAwards:Vector.<SArenaAward>; //奖励包状态
		public var dwArenaCDTime:uint; //(无符号32位整数)历练冷却到期时间戳
		public var dwLadderCDTime:uint; //(无符号32位整数)天梯冷却到期时间戳
		public var wChallenge:uint; //(无符号16位整数)当前挑战次数，每天0点清0
		public var wChallengeBuyTimes:uint; //(无符号16位整数)购买的挑战次数
		public var wSelfReflush:uint; //(无符号16位整数)当前购买刷新次数
		public var wSelfFreeReflush:uint; //(无符号16位整数)当前VIP免费刷新次数
		public var byArenaWirship:uint; //(无符号8位整数)膜拜次数
		public var dwLastLadderRank:uint; //(无符号32位整数)上次结算天梯排名，0表示排名
		public var dwMinLadderRank:uint; //(无符号32位整数)天梯最好排名,0表示无排名
		public var vecFlushFigter:Vector.<SFlushFitherForClient>; //最近刷的对手
		public var vecWirshipFigter:Vector.<SArenaRank2Client>; //膜拜对象列表
		public var dwFighterPower:uint; //(无符号32位整数)战斗力
		public var dwLadderRank:uint; //(无符号32位整数)天梯排名，0表示未参与天梯，9999表示已经与机器战斗，但是不计入排名，否者为真实排名
		public var wLadderChallenge:uint; //(无符号16位整数)天梯挑战次数
		public var dwArenaAward:uint; //(无符号32位整数)历练挑战奖励，天梯挑战奖励领取状况，右到左1位历练，2位天梯
		public var dwLadderBuyTimes:uint; //(无符号32位整数)购买的天梯挑战次数
		public var dwLadderBuyTimesToday:uint; //(无符号32位整数)今日购买的天梯挑战次数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwRanking:uint, dwScore:uint, eLevel:uint, dwTotalSize:uint, ePreLevel:uint, 
			dwPreRank:uint, vecAwards:Vector.<SArenaAward>, dwArenaCDTime:uint, dwLadderCDTime:uint, wChallenge:uint, 
			wChallengeBuyTimes:uint, wSelfReflush:uint, wSelfFreeReflush:uint, byArenaWirship:uint, dwLastLadderRank:uint, 
			dwMinLadderRank:uint, vecFlushFigter:Vector.<SFlushFitherForClient>, vecWirshipFigter:Vector.<SArenaRank2Client>, dwFighterPower:uint, dwLadderRank:uint, 
			wLadderChallenge:uint, dwArenaAward:uint, dwLadderBuyTimes:uint, dwLadderBuyTimesToday:uint):SArenaPlayerBaseData2Client
		{
			var s_:SArenaPlayerBaseData2Client = new SArenaPlayerBaseData2Client();
			s_.dwRanking = dwRanking;
			s_.dwScore = dwScore;
			s_.eLevel = eLevel;
			s_.dwTotalSize = dwTotalSize;
			s_.ePreLevel = ePreLevel;
			s_.dwPreRank = dwPreRank;
			s_.vecAwards = vecAwards;
			s_.dwArenaCDTime = dwArenaCDTime;
			s_.dwLadderCDTime = dwLadderCDTime;
			s_.wChallenge = wChallenge;
			s_.wChallengeBuyTimes = wChallengeBuyTimes;
			s_.wSelfReflush = wSelfReflush;
			s_.wSelfFreeReflush = wSelfFreeReflush;
			s_.byArenaWirship = byArenaWirship;
			s_.dwLastLadderRank = dwLastLadderRank;
			s_.dwMinLadderRank = dwMinLadderRank;
			s_.vecFlushFigter = vecFlushFigter;
			s_.vecWirshipFigter = vecWirshipFigter;
			s_.dwFighterPower = dwFighterPower;
			s_.dwLadderRank = dwLadderRank;
			s_.wLadderChallenge = wLadderChallenge;
			s_.dwArenaAward = dwArenaAward;
			s_.dwLadderBuyTimes = dwLadderBuyTimes;
			s_.dwLadderBuyTimesToday = dwLadderBuyTimesToday;
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
				topXml = <SArenaPlayerBaseData2Client _name_={name_} dwRanking={dwRanking} dwScore={dwScore} eLevel={eLevel} dwTotalSize={dwTotalSize} ePreLevel={ePreLevel}
				 dwPreRank={dwPreRank} dwArenaCDTime={dwArenaCDTime} dwLadderCDTime={dwLadderCDTime} wChallenge={wChallenge}
				 wChallengeBuyTimes={wChallengeBuyTimes} wSelfReflush={wSelfReflush} wSelfFreeReflush={wSelfFreeReflush} byArenaWirship={byArenaWirship} dwLastLadderRank={dwLastLadderRank}
				 dwMinLadderRank={dwMinLadderRank} dwFighterPower={dwFighterPower} dwLadderRank={dwLadderRank}
				 wLadderChallenge={wLadderChallenge} dwArenaAward={dwArenaAward} dwLadderBuyTimes={dwLadderBuyTimes} dwLadderBuyTimesToday={dwLadderBuyTimesToday}/>;
			else
				topXml = <SArenaPlayerBaseData2Client dwRanking={dwRanking} dwScore={dwScore} eLevel={eLevel} dwTotalSize={dwTotalSize} ePreLevel={ePreLevel}
				 dwPreRank={dwPreRank} dwArenaCDTime={dwArenaCDTime} dwLadderCDTime={dwLadderCDTime} wChallenge={wChallenge}
				 wChallengeBuyTimes={wChallengeBuyTimes} wSelfReflush={wSelfReflush} wSelfFreeReflush={wSelfFreeReflush} byArenaWirship={byArenaWirship} dwLastLadderRank={dwLastLadderRank}
				 dwMinLadderRank={dwMinLadderRank} dwFighterPower={dwFighterPower} dwLadderRank={dwLadderRank}
				 wLadderChallenge={wLadderChallenge} dwArenaAward={dwArenaAward} dwLadderBuyTimes={dwLadderBuyTimes} dwLadderBuyTimesToday={dwLadderBuyTimesToday}/>;
			if(vecAwards != null)
			{
				var vecAwardsXml:XML = <Vec_SArenaAward _name_="vecAwards"/>;
				for each(var s1:SArenaAward in vecAwards)
					vecAwardsXml.appendChild(s1.toXML());
				topXml.appendChild(vecAwardsXml);
			}
			if(vecFlushFigter != null)
			{
				var vecFlushFigterXml:XML = <Vec_SFlushFitherForClient _name_="vecFlushFigter"/>;
				for each(var s2:SFlushFitherForClient in vecFlushFigter)
					vecFlushFigterXml.appendChild(s2.toXML());
				topXml.appendChild(vecFlushFigterXml);
			}
			if(vecWirshipFigter != null)
			{
				var vecWirshipFigterXml:XML = <Vec_SArenaRank2Client _name_="vecWirshipFigter"/>;
				for each(var s3:SArenaRank2Client in vecWirshipFigter)
					vecWirshipFigterXml.appendChild(s3.toXML());
				topXml.appendChild(vecWirshipFigterXml);
			}
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
			obj_.eLevel = eLevel;
			obj_.dwTotalSize = dwTotalSize;
			obj_.ePreLevel = ePreLevel;
			obj_.dwPreRank = dwPreRank;
			obj_.vecAwards = vecAwards;
			obj_.dwArenaCDTime = dwArenaCDTime;
			obj_.dwLadderCDTime = dwLadderCDTime;
			obj_.wChallenge = wChallenge;
			obj_.wChallengeBuyTimes = wChallengeBuyTimes;
			obj_.wSelfReflush = wSelfReflush;
			obj_.wSelfFreeReflush = wSelfFreeReflush;
			obj_.byArenaWirship = byArenaWirship;
			obj_.dwLastLadderRank = dwLastLadderRank;
			obj_.dwMinLadderRank = dwMinLadderRank;
			obj_.vecFlushFigter = vecFlushFigter;
			obj_.vecWirshipFigter = vecWirshipFigter;
			obj_.dwFighterPower = dwFighterPower;
			obj_.dwLadderRank = dwLadderRank;
			obj_.wLadderChallenge = wLadderChallenge;
			obj_.dwArenaAward = dwArenaAward;
			obj_.dwLadderBuyTimes = dwLadderBuyTimes;
			obj_.dwLadderBuyTimesToday = dwLadderBuyTimesToday;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaPlayerBaseData2Client
		{
			var s_:SArenaPlayerBaseData2Client = new SArenaPlayerBaseData2Client();
			var dwRanking:uint = bytes.readUnsignedInt();
			s_.dwRanking = dwRanking;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var eLevel:uint = bytes.readUnsignedByte();
			s_.eLevel = eLevel;
			var dwTotalSize:uint = bytes.readUnsignedInt();
			s_.dwTotalSize = dwTotalSize;
			var ePreLevel:uint = bytes.readUnsignedByte();
			s_.ePreLevel = ePreLevel;
			var dwPreRank:uint = bytes.readUnsignedInt();
			s_.dwPreRank = dwPreRank;
			var vecAwards:Vector.<SArenaAward> = SArenaAward.vectorFromByteArray(bytes);
			s_.vecAwards = vecAwards;
			var dwArenaCDTime:uint = bytes.readUnsignedInt();
			s_.dwArenaCDTime = dwArenaCDTime;
			var dwLadderCDTime:uint = bytes.readUnsignedInt();
			s_.dwLadderCDTime = dwLadderCDTime;
			var wChallenge:uint = bytes.readUnsignedShort();
			s_.wChallenge = wChallenge;
			var wChallengeBuyTimes:uint = bytes.readUnsignedShort();
			s_.wChallengeBuyTimes = wChallengeBuyTimes;
			var wSelfReflush:uint = bytes.readUnsignedShort();
			s_.wSelfReflush = wSelfReflush;
			var wSelfFreeReflush:uint = bytes.readUnsignedShort();
			s_.wSelfFreeReflush = wSelfFreeReflush;
			var byArenaWirship:uint = bytes.readUnsignedByte();
			s_.byArenaWirship = byArenaWirship;
			var dwLastLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLastLadderRank = dwLastLadderRank;
			var dwMinLadderRank:uint = bytes.readUnsignedInt();
			s_.dwMinLadderRank = dwMinLadderRank;
			var vecFlushFigter:Vector.<SFlushFitherForClient> = SFlushFitherForClient.vectorFromByteArray(bytes);
			s_.vecFlushFigter = vecFlushFigter;
			var vecWirshipFigter:Vector.<SArenaRank2Client> = SArenaRank2Client.vectorFromByteArray(bytes);
			s_.vecWirshipFigter = vecWirshipFigter;
			var dwFighterPower:uint = bytes.readUnsignedInt();
			s_.dwFighterPower = dwFighterPower;
			var dwLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLadderRank = dwLadderRank;
			var wLadderChallenge:uint = bytes.readUnsignedShort();
			s_.wLadderChallenge = wLadderChallenge;
			var dwArenaAward:uint = bytes.readUnsignedInt();
			s_.dwArenaAward = dwArenaAward;
			var dwLadderBuyTimes:uint = bytes.readUnsignedInt();
			s_.dwLadderBuyTimes = dwLadderBuyTimes;
			var dwLadderBuyTimesToday:uint = bytes.readUnsignedInt();
			s_.dwLadderBuyTimesToday = dwLadderBuyTimesToday;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaPlayerBaseData2Client>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaPlayerBaseData2Client> = new Vector.<SArenaPlayerBaseData2Client>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaPlayerBaseData2Client = SArenaPlayerBaseData2Client.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwRanking);
			bytes.writeUnsignedInt(dwScore);
			bytes.writeByte(eLevel);
			bytes.writeUnsignedInt(dwTotalSize);
			bytes.writeByte(ePreLevel);
			bytes.writeUnsignedInt(dwPreRank);
			SArenaAward.vectorToByteArray(vecAwards, bytes);
			bytes.writeUnsignedInt(dwArenaCDTime);
			bytes.writeUnsignedInt(dwLadderCDTime);
			bytes.writeShort(wChallenge);
			bytes.writeShort(wChallengeBuyTimes);
			bytes.writeShort(wSelfReflush);
			bytes.writeShort(wSelfFreeReflush);
			bytes.writeByte(byArenaWirship);
			bytes.writeUnsignedInt(dwLastLadderRank);
			bytes.writeUnsignedInt(dwMinLadderRank);
			SFlushFitherForClient.vectorToByteArray(vecFlushFigter, bytes);
			SArenaRank2Client.vectorToByteArray(vecWirshipFigter, bytes);
			bytes.writeUnsignedInt(dwFighterPower);
			bytes.writeUnsignedInt(dwLadderRank);
			bytes.writeShort(wLadderChallenge);
			bytes.writeUnsignedInt(dwArenaAward);
			bytes.writeUnsignedInt(dwLadderBuyTimes);
			bytes.writeUnsignedInt(dwLadderBuyTimesToday);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaPlayerBaseData2Client>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaPlayerBaseData2Client in vec)
				s.toByteArray(bytes);
		}
	}
}
