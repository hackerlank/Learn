/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ChatNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:聊天
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数ChatNotify[聊天]的接收事件
	 */
	public final class REvt_ChatNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_ChatNotify";
		public static const DATA_ERROR:String = "LingShanProt_ChatNotify_Error";

		public var qwRoleID:BigInteger; //(无符号64位整数)结果
		public var strChatMsg:String; //聊天内容
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_ChatNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ChatNotify qwRoleID={qwRoleID} strChatMsg={strChatMsg} wRoomID={wRoomID}/>;
			return topXml;
		}
	}
}
