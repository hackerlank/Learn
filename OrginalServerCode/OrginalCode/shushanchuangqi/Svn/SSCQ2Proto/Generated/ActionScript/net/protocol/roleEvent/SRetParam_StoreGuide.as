/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_StoreGuide.as
//  Purpose:      存储新手引导信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	/**
	 * 存储新手引导信息的返回的参数组成的结构体
	 */
	public final class SRetParam_StoreGuide
	{
		public var bResult:Boolean; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_StoreGuide _name_={name_} bResult={bResult}/>;
			else
				topXml = <SRetParam_StoreGuide bResult={bResult}/>;
			return topXml;
		}
	}
}
