/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamAwardRecord.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 组队副本领奖记录
	 */
	public final class TeamAwardRecord
	{
		public var wDgnType:uint; //(无符号16位整数)副本模板
		public var byAwardTimes:uint; //(无符号8位整数)今日领奖次数

		/**
		 * 辅助创建函数
		 */
		public static function create(wDgnType:uint, byAwardTimes:uint):TeamAwardRecord
		{
			var s_:TeamAwardRecord = new TeamAwardRecord();
			s_.wDgnType = wDgnType;
			s_.byAwardTimes = byAwardTimes;
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
				topXml = <TeamAwardRecord _name_={name_} wDgnType={wDgnType} byAwardTimes={byAwardTimes}/>;
			else
				topXml = <TeamAwardRecord wDgnType={wDgnType} byAwardTimes={byAwardTimes}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wDgnType = wDgnType;
			obj_.byAwardTimes = byAwardTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamAwardRecord
		{
			var s_:TeamAwardRecord = new TeamAwardRecord();
			var wDgnType:uint = bytes.readUnsignedShort();
			s_.wDgnType = wDgnType;
			var byAwardTimes:uint = bytes.readUnsignedByte();
			s_.byAwardTimes = byAwardTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamAwardRecord>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamAwardRecord> = new Vector.<TeamAwardRecord>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamAwardRecord = TeamAwardRecord.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wDgnType);
			bytes.writeByte(byAwardTimes);
		}

		public static function vectorToByteArray(vec:Vector.<TeamAwardRecord>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamAwardRecord in vec)
				s.toByteArray(bytes);
		}
	}
}
