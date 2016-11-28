/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ChangeSelfPos.as
//  Purpose:      协议:竞技场协议, 函数:交换自己的将位置
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数ChangeSelfPos[交换自己的将位置]的返回事件
	 */
	public final class TEvt_ChangeSelfPos extends Event
	{
		public static const DATA_RETURN:String = "TeamGS_ChangeSelfPos";
		public static const DATA_ERROR:String = "TeamGS_ChangeSelfPos_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ChangeSelfPos; //返回的参数

		public function TEvt_ChangeSelfPos(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ChangeSelfPos ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
