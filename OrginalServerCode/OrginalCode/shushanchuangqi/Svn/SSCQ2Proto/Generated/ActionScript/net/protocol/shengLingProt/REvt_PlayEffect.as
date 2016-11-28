/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayEffect.as
//  Purpose:      协议:圣陵协议, 函数:播放特效
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;

	/**
	 * 函数PlayEffect[播放特效]的接收事件
	 */
	public final class REvt_PlayEffect extends Event
	{
		public static const DATA_RECEIVE:String = "ShengLingProt_PlayEffect";
		public static const DATA_ERROR:String = "ShengLingProt_PlayEffect_Error";


		public function REvt_PlayEffect(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayEffect/>;
			return topXml;
		}
	}
}
