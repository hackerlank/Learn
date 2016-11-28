/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleStatus.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家在活动中的状态信息
	 */
	public final class SRoleStatus
	{
		public var wCond:uint; //(无符号32位整数)活动ID
		public var dwMaxRole:uint; //(无符号32位整数)活动达到条件人数
		public var dwCurRole:uint; //(无符号32位整数)活动目前人数
		public var byStatus:uint; //(无符号8位整数)活动状态

		/**
		 * 辅助创建函数
		 */
		public static function create(wCond:uint, dwMaxRole:uint, dwCurRole:uint, byStatus:uint):SRoleStatus
		{
			var s_:SRoleStatus = new SRoleStatus();
			s_.wCond = wCond;
			s_.dwMaxRole = dwMaxRole;
			s_.dwCurRole = dwCurRole;
			s_.byStatus = byStatus;
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
				topXml = <SRoleStatus _name_={name_} wCond={wCond} dwMaxRole={dwMaxRole} dwCurRole={dwCurRole} byStatus={byStatus}/>;
			else
				topXml = <SRoleStatus wCond={wCond} dwMaxRole={dwMaxRole} dwCurRole={dwCurRole} byStatus={byStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wCond = wCond;
			obj_.dwMaxRole = dwMaxRole;
			obj_.dwCurRole = dwCurRole;
			obj_.byStatus = byStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleStatus
		{
			var s_:SRoleStatus = new SRoleStatus();
			var wCond:uint = bytes.readUnsignedInt();
			s_.wCond = wCond;
			var dwMaxRole:uint = bytes.readUnsignedInt();
			s_.dwMaxRole = dwMaxRole;
			var dwCurRole:uint = bytes.readUnsignedInt();
			s_.dwCurRole = dwCurRole;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleStatus>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleStatus> = new Vector.<SRoleStatus>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleStatus = SRoleStatus.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(wCond);
			bytes.writeUnsignedInt(dwMaxRole);
			bytes.writeUnsignedInt(dwCurRole);
			bytes.writeByte(byStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleStatus>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleStatus in vec)
				s.toByteArray(bytes);
		}
	}
}
