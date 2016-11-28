/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuardSucessNotify.as
//  Purpose:      协议:锁妖塔, 函数:镇守锁妖塔通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数GuardSucessNotify[镇守锁妖塔通知]的接收事件
	 */
	public final class REvt_GuardSucessNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_GuardSucessNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_GuardSucessNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数
		public var dwGuardPos:uint; //(无符号32位整数)镇守位置

		public function REvt_GuardSucessNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuardSucessNotify dwFloorID={dwFloorID} dwGuardPos={dwGuardPos}/>;
			return topXml;
		}
	}
}
