/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_LadderBattle.as
//  Purpose:      协议:竞技场协议, 函数:请求天梯挑战
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.events.Event;

	/**
	 * 函数LadderBattle[请求天梯挑战]的返回事件
	 */
	public final class TEvt_LadderBattle extends Event
	{
		public static const DATA_RETURN:String = "ArenaGS_LadderBattle";
		public static const DATA_ERROR:String = "ArenaGS_LadderBattle_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_LadderBattle; //返回的参数

		public function TEvt_LadderBattle(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_LadderBattle ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
