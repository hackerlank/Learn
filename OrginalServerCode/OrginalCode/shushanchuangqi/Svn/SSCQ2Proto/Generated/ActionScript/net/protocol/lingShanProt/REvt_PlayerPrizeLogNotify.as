/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerPrizeLogNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家奖励log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerPrizeLogNotify[玩家奖励log]的接收事件
	 */
	public final class REvt_PlayerPrizeLogNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_PlayerPrizeLogNotify";
		public static const DATA_ERROR:String = "LingShanProt_PlayerPrizeLogNotify_Error";

		public var vecTakePrizeLog:Vector.<STakePrizeLog>; //玩家奖励log列表

		public function REvt_PlayerPrizeLogNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerPrizeLogNotify/>;
			if(vecTakePrizeLog != null)
			{
				var vecTakePrizeLogXml:XML = <Vec_STakePrizeLog _name_="vecTakePrizeLog"/>;
				for each(var s1:STakePrizeLog in vecTakePrizeLog)
					vecTakePrizeLogXml.appendChild(s1.toXML());
				topXml.appendChild(vecTakePrizeLogXml);
			}
			return topXml;
		}
	}
}
