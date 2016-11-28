/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddFriendAck.as
//  Purpose:      协议:好友相关协议, 函数:增加好友/黑名单回应
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;

	/**
	 * 函数AddFriendAck[增加好友/黑名单回应]的接收事件
	 */
	public final class REvt_AddFriendAck extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_AddFriendAck";
		public static const DATA_ERROR:String = "FriendProt_AddFriendAck_Error";

		public var eResult:uint; //(枚举类型：EFriendResult)增加好友的结果
		public var strName:String; //名字 XXX: 如果主将改名需要修改此处
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别

		public function REvt_AddFriendAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddFriendAck eResult={eResult} strName={strName} eSex={eSex}/>;
			return topXml;
		}
	}
}
