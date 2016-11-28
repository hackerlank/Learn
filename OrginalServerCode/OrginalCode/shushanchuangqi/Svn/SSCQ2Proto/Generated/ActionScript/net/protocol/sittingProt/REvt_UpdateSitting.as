/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateSitting.as
//  Purpose:      协议:打坐协议, 函数:打坐状态变化
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.sittingProt
{
	import flash.events.Event;
	import net.protocol.mapProt.SPlayerAppear;

	/**
	 * 函数UpdateSitting[打坐状态变化]的接收事件
	 */
	public final class REvt_UpdateSitting extends Event
	{
		public static const DATA_RECEIVE:String = "SittingProt_UpdateSitting";
		public static const DATA_ERROR:String = "SittingProt_UpdateSitting_Error";

		public var byState:uint; //(无符号8位整数)0,表示结束打坐，1 ，开始打坐
		public var vecOtherApear:Vector.<SPlayerAppear>; //空表示单修，非空表示双修
		public var dwSittingTimer:uint; //(无符号32位整数)开始时间

		public function REvt_UpdateSitting(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateSitting byState={byState} dwSittingTimer={dwSittingTimer}/>;
			if(vecOtherApear != null)
			{
				var vecOtherApearXml:XML = <Vec_SPlayerAppear _name_="vecOtherApear"/>;
				for each(var s1:SPlayerAppear in vecOtherApear)
					vecOtherApearXml.appendChild(s1.toXML());
				topXml.appendChild(vecOtherApearXml);
			}
			return topXml;
		}
	}
}
