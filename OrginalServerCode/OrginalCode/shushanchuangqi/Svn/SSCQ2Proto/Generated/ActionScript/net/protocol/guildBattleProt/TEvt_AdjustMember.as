/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_AdjustMember.as
//  Purpose:      协议:帮派相关协议, 函数:帮派成员调整
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数AdjustMember[帮派成员调整]的返回事件
	 */
	public final class TEvt_AdjustMember extends Event
	{
		public static const DATA_RETURN:String = "GuildBattleProt_AdjustMember";
		public static const DATA_ERROR:String = "GuildBattleProt_AdjustMember_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_AdjustMember; //返回的参数

		public function TEvt_AdjustMember(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_AdjustMember ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
