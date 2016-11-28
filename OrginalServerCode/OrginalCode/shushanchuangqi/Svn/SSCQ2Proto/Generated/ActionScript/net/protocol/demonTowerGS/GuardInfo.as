/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    GuardInfo.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 镇守的玩家信息列表
	 */
	public final class GuardInfo
	{
		public var qwUserID:BigInteger; //(无符号64位整数)uid
		public var qwRoleID:BigInteger; //(无符号64位整数)角色id
		public var dwGuardPos:uint; //(无符号32位整数)封印位置
		public var dwLastFightCD:uint; //(无符号32位整数)战斗cd 1s
		public var oDemonFloorPlayer:SDemonFloorPlayer; //玩家信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, qwRoleID:BigInteger, dwGuardPos:uint, dwLastFightCD:uint, oDemonFloorPlayer:SDemonFloorPlayer):GuardInfo
		{
			var s_:GuardInfo = new GuardInfo();
			s_.qwUserID = qwUserID;
			s_.qwRoleID = qwRoleID;
			s_.dwGuardPos = dwGuardPos;
			s_.dwLastFightCD = dwLastFightCD;
			s_.oDemonFloorPlayer = oDemonFloorPlayer;
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
				topXml = <GuardInfo _name_={name_} qwUserID={qwUserID} qwRoleID={qwRoleID} dwGuardPos={dwGuardPos} dwLastFightCD={dwLastFightCD}/>;
			else
				topXml = <GuardInfo qwUserID={qwUserID} qwRoleID={qwRoleID} dwGuardPos={dwGuardPos} dwLastFightCD={dwLastFightCD}/>;
			if(oDemonFloorPlayer != null)
				topXml.appendChild(oDemonFloorPlayer.toXML("oDemonFloorPlayer"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.qwRoleID = qwRoleID;
			obj_.dwGuardPos = dwGuardPos;
			obj_.dwLastFightCD = dwLastFightCD;
			obj_.oDemonFloorPlayer = oDemonFloorPlayer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):GuardInfo
		{
			var s_:GuardInfo = new GuardInfo();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwGuardPos:uint = bytes.readUnsignedInt();
			s_.dwGuardPos = dwGuardPos;
			var dwLastFightCD:uint = bytes.readUnsignedInt();
			s_.dwLastFightCD = dwLastFightCD;
			var oDemonFloorPlayer:SDemonFloorPlayer = SDemonFloorPlayer.fromByteArray(bytes);
			s_.oDemonFloorPlayer = oDemonFloorPlayer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<GuardInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<GuardInfo> = new Vector.<GuardInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:GuardInfo = GuardInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwGuardPos);
			bytes.writeUnsignedInt(dwLastFightCD);
			oDemonFloorPlayer.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<GuardInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:GuardInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
