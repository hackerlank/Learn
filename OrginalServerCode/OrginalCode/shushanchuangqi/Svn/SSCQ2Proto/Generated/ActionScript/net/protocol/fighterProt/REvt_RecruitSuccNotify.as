/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_RecruitSuccNotify.as
//  Purpose:      协议:道具相关协议, 函数:招募散仙成功的弹框通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;

	/**
	 * 函数RecruitSuccNotify[招募散仙成功的弹框通知]的接收事件
	 */
	public final class REvt_RecruitSuccNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_RecruitSuccNotify";
		public static const DATA_ERROR:String = "FighterProt_RecruitSuccNotify_Error";

		public var wFighterID:uint; //(无符号16位整数)散仙ID

		public function REvt_RecruitSuccNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_RecruitSuccNotify wFighterID={wFighterID}/>;
			return topXml;
		}
	}
}
