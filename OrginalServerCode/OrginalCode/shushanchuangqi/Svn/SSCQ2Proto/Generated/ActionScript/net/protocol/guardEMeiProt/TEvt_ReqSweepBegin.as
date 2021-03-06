/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReqSweepBegin.as
//  Purpose:      协议:守卫峨眉协议, 函数:请求获取守卫峨眉扫荡开始
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.events.Event;

	/**
	 * 函数ReqSweepBegin[请求获取守卫峨眉扫荡开始]的返回事件
	 */
	public final class TEvt_ReqSweepBegin extends Event
	{
		public static const DATA_RETURN:String = "GuardEMeiProt_ReqSweepBegin";
		public static const DATA_ERROR:String = "GuardEMeiProt_ReqSweepBegin_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReqSweepBegin; //返回的参数

		public function TEvt_ReqSweepBegin(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReqSweepBegin ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
