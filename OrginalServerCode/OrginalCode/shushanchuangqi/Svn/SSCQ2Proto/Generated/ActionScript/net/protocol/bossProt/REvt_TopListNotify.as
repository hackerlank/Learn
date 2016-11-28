/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TopListNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:排行榜通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数TopListNotify[排行榜通知]的接收事件
	 */
	public final class REvt_TopListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_TopListNotify";
		public static const DATA_ERROR:String = "BossProt_TopListNotify_Error";

		public var vecTopList:Vector.<SPlayerInfo>; //排行榜列表

		public function REvt_TopListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TopListNotify/>;
			if(vecTopList != null)
			{
				var vecTopListXml:XML = <Vec_SPlayerInfo _name_="vecTopList"/>;
				for each(var s1:SPlayerInfo in vecTopList)
					vecTopListXml.appendChild(s1.toXML());
				topXml.appendChild(vecTopListXml);
			}
			return topXml;
		}
	}
}
