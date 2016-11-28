/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuyGEMEntryNum.as
//  Purpose:      请求购买守卫峨眉进入次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	/**
	 * 请求购买守卫峨眉进入次数的返回的参数组成的结构体
	 */
	public final class SRetParam_BuyGEMEntryNum
	{
		public var eGEMOptResult:int; //(枚举类型：EGEMOptResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuyGEMEntryNum _name_={name_} eGEMOptResult={eGEMOptResult}/>;
			else
				topXml = <SRetParam_BuyGEMEntryNum eGEMOptResult={eGEMOptResult}/>;
			return topXml;
		}
	}
}
