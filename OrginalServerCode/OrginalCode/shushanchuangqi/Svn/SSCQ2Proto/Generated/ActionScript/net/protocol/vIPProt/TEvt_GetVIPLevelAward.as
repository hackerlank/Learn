/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetVIPLevelAward.as
//  Purpose:      协议:VIP特权相关协议, 函数:领取VIP特权等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import flash.events.Event;

	/**
	 * 函数GetVIPLevelAward[领取VIP特权等级奖励]的返回事件
	 */
	public final class TEvt_GetVIPLevelAward extends Event
	{
		public static const DATA_RETURN:String = "VIPProt_GetVIPLevelAward";
		public static const DATA_ERROR:String = "VIPProt_GetVIPLevelAward_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetVIPLevelAward; //返回的参数

		public function TEvt_GetVIPLevelAward(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetVIPLevelAward ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
