/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetFirstRechargeStatus.as
//  Purpose:      协议:活动, 函数:是否已领取首充礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	import flash.events.Event;

	/**
	 * 函数GetFirstRechargeStatus[是否已领取首充礼包]的返回事件
	 */
	public final class TEvt_GetFirstRechargeStatus extends Event
	{
		public static const DATA_RETURN:String = "DayActProt_GetFirstRechargeStatus";
		public static const DATA_ERROR:String = "DayActProt_GetFirstRechargeStatus_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetFirstRechargeStatus; //返回的参数

		public function TEvt_GetFirstRechargeStatus(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetFirstRechargeStatus ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
