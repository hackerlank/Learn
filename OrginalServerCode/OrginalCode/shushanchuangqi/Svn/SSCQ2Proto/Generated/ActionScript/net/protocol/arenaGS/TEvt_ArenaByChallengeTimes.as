/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ArenaByChallengeTimes.as
//  Purpose:      协议:竞技场协议, 函数:请求购买挑战次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.events.Event;

	/**
	 * 函数ArenaByChallengeTimes[请求购买挑战次数]的返回事件
	 */
	public final class TEvt_ArenaByChallengeTimes extends Event
	{
		public static const DATA_RETURN:String = "ArenaGS_ArenaByChallengeTimes";
		public static const DATA_ERROR:String = "ArenaGS_ArenaByChallengeTimes_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ArenaByChallengeTimes; //返回的参数

		public function TEvt_ArenaByChallengeTimes(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ArenaByChallengeTimes ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
