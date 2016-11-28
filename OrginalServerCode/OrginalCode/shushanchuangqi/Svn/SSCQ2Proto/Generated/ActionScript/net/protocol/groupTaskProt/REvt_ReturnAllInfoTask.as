/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ReturnAllInfoTask.as
//  Purpose:      协议:师门任务协议, 函数:获取师门任务详情
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.events.Event;

	/**
	 * 函数ReturnAllInfoTask[获取师门任务详情]的接收事件
	 */
	public final class REvt_ReturnAllInfoTask extends Event
	{
		public static const DATA_RECEIVE:String = "GroupTaskProt_ReturnAllInfoTask";
		public static const DATA_ERROR:String = "GroupTaskProt_ReturnAllInfoTask_Error";

		public var stGroupTaskInfo:SGroupTaskInfoForClient; //师门任务详情

		public function REvt_ReturnAllInfoTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ReturnAllInfoTask/>;
			if(stGroupTaskInfo != null)
				topXml.appendChild(stGroupTaskInfo.toXML("stGroupTaskInfo"));
			return topXml;
		}
	}
}
