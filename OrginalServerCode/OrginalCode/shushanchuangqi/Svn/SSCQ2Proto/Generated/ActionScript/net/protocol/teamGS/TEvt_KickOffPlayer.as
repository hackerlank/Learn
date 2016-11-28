/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_KickOffPlayer.as
//  Purpose:      协议:竞技场协议, 函数:请求踢玩家出队伍
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数KickOffPlayer[请求踢玩家出队伍]的返回事件
	 */
	public final class TEvt_KickOffPlayer extends Event
	{
		public static const DATA_RETURN:String = "TeamGS_KickOffPlayer";
		public static const DATA_ERROR:String = "TeamGS_KickOffPlayer_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_KickOffPlayer; //返回的参数

		public function TEvt_KickOffPlayer(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_KickOffPlayer ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
