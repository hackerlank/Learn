/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetTaskList.as
//  Purpose:      协议:七日目标活动, 函数:获取任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
{
	import flash.events.Event;

	/**
	 * 函数GetTaskList[获取任务列表]的返回事件
	 */
	public final class TEvt_GetTaskList extends Event
	{
		public static const DATA_RETURN:String = "DayTarget_GetTaskList";
		public static const DATA_ERROR:String = "DayTarget_GetTaskList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetTaskList; //返回的参数

		public function TEvt_GetTaskList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetTaskList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
