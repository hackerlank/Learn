/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_InstinctActiveNotify.as
//  Purpose:      协议:道具相关协议, 函数:散仙血脉激活
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数InstinctActiveNotify[散仙血脉激活]的接收事件
	 */
	public final class REvt_InstinctActiveNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_InstinctActiveNotify";
		public static const DATA_ERROR:String = "FighterProt_InstinctActiveNotify_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)散仙唯一ID
		public var vecInstinctIDRandom:Vector.<uint>; //(无符号16位整数)血脉随机结果
		public var vecInstinctIDRet:Vector.<uint>; //(无符号16位整数)血脉最终结果

		public function REvt_InstinctActiveNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_InstinctActiveNotify qwInstID={qwInstID}/>;
			if(vecInstinctIDRandom != null)
			{
				var vecInstinctIDRandomXml:XML = <Vec_UINT16 _name_="vecInstinctIDRandom"/>;
				var text1:String = "";
				for each(var value1:uint in vecInstinctIDRandom)
					text1 += "[" + value1 + "]";
				vecInstinctIDRandomXml.appendChild(text1);
				topXml.appendChild(vecInstinctIDRandomXml);
			}
			if(vecInstinctIDRet != null)
			{
				var vecInstinctIDRetXml:XML = <Vec_UINT16 _name_="vecInstinctIDRet"/>;
				var text2:String = "";
				for each(var value2:uint in vecInstinctIDRet)
					text2 += "[" + value2 + "]";
				vecInstinctIDRetXml.appendChild(text2);
				topXml.appendChild(vecInstinctIDRetXml);
			}
			return topXml;
		}
	}
}
