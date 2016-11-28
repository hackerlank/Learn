/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_OnCountDown.as
//  Purpose:      协议:不好归类的小协议, 函数:通知倒计时
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数OnCountDown[通知倒计时]的接收事件
	 */
	public final class REvt_OnCountDown extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_OnCountDown";
		public static const DATA_ERROR:String = "MiscProt_OnCountDown_Error";

		public var dwTime:uint; //(无符号32位整数)活动倒计时时间

		public function REvt_OnCountDown(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_OnCountDown dwTime={dwTime}/>;
			return topXml;
		}
	}
}
