/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildKickNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派被踢出通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数GuildKickNotify[帮派被踢出通知]的接收事件
	 */
	public final class REvt_GuildKickNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildKickNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildKickNotify_Error";

		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var strName:String; //帮派名称
		public var strKickName:String; //踢人者姓名

		public function REvt_GuildKickNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildKickNotify qwGuildID={qwGuildID} strName={strName} strKickName={strKickName}/>;
			return topXml;
		}
	}
}
