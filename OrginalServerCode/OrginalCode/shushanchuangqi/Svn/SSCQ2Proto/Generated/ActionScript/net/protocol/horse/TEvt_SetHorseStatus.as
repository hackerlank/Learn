/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_SetHorseStatus.as
//  Purpose:      协议:坐骑, 函数:骑乘状态修改
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数SetHorseStatus[骑乘状态修改]的返回事件
	 */
	public final class TEvt_SetHorseStatus extends Event
	{
		public static const DATA_RETURN:String = "Horse_SetHorseStatus";
		public static const DATA_ERROR:String = "Horse_SetHorseStatus_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_SetHorseStatus; //返回的参数

		public function TEvt_SetHorseStatus(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_SetHorseStatus ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
