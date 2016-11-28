/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddTalentSkillNotify.as
//  Purpose:      协议:道具相关协议, 函数:散仙心法主卷等级满了添加一个天赋技能更新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数AddTalentSkillNotify[散仙心法主卷等级满了添加一个天赋技能更新通知]的接收事件
	 */
	public final class REvt_AddTalentSkillNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_AddTalentSkillNotify";
		public static const DATA_ERROR:String = "FighterProt_AddTalentSkillNotify_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var byIdx:uint; //(无符号8位整数)技能槽idx
		public var dwSkillID:uint; //(无符号32位整数)技能ID

		public function REvt_AddTalentSkillNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddTalentSkillNotify qwInstID={qwInstID} byIdx={byIdx} dwSkillID={dwSkillID}/>;
			return topXml;
		}
	}
}
