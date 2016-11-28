/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BeastSoulNotify.as
//  Purpose:      协议:阵灵相关协议, 函数:兽魂信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.SBeastSoulInfo;

	/**
	 * 函数BeastSoulNotify[兽魂信息]的接收事件
	 */
	public final class REvt_BeastSoulNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FormationProt_BeastSoulNotify";
		public static const DATA_ERROR:String = "FormationProt_BeastSoulNotify_Error";

		public var vecBeastSoul:Vector.<SBeastSoulInfo>; //兽魂信息

		public function REvt_BeastSoulNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BeastSoulNotify/>;
			if(vecBeastSoul != null)
			{
				var vecBeastSoulXml:XML = <Vec_SBeastSoulInfo _name_="vecBeastSoul"/>;
				for each(var s1:SBeastSoulInfo in vecBeastSoul)
					vecBeastSoulXml.appendChild(s1.toXML());
				topXml.appendChild(vecBeastSoulXml);
			}
			return topXml;
		}
	}
}
