/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DemonTowerPlayerNotify.as
//  Purpose:      协议:锁妖塔, 函数:镇妖塔玩家信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数DemonTowerPlayerNotify[镇妖塔玩家信息]的接收事件
	 */
	public final class REvt_DemonTowerPlayerNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_DemonTowerPlayerNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_DemonTowerPlayerNotify_Error";

		public var oDemonTowerPlayerInfo:SDemonTowerPlayer; //镇妖塔玩家信息

		public function REvt_DemonTowerPlayerNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DemonTowerPlayerNotify/>;
			if(oDemonTowerPlayerInfo != null)
				topXml.appendChild(oDemonTowerPlayerInfo.toXML("oDemonTowerPlayerInfo"));
			return topXml;
		}
	}
}
