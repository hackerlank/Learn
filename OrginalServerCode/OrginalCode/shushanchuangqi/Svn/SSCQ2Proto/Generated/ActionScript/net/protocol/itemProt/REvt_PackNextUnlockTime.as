/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PackNextUnlockTime.as
//  Purpose:      协议:道具相关协议, 函数:解锁格子还需要多少时间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数PackNextUnlockTime[解锁格子还需要多少时间]的接收事件
	 */
	public final class REvt_PackNextUnlockTime extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_PackNextUnlockTime";
		public static const DATA_ERROR:String = "ItemProt_PackNextUnlockTime_Error";

		public var dwTime:uint; //(无符号32位整数)时间，单位秒

		public function REvt_PackNextUnlockTime(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PackNextUnlockTime dwTime={dwTime}/>;
			return topXml;
		}
	}
}
