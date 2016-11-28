/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SampleFuncAck1.as
//  Purpose:      协议:通信协议示例, 函数:S->C示例函数1
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.BytesUtil;

	/**
	 * 函数SampleFuncAck1[S->C示例函数1]的接收事件
	 */
	public final class REvt_SampleFuncAck1 extends Event
	{
		public static const DATA_RECEIVE:String = "Example_SampleFuncAck1";
		public static const DATA_ERROR:String = "Example_SampleFuncAck1_Error";

		public var byParam1:int; //(有符号8位整数)8位有符号整数
		public var wParam2:int; //(有符号16位整数)16位有符号整数
		public var dwParam3:int; //(有符号32位整数)32位有符号整数
		public var qwParam4:BigInteger; //(有符号64位整数)64位有符号整数
		public var byParam5:uint; //(无符号8位整数)8位无符号整数
		public var wParam6:uint; //(无符号16位整数)16位无符号整数
		public var dwParam7:uint; //(无符号32位整数)32位无符号整数
		public var qwParam8:BigInteger; //(无符号64位整数)64位无符号整数
		public var bParam9:Boolean; //布尔值
		public var fParam10:Number; //(Float)单精度浮点数
		public var dParam11:Number; //(Double)双精度浮点数
		public var strParam12:String; //字符串
		public var strParam13:ByteArray; //AS字节数组
		public var eTest14:int; //(枚举类型：EExTest)枚举值
		public var vecExDesc15:Vector.<SExDescend4>; //继承结构体列表

		public function REvt_SampleFuncAck1(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SampleFuncAck1 byParam1={byParam1} wParam2={wParam2} dwParam3={dwParam3} qwParam4={qwParam4} byParam5={byParam5}
				 wParam6={wParam6} dwParam7={dwParam7} qwParam8={qwParam8} bParam9={bParam9} fParam10={fParam10}
				 dParam11={dParam11} strParam12={strParam12} strParam13={BytesUtil.bytes2String(strParam13)} eTest14={eTest14}/>;
			if(vecExDesc15 != null)
			{
				var vecExDesc15Xml:XML = <Vec_SExDescend4 _name_="vecExDesc15"/>;
				for each(var s1:SExDescend4 in vecExDesc15)
					vecExDesc15Xml.appendChild(s1.toXML());
				topXml.appendChild(vecExDesc15Xml);
			}
			return topXml;
		}
	}
}
