/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleSlotsInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * EDataType:eTypeSlotsInfo:玩家各种槽数据
	 */
	public final class SRoleSlotsInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家RoleID
		public var qwOwnerID:BigInteger; //(无符号64位整数)槽拥有者ID
		public var eStoreType:uint; //(枚举类型：itemProt.EStoreType)槽类型
		public var wMaxSlot:uint; //(无符号16位整数)槽允许的最大数量
		public var wMaxAvaliableSlot:uint; //(无符号16位整数)槽当前的最大数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwOwnerID:BigInteger, eStoreType:uint, wMaxSlot:uint, wMaxAvaliableSlot:uint):SRoleSlotsInfo
		{
			var s_:SRoleSlotsInfo = new SRoleSlotsInfo();
			s_.qwRoleID = qwRoleID;
			s_.qwOwnerID = qwOwnerID;
			s_.eStoreType = eStoreType;
			s_.wMaxSlot = wMaxSlot;
			s_.wMaxAvaliableSlot = wMaxAvaliableSlot;
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
				topXml = <SRoleSlotsInfo _name_={name_} qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} eStoreType={eStoreType} wMaxSlot={wMaxSlot} wMaxAvaliableSlot={wMaxAvaliableSlot}/>;
			else
				topXml = <SRoleSlotsInfo qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} eStoreType={eStoreType} wMaxSlot={wMaxSlot} wMaxAvaliableSlot={wMaxAvaliableSlot}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwOwnerID = qwOwnerID;
			obj_.eStoreType = eStoreType;
			obj_.wMaxSlot = wMaxSlot;
			obj_.wMaxAvaliableSlot = wMaxAvaliableSlot;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleSlotsInfo
		{
			var s_:SRoleSlotsInfo = new SRoleSlotsInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var eStoreType:uint = bytes.readUnsignedByte();
			s_.eStoreType = eStoreType;
			var wMaxSlot:uint = bytes.readUnsignedShort();
			s_.wMaxSlot = wMaxSlot;
			var wMaxAvaliableSlot:uint = bytes.readUnsignedShort();
			s_.wMaxAvaliableSlot = wMaxAvaliableSlot;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleSlotsInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleSlotsInfo> = new Vector.<SRoleSlotsInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleSlotsInfo = SRoleSlotsInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeByte(eStoreType);
			bytes.writeShort(wMaxSlot);
			bytes.writeShort(wMaxAvaliableSlot);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleSlotsInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleSlotsInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
