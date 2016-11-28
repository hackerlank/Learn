/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PropQWListNotify.as
//  Purpose:      协议:属性相关协议, 函数:属性列表通知(改变后通知)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数PropQWListNotify[属性列表通知(改变后通知)]的接收事件
	 */
	public final class REvt_PropQWListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "PropInfo_PropQWListNotify";
		public static const DATA_ERROR:String = "PropInfo_PropQWListNotify_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)变更对象ID
		public var eClass:uint; //(枚举类型：EPropClass)变更对象类型
		public var vecPropValue:Vector.<SPropQWValue>; //属性列表

		public function REvt_PropQWListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PropQWListNotify qwInstID={qwInstID} eClass={eClass}/>;
			if(vecPropValue != null)
			{
				var vecPropValueXml:XML = <Vec_SPropQWValue _name_="vecPropValue"/>;
				for each(var s1:SPropQWValue in vecPropValue)
					vecPropValueXml.appendChild(s1.toXML());
				topXml.appendChild(vecPropValueXml);
			}
			return topXml;
		}
	}
}
