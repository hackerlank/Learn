/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SVarsDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家变量数据
	 */
	public final class SVarsDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家RoleId
		public var byServerType:uint; //(无符号8位整数)服务器类型
		public var wVar:uint; //(无符号16位整数)变量ID
		public var qwValue:BigInteger; //(无符号64位整数)变量值
		public var dwExpired:uint; //(无符号32位整数)过期时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byServerType:uint, wVar:uint, qwValue:BigInteger, dwExpired:uint):SVarsDBInfo
		{
			var s_:SVarsDBInfo = new SVarsDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.byServerType = byServerType;
			s_.wVar = wVar;
			s_.qwValue = qwValue;
			s_.dwExpired = dwExpired;
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
				topXml = <SVarsDBInfo _name_={name_} qwRoleID={qwRoleID} byServerType={byServerType} wVar={wVar} qwValue={qwValue} dwExpired={dwExpired}/>;
			else
				topXml = <SVarsDBInfo qwRoleID={qwRoleID} byServerType={byServerType} wVar={wVar} qwValue={qwValue} dwExpired={dwExpired}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byServerType = byServerType;
			obj_.wVar = wVar;
			obj_.qwValue = qwValue;
			obj_.dwExpired = dwExpired;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SVarsDBInfo
		{
			var s_:SVarsDBInfo = new SVarsDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byServerType:uint = bytes.readUnsignedByte();
			s_.byServerType = byServerType;
			var wVar:uint = bytes.readUnsignedShort();
			s_.wVar = wVar;
			var qwValue:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwValue = qwValue;
			var dwExpired:uint = bytes.readUnsignedInt();
			s_.dwExpired = dwExpired;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SVarsDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SVarsDBInfo> = new Vector.<SVarsDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SVarsDBInfo = SVarsDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byServerType);
			bytes.writeShort(wVar);
			BytesUtil.writeUInt64(bytes, qwValue);
			bytes.writeUnsignedInt(dwExpired);
		}

		public static function vectorToByteArray(vec:Vector.<SVarsDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SVarsDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
