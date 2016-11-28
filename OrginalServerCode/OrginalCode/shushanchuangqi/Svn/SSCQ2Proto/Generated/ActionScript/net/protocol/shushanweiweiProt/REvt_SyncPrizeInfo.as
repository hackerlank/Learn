/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncPrizeInfo.as
//  Purpose:      协议:蜀山微微协议, 函数:同步玩家奖励信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
{
	import flash.events.Event;

	/**
	 * 函数SyncPrizeInfo[同步玩家奖励信息]的接收事件
	 */
	public final class REvt_SyncPrizeInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanweiweiProt_SyncPrizeInfo";
		public static const DATA_ERROR:String = "ShushanweiweiProt_SyncPrizeInfo_Error";

		public var vecResult:Vector.<SPrizeInfo>; //奖励结果

		public function REvt_SyncPrizeInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncPrizeInfo/>;
			if(vecResult != null)
			{
				var vecResultXml:XML = <Vec_SPrizeInfo _name_="vecResult"/>;
				for each(var s1:SPrizeInfo in vecResult)
					vecResultXml.appendChild(s1.toXML());
				topXml.appendChild(vecResultXml);
			}
			return topXml;
		}
	}
}
