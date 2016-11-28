/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateGuildXiheInfo.as
//  Purpose:      协议:帮派相关协议, 函数:更新玩家羲和神车信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateGuildXiheInfo[更新玩家羲和神车信息]的接收事件
	 */
	public final class REvt_UpdateGuildXiheInfo extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_UpdateGuildXiheInfo";
		public static const DATA_ERROR:String = "GuildProt_UpdateGuildXiheInfo_Error";

		public var sGuildXihe:SGuildXihe; //玩家羲和神车信息

		public function REvt_UpdateGuildXiheInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateGuildXiheInfo/>;
			if(sGuildXihe != null)
				topXml.appendChild(sGuildXihe.toXML("sGuildXihe"));
			return topXml;
		}
	}
}
