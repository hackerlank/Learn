/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AreaAppear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知区域出现
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数AreaAppear[通知区域出现]的接收事件
	 */
	public final class REvt_AreaAppear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_AreaAppear";
		public static const DATA_ERROR:String = "MapProt_AreaAppear_Error";

		public var dwAreaID:uint; //(无符号32位整数)区域实例ID
		public var rAreaAppear:SAreaAppear; //区域外观
		public var rPosition:SPosition; //出现位置

		public function REvt_AreaAppear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AreaAppear dwAreaID={dwAreaID}/>;
			if(rAreaAppear != null)
				topXml.appendChild(rAreaAppear.toXML("rAreaAppear"));
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
