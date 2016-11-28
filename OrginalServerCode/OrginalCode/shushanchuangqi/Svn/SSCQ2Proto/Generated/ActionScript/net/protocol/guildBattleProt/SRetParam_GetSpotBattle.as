/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSpotBattle.as
//  Purpose:      据点战报获取
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 据点战报获取的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSpotBattle
	{
		public var eResult:uint; //(枚举类型：EGBBattleResult)战报获取结果
		public var vecBattleData:Vector.<SBattleData>; //战报信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSpotBattle _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetSpotBattle eResult={eResult}/>;
			if(vecBattleData != null)
			{
				var vecBattleDataXml:XML = <Vec_SBattleData _name_="vecBattleData"/>;
				for each(var s1:SBattleData in vecBattleData)
					vecBattleDataXml.appendChild(s1.toXML());
				topXml.appendChild(vecBattleDataXml);
			}
			return topXml;
		}
	}
}
