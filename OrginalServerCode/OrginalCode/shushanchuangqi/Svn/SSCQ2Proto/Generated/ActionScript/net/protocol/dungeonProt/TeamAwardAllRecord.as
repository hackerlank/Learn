/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamAwardAllRecord.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 组队副本总领奖记录
	 */
	public final class TeamAwardAllRecord
	{
		public var byAwardTimesToday:uint; //(无符号8位整数)今日领奖次数
		public var vecDgn:Vector.<TeamAwardRecord>; //每个副本领奖次数

		/**
		 * 辅助创建函数
		 */
		public static function create(byAwardTimesToday:uint, vecDgn:Vector.<TeamAwardRecord>):TeamAwardAllRecord
		{
			var s_:TeamAwardAllRecord = new TeamAwardAllRecord();
			s_.byAwardTimesToday = byAwardTimesToday;
			s_.vecDgn = vecDgn;
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
				topXml = <TeamAwardAllRecord _name_={name_} byAwardTimesToday={byAwardTimesToday}/>;
			else
				topXml = <TeamAwardAllRecord byAwardTimesToday={byAwardTimesToday}/>;
			if(vecDgn != null)
			{
				var vecDgnXml:XML = <Vec_TeamAwardRecord _name_="vecDgn"/>;
				for each(var s1:TeamAwardRecord in vecDgn)
					vecDgnXml.appendChild(s1.toXML());
				topXml.appendChild(vecDgnXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byAwardTimesToday = byAwardTimesToday;
			obj_.vecDgn = vecDgn;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamAwardAllRecord
		{
			var s_:TeamAwardAllRecord = new TeamAwardAllRecord();
			var byAwardTimesToday:uint = bytes.readUnsignedByte();
			s_.byAwardTimesToday = byAwardTimesToday;
			var vecDgn:Vector.<TeamAwardRecord> = TeamAwardRecord.vectorFromByteArray(bytes);
			s_.vecDgn = vecDgn;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamAwardAllRecord>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamAwardAllRecord> = new Vector.<TeamAwardAllRecord>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamAwardAllRecord = TeamAwardAllRecord.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byAwardTimesToday);
			TeamAwardRecord.vectorToByteArray(vecDgn, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<TeamAwardAllRecord>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamAwardAllRecord in vec)
				s.toByteArray(bytes);
		}
	}
}
