/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STripodData.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import com.hurlant.math.BigInteger;
	import net.protocol.arenaGS.SArenaFighter;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家九疑鼎信息
	 */
	public final class STripodData
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家的ID
		public var stPlayer:SArenaFighter; //九疑鼎所属玩家的基础信息
		public var tripodHelpData:STripodHelp; //玩家九疑鼎的协助数据
		public var vecTripods:Vector.<STripodInfo>; //玩家的所有九疑鼎数据
		public var vecTripodLog:Vector.<STripodLog>; //九疑鼎日志

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, stPlayer:SArenaFighter, tripodHelpData:STripodHelp, vecTripods:Vector.<STripodInfo>, vecTripodLog:Vector.<STripodLog>):STripodData
		{
			var s_:STripodData = new STripodData();
			s_.qwRoleID = qwRoleID;
			s_.stPlayer = stPlayer;
			s_.tripodHelpData = tripodHelpData;
			s_.vecTripods = vecTripods;
			s_.vecTripodLog = vecTripodLog;
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
				topXml = <STripodData _name_={name_} qwRoleID={qwRoleID}/>;
			else
				topXml = <STripodData qwRoleID={qwRoleID}/>;
			if(stPlayer != null)
				topXml.appendChild(stPlayer.toXML("stPlayer"));
			if(tripodHelpData != null)
				topXml.appendChild(tripodHelpData.toXML("tripodHelpData"));
			if(vecTripods != null)
			{
				var vecTripodsXml:XML = <Vec_STripodInfo _name_="vecTripods"/>;
				for each(var s3:STripodInfo in vecTripods)
					vecTripodsXml.appendChild(s3.toXML());
				topXml.appendChild(vecTripodsXml);
			}
			if(vecTripodLog != null)
			{
				var vecTripodLogXml:XML = <Vec_STripodLog _name_="vecTripodLog"/>;
				for each(var s4:STripodLog in vecTripodLog)
					vecTripodLogXml.appendChild(s4.toXML());
				topXml.appendChild(vecTripodLogXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.stPlayer = stPlayer;
			obj_.tripodHelpData = tripodHelpData;
			obj_.vecTripods = vecTripods;
			obj_.vecTripodLog = vecTripodLog;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STripodData
		{
			var s_:STripodData = new STripodData();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var stPlayer:SArenaFighter = SArenaFighter.fromByteArray(bytes);
			s_.stPlayer = stPlayer;
			var tripodHelpData:STripodHelp = STripodHelp.fromByteArray(bytes);
			s_.tripodHelpData = tripodHelpData;
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes);
			s_.vecTripods = vecTripods;
			var vecTripodLog:Vector.<STripodLog> = STripodLog.vectorFromByteArray(bytes);
			s_.vecTripodLog = vecTripodLog;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STripodData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STripodData> = new Vector.<STripodData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STripodData = STripodData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			stPlayer.toByteArray(bytes);
			tripodHelpData.toByteArray(bytes);
			STripodInfo.vectorToByteArray(vecTripods, bytes);
			STripodLog.vectorToByteArray(vecTripodLog, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STripodData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STripodData in vec)
				s.toByteArray(bytes);
		}
	}
}
