/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetMoneyList.as
//  Purpose:      协议:不好归类的小协议, 函数:获取货币基础数值
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数GetMoneyList[获取货币基础数值]的返回事件
	 */
	public final class TEvt_GetMoneyList extends Event
	{
		public static const DATA_RETURN:String = "MiscProt_GetMoneyList";
		public static const DATA_ERROR:String = "MiscProt_GetMoneyList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetMoneyList; //返回的参数

		public function TEvt_GetMoneyList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetMoneyList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
