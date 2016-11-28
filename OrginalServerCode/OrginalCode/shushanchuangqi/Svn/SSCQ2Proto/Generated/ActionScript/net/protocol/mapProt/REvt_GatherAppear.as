/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GatherAppear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知采集物出现
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数GatherAppear[通知采集物出现]的接收事件
	 */
	public final class REvt_GatherAppear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_GatherAppear";
		public static const DATA_ERROR:String = "MapProt_GatherAppear_Error";

		public var dwGatherID:uint; //(无符号32位整数)生物ID
		public var rGatherAppear:SGatherAppear; //采集物外观
		public var rPosition:SPosition; //出现位置
		public var fDir:Number; //(Float)方向(弧度)
		public var bBorn:Boolean; //true为出生，false为进入视野

		public function REvt_GatherAppear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GatherAppear dwGatherID={dwGatherID} fDir={fDir} bBorn={bBorn}/>;
			if(rGatherAppear != null)
				topXml.appendChild(rGatherAppear.toXML("rGatherAppear"));
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
