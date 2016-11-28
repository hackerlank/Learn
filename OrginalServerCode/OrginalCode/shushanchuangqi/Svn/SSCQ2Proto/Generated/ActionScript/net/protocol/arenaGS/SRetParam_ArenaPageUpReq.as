/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaPageUpReq.as
//  Purpose:      请求翻页
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求翻页的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaPageUpReq
	{
		public var eResult:uint; //(枚举类型：EArenaResult)查询结果
		public var dwSize:uint; //(无符号32位整数)本段位的人数总计
		public var vecRankData:Vector.<SArenaRank2Client>; //排行榜数据

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaPageUpReq _name_={name_} eResult={eResult} dwSize={dwSize}/>;
			else
				topXml = <SRetParam_ArenaPageUpReq eResult={eResult} dwSize={dwSize}/>;
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
