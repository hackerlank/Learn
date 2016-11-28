/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_THBattleResultNotify.as
//  Purpose:      协议:寻宝协议, 函数:战斗结果通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数THBattleResultNotify[战斗结果通知]的接收事件
	 */
	public final class REvt_THBattleResultNotify extends Event
	{
		public static const DATA_RECEIVE:String = "TreasureHuntProt_THBattleResultNotify";
		public static const DATA_ERROR:String = "TreasureHuntProt_THBattleResultNotify_Error";

		public var sBattleResult:STHBattleResult; //战斗结果

		public function REvt_THBattleResultNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_THBattleResultNotify/>;
			if(sBattleResult != null)
				topXml.appendChild(sBattleResult.toXML("sBattleResult"));
			return topXml;
		}
	}
}
