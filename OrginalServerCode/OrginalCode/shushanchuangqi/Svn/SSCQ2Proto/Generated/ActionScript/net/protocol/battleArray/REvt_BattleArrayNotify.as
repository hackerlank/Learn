/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleArrayNotify.as
//  Purpose:      协议:破阵, 函数:阵信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数BattleArrayNotify[阵信息更新]的接收事件
	 */
	public final class REvt_BattleArrayNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BattleArray_BattleArrayNotify";
		public static const DATA_ERROR:String = "BattleArray_BattleArrayNotify_Error";

		public var oBattleArray:SBattleArray; //阵信息

		public function REvt_BattleArrayNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleArrayNotify/>;
			if(oBattleArray != null)
				topXml.appendChild(oBattleArray.toXML("oBattleArray"));
			return topXml;
		}
	}
}
