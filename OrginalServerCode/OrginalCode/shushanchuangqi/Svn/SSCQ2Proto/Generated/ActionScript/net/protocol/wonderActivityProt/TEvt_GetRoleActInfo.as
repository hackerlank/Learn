/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetRoleActInfo.as
//  Purpose:      协议:精彩活动, 函数:玩家活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.events.Event;

	/**
	 * 函数GetRoleActInfo[玩家活动信息]的返回事件
	 */
	public final class TEvt_GetRoleActInfo extends Event
	{
		public static const DATA_RETURN:String = "WonderActivityProt_GetRoleActInfo";
		public static const DATA_ERROR:String = "WonderActivityProt_GetRoleActInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetRoleActInfo; //返回的参数

		public function TEvt_GetRoleActInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetRoleActInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
