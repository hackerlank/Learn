/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AttackChangedNotify.as
//  Purpose:      协议:锁妖塔, 函数:被攻击通知(收到通知后拉取被攻击列表)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数AttackChangedNotify[被攻击通知(收到通知后拉取被攻击列表)]的接收事件
	 */
	public final class REvt_AttackChangedNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_AttackChangedNotify";
		public static const DATA_ERROR:String = "DemonTower_AttackChangedNotify_Error";


		public function REvt_AttackChangedNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AttackChangedNotify/>;
			return topXml;
		}
	}
}
