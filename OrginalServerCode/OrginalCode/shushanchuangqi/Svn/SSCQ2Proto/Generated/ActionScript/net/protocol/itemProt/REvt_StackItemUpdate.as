/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StackItemUpdate.as
//  Purpose:      协议:道具相关协议, 函数:堆叠道具数量刷新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数StackItemUpdate[堆叠道具数量刷新通知]的接收事件
	 */
	public final class REvt_StackItemUpdate extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_StackItemUpdate";
		public static const DATA_ERROR:String = "ItemProt_StackItemUpdate_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var qwInstID:BigInteger; //(无符号64位整数)堆叠道具的实例ID
		public var wStack:uint; //(无符号16位整数)当前堆叠数

		public function REvt_StackItemUpdate(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StackItemUpdate eStoreType={eStoreType} qwRoleID={qwRoleID} qwInstID={qwInstID} wStack={wStack}/>;
			return topXml;
		}
	}
}
