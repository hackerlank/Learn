/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRoleState.as
//  Purpose:      玩家在个人服活动中的状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import net.protocol.wonderActivityProt.SRoleAllStatus;

	/**
	 * 玩家在个人服活动中的状态的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRoleState
	{
		public var vecRet:Vector.<SRoleAllStatus>; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRoleState _name_={name_}/>;
			else
				topXml = <SRetParam_GetRoleState/>;
			if(vecRet != null)
			{
				var vecRetXml:XML = <Vec_SRoleAllStatus _name_="vecRet"/>;
				for each(var s1:SRoleAllStatus in vecRet)
					vecRetXml.appendChild(s1.toXML());
				topXml.appendChild(vecRetXml);
			}
			return topXml;
		}
	}
}
