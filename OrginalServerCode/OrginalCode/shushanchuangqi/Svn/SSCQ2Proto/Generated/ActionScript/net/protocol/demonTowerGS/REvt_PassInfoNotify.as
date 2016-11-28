/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PassInfoNotify.as
//  Purpose:      协议:锁妖塔, 函数:过关信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数PassInfoNotify[过关信息]的接收事件
	 */
	public final class REvt_PassInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_PassInfoNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_PassInfoNotify_Error";

		public var wFloorID:uint; //(无符号16位整数)通关层
		public var vecMinRound:Vector.<SDemonTowerKillMonster>; //最快通关
		public var vecMinBattlePoint:Vector.<SDemonTowerKillMonster>; //最小战斗力通关

		public function REvt_PassInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PassInfoNotify wFloorID={wFloorID}/>;
			if(vecMinRound != null)
			{
				var vecMinRoundXml:XML = <Vec_SDemonTowerKillMonster _name_="vecMinRound"/>;
				for each(var s1:SDemonTowerKillMonster in vecMinRound)
					vecMinRoundXml.appendChild(s1.toXML());
				topXml.appendChild(vecMinRoundXml);
			}
			if(vecMinBattlePoint != null)
			{
				var vecMinBattlePointXml:XML = <Vec_SDemonTowerKillMonster _name_="vecMinBattlePoint"/>;
				for each(var s2:SDemonTowerKillMonster in vecMinBattlePoint)
					vecMinBattlePointXml.appendChild(s2.toXML());
				topXml.appendChild(vecMinBattlePointXml);
			}
			return topXml;
		}
	}
}
