/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendPkgInfo.as
//  Purpose:      协议:累计登入礼包协议, 函数:登入礼包信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginPkgProt
{
	import flash.events.Event;

	/**
	 * 函数SendPkgInfo[登入礼包信息]的接收事件
	 */
	public final class REvt_SendPkgInfo extends Event
	{
		public static const DATA_RECEIVE:String = "LoginPkgProt_SendPkgInfo";
		public static const DATA_ERROR:String = "LoginPkgProt_SendPkgInfo_Error";

		public var wDays:uint; //(无符号16位整数)连续登入的天数
		public var wResult:uint; //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领

		public function REvt_SendPkgInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendPkgInfo wDays={wDays} wResult={wResult}/>;
			return topXml;
		}
	}
}
