/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AnswerAlarm.as
//  Purpose:      协议:答题协议, 函数:答题预告
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数AnswerAlarm[答题预告]的接收事件
	 */
	public final class REvt_AnswerAlarm extends Event
	{
		public static const DATA_RECEIVE:String = "AnswerProt_AnswerAlarm";
		public static const DATA_ERROR:String = "AnswerProt_AnswerAlarm_Error";

		public var dwTime:uint; //(无符号32位整数)时间

		public function REvt_AnswerAlarm(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AnswerAlarm dwTime={dwTime}/>;
			return topXml;
		}
	}
}
