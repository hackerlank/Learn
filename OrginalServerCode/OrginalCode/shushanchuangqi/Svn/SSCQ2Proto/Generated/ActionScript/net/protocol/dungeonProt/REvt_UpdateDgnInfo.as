/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateDgnInfo.as
//  Purpose:      协议:副本相关协议, 函数:更新单个副本信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateDgnInfo[更新单个副本信息]的接收事件
	 */
	public final class REvt_UpdateDgnInfo extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_UpdateDgnInfo";
		public static const DATA_ERROR:String = "DungeonProt_UpdateDgnInfo_Error";

		public var sDgnStar:DgnStar; //副本信息

		public function REvt_UpdateDgnInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateDgnInfo/>;
			if(sDgnStar != null)
				topXml.appendChild(sDgnStar.toXML("sDgnStar"));
			return topXml;
		}
	}
}
