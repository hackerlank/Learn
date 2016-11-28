/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PrizeNotify.as
//  Purpose:      协议:中午挂机活动, 函数:发送经验值和修为值
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.events.Event;

	/**
	 * 函数PrizeNotify[发送经验值和修为值]的接收事件
	 */
	public final class REvt_PrizeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LangHuanBlessProt_PrizeNotify";
		public static const DATA_ERROR:String = "LangHuanBlessProt_PrizeNotify_Error";

		public var dwXiuwei:uint; //(无符号32位整数)修为值
		public var dwExp:uint; //(无符号32位整数)经验值

		public function REvt_PrizeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PrizeNotify dwXiuwei={dwXiuwei} dwExp={dwExp}/>;
			return topXml;
		}
	}
}
