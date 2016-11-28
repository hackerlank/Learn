/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerSelfShipData.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家数据库信息
	 */
	public final class PlayerSelfShipData
	{
		public var dwBuyOpenShipTimes:uint; //(无符号32位整数)购买的运船次数
		public var dwBuyRoBShipTimes:uint; //(无符号32位整数)购买的抢劫次数
		public var dwBuyReflushShipTimes:uint; //(无符号32位整数)购买的刷新次数
		public var wReflushShip:uint; //(无符号16位整数)刷出来的船
		public var dwReflushShipTimer:uint; //(无符号32位整数)刷船的时间
		public var qwInviteDefense:BigInteger; //(无符号64位整数)邀请的护送者
		public var dwInviteDefenseAgreeTime:uint; //(无符号32位整数)别人同意护送的时间
		public var dwInviteDefensePoint:uint; //(无符号32位整数)护送者战斗力
		public var byInviteDefenseLevel:uint; //(无符号8位整数)护送者等级
		public var byInviteDefenseColor:uint; //(无符号8位整数)护送者颜色
		public var qwAgreeDefenseShipOwer:BigInteger; //(无符号64位整数)我同意护送的船
		public var dwAgreeDefenseShipOwerTime:uint; //(无符号32位整数)我同意护送的时间

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBuyOpenShipTimes:uint, dwBuyRoBShipTimes:uint, dwBuyReflushShipTimes:uint, wReflushShip:uint, dwReflushShipTimer:uint, 
			qwInviteDefense:BigInteger, dwInviteDefenseAgreeTime:uint, dwInviteDefensePoint:uint, byInviteDefenseLevel:uint, byInviteDefenseColor:uint, 
			qwAgreeDefenseShipOwer:BigInteger, dwAgreeDefenseShipOwerTime:uint):PlayerSelfShipData
		{
			var s_:PlayerSelfShipData = new PlayerSelfShipData();
			s_.dwBuyOpenShipTimes = dwBuyOpenShipTimes;
			s_.dwBuyRoBShipTimes = dwBuyRoBShipTimes;
			s_.dwBuyReflushShipTimes = dwBuyReflushShipTimes;
			s_.wReflushShip = wReflushShip;
			s_.dwReflushShipTimer = dwReflushShipTimer;
			s_.qwInviteDefense = qwInviteDefense;
			s_.dwInviteDefenseAgreeTime = dwInviteDefenseAgreeTime;
			s_.dwInviteDefensePoint = dwInviteDefensePoint;
			s_.byInviteDefenseLevel = byInviteDefenseLevel;
			s_.byInviteDefenseColor = byInviteDefenseColor;
			s_.qwAgreeDefenseShipOwer = qwAgreeDefenseShipOwer;
			s_.dwAgreeDefenseShipOwerTime = dwAgreeDefenseShipOwerTime;
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
				topXml = <PlayerSelfShipData _name_={name_} dwBuyOpenShipTimes={dwBuyOpenShipTimes} dwBuyRoBShipTimes={dwBuyRoBShipTimes} dwBuyReflushShipTimes={dwBuyReflushShipTimes} wReflushShip={wReflushShip} dwReflushShipTimer={dwReflushShipTimer}
				 qwInviteDefense={qwInviteDefense} dwInviteDefenseAgreeTime={dwInviteDefenseAgreeTime} dwInviteDefensePoint={dwInviteDefensePoint} byInviteDefenseLevel={byInviteDefenseLevel} byInviteDefenseColor={byInviteDefenseColor}
				 qwAgreeDefenseShipOwer={qwAgreeDefenseShipOwer} dwAgreeDefenseShipOwerTime={dwAgreeDefenseShipOwerTime}/>;
			else
				topXml = <PlayerSelfShipData dwBuyOpenShipTimes={dwBuyOpenShipTimes} dwBuyRoBShipTimes={dwBuyRoBShipTimes} dwBuyReflushShipTimes={dwBuyReflushShipTimes} wReflushShip={wReflushShip} dwReflushShipTimer={dwReflushShipTimer}
				 qwInviteDefense={qwInviteDefense} dwInviteDefenseAgreeTime={dwInviteDefenseAgreeTime} dwInviteDefensePoint={dwInviteDefensePoint} byInviteDefenseLevel={byInviteDefenseLevel} byInviteDefenseColor={byInviteDefenseColor}
				 qwAgreeDefenseShipOwer={qwAgreeDefenseShipOwer} dwAgreeDefenseShipOwerTime={dwAgreeDefenseShipOwerTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBuyOpenShipTimes = dwBuyOpenShipTimes;
			obj_.dwBuyRoBShipTimes = dwBuyRoBShipTimes;
			obj_.dwBuyReflushShipTimes = dwBuyReflushShipTimes;
			obj_.wReflushShip = wReflushShip;
			obj_.dwReflushShipTimer = dwReflushShipTimer;
			obj_.qwInviteDefense = qwInviteDefense;
			obj_.dwInviteDefenseAgreeTime = dwInviteDefenseAgreeTime;
			obj_.dwInviteDefensePoint = dwInviteDefensePoint;
			obj_.byInviteDefenseLevel = byInviteDefenseLevel;
			obj_.byInviteDefenseColor = byInviteDefenseColor;
			obj_.qwAgreeDefenseShipOwer = qwAgreeDefenseShipOwer;
			obj_.dwAgreeDefenseShipOwerTime = dwAgreeDefenseShipOwerTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerSelfShipData
		{
			var s_:PlayerSelfShipData = new PlayerSelfShipData();
			var dwBuyOpenShipTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyOpenShipTimes = dwBuyOpenShipTimes;
			var dwBuyRoBShipTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyRoBShipTimes = dwBuyRoBShipTimes;
			var dwBuyReflushShipTimes:uint = bytes.readUnsignedInt();
			s_.dwBuyReflushShipTimes = dwBuyReflushShipTimes;
			var wReflushShip:uint = bytes.readUnsignedShort();
			s_.wReflushShip = wReflushShip;
			var dwReflushShipTimer:uint = bytes.readUnsignedInt();
			s_.dwReflushShipTimer = dwReflushShipTimer;
			var qwInviteDefense:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInviteDefense = qwInviteDefense;
			var dwInviteDefenseAgreeTime:uint = bytes.readUnsignedInt();
			s_.dwInviteDefenseAgreeTime = dwInviteDefenseAgreeTime;
			var dwInviteDefensePoint:uint = bytes.readUnsignedInt();
			s_.dwInviteDefensePoint = dwInviteDefensePoint;
			var byInviteDefenseLevel:uint = bytes.readUnsignedByte();
			s_.byInviteDefenseLevel = byInviteDefenseLevel;
			var byInviteDefenseColor:uint = bytes.readUnsignedByte();
			s_.byInviteDefenseColor = byInviteDefenseColor;
			var qwAgreeDefenseShipOwer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwAgreeDefenseShipOwer = qwAgreeDefenseShipOwer;
			var dwAgreeDefenseShipOwerTime:uint = bytes.readUnsignedInt();
			s_.dwAgreeDefenseShipOwerTime = dwAgreeDefenseShipOwerTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerSelfShipData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerSelfShipData> = new Vector.<PlayerSelfShipData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerSelfShipData = PlayerSelfShipData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBuyOpenShipTimes);
			bytes.writeUnsignedInt(dwBuyRoBShipTimes);
			bytes.writeUnsignedInt(dwBuyReflushShipTimes);
			bytes.writeShort(wReflushShip);
			bytes.writeUnsignedInt(dwReflushShipTimer);
			BytesUtil.writeUInt64(bytes, qwInviteDefense);
			bytes.writeUnsignedInt(dwInviteDefenseAgreeTime);
			bytes.writeUnsignedInt(dwInviteDefensePoint);
			bytes.writeByte(byInviteDefenseLevel);
			bytes.writeByte(byInviteDefenseColor);
			BytesUtil.writeUInt64(bytes, qwAgreeDefenseShipOwer);
			bytes.writeUnsignedInt(dwAgreeDefenseShipOwerTime);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerSelfShipData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerSelfShipData in vec)
				s.toByteArray(bytes);
		}
	}
}
