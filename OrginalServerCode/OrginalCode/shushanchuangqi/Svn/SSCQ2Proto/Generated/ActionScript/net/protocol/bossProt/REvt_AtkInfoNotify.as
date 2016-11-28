/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AtkInfoNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:伤害boss信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数AtkInfoNotify[伤害boss信息]的接收事件
	 */
	public final class REvt_AtkInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_AtkInfoNotify";
		public static const DATA_ERROR:String = "BossProt_AtkInfoNotify_Error";

		public var dwDamage:uint; //(无符号32位整数)本次伤害
		public var dwExp:uint; //(无符号32位整数)本次活动经验值
		public var dwTotalDamage:uint; //(无符号32位整数)总伤害
		public var dwBossMaxHp:uint; //(无符号32位整数)boss最大血量

		public function REvt_AtkInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AtkInfoNotify dwDamage={dwDamage} dwExp={dwExp} dwTotalDamage={dwTotalDamage} dwBossMaxHp={dwBossMaxHp}/>;
			return topXml;
		}
	}
}
