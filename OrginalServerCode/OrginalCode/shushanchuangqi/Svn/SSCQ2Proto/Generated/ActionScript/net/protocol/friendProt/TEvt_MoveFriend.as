/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_MoveFriend.as
//  Purpose:      协议:好友相关协议, 函数:移动好友
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;

	/**
	 * 函数MoveFriend[移动好友]的返回事件
	 */
	public final class TEvt_MoveFriend extends Event
	{
		public static const DATA_RETURN:String = "FriendProt_MoveFriend";
		public static const DATA_ERROR:String = "FriendProt_MoveFriend_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var origParam:SOrigParam_MoveFriend; //原来的参数
		public var retParam:SRetParam_MoveFriend; //返回的参数

		public function TEvt_MoveFriend(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_MoveFriend ret={ret}/>;
			if(origParam != null)
				topXml.appendChild(origParam.toXML("origParam"));
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
