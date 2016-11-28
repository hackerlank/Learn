/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyDgnProcess.as
//  Purpose:      协议:副本相关协议, 函数:通告副本进程
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数NotifyDgnProcess[通告副本进程]的接收事件
	 */
	public final class REvt_NotifyDgnProcess extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_NotifyDgnProcess";
		public static const DATA_ERROR:String = "DungeonProt_NotifyDgnProcess_Error";

		public var wDgnType:uint; //(无符号16位整数)副本类型
		public var vecProcess:Vector.<MulCond>; //副本进度

		public function REvt_NotifyDgnProcess(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyDgnProcess wDgnType={wDgnType}/>;
			if(vecProcess != null)
			{
				var vecProcessXml:XML = <Vec_MulCond _name_="vecProcess"/>;
				for each(var s1:MulCond in vecProcess)
					vecProcessXml.appendChild(s1.toXML());
				topXml.appendChild(vecProcessXml);
			}
			return topXml;
		}
	}
}
