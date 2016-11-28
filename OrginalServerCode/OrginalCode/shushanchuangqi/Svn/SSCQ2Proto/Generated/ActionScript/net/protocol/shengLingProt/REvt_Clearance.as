/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_Clearance.as
//  Purpose:      协议:圣陵协议, 函数:玩家通关
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;

	/**
	 * 函数Clearance[玩家通关]的接收事件
	 */
	public final class REvt_Clearance extends Event
	{
		public static const DATA_RECEIVE:String = "ShengLingProt_Clearance";
		public static const DATA_ERROR:String = "ShengLingProt_Clearance_Error";


		public function REvt_Clearance(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_Clearance/>;
			return topXml;
		}
	}
}
