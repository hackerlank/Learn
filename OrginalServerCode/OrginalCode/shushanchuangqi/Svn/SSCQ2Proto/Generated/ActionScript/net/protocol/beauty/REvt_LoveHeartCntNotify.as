/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_LoveHeartCntNotify.as
//  Purpose:      协议:美女系统, 函数:爱心数目更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数LoveHeartCntNotify[爱心数目更新]的接收事件
	 */
	public final class REvt_LoveHeartCntNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Beauty_LoveHeartCntNotify";
		public static const DATA_ERROR:String = "Beauty_LoveHeartCntNotify_Error";

		public var dwLoveCnt:uint; //(无符号32位整数)爱心个数

		public function REvt_LoveHeartCntNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_LoveHeartCntNotify dwLoveCnt={dwLoveCnt}/>;
			return topXml;
		}
	}
}
