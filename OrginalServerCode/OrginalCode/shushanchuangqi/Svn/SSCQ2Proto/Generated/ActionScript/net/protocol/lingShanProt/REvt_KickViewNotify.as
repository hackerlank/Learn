/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_KickViewNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:从观察者房间踢掉
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数KickViewNotify[从观察者房间踢掉]的接收事件
	 */
	public final class REvt_KickViewNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_KickViewNotify";
		public static const DATA_ERROR:String = "LingShanProt_KickViewNotify_Error";

		public var wRoomID:uint; //(无符号16位整数)进入的房间id

		public function REvt_KickViewNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_KickViewNotify wRoomID={wRoomID}/>;
			return topXml;
		}
	}
}
