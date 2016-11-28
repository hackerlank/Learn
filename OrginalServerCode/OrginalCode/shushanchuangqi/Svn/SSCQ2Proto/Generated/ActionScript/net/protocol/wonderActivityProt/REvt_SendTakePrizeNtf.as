/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendTakePrizeNtf.as
//  Purpose:      协议:精彩活动, 函数:领奖状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.events.Event;

	/**
	 * 函数SendTakePrizeNtf[领奖状态通知]的接收事件
	 */
	public final class REvt_SendTakePrizeNtf extends Event
	{
		public static const DATA_RECEIVE:String = "WonderActivityProt_SendTakePrizeNtf";
		public static const DATA_ERROR:String = "WonderActivityProt_SendTakePrizeNtf_Error";

		public var wActID:uint; //(无符号16位整数)活动ID
		public var wCond:uint; //(无符号32位整数)条件ID
		public var eRet:uint; //(枚举类型：EGainResult)状态

		public function REvt_SendTakePrizeNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendTakePrizeNtf wActID={wActID} wCond={wCond} eRet={eRet}/>;
			return topXml;
		}
	}
}
