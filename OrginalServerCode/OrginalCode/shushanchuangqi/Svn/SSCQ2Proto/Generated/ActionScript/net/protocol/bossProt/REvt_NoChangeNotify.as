/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NoChangeNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:玩家名次变化通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数NoChangeNotify[玩家名次变化通知]的接收事件
	 */
	public final class REvt_NoChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_NoChangeNotify";
		public static const DATA_ERROR:String = "BossProt_NoChangeNotify_Error";

		public var dwNo:uint; //(无符号32位整数)玩家名次

		public function REvt_NoChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NoChangeNotify dwNo={dwNo}/>;
			return topXml;
		}
	}
}
