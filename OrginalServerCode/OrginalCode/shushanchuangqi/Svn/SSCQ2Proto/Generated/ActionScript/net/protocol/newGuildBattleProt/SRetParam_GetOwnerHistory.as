/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetOwnerHistory.as
//  Purpose:      获取历届占领帮会
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	/**
	 * 获取历届占领帮会的返回的参数组成的结构体
	 */
	public final class SRetParam_GetOwnerHistory
	{
		public var vecInfo:Vector.<SOwnerHistoryInfo>; //理解帮派信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetOwnerHistory _name_={name_}/>;
			else
				topXml = <SRetParam_GetOwnerHistory/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SOwnerHistoryInfo _name_="vecInfo"/>;
				for each(var s1:SOwnerHistoryInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
