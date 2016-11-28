/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CallMemberNotify.as
//  Purpose:      协议:帮派相关协议, 函数:召集帮众广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数CallMemberNotify[召集帮众广播]的接收事件
	 */
	public final class REvt_CallMemberNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_CallMemberNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_CallMemberNotify_Error";

		public var byQuality:uint; //(无符号8位整数)品质
		public var strName:String; //名字

		public function REvt_CallMemberNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CallMemberNotify byQuality={byQuality} strName={strName}/>;
			return topXml;
		}
	}
}
