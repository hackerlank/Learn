/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllAward.as
//  Purpose:      请求奖励信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求奖励信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllAward
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求刷将返回
		public var vecAwards:Vector.<SArenaAward>; //奖励包状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllAward _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetAllAward eResult={eResult}/>;
			if(vecAwards != null)
			{
				var vecAwardsXml:XML = <Vec_SArenaAward _name_="vecAwards"/>;
				for each(var s1:SArenaAward in vecAwards)
					vecAwardsXml.appendChild(s1.toXML());
				topXml.appendChild(vecAwardsXml);
			}
			return topXml;
		}
	}
}
