/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GetActionBuffNotify.as
//  Purpose:      协议:不好归类的小协议, 函数:Buffer中的体力
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数GetActionBuffNotify[Buffer中的体力]的接收事件
	 */
	public final class REvt_GetActionBuffNotify extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_GetActionBuffNotify";
		public static const DATA_ERROR:String = "MiscProt_GetActionBuffNotify_Error";

		public var dwValue:uint; //(无符号32位整数)Buffer中的体力
		public var TakeTime:uint; //(无符号32位整数)最近领取时间

		public function REvt_GetActionBuffNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GetActionBuffNotify dwValue={dwValue} TakeTime={TakeTime}/>;
			return topXml;
		}
	}
}
