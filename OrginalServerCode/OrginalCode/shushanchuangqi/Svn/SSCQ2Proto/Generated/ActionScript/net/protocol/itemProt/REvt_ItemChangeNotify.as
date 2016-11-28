/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ItemChangeNotify.as
//  Purpose:      协议:道具相关协议, 函数:道具(装备)属性变化通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数ItemChangeNotify[道具(装备)属性变化通知]的接收事件
	 */
	public final class REvt_ItemChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ItemChangeNotify";
		public static const DATA_ERROR:String = "ItemProt_ItemChangeNotify_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var qwOwnerID:BigInteger; //(无符号64位整数)所有者ID(可能是主将，副将，宠物...)
		public var rStoreItem:SItem; //装备更新后信息

		public function REvt_ItemChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ItemChangeNotify eStoreType={eStoreType} qwOwnerID={qwOwnerID}/>;
			if(rStoreItem != null)
				topXml.appendChild(rStoreItem.toXML("rStoreItem"));
			return topXml;
		}
	}
}
