/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerFighterLog.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家战斗信息（目前不需要战斗日志)
	 */
	public final class SPlayerFighterLog
	{
		public var qwEnemy:BigInteger; //(无符号64位整数)战斗玩家
		public var qwReportID:BigInteger; //(无符号64位整数)战斗日志
		public var bWin:Boolean; //是否胜利

		/**
		 * 辅助创建函数
		 */
		public static function create(qwEnemy:BigInteger, qwReportID:BigInteger, bWin:Boolean):SPlayerFighterLog
		{
			var s_:SPlayerFighterLog = new SPlayerFighterLog();
			s_.qwEnemy = qwEnemy;
			s_.qwReportID = qwReportID;
			s_.bWin = bWin;
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
				topXml = <SPlayerFighterLog _name_={name_} qwEnemy={qwEnemy} qwReportID={qwReportID} bWin={bWin}/>;
			else
				topXml = <SPlayerFighterLog qwEnemy={qwEnemy} qwReportID={qwReportID} bWin={bWin}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwEnemy = qwEnemy;
			obj_.qwReportID = qwReportID;
			obj_.bWin = bWin;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerFighterLog
		{
			var s_:SPlayerFighterLog = new SPlayerFighterLog();
			var qwEnemy:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwEnemy = qwEnemy;
			var qwReportID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwReportID = qwReportID;
			var bWin:Boolean = bytes.readBoolean();
			s_.bWin = bWin;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerFighterLog>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerFighterLog> = new Vector.<SPlayerFighterLog>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerFighterLog = SPlayerFighterLog.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwEnemy);
			BytesUtil.writeUInt64(bytes, qwReportID);
			bytes.writeBoolean(bWin);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerFighterLog>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerFighterLog in vec)
				s.toByteArray(bytes);
		}
	}
}
