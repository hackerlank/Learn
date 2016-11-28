/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GateInfoNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:城门战广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数GateInfoNotify[城门战广播]的接收事件
	 */
	public final class REvt_GateInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_GateInfoNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GateInfoNotify_Error";

		public var sInfo:SMountainGateInfo; //城门信息

		public function REvt_GateInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GateInfoNotify/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
