/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FeedBackExpireNotify.as
//  Purpose:      协议:消费回馈, 函数:回馈活动过期
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	import flash.events.Event;

	/**
	 * 函数FeedBackExpireNotify[回馈活动过期]的接收事件
	 */
	public final class REvt_FeedBackExpireNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FeedBackProt_FeedBackExpireNotify";
		public static const DATA_ERROR:String = "FeedBackProt_FeedBackExpireNotify_Error";

		public var dwActID:uint; //(无符号32位整数)活动id

		public function REvt_FeedBackExpireNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FeedBackExpireNotify dwActID={dwActID}/>;
			return topXml;
		}
	}
}
