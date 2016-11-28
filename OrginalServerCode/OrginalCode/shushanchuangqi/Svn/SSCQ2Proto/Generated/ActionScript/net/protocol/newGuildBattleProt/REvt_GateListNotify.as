/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GateListNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:城门战列表通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数GateListNotify[城门战列表通知]的接收事件
	 */
	public final class REvt_GateListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_GateListNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GateListNotify_Error";

		public var vecInfo:Vector.<SPlayerPanelInfo>; //城门玩家列表信息通知

		public function REvt_GateListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GateListNotify/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SPlayerPanelInfo _name_="vecInfo"/>;
				for each(var s1:SPlayerPanelInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
