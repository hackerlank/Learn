/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateGroupTask.as
//  Purpose:      协议:师门任务协议, 函数:任务列表更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateGroupTask[任务列表更新]的接收事件
	 */
	public final class REvt_UpdateGroupTask extends Event
	{
		public static const DATA_RECEIVE:String = "GroupTaskProt_UpdateGroupTask";
		public static const DATA_ERROR:String = "GroupTaskProt_UpdateGroupTask_Error";

		public var stTask:SGroupTask; //师门任务详情

		public function REvt_UpdateGroupTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateGroupTask/>;
			if(stTask != null)
				topXml.appendChild(stTask.toXML("stTask"));
			return topXml;
		}
	}
}
