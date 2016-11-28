/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateYaMenTask.as
//  Purpose:      协议:衙门任务协议, 函数:任务列表更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateYaMenTask[任务列表更新]的接收事件
	 */
	public final class REvt_UpdateYaMenTask extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_UpdateYaMenTask";
		public static const DATA_ERROR:String = "YaMenTaskProt_UpdateYaMenTask_Error";

		public var stTask:SYaMenTask; //衙门任务详情

		public function REvt_UpdateYaMenTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateYaMenTask/>;
			if(stTask != null)
				topXml.appendChild(stTask.toXML("stTask"));
			return topXml;
		}
	}
}
