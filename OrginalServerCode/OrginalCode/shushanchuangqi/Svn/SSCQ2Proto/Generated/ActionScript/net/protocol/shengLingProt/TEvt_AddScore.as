/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_AddScore.as
//  Purpose:      协议:圣陵协议, 函数:三消中积分累计
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;

	/**
	 * 函数AddScore[三消中积分累计]的返回事件
	 */
	public final class TEvt_AddScore extends Event
	{
		public static const DATA_RETURN:String = "ShengLingProt_AddScore";
		public static const DATA_ERROR:String = "ShengLingProt_AddScore_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_AddScore; //返回的参数

		public function TEvt_AddScore(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_AddScore ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
