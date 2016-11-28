/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SignupEnterNotify.as
//  Purpose:      协议:帮派相关协议, 函数:报名还没进入的通知进入
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数SignupEnterNotify[报名还没进入的通知进入]的接收事件
	 */
	public final class REvt_SignupEnterNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_SignupEnterNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_SignupEnterNotify_Error";


		public function REvt_SignupEnterNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SignupEnterNotify/>;
			return topXml;
		}
	}
}
