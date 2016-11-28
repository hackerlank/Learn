/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildExchangedItemNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派兑换物品更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GuildExchangedItemNotify[帮派兑换物品更新]的接收事件
	 */
	public final class REvt_GuildExchangedItemNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildProt_GuildExchangedItemNotify";
		public static const DATA_ERROR:String = "GuildProt_GuildExchangedItemNotify_Error";

		public var vecGuildExchangedItem:Vector.<SGuildExchangedItem>; //兑换物品信息
		public var dwGUildAllMemberExchangedItemNum:uint; //(无符号32位整数)帮派所有成员兑换物品总数量
		public var dwPlayerExchangedItemNum:uint; //(无符号32位整数)玩家兑换物品总数量

		public function REvt_GuildExchangedItemNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildExchangedItemNotify dwGUildAllMemberExchangedItemNum={dwGUildAllMemberExchangedItemNum} dwPlayerExchangedItemNum={dwPlayerExchangedItemNum}/>;
			if(vecGuildExchangedItem != null)
			{
				var vecGuildExchangedItemXml:XML = <Vec_SGuildExchangedItem _name_="vecGuildExchangedItem"/>;
				for each(var s1:SGuildExchangedItem in vecGuildExchangedItem)
					vecGuildExchangedItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildExchangedItemXml);
			}
			return topXml;
		}
	}
}
