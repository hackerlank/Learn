/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoleSpecInfo.as
//  Purpose:      获取角色面板信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	/**
	 * 获取角色面板信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoleSpecInfo
	{
		public var stRoleStream:SRoleStream; //角色信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoleSpecInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetRoleSpecInfo/>;
			if(stRoleStream != null)
				topXml.appendChild(stRoleStream.toXML("stRoleStream"));
			return topXml;
		}
	}
}
