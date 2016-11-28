/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_UnLockHorseSkillAttr.as
//  Purpose:      协议:坐骑, 函数:解锁技能属性（暂时不用）
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数UnLockHorseSkillAttr[解锁技能属性（暂时不用）]的返回事件
	 */
	public final class TEvt_UnLockHorseSkillAttr extends Event
	{
		public static const DATA_RETURN:String = "Horse_UnLockHorseSkillAttr";
		public static const DATA_ERROR:String = "Horse_UnLockHorseSkillAttr_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_UnLockHorseSkillAttr; //返回的参数

		public function TEvt_UnLockHorseSkillAttr(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_UnLockHorseSkillAttr ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
