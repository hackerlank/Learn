/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFightHeroInfo.as
//  Purpose:      战斗散仙信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	/**
	 * 战斗散仙信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFightHeroInfo
	{
		public var vecFightHeroInfo:Vector.<FightHeroInfo>; //战斗阵形信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFightHeroInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetFightHeroInfo/>;
			if(vecFightHeroInfo != null)
			{
				var vecFightHeroInfoXml:XML = <Vec_FightHeroInfo _name_="vecFightHeroInfo"/>;
				for each(var s1:FightHeroInfo in vecFightHeroInfo)
					vecFightHeroInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecFightHeroInfoXml);
			}
			return topXml;
		}
	}
}
