/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSecondRechargeStatus.as
//  Purpose:      获取二次充值礼包状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	/**
	 * 获取二次充值礼包状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSecondRechargeStatus
	{
		public var byRet:uint; //(无符号8位整数)0未充值 1已充值但未领取 2已领取
		public var dwSecondRechargeValue:uint; //(无符号32位整数)二次充值累计金额

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSecondRechargeStatus _name_={name_} byRet={byRet} dwSecondRechargeValue={dwSecondRechargeValue}/>;
			else
				topXml = <SRetParam_GetSecondRechargeStatus byRet={byRet} dwSecondRechargeValue={dwSecondRechargeValue}/>;
			return topXml;
		}
	}
}
