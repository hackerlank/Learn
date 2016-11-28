/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildCreateNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派创建结果通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildCreateNotify[帮派创建结果通知]的接收事件
	 */
	public final class REvt_GuildCreateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildCreateNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildCreateNotify_Error";

		public var eResult:uint; //(枚举类型：ECreateResult)创建结果
		public var vecGuildInfo:Vector.<SGuildAllInfo>; //帮派信息(大小为0或者1)

		public function REvt_GuildCreateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildCreateNotify eResult={eResult}/>;
			if(vecGuildInfo != null)
			{
				var vecGuildInfoXml:XML = <Vec_SGuildAllInfo _name_="vecGuildInfo"/>;
				for each(var s1:SGuildAllInfo in vecGuildInfo)
					vecGuildInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildInfoXml);
			}
			return topXml;
		}
	}
}
