/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DemonTowerResetNotify.as
//  Purpose:      协议:锁妖塔, 函数:19点重置奖励通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数DemonTowerResetNotify[19点重置奖励通知]的接收事件
	 */
	public final class REvt_DemonTowerResetNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_DemonTowerResetNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_DemonTowerResetNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数
		public var dwGuardPos:uint; //(无符号32位整数)镇守位置
		public var vecSoulPrize:Vector.<MoneyInfo>; //获得的魄奖励

		public function REvt_DemonTowerResetNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DemonTowerResetNotify dwFloorID={dwFloorID} dwGuardPos={dwGuardPos}/>;
			if(vecSoulPrize != null)
			{
				var vecSoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecSoulPrize"/>;
				for each(var s1:MoneyInfo in vecSoulPrize)
					vecSoulPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecSoulPrizeXml);
			}
			return topXml;
		}
	}
}
