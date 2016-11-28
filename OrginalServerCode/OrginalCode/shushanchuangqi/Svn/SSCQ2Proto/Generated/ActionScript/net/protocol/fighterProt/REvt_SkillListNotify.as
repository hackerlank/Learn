/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SkillListNotify.as
//  Purpose:      协议:道具相关协议, 函数:散仙技能列表返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数SkillListNotify[散仙技能列表返回]的接收事件
	 */
	public final class REvt_SkillListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_SkillListNotify";
		public static const DATA_ERROR:String = "FighterProt_SkillListNotify_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var VecFighterSkill:Vector.<SFighterSkill>; //技能ID

		public function REvt_SkillListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SkillListNotify qwInstID={qwInstID}/>;
			if(VecFighterSkill != null)
			{
				var VecFighterSkillXml:XML = <Vec_SFighterSkill _name_="VecFighterSkill"/>;
				for each(var s1:SFighterSkill in VecFighterSkill)
					VecFighterSkillXml.appendChild(s1.toXML());
				topXml.appendChild(VecFighterSkillXml);
			}
			return topXml;
		}
	}
}
