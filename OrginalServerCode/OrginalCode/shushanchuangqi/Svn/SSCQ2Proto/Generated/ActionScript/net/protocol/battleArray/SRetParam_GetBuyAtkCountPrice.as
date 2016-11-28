/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetBuyAtkCountPrice.as
//  Purpose:      获取当前购买价格
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	/**
	 * 获取当前购买价格的返回的参数组成的结构体
	 */
	public final class SRetParam_GetBuyAtkCountPrice
	{
		public var dwPrice:uint; //(无符号32位整数)价格
		public var dwBuyCount:uint; //(无符号32位整数)当天已购买次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetBuyAtkCountPrice _name_={name_} dwPrice={dwPrice} dwBuyCount={dwBuyCount}/>;
			else
				topXml = <SRetParam_GetBuyAtkCountPrice dwPrice={dwPrice} dwBuyCount={dwBuyCount}/>;
			return topXml;
		}
	}
}
