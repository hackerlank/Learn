/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildInfoNotify[帮派信息更新]的接收事件
	 */
	public final class REvt_GuildInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildInfoNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildInfoNotify_Error";

		public var eDataType:uint; //(枚举类型：EGuildDataType)帮派信息类型
		public var vecGuildInfoBase:Vector.<SGuildInfoBase>; //帮派信息

		public function REvt_GuildInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildInfoNotify eDataType={eDataType}/>;
			if(vecGuildInfoBase != null)
			{
				var vecGuildInfoBaseXml:XML = <Vec_SGuildInfoBase _name_="vecGuildInfoBase"/>;
				for each(var s1:SGuildInfoBase in vecGuildInfoBase)
					vecGuildInfoBaseXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildInfoBaseXml);
			}
			return topXml;
		}
	}
}
