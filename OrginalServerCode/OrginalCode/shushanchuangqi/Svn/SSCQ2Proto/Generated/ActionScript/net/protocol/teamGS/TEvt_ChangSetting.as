/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ChangSetting.as
//  Purpose:      协议:竞技场协议, 函数:更改设置请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数ChangSetting[更改设置请求]的返回事件
	 */
	public final class TEvt_ChangSetting extends Event
	{
		public static const DATA_RETURN:String = "TeamGS_ChangSetting";
		public static const DATA_ERROR:String = "TeamGS_ChangSetting_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ChangSetting; //返回的参数

		public function TEvt_ChangSetting(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ChangSetting ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
