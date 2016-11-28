/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLadderRobot.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 机器人排名信息
	 */
	public final class SLadderRobot
	{
		public var wMonsterID:uint; //(无符号16位整数)机器人ID
		public var wRank:uint; //(无符号16位整数)机器人排名

		/**
		 * 辅助创建函数
		 */
		public static function create(wMonsterID:uint, wRank:uint):SLadderRobot
		{
			var s_:SLadderRobot = new SLadderRobot();
			s_.wMonsterID = wMonsterID;
			s_.wRank = wRank;
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
				topXml = <SLadderRobot _name_={name_} wMonsterID={wMonsterID} wRank={wRank}/>;
			else
				topXml = <SLadderRobot wMonsterID={wMonsterID} wRank={wRank}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wMonsterID = wMonsterID;
			obj_.wRank = wRank;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLadderRobot
		{
			var s_:SLadderRobot = new SLadderRobot();
			var wMonsterID:uint = bytes.readUnsignedShort();
			s_.wMonsterID = wMonsterID;
			var wRank:uint = bytes.readUnsignedShort();
			s_.wRank = wRank;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLadderRobot>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLadderRobot> = new Vector.<SLadderRobot>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLadderRobot = SLadderRobot.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wMonsterID);
			bytes.writeShort(wRank);
		}

		public static function vectorToByteArray(vec:Vector.<SLadderRobot>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLadderRobot in vec)
				s.toByteArray(bytes);
		}
	}
}
