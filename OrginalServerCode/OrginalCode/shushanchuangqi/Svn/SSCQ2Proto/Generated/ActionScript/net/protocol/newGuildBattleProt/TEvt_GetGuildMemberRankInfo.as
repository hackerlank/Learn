/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetGuildMemberRankInfo.as
//  Purpose:      协议:新帮派战相关协议, 函数:获取战功榜帮派成员排名信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数GetGuildMemberRankInfo[获取战功榜帮派成员排名信息]的返回事件
	 */
	public final class TEvt_GetGuildMemberRankInfo extends Event
	{
		public static const DATA_RETURN:String = "NewGuildBattleProt_GetGuildMemberRankInfo";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GetGuildMemberRankInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetGuildMemberRankInfo; //返回的参数

		public function TEvt_GetGuildMemberRankInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetGuildMemberRankInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
