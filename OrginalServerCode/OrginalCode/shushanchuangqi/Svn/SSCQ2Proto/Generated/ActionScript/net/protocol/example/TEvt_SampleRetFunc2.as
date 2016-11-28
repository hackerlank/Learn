/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_SampleRetFunc2.as
//  Purpose:      协议:通信协议示例, 函数:C->S有返回值的示例函数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.events.Event;

	/**
	 * 函数SampleRetFunc2[C->S有返回值的示例函数]的返回事件
	 */
	public final class TEvt_SampleRetFunc2 extends Event
	{
		public static const DATA_RETURN:String = "Example_SampleRetFunc2";
		public static const DATA_ERROR:String = "Example_SampleRetFunc2_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var origParam:SOrigParam_SampleRetFunc2; //原来的参数
		public var retParam:SRetParam_SampleRetFunc2; //返回的参数

		public function TEvt_SampleRetFunc2(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_SampleRetFunc2 ret={ret}/>;
			if(origParam != null)
				topXml.appendChild(origParam.toXML("origParam"));
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
