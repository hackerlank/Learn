/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BubbleGet.as
//  Purpose:      协议:聊天协议, 函数:气泡信息获取
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;

	/**
	 * 函数BubbleGet[气泡信息获取]的返回事件
	 */
	public final class TEvt_BubbleGet extends Event
	{
		public static const DATA_RETURN:String = "ChatProt_BubbleGet";
		public static const DATA_ERROR:String = "ChatProt_BubbleGet_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BubbleGet; //返回的参数

		public function TEvt_BubbleGet(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BubbleGet ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
