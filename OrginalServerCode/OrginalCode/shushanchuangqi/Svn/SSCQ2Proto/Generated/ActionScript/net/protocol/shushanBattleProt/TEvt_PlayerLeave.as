/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_PlayerLeave.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:退出蜀山论剑活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerLeave[退出蜀山论剑活动]的返回事件
	 */
	public final class TEvt_PlayerLeave extends Event
	{
		public static const DATA_RETURN:String = "ShushanBattleProt_PlayerLeave";
		public static const DATA_ERROR:String = "ShushanBattleProt_PlayerLeave_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_PlayerLeave; //返回的参数

		public function TEvt_PlayerLeave(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_PlayerLeave ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
