/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_MeetBeauty.as
//  Purpose:      协议:美女系统, 函数:结识美女
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数MeetBeauty[结识美女]的返回事件
	 */
	public final class TEvt_MeetBeauty extends Event
	{
		public static const DATA_RETURN:String = "Beauty_MeetBeauty";
		public static const DATA_ERROR:String = "Beauty_MeetBeauty_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_MeetBeauty; //返回的参数

		public function TEvt_MeetBeauty(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_MeetBeauty ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
