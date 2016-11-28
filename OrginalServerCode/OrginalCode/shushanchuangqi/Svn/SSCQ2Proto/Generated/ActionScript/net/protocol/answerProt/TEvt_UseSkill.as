/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_UseSkill.as
//  Purpose:      协议:答题协议, 函数:玩家使用技能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数UseSkill[玩家使用技能]的返回事件
	 */
	public final class TEvt_UseSkill extends Event
	{
		public static const DATA_RETURN:String = "AnswerProt_UseSkill";
		public static const DATA_ERROR:String = "AnswerProt_UseSkill_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_UseSkill; //返回的参数

		public function TEvt_UseSkill(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_UseSkill ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
