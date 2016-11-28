/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    PlayerShip.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 金船信息
	 */
	public final class PlayerShip
	{
		public var qwInsID:BigInteger; //(无符号64位整数)金船唯一ID
		public var qwOwer:BigInteger; //(无符号64位整数)金船拥有者
		public var dwOwerPoint:uint; //(无符号32位整数)金船拥有者战斗力
		public var byOwerLevel:uint; //(无符号8位整数)拥有者等级
		public var byOwerColor:uint; //(无符号8位整数)拥有者颜色
		public var byChannel:uint; //(无符号8位整数)航道
		public var wShipId:uint; //(无符号16位整数)金船模板
		public var qwDefense:BigInteger; //(无符号64位整数)护送者ID
		public var dwDefensePoint:uint; //(无符号32位整数)护送者战斗力
		public var byDefenseLevel:uint; //(无符号8位整数)护送者等级
		public var byDefenseColor:uint; //(无符号8位整数)护送者颜色
		public var qwRoBId1:BigInteger; //(无符号64位整数)打劫者1
		public var byRoB1Color:uint; //(无符号8位整数)打劫者1颜色
		public var dwRoB1Point:uint; //(无符号32位整数)打劫者1战斗力
		public var byRoB1Level:uint; //(无符号8位整数)打劫者1等级
		public var qwRoBId2:BigInteger; //(无符号64位整数)打劫者2
		public var byRoB2Color:uint; //(无符号8位整数)打劫者2颜色
		public var dwRoB2Point:uint; //(无符号32位整数)打劫者2战斗力
		public var byRoB2Level:uint; //(无符号8位整数)打劫者2等级
		public var qwRoBId3:BigInteger; //(无符号64位整数)打劫者3
		public var byRoB3Color:uint; //(无符号8位整数)打劫者3颜色
		public var dwRoB3Point:uint; //(无符号32位整数)打劫者3战斗力
		public var byRoB3Level:uint; //(无符号8位整数)打劫者3等级
		public var dwBeginTimer:uint; //(无符号32位整数)开船时间
		public var dwEndTimer:uint; //(无符号32位整数)结束时间
		public var dwAwardRate:uint; //(无符号32位整数)奖励倍率

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInsID:BigInteger, qwOwer:BigInteger, dwOwerPoint:uint, byOwerLevel:uint, byOwerColor:uint, 
			byChannel:uint, wShipId:uint, qwDefense:BigInteger, dwDefensePoint:uint, byDefenseLevel:uint, 
			byDefenseColor:uint, qwRoBId1:BigInteger, byRoB1Color:uint, dwRoB1Point:uint, byRoB1Level:uint, 
			qwRoBId2:BigInteger, byRoB2Color:uint, dwRoB2Point:uint, byRoB2Level:uint, qwRoBId3:BigInteger, 
			byRoB3Color:uint, dwRoB3Point:uint, byRoB3Level:uint, dwBeginTimer:uint, dwEndTimer:uint, 
			dwAwardRate:uint):PlayerShip
		{
			var s_:PlayerShip = new PlayerShip();
			s_.qwInsID = qwInsID;
			s_.qwOwer = qwOwer;
			s_.dwOwerPoint = dwOwerPoint;
			s_.byOwerLevel = byOwerLevel;
			s_.byOwerColor = byOwerColor;
			s_.byChannel = byChannel;
			s_.wShipId = wShipId;
			s_.qwDefense = qwDefense;
			s_.dwDefensePoint = dwDefensePoint;
			s_.byDefenseLevel = byDefenseLevel;
			s_.byDefenseColor = byDefenseColor;
			s_.qwRoBId1 = qwRoBId1;
			s_.byRoB1Color = byRoB1Color;
			s_.dwRoB1Point = dwRoB1Point;
			s_.byRoB1Level = byRoB1Level;
			s_.qwRoBId2 = qwRoBId2;
			s_.byRoB2Color = byRoB2Color;
			s_.dwRoB2Point = dwRoB2Point;
			s_.byRoB2Level = byRoB2Level;
			s_.qwRoBId3 = qwRoBId3;
			s_.byRoB3Color = byRoB3Color;
			s_.dwRoB3Point = dwRoB3Point;
			s_.byRoB3Level = byRoB3Level;
			s_.dwBeginTimer = dwBeginTimer;
			s_.dwEndTimer = dwEndTimer;
			s_.dwAwardRate = dwAwardRate;
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
				topXml = <PlayerShip _name_={name_} qwInsID={qwInsID} qwOwer={qwOwer} dwOwerPoint={dwOwerPoint} byOwerLevel={byOwerLevel} byOwerColor={byOwerColor}
				 byChannel={byChannel} wShipId={wShipId} qwDefense={qwDefense} dwDefensePoint={dwDefensePoint} byDefenseLevel={byDefenseLevel}
				 byDefenseColor={byDefenseColor} qwRoBId1={qwRoBId1} byRoB1Color={byRoB1Color} dwRoB1Point={dwRoB1Point} byRoB1Level={byRoB1Level}
				 qwRoBId2={qwRoBId2} byRoB2Color={byRoB2Color} dwRoB2Point={dwRoB2Point} byRoB2Level={byRoB2Level} qwRoBId3={qwRoBId3}
				 byRoB3Color={byRoB3Color} dwRoB3Point={dwRoB3Point} byRoB3Level={byRoB3Level} dwBeginTimer={dwBeginTimer} dwEndTimer={dwEndTimer}
				 dwAwardRate={dwAwardRate}/>;
			else
				topXml = <PlayerShip qwInsID={qwInsID} qwOwer={qwOwer} dwOwerPoint={dwOwerPoint} byOwerLevel={byOwerLevel} byOwerColor={byOwerColor}
				 byChannel={byChannel} wShipId={wShipId} qwDefense={qwDefense} dwDefensePoint={dwDefensePoint} byDefenseLevel={byDefenseLevel}
				 byDefenseColor={byDefenseColor} qwRoBId1={qwRoBId1} byRoB1Color={byRoB1Color} dwRoB1Point={dwRoB1Point} byRoB1Level={byRoB1Level}
				 qwRoBId2={qwRoBId2} byRoB2Color={byRoB2Color} dwRoB2Point={dwRoB2Point} byRoB2Level={byRoB2Level} qwRoBId3={qwRoBId3}
				 byRoB3Color={byRoB3Color} dwRoB3Point={dwRoB3Point} byRoB3Level={byRoB3Level} dwBeginTimer={dwBeginTimer} dwEndTimer={dwEndTimer}
				 dwAwardRate={dwAwardRate}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInsID = qwInsID;
			obj_.qwOwer = qwOwer;
			obj_.dwOwerPoint = dwOwerPoint;
			obj_.byOwerLevel = byOwerLevel;
			obj_.byOwerColor = byOwerColor;
			obj_.byChannel = byChannel;
			obj_.wShipId = wShipId;
			obj_.qwDefense = qwDefense;
			obj_.dwDefensePoint = dwDefensePoint;
			obj_.byDefenseLevel = byDefenseLevel;
			obj_.byDefenseColor = byDefenseColor;
			obj_.qwRoBId1 = qwRoBId1;
			obj_.byRoB1Color = byRoB1Color;
			obj_.dwRoB1Point = dwRoB1Point;
			obj_.byRoB1Level = byRoB1Level;
			obj_.qwRoBId2 = qwRoBId2;
			obj_.byRoB2Color = byRoB2Color;
			obj_.dwRoB2Point = dwRoB2Point;
			obj_.byRoB2Level = byRoB2Level;
			obj_.qwRoBId3 = qwRoBId3;
			obj_.byRoB3Color = byRoB3Color;
			obj_.dwRoB3Point = dwRoB3Point;
			obj_.byRoB3Level = byRoB3Level;
			obj_.dwBeginTimer = dwBeginTimer;
			obj_.dwEndTimer = dwEndTimer;
			obj_.dwAwardRate = dwAwardRate;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):PlayerShip
		{
			var s_:PlayerShip = new PlayerShip();
			var qwInsID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInsID = qwInsID;
			var qwOwer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwer = qwOwer;
			var dwOwerPoint:uint = bytes.readUnsignedInt();
			s_.dwOwerPoint = dwOwerPoint;
			var byOwerLevel:uint = bytes.readUnsignedByte();
			s_.byOwerLevel = byOwerLevel;
			var byOwerColor:uint = bytes.readUnsignedByte();
			s_.byOwerColor = byOwerColor;
			var byChannel:uint = bytes.readUnsignedByte();
			s_.byChannel = byChannel;
			var wShipId:uint = bytes.readUnsignedShort();
			s_.wShipId = wShipId;
			var qwDefense:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwDefense = qwDefense;
			var dwDefensePoint:uint = bytes.readUnsignedInt();
			s_.dwDefensePoint = dwDefensePoint;
			var byDefenseLevel:uint = bytes.readUnsignedByte();
			s_.byDefenseLevel = byDefenseLevel;
			var byDefenseColor:uint = bytes.readUnsignedByte();
			s_.byDefenseColor = byDefenseColor;
			var qwRoBId1:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoBId1 = qwRoBId1;
			var byRoB1Color:uint = bytes.readUnsignedByte();
			s_.byRoB1Color = byRoB1Color;
			var dwRoB1Point:uint = bytes.readUnsignedInt();
			s_.dwRoB1Point = dwRoB1Point;
			var byRoB1Level:uint = bytes.readUnsignedByte();
			s_.byRoB1Level = byRoB1Level;
			var qwRoBId2:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoBId2 = qwRoBId2;
			var byRoB2Color:uint = bytes.readUnsignedByte();
			s_.byRoB2Color = byRoB2Color;
			var dwRoB2Point:uint = bytes.readUnsignedInt();
			s_.dwRoB2Point = dwRoB2Point;
			var byRoB2Level:uint = bytes.readUnsignedByte();
			s_.byRoB2Level = byRoB2Level;
			var qwRoBId3:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoBId3 = qwRoBId3;
			var byRoB3Color:uint = bytes.readUnsignedByte();
			s_.byRoB3Color = byRoB3Color;
			var dwRoB3Point:uint = bytes.readUnsignedInt();
			s_.dwRoB3Point = dwRoB3Point;
			var byRoB3Level:uint = bytes.readUnsignedByte();
			s_.byRoB3Level = byRoB3Level;
			var dwBeginTimer:uint = bytes.readUnsignedInt();
			s_.dwBeginTimer = dwBeginTimer;
			var dwEndTimer:uint = bytes.readUnsignedInt();
			s_.dwEndTimer = dwEndTimer;
			var dwAwardRate:uint = bytes.readUnsignedInt();
			s_.dwAwardRate = dwAwardRate;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<PlayerShip>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<PlayerShip> = new Vector.<PlayerShip>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:PlayerShip = PlayerShip.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInsID);
			BytesUtil.writeUInt64(bytes, qwOwer);
			bytes.writeUnsignedInt(dwOwerPoint);
			bytes.writeByte(byOwerLevel);
			bytes.writeByte(byOwerColor);
			bytes.writeByte(byChannel);
			bytes.writeShort(wShipId);
			BytesUtil.writeUInt64(bytes, qwDefense);
			bytes.writeUnsignedInt(dwDefensePoint);
			bytes.writeByte(byDefenseLevel);
			bytes.writeByte(byDefenseColor);
			BytesUtil.writeUInt64(bytes, qwRoBId1);
			bytes.writeByte(byRoB1Color);
			bytes.writeUnsignedInt(dwRoB1Point);
			bytes.writeByte(byRoB1Level);
			BytesUtil.writeUInt64(bytes, qwRoBId2);
			bytes.writeByte(byRoB2Color);
			bytes.writeUnsignedInt(dwRoB2Point);
			bytes.writeByte(byRoB2Level);
			BytesUtil.writeUInt64(bytes, qwRoBId3);
			bytes.writeByte(byRoB3Color);
			bytes.writeUnsignedInt(dwRoB3Point);
			bytes.writeByte(byRoB3Level);
			bytes.writeUnsignedInt(dwBeginTimer);
			bytes.writeUnsignedInt(dwEndTimer);
			bytes.writeUnsignedInt(dwAwardRate);
		}

		public static function vectorToByteArray(vec:Vector.<PlayerShip>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:PlayerShip in vec)
				s.toByteArray(bytes);
		}
	}
}
