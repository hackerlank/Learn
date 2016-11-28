/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NpcAppear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知NPC出现
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NpcAppear[通知NPC出现]的接收事件
	 */
	public final class REvt_NpcAppear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NpcAppear";
		public static const DATA_ERROR:String = "MapProt_NpcAppear_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var rNpcAppear:SNpcAppear; //NPC外观
		public var rPosition:SPosition; //出现位置
		public var fDir:Number; //(Float)方向(弧度)
		public var bBorn:Boolean; //true为出生，false为进入视野

		public function REvt_NpcAppear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NpcAppear qwCreatureID={qwCreatureID} fDir={fDir} bBorn={bBorn}/>;
			if(rNpcAppear != null)
				topXml.appendChild(rNpcAppear.toXML("rNpcAppear"));
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
