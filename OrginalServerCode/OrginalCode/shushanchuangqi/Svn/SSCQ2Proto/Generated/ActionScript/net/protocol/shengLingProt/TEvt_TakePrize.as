/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_TakePrize.as
//  Purpose:      协议:圣陵协议, 函数:玩家领奖
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;

	/**
	 * 函数TakePrize[玩家领奖]的返回事件
	 */
	public final class TEvt_TakePrize extends Event
	{
		public static const DATA_RETURN:String = "ShengLingProt_TakePrize";
		public static const DATA_ERROR:String = "ShengLingProt_TakePrize_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_TakePrize; //返回的参数

		public function TEvt_TakePrize(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_TakePrize ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
