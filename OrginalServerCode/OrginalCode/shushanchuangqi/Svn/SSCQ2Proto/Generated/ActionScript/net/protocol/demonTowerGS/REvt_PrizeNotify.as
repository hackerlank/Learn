/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PrizeNotify.as
//  Purpose:      协议:锁妖塔, 函数:镇妖塔分身崩溃通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数PrizeNotify[镇妖塔分身崩溃通知]的接收事件
	 */
	public final class REvt_PrizeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_PrizeNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_PrizeNotify_Error";

		public var eDemonTowerPrize:uint; //(枚举类型：EDemonTowerPrize)魄奖励类型
		public var dwFloorID:uint; //(无符号32位整数)层数
		public var dwGuardPos:uint; //(无符号32位整数)镇守位置
		public var vecPrize:Vector.<MoneyInfo>; //魄奖励

		public function REvt_PrizeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PrizeNotify eDemonTowerPrize={eDemonTowerPrize} dwFloorID={dwFloorID} dwGuardPos={dwGuardPos}/>;
			if(vecPrize != null)
			{
				var vecPrizeXml:XML = <Vec_MoneyInfo _name_="vecPrize"/>;
				for each(var s1:MoneyInfo in vecPrize)
					vecPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecPrizeXml);
			}
			return topXml;
		}
	}
}
