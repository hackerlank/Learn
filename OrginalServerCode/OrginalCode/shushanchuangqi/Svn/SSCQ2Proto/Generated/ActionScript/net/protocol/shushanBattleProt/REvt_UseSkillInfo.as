/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UseSkillInfo.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:蜀山论剑玩家使用技能信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数UseSkillInfo[蜀山论剑玩家使用技能信息]的接收事件
	 */
	public final class REvt_UseSkillInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_UseSkillInfo";
		public static const DATA_ERROR:String = "ShushanBattleProt_UseSkillInfo_Error";

		public var stUseSkill:SSSBattleUseSkill; //使用技能信息

		public function REvt_UseSkillInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UseSkillInfo/>;
			if(stUseSkill != null)
				topXml.appendChild(stUseSkill.toXML("stUseSkill"));
			return topXml;
		}
	}
}
