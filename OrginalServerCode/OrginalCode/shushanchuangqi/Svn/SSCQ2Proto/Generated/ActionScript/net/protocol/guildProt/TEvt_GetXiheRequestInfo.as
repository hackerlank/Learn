/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetXiheRequestInfo.as
//  Purpose:      协议:帮派相关协议, 函数:获取自己帮派成员的羲和神车请求帮助列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数GetXiheRequestInfo[获取自己帮派成员的羲和神车请求帮助列表]的返回事件
	 */
	public final class TEvt_GetXiheRequestInfo extends Event
	{
		public static const DATA_RETURN:String = "GuildProt_GetXiheRequestInfo";
		public static const DATA_ERROR:String = "GuildProt_GetXiheRequestInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetXiheRequestInfo; //返回的参数

		public function TEvt_GetXiheRequestInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetXiheRequestInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
