/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AnswerCountdown.as
//  Purpose:      协议:答题协议, 函数:答题开始倒计时30秒通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数AnswerCountdown[答题开始倒计时30秒通知]的接收事件
	 */
	public final class REvt_AnswerCountdown extends Event
	{
		public static const DATA_RECEIVE:String = "AnswerProt_AnswerCountdown";
		public static const DATA_ERROR:String = "AnswerProt_AnswerCountdown_Error";

		public var dwTime:uint; //(无符号32位整数)时间

		public function REvt_AnswerCountdown(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AnswerCountdown dwTime={dwTime}/>;
			return topXml;
		}
	}
}
