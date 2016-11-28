/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoleBuffInfo.as
//  Purpose:      获取角色Buff信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import net.protocol.protoCommon.SBuffInfo;

	/**
	 * 获取角色Buff信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoleBuffInfo
	{
		public var vecBuffInfo:Vector.<SBuffInfo>; //玩家Buff信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoleBuffInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetRoleBuffInfo/>;
			if(vecBuffInfo != null)
			{
				var vecBuffInfoXml:XML = <Vec_SBuffInfo _name_="vecBuffInfo"/>;
				for each(var s1:SBuffInfo in vecBuffInfo)
					vecBuffInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBuffInfoXml);
			}
			return topXml;
		}
	}
}
