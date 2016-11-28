/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleData.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗详细数据
	 */
	public final class SBattleData
	{
		public var byIndex:uint; //(无符号8位整数)战斗场编号(1~3)
		public var qwRoleIDA:BigInteger; //(无符号64位整数)A方玩家ID
		public var qwRoleIDB:BigInteger; //(无符号64位整数)B方玩家ID
		public var eWinnerSide:uint; //(枚举类型：EGBSide)获胜方
		public var strBattleReport:ByteArray; //战报

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, qwRoleIDA:BigInteger, qwRoleIDB:BigInteger, eWinnerSide:uint, strBattleReport:ByteArray):SBattleData
		{
			var s_:SBattleData = new SBattleData();
			s_.byIndex = byIndex;
			s_.qwRoleIDA = qwRoleIDA;
			s_.qwRoleIDB = qwRoleIDB;
			s_.eWinnerSide = eWinnerSide;
			s_.strBattleReport = strBattleReport;
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
				topXml = <SBattleData _name_={name_} byIndex={byIndex} qwRoleIDA={qwRoleIDA} qwRoleIDB={qwRoleIDB} eWinnerSide={eWinnerSide} strBattleReport={BytesUtil.bytes2String(strBattleReport)}/>;
			else
				topXml = <SBattleData byIndex={byIndex} qwRoleIDA={qwRoleIDA} qwRoleIDB={qwRoleIDB} eWinnerSide={eWinnerSide} strBattleReport={BytesUtil.bytes2String(strBattleReport)}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.qwRoleIDA = qwRoleIDA;
			obj_.qwRoleIDB = qwRoleIDB;
			obj_.eWinnerSide = eWinnerSide;
			obj_.strBattleReport = strBattleReport;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleData
		{
			var s_:SBattleData = new SBattleData();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var qwRoleIDA:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleIDA = qwRoleIDA;
			var qwRoleIDB:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleIDB = qwRoleIDB;
			var eWinnerSide:uint = bytes.readUnsignedByte();
			s_.eWinnerSide = eWinnerSide;
			var strBattleReport:ByteArray = BytesUtil.readBytes(bytes);
			s_.strBattleReport = strBattleReport;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleData> = new Vector.<SBattleData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleData = SBattleData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			BytesUtil.writeUInt64(bytes, qwRoleIDA);
			BytesUtil.writeUInt64(bytes, qwRoleIDB);
			bytes.writeByte(eWinnerSide);
			BytesUtil.writeBytes(bytes, strBattleReport);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleData in vec)
				s.toByteArray(bytes);
		}
	}
}
