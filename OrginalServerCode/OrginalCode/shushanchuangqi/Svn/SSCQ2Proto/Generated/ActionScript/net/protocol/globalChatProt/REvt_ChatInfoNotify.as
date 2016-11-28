/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ChatInfoNotify.as
//  Purpose:      协议:全局聊天协议, 函数:聊天信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.events.Event;

	/**
	 * 函数ChatInfoNotify[聊天信息通知]的接收事件
	 */
	public final class REvt_ChatInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GlobalChatProt_ChatInfoNotify";
		public static const DATA_ERROR:String = "GlobalChatProt_ChatInfoNotify_Error";

		public var eChannelType:uint; //(枚举类型：EChannelType)通道类型
		public var rSenderInfo:SSenderInfo; //发送者信息
		public var strInfo:String; //聊天信息
		public var vecShowInfo:Vector.<SShowInfo>; //炫耀物品信息

		public function REvt_ChatInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ChatInfoNotify eChannelType={eChannelType} strInfo={strInfo}/>;
			if(rSenderInfo != null)
				topXml.appendChild(rSenderInfo.toXML("rSenderInfo"));
			if(vecShowInfo != null)
			{
				var vecShowInfoXml:XML = <Vec_SShowInfo _name_="vecShowInfo"/>;
				for each(var s2:SShowInfo in vecShowInfo)
					vecShowInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecShowInfoXml);
			}
			return topXml;
		}
	}
}
