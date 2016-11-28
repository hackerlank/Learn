/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_MalBuy.as
//  Purpose:      商场购买
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	/**
	 * 商场购买的返回的参数组成的结构体
	 */
	public final class SRetParam_MalBuy
	{
		public var eResult:int; //(枚举类型：EMallResult)购买结果返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_MalBuy _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_MalBuy eResult={eResult}/>;
			return topXml;
		}
	}
}
