/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendTopic.as
//  Purpose:      协议:答题协议, 函数:发送题目
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数SendTopic[发送题目]的接收事件
	 */
	public final class REvt_SendTopic extends Event
	{
		public static const DATA_RECEIVE:String = "AnswerProt_SendTopic";
		public static const DATA_ERROR:String = "AnswerProt_SendTopic_Error";

		public var sTopic:SAnswerTopic; //题目信息

		public function REvt_SendTopic(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendTopic/>;
			if(sTopic != null)
				topXml.appendChild(sTopic.toXML("sTopic"));
			return topXml;
		}
	}
}
