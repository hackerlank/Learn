/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NoticeKicked.as
//  Purpose:      协议:竞技场协议, 函数:通告自己被踢
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数NoticeKicked[通告自己被踢]的接收事件
	 */
	public final class REvt_NoticeKicked extends Event
	{
		public static const DATA_RECEIVE:String = "TeamGS_NoticeKicked";
		public static const DATA_ERROR:String = "TeamGS_NoticeKicked_Error";

		public var DgnType:uint; //(无符号16位整数)副本类型

		public function REvt_NoticeKicked(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NoticeKicked DgnType={DgnType}/>;
			return topXml;
		}
	}
}
