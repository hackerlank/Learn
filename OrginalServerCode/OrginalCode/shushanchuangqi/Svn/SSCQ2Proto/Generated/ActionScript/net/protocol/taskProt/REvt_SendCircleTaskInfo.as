/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendCircleTaskInfo.as
//  Purpose:      协议:任务协议, 函数:通知环任务信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数SendCircleTaskInfo[通知环任务信息]的接收事件
	 */
	public final class REvt_SendCircleTaskInfo extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_SendCircleTaskInfo";
		public static const DATA_ERROR:String = "TaskProt_SendCircleTaskInfo_Error";

		public var byStar:uint; //(无符号8位整数)环任务星级
		public var byNum:uint; //(无符号8位整数)环任务环数

		public function REvt_SendCircleTaskInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendCircleTaskInfo byStar={byStar} byNum={byNum}/>;
			return topXml;
		}
	}
}
