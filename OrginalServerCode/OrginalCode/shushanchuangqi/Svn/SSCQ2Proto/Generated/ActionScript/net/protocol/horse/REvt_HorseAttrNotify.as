/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_HorseAttrNotify.as
//  Purpose:      协议:坐骑, 函数:坐骑属性信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;
	import net.protocol.protoCommon.SFtAttrMod;

	/**
	 * 函数HorseAttrNotify[坐骑属性信息]的接收事件
	 */
	public final class REvt_HorseAttrNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Horse_HorseAttrNotify";
		public static const DATA_ERROR:String = "Horse_HorseAttrNotify_Error";

		public var dwHorseID:uint; //(无符号32位整数)坐骑ID
		public var vecAttrInfo:Vector.<SFtAttrMod>; //坐骑属性信息表

		public function REvt_HorseAttrNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_HorseAttrNotify dwHorseID={dwHorseID}/>;
			if(vecAttrInfo != null)
			{
				var vecAttrInfoXml:XML = <Vec_SFtAttrMod _name_="vecAttrInfo"/>;
				for each(var s1:SFtAttrMod in vecAttrInfo)
					vecAttrInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecAttrInfoXml);
			}
			return topXml;
		}
	}
}
