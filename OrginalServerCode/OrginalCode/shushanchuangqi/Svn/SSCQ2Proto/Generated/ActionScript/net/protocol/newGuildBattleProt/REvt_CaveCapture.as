/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CaveCapture.as
//  Purpose:      协议:新帮派战相关协议, 函数:洞府战被占领通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数CaveCapture[洞府战被占领通知]的接收事件
	 */
	public final class REvt_CaveCapture extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_CaveCapture";
		public static const DATA_ERROR:String = "NewGuildBattleProt_CaveCapture_Error";

		public var eMountainType:uint; //(枚举类型：ENGBMountain)灵山类型
		public var strGuildName:String; //当前占领帮派名称

		public function REvt_CaveCapture(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CaveCapture eMountainType={eMountainType} strGuildName={strGuildName}/>;
			return topXml;
		}
	}
}
