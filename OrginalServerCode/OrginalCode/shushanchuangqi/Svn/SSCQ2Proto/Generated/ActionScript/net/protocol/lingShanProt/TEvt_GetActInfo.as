/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetActInfo.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:获取活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数GetActInfo[获取活动信息]的返回事件
	 */
	public final class TEvt_GetActInfo extends Event
	{
		public static const DATA_RETURN:String = "LingShanProt_GetActInfo";
		public static const DATA_ERROR:String = "LingShanProt_GetActInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetActInfo; //返回的参数

		public function TEvt_GetActInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetActInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
