/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateStudyState.as
//  Purpose:      协议:衙门任务协议, 函数:更新清修状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateStudyState[更新清修状态]的接收事件
	 */
	public final class REvt_UpdateStudyState extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_UpdateStudyState";
		public static const DATA_ERROR:String = "YaMenTaskProt_UpdateStudyState_Error";

		public var eStudyState:uint; //(枚举类型：EYaMenStudyState)清修状态

		public function REvt_UpdateStudyState(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateStudyState eStudyState={eStudyState}/>;
			return topXml;
		}
	}
}
