/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    NewSBattleReport.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战报
	 */
	public class NewSBattleReport
	{
		public var qwHash:BigInteger; //(无符号64位整数)新版本战报校验字段(应该始终为0xFFFFFFFF)

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_NewSBattleReport.eType_NewSBattleReport;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <NewSBattleReport _name_={name_} qwHash={qwHash}/>;
			else
				topXml = <NewSBattleReport qwHash={qwHash}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwHash = qwHash;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):NewSBattleReport
		{
			var s_:NewSBattleReport = new NewSBattleReport();
			var qwHash:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwHash = qwHash;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):NewSBattleReport
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:NewSBattleReport;
			switch(eType)
			{
				case EType_NewSBattleReport.eType_NewSBattleReport:
					s = NewSBattleReport.fromByteArray(bytes);
					break;
				case EType_NewSBattleReport.eType_NewSBattleReportV1:
					s = NewSBattleReportV1.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_NewSBattleReport:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<NewSBattleReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<NewSBattleReport> = new Vector.<NewSBattleReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:NewSBattleReport = NewSBattleReport.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<NewSBattleReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<NewSBattleReport> = new Vector.<NewSBattleReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:NewSBattleReport = NewSBattleReport.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwHash);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<NewSBattleReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:NewSBattleReport in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<NewSBattleReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:NewSBattleReport in vec)
				s.superToByteArray(bytes);
		}
	}
}
