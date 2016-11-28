/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FloorPassNotify.as
//  Purpose:      协议:锁妖塔, 函数:通关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数FloorPassNotify[通关协议]的接收事件
	 */
	public final class REvt_FloorPassNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_FloorPassNotify";
		public static const DATA_ERROR:String = "DemonTower_FloorPassNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)通关层数

		public function REvt_FloorPassNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FloorPassNotify dwFloorID={dwFloorID}/>;
			return topXml;
		}
	}
}
