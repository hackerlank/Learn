/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ReturnAllInfoTask.as
//  Purpose:      协议:衙门任务协议, 函数:获取衙门任务详情
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数ReturnAllInfoTask[获取衙门任务详情]的接收事件
	 */
	public final class REvt_ReturnAllInfoTask extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_ReturnAllInfoTask";
		public static const DATA_ERROR:String = "YaMenTaskProt_ReturnAllInfoTask_Error";

		public var stYaMenTaskInfo:SYaMenTaskInfoForClient; //衙门任务详情

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
			if(stYaMenTaskInfo != null)
				topXml.appendChild(stYaMenTaskInfo.toXML("stYaMenTaskInfo"));
			return topXml;
		}
	}
}
