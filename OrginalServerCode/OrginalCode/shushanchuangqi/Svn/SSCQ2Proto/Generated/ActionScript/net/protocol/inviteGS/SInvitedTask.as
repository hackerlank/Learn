/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SInvitedTask.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 邀请任务状态
	 */
	public final class SInvitedTask
	{
		public var dwInviteTaskID:uint; //(无符号32位整数)任务id
		public var wTaskType:uint; //(无符号16位整数)任务类型
		public var eInvitedTask:uint; //(枚举类型：EInvitedTask)任务状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwInviteTaskID:uint, wTaskType:uint, eInvitedTask:uint):SInvitedTask
		{
			var s_:SInvitedTask = new SInvitedTask();
			s_.dwInviteTaskID = dwInviteTaskID;
			s_.wTaskType = wTaskType;
			s_.eInvitedTask = eInvitedTask;
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
				topXml = <SInvitedTask _name_={name_} dwInviteTaskID={dwInviteTaskID} wTaskType={wTaskType} eInvitedTask={eInvitedTask}/>;
			else
				topXml = <SInvitedTask dwInviteTaskID={dwInviteTaskID} wTaskType={wTaskType} eInvitedTask={eInvitedTask}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwInviteTaskID = dwInviteTaskID;
			obj_.wTaskType = wTaskType;
			obj_.eInvitedTask = eInvitedTask;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SInvitedTask
		{
			var s_:SInvitedTask = new SInvitedTask();
			var dwInviteTaskID:uint = bytes.readUnsignedInt();
			s_.dwInviteTaskID = dwInviteTaskID;
			var wTaskType:uint = bytes.readUnsignedShort();
			s_.wTaskType = wTaskType;
			var eInvitedTask:uint = bytes.readUnsignedByte();
			s_.eInvitedTask = eInvitedTask;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SInvitedTask>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SInvitedTask> = new Vector.<SInvitedTask>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SInvitedTask = SInvitedTask.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwInviteTaskID);
			bytes.writeShort(wTaskType);
			bytes.writeByte(eInvitedTask);
		}

		public static function vectorToByteArray(vec:Vector.<SInvitedTask>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SInvitedTask in vec)
				s.toByteArray(bytes);
		}
	}
}
