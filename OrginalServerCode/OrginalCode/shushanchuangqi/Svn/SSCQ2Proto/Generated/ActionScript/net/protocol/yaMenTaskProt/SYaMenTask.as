/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SYaMenTask.as
//  Purpose:      衙门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 挑战的任务状态
	 */
	public final class SYaMenTask
	{
		public var dwTaskId:uint; //(无符号32位整数)任务的ID
		public var eYaMenTaskState:uint; //(枚举类型：EYaMenTaskState)当前刷的任务信息

		/**
		 * 辅助创建函数
		 */
		public static function create(dwTaskId:uint, eYaMenTaskState:uint):SYaMenTask
		{
			var s_:SYaMenTask = new SYaMenTask();
			s_.dwTaskId = dwTaskId;
			s_.eYaMenTaskState = eYaMenTaskState;
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
				topXml = <SYaMenTask _name_={name_} dwTaskId={dwTaskId} eYaMenTaskState={eYaMenTaskState}/>;
			else
				topXml = <SYaMenTask dwTaskId={dwTaskId} eYaMenTaskState={eYaMenTaskState}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwTaskId = dwTaskId;
			obj_.eYaMenTaskState = eYaMenTaskState;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SYaMenTask
		{
			var s_:SYaMenTask = new SYaMenTask();
			var dwTaskId:uint = bytes.readUnsignedInt();
			s_.dwTaskId = dwTaskId;
			var eYaMenTaskState:uint = bytes.readUnsignedByte();
			s_.eYaMenTaskState = eYaMenTaskState;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SYaMenTask>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SYaMenTask> = new Vector.<SYaMenTask>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SYaMenTask = SYaMenTask.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwTaskId);
			bytes.writeByte(eYaMenTaskState);
		}

		public static function vectorToByteArray(vec:Vector.<SYaMenTask>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SYaMenTask in vec)
				s.toByteArray(bytes);
		}
	}
}
