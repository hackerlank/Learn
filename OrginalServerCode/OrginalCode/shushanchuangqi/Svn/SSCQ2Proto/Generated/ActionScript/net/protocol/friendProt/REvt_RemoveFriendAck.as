/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_RemoveFriendAck.as
//  Purpose:      协议:好友相关协议, 函数:删除好友/黑名单回应
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数RemoveFriendAck[删除好友/黑名单回应]的接收事件
	 */
	public final class REvt_RemoveFriendAck extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_RemoveFriendAck";
		public static const DATA_ERROR:String = "FriendProt_RemoveFriendAck_Error";

		public var eResult:uint; //(枚举类型：EFriendResult)删除好友的结果
		public var qwUserID:BigInteger; //(无符号64位整数)删除的好友帐号ID

		public function REvt_RemoveFriendAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_RemoveFriendAck eResult={eResult} qwUserID={qwUserID}/>;
			return topXml;
		}
	}
}
