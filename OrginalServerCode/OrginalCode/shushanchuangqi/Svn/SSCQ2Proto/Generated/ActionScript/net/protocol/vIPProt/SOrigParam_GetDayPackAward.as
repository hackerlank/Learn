/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_GetDayPackAward.as
//  Purpose:      领取VIP特权每日礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	/**
	 * 领取VIP特权每日礼包的原来的参数组成的结构体
	 */
	public final class SOrigParam_GetDayPackAward
	{
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_GetDayPackAward _name_={name_}/>;
			else
				topXml = <SOrigParam_GetDayPackAward/>;
			return topXml;
		}
	}
}
