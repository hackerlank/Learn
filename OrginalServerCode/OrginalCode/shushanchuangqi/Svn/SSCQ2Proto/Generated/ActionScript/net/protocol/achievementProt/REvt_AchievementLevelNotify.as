/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AchievementLevelNotify.as
//  Purpose:      协议:成就相关协议, 函数:成就等级通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.events.Event;

	/**
	 * 函数AchievementLevelNotify[成就等级通知]的接收事件
	 */
	public final class REvt_AchievementLevelNotify extends Event
	{
		public static const DATA_RECEIVE:String = "AchievementProt_AchievementLevelNotify";
		public static const DATA_ERROR:String = "AchievementProt_AchievementLevelNotify_Error";

		public var wLevel:uint; //(无符号16位整数)成就等级

		public function REvt_AchievementLevelNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AchievementLevelNotify wLevel={wLevel}/>;
			return topXml;
		}
	}
}
