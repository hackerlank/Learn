/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FreeMoneyCdNotify.as
//  Purpose:      协议:美女系统, 函数:免费抽奖cd
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数FreeMoneyCdNotify[免费抽奖cd]的接收事件
	 */
	public final class REvt_FreeMoneyCdNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Beauty_FreeMoneyCdNotify";
		public static const DATA_ERROR:String = "Beauty_FreeMoneyCdNotify_Error";

		public var eLotteryBeautyType:uint; //(枚举类型：ELotteryBeautyType)抽奖类型,只有单次金币，银币两种类型
		public var dwNextChatTime:uint; //(无符号32位整数)下次聊天冷却时间

		public function REvt_FreeMoneyCdNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FreeMoneyCdNotify eLotteryBeautyType={eLotteryBeautyType} dwNextChatTime={dwNextChatTime}/>;
			return topXml;
		}
	}
}
