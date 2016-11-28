/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BubbleNotify.as
//  Purpose:      协议:聊天协议, 函数:气泡提示信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.SBubbleInfo;

	/**
	 * 函数BubbleNotify[气泡提示信息]的接收事件
	 */
	public final class REvt_BubbleNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ChatProt_BubbleNotify";
		public static const DATA_ERROR:String = "ChatProt_BubbleNotify_Error";

		public var vecBubbleInfo:Vector.<SBubbleInfo>; //气泡列表信息

		public function REvt_BubbleNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BubbleNotify/>;
			if(vecBubbleInfo != null)
			{
				var vecBubbleInfoXml:XML = <Vec_SBubbleInfo _name_="vecBubbleInfo"/>;
				for each(var s1:SBubbleInfo in vecBubbleInfo)
					vecBubbleInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBubbleInfoXml);
			}
			return topXml;
		}
	}
}
