/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    ShipReport.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 金船战报
	 */
	public final class ShipReport
	{
		public var qwInsID:BigInteger; //(无符号64位整数)金船唯一ID
		public var eSource:uint; //(枚举类型：EShipBattleSource)战斗原因
		public var qwOwer:BigInteger; //(无符号64位整数)金船拥有者
		public var byOwerColor:uint; //(无符号8位整数)拥有者颜色
		public var wShipId:uint; //(无符号16位整数)金船模板
		public var qwDefense:BigInteger; //(无符号64位整数)护送者ID
		public var byDefenseColor:uint; //(无符号8位整数)护送者颜色
		public var qwRoBId:BigInteger; //(无符号64位整数)打劫者
		public var byRoBColor:uint; //(无符号8位整数)打劫者颜色
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var dwFinishTimer:uint; //(无符号32位整数)该船到达时间
		public var dwTimer:uint; //(无符号32位整数)发生时间
		public var byRobTimes:uint; //(无符号8位整数)被抢劫次数
		public var dwAwardRate:uint; //(无符号32位整数)奖励倍率

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInsID:BigInteger, eSource:uint, qwOwer:BigInteger, byOwerColor:uint, wShipId:uint, 
			qwDefense:BigInteger, byDefenseColor:uint, qwRoBId:BigInteger, byRoBColor:uint, qwBattleID:BigInteger, 
			dwFinishTimer:uint, dwTimer:uint, byRobTimes:uint, dwAwardRate:uint):ShipReport
		{
			var s_:ShipReport = new ShipReport();
			s_.qwInsID = qwInsID;
			s_.eSource = eSource;
			s_.qwOwer = qwOwer;
			s_.byOwerColor = byOwerColor;
			s_.wShipId = wShipId;
			s_.qwDefense = qwDefense;
			s_.byDefenseColor = byDefenseColor;
			s_.qwRoBId = qwRoBId;
			s_.byRoBColor = byRoBColor;
			s_.qwBattleID = qwBattleID;
			s_.dwFinishTimer = dwFinishTimer;
			s_.dwTimer = dwTimer;
			s_.byRobTimes = byRobTimes;
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
				topXml = <ShipReport _name_={name_} qwInsID={qwInsID} eSource={eSource} qwOwer={qwOwer} byOwerColor={byOwerColor} wShipId={wShipId}
				 qwDefense={qwDefense} byDefenseColor={byDefenseColor} qwRoBId={qwRoBId} byRoBColor={byRoBColor} qwBattleID={qwBattleID}
				 dwFinishTimer={dwFinishTimer} dwTimer={dwTimer} byRobTimes={byRobTimes} dwAwardRate={dwAwardRate}/>;
			else
				topXml = <ShipReport qwInsID={qwInsID} eSource={eSource} qwOwer={qwOwer} byOwerColor={byOwerColor} wShipId={wShipId}
				 qwDefense={qwDefense} byDefenseColor={byDefenseColor} qwRoBId={qwRoBId} byRoBColor={byRoBColor} qwBattleID={qwBattleID}
				 dwFinishTimer={dwFinishTimer} dwTimer={dwTimer} byRobTimes={byRobTimes} dwAwardRate={dwAwardRate}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInsID = qwInsID;
			obj_.eSource = eSource;
			obj_.qwOwer = qwOwer;
			obj_.byOwerColor = byOwerColor;
			obj_.wShipId = wShipId;
			obj_.qwDefense = qwDefense;
			obj_.byDefenseColor = byDefenseColor;
			obj_.qwRoBId = qwRoBId;
			obj_.byRoBColor = byRoBColor;
			obj_.qwBattleID = qwBattleID;
			obj_.dwFinishTimer = dwFinishTimer;
			obj_.dwTimer = dwTimer;
			obj_.byRobTimes = byRobTimes;
			obj_.dwAwardRate = dwAwardRate;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):ShipReport
		{
			var s_:ShipReport = new ShipReport();
			var qwInsID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInsID = qwInsID;
			var eSource:uint = bytes.readUnsignedByte();
			s_.eSource = eSource;
			var qwOwer:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwer = qwOwer;
			var byOwerColor:uint = bytes.readUnsignedByte();
			s_.byOwerColor = byOwerColor;
			var wShipId:uint = bytes.readUnsignedShort();
			s_.wShipId = wShipId;
			var qwDefense:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwDefense = qwDefense;
			var byDefenseColor:uint = bytes.readUnsignedByte();
			s_.byDefenseColor = byDefenseColor;
			var qwRoBId:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoBId = qwRoBId;
			var byRoBColor:uint = bytes.readUnsignedByte();
			s_.byRoBColor = byRoBColor;
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var dwFinishTimer:uint = bytes.readUnsignedInt();
			s_.dwFinishTimer = dwFinishTimer;
			var dwTimer:uint = bytes.readUnsignedInt();
			s_.dwTimer = dwTimer;
			var byRobTimes:uint = bytes.readUnsignedByte();
			s_.byRobTimes = byRobTimes;
			var dwAwardRate:uint = bytes.readUnsignedInt();
			s_.dwAwardRate = dwAwardRate;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<ShipReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<ShipReport> = new Vector.<ShipReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:ShipReport = ShipReport.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInsID);
			bytes.writeByte(eSource);
			BytesUtil.writeUInt64(bytes, qwOwer);
			bytes.writeByte(byOwerColor);
			bytes.writeShort(wShipId);
			BytesUtil.writeUInt64(bytes, qwDefense);
			bytes.writeByte(byDefenseColor);
			BytesUtil.writeUInt64(bytes, qwRoBId);
			bytes.writeByte(byRoBColor);
			BytesUtil.writeUInt64(bytes, qwBattleID);
			bytes.writeUnsignedInt(dwFinishTimer);
			bytes.writeUnsignedInt(dwTimer);
			bytes.writeByte(byRobTimes);
			bytes.writeUnsignedInt(dwAwardRate);
		}

		public static function vectorToByteArray(vec:Vector.<ShipReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:ShipReport in vec)
				s.toByteArray(bytes);
		}
	}
}
