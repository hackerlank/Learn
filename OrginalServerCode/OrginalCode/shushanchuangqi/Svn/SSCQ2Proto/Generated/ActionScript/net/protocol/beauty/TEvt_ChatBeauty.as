/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ChatBeauty.as
//  Purpose:      协议:美女系统, 函数:和美女聊天
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数ChatBeauty[和美女聊天]的返回事件
	 */
	public final class TEvt_ChatBeauty extends Event
	{
		public static const DATA_RETURN:String = "Beauty_ChatBeauty";
		public static const DATA_ERROR:String = "Beauty_ChatBeauty_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ChatBeauty; //返回的参数

		public function TEvt_ChatBeauty(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ChatBeauty ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
