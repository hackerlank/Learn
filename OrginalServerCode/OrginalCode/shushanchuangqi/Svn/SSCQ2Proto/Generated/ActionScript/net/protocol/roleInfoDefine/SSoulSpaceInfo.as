/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSoulSpaceInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家魄空间信息
	 */
	public final class SSoulSpaceInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var dwSoulSpaceID:BigInteger; //(无符号64位整数)魄空间ID
		public var dwSoulSpaceLevel:BigInteger; //(无符号64位整数)魄空间等级

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwSoulSpaceID:BigInteger, dwSoulSpaceLevel:BigInteger):SSoulSpaceInfo
		{
			var s_:SSoulSpaceInfo = new SSoulSpaceInfo();
			s_.qwRoleID = qwRoleID;
			s_.dwSoulSpaceID = dwSoulSpaceID;
			s_.dwSoulSpaceLevel = dwSoulSpaceLevel;
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
				topXml = <SSoulSpaceInfo _name_={name_} qwRoleID={qwRoleID} dwSoulSpaceID={dwSoulSpaceID} dwSoulSpaceLevel={dwSoulSpaceLevel}/>;
			else
				topXml = <SSoulSpaceInfo qwRoleID={qwRoleID} dwSoulSpaceID={dwSoulSpaceID} dwSoulSpaceLevel={dwSoulSpaceLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwSoulSpaceID = dwSoulSpaceID;
			obj_.dwSoulSpaceLevel = dwSoulSpaceLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSoulSpaceInfo
		{
			var s_:SSoulSpaceInfo = new SSoulSpaceInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwSoulSpaceID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.dwSoulSpaceID = dwSoulSpaceID;
			var dwSoulSpaceLevel:BigInteger = BytesUtil.readUInt64(bytes);
			s_.dwSoulSpaceLevel = dwSoulSpaceLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSoulSpaceInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSoulSpaceInfo> = new Vector.<SSoulSpaceInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSoulSpaceInfo = SSoulSpaceInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, dwSoulSpaceID);
			BytesUtil.writeUInt64(bytes, dwSoulSpaceLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SSoulSpaceInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSoulSpaceInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
