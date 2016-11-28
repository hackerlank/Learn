/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_LevelPrizeNotify.as
//  Purpose:      协议:等级奖励, 函数:等级奖励活动状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.events.Event;

	/**
	 * 函数LevelPrizeNotify[等级奖励活动状态通知]的接收事件
	 */
	public final class REvt_LevelPrizeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LevelPrize_LevelPrizeNotify";
		public static const DATA_ERROR:String = "LevelPrize_LevelPrizeNotify_Error";

		public var wActID:uint; //(无符号16位整数)活动Id
		public var eStatus:uint; //(枚举类型：EActState)活动状态

		public function REvt_LevelPrizeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_LevelPrizeNotify wActID={wActID} eStatus={eStatus}/>;
			return topXml;
		}
	}
}
