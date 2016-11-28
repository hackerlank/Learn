/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STakePrizeLog.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家获取奖励记录
	 */
	public final class STakePrizeLog
	{
		public var eType:uint; //(枚举类型：ELingShanPrizeType)奖励类型
		public var wTakeBoxCount:uint; //(无符号16位整数)获得宝箱数量
		public var strFailName:String; //敌对玩家
		public var qwReportID:BigInteger; //(无符号64位整数)战报id
		public var fHPRate:Number; //(Float)最终血量
		public var dwSuiYuan:uint; //(无符号32位整数)增加的随缘值
		public var eCollideType:uint; //(枚举类型：ECollideType)碰撞类型

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, wTakeBoxCount:uint, strFailName:String, qwReportID:BigInteger, fHPRate:Number, 
			dwSuiYuan:uint, eCollideType:uint):STakePrizeLog
		{
			var s_:STakePrizeLog = new STakePrizeLog();
			s_.eType = eType;
			s_.wTakeBoxCount = wTakeBoxCount;
			s_.strFailName = strFailName;
			s_.qwReportID = qwReportID;
			s_.fHPRate = fHPRate;
			s_.dwSuiYuan = dwSuiYuan;
			s_.eCollideType = eCollideType;
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
				topXml = <STakePrizeLog _name_={name_} eType={eType} wTakeBoxCount={wTakeBoxCount} strFailName={strFailName} qwReportID={qwReportID} fHPRate={fHPRate}
				 dwSuiYuan={dwSuiYuan} eCollideType={eCollideType}/>;
			else
				topXml = <STakePrizeLog eType={eType} wTakeBoxCount={wTakeBoxCount} strFailName={strFailName} qwReportID={qwReportID} fHPRate={fHPRate}
				 dwSuiYuan={dwSuiYuan} eCollideType={eCollideType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.wTakeBoxCount = wTakeBoxCount;
			obj_.strFailName = strFailName;
			obj_.qwReportID = qwReportID;
			obj_.fHPRate = fHPRate;
			obj_.dwSuiYuan = dwSuiYuan;
			obj_.eCollideType = eCollideType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STakePrizeLog
		{
			var s_:STakePrizeLog = new STakePrizeLog();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var wTakeBoxCount:uint = bytes.readUnsignedShort();
			s_.wTakeBoxCount = wTakeBoxCount;
			var strFailName:String = BytesUtil.readString(bytes);
			s_.strFailName = strFailName;
			var qwReportID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwReportID = qwReportID;
			var fHPRate:Number = bytes.readFloat();
			s_.fHPRate = fHPRate;
			var dwSuiYuan:uint = bytes.readUnsignedInt();
			s_.dwSuiYuan = dwSuiYuan;
			var eCollideType:uint = bytes.readUnsignedByte();
			s_.eCollideType = eCollideType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STakePrizeLog>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STakePrizeLog> = new Vector.<STakePrizeLog>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STakePrizeLog = STakePrizeLog.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeShort(wTakeBoxCount);
			BytesUtil.writeString(bytes, strFailName);
			BytesUtil.writeUInt64(bytes, qwReportID);
			bytes.writeFloat(fHPRate);
			bytes.writeUnsignedInt(dwSuiYuan);
			bytes.writeByte(eCollideType);
		}

		public static function vectorToByteArray(vec:Vector.<STakePrizeLog>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STakePrizeLog in vec)
				s.toByteArray(bytes);
		}
	}
}
