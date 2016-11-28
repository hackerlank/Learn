/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BuffNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:玩家Buff变化通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;
	import net.protocol.protoCommon.SBuffInfo;

	/**
	 * 函数BuffNotify[玩家Buff变化通知]的接收事件
	 */
	public final class REvt_BuffNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_BuffNotify";
		public static const DATA_ERROR:String = "RoleEvent_BuffNotify_Error";

		public var eType:uint; //(枚举类型：protoCommon.EDataChange)更新类型，增加，删除，修改
		public var vecBuffInfo:Vector.<SBuffInfo>; //玩家Buff信息

		public function REvt_BuffNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BuffNotify eType={eType}/>;
			if(vecBuffInfo != null)
			{
				var vecBuffInfoXml:XML = <Vec_SBuffInfo _name_="vecBuffInfo"/>;
				for each(var s1:SBuffInfo in vecBuffInfo)
					vecBuffInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBuffInfoXml);
			}
			return topXml;
		}
	}
}
