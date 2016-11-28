/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TopKiller.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:广播连杀王玩家信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数TopKiller[广播连杀王玩家信息]的接收事件
	 */
	public final class REvt_TopKiller extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_TopKiller";
		public static const DATA_ERROR:String = "ShushanBattleProt_TopKiller_Error";

		public var strName:String; //玩家名字
		public var byTopStreak:uint; //(无符号8位整数)最高连杀数

		public function REvt_TopKiller(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TopKiller strName={strName} byTopStreak={byTopStreak}/>;
			return topXml;
		}
	}
}
