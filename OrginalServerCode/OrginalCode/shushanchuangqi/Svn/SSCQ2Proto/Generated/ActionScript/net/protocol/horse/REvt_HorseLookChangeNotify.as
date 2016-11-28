/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_HorseLookChangeNotify.as
//  Purpose:      协议:坐骑, 函数:坐骑外观改变
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数HorseLookChangeNotify[坐骑外观改变]的接收事件
	 */
	public final class REvt_HorseLookChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Horse_HorseLookChangeNotify";
		public static const DATA_ERROR:String = "Horse_HorseLookChangeNotify_Error";

		public var qwRoleID:BigInteger; //(无符号64位整数)角色Id
		public var dwHorseID:uint; //(无符号32位整数)坐骑模型
		public var dwHorseLevel:uint; //(无符号32位整数)坐骑等级

		public function REvt_HorseLookChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_HorseLookChangeNotify qwRoleID={qwRoleID} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel}/>;
			return topXml;
		}
	}
}
