/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetGuardInfo.as
//  Purpose:      获取镇守信息信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	/**
	 * 获取镇守信息信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetGuardInfo
	{
		public var vecGuardInfo:Vector.<GuardInfo>; //镇守信息信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetGuardInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetGuardInfo/>;
			if(vecGuardInfo != null)
			{
				var vecGuardInfoXml:XML = <Vec_GuardInfo _name_="vecGuardInfo"/>;
				for each(var s1:GuardInfo in vecGuardInfo)
					vecGuardInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuardInfoXml);
			}
			return topXml;
		}
	}
}
