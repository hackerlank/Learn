/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PassDemonTowerNotify.as
//  Purpose:      协议:锁妖塔, 函数:锁妖塔过关通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数PassDemonTowerNotify[锁妖塔过关通知]的接收事件
	 */
	public final class REvt_PassDemonTowerNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_PassDemonTowerNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_PassDemonTowerNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)锁妖塔过关层数

		public function REvt_PassDemonTowerNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PassDemonTowerNotify dwFloorID={dwFloorID}/>;
			return topXml;
		}
	}
}
