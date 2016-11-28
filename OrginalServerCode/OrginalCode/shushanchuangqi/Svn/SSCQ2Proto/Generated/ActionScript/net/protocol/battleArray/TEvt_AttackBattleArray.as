/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_AttackBattleArray.as
//  Purpose:      协议:破阵, 函数:攻击阵图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;

	/**
	 * 函数AttackBattleArray[攻击阵图]的返回事件
	 */
	public final class TEvt_AttackBattleArray extends Event
	{
		public static const DATA_RETURN:String = "BattleArray_AttackBattleArray";
		public static const DATA_ERROR:String = "BattleArray_AttackBattleArray_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_AttackBattleArray; //返回的参数

		public function TEvt_AttackBattleArray(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_AttackBattleArray ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
