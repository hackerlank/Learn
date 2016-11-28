/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BuyAction.as
//  Purpose:      协议:不好归类的小协议, 函数:购买体力
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数BuyAction[购买体力]的返回事件
	 */
	public final class TEvt_BuyAction extends Event
	{
		public static const DATA_RETURN:String = "MiscProt_BuyAction";
		public static const DATA_ERROR:String = "MiscProt_BuyAction_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BuyAction; //返回的参数

		public function TEvt_BuyAction(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BuyAction ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
