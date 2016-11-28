/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SpotInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派战据点信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数SpotInfoNotify[帮派战据点信息通知]的接收事件
	 */
	public final class REvt_SpotInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_SpotInfoNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_SpotInfoNotify_Error";

		public var vecSpotInfo:Vector.<SSpotInfo>; //据点详细信息

		public function REvt_SpotInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SpotInfoNotify/>;
			if(vecSpotInfo != null)
			{
				var vecSpotInfoXml:XML = <Vec_SSpotInfo _name_="vecSpotInfo"/>;
				for each(var s1:SSpotInfo in vecSpotInfo)
					vecSpotInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSpotInfoXml);
			}
			return topXml;
		}
	}
}
