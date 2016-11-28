/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerSelfView.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家信息
	 */
	public final class PlayerSelfView
	{
		public var stData:PlayerSelfShipData; //基本信息
		public var dwRobTimes:uint; //(无符号32位整数)抢劫次数
		public var byDefenseTimes:uint; //(无符号8位整数)护送次数
		public var dwOpenShipTimes:uint; //(无符号32位整数)开船次数
		public var dwReFluseTimes:uint; //(无符号32位整数)刷新次数
		public var dwBuyRobTimes:uint; //(无符号32位整数)今日购买的抢劫次数
		public var dwBuyOpenShipTimesToday:uint; //(无符号32位整数)今日购买的运船次数
		public var dwBuyRlushShipTimesToday:uint; //(无符号32位整数)今日购买的刷新次数
		public var dwFreezBattleTime:uint; //(无符号32位整数)金船战斗冷却时间
		public var dwBeginTimer:uint; //(无符号32位整数)自己开船时间
		public var dwEndTimer:uint; //(无符号32位整数)自己船结束时间
		public var qwDefenseShip:BigInteger; //(无符号64位整数)我护送的船
		public var qwSelfShip:BigInteger; //(无符号64位整数)我自己的船
		public var strInviteDefenseName:String; //同意护送者名字

		/**
		 * 辅助创建函数
		 */
		public static function create(stData:PlayerSelfShipData, dwRobTimes:uint, byDefenseTimes:uint, dwOpenShipTimes:uint, dwReFluseTimes:uint, 
			dwBuyRobTimes:uint, dwBuyOpenShipTimesToday:uint, dwBuyRlushShipTimesToday:uint, dwFreezBattleTime:uint, dwBeginTimer:uint, 
			dwEndTimer:uint, qwDefenseShip:BigInteger, qwSelfShip:BigInteger, strInviteDefenseName:String):PlayerSelfView
		{
			var s_:PlayerSelfView = new PlayerSelfView();
			s_.stData = stData;
			s_.dwRobTimes = dwRobTimes;
			s_.byDefenseTimes = byDefenseTimes;
			s_.dwOpenShipTimes = dwOpenShipTimes;
			s_.dwReFluseTimes = dwReFluseTimes;
			s_.dwBuyRobTimes = dwBuyRobTimes;
			s_.dwBuyOpenShipTimesToday = dwBuyOpenShipTimesToday;
			s_.dwBuyRlushShipTimesToday = dwBuyRlushShipTimesToday;
			s_.dwFreezBattleTime = dwFreezBattleTime;
			s_.dwBeginTimer = dwBeginTimer;
			s_.dwEndTimer = dwEndTimer;
			s_.qwDefenseShip = qwDefenseShip;
			s_.qwSelfShip = qwSelfShip;
			s_.strInviteDefenseName = strInviteDefenseName;
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
				topXml = <PlayerSelfView _name_={name_} dwRobTimes={dwRobTimes} byDefenseTimes={byDefenseTimes} dwOpenShipTimes={dwOpenShipTimes} dwReFluseTimes={dwReFluseTimes}
				 dwBuyRobTimes={dwBuyRobTimes} dwBuyOpenShipTimesToday={dwBuyOpenShipTimesToday} dwBuyRlushShipTimesToday={dwBuyRlushShipTimesToday} dwFreezBattleTime={dwFreezBattleTime} dwBeginTimer={dwBeginTimer}
				 dwEndTimer={dwEndTimer} qwDefenseShip={qwDefenseShip} qwSelfShip={qwSelfShip} strInviteDefenseName={strInviteDefenseName}/>;
			else
				topXml = <PlayerSelfView dwRobTimes={dwRobTimes} byDefenseTimes={byDefenseTimes} dwOpenShipTimes={dwOpenShipTimes} dwReFluseTimes={dwReFluseTimes}
				 dwBuyRobTimes={dwBuyRobTimes} dwBuyOpenShipTimesToday={dwBuyOpenShipTimesToday} dwBuyRlushShipTimesToday={dwBuyRlushShipTimesToday} dwFreezBattleTime={dwFreezBattleTime} dwBeginTimer={dwBeginTimer}
				 dwEndTimer={dwEndTimer} qwDefenseShip={qwDefenseShip} qwSelfShip={qwSelfShip} strInviteDefenseName={strInviteDefenseName}/>;
			if(stData != null)
				topXml.appendChild(stData.toXML("stData"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.stData = stData;
			obj_.dwRobTimes = dwRobTimes;
			obj_.byDefenseTimes = byDefenseTimes;
			obj_.dwOpenShipTimes = dwOpenShipTimes;
			obj_.dwReFluseTimes = dwReFluseTimes;
			obj_.dwBuyRobTimes = dwBuyRobTimes;
			obj_.dwBuyOpenShipTimesToday = dwBuyOpenShipTimesToday;
			obj_.dwBuyRlushShipTimesToday = dwBuyRlushShipTimesToday;
			obj_.dwFreezBattleTime = dwFreezBattleTime;
			obj_.dwBeginTimer = dwBeginTimer;
			obj_.dwEndTimer = dwEndTimer;
			obj_.qwDefenseShip = qwDefenseShip;
			obj_.qwSelfShip = qwSelfShip;
			obj_.strInviteDefenseName = strInviteDefenseName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerSelfView
		{
			var s_:PlayerSelfView = new PlayerSelfView();
			var stData:PlayerSelfShipData = PlayerSelfShipData.fromByteArray(bytes);
			s_.stData = stData;
			var dwRobTimes:uint = bytes.readUnsignedInt();
			s_.dwRobTimes = dwRobTimes;
			var byDefenseTimes:uint = bytes.readUnsignedByte();
			s_.byDefenseTimes = byDefenseTimes;
			var dwOpenShipTimes:uint = bytes.readUnsignedInt();
			s_.dwOpenShipTimes = dwOpenShipTimes;
			var dwReFluseTimes:uint = bytes.readUnsignedInt();
			s_.dwReFluseTimes = dwReFluseTimes;
			var dwBuyRobTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyRobTimes = dwBuyRobTimes;
			var dwBuyOpenShipTimesToday:uint = bytes.readUnsignedInt();
			s_.dwBuyOpenShipTimesToday = dwBuyOpenShipTimesToday;
			var dwBuyRlushShipTimesToday:uint = bytes.readUnsignedInt();
			s_.dwBuyRlushShipTimesToday = dwBuyRlushShipTimesToday;
			var dwFreezBattleTime:uint = bytes.readUnsignedInt();
			s_.dwFreezBattleTime = dwFreezBattleTime;
			var dwBeginTimer:uint = bytes.readUnsignedInt();
			s_.dwBeginTimer = dwBeginTimer;
			var dwEndTimer:uint = bytes.readUnsignedInt();
			s_.dwEndTimer = dwEndTimer;
			var qwDefenseShip:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwDefenseShip = qwDefenseShip;
			var qwSelfShip:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwSelfShip = qwSelfShip;
			var strInviteDefenseName:String = BytesUtil.readString(bytes);
			s_.strInviteDefenseName = strInviteDefenseName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerSelfView>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerSelfView> = new Vector.<PlayerSelfView>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerSelfView = PlayerSelfView.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			stData.toByteArray(bytes);
			bytes.writeUnsignedInt(dwRobTimes);
			bytes.writeByte(byDefenseTimes);
			bytes.writeUnsignedInt(dwOpenShipTimes);
			bytes.writeUnsignedInt(dwReFluseTimes);
			bytes.writeUnsignedInt(dwBuyRobTimes);
			bytes.writeUnsignedInt(dwBuyOpenShipTimesToday);
			bytes.writeUnsignedInt(dwBuyRlushShipTimesToday);
			bytes.writeUnsignedInt(dwFreezBattleTime);
			bytes.writeUnsignedInt(dwBeginTimer);
			bytes.writeUnsignedInt(dwEndTimer);
			BytesUtil.writeUInt64(bytes, qwDefenseShip);
			BytesUtil.writeUInt64(bytes, qwSelfShip);
			BytesUtil.writeString(bytes, strInviteDefenseName);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerSelfView>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerSelfView in vec)
				s.toByteArray(bytes);
		}
	}
}
