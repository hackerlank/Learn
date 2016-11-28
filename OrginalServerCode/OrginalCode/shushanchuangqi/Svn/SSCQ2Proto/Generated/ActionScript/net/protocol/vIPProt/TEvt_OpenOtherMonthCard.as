/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_OpenOtherMonthCard.as
//  Purpose:      协议:VIP特权相关协议, 函数:请求开启好友月卡
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import flash.events.Event;

	/**
	 * 函数OpenOtherMonthCard[请求开启好友月卡]的返回事件
	 */
	public final class TEvt_OpenOtherMonthCard extends Event
	{
		public static const DATA_RETURN:String = "VIPProt_OpenOtherMonthCard";
		public static const DATA_ERROR:String = "VIPProt_OpenOtherMonthCard_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_OpenOtherMonthCard; //返回的参数

		public function TEvt_OpenOtherMonthCard(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_OpenOtherMonthCard ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
