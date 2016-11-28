/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildApplyRejectNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派申请拒绝通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数GuildApplyRejectNotify[帮派申请拒绝通知]的接收事件
	 */
	public final class REvt_GuildApplyRejectNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildApplyRejectNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildApplyRejectNotify_Error";

		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID

		public function REvt_GuildApplyRejectNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildApplyRejectNotify qwGuildID={qwGuildID}/>;
			return topXml;
		}
	}
}
