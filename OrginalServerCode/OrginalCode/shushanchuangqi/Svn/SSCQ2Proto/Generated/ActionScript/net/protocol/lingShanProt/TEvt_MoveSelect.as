/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_MoveSelect.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:移动选择
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数MoveSelect[移动选择]的返回事件
	 */
	public final class TEvt_MoveSelect extends Event
	{
		public static const DATA_RETURN:String = "LingShanProt_MoveSelect";
		public static const DATA_ERROR:String = "LingShanProt_MoveSelect_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_MoveSelect; //返回的参数

		public function TEvt_MoveSelect(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_MoveSelect ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
