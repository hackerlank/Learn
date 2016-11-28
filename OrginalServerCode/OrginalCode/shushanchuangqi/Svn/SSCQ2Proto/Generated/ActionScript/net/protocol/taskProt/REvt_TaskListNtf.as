/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TaskListNtf.as
//  Purpose:      协议:任务协议, 函数:任务列表通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数TaskListNtf[任务列表通知]的接收事件
	 */
	public final class REvt_TaskListNtf extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_TaskListNtf";
		public static const DATA_ERROR:String = "TaskProt_TaskListNtf_Error";

		public var vecTask:Vector.<STask>; //任务列表

		public function REvt_TaskListNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TaskListNtf/>;
			if(vecTask != null)
			{
				var vecTaskXml:XML = <Vec_STask _name_="vecTask"/>;
				for each(var s1:STask in vecTask)
					vecTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecTaskXml);
			}
			return topXml;
		}
	}
}
