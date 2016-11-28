/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SBattleArrayAttackCntNotify.as
//  Purpose:      协议:破阵, 函数:攻击阵图信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数SBattleArrayAttackCntNotify[攻击阵图信息]的接收事件
	 */
	public final class REvt_SBattleArrayAttackCntNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BattleArray_SBattleArrayAttackCntNotify";
		public static const DATA_ERROR:String = "BattleArray_SBattleArrayAttackCntNotify_Error";

		public var oBattleArrayAttackCnt:SBattleArrayAttackCnt; //攻击阵图信息

		public function REvt_SBattleArrayAttackCntNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SBattleArrayAttackCntNotify/>;
			if(oBattleArrayAttackCnt != null)
				topXml.appendChild(oBattleArrayAttackCnt.toXML("oBattleArrayAttackCnt"));
			return topXml;
		}
	}
}
