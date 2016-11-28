/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildListInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派列表信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildListInfoNotify[帮派列表信息]的接收事件
	 */
	public final class REvt_GuildListInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildListInfoNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildListInfoNotify_Error";

		public var dwMaxGuildCount:uint; //(无符号32位整数)最大帮派
		public var dwCurGuildCount:uint; //(无符号32位整数)当前帮派索引
		public var vecGuildListInfo:Vector.<SGuildListInfo>; //帮派列表信息

		public function REvt_GuildListInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildListInfoNotify dwMaxGuildCount={dwMaxGuildCount} dwCurGuildCount={dwCurGuildCount}/>;
			if(vecGuildListInfo != null)
			{
				var vecGuildListInfoXml:XML = <Vec_SGuildListInfo _name_="vecGuildListInfo"/>;
				for each(var s1:SGuildListInfo in vecGuildListInfo)
					vecGuildListInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildListInfoXml);
			}
			return topXml;
		}
	}
}
