/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateTaskList.as
//  Purpose:      协议:七日目标活动, 函数:任务信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
{
	import flash.events.Event;

	/**
	 * 函数UpdateTaskList[任务信息更新]的接收事件
	 */
	public final class REvt_UpdateTaskList extends Event
	{
		public static const DATA_RECEIVE:String = "DayTarget_UpdateTaskList";
		public static const DATA_ERROR:String = "DayTarget_UpdateTaskList_Error";

		public var oDayTargetTask:SDayTargetTask; //任务信息

		public function REvt_UpdateTaskList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateTaskList/>;
			if(oDayTargetTask != null)
				topXml.appendChild(oDayTargetTask.toXML("oDayTargetTask"));
			return topXml;
		}
	}
}
