/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReqSweepEnd.as
//  Purpose:      协议:守卫峨眉协议, 函数:请求获取守卫峨眉扫荡结束(放弃扫荡)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.events.Event;

	/**
	 * 函数ReqSweepEnd[请求获取守卫峨眉扫荡结束(放弃扫荡)]的返回事件
	 */
	public final class TEvt_ReqSweepEnd extends Event
	{
		public static const DATA_RETURN:String = "GuardEMeiProt_ReqSweepEnd";
		public static const DATA_ERROR:String = "GuardEMeiProt_ReqSweepEnd_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReqSweepEnd; //返回的参数

		public function TEvt_ReqSweepEnd(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReqSweepEnd ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
