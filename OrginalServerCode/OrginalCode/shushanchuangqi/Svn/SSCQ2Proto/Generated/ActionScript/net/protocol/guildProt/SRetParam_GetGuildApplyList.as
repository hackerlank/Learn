/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetGuildApplyList.as
//  Purpose:      获得已申请帮派列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 获得已申请帮派列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetGuildApplyList
	{
		public var eResult:uint; //(枚举类型：EApplyResult)返回结果
		public var vecGuildListInfo:Vector.<SGuildListInfo>; //帮派列表信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetGuildApplyList _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetGuildApplyList eResult={eResult}/>;
			if(vecGuildListInfo != null)
			{
				var vecGuildListInfoXml:XML = <Vec_SGuildListInfo _name_="vecGuildListInfo"/>;
				for each(var s1:SGuildListInfo in vecGuildListInfo)
					vecGuildListInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildListInfoXml);
			}
			return topXml;
		}
	}
}
