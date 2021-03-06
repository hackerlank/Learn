/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMoneyTreeInfo.as
//  Purpose:      请求摇钱树信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.moneyTreeProt
{
	/**
	 * 请求摇钱树信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMoneyTreeInfo
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
				topXml = <SRetParam_GetMoneyTreeInfo _name_={name_} todayUseCount={todayUseCount}/>;
			else
				topXml = <SRetParam_GetMoneyTreeInfo todayUseCount={todayUseCount}/>;
			return topXml;
		}
	}
}
