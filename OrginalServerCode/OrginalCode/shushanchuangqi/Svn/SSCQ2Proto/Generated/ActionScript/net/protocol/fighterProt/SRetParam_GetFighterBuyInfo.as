/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFighterBuyInfo.as
//  Purpose:      获取购买散仙信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 获取购买散仙信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFighterBuyInfo
	{
		public var vecFighterBuyInfo:Vector.<SFighterBuyInfo>; //购买散仙信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFighterBuyInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetFighterBuyInfo/>;
			if(vecFighterBuyInfo != null)
			{
				var vecFighterBuyInfoXml:XML = <Vec_SFighterBuyInfo _name_="vecFighterBuyInfo"/>;
				for each(var s1:SFighterBuyInfo in vecFighterBuyInfo)
					vecFighterBuyInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecFighterBuyInfoXml);
			}
			return topXml;
		}
	}
}
