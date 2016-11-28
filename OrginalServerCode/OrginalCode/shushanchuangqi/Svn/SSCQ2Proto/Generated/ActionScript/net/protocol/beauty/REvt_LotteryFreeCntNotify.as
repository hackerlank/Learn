/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_LotteryFreeCntNotify.as
//  Purpose:      协议:美女系统, 函数:当前已免费抽奖次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数LotteryFreeCntNotify[当前已免费抽奖次数]的接收事件
	 */
	public final class REvt_LotteryFreeCntNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Beauty_LotteryFreeCntNotify";
		public static const DATA_ERROR:String = "Beauty_LotteryFreeCntNotify_Error";

		public var byFreeCnt:uint; //(无符号8位整数)已免费抽奖次数

		public function REvt_LotteryFreeCntNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_LotteryFreeCntNotify byFreeCnt={byFreeCnt}/>;
			return topXml;
		}
	}
}
