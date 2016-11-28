/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPassInfo.as
//  Purpose:      获取过关信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	/**
	 * 获取过关信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPassInfo
	{
		public var vecMinRound:Vector.<SDemonTowerKillMonster>; //最快通关
		public var vecMinBattlePoint:Vector.<SDemonTowerKillMonster>; //最小战斗力通关

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPassInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetPassInfo/>;
			if(vecMinRound != null)
			{
				var vecMinRoundXml:XML = <Vec_SDemonTowerKillMonster _name_="vecMinRound"/>;
				for each(var s1:SDemonTowerKillMonster in vecMinRound)
					vecMinRoundXml.appendChild(s1.toXML());
				topXml.appendChild(vecMinRoundXml);
			}
			if(vecMinBattlePoint != null)
			{
				var vecMinBattlePointXml:XML = <Vec_SDemonTowerKillMonster _name_="vecMinBattlePoint"/>;
				for each(var s2:SDemonTowerKillMonster in vecMinBattlePoint)
					vecMinBattlePointXml.appendChild(s2.toXML());
				topXml.appendChild(vecMinBattlePointXml);
			}
			return topXml;
		}
	}
}
