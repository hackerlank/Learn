/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SkillInfoNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派战技能信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数SkillInfoNotify[帮派战技能信息通知]的接收事件
	 */
	public final class REvt_SkillInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_SkillInfoNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_SkillInfoNotify_Error";

		public var vecSkillInfo:Vector.<SSkillInfo>; //具体已购买技能

		public function REvt_SkillInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SkillInfoNotify/>;
			if(vecSkillInfo != null)
			{
				var vecSkillInfoXml:XML = <Vec_SSkillInfo _name_="vecSkillInfo"/>;
				for each(var s1:SSkillInfo in vecSkillInfo)
					vecSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSkillInfoXml);
			}
			return topXml;
		}
	}
}
