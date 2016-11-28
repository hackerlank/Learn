/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_QuickPetsLevelUp.as
//  Purpose:      协议:阵灵相关协议, 函数:阵灵一键升级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;

	/**
	 * 函数QuickPetsLevelUp[阵灵一键升级]的返回事件
	 */
	public final class TEvt_QuickPetsLevelUp extends Event
	{
		public static const DATA_RETURN:String = "FormationProt_QuickPetsLevelUp";
		public static const DATA_ERROR:String = "FormationProt_QuickPetsLevelUp_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_QuickPetsLevelUp; //返回的参数

		public function TEvt_QuickPetsLevelUp(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_QuickPetsLevelUp ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
