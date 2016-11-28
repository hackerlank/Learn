/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AskAddFriend.as
//  Purpose:      协议:好友相关协议, 函数:询问增加好友
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数AskAddFriend[询问增加好友]的接收事件
	 */
	public final class REvt_AskAddFriend extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_AskAddFriend";
		public static const DATA_ERROR:String = "FriendProt_AskAddFriend_Error";

		public var strRoleName:String; //角色名字
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var wFighterID:uint; //(无符号16位整数)主将ID
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var byLevel:uint; //(无符号8位整数)等级

		public function REvt_AskAddFriend(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AskAddFriend strRoleName={strRoleName} qwUserID={qwUserID} wFighterID={wFighterID} eSex={eSex} byLevel={byLevel}/>;
			return topXml;
		}
	}
}
