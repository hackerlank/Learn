/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_LevelChangeNotify.as
//  Purpose:      协议:好友相关协议, 函数:等级变化通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数LevelChangeNotify[等级变化通知]的接收事件
	 */
	public final class REvt_LevelChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_LevelChangeNotify";
		public static const DATA_ERROR:String = "FriendProt_LevelChangeNotify_Error";

		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var byLevel:uint; //(无符号8位整数)当前等级

		public function REvt_LevelChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_LevelChangeNotify qwUserID={qwUserID} byLevel={byLevel}/>;
			return topXml;
		}
	}
}
