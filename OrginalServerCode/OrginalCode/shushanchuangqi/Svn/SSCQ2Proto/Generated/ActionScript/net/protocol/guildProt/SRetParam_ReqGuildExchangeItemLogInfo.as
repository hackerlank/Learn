/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ReqGuildExchangeItemLogInfo.as
//  Purpose:      请求帮派兑换物品日志信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 请求帮派兑换物品日志信息的返回的参数组成的结构体
	 */
	public final class SRetParam_ReqGuildExchangeItemLogInfo
	{
		public var vecGuildLogInfo:Vector.<SGuildLogInfo>; //兑换物品日志信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ReqGuildExchangeItemLogInfo _name_={name_}/>;
			else
				topXml = <SRetParam_ReqGuildExchangeItemLogInfo/>;
			if(vecGuildLogInfo != null)
			{
				var vecGuildLogInfoXml:XML = <Vec_SGuildLogInfo _name_="vecGuildLogInfo"/>;
				for each(var s1:SGuildLogInfo in vecGuildLogInfo)
					vecGuildLogInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildLogInfoXml);
			}
			return topXml;
		}
	}
}
