/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PanelInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:更新帮派战小面板信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PanelInfoNotify[更新帮派战小面板信息]的接收事件
	 */
	public final class REvt_PanelInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_PanelInfoNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_PanelInfoNotify_Error";

		public var dwSelfScore:uint; //(无符号32位整数)我的积分
		public var dwGuildScore:uint; //(无符号32位整数)帮派积分
		public var dwGuildRank:uint; //(无符号32位整数)帮派排名

		public function REvt_PanelInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PanelInfoNotify dwSelfScore={dwSelfScore} dwGuildScore={dwGuildScore} dwGuildRank={dwGuildRank}/>;
			return topXml;
		}
	}
}
