/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ChangeMapNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:准备切地图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数ChangeMapNotify[准备切地图]的接收事件
	 */
	public final class REvt_ChangeMapNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_ChangeMapNotify";
		public static const DATA_ERROR:String = "RoleEvent_ChangeMapNotify_Error";

		public var wMapId:uint; //(无符号16位整数)地图id，客户端准备资源
		public var qwDgnId:BigInteger; //(无符号64位整数)副本实例，非单人副本为0
		public var wDgnType:uint; //(无符号16位整数)副本模板，单人副本为0

		public function REvt_ChangeMapNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ChangeMapNotify wMapId={wMapId} qwDgnId={qwDgnId} wDgnType={wDgnType}/>;
			return topXml;
		}
	}
}
