/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SkillUpNotify.as
//  Purpose:      协议:道具相关协议, 函数:装备技能返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;

	/**
	 * 函数SkillUpNotify[装备技能返回]的接收事件
	 */
	public final class REvt_SkillUpNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_SkillUpNotify";
		public static const DATA_ERROR:String = "FighterProt_SkillUpNotify_Error";

		public var dwSkillID:uint; //(无符号32位整数)技能ID
		public var iSlot:int; //(有符号32位整数)技能槽 -1表示卸下技能

		public function REvt_SkillUpNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SkillUpNotify dwSkillID={dwSkillID} iSlot={iSlot}/>;
			return topXml;
		}
	}
}
