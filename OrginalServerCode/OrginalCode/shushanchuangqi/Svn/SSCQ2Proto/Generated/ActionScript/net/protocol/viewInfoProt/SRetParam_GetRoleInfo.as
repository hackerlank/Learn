/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoleInfo.as
//  Purpose:      获取对方主角信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	/**
	 * 获取对方主角信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoleInfo
	{
		public var RoleData:SRoleData; //对方主角信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoleInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetRoleInfo/>;
			if(RoleData != null)
				topXml.appendChild(RoleData.toXML("RoleData"));
			return topXml;
		}
	}
}
