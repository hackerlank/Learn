/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateMonthCardOverdue.as
//  Purpose:      协议:VIP特权相关协议, 函数:月卡过期通知消息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateMonthCardOverdue[月卡过期通知消息]的接收事件
	 */
	public final class REvt_UpdateMonthCardOverdue extends Event
	{
		public static const DATA_RECEIVE:String = "VIPProt_UpdateMonthCardOverdue";
		public static const DATA_ERROR:String = "VIPProt_UpdateMonthCardOverdue_Error";

		public var byVal:uint; //(无符号8位整数)0未过期 >0已过期

		public function REvt_UpdateMonthCardOverdue(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateMonthCardOverdue byVal={byVal}/>;
			return topXml;
		}
	}
}
