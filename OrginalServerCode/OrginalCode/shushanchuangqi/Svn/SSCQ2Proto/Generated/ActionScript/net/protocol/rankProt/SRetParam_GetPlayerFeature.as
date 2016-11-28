/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPlayerFeature.as
//  Purpose:      获得玩家外观信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import net.protocol.battleGS.SFeatureBase;

	/**
	 * 获得玩家外观信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPlayerFeature
	{
		public var eResult:uint; //(枚举类型：ERankResult)崇拜结果
		public var pFeature:SFeatureBase; //外观信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPlayerFeature _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetPlayerFeature eResult={eResult}/>;
			if(pFeature != null)
				topXml.appendChild(pFeature.toXML("pFeature"));
			return topXml;
		}
	}
}
