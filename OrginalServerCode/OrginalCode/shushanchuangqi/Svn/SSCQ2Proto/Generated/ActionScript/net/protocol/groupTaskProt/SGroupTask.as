/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGroupTask.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 挑战的任务状态
	 */
	public final class SGroupTask
	{
		public var dwTaskId:uint; //(无符号32位整数)任务的ID
		public var eGroupTaskState:uint; //(枚举类型：EGroupTaskState)当前刷的任务信息

		/**
		 * 辅助创建函数
		 */
		public static function create(dwTaskId:uint, eGroupTaskState:uint):SGroupTask
		{
			var s_:SGroupTask = new SGroupTask();
			s_.dwTaskId = dwTaskId;
			s_.eGroupTaskState = eGroupTaskState;
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
				topXml = <SGroupTask _name_={name_} dwTaskId={dwTaskId} eGroupTaskState={eGroupTaskState}/>;
			else
				topXml = <SGroupTask dwTaskId={dwTaskId} eGroupTaskState={eGroupTaskState}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwTaskId = dwTaskId;
			obj_.eGroupTaskState = eGroupTaskState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGroupTask
		{
			var s_:SGroupTask = new SGroupTask();
			var dwTaskId:uint = bytes.readUnsignedInt();
			s_.dwTaskId = dwTaskId;
			var eGroupTaskState:uint = bytes.readUnsignedByte();
			s_.eGroupTaskState = eGroupTaskState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGroupTask>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGroupTask> = new Vector.<SGroupTask>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGroupTask = SGroupTask.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwTaskId);
			bytes.writeByte(eGroupTaskState);
		}

		public static function vectorToByteArray(vec:Vector.<SGroupTask>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGroupTask in vec)
				s.toByteArray(bytes);
		}
	}
}
