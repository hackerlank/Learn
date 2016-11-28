/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GetBattleArrayNotify.as
//  Purpose:      协议:破阵, 函数:全部阵信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数GetBattleArrayNotify[全部阵信息]的接收事件
	 */
	public final class REvt_GetBattleArrayNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BattleArray_GetBattleArrayNotify";
		public static const DATA_ERROR:String = "BattleArray_GetBattleArrayNotify_Error";

		public var vecBattleArray:Vector.<SBattleArray>; //阵信息列表
		public var vecBattleArrayAttackCnt:Vector.<SBattleArrayAttackCnt>; //攻击阵图信息
		public var dwBuyCnt:uint; //(无符号32位整数)可用的次数
		public var dwDayBuyCnt:uint; //(无符号32位整数)当天购买次数

		public function REvt_GetBattleArrayNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GetBattleArrayNotify dwBuyCnt={dwBuyCnt} dwDayBuyCnt={dwDayBuyCnt}/>;
			if(vecBattleArray != null)
			{
				var vecBattleArrayXml:XML = <Vec_SBattleArray _name_="vecBattleArray"/>;
				for each(var s1:SBattleArray in vecBattleArray)
					vecBattleArrayXml.appendChild(s1.toXML());
				topXml.appendChild(vecBattleArrayXml);
			}
			if(vecBattleArrayAttackCnt != null)
			{
				var vecBattleArrayAttackCntXml:XML = <Vec_SBattleArrayAttackCnt _name_="vecBattleArrayAttackCnt"/>;
				for each(var s2:SBattleArrayAttackCnt in vecBattleArrayAttackCnt)
					vecBattleArrayAttackCntXml.appendChild(s2.toXML());
				topXml.appendChild(vecBattleArrayAttackCntXml);
			}
			return topXml;
		}
	}
}
