/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GainYDBag.as
//  Purpose:      协议:QQ黄钻协议, 函数:获取黄钻礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
{
	import flash.events.Event;

	/**
	 * 函数GainYDBag[获取黄钻礼包]的返回事件
	 */
	public final class TEvt_GainYDBag extends Event
	{
		public static const DATA_RETURN:String = "YelloDiamondProt_GainYDBag";
		public static const DATA_ERROR:String = "YelloDiamondProt_GainYDBag_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GainYDBag; //返回的参数

		public function TEvt_GainYDBag(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GainYDBag ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
