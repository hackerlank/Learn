/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_Enter.as
//  Purpose:      协议:帮派相关协议, 函数:进入帮派战(进入准备场地)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数Enter[进入帮派战(进入准备场地)]的返回事件
	 */
	public final class TEvt_Enter extends Event
	{
		public static const DATA_RETURN:String = "GuildBattleProt_Enter";
		public static const DATA_ERROR:String = "GuildBattleProt_Enter_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_Enter; //返回的参数

		public function TEvt_Enter(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_Enter ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
