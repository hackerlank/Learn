/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FormationNotify.as
//  Purpose:      协议:阵灵相关协议, 函数:阵形信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;

	/**
	 * 函数FormationNotify[阵形信息]的接收事件
	 */
	public final class REvt_FormationNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FormationProt_FormationNotify";
		public static const DATA_ERROR:String = "FormationProt_FormationNotify_Error";

		public var wFormationID:uint; //(无符号16位整数)阵形ID
		public var bySelected:uint; //(无符号8位整数)状态: 0-未启用 1-未启用

		public function REvt_FormationNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FormationNotify wFormationID={wFormationID} bySelected={bySelected}/>;
			return topXml;
		}
	}
}
