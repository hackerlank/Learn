/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleArrayDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 破阵信息
	 */
	public final class SBattleArrayDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wBattleArrayID:uint; //(无符号16位整数)阵id
		public var dwBattleArrayLevelID:uint; //(无符号32位整数)进度(阵图id)
		public var byBattleArrayStatus:uint; //(无符号8位整数)状态

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wBattleArrayID:uint, dwBattleArrayLevelID:uint, byBattleArrayStatus:uint):SBattleArrayDBInfo
		{
			var s_:SBattleArrayDBInfo = new SBattleArrayDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wBattleArrayID = wBattleArrayID;
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			s_.byBattleArrayStatus = byBattleArrayStatus;
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
				topXml = <SBattleArrayDBInfo _name_={name_} qwRoleID={qwRoleID} wBattleArrayID={wBattleArrayID} dwBattleArrayLevelID={dwBattleArrayLevelID} byBattleArrayStatus={byBattleArrayStatus}/>;
			else
				topXml = <SBattleArrayDBInfo qwRoleID={qwRoleID} wBattleArrayID={wBattleArrayID} dwBattleArrayLevelID={dwBattleArrayLevelID} byBattleArrayStatus={byBattleArrayStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wBattleArrayID = wBattleArrayID;
			obj_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			obj_.byBattleArrayStatus = byBattleArrayStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleArrayDBInfo
		{
			var s_:SBattleArrayDBInfo = new SBattleArrayDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wBattleArrayID:uint = bytes.readUnsignedShort();
			s_.wBattleArrayID = wBattleArrayID;
			var dwBattleArrayLevelID:uint = bytes.readUnsignedInt();
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			var byBattleArrayStatus:uint = bytes.readUnsignedByte();
			s_.byBattleArrayStatus = byBattleArrayStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleArrayDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleArrayDBInfo> = new Vector.<SBattleArrayDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleArrayDBInfo = SBattleArrayDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wBattleArrayID);
			bytes.writeUnsignedInt(dwBattleArrayLevelID);
			bytes.writeByte(byBattleArrayStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleArrayDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleArrayDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
