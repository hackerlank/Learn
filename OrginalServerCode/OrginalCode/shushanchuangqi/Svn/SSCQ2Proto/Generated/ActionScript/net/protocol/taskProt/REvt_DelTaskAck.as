/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DelTaskAck.as
//  Purpose:      协议:任务协议, 函数:删除任务
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数DelTaskAck[删除任务]的接收事件
	 */
	public final class REvt_DelTaskAck extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_DelTaskAck";
		public static const DATA_ERROR:String = "TaskProt_DelTaskAck_Error";

		public var wTaskID:uint; //(无符号16位整数)任务ID

		public function REvt_DelTaskAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DelTaskAck wTaskID={wTaskID}/>;
			return topXml;
		}
	}
}
