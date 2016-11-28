/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetGuildApplyInfo.as
//  Purpose:      获取帮派申请列表信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 获取帮派申请列表信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetGuildApplyInfo
	{
		public var eResult:uint; //(枚举类型：EGuildResult)返回结果
		public var vecApplyInfo:Vector.<SGuildApplyInfo>; //申请列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetGuildApplyInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetGuildApplyInfo eResult={eResult}/>;
			if(vecApplyInfo != null)
			{
				var vecApplyInfoXml:XML = <Vec_SGuildApplyInfo _name_="vecApplyInfo"/>;
				for each(var s1:SGuildApplyInfo in vecApplyInfo)
					vecApplyInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecApplyInfoXml);
			}
			return topXml;
		}
	}
}
