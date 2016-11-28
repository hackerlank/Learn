/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetBuyAtkCountPrice.as
//  Purpose:      协议:破阵, 函数:获取当前购买价格
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数GetBuyAtkCountPrice[获取当前购买价格]的返回事件
	 */
	public final class TEvt_GetBuyAtkCountPrice extends Event
	{
		public static const DATA_RETURN:String = "BattleArray_GetBuyAtkCountPrice";
		public static const DATA_ERROR:String = "BattleArray_GetBuyAtkCountPrice_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetBuyAtkCountPrice; //返回的参数

		public function TEvt_GetBuyAtkCountPrice(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetBuyAtkCountPrice ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
