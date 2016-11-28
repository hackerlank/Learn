/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyCreatureMove.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知Creature移动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NotifyCreatureMove[通知Creature移动]的接收事件
	 */
	public final class REvt_NotifyCreatureMove extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NotifyCreatureMove";
		public static const DATA_ERROR:String = "MapProt_NotifyCreatureMove_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var vecPosition:Vector.<SPosition>; //移动位置列表

		public function REvt_NotifyCreatureMove(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyCreatureMove qwCreatureID={qwCreatureID}/>;
			if(vecPosition != null)
			{
				var vecPositionXml:XML = <Vec_SPosition _name_="vecPosition"/>;
				for each(var s1:SPosition in vecPosition)
					vecPositionXml.appendChild(s1.toXML());
				topXml.appendChild(vecPositionXml);
			}
			return topXml;
		}
	}
}
