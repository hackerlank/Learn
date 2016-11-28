/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_CreateGuild.as
//  Purpose:      创建帮派
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 创建帮派的返回的参数组成的结构体
	 */
	public final class SRetParam_CreateGuild
	{
		public var eResult:uint; //(枚举类型：ECreateResult)创建结果
		public var vecGuildInfo:Vector.<SGuildAllInfo>; //帮派信息(大小为0或者1)

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_CreateGuild _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_CreateGuild eResult={eResult}/>;
			if(vecGuildInfo != null)
			{
				var vecGuildInfoXml:XML = <Vec_SGuildAllInfo _name_="vecGuildInfo"/>;
				for each(var s1:SGuildAllInfo in vecGuildInfo)
					vecGuildInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuildInfoXml);
			}
			return topXml;
		}
	}
}
