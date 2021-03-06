/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GiveUpTask.as
//  Purpose:      协议:任务协议, 函数:放弃任务请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数GiveUpTask[放弃任务请求]的返回事件
	 */
	public final class TEvt_GiveUpTask extends Event
	{
		public static const DATA_RETURN:String = "TaskProt_GiveUpTask";
		public static const DATA_ERROR:String = "TaskProt_GiveUpTask_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GiveUpTask; //返回的参数

		public function TEvt_GiveUpTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GiveUpTask ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
