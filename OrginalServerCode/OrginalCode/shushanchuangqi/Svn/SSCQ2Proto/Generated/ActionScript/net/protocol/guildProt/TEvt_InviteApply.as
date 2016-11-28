/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_InviteApply.as
//  Purpose:      协议:帮派相关协议, 函数:邀请加入
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.events.Event;

	/**
	 * 函数InviteApply[邀请加入]的返回事件
	 */
	public final class TEvt_InviteApply extends Event
	{
		public static const DATA_RETURN:String = "GuildProt_InviteApply";
		public static const DATA_ERROR:String = "GuildProt_InviteApply_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_InviteApply; //返回的参数

		public function TEvt_InviteApply(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_InviteApply ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
