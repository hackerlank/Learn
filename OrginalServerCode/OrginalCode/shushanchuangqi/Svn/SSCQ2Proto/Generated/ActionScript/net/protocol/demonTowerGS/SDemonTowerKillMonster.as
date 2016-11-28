/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDemonTowerKillMonster.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 通关信息
	 */
	public final class SDemonTowerKillMonster
	{
		public var qwUserID:BigInteger; //(无符号64位整数)账号id
		public var strName:String; //名字
		public var byColor:uint; //(无符号8位整数)角色颜色
		public var bySex:uint; //(无符号8位整数)性别
		public var byCareer:uint; //(无符号8位整数)职业
		public var byLevel:uint; //(无符号8位整数)等级
		public var dwRounds:uint; //(无符号32位整数)通关回合数
		public var dwBattlePoint:uint; //(无符号32位整数)战斗力
		public var qwReportID:BigInteger; //(无符号64位整数)战报

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, strName:String, byColor:uint, bySex:uint, byCareer:uint, 
			byLevel:uint, dwRounds:uint, dwBattlePoint:uint, qwReportID:BigInteger):SDemonTowerKillMonster
		{
			var s_:SDemonTowerKillMonster = new SDemonTowerKillMonster();
			s_.qwUserID = qwUserID;
			s_.strName = strName;
			s_.byColor = byColor;
			s_.bySex = bySex;
			s_.byCareer = byCareer;
			s_.byLevel = byLevel;
			s_.dwRounds = dwRounds;
			s_.dwBattlePoint = dwBattlePoint;
			s_.qwReportID = qwReportID;
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
				topXml = <SDemonTowerKillMonster _name_={name_} qwUserID={qwUserID} strName={strName} byColor={byColor} bySex={bySex} byCareer={byCareer}
				 byLevel={byLevel} dwRounds={dwRounds} dwBattlePoint={dwBattlePoint} qwReportID={qwReportID}/>;
			else
				topXml = <SDemonTowerKillMonster qwUserID={qwUserID} strName={strName} byColor={byColor} bySex={bySex} byCareer={byCareer}
				 byLevel={byLevel} dwRounds={dwRounds} dwBattlePoint={dwBattlePoint} qwReportID={qwReportID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.strName = strName;
			obj_.byColor = byColor;
			obj_.bySex = bySex;
			obj_.byCareer = byCareer;
			obj_.byLevel = byLevel;
			obj_.dwRounds = dwRounds;
			obj_.dwBattlePoint = dwBattlePoint;
			obj_.qwReportID = qwReportID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDemonTowerKillMonster
		{
			var s_:SDemonTowerKillMonster = new SDemonTowerKillMonster();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			var bySex:uint = bytes.readUnsignedByte();
			s_.bySex = bySex;
			var byCareer:uint = bytes.readUnsignedByte();
			s_.byCareer = byCareer;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwRounds:uint = bytes.readUnsignedInt();
			s_.dwRounds = dwRounds;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			var qwReportID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwReportID = qwReportID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDemonTowerKillMonster>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDemonTowerKillMonster> = new Vector.<SDemonTowerKillMonster>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDemonTowerKillMonster = SDemonTowerKillMonster.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byColor);
			bytes.writeByte(bySex);
			bytes.writeByte(byCareer);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwRounds);
			bytes.writeUnsignedInt(dwBattlePoint);
			BytesUtil.writeUInt64(bytes, qwReportID);
		}

		public static function vectorToByteArray(vec:Vector.<SDemonTowerKillMonster>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDemonTowerKillMonster in vec)
				s.toByteArray(bytes);
		}
	}
}
