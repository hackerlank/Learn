/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllPrize.as
//  Purpose:      获得活动所有奖励配置
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	/**
	 * 获得活动所有奖励配置的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllPrize
	{
		public var wActID:uint; //(无符号16位整数)活动ID
		public var sFirstPlayer:SWActPlayerInfo; //第一名玩家信息
		public var sSelfPlayer:SWActPlayerInfo; //玩家自己信息
		public var vecPrizeConfig:Vector.<SPrizeConfig>; //奖励信息
		public var eRet:uint; //(枚举类型：EWActResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllPrize _name_={name_} wActID={wActID} eRet={eRet}/>;
			else
				topXml = <SRetParam_GetAllPrize wActID={wActID} eRet={eRet}/>;
			if(sFirstPlayer != null)
				topXml.appendChild(sFirstPlayer.toXML("sFirstPlayer"));
			if(sSelfPlayer != null)
				topXml.appendChild(sSelfPlayer.toXML("sSelfPlayer"));
			if(vecPrizeConfig != null)
			{
				var vecPrizeConfigXml:XML = <Vec_SPrizeConfig _name_="vecPrizeConfig"/>;
				for each(var s3:SPrizeConfig in vecPrizeConfig)
					vecPrizeConfigXml.appendChild(s3.toXML());
				topXml.appendChild(vecPrizeConfigXml);
			}
			return topXml;
		}
	}
}
