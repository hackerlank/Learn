/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ChangeModel.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:更换模型信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数ChangeModel[更换模型信息]的返回事件
	 */
	public final class TEvt_ChangeModel extends Event
	{
		public static const DATA_RETURN:String = "LingShanProt_ChangeModel";
		public static const DATA_ERROR:String = "LingShanProt_ChangeModel_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ChangeModel; //返回的参数

		public function TEvt_ChangeModel(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ChangeModel ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
