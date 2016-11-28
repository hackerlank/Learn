/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_EnterTeam.as
//  Purpose:      协议:竞技场协议, 函数:请求加入房间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数EnterTeam[请求加入房间]的返回事件
	 */
	public final class TEvt_EnterTeam extends Event
	{
		public static const DATA_RETURN:String = "TeamGS_EnterTeam";
		public static const DATA_ERROR:String = "TeamGS_EnterTeam_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_EnterTeam; //返回的参数

		public function TEvt_EnterTeam(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_EnterTeam ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
