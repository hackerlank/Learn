/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_CaveCapture.as
//  Purpose:      协议:新帮派战相关协议, 函数:洞府战占领阵眼
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数CaveCapture[洞府战占领阵眼]的返回事件
	 */
	public final class TEvt_CaveCapture extends Event
	{
		public static const DATA_RETURN:String = "NewGuildBattleProt_CaveCapture";
		public static const DATA_ERROR:String = "NewGuildBattleProt_CaveCapture_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_CaveCapture; //返回的参数

		public function TEvt_CaveCapture(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_CaveCapture ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
