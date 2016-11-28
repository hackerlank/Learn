/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ReliveTimeNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:玩家复活时间通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数ReliveTimeNotify[玩家复活时间通知]的接收事件
	 */
	public final class REvt_ReliveTimeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_ReliveTimeNotify";
		public static const DATA_ERROR:String = "BossProt_ReliveTimeNotify_Error";

		public var dwReliveTime:uint; //(无符号32位整数)复活时间

		public function REvt_ReliveTimeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ReliveTimeNotify dwReliveTime={dwReliveTime}/>;
			return topXml;
		}
	}
}
