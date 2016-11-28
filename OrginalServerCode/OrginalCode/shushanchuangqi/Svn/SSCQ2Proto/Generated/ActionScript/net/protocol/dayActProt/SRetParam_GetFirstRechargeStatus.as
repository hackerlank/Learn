/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFirstRechargeStatus.as
//  Purpose:      是否已领取首充礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	/**
	 * 是否已领取首充礼包的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFirstRechargeStatus
	{
		public var byRet:uint; //(无符号8位整数)0未充值 1已充值但未领取 2已领取

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFirstRechargeStatus _name_={name_} byRet={byRet}/>;
			else
				topXml = <SRetParam_GetFirstRechargeStatus byRet={byRet}/>;
			return topXml;
		}
	}
}
