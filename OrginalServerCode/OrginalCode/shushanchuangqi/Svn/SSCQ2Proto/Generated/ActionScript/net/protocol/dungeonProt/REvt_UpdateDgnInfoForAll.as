/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateDgnInfoForAll.as
//  Purpose:      协议:副本相关协议, 函数:更新所有副本信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateDgnInfoForAll[更新所有副本信息]的接收事件
	 */
	public final class REvt_UpdateDgnInfoForAll extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_UpdateDgnInfoForAll";
		public static const DATA_ERROR:String = "DungeonProt_UpdateDgnInfoForAll_Error";

		public var sLiXian:DgnLiXian; //历险副本信息
		public var vecStar:Vector.<DgnStar>; //副本星级

		public function REvt_UpdateDgnInfoForAll(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateDgnInfoForAll/>;
			if(sLiXian != null)
				topXml.appendChild(sLiXian.toXML("sLiXian"));
			if(vecStar != null)
			{
				var vecStarXml:XML = <Vec_DgnStar _name_="vecStar"/>;
				for each(var s2:DgnStar in vecStar)
					vecStarXml.appendChild(s2.toXML());
				topXml.appendChild(vecStarXml);
			}
			return topXml;
		}
	}
}
