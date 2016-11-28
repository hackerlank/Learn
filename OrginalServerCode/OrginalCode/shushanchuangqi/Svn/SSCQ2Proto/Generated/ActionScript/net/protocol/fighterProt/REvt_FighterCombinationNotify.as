/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FighterCombinationNotify.as
//  Purpose:      协议:道具相关协议, 函数:玩家的散仙组合列表返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;

	/**
	 * 函数FighterCombinationNotify[玩家的散仙组合列表返回]的接收事件
	 */
	public final class REvt_FighterCombinationNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_FighterCombinationNotify";
		public static const DATA_ERROR:String = "FighterProt_FighterCombinationNotify_Error";

		public var VecCombination:Vector.<SFighterCombination>; //散仙组合列表

		public function REvt_FighterCombinationNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FighterCombinationNotify/>;
			if(VecCombination != null)
			{
				var VecCombinationXml:XML = <Vec_SFighterCombination _name_="VecCombination"/>;
				for each(var s1:SFighterCombination in VecCombination)
					VecCombinationXml.appendChild(s1.toXML());
				topXml.appendChild(VecCombinationXml);
			}
			return topXml;
		}
	}
}
