/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyTaskRecordAck.as
//  Purpose:      协议:任务协议, 函数:任务记录
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数NotifyTaskRecordAck[任务记录]的接收事件
	 */
	public final class REvt_NotifyTaskRecordAck extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_NotifyTaskRecordAck";
		public static const DATA_ERROR:String = "TaskProt_NotifyTaskRecordAck_Error";

		public var vecTaskID:Vector.<uint>; //(无符号16位整数)任务完成记录

		public function REvt_NotifyTaskRecordAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyTaskRecordAck/>;
			if(vecTaskID != null)
			{
				var vecTaskIDXml:XML = <Vec_UINT16 _name_="vecTaskID"/>;
				var text1:String = "";
				for each(var value1:uint in vecTaskID)
					text1 += "[" + value1 + "]";
				vecTaskIDXml.appendChild(text1);
				topXml.appendChild(vecTaskIDXml);
			}
			return topXml;
		}
	}
}
