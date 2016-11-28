/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TaskUpdateNtf.as
//  Purpose:      协议:任务协议, 函数:任务更新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数TaskUpdateNtf[任务更新通知]的接收事件
	 */
	public final class REvt_TaskUpdateNtf extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_TaskUpdateNtf";
		public static const DATA_ERROR:String = "TaskProt_TaskUpdateNtf_Error";

		public var rTask:STask; //任务

		public function REvt_TaskUpdateNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TaskUpdateNtf/>;
			if(rTask != null)
				topXml.appendChild(rTask.toXML("rTask"));
			return topXml;
		}
	}
}
