/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_YellowDiamondNotify.as
//  Purpose:      协议:好友相关协议, 函数:QQ黄钻好友通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数YellowDiamondNotify[QQ黄钻好友通知]的接收事件
	 */
	public final class REvt_YellowDiamondNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_YellowDiamondNotify";
		public static const DATA_ERROR:String = "FriendProt_YellowDiamondNotify_Error";

		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var bYearlyPay:Boolean; //是否年费黄钻

		public function REvt_YellowDiamondNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_YellowDiamondNotify qwUserID={qwUserID} byLevel={byLevel} bYearlyPay={bYearlyPay}/>;
			return topXml;
		}
	}
}
