/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GateAttackPlayer.as
//  Purpose:      协议:新帮派战相关协议, 函数:城门战攻击玩家/城门
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数GateAttackPlayer[城门战攻击玩家/城门]的返回事件
	 */
	public final class TEvt_GateAttackPlayer extends Event
	{
		public static const DATA_RETURN:String = "NewGuildBattleProt_GateAttackPlayer";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GateAttackPlayer_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GateAttackPlayer; //返回的参数

		public function TEvt_GateAttackPlayer(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GateAttackPlayer ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
