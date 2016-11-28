/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReqGEMPrepareBattleInfo.as
//  Purpose:      协议:守卫峨眉协议, 函数:请求守卫峨眉准备战斗信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.events.Event;

	/**
	 * 函数ReqGEMPrepareBattleInfo[请求守卫峨眉准备战斗信息]的返回事件
	 */
	public final class TEvt_ReqGEMPrepareBattleInfo extends Event
	{
		public static const DATA_RETURN:String = "GuardEMeiProt_ReqGEMPrepareBattleInfo";
		public static const DATA_ERROR:String = "GuardEMeiProt_ReqGEMPrepareBattleInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReqGEMPrepareBattleInfo; //返回的参数

		public function TEvt_ReqGEMPrepareBattleInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReqGEMPrepareBattleInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
