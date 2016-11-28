/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_KeepAlive.as
//  Purpose:      协议:GameServer的基本协议, 函数:心跳
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.events.Event;

	/**
	 * 函数KeepAlive[心跳]的返回事件
	 */
	public final class TEvt_KeepAlive extends Event
	{
		public static const DATA_RETURN:String = "GameSvrBasic_KeepAlive";
		public static const DATA_ERROR:String = "GameSvrBasic_KeepAlive_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_KeepAlive; //返回的参数

		public function TEvt_KeepAlive(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_KeepAlive ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
