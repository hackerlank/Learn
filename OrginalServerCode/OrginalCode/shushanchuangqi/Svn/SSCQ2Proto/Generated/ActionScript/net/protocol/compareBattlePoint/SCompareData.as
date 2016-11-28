/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCompareData.as
//  Purpose:      变强(战力对比)相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.compareBattlePoint
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 对比的数据结构
	 */
	public final class SCompareData
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家名字
		public var byLevel:uint; //(无符号8位整数)玩家等级
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)玩家主将职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)玩家主将性别
		public var dwBattlePoint:uint; //(无符号32位整数)玩家总战斗力
		public var dwHeroBP:uint; //(无符号32位整数)散仙的战斗力(渡劫和心法除外)
		public var dwBeautyBP:uint; //(无符号32位整数)美女系统战斗力
		public var dwTrumpBP:uint; //(无符号32位整数)法宝战斗力
		public var dwHorseBP:uint; //(无符号32位整数)坐骑战斗力
		public var dwDujieBP:uint; //(无符号32位整数)渡劫战斗力
		public var dwXinfaBP:uint; //(无符号32位整数)心法战斗力
		public var dwClanBP:uint; //(无符号32位整数)帮派战斗力

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, byLevel:uint, eCareer:uint, eSex:uint, 
			dwBattlePoint:uint, dwHeroBP:uint, dwBeautyBP:uint, dwTrumpBP:uint, dwHorseBP:uint, 
			dwDujieBP:uint, dwXinfaBP:uint, dwClanBP:uint):SCompareData
		{
			var s_:SCompareData = new SCompareData();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.byLevel = byLevel;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.dwBattlePoint = dwBattlePoint;
			s_.dwHeroBP = dwHeroBP;
			s_.dwBeautyBP = dwBeautyBP;
			s_.dwTrumpBP = dwTrumpBP;
			s_.dwHorseBP = dwHorseBP;
			s_.dwDujieBP = dwDujieBP;
			s_.dwXinfaBP = dwXinfaBP;
			s_.dwClanBP = dwClanBP;
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
				topXml = <SCompareData _name_={name_} qwRoleID={qwRoleID} strName={strName} byLevel={byLevel} eCareer={eCareer} eSex={eSex}
				 dwBattlePoint={dwBattlePoint} dwHeroBP={dwHeroBP} dwBeautyBP={dwBeautyBP} dwTrumpBP={dwTrumpBP} dwHorseBP={dwHorseBP}
				 dwDujieBP={dwDujieBP} dwXinfaBP={dwXinfaBP} dwClanBP={dwClanBP}/>;
			else
				topXml = <SCompareData qwRoleID={qwRoleID} strName={strName} byLevel={byLevel} eCareer={eCareer} eSex={eSex}
				 dwBattlePoint={dwBattlePoint} dwHeroBP={dwHeroBP} dwBeautyBP={dwBeautyBP} dwTrumpBP={dwTrumpBP} dwHorseBP={dwHorseBP}
				 dwDujieBP={dwDujieBP} dwXinfaBP={dwXinfaBP} dwClanBP={dwClanBP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.byLevel = byLevel;
			obj_.eCareer = eCareer;
			obj_.eSex = eSex;
			obj_.dwBattlePoint = dwBattlePoint;
			obj_.dwHeroBP = dwHeroBP;
			obj_.dwBeautyBP = dwBeautyBP;
			obj_.dwTrumpBP = dwTrumpBP;
			obj_.dwHorseBP = dwHorseBP;
			obj_.dwDujieBP = dwDujieBP;
			obj_.dwXinfaBP = dwXinfaBP;
			obj_.dwClanBP = dwClanBP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCompareData
		{
			var s_:SCompareData = new SCompareData();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			var dwHeroBP:uint = bytes.readUnsignedInt();
			s_.dwHeroBP = dwHeroBP;
			var dwBeautyBP:uint = bytes.readUnsignedInt();
			s_.dwBeautyBP = dwBeautyBP;
			var dwTrumpBP:uint = bytes.readUnsignedInt();
			s_.dwTrumpBP = dwTrumpBP;
			var dwHorseBP:uint = bytes.readUnsignedInt();
			s_.dwHorseBP = dwHorseBP;
			var dwDujieBP:uint = bytes.readUnsignedInt();
			s_.dwDujieBP = dwDujieBP;
			var dwXinfaBP:uint = bytes.readUnsignedInt();
			s_.dwXinfaBP = dwXinfaBP;
			var dwClanBP:uint = bytes.readUnsignedInt();
			s_.dwClanBP = dwClanBP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCompareData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCompareData> = new Vector.<SCompareData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCompareData = SCompareData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byLevel);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			bytes.writeUnsignedInt(dwBattlePoint);
			bytes.writeUnsignedInt(dwHeroBP);
			bytes.writeUnsignedInt(dwBeautyBP);
			bytes.writeUnsignedInt(dwTrumpBP);
			bytes.writeUnsignedInt(dwHorseBP);
			bytes.writeUnsignedInt(dwDujieBP);
			bytes.writeUnsignedInt(dwXinfaBP);
			bytes.writeUnsignedInt(dwClanBP);
		}

		public static function vectorToByteArray(vec:Vector.<SCompareData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCompareData in vec)
				s.toByteArray(bytes);
		}
	}
}
