/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CittaAddNtf.as
//  Purpose:      协议:道具相关协议, 函数:当前玩家制造或者分解心法，包裹或仓库中道具增加通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数CittaAddNtf[当前玩家制造或者分解心法，包裹或仓库中道具增加通知]的接收事件
	 */
	public final class REvt_CittaAddNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_CittaAddNtf";
		public static const DATA_ERROR:String = "ItemProt_CittaAddNtf_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var vecStoreItem:Vector.<SItem>; //包裹或仓库中道具的列表
		public var bNew:Boolean; //是否新获得道具

		public function REvt_CittaAddNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CittaAddNtf eStoreType={eStoreType} bNew={bNew}/>;
			if(vecStoreItem != null)
			{
				var vecStoreItemXml:XML = <Vec_SItem _name_="vecStoreItem"/>;
				for each(var s1:SItem in vecStoreItem)
					vecStoreItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecStoreItemXml);
			}
			return topXml;
		}
	}
}
