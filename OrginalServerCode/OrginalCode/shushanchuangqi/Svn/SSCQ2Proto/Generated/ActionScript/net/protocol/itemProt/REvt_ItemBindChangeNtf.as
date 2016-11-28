/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ItemBindChangeNtf.as
//  Purpose:      协议:道具相关协议, 函数:道具绑定改变通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数ItemBindChangeNtf[道具绑定改变通知]的接收事件
	 */
	public final class REvt_ItemBindChangeNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ItemBindChangeNtf";
		public static const DATA_ERROR:String = "ItemProt_ItemBindChangeNtf_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwInstID:BigInteger; //(无符号64位整数)道具的实例ID
		public var eBindType:uint; //(枚举类型：EBindType)道具的绑定类型
		public var bBind:Boolean; //道具是否绑定

		public function REvt_ItemBindChangeNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ItemBindChangeNtf eStoreType={eStoreType} qwInstID={qwInstID} eBindType={eBindType} bBind={bBind}/>;
			return topXml;
		}
	}
}
