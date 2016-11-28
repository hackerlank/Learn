/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FieldInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派战信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数FieldInfoNotify[帮派战信息通知]的接收事件
	 */
	public final class REvt_FieldInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_FieldInfoNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_FieldInfoNotify_Error";

		public var sFieldInfo:SFieldInfo; //战场信息

		public function REvt_FieldInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FieldInfoNotify/>;
			if(sFieldInfo != null)
				topXml.appendChild(sFieldInfo.toXML("sFieldInfo"));
			return topXml;
		}
	}
}
