/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleTaskInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 任务存储结构
	 */
	public final class RoleTaskInfo
	{
		public var dwTaskId:uint; //(无符号32位整数)任务Id
		public var eTaskState:uint; //(枚举类型：taskProt.ETaskState)任务状态
		public var dwAcceptTimes:uint; //(无符号32位整数)接受任务次数
		public var dwLastAcceptTimer:uint; //(无符号32位整数)最近任务接受时间
		public var dwFinishTimes:uint; //(无符号32位整数)完成任务次数
		public var dwLastFinishTimer:uint; //(无符号32位整数)最近完成任务时间
		public var byProcessType1:uint; //(无符号8位整数)进度1的类型
		public var dwProcessParam11:uint; //(无符号32位整数)进度1的第1个参数
		public var dwProcessParam12:uint; //(无符号32位整数)进度1的第2个参数
		public var byProcessType2:uint; //(无符号8位整数)进度2的类型
		public var dwProcessParam21:uint; //(无符号32位整数)进度2的第1个参数
		public var dwProcessParam22:uint; //(无符号32位整数)进度2的第2个参数
		public var byProcessType3:uint; //(无符号8位整数)进度3的类型
		public var dwProcessParam31:uint; //(无符号32位整数)进度3的第1个参数
		public var dwProcessParam32:uint; //(无符号32位整数)进度3的第2个参数
		public var dwRepeatAcceptTimes:uint; //(无符号32位整数)当前有效接任务次数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwTaskId:uint, eTaskState:uint, dwAcceptTimes:uint, dwLastAcceptTimer:uint, dwFinishTimes:uint, 
			dwLastFinishTimer:uint, byProcessType1:uint, dwProcessParam11:uint, dwProcessParam12:uint, byProcessType2:uint, 
			dwProcessParam21:uint, dwProcessParam22:uint, byProcessType3:uint, dwProcessParam31:uint, dwProcessParam32:uint, 
			dwRepeatAcceptTimes:uint):RoleTaskInfo
		{
			var s_:RoleTaskInfo = new RoleTaskInfo();
			s_.dwTaskId = dwTaskId;
			s_.eTaskState = eTaskState;
			s_.dwAcceptTimes = dwAcceptTimes;
			s_.dwLastAcceptTimer = dwLastAcceptTimer;
			s_.dwFinishTimes = dwFinishTimes;
			s_.dwLastFinishTimer = dwLastFinishTimer;
			s_.byProcessType1 = byProcessType1;
			s_.dwProcessParam11 = dwProcessParam11;
			s_.dwProcessParam12 = dwProcessParam12;
			s_.byProcessType2 = byProcessType2;
			s_.dwProcessParam21 = dwProcessParam21;
			s_.dwProcessParam22 = dwProcessParam22;
			s_.byProcessType3 = byProcessType3;
			s_.dwProcessParam31 = dwProcessParam31;
			s_.dwProcessParam32 = dwProcessParam32;
			s_.dwRepeatAcceptTimes = dwRepeatAcceptTimes;
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
				topXml = <RoleTaskInfo _name_={name_} dwTaskId={dwTaskId} eTaskState={eTaskState} dwAcceptTimes={dwAcceptTimes} dwLastAcceptTimer={dwLastAcceptTimer} dwFinishTimes={dwFinishTimes}
				 dwLastFinishTimer={dwLastFinishTimer} byProcessType1={byProcessType1} dwProcessParam11={dwProcessParam11} dwProcessParam12={dwProcessParam12} byProcessType2={byProcessType2}
				 dwProcessParam21={dwProcessParam21} dwProcessParam22={dwProcessParam22} byProcessType3={byProcessType3} dwProcessParam31={dwProcessParam31} dwProcessParam32={dwProcessParam32}
				 dwRepeatAcceptTimes={dwRepeatAcceptTimes}/>;
			else
				topXml = <RoleTaskInfo dwTaskId={dwTaskId} eTaskState={eTaskState} dwAcceptTimes={dwAcceptTimes} dwLastAcceptTimer={dwLastAcceptTimer} dwFinishTimes={dwFinishTimes}
				 dwLastFinishTimer={dwLastFinishTimer} byProcessType1={byProcessType1} dwProcessParam11={dwProcessParam11} dwProcessParam12={dwProcessParam12} byProcessType2={byProcessType2}
				 dwProcessParam21={dwProcessParam21} dwProcessParam22={dwProcessParam22} byProcessType3={byProcessType3} dwProcessParam31={dwProcessParam31} dwProcessParam32={dwProcessParam32}
				 dwRepeatAcceptTimes={dwRepeatAcceptTimes}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwTaskId = dwTaskId;
			obj_.eTaskState = eTaskState;
			obj_.dwAcceptTimes = dwAcceptTimes;
			obj_.dwLastAcceptTimer = dwLastAcceptTimer;
			obj_.dwFinishTimes = dwFinishTimes;
			obj_.dwLastFinishTimer = dwLastFinishTimer;
			obj_.byProcessType1 = byProcessType1;
			obj_.dwProcessParam11 = dwProcessParam11;
			obj_.dwProcessParam12 = dwProcessParam12;
			obj_.byProcessType2 = byProcessType2;
			obj_.dwProcessParam21 = dwProcessParam21;
			obj_.dwProcessParam22 = dwProcessParam22;
			obj_.byProcessType3 = byProcessType3;
			obj_.dwProcessParam31 = dwProcessParam31;
			obj_.dwProcessParam32 = dwProcessParam32;
			obj_.dwRepeatAcceptTimes = dwRepeatAcceptTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleTaskInfo
		{
			var s_:RoleTaskInfo = new RoleTaskInfo();
			var dwTaskId:uint = bytes.readUnsignedInt();
			s_.dwTaskId = dwTaskId;
			var eTaskState:uint = bytes.readUnsignedByte();
			s_.eTaskState = eTaskState;
			var dwAcceptTimes:uint = bytes.readUnsignedInt();
			s_.dwAcceptTimes = dwAcceptTimes;
			var dwLastAcceptTimer:uint = bytes.readUnsignedInt();
			s_.dwLastAcceptTimer = dwLastAcceptTimer;
			var dwFinishTimes:uint = bytes.readUnsignedInt();
			s_.dwFinishTimes = dwFinishTimes;
			var dwLastFinishTimer:uint = bytes.readUnsignedInt();
			s_.dwLastFinishTimer = dwLastFinishTimer;
			var byProcessType1:uint = bytes.readUnsignedByte();
			s_.byProcessType1 = byProcessType1;
			var dwProcessParam11:uint = bytes.readUnsignedInt();
			s_.dwProcessParam11 = dwProcessParam11;
			var dwProcessParam12:uint = bytes.readUnsignedInt();
			s_.dwProcessParam12 = dwProcessParam12;
			var byProcessType2:uint = bytes.readUnsignedByte();
			s_.byProcessType2 = byProcessType2;
			var dwProcessParam21:uint = bytes.readUnsignedInt();
			s_.dwProcessParam21 = dwProcessParam21;
			var dwProcessParam22:uint = bytes.readUnsignedInt();
			s_.dwProcessParam22 = dwProcessParam22;
			var byProcessType3:uint = bytes.readUnsignedByte();
			s_.byProcessType3 = byProcessType3;
			var dwProcessParam31:uint = bytes.readUnsignedInt();
			s_.dwProcessParam31 = dwProcessParam31;
			var dwProcessParam32:uint = bytes.readUnsignedInt();
			s_.dwProcessParam32 = dwProcessParam32;
			var dwRepeatAcceptTimes:uint = bytes.readUnsignedInt();
			s_.dwRepeatAcceptTimes = dwRepeatAcceptTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleTaskInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleTaskInfo> = new Vector.<RoleTaskInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleTaskInfo = RoleTaskInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwTaskId);
			bytes.writeByte(eTaskState);
			bytes.writeUnsignedInt(dwAcceptTimes);
			bytes.writeUnsignedInt(dwLastAcceptTimer);
			bytes.writeUnsignedInt(dwFinishTimes);
			bytes.writeUnsignedInt(dwLastFinishTimer);
			bytes.writeByte(byProcessType1);
			bytes.writeUnsignedInt(dwProcessParam11);
			bytes.writeUnsignedInt(dwProcessParam12);
			bytes.writeByte(byProcessType2);
			bytes.writeUnsignedInt(dwProcessParam21);
			bytes.writeUnsignedInt(dwProcessParam22);
			bytes.writeByte(byProcessType3);
			bytes.writeUnsignedInt(dwProcessParam31);
			bytes.writeUnsignedInt(dwProcessParam32);
			bytes.writeUnsignedInt(dwRepeatAcceptTimes);
		}

		public static function vectorToByteArray(vec:Vector.<RoleTaskInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleTaskInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
