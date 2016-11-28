/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetLayerPrized.as
//  Purpose:      协议:锁妖塔, 函数:获取已领奖励层数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数GetLayerPrized[获取已领奖励层数]的返回事件
	 */
	public final class TEvt_GetLayerPrized extends Event
	{
		public static const DATA_RETURN:String = "DemonTower_GetLayerPrized";
		public static const DATA_ERROR:String = "DemonTower_GetLayerPrized_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetLayerPrized; //返回的参数

		public function TEvt_GetLayerPrized(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetLayerPrized ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
