/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncLotteryInfo.as
//  Purpose:      协议:不好归类的小协议, 函数:通知宝箱活动剩余轮次
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数SyncLotteryInfo[通知宝箱活动剩余轮次]的接收事件
	 */
	public final class REvt_SyncLotteryInfo extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_SyncLotteryInfo";
		public static const DATA_ERROR:String = "MiscProt_SyncLotteryInfo_Error";

		public var dwLottery:uint; //(无符号32位整数)抽奖券
		public var vecTotalInfo:Vector.<SLotteryInfo>; //总的抽奖信息
		public var vecSelfInfo:Vector.<SLotteryInfo>; //自己抽奖信息

		public function REvt_SyncLotteryInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncLotteryInfo dwLottery={dwLottery}/>;
			if(vecTotalInfo != null)
			{
				var vecTotalInfoXml:XML = <Vec_SLotteryInfo _name_="vecTotalInfo"/>;
				for each(var s1:SLotteryInfo in vecTotalInfo)
					vecTotalInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTotalInfoXml);
			}
			if(vecSelfInfo != null)
			{
				var vecSelfInfoXml:XML = <Vec_SLotteryInfo _name_="vecSelfInfo"/>;
				for each(var s2:SLotteryInfo in vecSelfInfo)
					vecSelfInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecSelfInfoXml);
			}
			return topXml;
		}
	}
}
