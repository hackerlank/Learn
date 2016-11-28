/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NameChangeNotify.as
//  Purpose:      协议:属性相关协议, 函数:Creature的名字改变通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NameChangeNotify[Creature的名字改变通知]的接收事件
	 */
	public final class REvt_NameChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "PropInfo_NameChangeNotify";
		public static const DATA_ERROR:String = "PropInfo_NameChangeNotify_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var strName:String; //新名字

		public function REvt_NameChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NameChangeNotify qwCreatureID={qwCreatureID} strName={strName}/>;
			return topXml;
		}
	}
}
