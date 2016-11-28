/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STask.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 任务的属性
	 */
	public final class STask
	{
		public var wTaskID:uint; //(无符号16位整数)任务的ID
		public var eTaskState:uint; //(枚举类型：ETaskState)任务的状态
		public var dwAcceptTime:uint; //(无符号32位整数)接取时间
		public var byRepeat:uint; //(无符号8位整数)同时接取数
		public var vecTaskInfo:Vector.<STaskInfo>; //任务信息列表

		/**
		 * 辅助创建函数
		 */
		public static function create(wTaskID:uint, eTaskState:uint, dwAcceptTime:uint, byRepeat:uint, vecTaskInfo:Vector.<STaskInfo>):STask
		{
			var s_:STask = new STask();
			s_.wTaskID = wTaskID;
			s_.eTaskState = eTaskState;
			s_.dwAcceptTime = dwAcceptTime;
			s_.byRepeat = byRepeat;
			s_.vecTaskInfo = vecTaskInfo;
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
				topXml = <STask _name_={name_} wTaskID={wTaskID} eTaskState={eTaskState} dwAcceptTime={dwAcceptTime} byRepeat={byRepeat}/>;
			else
				topXml = <STask wTaskID={wTaskID} eTaskState={eTaskState} dwAcceptTime={dwAcceptTime} byRepeat={byRepeat}/>;
			if(vecTaskInfo != null)
			{
				var vecTaskInfoXml:XML = <Vec_STaskInfo _name_="vecTaskInfo"/>;
				for each(var s1:STaskInfo in vecTaskInfo)
					vecTaskInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTaskInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wTaskID = wTaskID;
			obj_.eTaskState = eTaskState;
			obj_.dwAcceptTime = dwAcceptTime;
			obj_.byRepeat = byRepeat;
			obj_.vecTaskInfo = vecTaskInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STask
		{
			var s_:STask = new STask();
			var wTaskID:uint = bytes.readUnsignedShort();
			s_.wTaskID = wTaskID;
			var eTaskState:uint = bytes.readUnsignedByte();
			s_.eTaskState = eTaskState;
			var dwAcceptTime:uint = bytes.readUnsignedInt();
			s_.dwAcceptTime = dwAcceptTime;
			var byRepeat:uint = bytes.readUnsignedByte();
			s_.byRepeat = byRepeat;
			var vecTaskInfo:Vector.<STaskInfo> = STaskInfo.superVectorFromByteArray(bytes);
			s_.vecTaskInfo = vecTaskInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STask>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STask> = new Vector.<STask>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STask = STask.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wTaskID);
			bytes.writeByte(eTaskState);
			bytes.writeUnsignedInt(dwAcceptTime);
			bytes.writeByte(byRepeat);
			STaskInfo.superVectorToByteArray(vecTaskInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STask>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STask in vec)
				s.toByteArray(bytes);
		}
	}
}
