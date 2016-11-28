/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FighterPosNotify.as
//  Purpose:      协议:道具相关协议, 函数:阵型位置变更
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;

	/**
	 * 函数FighterPosNotify[阵型位置变更]的接收事件
	 */
	public final class REvt_FighterPosNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_FighterPosNotify";
		public static const DATA_ERROR:String = "FighterProt_FighterPosNotify_Error";

		public var vecPos:Vector.<SFighterPos>; //阵型位置

		public function REvt_FighterPosNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FighterPosNotify/>;
			if(vecPos != null)
			{
				var vecPosXml:XML = <Vec_SFighterPos _name_="vecPos"/>;
				for each(var s1:SFighterPos in vecPos)
					vecPosXml.appendChild(s1.toXML());
				topXml.appendChild(vecPosXml);
			}
			return topXml;
		}
	}
}
