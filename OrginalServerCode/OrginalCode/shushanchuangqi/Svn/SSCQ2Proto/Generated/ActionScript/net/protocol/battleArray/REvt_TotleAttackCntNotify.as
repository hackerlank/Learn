/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TotleAttackCntNotify.as
//  Purpose:      协议:破阵, 函数:总攻击次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数TotleAttackCntNotify[总攻击次数]的接收事件
	 */
	public final class REvt_TotleAttackCntNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BattleArray_TotleAttackCntNotify";
		public static const DATA_ERROR:String = "BattleArray_TotleAttackCntNotify_Error";

		public var dwAttackCnt:uint; //(无符号32位整数)总攻击次数
		public var dwBuyCnt:uint; //(无符号32位整数)剩余购买数

		public function REvt_TotleAttackCntNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TotleAttackCntNotify dwAttackCnt={dwAttackCnt} dwBuyCnt={dwBuyCnt}/>;
			return topXml;
		}
	}
}
