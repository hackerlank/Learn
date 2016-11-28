/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_APNotify.as
//  Purpose:      协议:成就相关协议, 函数:成就点通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.events.Event;

	/**
	 * 函数APNotify[成就点通知]的接收事件
	 */
	public final class REvt_APNotify extends Event
	{
		public static const DATA_RECEIVE:String = "AchievementProt_APNotify";
		public static const DATA_ERROR:String = "AchievementProt_APNotify_Error";

		public var dwAP:uint; //(无符号32位整数)成就点

		public function REvt_APNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_APNotify dwAP={dwAP}/>;
			return topXml;
		}
	}
}
