/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BuySkill.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:购买蜀山论剑霸气or怒气
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数BuySkill[购买蜀山论剑霸气or怒气]的返回事件
	 */
	public final class TEvt_BuySkill extends Event
	{
		public static const DATA_RETURN:String = "ShushanBattleProt_BuySkill";
		public static const DATA_ERROR:String = "ShushanBattleProt_BuySkill_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BuySkill; //返回的参数

		public function TEvt_BuySkill(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BuySkill ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
