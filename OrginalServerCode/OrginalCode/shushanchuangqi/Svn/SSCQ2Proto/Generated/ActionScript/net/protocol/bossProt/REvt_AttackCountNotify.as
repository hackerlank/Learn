/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AttackCountNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:玩家直接攻击次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数AttackCountNotify[玩家直接攻击次数]的接收事件
	 */
	public final class REvt_AttackCountNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_AttackCountNotify";
		public static const DATA_ERROR:String = "BossProt_AttackCountNotify_Error";

		public var dwAttackCount:uint; //(无符号16位整数)玩家直接攻击次数

		public function REvt_AttackCountNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AttackCountNotify dwAttackCount={dwAttackCount}/>;
			return topXml;
		}
	}
}
