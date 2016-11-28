/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllWirship.as
//  Purpose:      请求膜拜信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求膜拜信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllWirship
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var vecWirshipFigter:Vector.<SArenaRank2Client>; //膜拜对象列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllWirship _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetAllWirship eResult={eResult}/>;
			if(vecWirshipFigter != null)
			{
				var vecWirshipFigterXml:XML = <Vec_SArenaRank2Client _name_="vecWirshipFigter"/>;
				for each(var s1:SArenaRank2Client in vecWirshipFigter)
					vecWirshipFigterXml.appendChild(s1.toXML());
				topXml.appendChild(vecWirshipFigterXml);
			}
			return topXml;
		}
	}
}
