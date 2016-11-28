/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AnswerBegin.as
//  Purpose:      协议:答题协议, 函数:答题开始
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数AnswerBegin[答题开始]的接收事件
	 */
	public final class REvt_AnswerBegin extends Event
	{
		public static const DATA_RECEIVE:String = "AnswerProt_AnswerBegin";
		public static const DATA_ERROR:String = "AnswerProt_AnswerBegin_Error";

		public var dwTime:uint; //(无符号32位整数)时间

		public function REvt_AnswerBegin(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AnswerBegin dwTime={dwTime}/>;
			return topXml;
		}
	}
}
