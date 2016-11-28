/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ExchangeItemList.as
//  Purpose:      已兑换列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	/**
	 * 已兑换列表的返回的参数组成的结构体
	 */
	public final class SRetParam_ExchangeItemList
	{
		public var vecExchangeInfo:Vector.<ExchangeInfo>; //已兑换列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ExchangeItemList _name_={name_}/>;
			else
				topXml = <SRetParam_ExchangeItemList/>;
			if(vecExchangeInfo != null)
			{
				var vecExchangeInfoXml:XML = <Vec_ExchangeInfo _name_="vecExchangeInfo"/>;
				for each(var s1:ExchangeInfo in vecExchangeInfo)
					vecExchangeInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecExchangeInfoXml);
			}
			return topXml;
		}
	}
}
