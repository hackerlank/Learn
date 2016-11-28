/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_LadderPageUpReq.as
//  Purpose:      请求天梯排名
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求天梯排名的返回的参数组成的结构体
	 */
	public final class SRetParam_LadderPageUpReq
	{
		public var eResult:uint; //(枚举类型：EArenaResult)查询结果
		public var vecRankData:Vector.<SArenaRank2Client>; //排行榜数据

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_LadderPageUpReq _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_LadderPageUpReq eResult={eResult}/>;
			if(vecRankData != null)
			{
				var vecRankDataXml:XML = <Vec_SArenaRank2Client _name_="vecRankData"/>;
				for each(var s1:SArenaRank2Client in vecRankData)
					vecRankDataXml.appendChild(s1.toXML());
				topXml.appendChild(vecRankDataXml);
			}
			return topXml;
		}
	}
}
