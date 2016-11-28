/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFightFormationDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 新阵型信息
	 */
	public final class SFightFormationDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wBattleType:uint; //(无符号16位整数)战斗类型
		public var wFormationID:uint; //(无符号16位整数)当前阵形ID
		public var strBattlePosInfo:String; //阵型信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wBattleType:uint, wFormationID:uint, strBattlePosInfo:String):SFightFormationDBInfo
		{
			var s_:SFightFormationDBInfo = new SFightFormationDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wBattleType = wBattleType;
			s_.wFormationID = wFormationID;
			s_.strBattlePosInfo = strBattlePosInfo;
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
				topXml = <SFightFormationDBInfo _name_={name_} qwRoleID={qwRoleID} wBattleType={wBattleType} wFormationID={wFormationID} strBattlePosInfo={strBattlePosInfo}/>;
			else
				topXml = <SFightFormationDBInfo qwRoleID={qwRoleID} wBattleType={wBattleType} wFormationID={wFormationID} strBattlePosInfo={strBattlePosInfo}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wBattleType = wBattleType;
			obj_.wFormationID = wFormationID;
			obj_.strBattlePosInfo = strBattlePosInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFightFormationDBInfo
		{
			var s_:SFightFormationDBInfo = new SFightFormationDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wBattleType:uint = bytes.readUnsignedShort();
			s_.wBattleType = wBattleType;
			var wFormationID:uint = bytes.readUnsignedShort();
			s_.wFormationID = wFormationID;
			var strBattlePosInfo:String = BytesUtil.readString(bytes);
			s_.strBattlePosInfo = strBattlePosInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFightFormationDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFightFormationDBInfo> = new Vector.<SFightFormationDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFightFormationDBInfo = SFightFormationDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wBattleType);
			bytes.writeShort(wFormationID);
			BytesUtil.writeString(bytes, strBattlePosInfo);
		}

		public static function vectorToByteArray(vec:Vector.<SFightFormationDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFightFormationDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
