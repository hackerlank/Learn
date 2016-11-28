/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DemonTowerAtkCDNotify.as
//  Purpose:      协议:锁妖塔, 函数:锁妖塔镇守攻击cd
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数DemonTowerAtkCDNotify[锁妖塔镇守攻击cd]的接收事件
	 */
	public final class REvt_DemonTowerAtkCDNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_DemonTowerAtkCDNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_DemonTowerAtkCDNotify_Error";

		public var dwGuardNextAttackTime:uint; //(无符号32位整数)锁妖塔可攻击最早时间

		public function REvt_DemonTowerAtkCDNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DemonTowerAtkCDNotify dwGuardNextAttackTime={dwGuardNextAttackTime}/>;
			return topXml;
		}
	}
}
