/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StoreItemDelNtf.as
//  Purpose:      协议:道具相关协议, 函数:当前玩家的包裹或仓库中道具删除通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数StoreItemDelNtf[当前玩家的包裹或仓库中道具删除通知]的接收事件
	 */
	public final class REvt_StoreItemDelNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_StoreItemDelNtf";
		public static const DATA_ERROR:String = "ItemProt_StoreItemDelNtf_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var vecInstID:Vector.<BigInteger>; //(无符号64位整数)道具的实例ID列表

		public function REvt_StoreItemDelNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StoreItemDelNtf eStoreType={eStoreType}/>;
			if(vecInstID != null)
			{
				var vecInstIDXml:XML = <Vec_UINT64 _name_="vecInstID"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecInstID)
					text1 += "[" + value1 + "]";
				vecInstIDXml.appendChild(text1);
				topXml.appendChild(vecInstIDXml);
			}
			return topXml;
		}
	}
}
