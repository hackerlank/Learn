/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_THLootNotify.as
//  Purpose:      协议:寻宝协议, 函数:寻宝掉落通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数THLootNotify[寻宝掉落通知]的接收事件
	 */
	public final class REvt_THLootNotify extends Event
	{
		public static const DATA_RECEIVE:String = "TreasureHuntProt_THLootNotify";
		public static const DATA_ERROR:String = "TreasureHuntProt_THLootNotify_Error";

		public var vecTHAwardInfo:Vector.<STHAwardInfo>; //掉落

		public function REvt_THLootNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_THLootNotify/>;
			if(vecTHAwardInfo != null)
			{
				var vecTHAwardInfoXml:XML = <Vec_STHAwardInfo _name_="vecTHAwardInfo"/>;
				for each(var s1:STHAwardInfo in vecTHAwardInfo)
					vecTHAwardInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTHAwardInfoXml);
			}
			return topXml;
		}
	}
}
