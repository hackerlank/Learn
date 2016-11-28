/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuyDiscountItem.as
//  Purpose:      购买商场限购道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	/**
	 * 购买商场限购道具的返回的参数组成的结构体
	 */
	public final class SRetParam_BuyDiscountItem
	{
		public var eResult:int; //(枚举类型：EMallResult)购买结果返回
		public var byPos:uint; //(无符号8位整数)限购位置(0,1,2)
		public var wCount:uint; //(无符号16位整数)购买个数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuyDiscountItem _name_={name_} eResult={eResult} byPos={byPos} wCount={wCount}/>;
			else
				topXml = <SRetParam_BuyDiscountItem eResult={eResult} byPos={byPos} wCount={wCount}/>;
			return topXml;
		}
	}
}
