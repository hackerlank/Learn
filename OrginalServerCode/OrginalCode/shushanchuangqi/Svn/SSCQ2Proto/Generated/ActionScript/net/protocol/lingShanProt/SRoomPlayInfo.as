/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoomPlayInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 比赛的玩家信息
	 */
	public final class SRoomPlayInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家id
		public var dwModelID:uint; //(无符号32位整数)模型id
		public var dwKillCnt:uint; //(无符号16位整数)击杀人数
		public var bGodBox:Boolean; //是否带有大宝箱
		public var wPos:uint; //(无符号16位整数)当前所在地图位置

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwModelID:uint, dwKillCnt:uint, bGodBox:Boolean, wPos:uint):SRoomPlayInfo
		{
			var s_:SRoomPlayInfo = new SRoomPlayInfo();
			s_.qwRoleID = qwRoleID;
			s_.dwModelID = dwModelID;
			s_.dwKillCnt = dwKillCnt;
			s_.bGodBox = bGodBox;
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
				topXml = <SRoomPlayInfo _name_={name_} qwRoleID={qwRoleID} dwModelID={dwModelID} dwKillCnt={dwKillCnt} bGodBox={bGodBox} wPos={wPos}/>;
			else
				topXml = <SRoomPlayInfo qwRoleID={qwRoleID} dwModelID={dwModelID} dwKillCnt={dwKillCnt} bGodBox={bGodBox} wPos={wPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwModelID = dwModelID;
			obj_.dwKillCnt = dwKillCnt;
			obj_.bGodBox = bGodBox;
			obj_.wPos = wPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoomPlayInfo
		{
			var s_:SRoomPlayInfo = new SRoomPlayInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwModelID:uint = bytes.readUnsignedInt();
			s_.dwModelID = dwModelID;
			var dwKillCnt:uint = bytes.readUnsignedShort();
			s_.dwKillCnt = dwKillCnt;
			var bGodBox:Boolean = bytes.readBoolean();
			s_.bGodBox = bGodBox;
			var wPos:uint = bytes.readUnsignedShort();
			s_.wPos = wPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoomPlayInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoomPlayInfo> = new Vector.<SRoomPlayInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoomPlayInfo = SRoomPlayInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwModelID);
			bytes.writeShort(dwKillCnt);
			bytes.writeBoolean(bGodBox);
			bytes.writeShort(wPos);
		}

		public static function vectorToByteArray(vec:Vector.<SRoomPlayInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoomPlayInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
