/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GMCommandAck.as
//  Purpose:      协议:GameServer的基本协议, 函数:GM指令结果返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.events.Event;

	/**
	 * 函数GMCommandAck[GM指令结果返回]的接收事件
	 */
	public final class REvt_GMCommandAck extends Event
	{
		public static const DATA_RECEIVE:String = "GameSvrBasic_GMCommandAck";
		public static const DATA_ERROR:String = "GameSvrBasic_GMCommandAck_Error";

		public var strResult:String; //指令结果

		public function REvt_GMCommandAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GMCommandAck strResult={strResult}/>;
			return topXml;
		}
	}
}
