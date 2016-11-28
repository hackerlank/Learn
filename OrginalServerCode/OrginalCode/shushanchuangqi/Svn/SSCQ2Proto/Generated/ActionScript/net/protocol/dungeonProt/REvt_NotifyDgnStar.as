/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyDgnStar.as
//  Purpose:      协议:副本相关协议, 函数:通告副本星级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数NotifyDgnStar[通告副本星级]的接收事件
	 */
	public final class REvt_NotifyDgnStar extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_NotifyDgnStar";
		public static const DATA_ERROR:String = "DungeonProt_NotifyDgnStar_Error";

		public var wDgnType:uint; //(无符号16位整数)副本类型
		public var vecStar:Vector.<MulCond>; //副本星级

		public function REvt_NotifyDgnStar(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyDgnStar wDgnType={wDgnType}/>;
			if(vecStar != null)
			{
				var vecStarXml:XML = <Vec_MulCond _name_="vecStar"/>;
				for each(var s1:MulCond in vecStar)
					vecStarXml.appendChild(s1.toXML());
				topXml.appendChild(vecStarXml);
			}
			return topXml;
		}
	}
}
