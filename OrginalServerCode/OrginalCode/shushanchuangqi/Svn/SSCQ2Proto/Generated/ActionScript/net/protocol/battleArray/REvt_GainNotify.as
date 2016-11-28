/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GainNotify.as
//  Purpose:      协议:破阵, 函数:获得物品通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.events.Event;
	import net.protocol.itemProt.SItemGenInfo;

	/**
	 * 函数GainNotify[获得物品通知]的接收事件
	 */
	public final class REvt_GainNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BattleArray_GainNotify";
		public static const DATA_ERROR:String = "BattleArray_GainNotify_Error";

		public var eBattleArrayGain:uint; //(枚举类型：EBattleArrayGain)类型
		public var vecItemGenInfo:Vector.<SItemGenInfo>; //物品

		public function REvt_GainNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GainNotify eBattleArrayGain={eBattleArrayGain}/>;
			if(vecItemGenInfo != null)
			{
				var vecItemGenInfoXml:XML = <Vec_SItemGenInfo _name_="vecItemGenInfo"/>;
				for each(var s1:SItemGenInfo in vecItemGenInfo)
					vecItemGenInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemGenInfoXml);
			}
			return topXml;
		}
	}
}
