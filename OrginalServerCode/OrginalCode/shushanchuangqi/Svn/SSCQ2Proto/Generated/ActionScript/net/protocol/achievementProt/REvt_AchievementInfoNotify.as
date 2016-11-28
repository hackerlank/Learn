/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AchievementInfoNotify.as
//  Purpose:      协议:成就相关协议, 函数:成就等级通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.events.Event;

	/**
	 * 函数AchievementInfoNotify[成就等级通知]的接收事件
	 */
	public final class REvt_AchievementInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "AchievementProt_AchievementInfoNotify";
		public static const DATA_ERROR:String = "AchievementProt_AchievementInfoNotify_Error";

		public var oAchievementInfo:SAchievementInfo; //成就信息

		public function REvt_AchievementInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AchievementInfoNotify/>;
			if(oAchievementInfo != null)
				topXml.appendChild(oAchievementInfo.toXML("oAchievementInfo"));
			return topXml;
		}
	}
}
