/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_OpenAllSystem.as
//  Purpose:      协议:GameServer的基本协议, 函数:打开所有功能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.events.Event;

	/**
	 * 函数OpenAllSystem[打开所有功能]的接收事件
	 */
	public final class REvt_OpenAllSystem extends Event
	{
		public static const DATA_RECEIVE:String = "GameSvrBasic_OpenAllSystem";
		public static const DATA_ERROR:String = "GameSvrBasic_OpenAllSystem_Error";

		public var bOpen:Boolean; //是否打开

		public function REvt_OpenAllSystem(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_OpenAllSystem bOpen={bOpen}/>;
			return topXml;
		}
	}
}
