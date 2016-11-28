/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateSevenConsumeAct.as
//  Purpose:      协议:精彩活动, 函数:更新七日消费活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateSevenConsumeAct[更新七日消费活动信息]的接收事件
	 */
	public final class REvt_UpdateSevenConsumeAct extends Event
	{
		public static const DATA_RECEIVE:String = "WonderActivityProt_UpdateSevenConsumeAct";
		public static const DATA_ERROR:String = "WonderActivityProt_UpdateSevenConsumeAct_Error";

		public var oSevenConsumeAct:SSevenConsumeAct; //七日消费活动信息

		public function REvt_UpdateSevenConsumeAct(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateSevenConsumeAct/>;
			if(oSevenConsumeAct != null)
				topXml.appendChild(oSevenConsumeAct.toXML("oSevenConsumeAct"));
			return topXml;
		}
	}
}
