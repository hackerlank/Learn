/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_FinishTask.as
//  Purpose:      协议:任务协议, 函数:完成任务请求(领取奖励)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数FinishTask[完成任务请求(领取奖励)]的返回事件
	 */
	public final class TEvt_FinishTask extends Event
	{
		public static const DATA_RETURN:String = "TaskProt_FinishTask";
		public static const DATA_ERROR:String = "TaskProt_FinishTask_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_FinishTask; //返回的参数

		public function TEvt_FinishTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_FinishTask ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
