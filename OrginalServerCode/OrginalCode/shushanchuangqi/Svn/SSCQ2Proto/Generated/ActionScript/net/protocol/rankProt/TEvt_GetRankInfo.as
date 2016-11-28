/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetRankInfo.as
//  Purpose:      协议:排行榜相关协议, 函数:获取排行榜数据
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.events.Event;

	/**
	 * 函数GetRankInfo[获取排行榜数据]的返回事件
	 */
	public final class TEvt_GetRankInfo extends Event
	{
		public static const DATA_RETURN:String = "RankProt_GetRankInfo";
		public static const DATA_ERROR:String = "RankProt_GetRankInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetRankInfo; //返回的参数

		public function TEvt_GetRankInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetRankInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
