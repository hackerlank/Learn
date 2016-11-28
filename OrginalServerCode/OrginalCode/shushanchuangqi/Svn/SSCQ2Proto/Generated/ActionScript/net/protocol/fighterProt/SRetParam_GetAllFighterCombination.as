/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllFighterCombination.as
//  Purpose:      获取玩家的所有散仙组合
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 获取玩家的所有散仙组合的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllFighterCombination
	{
		public var vecCombinationInfo:Vector.<SFighterCombination>; //玩家的散仙组合信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllFighterCombination _name_={name_}/>;
			else
				topXml = <SRetParam_GetAllFighterCombination/>;
			if(vecCombinationInfo != null)
			{
				var vecCombinationInfoXml:XML = <Vec_SFighterCombination _name_="vecCombinationInfo"/>;
				for each(var s1:SFighterCombination in vecCombinationInfo)
					vecCombinationInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecCombinationInfoXml);
			}
			return topXml;
		}
	}
}
