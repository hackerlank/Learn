/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetGuildInfo.as
//  Purpose:      协议:帮派相关协议, 函数:获取帮派面板信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GetGuildInfo[获取帮派面板信息]的返回事件
	 */
	public final class TEvt_GetGuildInfo extends Event
	{
		public static const DATA_RETURN:String = "GuildProt_GetGuildInfo";
		public static const DATA_ERROR:String = "GuildProt_GetGuildInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetGuildInfo; //返回的参数

		public function TEvt_GetGuildInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetGuildInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
