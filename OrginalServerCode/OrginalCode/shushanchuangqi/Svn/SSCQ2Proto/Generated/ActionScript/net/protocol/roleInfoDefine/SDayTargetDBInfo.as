/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDayTargetDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 7日目标活动信息
	 */
	public final class SDayTargetDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wTaskID:uint; //(无符号16位整数)任务ID
		public var byStatus:uint; //(无符号8位整数)任务状态
		public var dwProcess:uint; //(无符号32位整数)任务进度

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wTaskID:uint, byStatus:uint, dwProcess:uint):SDayTargetDBInfo
		{
			var s_:SDayTargetDBInfo = new SDayTargetDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wTaskID = wTaskID;
			s_.byStatus = byStatus;
			s_.dwProcess = dwProcess;
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
				topXml = <SDayTargetDBInfo _name_={name_} qwRoleID={qwRoleID} wTaskID={wTaskID} byStatus={byStatus} dwProcess={dwProcess}/>;
			else
				topXml = <SDayTargetDBInfo qwRoleID={qwRoleID} wTaskID={wTaskID} byStatus={byStatus} dwProcess={dwProcess}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wTaskID = wTaskID;
			obj_.byStatus = byStatus;
			obj_.dwProcess = dwProcess;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDayTargetDBInfo
		{
			var s_:SDayTargetDBInfo = new SDayTargetDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wTaskID:uint = bytes.readUnsignedShort();
			s_.wTaskID = wTaskID;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			var dwProcess:uint = bytes.readUnsignedInt();
			s_.dwProcess = dwProcess;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDayTargetDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDayTargetDBInfo> = new Vector.<SDayTargetDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDayTargetDBInfo = SDayTargetDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wTaskID);
			bytes.writeByte(byStatus);
			bytes.writeUnsignedInt(dwProcess);
		}

		public static function vectorToByteArray(vec:Vector.<SDayTargetDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDayTargetDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
