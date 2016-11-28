/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetRankInfo.as
//  Purpose:      获取排行榜数据
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	/**
	 * 获取排行榜数据的返回的参数组成的结构体
	 */
	public final class SRetParam_GetRankInfo
	{
		public var eType:uint; //(枚举类型：ERankType)排行榜类型
		public var dwMaxCount:uint; //(无符号32位整数)最大排名数量
		public var dwCurIndex:uint; //(无符号32位整数)当前排名索引
		public var dwSelfRank:uint; //(无符号32位整数)自己所在排名
		public var vecRankInfo:Vector.<SRankInfo>; //排行榜数据
		public var vecSelfRankInfo:Vector.<SRankInfo>; //自己所在排名

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetRankInfo _name_={name_} eType={eType} dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex} dwSelfRank={dwSelfRank}/>;
			else
				topXml = <SRetParam_GetRankInfo eType={eType} dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex} dwSelfRank={dwSelfRank}/>;
			if(vecRankInfo != null)
			{
				var vecRankInfoXml:XML = <Vec_SRankInfo _name_="vecRankInfo"/>;
				for each(var s1:SRankInfo in vecRankInfo)
					vecRankInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecRankInfoXml);
			}
			if(vecSelfRankInfo != null)
			{
				var vecSelfRankInfoXml:XML = <Vec_SRankInfo _name_="vecSelfRankInfo"/>;
				for each(var s2:SRankInfo in vecSelfRankInfo)
					vecSelfRankInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecSelfRankInfoXml);
			}
			return topXml;
		}
	}
}
