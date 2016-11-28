/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetBeatyInfo.as
//  Purpose:      协议:美女系统, 函数:获取美女信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数GetBeatyInfo[获取美女信息]的返回事件
	 */
	public final class TEvt_GetBeatyInfo extends Event
	{
		public static const DATA_RETURN:String = "Beauty_GetBeatyInfo";
		public static const DATA_ERROR:String = "Beauty_GetBeatyInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetBeatyInfo; //返回的参数

		public function TEvt_GetBeatyInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetBeatyInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
