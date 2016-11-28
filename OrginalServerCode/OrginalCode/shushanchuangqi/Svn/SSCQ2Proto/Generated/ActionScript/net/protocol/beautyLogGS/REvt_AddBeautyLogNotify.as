/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddBeautyLogNotify.as
//  Purpose:      协议:美女log, 函数:美女log添加
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beautyLogGS
{
	import flash.events.Event;

	/**
	 * 函数AddBeautyLogNotify[美女log添加]的接收事件
	 */
	public final class REvt_AddBeautyLogNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BeautyLogGS_AddBeautyLogNotify";
		public static const DATA_ERROR:String = "BeautyLogGS_AddBeautyLogNotify_Error";

		public var oAddBeautyLog:SBeautyLog; //美女log信息

		public function REvt_AddBeautyLogNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddBeautyLogNotify/>;
			if(oAddBeautyLog != null)
				topXml.appendChild(oAddBeautyLog.toXML("oAddBeautyLog"));
			return topXml;
		}
	}
}
