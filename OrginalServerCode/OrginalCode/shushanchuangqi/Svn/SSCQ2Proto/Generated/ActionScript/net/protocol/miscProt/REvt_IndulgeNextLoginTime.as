/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_IndulgeNextLoginTime.as
//  Purpose:      协议:不好归类的小协议, 函数:聊天信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数IndulgeNextLoginTime[聊天信息通知]的接收事件
	 */
	public final class REvt_IndulgeNextLoginTime extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_IndulgeNextLoginTime";
		public static const DATA_ERROR:String = "MiscProt_IndulgeNextLoginTime_Error";

		public var dwTime:uint; //(无符号32位整数)可以登陆时间(秒)

		public function REvt_IndulgeNextLoginTime(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_IndulgeNextLoginTime dwTime={dwTime}/>;
			return topXml;
		}
	}
}
