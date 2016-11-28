/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildApplyPassedNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派申请通过通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildApplyPassedNotify[帮派申请通过通知]的接收事件
	 */
	public final class REvt_GuildApplyPassedNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildApplyPassedNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildApplyPassedNotify_Error";

		public var sGuildAllInfo:SGuildAllInfo; //帮派信息

		public function REvt_GuildApplyPassedNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildApplyPassedNotify/>;
			if(sGuildAllInfo != null)
				topXml.appendChild(sGuildAllInfo.toXML("sGuildAllInfo"));
			return topXml;
		}
	}
}
