/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_CompareOtherBPByID.as
//  Purpose:      协议:变强(战力对比)相关协议, 函数:战斗力对比
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.compareBattlePoint
{
	import flash.events.Event;

	/**
	 * 函数CompareOtherBPByID[战斗力对比]的返回事件
	 */
	public final class TEvt_CompareOtherBPByID extends Event
	{
		public static const DATA_RETURN:String = "CompareBattlePoint_CompareOtherBPByID";
		public static const DATA_ERROR:String = "CompareBattlePoint_CompareOtherBPByID_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_CompareOtherBPByID; //返回的参数

		public function TEvt_CompareOtherBPByID(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_CompareOtherBPByID ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
