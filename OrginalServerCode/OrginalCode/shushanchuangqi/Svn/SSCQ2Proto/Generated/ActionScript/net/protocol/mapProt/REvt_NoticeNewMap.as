/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NoticeNewMap.as
//  Purpose:      协议:地图相关功能的协议, 函数:新地图产生，通知同地图玩家
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数NoticeNewMap[新地图产生，通知同地图玩家]的接收事件
	 */
	public final class REvt_NoticeNewMap extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NoticeNewMap";
		public static const DATA_ERROR:String = "MapProt_NoticeNewMap_Error";

		public var vecLoad:Vector.<MapOverLoad>; //地图负载

		public function REvt_NoticeNewMap(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NoticeNewMap/>;
			if(vecLoad != null)
			{
				var vecLoadXml:XML = <Vec_MapOverLoad _name_="vecLoad"/>;
				for each(var s1:MapOverLoad in vecLoad)
					vecLoadXml.appendChild(s1.toXML());
				topXml.appendChild(vecLoadXml);
			}
			return topXml;
		}
	}
}
