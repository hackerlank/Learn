/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_KickPlayerNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:从房间离开
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数KickPlayerNotify[从房间离开]的接收事件
	 */
	public final class REvt_KickPlayerNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_KickPlayerNotify";
		public static const DATA_ERROR:String = "LingShanProt_KickPlayerNotify_Error";

		public var qwRoleID:BigInteger; //(无符号64位整数)进入的房间id
		public var wRoomID:uint; //(无符号16位整数)进入的房间id

		public function REvt_KickPlayerNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_KickPlayerNotify qwRoleID={qwRoleID} wRoomID={wRoomID}/>;
			return topXml;
		}
	}
}
