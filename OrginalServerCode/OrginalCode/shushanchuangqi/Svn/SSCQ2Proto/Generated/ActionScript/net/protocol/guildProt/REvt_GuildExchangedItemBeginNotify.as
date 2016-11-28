/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildExchangedItemBeginNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派战兑换物品开始
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildExchangedItemBeginNotify[帮派战兑换物品开始]的接收事件
	 */
	public final class REvt_GuildExchangedItemBeginNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildExchangedItemBeginNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildExchangedItemBeginNotify_Error";

		public var vecLingShanType:Vector.<uint>; //(无符号8位整数)灵山类型

		public function REvt_GuildExchangedItemBeginNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildExchangedItemBeginNotify/>;
			if(vecLingShanType != null)
			{
				var vecLingShanTypeXml:XML = <Vec_UINT8 _name_="vecLingShanType"/>;
				var text1:String = "";
				for each(var value1:uint in vecLingShanType)
					text1 += "[" + value1 + "]";
				vecLingShanTypeXml.appendChild(text1);
				topXml.appendChild(vecLingShanTypeXml);
			}
			return topXml;
		}
	}
}
