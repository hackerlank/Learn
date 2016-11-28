/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuyFenbaoyan.as
//  Purpose:      分宝岩购买活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	/**
	 * 分宝岩购买活动的返回的参数组成的结构体
	 */
	public final class SRetParam_BuyFenbaoyan
	{
		public var eRet:uint; //(枚举类型：EMiscOptRes)购买结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuyFenbaoyan _name_={name_} eRet={eRet}/>;
			else
				topXml = <SRetParam_BuyFenbaoyan eRet={eRet}/>;
			return topXml;
		}
	}
}
