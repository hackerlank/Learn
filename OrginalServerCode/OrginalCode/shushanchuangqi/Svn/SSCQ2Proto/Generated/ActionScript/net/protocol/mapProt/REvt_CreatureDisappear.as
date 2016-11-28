/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CreatureDisappear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知地图上生物消失
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数CreatureDisappear[通知地图上生物消失]的接收事件
	 */
	public final class REvt_CreatureDisappear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_CreatureDisappear";
		public static const DATA_ERROR:String = "MapProt_CreatureDisappear_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var bDieFade:Boolean; //true为死亡消失，false为移出视野

		public function REvt_CreatureDisappear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CreatureDisappear qwCreatureID={qwCreatureID} bDieFade={bDieFade}/>;
			return topXml;
		}
	}
}
