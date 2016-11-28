/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_EnterDemonTowerNotify.as
//  Purpose:      协议:锁妖塔, 函数:玩家切层通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数EnterDemonTowerNotify[玩家切层通知]的接收事件
	 */
	public final class REvt_EnterDemonTowerNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_EnterDemonTowerNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_EnterDemonTowerNotify_Error";

		public var dwCurFloorID:uint; //(无符号32位整数)当前进入的层数

		public function REvt_EnterDemonTowerNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_EnterDemonTowerNotify dwCurFloorID={dwCurFloorID}/>;
			return topXml;
		}
	}
}
