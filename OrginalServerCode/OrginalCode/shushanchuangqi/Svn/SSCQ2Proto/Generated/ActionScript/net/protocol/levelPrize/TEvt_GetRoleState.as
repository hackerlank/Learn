/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetRoleState.as
//  Purpose:      协议:等级奖励, 函数:玩家在个人服活动中的状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.events.Event;

	/**
	 * 函数GetRoleState[玩家在个人服活动中的状态]的返回事件
	 */
	public final class TEvt_GetRoleState extends Event
	{
		public static const DATA_RETURN:String = "LevelPrize_GetRoleState";
		public static const DATA_ERROR:String = "LevelPrize_GetRoleState_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetRoleState; //返回的参数

		public function TEvt_GetRoleState(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetRoleState ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
