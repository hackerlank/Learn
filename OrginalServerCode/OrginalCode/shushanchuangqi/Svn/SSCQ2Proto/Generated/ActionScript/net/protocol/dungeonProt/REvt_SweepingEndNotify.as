/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SweepingEndNotify.as
//  Purpose:      协议:副本相关协议, 函数:扫荡结束通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数SweepingEndNotify[扫荡结束通知]的接收事件
	 */
	public final class REvt_SweepingEndNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_SweepingEndNotify";
		public static const DATA_ERROR:String = "DungeonProt_SweepingEndNotify_Error";

		public var eResult:uint; //(枚举类型：EDungeonResult)服务器返回结果

		public function REvt_SweepingEndNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SweepingEndNotify eResult={eResult}/>;
			return topXml;
		}
	}
}
