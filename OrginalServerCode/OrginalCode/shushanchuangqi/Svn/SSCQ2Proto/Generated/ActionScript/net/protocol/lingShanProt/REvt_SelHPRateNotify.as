/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SelHPRateNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家个人血量通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数SelHPRateNotify[玩家个人血量通知]的接收事件
	 */
	public final class REvt_SelHPRateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_SelHPRateNotify";
		public static const DATA_ERROR:String = "LingShanProt_SelHPRateNotify_Error";

		public var fHPRate:Number; //(Float)血量百分比

		public function REvt_SelHPRateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SelHPRateNotify fHPRate={fHPRate}/>;
			return topXml;
		}
	}
}
