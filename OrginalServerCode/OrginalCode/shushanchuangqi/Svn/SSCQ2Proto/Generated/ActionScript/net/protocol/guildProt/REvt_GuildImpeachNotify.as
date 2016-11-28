/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildImpeachNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派弹劾通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数GuildImpeachNotify[帮派弹劾通知]的接收事件
	 */
	public final class REvt_GuildImpeachNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildImpeachNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildImpeachNotify_Error";

		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var strLauncherName:String; //发起者姓名
		public var strOwnerName:String; //帮主姓名

		public function REvt_GuildImpeachNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildImpeachNotify qwGuildID={qwGuildID} strLauncherName={strLauncherName} strOwnerName={strOwnerName}/>;
			return topXml;
		}
	}
}
