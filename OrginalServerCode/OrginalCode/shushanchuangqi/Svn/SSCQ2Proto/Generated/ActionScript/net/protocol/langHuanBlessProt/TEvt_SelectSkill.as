/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_SelectSkill.as
//  Purpose:      协议:中午挂机活动, 函数:选择问道
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.events.Event;

	/**
	 * 函数SelectSkill[选择问道]的返回事件
	 */
	public final class TEvt_SelectSkill extends Event
	{
		public static const DATA_RETURN:String = "LangHuanBlessProt_SelectSkill";
		public static const DATA_ERROR:String = "LangHuanBlessProt_SelectSkill_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_SelectSkill; //返回的参数

		public function TEvt_SelectSkill(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_SelectSkill ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
