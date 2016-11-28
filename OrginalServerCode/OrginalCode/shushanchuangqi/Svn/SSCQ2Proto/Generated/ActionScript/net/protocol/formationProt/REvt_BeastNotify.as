/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BeastNotify.as
//  Purpose:      协议:阵灵相关协议, 函数:兽魂信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;

	/**
	 * 函数BeastNotify[兽魂信息]的接收事件
	 */
	public final class REvt_BeastNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FormationProt_BeastNotify";
		public static const DATA_ERROR:String = "FormationProt_BeastNotify_Error";

		public var wBeastID:uint; //(无符号16位整数)兽魂ID

		public function REvt_BeastNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BeastNotify wBeastID={wBeastID}/>;
			return topXml;
		}
	}
}
