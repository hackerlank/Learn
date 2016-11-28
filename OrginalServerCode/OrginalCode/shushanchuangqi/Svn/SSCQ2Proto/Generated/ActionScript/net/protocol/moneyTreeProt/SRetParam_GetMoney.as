/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMoney.as
//  Purpose:      请求摇钱
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.moneyTreeProt
{
	/**
	 * 请求摇钱的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMoney
	{
		public var todayUseCount:uint; //(无符号16位整数)今日使用次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetMoney _name_={name_} todayUseCount={todayUseCount}/>;
			else
				topXml = <SRetParam_GetMoney todayUseCount={todayUseCount}/>;
			return topXml;
		}
	}
}
