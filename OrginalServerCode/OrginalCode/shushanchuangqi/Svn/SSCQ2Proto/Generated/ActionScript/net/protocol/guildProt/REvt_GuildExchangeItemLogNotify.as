/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildExchangeItemLogNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派兑换物品日志更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildExchangeItemLogNotify[帮派兑换物品日志更新]的接收事件
	 */
	public final class REvt_GuildExchangeItemLogNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildExchangeItemLogNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildExchangeItemLogNotify_Error";

		public var sGuildLogInfo:SGuildLogInfo; //兑换物品日志信息

		public function REvt_GuildExchangeItemLogNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildExchangeItemLogNotify/>;
			if(sGuildLogInfo != null)
				topXml.appendChild(sGuildLogInfo.toXML("sGuildLogInfo"));
			return topXml;
		}
	}
}
