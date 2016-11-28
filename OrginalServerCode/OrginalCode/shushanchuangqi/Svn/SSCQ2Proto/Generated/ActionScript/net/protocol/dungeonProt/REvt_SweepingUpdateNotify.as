/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SweepingUpdateNotify.as
//  Purpose:      协议:副本相关协议, 函数:扫荡更新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;

	/**
	 * 函数SweepingUpdateNotify[扫荡更新通知]的接收事件
	 */
	public final class REvt_SweepingUpdateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_SweepingUpdateNotify";
		public static const DATA_ERROR:String = "DungeonProt_SweepingUpdateNotify_Error";

		public var vecItem:Vector.<SItemGenInfo>; //获得物品
		public var vecResSource:Vector.<SResource>; //获得资源
		public var wCurrCount:uint; //(无符号16位整数)当前次数
		public var dwSweepEndTime:uint; //(无符号32位整数)扫荡结束时间

		public function REvt_SweepingUpdateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SweepingUpdateNotify wCurrCount={wCurrCount} dwSweepEndTime={dwSweepEndTime}/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s1:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			if(vecResSource != null)
			{
				var vecResSourceXml:XML = <Vec_SResource _name_="vecResSource"/>;
				for each(var s2:SResource in vecResSource)
					vecResSourceXml.appendChild(s2.toXML());
				topXml.appendChild(vecResSourceXml);
			}
			return topXml;
		}
	}
}
