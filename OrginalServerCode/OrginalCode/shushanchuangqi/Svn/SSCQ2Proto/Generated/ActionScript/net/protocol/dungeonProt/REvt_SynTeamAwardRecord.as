/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SynTeamAwardRecord.as
//  Purpose:      协议:副本相关协议, 函数:同步领奖记录
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数SynTeamAwardRecord[同步领奖记录]的接收事件
	 */
	public final class REvt_SynTeamAwardRecord extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_SynTeamAwardRecord";
		public static const DATA_ERROR:String = "DungeonProt_SynTeamAwardRecord_Error";

		public var stAward:TeamAwardAllRecord; //同步数据

		public function REvt_SynTeamAwardRecord(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SynTeamAwardRecord/>;
			if(stAward != null)
				topXml.appendChild(stAward.toXML("stAward"));
			return topXml;
		}
	}
}
