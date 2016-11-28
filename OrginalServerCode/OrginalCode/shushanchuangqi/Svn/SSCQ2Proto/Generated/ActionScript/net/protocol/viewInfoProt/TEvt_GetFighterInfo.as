/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetFighterInfo.as
//  Purpose:      协议:查看信息协议, 函数:获取散仙信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.events.Event;

	/**
	 * 函数GetFighterInfo[获取散仙信息]的返回事件
	 */
	public final class TEvt_GetFighterInfo extends Event
	{
		public static const DATA_RETURN:String = "ViewInfoProt_GetFighterInfo";
		public static const DATA_ERROR:String = "ViewInfoProt_GetFighterInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetFighterInfo; //返回的参数

		public function TEvt_GetFighterInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetFighterInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
