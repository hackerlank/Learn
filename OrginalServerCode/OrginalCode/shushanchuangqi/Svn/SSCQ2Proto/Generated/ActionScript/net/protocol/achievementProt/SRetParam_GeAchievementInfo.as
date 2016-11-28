/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GeAchievementInfo.as
//  Purpose:      获取成就信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	/**
	 * 获取成就信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GeAchievementInfo
	{
		public var vecAchievementInfo:Vector.<SAchievementInfo>; //成就榜信息
		public var wLevel:uint; //(无符号16位整数)成就等级
		public var dwAP:uint; //(无符号32位整数)成就点

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GeAchievementInfo _name_={name_} wLevel={wLevel} dwAP={dwAP}/>;
			else
				topXml = <SRetParam_GeAchievementInfo wLevel={wLevel} dwAP={dwAP}/>;
			if(vecAchievementInfo != null)
			{
				var vecAchievementInfoXml:XML = <Vec_SAchievementInfo _name_="vecAchievementInfo"/>;
				for each(var s1:SAchievementInfo in vecAchievementInfo)
					vecAchievementInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecAchievementInfoXml);
			}
			return topXml;
		}
	}
}
