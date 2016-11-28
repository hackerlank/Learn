/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_FlushTask.as
//  Purpose:      协议:师门任务协议, 函数:刷新师门任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.events.Event;

	/**
	 * 函数FlushTask[刷新师门任务列表]的返回事件
	 */
	public final class TEvt_FlushTask extends Event
	{
		public static const DATA_RETURN:String = "GroupTaskProt_FlushTask";
		public static const DATA_ERROR:String = "GroupTaskProt_FlushTask_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_FlushTask; //返回的参数

		public function TEvt_FlushTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_FlushTask ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
