/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FindUserIDNameAck.as
//  Purpose:      协议:好友相关协议, 函数:角色查询
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数FindUserIDNameAck[角色查询]的接收事件
	 */
	public final class REvt_FindUserIDNameAck extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_FindUserIDNameAck";
		public static const DATA_ERROR:String = "FriendProt_FindUserIDNameAck_Error";

		public var eResult:uint; //(枚举类型：EFriendResult)查询返回
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var strRoleName:String; //主角色名
		public var wHeroID:uint; //(无符号16位整数)主将ID
		public var byLevel:uint; //(无符号8位整数)用户等级
		public var bOnlineStatus:Boolean; //在线状态

		public function REvt_FindUserIDNameAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FindUserIDNameAck eResult={eResult} qwUserID={qwUserID} strRoleName={strRoleName} wHeroID={wHeroID} byLevel={byLevel}
				 bOnlineStatus={bOnlineStatus}/>;
			return topXml;
		}
	}
}
