/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SkillAddNotify.as
//  Purpose:      协议:道具相关协议, 函数:增加新技能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;

	/**
	 * 函数SkillAddNotify[增加新技能]的接收事件
	 */
	public final class REvt_SkillAddNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_SkillAddNotify";
		public static const DATA_ERROR:String = "FighterProt_SkillAddNotify_Error";

		public var dwSkillID:uint; //(无符号32位整数)技能ID

		public function REvt_SkillAddNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SkillAddNotify dwSkillID={dwSkillID}/>;
			return topXml;
		}
	}
}
