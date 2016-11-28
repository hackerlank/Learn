/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BlockerAppear.as
//  Purpose:      协议:地图相关功能的协议, 函数:阻挡物出现
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数BlockerAppear[阻挡物出现]的接收事件
	 */
	public final class REvt_BlockerAppear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_BlockerAppear";
		public static const DATA_ERROR:String = "MapProt_BlockerAppear_Error";

		public var dwInstID:uint; //(无符号32位整数)唯一ID
		public var rBlockerAppear:SBlockerAppear; //阻挡物开关
		public var rPosition:SPosition; //出现位置
		public var fDir:Number; //(Float)方向(弧度)
		public var bBorn:Boolean; //true为出生，false为进入视野

		public function REvt_BlockerAppear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BlockerAppear dwInstID={dwInstID} fDir={fDir} bBorn={bBorn}/>;
			if(rBlockerAppear != null)
				topXml.appendChild(rBlockerAppear.toXML("rBlockerAppear"));
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
