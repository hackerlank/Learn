/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_WhisperSuccessNotify.as
//  Purpose:      协议:好友相关协议, 函数:私聊成功通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数WhisperSuccessNotify[私聊成功通知]的接收事件
	 */
	public final class REvt_WhisperSuccessNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_WhisperSuccessNotify";
		public static const DATA_ERROR:String = "FriendProt_WhisperSuccessNotify_Error";

		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strBaseInfo:String; //聊天基本信息

		public function REvt_WhisperSuccessNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_WhisperSuccessNotify qwUserID={qwUserID} strBaseInfo={strBaseInfo}/>;
			return topXml;
		}
	}
}
