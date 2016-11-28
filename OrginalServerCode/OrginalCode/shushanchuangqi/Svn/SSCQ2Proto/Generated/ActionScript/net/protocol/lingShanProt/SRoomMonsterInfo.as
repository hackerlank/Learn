/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoomMonsterInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 地图的怪物信息
	 */
	public final class SRoomMonsterInfo
	{
		public var dwMonsterID:uint; //(无符号32位整数)怪物组id
		public var dwKillCnt:uint; //(无符号16位整数)击杀人数
		public var wPos:uint; //(无符号16位整数)当前所在地图位置

		/**
		 * 辅助创建函数
		 */
		public static function create(dwMonsterID:uint, dwKillCnt:uint, wPos:uint):SRoomMonsterInfo
		{
			var s_:SRoomMonsterInfo = new SRoomMonsterInfo();
			s_.dwMonsterID = dwMonsterID;
			s_.dwKillCnt = dwKillCnt;
			s_.wPos = wPos;
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
				topXml = <SRoomMonsterInfo _name_={name_} dwMonsterID={dwMonsterID} dwKillCnt={dwKillCnt} wPos={wPos}/>;
			else
				topXml = <SRoomMonsterInfo dwMonsterID={dwMonsterID} dwKillCnt={dwKillCnt} wPos={wPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwMonsterID = dwMonsterID;
			obj_.dwKillCnt = dwKillCnt;
			obj_.wPos = wPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoomMonsterInfo
		{
			var s_:SRoomMonsterInfo = new SRoomMonsterInfo();
			var dwMonsterID:uint = bytes.readUnsignedInt();
			s_.dwMonsterID = dwMonsterID;
			var dwKillCnt:uint = bytes.readUnsignedShort();
			s_.dwKillCnt = dwKillCnt;
			var wPos:uint = bytes.readUnsignedShort();
			s_.wPos = wPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoomMonsterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoomMonsterInfo> = new Vector.<SRoomMonsterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoomMonsterInfo = SRoomMonsterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwMonsterID);
			bytes.writeShort(dwKillCnt);
			bytes.writeShort(wPos);
		}

		public static function vectorToByteArray(vec:Vector.<SRoomMonsterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoomMonsterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
