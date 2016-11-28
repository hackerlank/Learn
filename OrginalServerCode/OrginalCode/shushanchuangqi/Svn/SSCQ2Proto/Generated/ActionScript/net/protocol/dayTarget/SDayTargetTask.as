/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDayTargetTask.as
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 任务信息列表
	 */
	public final class SDayTargetTask
	{
		public var wTaskID:uint; //(无符号16位整数)任务ID
		public var eTaskStatus:uint; //(枚举类型：EDayTargeTasktStatus)任务状态
		public var dwParam:uint; //(无符号32位整数)进度

		/**
		 * 辅助创建函数
		 */
		public static function create(wTaskID:uint, eTaskStatus:uint, dwParam:uint):SDayTargetTask
		{
			var s_:SDayTargetTask = new SDayTargetTask();
			s_.wTaskID = wTaskID;
			s_.eTaskStatus = eTaskStatus;
			s_.dwParam = dwParam;
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
				topXml = <SDayTargetTask _name_={name_} wTaskID={wTaskID} eTaskStatus={eTaskStatus} dwParam={dwParam}/>;
			else
				topXml = <SDayTargetTask wTaskID={wTaskID} eTaskStatus={eTaskStatus} dwParam={dwParam}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wTaskID = wTaskID;
			obj_.eTaskStatus = eTaskStatus;
			obj_.dwParam = dwParam;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDayTargetTask
		{
			var s_:SDayTargetTask = new SDayTargetTask();
			var wTaskID:uint = bytes.readUnsignedShort();
			s_.wTaskID = wTaskID;
			var eTaskStatus:uint = bytes.readUnsignedByte();
			s_.eTaskStatus = eTaskStatus;
			var dwParam:uint = bytes.readUnsignedInt();
			s_.dwParam = dwParam;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDayTargetTask>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDayTargetTask> = new Vector.<SDayTargetTask>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDayTargetTask = SDayTargetTask.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wTaskID);
			bytes.writeByte(eTaskStatus);
			bytes.writeUnsignedInt(dwParam);
		}

		public static function vectorToByteArray(vec:Vector.<SDayTargetTask>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDayTargetTask in vec)
				s.toByteArray(bytes);
		}
	}
}
