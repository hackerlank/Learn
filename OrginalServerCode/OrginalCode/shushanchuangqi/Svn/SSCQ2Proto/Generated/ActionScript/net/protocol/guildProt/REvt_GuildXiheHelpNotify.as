/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildXiheHelpNotify.as
//  Purpose:      协议:帮派相关协议, 函数:更新玩家羲和神车帮助信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildXiheHelpNotify[更新玩家羲和神车帮助信息]的接收事件
	 */
	public final class REvt_GuildXiheHelpNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildXiheHelpNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildXiheHelpNotify_Error";

		public var byType:uint; //(无符号8位整数)0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
		public var sXiheRequest:SXiheRequest; //玩家羲和神车请求帮助的信息

		public function REvt_GuildXiheHelpNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildXiheHelpNotify byType={byType}/>;
			if(sXiheRequest != null)
				topXml.appendChild(sXiheRequest.toXML("sXiheRequest"));
			return topXml;
		}
	}
}
