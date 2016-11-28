/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PrizeNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:玩家奖励获取通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数PrizeNotify[玩家奖励获取通知]的接收事件
	 */
	public final class REvt_PrizeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_PrizeNotify";
		public static const DATA_ERROR:String = "BossProt_PrizeNotify_Error";

		public var vecPlayerPrize:Vector.<SPlayerPrize>; //玩家奖励列表

		public function REvt_PrizeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PrizeNotify/>;
			if(vecPlayerPrize != null)
			{
				var vecPlayerPrizeXml:XML = <Vec_SPlayerPrize _name_="vecPlayerPrize"/>;
				for each(var s1:SPlayerPrize in vecPlayerPrize)
					vecPlayerPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlayerPrizeXml);
			}
			return topXml;
		}
	}
}
