/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoleActInfo.as
//  Purpose:      玩家活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	/**
	 * 玩家活动信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoleActInfo
	{
		public var wActIDRet:uint; //(无符号16位整数)活动ID
		public var vecRet:Vector.<SRoleStatus>; //操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoleActInfo _name_={name_} wActIDRet={wActIDRet}/>;
			else
				topXml = <SRetParam_GetRoleActInfo wActIDRet={wActIDRet}/>;
			if(vecRet != null)
			{
				var vecRetXml:XML = <Vec_SRoleStatus _name_="vecRet"/>;
				for each(var s1:SRoleStatus in vecRet)
					vecRetXml.appendChild(s1.toXML());
				topXml.appendChild(vecRetXml);
			}
			return topXml;
		}
	}
}
