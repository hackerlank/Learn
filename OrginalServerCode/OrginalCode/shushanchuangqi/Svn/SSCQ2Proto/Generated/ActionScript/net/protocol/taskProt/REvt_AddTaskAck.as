/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddTaskAck.as
//  Purpose:      协议:任务协议, 函数:添加任务
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数AddTaskAck[添加任务]的接收事件
	 */
	public final class REvt_AddTaskAck extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_AddTaskAck";
		public static const DATA_ERROR:String = "TaskProt_AddTaskAck_Error";

		public var byCost:uint; //(无符号8位整数)立即完成
		public var rTask:STask; //任务

		public function REvt_AddTaskAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddTaskAck byCost={byCost}/>;
			if(rTask != null)
				topXml.appendChild(rTask.toXML("rTask"));
			return topXml;
		}
	}
}
