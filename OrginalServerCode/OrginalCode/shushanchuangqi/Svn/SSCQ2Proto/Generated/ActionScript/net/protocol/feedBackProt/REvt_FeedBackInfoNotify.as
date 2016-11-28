/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FeedBackInfoNotify.as
//  Purpose:      协议:消费回馈, 函数:回馈信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	import flash.events.Event;

	/**
	 * 函数FeedBackInfoNotify[回馈信息更新]的接收事件
	 */
	public final class REvt_FeedBackInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FeedBackProt_FeedBackInfoNotify";
		public static const DATA_ERROR:String = "FeedBackProt_FeedBackInfoNotify_Error";

		public var oFeedBackInfo:SFeedBackInfo; //回馈信息

		public function REvt_FeedBackInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FeedBackInfoNotify/>;
			if(oFeedBackInfo != null)
				topXml.appendChild(oFeedBackInfo.toXML("oFeedBackInfo"));
			return topXml;
		}
	}
}
