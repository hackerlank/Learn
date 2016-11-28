/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSpotInfo.as
//  Purpose:      帮派据点信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 帮派据点信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSpotInfo
	{
		public var eResult:uint; //(枚举类型：EGBResult)返回结果
		public var vecSpotInfo:Vector.<SSpotInfo>; //据点详细信息（数量为0/1）

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSpotInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetSpotInfo eResult={eResult}/>;
			if(vecSpotInfo != null)
			{
				var vecSpotInfoXml:XML = <Vec_SSpotInfo _name_="vecSpotInfo"/>;
				for each(var s1:SSpotInfo in vecSpotInfo)
					vecSpotInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSpotInfoXml);
			}
			return topXml;
		}
	}
}
