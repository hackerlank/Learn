/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DungeonMapIdxNotify.as
//  Purpose:      协议:副本相关协议, 函数:副本地图怪物采集物索引通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数DungeonMapIdxNotify[副本地图怪物采集物索引通知]的接收事件
	 */
	public final class REvt_DungeonMapIdxNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_DungeonMapIdxNotify";
		public static const DATA_ERROR:String = "DungeonProt_DungeonMapIdxNotify_Error";

		public var vecIdx:Vector.<uint>; //(无符号8位整数)索引ID

		public function REvt_DungeonMapIdxNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DungeonMapIdxNotify/>;
			if(vecIdx != null)
			{
				var vecIdxXml:XML = <Vec_UINT8 _name_="vecIdx"/>;
				var text1:String = "";
				for each(var value1:uint in vecIdx)
					text1 += "[" + value1 + "]";
				vecIdxXml.appendChild(text1);
				topXml.appendChild(vecIdxXml);
			}
			return topXml;
		}
	}
}
