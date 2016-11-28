/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SpotBattleNotify.as
//  Purpose:      协议:帮派相关协议, 函数:据点战斗通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数SpotBattleNotify[据点战斗通知]的接收事件
	 */
	public final class REvt_SpotBattleNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_SpotBattleNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_SpotBattleNotify_Error";

		public var eType:uint; //(枚举类型：EGBSpot)据点类型
		public var vecBattleData:Vector.<SBattleData>; //战报信息

		public function REvt_SpotBattleNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SpotBattleNotify eType={eType}/>;
			if(vecBattleData != null)
			{
				var vecBattleDataXml:XML = <Vec_SBattleData _name_="vecBattleData"/>;
				for each(var s1:SBattleData in vecBattleData)
					vecBattleDataXml.appendChild(s1.toXML());
				topXml.appendChild(vecBattleDataXml);
			}
			return topXml;
		}
	}
}
