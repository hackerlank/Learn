/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TeamBattleResult.as
//  Purpose:      协议:副本相关协议, 函数:队伍战斗结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数TeamBattleResult[队伍战斗结果]的接收事件
	 */
	public final class REvt_TeamBattleResult extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_TeamBattleResult";
		public static const DATA_ERROR:String = "DungeonProt_TeamBattleResult_Error";

		public var DgnType:uint; //(无符号16位整数)副本类型
		public var bySuc:uint; //(无符号8位整数)0,失败，1成功

		public function REvt_TeamBattleResult(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TeamBattleResult DgnType={DgnType} bySuc={bySuc}/>;
			return topXml;
		}
	}
}
