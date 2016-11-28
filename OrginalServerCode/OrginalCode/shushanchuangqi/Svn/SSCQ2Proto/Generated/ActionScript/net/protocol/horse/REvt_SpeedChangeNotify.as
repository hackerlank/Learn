/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SpeedChangeNotify.as
//  Purpose:      协议:坐骑, 函数:玩家速度通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数SpeedChangeNotify[玩家速度通知]的接收事件
	 */
	public final class REvt_SpeedChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Horse_SpeedChangeNotify";
		public static const DATA_ERROR:String = "Horse_SpeedChangeNotify_Error";

		public var dwSpeed:uint; //(无符号32位整数)玩家速度

		public function REvt_SpeedChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SpeedChangeNotify dwSpeed={dwSpeed}/>;
			return topXml;
		}
	}
}
