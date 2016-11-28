/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetGuildApplyList.as
//  Purpose:      协议:帮派相关协议, 函数:获得已申请帮派列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GetGuildApplyList[获得已申请帮派列表]的返回事件
	 */
	public final class TEvt_GetGuildApplyList extends Event
	{
		public static const DATA_RETURN:String = "GuildProt_GetGuildApplyList";
		public static const DATA_ERROR:String = "GuildProt_GetGuildApplyList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetGuildApplyList; //返回的参数

		public function TEvt_GetGuildApplyList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetGuildApplyList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
