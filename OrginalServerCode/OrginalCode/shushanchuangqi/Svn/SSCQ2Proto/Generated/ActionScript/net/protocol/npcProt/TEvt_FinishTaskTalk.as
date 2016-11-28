/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_FinishTaskTalk.as
//  Purpose:      协议:NPC相关协议, 函数:完成一任务对话
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	import flash.events.Event;

	/**
	 * 函数FinishTaskTalk[完成一任务对话]的返回事件
	 */
	public final class TEvt_FinishTaskTalk extends Event
	{
		public static const DATA_RETURN:String = "NpcProt_FinishTaskTalk";
		public static const DATA_ERROR:String = "NpcProt_FinishTaskTalk_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_FinishTaskTalk; //返回的参数

		public function TEvt_FinishTaskTalk(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_FinishTaskTalk ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
