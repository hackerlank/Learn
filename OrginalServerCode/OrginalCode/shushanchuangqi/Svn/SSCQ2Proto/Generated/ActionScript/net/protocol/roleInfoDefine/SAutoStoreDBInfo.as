/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAutoStoreDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 动态存储信息
	 */
	public final class SAutoStoreDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wType:uint; //(无符号16位整数)大类
		public var dwClassID:uint; //(无符号32位整数)小类
		public var dwValue:uint; //(无符号32位整数)数值

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wType:uint, dwClassID:uint, dwValue:uint):SAutoStoreDBInfo
		{
			var s_:SAutoStoreDBInfo = new SAutoStoreDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wType = wType;
			s_.dwClassID = dwClassID;
			s_.dwValue = dwValue;
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
				topXml = <SAutoStoreDBInfo _name_={name_} qwRoleID={qwRoleID} wType={wType} dwClassID={dwClassID} dwValue={dwValue}/>;
			else
				topXml = <SAutoStoreDBInfo qwRoleID={qwRoleID} wType={wType} dwClassID={dwClassID} dwValue={dwValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wType = wType;
			obj_.dwClassID = dwClassID;
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAutoStoreDBInfo
		{
			var s_:SAutoStoreDBInfo = new SAutoStoreDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wType:uint = bytes.readUnsignedShort();
			s_.wType = wType;
			var dwClassID:uint = bytes.readUnsignedInt();
			s_.dwClassID = dwClassID;
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAutoStoreDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAutoStoreDBInfo> = new Vector.<SAutoStoreDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAutoStoreDBInfo = SAutoStoreDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wType);
			bytes.writeUnsignedInt(dwClassID);
			bytes.writeUnsignedInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SAutoStoreDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAutoStoreDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
