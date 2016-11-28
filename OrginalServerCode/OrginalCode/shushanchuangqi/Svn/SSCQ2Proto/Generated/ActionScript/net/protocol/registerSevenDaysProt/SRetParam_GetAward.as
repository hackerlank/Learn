/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAward.as
//  Purpose:      获取奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
{
	/**
	 * 获取奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAward
	{
		public var eResult:uint; //(枚举类型：ERegisterSevenDaysResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAward _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetAward eResult={eResult}/>;
			return topXml;
		}
	}
}
