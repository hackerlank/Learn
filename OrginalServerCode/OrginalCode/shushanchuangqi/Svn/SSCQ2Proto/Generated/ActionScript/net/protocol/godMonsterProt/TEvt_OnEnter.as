/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_OnEnter.as
//  Purpose:      协议:天元神兽协议, 函数:打开活动面板
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.events.Event;

	/**
	 * 函数OnEnter[打开活动面板]的返回事件
	 */
	public final class TEvt_OnEnter extends Event
	{
		public static const DATA_RETURN:String = "GodMonsterProt_OnEnter";
		public static const DATA_ERROR:String = "GodMonsterProt_OnEnter_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_OnEnter; //返回的参数

		public function TEvt_OnEnter(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_OnEnter ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
