/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ElasticFrameNotify.as
//  Purpose:      协议:聊天协议, 函数:弹窗通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;

	/**
	 * 函数ElasticFrameNotify[弹窗通知]的接收事件
	 */
	public final class REvt_ElasticFrameNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ChatProt_ElasticFrameNotify";
		public static const DATA_ERROR:String = "ChatProt_ElasticFrameNotify_Error";

		public var wMsgID:uint; //(无符号16位整数)消息ID

		public function REvt_ElasticFrameNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ElasticFrameNotify wMsgID={wMsgID}/>;
			return topXml;
		}
	}
}
