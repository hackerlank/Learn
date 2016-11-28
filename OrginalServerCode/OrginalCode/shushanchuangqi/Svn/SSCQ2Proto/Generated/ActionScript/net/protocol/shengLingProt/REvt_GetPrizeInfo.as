/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GetPrizeInfo.as
//  Purpose:      协议:圣陵协议, 函数:获得奖励道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;
	import net.protocol.itemProt.SItemGenInfo;

	/**
	 * 函数GetPrizeInfo[获得奖励道具]的接收事件
	 */
	public final class REvt_GetPrizeInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShengLingProt_GetPrizeInfo";
		public static const DATA_ERROR:String = "ShengLingProt_GetPrizeInfo_Error";

		public var vecItem:Vector.<SItemGenInfo>; //玩家物品

		public function REvt_GetPrizeInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GetPrizeInfo/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s1:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}
	}
}
