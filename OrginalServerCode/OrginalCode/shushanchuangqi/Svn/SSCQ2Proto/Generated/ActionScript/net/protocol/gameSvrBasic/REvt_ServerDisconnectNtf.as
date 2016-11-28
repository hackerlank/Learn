/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ServerDisconnectNtf.as
//  Purpose:      协议:GameServer的基本协议, 函数:服务器断开连接通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.events.Event;

	/**
	 * 函数ServerDisconnectNtf[服务器断开连接通知]的接收事件
	 */
	public final class REvt_ServerDisconnectNtf extends Event
	{
		public static const DATA_RECEIVE:String = "GameSvrBasic_ServerDisconnectNtf";
		public static const DATA_ERROR:String = "GameSvrBasic_ServerDisconnectNtf_Error";

		public var eBreakReason:uint; //(枚举类型：EBreakReason)断开连接原因

		public function REvt_ServerDisconnectNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ServerDisconnectNtf eBreakReason={eBreakReason}/>;
			return topXml;
		}
	}
}
