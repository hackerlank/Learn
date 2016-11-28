/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyCreatureJump.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知Creature跳点
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NotifyCreatureJump[通知Creature跳点]的接收事件
	 */
	public final class REvt_NotifyCreatureJump extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NotifyCreatureJump";
		public static const DATA_ERROR:String = "MapProt_NotifyCreatureJump_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)Creature ID
		public var rPosition:SPosition; //跳点目的位置
		public var wJumpId:uint; //(无符号16位整数)跳点ID

		public function REvt_NotifyCreatureJump(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyCreatureJump qwCreatureID={qwCreatureID} wJumpId={wJumpId}/>;
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
