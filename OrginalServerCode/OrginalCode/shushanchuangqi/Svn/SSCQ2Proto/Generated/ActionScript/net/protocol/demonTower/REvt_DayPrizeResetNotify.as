/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DayPrizeResetNotify.as
//  Purpose:      协议:锁妖塔, 函数:每日重置奖励通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数DayPrizeResetNotify[每日重置奖励通知]的接收事件
	 */
	public final class REvt_DayPrizeResetNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_DayPrizeResetNotify";
		public static const DATA_ERROR:String = "DemonTower_DayPrizeResetNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数

		public function REvt_DayPrizeResetNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DayPrizeResetNotify dwFloorID={dwFloorID}/>;
			return topXml;
		}
	}
}
