/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetHorseAttr.as
//  Purpose:      协议:坐骑, 函数:获取坐骑属性
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数GetHorseAttr[获取坐骑属性]的返回事件
	 */
	public final class TEvt_GetHorseAttr extends Event
	{
		public static const DATA_RETURN:String = "Horse_GetHorseAttr";
		public static const DATA_ERROR:String = "Horse_GetHorseAttr_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetHorseAttr; //返回的参数

		public function TEvt_GetHorseAttr(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetHorseAttr ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
