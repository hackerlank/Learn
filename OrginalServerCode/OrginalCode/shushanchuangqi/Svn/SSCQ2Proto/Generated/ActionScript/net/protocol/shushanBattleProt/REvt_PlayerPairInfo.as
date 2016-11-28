/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerPairInfo.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:蜀山论剑玩家的配对信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerPairInfo[蜀山论剑玩家的配对信息]的接收事件
	 */
	public final class REvt_PlayerPairInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_PlayerPairInfo";
		public static const DATA_ERROR:String = "ShushanBattleProt_PlayerPairInfo_Error";

		public var stPairInfo:SSSBattlePairInfo; //玩家的配对信息

		public function REvt_PlayerPairInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerPairInfo/>;
			if(stPairInfo != null)
				topXml.appendChild(stPairInfo.toXML("stPairInfo"));
			return topXml;
		}
	}
}
