/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetPlayerRankInfo.as
//  Purpose:      获取战功榜个人排名信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	/**
	 * 获取战功榜个人排名信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetPlayerRankInfo
	{
		public var eResult:uint; //(枚举类型：ENGBResult)返回结果
		public var dwMaxCount:uint; //(无符号32位整数)最大排名数量
		public var dwCurIndex:uint; //(无符号32位整数)当前排名索引
		public var vecInfo:Vector.<SPlayerRankInfo>; //排名信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetPlayerRankInfo _name_={name_} eResult={eResult} dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex}/>;
			else
				topXml = <SRetParam_GetPlayerRankInfo eResult={eResult} dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SPlayerRankInfo _name_="vecInfo"/>;
				for each(var s1:SPlayerRankInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
