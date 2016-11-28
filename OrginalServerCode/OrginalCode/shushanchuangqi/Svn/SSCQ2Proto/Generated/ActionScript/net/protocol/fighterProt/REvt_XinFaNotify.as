/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_XinFaNotify.as
//  Purpose:      协议:道具相关协议, 函数:心法数据更新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数XinFaNotify[心法数据更新通知]的接收事件
	 */
	public final class REvt_XinFaNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_XinFaNotify";
		public static const DATA_ERROR:String = "FighterProt_XinFaNotify_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var dwXinFaID:uint; //(无符号32位整数)心法ID
		public var byXinFaLvl:uint; //(无符号8位整数)心法等级
		public var iSlot:int; //(有符号32位整数)心法槽 -1表示心法没装备

		public function REvt_XinFaNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_XinFaNotify qwInstID={qwInstID} dwXinFaID={dwXinFaID} byXinFaLvl={byXinFaLvl} iSlot={iSlot}/>;
			return topXml;
		}
	}
}
