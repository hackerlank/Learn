/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_PlayerEnter.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:参加蜀山论剑活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerEnter[参加蜀山论剑活动]的返回事件
	 */
	public final class TEvt_PlayerEnter extends Event
	{
		public static const DATA_RETURN:String = "ShushanBattleProt_PlayerEnter";
		public static const DATA_ERROR:String = "ShushanBattleProt_PlayerEnter_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_PlayerEnter; //返回的参数

		public function TEvt_PlayerEnter(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_PlayerEnter ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}