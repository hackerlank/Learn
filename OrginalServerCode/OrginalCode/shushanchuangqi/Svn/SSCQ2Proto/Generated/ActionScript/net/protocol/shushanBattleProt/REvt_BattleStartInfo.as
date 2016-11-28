/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleStartInfo.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:蜀山论剑准备/开始/结束信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数BattleStartInfo[蜀山论剑准备/开始/结束信息]的接收事件
	 */
	public final class REvt_BattleStartInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_BattleStartInfo";
		public static const DATA_ERROR:String = "ShushanBattleProt_BattleStartInfo_Error";

		public var byStatus:uint; //(无符号8位整数)状态=>0:准备 1:开始 2:结束
		public var dwTimeLeft:uint; //(无符号32位整数)byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间

		public function REvt_BattleStartInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleStartInfo byStatus={byStatus} dwTimeLeft={dwTimeLeft}/>;
			return topXml;
		}
	}
}
