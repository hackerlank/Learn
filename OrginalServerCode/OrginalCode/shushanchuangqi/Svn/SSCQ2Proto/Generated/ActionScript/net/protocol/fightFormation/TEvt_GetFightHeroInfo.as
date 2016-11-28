/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetFightHeroInfo.as
//  Purpose:      协议:新阵型相关协议, 函数:战斗散仙信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	import flash.events.Event;

	/**
	 * 函数GetFightHeroInfo[战斗散仙信息]的返回事件
	 */
	public final class TEvt_GetFightHeroInfo extends Event
	{
		public static const DATA_RETURN:String = "FightFormation_GetFightHeroInfo";
		public static const DATA_ERROR:String = "FightFormation_GetFightHeroInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetFightHeroInfo; //返回的参数

		public function TEvt_GetFightHeroInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetFightHeroInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
