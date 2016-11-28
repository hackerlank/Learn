/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_WhisperErrorNotify.as
//  Purpose:      协议:全局聊天协议, 函数:私聊错误通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数WhisperErrorNotify[私聊错误通知]的接收事件
	 */
	public final class REvt_WhisperErrorNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GlobalChatProt_WhisperErrorNotify";
		public static const DATA_ERROR:String = "GlobalChatProt_WhisperErrorNotify_Error";

		public var eErrType:uint; //(枚举类型：EWhisperErrorType)错误类型
		public var qwUsrID:BigInteger; //(无符号64位整数)帐号ID

		public function REvt_WhisperErrorNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_WhisperErrorNotify eErrType={eErrType} qwUsrID={qwUsrID}/>;
			return topXml;
		}
	}
}
