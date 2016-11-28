/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateFinishTask.as
//  Purpose:      协议:师门任务协议, 函数:完成任务数更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateFinishTask[完成任务数更新]的接收事件
	 */
	public final class REvt_UpdateFinishTask extends Event
	{
		public static const DATA_RECEIVE:String = "GroupTaskProt_UpdateFinishTask";
		public static const DATA_ERROR:String = "GroupTaskProt_UpdateFinishTask_Error";

		public var byFinishTask:uint; //(无符号8位整数)今日完成的师门任务数
		public var byAcceptTaskTimes:uint; //(无符号8位整数)剩余可接任务数
		public var byVIPTaskTimes:uint; //(无符号8位整数)购买的可接任务数
		public var byBuyTimesToday:uint; //(无符号8位整数)今日购买的任务数

		public function REvt_UpdateFinishTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateFinishTask byFinishTask={byFinishTask} byAcceptTaskTimes={byAcceptTaskTimes} byVIPTaskTimes={byVIPTaskTimes} byBuyTimesToday={byBuyTimesToday}/>;
			return topXml;
		}
	}
}
